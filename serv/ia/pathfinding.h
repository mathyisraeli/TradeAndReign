#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "../perso.h"
#include "../shared_var.h"
#include "../ground.h"

struct personnages;

struct path
{
    float g;
    float f;
    int prev;
    char walkable;
};

struct heap
{
    int *data;
    int size;
};

int findpath(struct personnages *p);
void init_grid(struct personnages *p);

