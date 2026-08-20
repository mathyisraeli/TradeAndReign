#include "visibility.h"
#include "dynamic_characters_list.h"
#include "bioms.h"
#include "building.h"
#include <stdlib.h>

struct visible_entities_list *visible_entities = NULL;
static int visible_entities_capacity = 0;

void init_visible_entities(void)
{
    visible_entities_capacity = list.capacity;
    visible_entities = calloc(visible_entities_capacity, sizeof(struct visible_entities_list));
}

static void grow_visible_entities(void)
{
    if (list.capacity <= visible_entities_capacity)
        return;
    int old_capacity = visible_entities_capacity;
    visible_entities_capacity = list.capacity;
    visible_entities = realloc(visible_entities, visible_entities_capacity * sizeof(struct visible_entities_list));
    for (int i = old_capacity; i < visible_entities_capacity; i++)
    {
        visible_entities[i].data = NULL;
        visible_entities[i].size = 0;
        visible_entities[i].capacity = 0;
    }
}

static void append_current(VisibleEntity **current, int *size, int *capacity, uint8_t type, int32_t id)
{
    if (*size == *capacity)
    {
        *capacity = *capacity == 0 ? 8 : *capacity * 2;
        *current = realloc(*current, *capacity * sizeof(VisibleEntity));
    }
    (*current)[*size].type = type;
    (*current)[*size].id = id;
    (*current)[*size].state = 0;
    *size += 1;
}

// (type, id) couples currently within VISIBLE_RADIUS of player p, gathered via the
// 25x25 biom grid for personnages (checked exactly on a per-perso basis) and a plain
// scan for buildings, which have no biom index.
// Public (not static) since it's also called directly on login, before the player
// is folded into the tick loop's update_visible_entities().
void update_visible_entities_for_player(int p)
{
    grow_visible_entities();
    struct personnages *player = &list.data[p];

    VisibleEntity *current = NULL;
    int current_size = 0;
    int current_capacity = 0;

    int xbiom = (int)(player->x * 0.04f); //0.04 = 1/25
    int ybiom = (int)(player->y * 0.04f);

    for (int dy = -1; dy <= 1; dy++)
    {
        int ny = ybiom + dy;
        if (ny < 0 || ny >= max_y_biom)
            continue;
        for (int dx = -1; dx <= 1; dx++)
        {
            int nx = xbiom + dx;
            if (nx < 0 || nx >= max_x_biom)
                continue;
            struct dynamic_char_bioms_list *cell = &list_bioms[nx + ny * max_x_biom];
            for (int i = 0; i < cell->size; i++)
            {
                int q = cell->data[i];
                if (q == p || list.data[q].is_active != 1)
                    continue;
                float ddx = list.data[q].x - player->x;
                float ddy = list.data[q].y - player->y;
                if (ddx * ddx + ddy * ddy <= VISIBLE_RADIUS * VISIBLE_RADIUS)
                    append_current(&current, &current_size, &current_capacity, VISIBLE_ENTITY_TYPE_PERSO, q);
            }
        }
    }

    for (struct building *b = list_building; b != NULL; b = b->next)
    {
        if (b->pv <= 0)
            continue;
        float ddx = (float)b->x - player->x;
        float ddy = (float)b->y - player->y;
        if (ddx * ddx + ddy * ddy <= VISIBLE_RADIUS * VISIBLE_RADIUS)
            append_current(&current, &current_size, &current_capacity, VISIBLE_ENTITY_TYPE_BUILDING, b->id);
    }

    struct visible_entities_list *vis = &visible_entities[p];

    // The gathering loop above skips q == p on purpose, so the player's own
    // entry (added once at login by add_self_to_visible_entities) has to be
    // carried forward by hand on every recompute, or it would vanish the
    // first time this runs after login.
    int self_present = 0;
    for (int j = 0; j < vis->size; j++)
    {
        if (vis->data[j].type == VISIBLE_ENTITY_TYPE_PERSO && vis->data[j].id == p)
        {
            self_present = 1;
            break;
        }
    }

    for (int i = 0; i < current_size; i++)
    {
        int already_visible = 0;
        for (int j = 0; j < vis->size; j++)
        {
            if (vis->data[j].type == current[i].type && vis->data[j].id == current[i].id)
            {
                already_visible = 1;
                break;
            }
        }
        current[i].state = already_visible ? 2 : 1;
    }

    // Entities that were visible last tick but aren't in `current` anymore
    // (out of range) aren't dropped immediately: they're kept one more tick
    // with state 3 so send_order_to_player() can tell the client "this one
    // left" (position -100 -100). An entry already at state 3 has already
    // been reported that way, so this time it's dropped for good instead.
    for (int j = 0; j < vis->size; j++)
    {
        VisibleEntity *old = &vis->data[j];
        if (old->type == VISIBLE_ENTITY_TYPE_PERSO && old->id == p)
            continue; // self is tracked separately via self_present above

        int still_visible = 0;
        for (int i = 0; i < current_size; i++)
        {
            if (current[i].type == old->type && current[i].id == old->id)
            {
                still_visible = 1;
                break;
            }
        }
        if (still_visible)
            continue;

        if (old->state == 3)
            continue; // was reported as leaving last tick; purge it now

        append_current(&current, &current_size, &current_capacity, old->type, old->id);
        current[current_size - 1].state = 3;
    }

    if (self_present)
    {
        append_current(&current, &current_size, &current_capacity, VISIBLE_ENTITY_TYPE_PERSO, p);
        current[current_size - 1].state = 2;
    }

    free(vis->data);
    vis->data = current;
    vis->size = current_size;
    vis->capacity = current_capacity;
}

// Adds the player's own character to their own visibility list. Called once,
// right after login (see main.c), since the gathering loop in
// update_visible_entities_for_player deliberately skips q == p; from then on
// the entry is carried forward automatically by that function (see
// self_present above), so this never needs to run again for that player.
void add_self_to_visible_entities(int player_id)
{
    grow_visible_entities();
    struct visible_entities_list *vis = &visible_entities[player_id];
    if (vis->size == vis->capacity)
    {
        vis->capacity = vis->capacity == 0 ? 8 : vis->capacity * 2;
        vis->data = realloc(vis->data, vis->capacity * sizeof(VisibleEntity));
    }
    vis->data[vis->size].type = VISIBLE_ENTITY_TYPE_PERSO;
    vis->data[vis->size].id = player_id;
    vis->data[vis->size].state = 1;
    vis->size += 1;
}

void update_visible_entities(void)
{
    for (int i = 0; i <= list.maxid; i++)
    {
        if (list.data[i].is_active == 1 && list.data[i].online == '1')
            update_visible_entities_for_player(i);
    }
}

// Drops whatever a player's collection held from a previous session so that,
// right after (re)connecting, everything currently in range comes back as
// state 1 (new) instead of being silently gated behind a stale a_bouger check.
void reset_visible_entities_for_player(int player_id)
{
    grow_visible_entities();
    struct visible_entities_list *vis = &visible_entities[player_id];
    free(vis->data);
    vis->data = NULL;
    vis->size = 0;
    vis->capacity = 0;
}
