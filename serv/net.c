#include "net.h"

void send_all_chars(int socket)
{
    socket = socket;
    
    char *order = &order_send[10];
	order[0] = 0;
    for (int i = 0; i <= list.maxid; i++)
    {
        if (list.data[i].is_active != 1)
            continue;
        struct personnages *p = &list.data[i];
        sprintf(order + strlen(order), "%s %d %d %d %d %d %d %d %d %c %s %s %s %s %d %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %s %s %s %s %s %s %s %f %f %f %f %f [",
        p->skin, i, p->pv, p->nb_vassaux, p->faim, p->inside, p->house_id, p->animation, p->animation_2, p->angle, p->physique, p->nom_de_compte, p->nom,  p->nom_superieur, p->echange_player,
        p->items_cnt[0], p->items[0], p->items_cnt[1], p->items[1], p->items_cnt[2], p->items[2], p->items_cnt[3], p->items[3], p->items_cnt[4], p->items[4], p->items_cnt[5], p->items[5],
        p->items_cnt[6], p->items[6], p->items_cnt[7], p->items[7], p->items_cnt[8], p->items[8], p->items_cnt[9], p->items[9], p->items_cnt[10], p->items[10], p->items_cnt[11], p->items[11],
        p->items[12], p->items[13],p->items[14], p->items[15],p->items[16], p->items[17], p->x, p->y, p->altitude, p->ordrex, p->ordrey);
        for (struct linked_enemie *pp = p->e_list; pp != NULL; pp = pp->next)
        {
            if (pp->next != NULL)
                sprintf (order + strlen(order), "%s %d ", pp->nom, pp->rang);
            else
                sprintf (order + strlen(order), "%s %d", pp->nom, pp->rang);
        }
        sprintf(order + strlen(order),  "] [%s]%s\n",p->skill, p->speak); 
        if (1.1 * strlen(order) > size_order_send)
        {
            size_order_send *= 2;
            printf ("size_order_send %ld\n", size_order_send);
            order_send = realloc(order_send, size_order_send);
            order = &order_send[10];
        }
    }
    for (struct building *pa = list_building; pa != NULL; pa = pa->next)
    { 
        sprintf(order + strlen(order), "%s %d %d %d %d %c %c\n", pa->skin, pa->id, pa->pv, pa->x, pa->y, pa->angle,pa->state);
        if (1.1 * strlen(order) > size_order_send)
        {
            size_order_send *= 2;
            printf ("size_order_send %ld\n", size_order_send);
            order_send = realloc(order_send, size_order_send);
            order = &order_send[10];
        }
    }
    int s = strlen(order);
    sprintf (order_send, "%d", s);
    send(socket, order_send, s + 10, MSG_NOSIGNAL);
}

int generate_order()
{
    //printf ("generate_order 1\n");
    char *order = &order_send[10];
	order[0] = 0;
    for (int i = 0; i <= list.maxid; i++)
    {
        if (list.data[i].is_active != 1 && list.data[i].a_bouger != 1)
            continue;
        struct personnages *p = &list.data[i];
        sprintf(order + strlen(order), "%s %d %d %d %d %d %d %d %d %c %s %s %s %s %d %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %s %s %s %s %s %s %s %f %f %f %f %f [",
        p->skin, i, p->pv, p->nb_vassaux, p->faim, p->inside, p->house_id, p->animation, p->animation_2, p->angle, p->physique, p->nom_de_compte, p->nom,  p->nom_superieur, p->echange_player,
        p->items_cnt[0], p->items[0], p->items_cnt[1], p->items[1], p->items_cnt[2], p->items[2], p->items_cnt[3], p->items[3], p->items_cnt[4], p->items[4], p->items_cnt[5], p->items[5],
        p->items_cnt[6], p->items[6], p->items_cnt[7], p->items[7], p->items_cnt[8], p->items[8], p->items_cnt[9], p->items[9], p->items_cnt[10], p->items[10], p->items_cnt[11], p->items[11],
        p->items[12], p->items[13],p->items[14], p->items[15],p->items[16], p->items[17], p->x, p->y, p->altitude, p->ordrex, p->ordrey);
        for (struct linked_enemie *pp = p->e_list; pp != NULL; pp = pp->next)
        {
            if (pp->next != NULL)
                sprintf (order + strlen(order), "%s %d ", pp->nom, pp->rang);
            else
                sprintf (order + strlen(order), "%s %d", pp->nom, pp->rang);
        }
        sprintf(order + strlen(order),  "] [%s]%s\n",p->skill, p->speak); 
        p->a_bouger = 0;
        if (1.1 * strlen(order) > size_order_send)
        {
            size_order_send *= 2;
            //printf ("size_order_send %ld\n", size_order_send);
            order_send = realloc(order_send, size_order_send);
            order = &order_send[10];
        }
    }
    for (struct building *pa = list_building; pa != NULL; pa = pa->next)
    { 
        if (pa->a_bouger != 0)
        {
            sprintf(order + strlen(order), "%s %d %d %d %d %c %c\n", pa->skin, pa->id, pa->pv, pa->x, pa->y, pa->angle,pa->state);
            pa->a_bouger = 0;
            if (1.1 * strlen(order) > size_order_send)
            {
                size_order_send *= 2;
                printf ("size_order_send %ld\n", size_order_send);
                order_send = realloc(order_send, size_order_send);
                order = &order_send[10];
            }
        }
    }
    int s = strlen(order);
    sprintf (order_send, "%d", s);
    return s;
}

