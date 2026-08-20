#pragma once
#include "perso.h"
#include "building.h"
#include "../shared/linked_item.h"
#include "ground.h"
#include "visibility.h"
#include <poll.h>
#include <errno.h>

void send_order_to_player(int socket, int player_id);
void reset_a_bouger(void);
void send_ground(struct personnages *p, int socket);
void send_all(int socket, int size, uint8_t *to_send);
