#pragma once
#include <stdio.h>
#include <err.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <math.h>
#include "sys/types.h"
#include "sys/socket.h"
#include "netinet/in.h"
#include "arpa/inet.h"
#include "linked_display.h"

struct personnages
{
    int id;                         // 1
    int pv;                         // 2
    int timer_dom;                  // local
    int speak_timer;                 // local
    int nb_vassaux;                 // 3
    int faim;                       // 4
    int inside;                     // 5
    int porte_dom;                  // local
    int dom;                        // local
    int poid;                       // local
    int house_id;                   // 6
    int animation;                  // 7
    int animation_2;                // 8
    int faim_time;                  // local
    int max_pv;                     // local
    int vitesse_dom;                // local
    int echange_player;             // 14
    int items_cnt[12];              // 15 bis               10 premiers item // echange //
    char angle;                     // 9
    char skin[4];                   // 0
    char physique[6];               // 10                  sexe/taille/couleur_de_peau/couleur_de_cheuveu/coifure
    char nom_de_compte[50];         // 11
    char nom[50];                   // 12
    char nom_superieur[50];         // 13 
    char items[18][50];             // 15 bis               10 premiers item // echange //  left hand right hand headgear tunic pant shoes
    char speak[90];                 // 23
    char skill[62];                 // 22
    float x;                        // 16
    float y;                        // 17
    float altitude;                 // 18
    float ordrex;                   // 19
    float ordrey;                   // 20
    float screenx;                  // local
    float screeny;                  // local
    float sizescreenx;              // local
    float sizescreeny;              // local
    float vitesse_dep;              // local
    struct linked_enemie *e_list;   // 21
};

struct linked_list
{
    struct personnages *p;
    struct linked_list *next;
};

#include "network/net.h"
#include "diplomatique/diplo.h"
#include "init_sprite.h"
#include "inventory/parse_equipement.h"
#include "network/parseur.h"
#include "select_sprite.h"


char exist_in_linked(struct linked_list *list, struct personnages *to_test);
struct linked_list *copy_linked(struct linked_list *list);
struct linked_list *append_in_linked(struct linked_list *list,struct personnages *p);
int append_perso(char *line);
void disp_perso_list(struct personnages *moi);
//struct personnages *find_perso(struct linked_list *list ,char *name);
//void buble_sort_perso(struct linked_list *list, struct personnages *moi);
void free_linked(struct linked_list *list, char free_content);
struct linked_list *death(void);
struct linked_list *remove_from_linked_list(struct linked_list *list, struct personnages *to_rem);
struct personnages *find_perso_by_name(char *name);
struct personnages *find_perso_by_id(int id);
struct linked_list *clean_selected(struct linked_list *list);
int getSizeLinkedList(struct linked_list *list);