#pragma once
#include "shared_var.h"
#include <stdio.h>
#include <stdlib.h>
#include "../shared/utile.h"

struct building
{
    int id;
    int pv;
    int x;
    int y;
    char skin[4];
    char angle;
    char state;
    ////////////////////////////
    char counter;
    struct building *next;
	char a_bouger;
};

int append_building(char *line, char *skin, int id);
int parse_new_building(struct building *b, char *line, char *skin, int id);
void remove_building_altitude(struct building *b);
void add_building_altitude(struct building *b);
struct building *get_ptr_from_id_building(int id);
int find_smalest_valid_id_building(int from);
void add_wood_pillar_or_wood_house(int moix, int moiy);
void will_create_building(void);