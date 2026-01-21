#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include "diplo.h"
#include "ia/pathfinding.h"
#include "../shared/linked_item.h"
#include "building.h"

extern struct personnages *lits;

struct personnages
{
    char skin[4];
    int id;
    int pv;
    char nom_de_compte[50];
    float x;
    float y;
    float altitude;
    float ordrex;
    float ordrey;
    char angle;
    int timer_dom;
    int faim;
    int inside;
    char nom[50];
    char nom_superieur[50];
    char titre[50];
    char religion[50];
    int nb_vassaux;
    struct linked_enemie *e_list;
    struct linked_item *i_list;
    char echange_player[50];
    char item1[50];
    int count_item1;
    char item2[50];
    int count_item2;
    char speak[90];
    int animation;
	int animation_2;
    char chemin_is_set;
    char left_hand[50];
    char right_hand[50];
    char headgear[50];
    char tunic[50];
    char pant[50];
    char shoes[50];
    char skill[62*3];
    int house_id;
    char physique[6];
    /////////////
    char online;
    float dom;
    float porte_dom;
    float vitesse_dep;
    float moved_x;
    float moved_y;
	char a_bouger;
    char is_active;
    int speak_timer;
    struct path* chemin;
};

int parse_new(struct personnages *p, char *line, char *skin, int id);
void parse_order(char *line);
struct personnages *get_ptr_from_id(int id);
int get_id(char *line, int *i);
void append_enemi(char *name);
struct personnages *find_perso_by_name(char *name);
void save_map(int);
void kill(struct personnages *p);
int find_smalest_valid_id_perso(int from);