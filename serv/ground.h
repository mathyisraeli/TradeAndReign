#pragma once
#include "shared_var.h"

enum Texture {
    lim, lii, lis, qua, qui, qug,qus,quz,qzc,qzg,qzs,bas,bai, bac, bal, 
    gra, gri, grc, grt, grd, grs, san, sai, sag, sha, shv, shs, shg, sht, shl, shc, shi, mar, 
    mai, gys, gyp, wat, soi, coa, sal, snd, dus, sno, gLi, gqa, gqz, gba, ggr,gsa,gsh,gma,ggy
};   

struct linked_ground{
    uint16_t altitude;
    enum Texture texture;
    struct linked_ground *next;
};

int altitude(int index);
void create_array(char *ground_string);
void remove_1_pixel(int index);
void add_1_pixel(int index, enum Texture texture);
enum Texture texture_from_string(char *str);
void handle_altitude(void);
void melt_snow(int n);
void ground_to_string(void);
void save_ground(int n);