void send_ground(struct personnages *p, int socket)
{
    //printf ("%d %d %d %d\n", max(0, (int)p->y - 24), min(max_y, (int)p->y + 24), max(0, (int)p->x - 24), min(max_x, (int)p->x + 24));
    uint16_t offset = 2;
    for (int i = max(0, (int)p->y - 24); i < min(max_y, (int)p->y + 24); i++)
    {
        for (int j = max(0, (int)p->x - 24); j < min(max_x, (int)p->x + 24); j++)
        {
            send_ground_buffer[offset++] =  (uint8_t)ground[i *max_x+j]->texture;
            int16_t alt = htons(altitude(i * max_x + j));
            memcpy(send_ground_buffer + offset, &alt, sizeof(alt));
            offset += sizeof(alt);
        }
    }
    uint16_t size = htons(offset-2);
    memcpy(send_ground_buffer, &size, sizeof(size));
    send_all(socket, offset, send_ground_buffer);
    //printf ("%d\n", offset);
}

void send_all(int socket, int size, uint8_t *to_send)
{
    int sent = 0;
    while (sent < size)
    {
        int r = send(socket, to_send+sent, size-sent, MSG_NOSIGNAL);
        if (r < 0)
        {
            if (errno == EAGAIN || errno == EWOULDBLOCK)
            {
                struct pollfd pfd;
                pfd.fd = socket;
                pfd.events = POLLOUT;

                poll(&pfd, 1, -1);

                continue;
            }
            else
                break;
        }
        else if (r == 0)
            break;
        else
            sent += r;
    }
}


