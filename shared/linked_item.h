#pragma once
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


int count(char *name);
int n_item(char items[18][50]);
char can_add(char *name, int cnt, char items[18][50], int items_cnt[12]);
void append_in_inventory(char *name, int n, char items[18][50], int items_cnt[12]);
int count_item(char *name, char items[18][50], int items_cnt[12]);
struct linked_item *get_item_n(int n, struct linked_item *l);
int find_index_in_inventory(char *name, char items[18][50]);
void print(char items[18][50],  int items_cnt[12]);
void remove_from_inventory(char *name, int n, char items[18][50], int items_cnt[12]);
void echange_item(char p1_items[18][50], int p1_items_cnt[12], char p2_items[18][50], int p2_items_cnt[12], char p1_echange_player[50]);