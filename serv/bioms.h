#pragma once
#include "shared_var.h"

struct dynamic_char_bioms_list{
    int *data;  // tableau dynamique
    int capacity;      // capacité actuelle
    int size;
} ;

void init_bioms(void);
void append_perso_bioms(int p, int biom);
void remove_perso_bioms(int p, int biom);