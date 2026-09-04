#include "main.h"
#include "shared_var.h"

static int create_and_bind (char *port)
{
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int s, sfd;
    memset (&hints, 0, sizeof (struct addrinfo));
    hints.ai_family = AF_UNSPEC;     /* Return IPv4 and IPv6 choices */
    hints.ai_socktype = SOCK_STREAM; /* We want a TCP socket */
    hints.ai_flags = AI_PASSIVE;     /* All interfaces */
    s = getaddrinfo (NULL, port, &hints, &result);
    if (s != 0)
    {   
        fprintf (stderr, "getaddrinfo: %s\n", gai_strerror (s));
        return -1;
    }
    for (rp = result; rp != NULL; rp = rp->ai_next)
    {
        sfd = socket (rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (sfd == -1)
            continue;
        s = bind (sfd, rp->ai_addr, rp->ai_addrlen);
        if (s == 0)
            break;
        close (sfd);
    }
    if (rp == NULL)
    {
        fprintf (stderr, "Could not bind\n");
        return -1;
    }
    freeaddrinfo (result);
    return sfd;
}

static int make_socket_non_blocking (int sfd)
{
    int flags, s;
    flags = fcntl (sfd, F_GETFL, 0);
    if (flags == -1)
    {
        perror ("fcntl");
        return -1;
    }
    flags |= O_NONBLOCK;
    s = fcntl (sfd, F_SETFL, flags);
    if (s == -1)
    {
        perror ("fcntl");
        return -1;
    }
    return 0;
}

#define MAXEVENTS 64

// Returns the highest n such that "<base_path without .txt>_n.txt" exists on
// disk (checked sequentially from 1, since save numbers are only ever
// appended by save_map()/save_ground() and never skipped or deleted), or 0
// if no saved version exists yet.
static int find_latest_version(const char *base_path)
{
    char path[96];
    int n = 0;
    while (1)
    {
        sprintf(path, "%.*s_%d.txt", (int)(strlen(base_path) - 4), base_path, n + 1);
        FILE *f = fopen(path, "r");
        if (f == NULL)
            break;
        fclose(f);
        n++;
    }
    return n;
}

int main(int argc, char **argv)
{
    setvbuf(stdout, NULL, _IONBF, 0);
    setbuf(stdout, NULL);
	if (argc != 3)
	{
		printf("usage: %s <port> <world_id 1-12>\n", argv[0]);
		return 1;
	}

    int world_id = atoi(argv[2]);
    if (world_id < 1 || world_id > 12)
    {
        printf("error: world_id must be between 1 and 12\n");
        return 1;
    }

    snprintf(ground_path, sizeof(ground_path), "world/g%d.txt", world_id);
    snprintf(map_path, sizeof(map_path), "world/m%d.txt", world_id);

    int save_version = find_latest_version(ground_path);
    char load_ground_path[96];
    char load_map_path[96];
    if (save_version > 0)
    {
        sprintf(load_ground_path, "%.*s_%d.txt", (int)(strlen(ground_path) - 4), ground_path, save_version);
        sprintf(load_map_path, "%.*s_%d.txt", (int)(strlen(map_path) - 4), map_path, save_version);
        printf("loading world %d, latest save version %d\n", world_id, save_version);
    }
    else
    {
        strcpy(load_ground_path, ground_path);
        strcpy(load_map_path, map_path);
        printf("loading world %d, no saved version found, using base files\n", world_id);
    }

    unsigned int save_map_count = 0;
	char *ground_str;
	load_file_as_string(load_ground_path, &ground_str);
	create_array(ground_str);
    free(ground_str);
    init_bioms();
	init_map(load_map_path);
    init_visible_entities();
    count_pop(world_id);
    heap_pathfinding.data = malloc(sizeof(int)*max_x*max_y);
    heap_pathfinding.size = 0;
	char statut[MAXEVENTS] = {0};
	struct personnages *chars_connected[MAXEVENTS];
	//int afktiming[MAXEVENTS + 5] = {0};

    int sfd, s;
    int efd;
    struct epoll_event event;
    struct epoll_event *events;
	sfd = create_and_bind (argv[1]);
    if (sfd == -1)
        abort ();
    s = make_socket_non_blocking (sfd);
    if (s == -1)
        abort ();
    s = listen (sfd, SOMAXCONN);
    if (s == -1)
    {
        perror ("listen");
        abort ();
    }
    efd = epoll_create1 (0);
    if (efd == -1)
    {
        perror ("epoll_create");
        abort ();
    }
    event.data.fd = sfd;
    event.events = EPOLLIN | EPOLLET;
    s = epoll_ctl (efd, EPOLL_CTL_ADD, sfd, &event);
    if (s == -1)
    {
        perror ("epoll_ctl");
        abort ();
    }

    /* Buffer where events are returned */
    events = calloc (MAXEVENTS, sizeof event);

	order_send = malloc(10000);
    size_order_send = 10000;
	//debout boucle, on suppose que la carte est initialisée.
    struct timeval start;struct timeval end;
    gettimeofday(&start, NULL);
	while (1)
    {
        int n, i;
        n = epoll_wait (efd, events, MAXEVENTS, 0);
        for (i = 0; i < n; i++)
        {
            int fd = events[i].data.fd;
            if ((events[i].events & EPOLLERR) ||
                    (events[i].events & EPOLLHUP) ||
                    (!(events[i].events & EPOLLIN)))
            {
                close (fd);
				statut[fd] = 0;
                chars_connected[fd]->online = '0';
                chars_connected[fd] = NULL;
                continue;
            }
            else if (sfd == fd)
            {
                /* We have a notification on the listening socket, which
                 * means one or more incoming connections. */
                while (1)
                {
                    struct sockaddr in_addr;
                    socklen_t in_len;
                    int infd;
#if 0
                    char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];
#endif

                    in_len = sizeof in_addr;
                    infd = accept (sfd, &in_addr, &in_len);
                    if (infd == -1)
                    {
                        printf("errno=%d, EAGAIN=%d, EWOULDBLOCK=%d\n", errno, EAGAIN, EWOULDBLOCK);
                        if ((errno == EAGAIN) ||
                                (errno == EWOULDBLOCK))
                        {
                            /* We have processed all incoming
                             * connections. */
                            printf ("processed all incoming connections.\n");
							break;
                        }
                        else
                        {
                            perror ("accept");
                            break;
                        }
                    }


                    /* Make the incoming socket non-blocking and add it to the
                     * list of fds to monitor. */
                    s = make_socket_non_blocking (infd);
                    if (s == -1)
                        abort ();

                    event.data.fd = infd;
                    event.events = EPOLLIN | EPOLLET;
                    printf("set events %u, infd=%d\n", event.events, infd);
                    s = epoll_ctl (efd, EPOLL_CTL_ADD, infd, &event);
                    if (s == -1)
                    {
                        perror ("epoll_ctl");
                        abort ();
                    }
                }
                /*              continue; */
            }
            else
			{
				/* We have data on the fd waiting to be read. Read and
                 * display it. We must read whatever data is available
                 * completely, as we are running in edge-triggered mode
                 * and won't get a notification again for the same
                 * data. */
                int done = 0;

                while (1)
                {
                    ssize_t count;
                    char buf[99999];
                    count = read (events[i].data.fd, buf, sizeof buf);
                    if (count == -1)
                    {
                        /* If errno == EAGAIN, that means we have read all
                         * data. So go back to the main loop. */
                        if (errno != EAGAIN)
                        {
                            printf  ("error reading order\n");
                            done = 1;
                        }
                        break;
                    }
                    else if (count == 0)
                    {
                        /* End of file. The remote has closed the
                         * connection. */
                        done = 1;
                        break;
                    }
                    else
                    {
                        buf[count] = 0;
                        if (statut[fd] == 0)
                        {
                            struct personnages *p = have_char(  buf);
                            //printf ("%d %p %d\n", open_acount(buf), p, p->online );
							if (open_acount(buf) == 1 && p != NULL && p->online != '1') // good acount and password
							{
								statut[fd] = 1;
								s = write (fd, "o", 1);
								chars_connected[fd] = p;
                                s = write(fd, size_background, 20);
                                send_ground(chars_connected[fd], fd);
                                p->online = '1';
                                int player_id = p - list.data;
                                reset_visible_entities_for_player(player_id);
                                update_visible_entities_for_player(player_id);
                                add_self_to_visible_entities(player_id);
                                send_order_to_player(fd, player_id);
							}
							else
                            {
								s = write (fd, "n", 1);
                            }
                        }
                        else
							parse_order(buf); 
                    }
				}
                if (done)
                {
                    if (statut[fd] == 1)
                    {
                        chars_connected[fd]->online = '0';
                        chars_connected[fd] = NULL;
                    }
					statut[fd] = 0;
                    close (fd);
                }
            }
        }
        gettimeofday(&end, NULL);
        double elapsedTime = (end.tv_sec - start.tv_sec) * 1000.0;      // sec to ms
        elapsedTime += (end.tv_usec - start.tv_usec) / 1000.0;
        if (elapsedTime >=50)
        {
        	start = end;
            if (save_map_count % 5 == 0)
                handle_altitude();
            ia();
            printf ("%f\n", elapsedTime);
            collision();
            update_visible_entities();
            for (int i = 0; i < MAXEVENTS ;i++)
            {
                if (statut[i] == 1)
			    {
                    int player_id = chars_connected[i] - list.data;
                    send_order_to_player(i, player_id);
                    send_ground(chars_connected[i], i);
			    }
            }
            reset_a_bouger();
            death();
            will_create_building();
            save_map_count += 1;
            if (save_map_count % 60 == 0)
            {
                melt_snow();
                if (save_map_count % 18000 == 0) // 18000 ticks * 50ms = 15 min
                {
                    save_version += 1;
                    save_map(save_version);
                    save_ground(save_version);
                }
            }
            
            //printf ("elapsedTime = %5.3fms \n", elapsedTime);
		}
    }

    free (events);

    close (sfd);

    return EXIT_SUCCESS;
}
