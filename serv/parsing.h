#pragma once
#include "perso.h"
#include "building.h"
#include "ground.h"

int parse_new(struct personnages *p, char *line, char *skin);
int parse_new_building(struct building *b, char *line, char *skin, int id);
void parse_order(char *line);
