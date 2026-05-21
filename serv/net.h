#pragma once
#include "perso.h"
#include "building.h"
#include "../shared/linked_item.h"
#include "ground.h"
#include <poll.h>
#include <errno.h>

int generate_order();
void send_ground(struct personnages *p, int socket);
void send_all_chars(int socket);
void send_all(int socket, int size, uint8_t *to_send);
