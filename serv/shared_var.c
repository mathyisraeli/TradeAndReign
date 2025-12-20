#include "shared_var.h"
int max_x;
int max_y;
struct linked_ground **ground;
struct personnages **list_bioms = NULL;
struct building *list_building = NULL;
uint8_t **building_altitude;
int *building_id;

int index_ground_modif[99999];
int index_check_altitude[99999];
int n_ground_modif;
int n_ground_altitude;
char *background_send;
char *order_send;
size_t size_background_send;
size_t size_order_send;
int rdm_directions[4] = {1,2,3,4};