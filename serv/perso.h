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
    // id                                                           -   1
    int pv;                         //                              -   2
    int nb_vassaux;                 //                              -   3
    int timer_dom;                  // NOT NETWORK  -   NOT IN FILE
    int faim;                       //                              -   4
    int inside;                     //                              -   5
    int house_id;                   //                              -   6
    int animation;                  //                              -   7
	int animation_2;                //                              -   8
    int speak_timer;                // NOT NETWORK  -   NOT IN FILE
    int items_cnt[12];              //                              -   15 BIS
    char angle;                     //                              -   9
    char chemin_is_set;             // NOT NETWORK  -   NOT IN FILE   
    char online;                    // NOT NETWORK  -   NOT IN FILE
    char a_bouger;                  // NOT NETWORK  -   NOT IN FILE
    char is_active;                 // NOT NETWORK  -   NOT IN FILE
    char skin[4];                   //                              -   0
    char physique[7];               //                              -   10
    char nom_de_compte[50];         //                              -   11
    char nom[50];                   //                              -   12
    char nom_superieur[50];         //                              -   13  
    char echange_player[50];        //                              -   14
    char speak[90];                 //                              -   23 (LAST)
    char skill[62*3];               //                              -   22
    char items[18][50];             //                              -   15 BIS
    float x;                        //                              -   16
    float y;                        //                              -   17
    float altitude;                 //                              -   18
    float ordrex;                   //                              -   19
    float ordrey;                   //                              -   20
    float dom;                      // NOT NETWORK  -   NOT IN FILE
    float porte_dom;                // NOT NETWORK  -   NOT IN FILE
    float vitesse_dep;              // NOT NETWORK  -   NOT IN FILE
    float moved_x;                  // NOT NETWORK  -   NOT IN FILE
    float moved_y;                  // NOT NETWORK  -   NOT IN FILE
    struct linked_enemie *e_list;   //                              -   21
    struct path* chemin;            // NOT NETWORK  -   NOT IN FILE
};

int parse_new(struct personnages *p, char *line, char *skin);
void parse_order(char *line);
struct personnages *get_ptr_from_id(int id);
int get_id(char *line, int *i);
void append_enemi(char *name);
struct personnages *find_perso_by_name(char *name);
void save_map(int);
void kill(struct personnages *p);
int find_smalest_valid_id_perso(int from);