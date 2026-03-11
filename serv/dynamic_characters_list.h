#pragma once
#include "perso.h"
#include <stdlib.h>
#include "shared_var.h"
#include "bioms.h"

struct dynamic_char_list{
    struct personnages *data;  // tableau dynamique
    int capacity;      // capacité actuelle
    int maxid;
} ;

int append_perso(char *line, char *skin ,int id);
void death(void);
void init_map(const char *map_path);
int append_empty_perso(void);