void parse_order(char *line)
{
    int i = 0;
    int j;
    char tmpC[50];
    while (line[i] != 0)
    { 
        tmpC[0] = line[i];
        i += 2;
        int id = atoi(&line[i]);
        while (line[i] != ' ')
            i+= 1;
        i += 1;
        int idaction = atoi(&line[i]);
        i += 3;
        if (tmpC[0] == '0') // living
        {
            struct personnages *p = &list.data[id];
            switch(idaction)
            {
                case 0:
                    if (line[i] == '+')
                    {
                        i++;
                        p->pv += atoi(&line[i]);
                    }
                    else if (line[i] == '-')
                    {
                        i++;
                        p->pv -= atoi(&line[i]);
                    }
                    else
                    {
                        i++;
                        p->pv = atoi(&line[i]);
                    }
                    while(line[i] != ' ')
                        i++;
                    i++;
                    break;
                case 1:
                    if (line[i] == '+')
                    {
                        i++;
                        p->moved_x += atof(&line[i]);
                        p->faim -= 1;
                    }
                    else if (line[i] == '-')
                    {
                        i++;
                        p->moved_x -= atof(&line[i]);
                        p->faim -= 1;
                    }
                    else
                        p->x = atof(&line[i]);
                    while(line[i] != ' ')
                        i++;
                    i++;
                    break;
                case 2:
                    if (line[i] == '+')
                    {
                        i++;
                        p->moved_y += atof(&line[i]);
                        p->faim -= 1;
                    }
                    else if (line[i] == '-')
                    {
                        i++;
                        p->moved_y -= atof(&line[i]);
                        p->faim -= 1;
                    }
                    else
                        p->y = atof(&line[i]);
                    while(line[i] != ' ')
                        i++;
                    i++;
                    break;
                case 3:
                    p->ordrex = atof(&line[i]);
                    while(line[i] != ' ')
                        i++;
                    i++;
                    break;
                case 4:
                    p->ordrey = atof(&line[i]);
                    while(line[i] != ' ')
                        i++;
                    i++;
                    break;
                case 5:
                    p->angle = line[i];
                    i += 2;
                    break;
                case 6:
                    p->timer_dom = atoi(&line[i]);
                    while(line[i] != ' ')
                        i++;
                    i++;
                    break;
                case 7:
                    p->faim += atoi(&line[i]);
                    while(line[i] != ' ')
                        i++;
                    i++;
                    break;
                case 8:
                    remove_1_pixel(atoi(&line[i]));
                    while(line[i] != ' ')
                        i++;
                    i++;
                    break;
                case 9:
                    p->inside = atoi(&line[i]);
                    while(line[i] != ' ')
                    {
                        i++;
                    }
                    i++;
                    break;
                case 10:
                    j = 0;
                    while(line[i] != ' ')
                    {
                        p->nom_superieur[j] = line[i];
                        i++;
                        j++;
                    }
                    p->nom_superieur[j] = 0;
                    i++;
                    break;

                case 13:
                    int index = atoi(&line[i]);
                    while(line[i] != ' ')
                        i++;
                    i++;
                    add_1_pixel(index, texture_from_string(line + i));
                    i += 4;
                    break;
                case 14:
                    if (line[i] == '+')
                    {
                        i++;
                        p->nb_vassaux += atoi(&line[i]);
                    }
                    else if (line[i] == '-')
                    {
                        i++;
                        p->nb_vassaux -= atoi(&line[i]);
                    }
                    else
                        p->nb_vassaux = atof(&line[i]);
                    while(line[i] != ' ')
                        i++;
                    i++;
                    break;
                case 15:// Modifie enemie
                    if (line[i] == '+') // Rajoute enemie
                    {
                        i++;
                        int n = atoi(&line[i]);
                        while (line[i] != ' ')
                            i++;
                        i++;
                        j = 0;
                        while (line[i] != ' ')
                        {
                            tmpC[j] = line[i];
                            j++;
                            i++;
                        }
                        tmpC[j] = 0;
                        i++;
                        p->e_list = append_enemie(tmpC, p->e_list, n);
                    }
                    else // enleve enemie
                    {
                        j = 0;
                        while (line[i] != ' ')
                        {
                            tmpC[j] = line[i];
                            j++;
                            i++;
                        }
                        tmpC[j] = 0;
                        i++;
                        p->e_list = remove_enemie(tmpC, p->e_list);
                    }
                    break;
                case 16: // pas sur
                    if (line[i] == '+')
                    {
                        i++;
                        int n = atoi(&line[i]);
                        while (line[i] != ' ')
                            i++;
                        i++;
                        j = 0;
                        while (line[i] != ' ')
                        {
                            tmpC[j] = line[i];
                            j++;
                            i++;
                        }
                        tmpC[j] = 0;
                        i++;
                        append_in_inventory(tmpC,n , p->items, p->items_cnt);
                    }
                    else
                    {
                        int n = atoi(&line[i]);
                        while (line[i] != ' ')
                            i++;
                        i++;
                        j = 0;
                        while (line[i] != ' ')
                        {
                            tmpC[j] = line[i];
                            j++;
                            i++;
                        }
                        tmpC[j] = 0;
                        i++;
                        remove_from_inventory(tmpC, n, p->items, p->items_cnt);
                    }
                    break;
                case 17:
                    p->echange_player = atoi(&line[i]);
                    while (line[i] != ' ')
                    {
                        i++;    
                    }
                    i++;
                    j = 0;
                    while (line[i] != ' ')
                    {
                        p->items[10][j] = line[i];
                        i++;
                        j++;
                    }
                    p->items[10][j] = 0;
                    i++;
                    p->items_cnt[10] = atoi(&line[i]);
                    while(line[i] != ' ')
                        i++;
                    i++;
                    j = 0;
                    while (line[i] != ' ')
                    {
                        p->items[11][j] = line[i];
                        i++;
                        j++;
                    }
                    p->items[11][j] = 0;
                    i++;
                    p->items_cnt[11] = atoi(&line[i]);
                    while(line[i] != ' ')
                        i++;
                    i++;
                    break;
                case 20: // pas sur
                    j = 0;
                    while (line[i] != 31)
                    {
                        p->speak[j] = line[i];
                        i++;
                        j++;
                    }
                    p->speak[j] = 0;
                    i += 2;
                    break;
                case 21:
                    p->animation = atoi(&line[i]);
                    while(line[i] != ' ')
                        i++;
                    i++;
                    break;
                case 22:
                    p->animation_2 = atoi(&line[i]);
                    while (line[i] != ' ')
                        i++;
                    i++;
                    break;
                case 23:
                    p->chemin_is_set = line[i] - '0';
                    i += 2;
                    break;
                case 24:
                    j = 0;
                    while(line[i] != ' ')
                    {
                        p->items[12][j] = line[i];
                        i++;
                        j++;
                    }
                    p->items[12][j] = 0;
                    i++;
                    break;
                case 25:
                    j = 0;
                    while(line[i] != ' ')
                    {
                        p->items[13][j] = line[i];
                        i++;
                        j++;
                    }
                    p->items[13][j] = 0;
                    i++;
                    break;
                case 26:
                    j = 0;
                    while(line[i] != ' ')
                    {
                        p->items[14][j] = line[i];
                        i++;
                        j++;
                    }
                    p->items[14][j] = 0;
                    i++;
                    break;
                case 27:
                    j = 0;
                    while(line[i] != ' ')
                    {
                        p->items[15][j] = line[i];
                        i++;
                        j++;
                    }
                    p->items[15][j] = 0;
                    i++;
                    break;
                case 28:
                    j = 0;
                    while(line[i] != ' ')
                    {
                        p->items[16][j] = line[i];
                        i++;
                        j++;
                    }
                    p->items[16][j] = 0;
                    i++;
                    break;
                case 29:
                    j = 0;
                    while(line[i] != ' ')
                    {
                        p->items[17][j] = line[i];
                        i++;
                        j++;
                    }
                    p->items[17][j] = 0;
                    i++;
                    break;
                case 31:
                    if (line[i] == '+')
                    {
                        i++;
                        p->altitude += atoi(&line[i]);
                    }
                    else if (line[i] == '-')
                    {
                        i++;
                        p->altitude -= atoi(&line[i]);
                    }
                    else
                    {
                        i++;
                        p->altitude = atoi(&line[i]);
                    }
                    while(line[i] != ' ')
                        i++;
                    i++;
                    break;
                case 32:
                    p->house_id = atoi(&line[i]);
                    while(line[i] != ' ')
                        i++;
                    i++;
                    break;
            }
            p->a_bouger = 1;
        }
        else if (tmpC[0] == '1') // building
        {
            struct building *b = get_ptr_from_id_building(id);
            switch(idaction)
            {
                case 0:
                    if (line[i] == '+')
                    {
                        i++;
                        b->pv += atoi(&line[i]);
                    }
                    else if (line[i] == '-')
                    {
                        i++;
                        b->pv -= atoi(&line[i]);
                    }
                    else
                    {
                        b->pv = atoi(&line[i]);
                    }
                    while(line[i] != ' ')
                        i++;
                    i++;
                    break;
                case 1:
                    if (line[i] == '+')
                    {
                        b->a_bouger = 2;
                        i++;
                        b->x += atof(&line[i]);
                    }
                    else if (line[i] == '-')
                    {
                        b->a_bouger = 3;
                        i++;
                        b->x -= atof(&line[i]);
                    }
                    else
                        b->x = atof(&line[i]);
                    while(line[i] != ' ')
                        i++;
                    i++;
                    break;
                case 2:
                    if (line[i] == '+')
                    {
                        b->a_bouger = 4;
                        i++;
                        b->y += atof(&line[i]);
                    }
                    else if (line[i] == '-')
                    {
                        b->a_bouger = 5;
                        i++;
                        b->y -= atof(&line[i]);
                    }
                    else
                        b->y = atof(&line[i]);
                    while(line[i] != ' ')
                        i++;
                    i++;
                    break;
                case 3:
                    if (b->angle == 'a')
                        b->a_bouger = 6;
                    else if (b->angle == 'b')
                        b->a_bouger = 7;
                    else if (b->angle == 'k')
                        b->a_bouger = 8;
                    else if (b->angle == 'e')
                        b->a_bouger = 9;
                    b->angle = line[i];
                    i += 2;
                    break;
                case 4:
                    b->state = line[i];
                    i += 2;
                    break;
            }
            b->a_bouger = 1;
        }
    }
}