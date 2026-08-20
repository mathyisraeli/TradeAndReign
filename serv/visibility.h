#pragma once
#include <stdint.h>
#include "shared_var.h"

#define VISIBLE_ENTITY_TYPE_PERSO 0
#define VISIBLE_ENTITY_TYPE_BUILDING 1
#define VISIBLE_RADIUS 21.0f

typedef struct {
    uint8_t type;
    int32_t id;
    uint8_t state;
} VisibleEntity;

struct visible_entities_list {
    VisibleEntity *data;
    int size;
    int capacity;
};

extern struct visible_entities_list *visible_entities;

void init_visible_entities(void);
void update_visible_entities(void);
void update_visible_entities_for_player(int player_id);
void reset_visible_entities_for_player(int player_id);
void add_self_to_visible_entities(int player_id);
