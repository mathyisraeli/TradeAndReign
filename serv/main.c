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

int main(int argc, char **argv)
{
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

    char ground_path[64];
    char map_path[64];
    snprintf(ground_path, sizeof(ground_path), "world/g%d.txt", world_id);
    snprintf(map_path, sizeof(map_path), "world/m%d.txt", world_id);

    unsigned int save_map_count = 0;
	char *ground_str;
	load_file_as_string(ground_path, &ground_str);
	create_array(ground_str);
    free(ground_str);
    init_bioms();
	init_map(map_path);
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
            if ((events[i].events & EPOLLERR) ||
                    (events[i].events & EPOLLHUP) ||
                    (!(events[i].events & EPOLLIN)))
            {
                close (events[i].data.fd);
				statut[i] = 0;
                chars_connected[i]->online = '0';
                chars_connected[i] = NULL;
                continue;
            }
            else if (sfd == events[i].data.fd)
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
                        if (statut[i] == 0)
                        {
                            struct personnages *p = have_char(buf);
							if (open_acount(buf) == 1 && p != NULL && p->online != '1') // good acount and password
							{
								statut[i] = 1;
								s = write (events[i].data.fd, "o", 1);
								chars_connected[i] = p;
                                s = write(events[i].data.fd, size_background, 20);
                                send_ground(chars_connected[i], events[i].data.fd);
                                send_all_chars(events[i].data.fd);
                                p->online = '1';
							}
							else
                            {
								s = write (events[i].data.fd, "n", 1);
                            }
                        }
                        else
							parse_order(buf); 
                    }
				}
                if (done)
                {
                    if (statut[i] == 1)
                    {
                        chars_connected[i]->online = '0';
                        chars_connected[i] = NULL;
                    }
					statut[i] = 0;
                    close (events[i].data.fd);
                }
            }
        }
        gettimeofday(&end, NULL);
        double elapsedTime = (end.tv_sec - start.tv_sec) * 1000.0;      // sec to ms
        elapsedTime += (end.tv_usec - start.tv_usec) / 1000.0;
        if (elapsedTime >= 75)
        {
        	start = end;
            //printf ("handle altitude\n");
            handle_altitude();
            ia();
            //printf ("collision\n");
            collision();
            int size_order = generate_order();
            for (int i = 0; i < MAXEVENTS ;i++)
            {
                if (statut[i] == 1)
			    {
               	    send(events[i].data.fd, order_send, size_order+10, MSG_NOSIGNAL);
                    send_ground(chars_connected[i], events[i].data.fd);
			    }
            }
            death();
            will_create_building();
            save_map_count += 1;
            if (save_map_count % 60 == 0)
            {
                melt_snow(save_map_count%max_x);
                if (save_map_count % 12000 == 0)
                {
                    //save_map(save_map_count/12000);
                    //save_ground(save_map_count/12000);
                }
            }
            
            //printf ("elapsedTime = %5.3fms \n", elapsedTime);
		}
    }

    free (events);

    close (sfd);

    return EXIT_SUCCESS;
}
