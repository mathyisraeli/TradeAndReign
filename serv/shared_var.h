#pragma once
#include <stddef.h>
#include "dynamic_characters_list.h"

extern struct dynamic_char_list list;
extern struct dynamic_char_bioms_list *list_bioms;
extern struct building *list_building;
extern  struct linked_ground **ground;
extern uint8_t **building_altitude;
extern int *building_id;
extern int max_x;
extern int max_y;
extern int max_x_biom;
extern int max_y_biom;
extern uint8_t send_ground_buffer[7500];
extern char size_background[20];
extern int n_ground_altitude;
extern char *order_send;
extern size_t size_order_send;
extern char will_create_building_char[999];
extern int rdm_directions[4];
extern struct heap heap_pathfinding;
extern char ground_path[64];
extern char map_path[64];