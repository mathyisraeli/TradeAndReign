#pragma once
#include "perso.h"
#include "building.h"
#include "../shared/linked_item.h"
#include "ground.h"

int generate_order();
void send_ground(struct personnages *p, int socket);
void send_all_chars(int socket);