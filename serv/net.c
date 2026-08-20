#include "net.h"

// Appends one personnage's full order line to *order, growing order_send /
// refreshing *order on realloc exactly like the inline code this was factored
// out of. send_x/send_y are passed separately from p->x/p->y so a caller can
// report a fake position (-100, -100) for an entity that just left visibility
// range, instead of its real (and, for the receiving client, stale) location.
static void append_perso_to_order(char **order, struct personnages *p, int32_t id, float send_x, float send_y)
{
    sprintf(*order + strlen(*order), "%s %d %d %d %d %d %d %d %d %c %s %s %s %s %d %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %s %s %s %s %s %s %s %f %f %f %f %f [",
    p->skin, id, p->pv, p->nb_vassaux, p->faim, p->inside, p->house_id, p->animation, p->animation_2, p->angle, p->physique, p->nom_de_compte, p->nom,  p->nom_superieur, p->echange_player,
    p->items_cnt[0], p->items[0], p->items_cnt[1], p->items[1], p->items_cnt[2], p->items[2], p->items_cnt[3], p->items[3], p->items_cnt[4], p->items[4], p->items_cnt[5], p->items[5],
    p->items_cnt[6], p->items[6], p->items_cnt[7], p->items[7], p->items_cnt[8], p->items[8], p->items_cnt[9], p->items[9], p->items_cnt[10], p->items[10], p->items_cnt[11], p->items[11],
    p->items[12], p->items[13],p->items[14], p->items[15],p->items[16], p->items[17], send_x, send_y, p->altitude, p->ordrex, p->ordrey);
    for (struct linked_enemie *pp = p->e_list; pp != NULL; pp = pp->next)
    {
        if (pp->next != NULL)
            sprintf (*order + strlen(*order), "%s %d ", pp->nom, pp->rang);
        else
            sprintf (*order + strlen(*order), "%s %d", pp->nom, pp->rang);
    }
    sprintf(*order + strlen(*order),  "] [%s]%s\n",p->skill, p->speak);
    if (1.1 * strlen(*order) > size_order_send)
    {
        size_order_send *= 2;
        order_send = realloc(order_send, size_order_send);
        *order = &order_send[10];
    }
}

// Appends one building's order line to *order, growing order_send / refreshing
// *order on realloc. send_x/send_y let a caller report -100 -100 for a
// building that just left visibility range, same idea as append_perso_to_order.
static void append_building_to_order(char **order, struct building *pa, int send_x, int send_y)
{
    sprintf(*order + strlen(*order), "%s %d %d %d %d %c %c\n", pa->skin, pa->id, pa->pv, send_x, send_y, pa->angle, pa->state);
    if (1.1 * strlen(*order) > size_order_send)
    {
        size_order_send *= 2;
        order_send = realloc(order_send, size_order_send);
        *order = &order_send[10];
    }
}

// Builds order_send with only what `player_id` needs to hear about this tick
// (visible entities that just entered range (state 1) unconditionally,
// already-visible ones (state 2) only if they actually changed (a_bouger),
// and entities that just left range (state 3) unconditionally, reported at
// position -100 -100 so the client can drop them), then sends it right away
// — there's no shared/broadcast buffer to reuse across players anymore, so
// generating and sending are one step.
// a_bouger itself is NOT reset here since every connected player is served
// from the same a_bouger snapshot during this tick; see reset_a_bouger().
void send_order_to_player(int socket, int player_id)
{
    char *order = &order_send[10];
	order[0] = 0;
    struct visible_entities_list *vis = &visible_entities[player_id];
    for (int k = 0; k < vis->size; k++)
    {
        VisibleEntity *ve = &vis->data[k];
        if (ve->type == VISIBLE_ENTITY_TYPE_PERSO)
        {
            struct personnages *p = &list.data[ve->id];
            if (ve->state != 1 && ve->state != 3 && !(ve->state == 2 && p->a_bouger == 1))
                continue;
            if (ve->state == 3)
                append_perso_to_order(&order, p, ve->id, -100, -100);
            else
                append_perso_to_order(&order, p, ve->id, p->x, p->y);
        }
        else // VISIBLE_ENTITY_TYPE_BUILDING
        {
            struct building *pa = get_ptr_from_id_building(ve->id);
            if (pa == NULL)
                continue;
            if (ve->state != 1 && ve->state != 3 && !(ve->state == 2 && pa->a_bouger == 1))
                continue;
            if (ve->state == 3)
                append_building_to_order(&order, pa, -100, -100);
            else
                append_building_to_order(&order, pa, pa->x, pa->y);
        }
    }

    // Entities at 0 PV are reported to every player unconditionally, regardless
    // of distance/visibility, so a death is never missed just because the
    // killer or the victim was out of the receiving player's sight.
    for (int i = 0; i <= list.maxid; i++)
    {
        if (list.data[i].is_active == 1 && list.data[i].pv <= 0)
            append_perso_to_order(&order, &list.data[i], i, list.data[i].x, list.data[i].y);
    }
    for (struct building *pa = list_building; pa != NULL; pa = pa->next)
    {
        if (pa->pv <= 0)
            append_building_to_order(&order, pa, pa->x, pa->y);
    }

    int s = strlen(order);
    sprintf (order_send, "%d", s);
    send_all(socket, s + 10, (uint8_t *)order_send);
}

// The global a_bouger reset, decoupled from any single player's send so every
// connected player gets to compare against the same pre-tick a_bouger values.
void reset_a_bouger(void)
{
    for (int i = 0; i <= list.maxid; i++)
        if (list.data[i].is_active == 1)
            list.data[i].a_bouger = 0;
    for (struct building *pa = list_building; pa != NULL; pa = pa->next)
        pa->a_bouger = 0;
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