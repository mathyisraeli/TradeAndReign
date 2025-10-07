#pragma once
#include <SDL2/SDL.h>
#include <stdlib.h>
#include "shared_var.h"

struct img
{
    struct textures *t;
    struct skin *s;
    struct gui_sprite *g;
};

struct textures
{
    SDL_Texture *he1;
    SDL_Texture *he2;
    SDL_Texture *he3;
    SDL_Texture *he4;
    SDL_Texture *he5;
    SDL_Texture *bl1;
    SDL_Texture *bl2;
    SDL_Texture *bl3;
    SDL_Texture *ea1;
    SDL_Texture *ea2;
    SDL_Texture *ea3;
    SDL_Texture *gr1;
    SDL_Texture *gr2;
    SDL_Texture *ne1;
    SDL_Texture *ne2;
    SDL_Texture *ne3;
    SDL_Texture *sa1;
    SDL_Texture *sa2;
    SDL_Texture *sa3;
    SDL_Texture *te1;
    SDL_Texture *te2;
    SDL_Texture *te3;
    SDL_Texture *w1;
    SDL_Texture *granit;
    SDL_Texture *basalt;
    SDL_Texture *calcaire;
    SDL_Texture *gres;
    SDL_Texture *marbre;
    SDL_Texture *schiste;
    SDL_Texture *fond;
};

struct skin
{
    // Homme qui marche
    SDL_Texture *Man[2][10][30][6][8]; //sexe /  couleur de peau / animation2 / animation / angle

    SDL_Texture *breechesLin[30][6][8];
    SDL_Texture *shiftLin[30][6][8];

    SDL_Texture *ship1_50cm_wood;
    SDL_Texture *ship1_100cm_wood;
    SDL_Texture *ship1_150cm_wood;
    SDL_Texture *ship1_200cm_wood;
    SDL_Texture *ship1_200cm_wood_triangle;
    SDL_Texture *ship1_flat_wood;
    SDL_Texture *ship1_flat_black;
    SDL_Texture *ship1_flat_wood_down_triangle;
    SDL_Texture *ship1_flat_wood_right_triangle;
    SDL_Texture *ship1_flat_wood_left_triangle;
    SDL_Texture *ship1_flat_wood_up_triangle;
    SDL_Texture *ship1_bigSail;
    SDL_Texture *ship1_bigSailFolded;

    SDL_Texture *fruit;
    SDL_Texture *legume;
    SDL_Texture *tree1Standing;
    SDL_Texture *tree1Felled;

    SDL_Texture *terracotta_house_3x3[9];
    SDL_Texture *terracotta_house_3x3_inside[6];
    SDL_Texture *wooden_house_6x6[11];
    SDL_Texture *wooden_house_3x3_faceline[3];

    SDL_Texture *wood_pillar;

    SDL_Texture *bridgeSlab;
    SDL_Texture *bridgePillar;

    // Drapeaux
    SDL_Texture *drapeauBlanc[12]; // 11 directions

    // Standing textures for littleManEmptyStuff
    SDL_Texture *littleManEmptyStuff_standing[12]; // 8 directions

    // Punching textures for littleManEmptyStuff
    SDL_Texture *littleManEmptyStuff_punching[4][12]; // 8 directions, 4 frames each

    // Walking textures for littleManEmptyStuff
    SDL_Texture *littleManEmptyStuff_walking[6][12]; // 8 directions, 6 frames each

};

struct gui_sprite
{
    SDL_Texture *croix;
    SDL_Texture *croix_inverse;
    SDL_Texture *demarcation;
    SDL_Texture *plus;
    SDL_Texture *moins;
    SDL_Texture *elipse;
    SDL_Texture *selecteur;
    SDL_Texture *main_menu_button;
    SDL_Texture *pressed_main_menu_button;
    SDL_Texture *sound_button;
    SDL_Texture *pressed_sound_button;
    SDL_Texture *square;
    SDL_Texture *triangle;
    SDL_Texture *lines;
    SDL_Texture *splited_lines;
    SDL_Texture *pressed_square;
    SDL_Texture *pressed_triangle;
    SDL_Texture *pressed_lines;
    SDL_Texture *pressed_splited_lines;
};


struct img *init_img();
struct textures *init_textures();
struct skin *init_skin();
struct gui_sprite *init_gui_sprite();
void initTextureObject(SDL_Texture** textureObject, char* bmpPath);
