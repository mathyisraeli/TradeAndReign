#include "shared_var.h"
int max_x;
int max_y;
int max_y_biom;
int max_x_biom;
struct linked_ground **ground;
struct dynamic_char_list list;
struct dynamic_char_bioms_list *list_bioms;
struct building *list_building = NULL;
uint8_t **building_altitude;
int *building_id;

uint8_t send_ground_buffer[7500];
int index_check_altitude[99999];
char size_background[20];

int n_ground_altitude;
char *order_send;
size_t size_order_send;
int rdm_directions[4] = {1,2,3,4};