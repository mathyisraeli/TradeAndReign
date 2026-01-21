#pragma once
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct linked_item
{
    char nom[50];
    int count;
    struct linked_item *next;
};

int count(char *name);
int n_item(struct linked_item *l);
char can_add(char *name, int cnt, struct linked_item *l);
struct linked_item *append_in_inventory(char *name, struct linked_item *p, int n);
void moove_item(int a, int b, struct linked_item *l);
int count_item(struct linked_item *l, char *name);
struct linked_item *get_item_n(int n, struct linked_item *l);
struct linked_item *exist_in_linked_item(struct linked_item *e, char *cmp);
void free_linked_item(struct linked_item *e);
void print(struct linked_item *e);
struct linked_item *del(struct linked_item *root, struct linked_item *to_del);
struct linked_item *remove_from_inventory(char *name, struct linked_item *p, int n);