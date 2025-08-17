#include "init_sprite.h"


void initTextureObject(SDL_Texture** textureObject, char* bmpPath)
{
    SDL_Surface *a = SDL_LoadBMP(bmpPath);
    SDL_SetColorKey(a, SDL_SCANCODE_Y, SDL_MapRGB(a->format,255,255,255));
    a = SDL_ConvertSurfaceFormat(a, SDL_GetWindowPixelFormat(window), 0);
    *textureObject = SDL_CreateTextureFromSurface(renderer, a);
    SDL_FreeSurface(a);
}


struct skin *init_skin()
{
    struct skin *to_return = malloc(sizeof(struct skin));
    initTextureObject(&(to_return->drapeauBlanc[0]), "img/batiments/drapeau/face_dos.bmp");//
    initTextureObject(&(to_return->drapeauBlanc[1]), "img/batiments/drapeau/dosDroite.bmp");//
    initTextureObject(&(to_return->drapeauBlanc[2]), "img/batiments/drapeau/droiteDos.bmp");//
    initTextureObject(&(to_return->drapeauBlanc[3]), "img/batiments/drapeau/droite.bmp");//
    initTextureObject(&(to_return->drapeauBlanc[4]), "img/batiments/drapeau/droiteFace.bmp");//
    initTextureObject(&(to_return->drapeauBlanc[5]), "img/batiments/drapeau/faceDroite.bmp");//
    initTextureObject(&(to_return->drapeauBlanc[6]), "img/batiments/drapeau/face_dos.bmp");//
    initTextureObject(&(to_return->drapeauBlanc[7]), "img/batiments/drapeau/faceGauche.bmp");//
    initTextureObject(&(to_return->drapeauBlanc[8]), "img/batiments/drapeau/gaucheFace.bmp");//
    initTextureObject(&(to_return->drapeauBlanc[9]), "img/batiments/drapeau/gauche.bmp");//
    initTextureObject(&(to_return->drapeauBlanc[10]), "img/batiments/drapeau/gaucheDos.bmp");//
    initTextureObject(&(to_return->drapeauBlanc[11]), "img/batiments/drapeau/dosGauche.bmp");//
    

    
    initTextureObject(&(to_return->ship1_50cm_wood), "img/ship/ship1/50cm_wood.bmp");
    initTextureObject(&(to_return->ship1_100cm_wood), "img/ship/ship1/100cm_wood.bmp");
    initTextureObject(&(to_return->ship1_150cm_wood), "img/ship/ship1/150cm_wood.bmp");
    initTextureObject(&(to_return->ship1_200cm_wood), "img/ship/ship1/200cm_wood.bmp");
    initTextureObject(&(to_return->ship1_200cm_wood_triangle), "img/ship/ship1/200cm_wood_triangle.bmp");
    initTextureObject(&(to_return->ship1_flat_wood), "img/ship/ship1/flat_wood.bmp");
    initTextureObject(&(to_return->ship1_flat_black), "img/ship/ship1/flat_black.bmp");
    initTextureObject(&(to_return->ship1_flat_wood_down_triangle), "img/ship/ship1/flat_wood_down_triangle.bmp");
    initTextureObject(&(to_return->ship1_flat_wood_right_triangle), "img/ship/ship1/flat_wood_right_triangle.bmp");
    initTextureObject(&(to_return->ship1_flat_wood_left_triangle), "img/ship/ship1/flat_wood_left_triangle.bmp");
    initTextureObject(&(to_return->ship1_flat_wood_up_triangle), "img/ship/ship1/flat_wood_up_triangle.bmp");
    initTextureObject(&(to_return->ship1_bigSail), "img/ship/ship1/bigSail.bmp");
    initTextureObject(&(to_return->ship1_bigSailFolded), "img/ship/ship1/bigSailFolded.bmp");


    //initTextureObject(&(to_return->fruit), "img/nature/nouriture/fruit.bmp");
    //initTextureObject(&(to_return->legume), "img/nature/nouriture/legume.bmp");
    initTextureObject(&(to_return->tree1Standing), "img/nature/tree1Standing.bmp");
    initTextureObject(&(to_return->tree1Felled), "img/nature/tree1Felled.bmp");

    
    initTextureObject(&(to_return->wooden_house_3x3_faceline[0]), "img/batiments/3x3_wooden_house/faceline1.bmp");
    initTextureObject(&(to_return->wooden_house_3x3_faceline[1]), "img/batiments/3x3_wooden_house/faceline2.bmp");
    initTextureObject(&(to_return->wooden_house_3x3_faceline[2]), "img/batiments/3x3_wooden_house/faceline3.bmp");

    initTextureObject(&(to_return->wooden_house_6x6[0]), "img/batiments/6x6_wooden_house/0.bmp");
    initTextureObject(&(to_return->wooden_house_6x6[1]), "img/batiments/6x6_wooden_house/1.bmp");
    initTextureObject(&(to_return->wooden_house_6x6[2]), "img/batiments/6x6_wooden_house/2.bmp");
    initTextureObject(&(to_return->wooden_house_6x6[3]), "img/batiments/6x6_wooden_house/3.bmp");
    initTextureObject(&(to_return->wooden_house_6x6[4]), "img/batiments/6x6_wooden_house/4.bmp");
    initTextureObject(&(to_return->wooden_house_6x6[5]), "img/batiments/6x6_wooden_house/5.bmp");
    initTextureObject(&(to_return->wooden_house_6x6[6]), "img/batiments/6x6_wooden_house/6.bmp");
    initTextureObject(&(to_return->wooden_house_6x6[7]), "img/batiments/6x6_wooden_house/7.bmp");
    initTextureObject(&(to_return->wooden_house_6x6[8]), "img/batiments/6x6_wooden_house/8.bmp");
    initTextureObject(&(to_return->wooden_house_6x6[9]), "img/batiments/6x6_wooden_house/9.bmp");
    initTextureObject(&(to_return->wooden_house_6x6[10]), "img/batiments/6x6_wooden_house/inside.bmp");

    

    initTextureObject(&(to_return->terracotta_house_3x3[0]), "img/batiments/3x3_terracotta_house/1.bmp");
    initTextureObject(&(to_return->terracotta_house_3x3[1]), "img/batiments/3x3_terracotta_house/2.bmp");
    initTextureObject(&(to_return->terracotta_house_3x3[2]), "img/batiments/3x3_terracotta_house/3.bmp");
    initTextureObject(&(to_return->terracotta_house_3x3[3]), "img/batiments/3x3_terracotta_house/4.bmp");
    initTextureObject(&(to_return->terracotta_house_3x3[4]), "img/batiments/3x3_terracotta_house/5.bmp");
    initTextureObject(&(to_return->terracotta_house_3x3[5]), "img/batiments/3x3_terracotta_house/6.bmp");
    initTextureObject(&(to_return->terracotta_house_3x3[6]), "img/batiments/3x3_terracotta_house/7.bmp");
    initTextureObject(&(to_return->terracotta_house_3x3[7]), "img/batiments/3x3_terracotta_house/8.bmp");
    initTextureObject(&(to_return->terracotta_house_3x3[8]), "img/batiments/3x3_terracotta_house/9.bmp");

    initTextureObject(&(to_return->terracotta_house_3x3_inside[0]), "img/batiments/3x3_terracotta_house/inside1.bmp");
    initTextureObject(&(to_return->terracotta_house_3x3_inside[1]), "img/batiments/3x3_terracotta_house/inside2.bmp");
    initTextureObject(&(to_return->terracotta_house_3x3_inside[2]), "img/batiments/3x3_terracotta_house/inside3.bmp");
    initTextureObject(&(to_return->terracotta_house_3x3_inside[3]), "img/batiments/3x3_terracotta_house/inside4.bmp");
    initTextureObject(&(to_return->terracotta_house_3x3_inside[4]), "img/batiments/3x3_terracotta_house/inside5.bmp");
    initTextureObject(&(to_return->terracotta_house_3x3_inside[5]), "img/batiments/3x3_terracotta_house/inside6.bmp");

    initTextureObject(&(to_return->wood_pillar), "img/batiments/pillar/wood.bmp");

    initTextureObject(&(to_return->bridgePillar), "img/batiments/bridges/pillar.bmp");
    initTextureObject(&(to_return->bridgeSlab), "img/batiments/bridges/slab.bmp");

    initTextureObject(&(to_return->Man[0][6][0][0][0]), "img/man/Bronze/walk-0-1.bmp");
    initTextureObject(&(to_return->Man[0][6][0][0][1]), "img/man/Bronze/walk-45-1.bmp");
    initTextureObject(&(to_return->Man[0][6][0][0][2]), "img/man/Bronze/walk-90-1.bmp");
    initTextureObject(&(to_return->Man[0][6][0][0][3]), "img/man/Bronze/walk-135-1.bmp");
    initTextureObject(&(to_return->Man[0][6][0][0][4]), "img/man/Bronze/walk-180-1.bmp");
    initTextureObject(&(to_return->Man[0][6][0][0][5]), "img/man/Bronze/walk-225-1.bmp");
    initTextureObject(&(to_return->Man[0][6][0][0][6]), "img/man/Bronze/walk-270-1.bmp");
    initTextureObject(&(to_return->Man[0][6][0][0][7]), "img/man/Bronze/walk-315-1.bmp");

    initTextureObject(&(to_return->Man[0][6][0][1][0]), "img/man/Bronze/walk-0-2.bmp");
    initTextureObject(&(to_return->Man[0][6][0][1][1]), "img/man/Bronze/walk-45-2.bmp");
    initTextureObject(&(to_return->Man[0][6][0][1][2]), "img/man/Bronze/walk-90-2.bmp");
    initTextureObject(&(to_return->Man[0][6][0][1][3]), "img/man/Bronze/walk-135-2.bmp");
    initTextureObject(&(to_return->Man[0][6][0][1][4]), "img/man/Bronze/walk-180-2.bmp");
    initTextureObject(&(to_return->Man[0][6][0][1][5]), "img/man/Bronze/walk-225-2.bmp");
    initTextureObject(&(to_return->Man[0][6][0][1][6]), "img/man/Bronze/walk-270-2.bmp");
    initTextureObject(&(to_return->Man[0][6][0][1][7]), "img/man/Bronze/walk-315-2.bmp");

    initTextureObject(&(to_return->Man[0][6][0][2][0]), "img/man/Bronze/walk-0-3.bmp");
    initTextureObject(&(to_return->Man[0][6][0][2][1]), "img/man/Bronze/walk-45-3.bmp");
    initTextureObject(&(to_return->Man[0][6][0][2][2]), "img/man/Bronze/walk-90-3.bmp");
    initTextureObject(&(to_return->Man[0][6][0][2][3]), "img/man/Bronze/walk-135-3.bmp");
    initTextureObject(&(to_return->Man[0][6][0][2][4]), "img/man/Bronze/walk-180-3.bmp");
    initTextureObject(&(to_return->Man[0][6][0][2][5]), "img/man/Bronze/walk-225-3.bmp");
    initTextureObject(&(to_return->Man[0][6][0][2][6]), "img/man/Bronze/walk-270-3.bmp");
    initTextureObject(&(to_return->Man[0][6][0][2][7]), "img/man/Bronze/walk-315-3.bmp");

    initTextureObject(&(to_return->Man[0][6][0][3][0]), "img/man/Bronze/walk-0-4.bmp");
    initTextureObject(&(to_return->Man[0][6][0][3][1]), "img/man/Bronze/walk-45-4.bmp");
    initTextureObject(&(to_return->Man[0][6][0][3][2]), "img/man/Bronze/walk-90-4.bmp");
    initTextureObject(&(to_return->Man[0][6][0][3][3]), "img/man/Bronze/walk-135-4.bmp");
    initTextureObject(&(to_return->Man[0][6][0][3][4]), "img/man/Bronze/walk-180-4.bmp");
    initTextureObject(&(to_return->Man[0][6][0][3][5]), "img/man/Bronze/walk-225-4.bmp");
    initTextureObject(&(to_return->Man[0][6][0][3][6]), "img/man/Bronze/walk-270-4.bmp");
    initTextureObject(&(to_return->Man[0][6][0][3][7]), "img/man/Bronze/walk-315-4.bmp");

    initTextureObject(&(to_return->Man[0][6][0][4][0]), "img/man/Bronze/walk-0-5.bmp");
    initTextureObject(&(to_return->Man[0][6][0][4][1]), "img/man/Bronze/walk-45-5.bmp");
    initTextureObject(&(to_return->Man[0][6][0][4][2]), "img/man/Bronze/walk-90-5.bmp");
    initTextureObject(&(to_return->Man[0][6][0][4][3]), "img/man/Bronze/walk-135-5.bmp");
    initTextureObject(&(to_return->Man[0][6][0][4][4]), "img/man/Bronze/walk-180-5.bmp");
    initTextureObject(&(to_return->Man[0][6][0][4][5]), "img/man/Bronze/walk-225-5.bmp");
    initTextureObject(&(to_return->Man[0][6][0][4][6]), "img/man/Bronze/walk-270-5.bmp");
    initTextureObject(&(to_return->Man[0][6][0][4][7]), "img/man/Bronze/walk-315-5.bmp");

    initTextureObject(&(to_return->Man[0][6][0][5][0]), "img/man/Bronze/walk-0-6.bmp");
    initTextureObject(&(to_return->Man[0][6][0][5][1]), "img/man/Bronze/walk-45-6.bmp");
    initTextureObject(&(to_return->Man[0][6][0][5][2]), "img/man/Bronze/walk-90-6.bmp");
    initTextureObject(&(to_return->Man[0][6][0][5][3]), "img/man/Bronze/walk-135-6.bmp");
    initTextureObject(&(to_return->Man[0][6][0][5][4]), "img/man/Bronze/walk-180-6.bmp");
    initTextureObject(&(to_return->Man[0][6][0][5][5]), "img/man/Bronze/walk-225-6.bmp");
    initTextureObject(&(to_return->Man[0][6][0][5][6]), "img/man/Bronze/walk-270-6.bmp");
    initTextureObject(&(to_return->Man[0][6][0][5][7]), "img/man/Bronze/walk-315-6.bmp");

    initTextureObject(&(to_return->Man[0][6][1][0][0]), "img/man/Bronze/punch-0-1.bmp");
    initTextureObject(&(to_return->Man[0][6][1][0][1]), "img/man/Bronze/punch-45-1.bmp");
    initTextureObject(&(to_return->Man[0][6][1][0][2]), "img/man/Bronze/punch-90-1.bmp");
    initTextureObject(&(to_return->Man[0][6][1][0][3]), "img/man/Bronze/punch-135-1.bmp");
    initTextureObject(&(to_return->Man[0][6][1][0][4]), "img/man/Bronze/punch-180-1.bmp");
    initTextureObject(&(to_return->Man[0][6][1][0][5]), "img/man/Bronze/punch-225-1.bmp");
    initTextureObject(&(to_return->Man[0][6][1][0][6]), "img/man/Bronze/punch-270-1.bmp");
    initTextureObject(&(to_return->Man[0][6][1][0][7]), "img/man/Bronze/punch-315-1.bmp");

    initTextureObject(&(to_return->Man[0][6][1][1][0]), "img/man/Bronze/punch-0-2.bmp");
    initTextureObject(&(to_return->Man[0][6][1][1][1]), "img/man/Bronze/punch-45-2.bmp");
    initTextureObject(&(to_return->Man[0][6][1][1][2]), "img/man/Bronze/punch-90-2.bmp");
    initTextureObject(&(to_return->Man[0][6][1][1][3]), "img/man/Bronze/punch-135-2.bmp");
    initTextureObject(&(to_return->Man[0][6][1][1][4]), "img/man/Bronze/punch-180-2.bmp");
    initTextureObject(&(to_return->Man[0][6][1][1][5]), "img/man/Bronze/punch-225-2.bmp");
    initTextureObject(&(to_return->Man[0][6][1][1][6]), "img/man/Bronze/punch-270-2.bmp");
    initTextureObject(&(to_return->Man[0][6][1][1][7]), "img/man/Bronze/punch-315-2.bmp");

    initTextureObject(&(to_return->Man[0][6][1][2][0]), "img/man/Bronze/punch-0-3.bmp");
    initTextureObject(&(to_return->Man[0][6][1][2][1]), "img/man/Bronze/punch-45-3.bmp");
    initTextureObject(&(to_return->Man[0][6][1][2][2]), "img/man/Bronze/punch-90-3.bmp");
    initTextureObject(&(to_return->Man[0][6][1][2][3]), "img/man/Bronze/punch-135-3.bmp");
    initTextureObject(&(to_return->Man[0][6][1][2][4]), "img/man/Bronze/punch-180-3.bmp");
    initTextureObject(&(to_return->Man[0][6][1][2][5]), "img/man/Bronze/punch-225-3.bmp");
    initTextureObject(&(to_return->Man[0][6][1][2][6]), "img/man/Bronze/punch-270-3.bmp");
    initTextureObject(&(to_return->Man[0][6][1][2][7]), "img/man/Bronze/punch-315-3.bmp");

    initTextureObject(&(to_return->Man[0][6][1][3][0]), "img/man/Bronze/punch-0-4.bmp");
    initTextureObject(&(to_return->Man[0][6][1][3][1]), "img/man/Bronze/punch-45-4.bmp");
    initTextureObject(&(to_return->Man[0][6][1][3][2]), "img/man/Bronze/punch-90-4.bmp");
    initTextureObject(&(to_return->Man[0][6][1][3][3]), "img/man/Bronze/punch-135-4.bmp");
    initTextureObject(&(to_return->Man[0][6][1][3][4]), "img/man/Bronze/punch-180-4.bmp");
    initTextureObject(&(to_return->Man[0][6][1][3][5]), "img/man/Bronze/punch-225-4.bmp");
    initTextureObject(&(to_return->Man[0][6][1][3][6]), "img/man/Bronze/punch-270-4.bmp");
    initTextureObject(&(to_return->Man[0][6][1][3][7]), "img/man/Bronze/punch-315-4.bmp");

    initTextureObject(&(to_return->Man[0][6][1][4][0]), "img/man/Bronze/punch-0-5.bmp");
    initTextureObject(&(to_return->Man[0][6][1][4][1]), "img/man/Bronze/punch-45-5.bmp");
    initTextureObject(&(to_return->Man[0][6][1][4][2]), "img/man/Bronze/punch-90-5.bmp");
    initTextureObject(&(to_return->Man[0][6][1][4][3]), "img/man/Bronze/punch-135-5.bmp");
    initTextureObject(&(to_return->Man[0][6][1][4][4]), "img/man/Bronze/punch-180-5.bmp");
    initTextureObject(&(to_return->Man[0][6][1][4][5]), "img/man/Bronze/punch-225-5.bmp");
    initTextureObject(&(to_return->Man[0][6][1][4][6]), "img/man/Bronze/punch-270-5.bmp");
    initTextureObject(&(to_return->Man[0][6][1][4][7]), "img/man/Bronze/punch-315-5.bmp");

    initTextureObject(&(to_return->Man[0][6][1][5][0]), "img/man/Bronze/punch-0-6.bmp");
    initTextureObject(&(to_return->Man[0][6][1][5][1]), "img/man/Bronze/punch-45-6.bmp");
    initTextureObject(&(to_return->Man[0][6][1][5][2]), "img/man/Bronze/punch-90-6.bmp");
    initTextureObject(&(to_return->Man[0][6][1][5][3]), "img/man/Bronze/punch-135-6.bmp");
    initTextureObject(&(to_return->Man[0][6][1][5][4]), "img/man/Bronze/punch-180-6.bmp");
    initTextureObject(&(to_return->Man[0][6][1][5][5]), "img/man/Bronze/punch-225-6.bmp");
    initTextureObject(&(to_return->Man[0][6][1][5][6]), "img/man/Bronze/punch-270-6.bmp");
    initTextureObject(&(to_return->Man[0][6][1][5][7]), "img/man/Bronze/punch-315-6.bmp");

    initTextureObject(&(to_return->Man[0][6][2][0][0]), "img/man/Bronze/gather-0-1.bmp");
    initTextureObject(&(to_return->Man[0][6][2][0][1]), "img/man/Bronze/gather-45-1.bmp");
    initTextureObject(&(to_return->Man[0][6][2][0][2]), "img/man/Bronze/gather-90-1.bmp");
    initTextureObject(&(to_return->Man[0][6][2][0][3]), "img/man/Bronze/gather-135-1.bmp");
    initTextureObject(&(to_return->Man[0][6][2][0][4]), "img/man/Bronze/gather-180-1.bmp");
    initTextureObject(&(to_return->Man[0][6][2][0][5]), "img/man/Bronze/gather-225-1.bmp");
    initTextureObject(&(to_return->Man[0][6][2][0][6]), "img/man/Bronze/gather-270-1.bmp");
    initTextureObject(&(to_return->Man[0][6][2][0][7]), "img/man/Bronze/gather-315-1.bmp");

    initTextureObject(&(to_return->Man[0][6][2][1][0]), "img/man/Bronze/gather-0-2.bmp");
    initTextureObject(&(to_return->Man[0][6][2][1][1]), "img/man/Bronze/gather-45-2.bmp");
    initTextureObject(&(to_return->Man[0][6][2][1][2]), "img/man/Bronze/gather-90-2.bmp");
    initTextureObject(&(to_return->Man[0][6][2][1][3]), "img/man/Bronze/gather-135-2.bmp");
    initTextureObject(&(to_return->Man[0][6][2][1][4]), "img/man/Bronze/gather-180-2.bmp");
    initTextureObject(&(to_return->Man[0][6][2][1][5]), "img/man/Bronze/gather-225-2.bmp");
    initTextureObject(&(to_return->Man[0][6][2][1][6]), "img/man/Bronze/gather-270-2.bmp");
    initTextureObject(&(to_return->Man[0][6][2][1][7]), "img/man/Bronze/gather-315-2.bmp");

    initTextureObject(&(to_return->Man[0][6][2][2][0]), "img/man/Bronze/gather-0-3.bmp");
    initTextureObject(&(to_return->Man[0][6][2][2][1]), "img/man/Bronze/gather-45-3.bmp");
    initTextureObject(&(to_return->Man[0][6][2][2][2]), "img/man/Bronze/gather-90-3.bmp");
    initTextureObject(&(to_return->Man[0][6][2][2][3]), "img/man/Bronze/gather-135-3.bmp");
    initTextureObject(&(to_return->Man[0][6][2][2][4]), "img/man/Bronze/gather-180-3.bmp");
    initTextureObject(&(to_return->Man[0][6][2][2][5]), "img/man/Bronze/gather-225-3.bmp");
    initTextureObject(&(to_return->Man[0][6][2][2][6]), "img/man/Bronze/gather-270-3.bmp");
    initTextureObject(&(to_return->Man[0][6][2][2][7]), "img/man/Bronze/gather-315-3.bmp");

    initTextureObject(&(to_return->Man[0][6][2][3][0]), "img/man/Bronze/gather-0-4.bmp");
    initTextureObject(&(to_return->Man[0][6][2][3][1]), "img/man/Bronze/gather-45-4.bmp");
    initTextureObject(&(to_return->Man[0][6][2][3][2]), "img/man/Bronze/gather-90-4.bmp");
    initTextureObject(&(to_return->Man[0][6][2][3][3]), "img/man/Bronze/gather-135-4.bmp");
    initTextureObject(&(to_return->Man[0][6][2][3][4]), "img/man/Bronze/gather-180-4.bmp");
    initTextureObject(&(to_return->Man[0][6][2][3][5]), "img/man/Bronze/gather-225-4.bmp");
    initTextureObject(&(to_return->Man[0][6][2][3][6]), "img/man/Bronze/gather-270-4.bmp");
    initTextureObject(&(to_return->Man[0][6][2][3][7]), "img/man/Bronze/gather-315-4.bmp");

    initTextureObject(&(to_return->Man[0][6][2][4][0]), "img/man/Bronze/gather-0-5.bmp");
    initTextureObject(&(to_return->Man[0][6][2][4][1]), "img/man/Bronze/gather-45-5.bmp");
    initTextureObject(&(to_return->Man[0][6][2][4][2]), "img/man/Bronze/gather-90-5.bmp");
    initTextureObject(&(to_return->Man[0][6][2][4][3]), "img/man/Bronze/gather-135-5.bmp");
    initTextureObject(&(to_return->Man[0][6][2][4][4]), "img/man/Bronze/gather-180-5.bmp");
    initTextureObject(&(to_return->Man[0][6][2][4][5]), "img/man/Bronze/gather-225-5.bmp");
    initTextureObject(&(to_return->Man[0][6][2][4][6]), "img/man/Bronze/gather-270-5.bmp");
    initTextureObject(&(to_return->Man[0][6][2][4][7]), "img/man/Bronze/gather-315-5.bmp");

    initTextureObject(&(to_return->Man[0][6][2][5][0]), "img/man/Bronze/gather-0-6.bmp");
    initTextureObject(&(to_return->Man[0][6][2][5][1]), "img/man/Bronze/gather-45-6.bmp");
    initTextureObject(&(to_return->Man[0][6][2][5][2]), "img/man/Bronze/gather-90-6.bmp");
    initTextureObject(&(to_return->Man[0][6][2][5][3]), "img/man/Bronze/gather-135-6.bmp");
    initTextureObject(&(to_return->Man[0][6][2][5][4]), "img/man/Bronze/gather-180-6.bmp");
    initTextureObject(&(to_return->Man[0][6][2][5][5]), "img/man/Bronze/gather-225-6.bmp");
    initTextureObject(&(to_return->Man[0][6][2][5][6]), "img/man/Bronze/gather-270-6.bmp");
    initTextureObject(&(to_return->Man[0][6][2][5][7]), "img/man/Bronze/gather-315-6.bmp");

    initTextureObject(&(to_return->breechesLin[0][0][0]), "img/man/breeches-lin/walk-0-1.bmp");
    initTextureObject(&(to_return->breechesLin[0][0][1]), "img/man/breeches-lin/walk-45-1.bmp");
    initTextureObject(&(to_return->breechesLin[0][0][2]), "img/man/breeches-lin/walk-90-1.bmp");
    initTextureObject(&(to_return->breechesLin[0][0][3]), "img/man/breeches-lin/walk-135-1.bmp");
    initTextureObject(&(to_return->breechesLin[0][0][4]), "img/man/breeches-lin/walk-180-1.bmp");
    initTextureObject(&(to_return->breechesLin[0][0][5]), "img/man/breeches-lin/walk-225-1.bmp");
    initTextureObject(&(to_return->breechesLin[0][0][6]), "img/man/breeches-lin/walk-270-1.bmp");
    initTextureObject(&(to_return->breechesLin[0][0][7]), "img/man/breeches-lin/walk-315-1.bmp");

    initTextureObject(&(to_return->breechesLin[0][1][0]), "img/man/breeches-lin/walk-0-2.bmp");
    initTextureObject(&(to_return->breechesLin[0][1][1]), "img/man/breeches-lin/walk-45-2.bmp");
    initTextureObject(&(to_return->breechesLin[0][1][2]), "img/man/breeches-lin/walk-90-2.bmp");
    initTextureObject(&(to_return->breechesLin[0][1][3]), "img/man/breeches-lin/walk-135-2.bmp");
    initTextureObject(&(to_return->breechesLin[0][1][4]), "img/man/breeches-lin/walk-180-2.bmp");
    initTextureObject(&(to_return->breechesLin[0][1][5]), "img/man/breeches-lin/walk-225-2.bmp");
    initTextureObject(&(to_return->breechesLin[0][1][6]), "img/man/breeches-lin/walk-270-2.bmp");
    initTextureObject(&(to_return->breechesLin[0][1][7]), "img/man/breeches-lin/walk-315-2.bmp");

    initTextureObject(&(to_return->breechesLin[0][2][0]), "img/man/breeches-lin/walk-0-3.bmp");
    initTextureObject(&(to_return->breechesLin[0][2][1]), "img/man/breeches-lin/walk-45-3.bmp");
    initTextureObject(&(to_return->breechesLin[0][2][2]), "img/man/breeches-lin/walk-90-3.bmp");
    initTextureObject(&(to_return->breechesLin[0][2][3]), "img/man/breeches-lin/walk-135-3.bmp");
    initTextureObject(&(to_return->breechesLin[0][2][4]), "img/man/breeches-lin/walk-180-3.bmp");
    initTextureObject(&(to_return->breechesLin[0][2][5]), "img/man/breeches-lin/walk-225-3.bmp");
    initTextureObject(&(to_return->breechesLin[0][2][6]), "img/man/breeches-lin/walk-270-3.bmp");
    initTextureObject(&(to_return->breechesLin[0][2][7]), "img/man/breeches-lin/walk-315-3.bmp");

    initTextureObject(&(to_return->breechesLin[0][3][0]), "img/man/breeches-lin/walk-0-4.bmp");
    initTextureObject(&(to_return->breechesLin[0][3][1]), "img/man/breeches-lin/walk-45-4.bmp");
    initTextureObject(&(to_return->breechesLin[0][3][2]), "img/man/breeches-lin/walk-90-4.bmp");
    initTextureObject(&(to_return->breechesLin[0][3][3]), "img/man/breeches-lin/walk-135-4.bmp");
    initTextureObject(&(to_return->breechesLin[0][3][4]), "img/man/breeches-lin/walk-180-4.bmp");
    initTextureObject(&(to_return->breechesLin[0][3][5]), "img/man/breeches-lin/walk-225-4.bmp");
    initTextureObject(&(to_return->breechesLin[0][3][6]), "img/man/breeches-lin/walk-270-4.bmp");
    initTextureObject(&(to_return->breechesLin[0][3][7]), "img/man/breeches-lin/walk-315-4.bmp");

    initTextureObject(&(to_return->breechesLin[0][4][0]), "img/man/breeches-lin/walk-0-5.bmp");
    initTextureObject(&(to_return->breechesLin[0][4][1]), "img/man/breeches-lin/walk-45-5.bmp");
    initTextureObject(&(to_return->breechesLin[0][4][2]), "img/man/breeches-lin/walk-90-5.bmp");
    initTextureObject(&(to_return->breechesLin[0][4][3]), "img/man/breeches-lin/walk-135-5.bmp");
    initTextureObject(&(to_return->breechesLin[0][4][4]), "img/man/breeches-lin/walk-180-5.bmp");
    initTextureObject(&(to_return->breechesLin[0][4][5]), "img/man/breeches-lin/walk-225-5.bmp");
    initTextureObject(&(to_return->breechesLin[0][4][6]), "img/man/breeches-lin/walk-270-5.bmp");
    initTextureObject(&(to_return->breechesLin[0][4][7]), "img/man/breeches-lin/walk-315-5.bmp");

    initTextureObject(&(to_return->breechesLin[0][5][0]), "img/man/breeches-lin/walk-0-6.bmp");
    initTextureObject(&(to_return->breechesLin[0][5][1]), "img/man/breeches-lin/walk-45-6.bmp");
    initTextureObject(&(to_return->breechesLin[0][5][2]), "img/man/breeches-lin/walk-90-6.bmp");
    initTextureObject(&(to_return->breechesLin[0][5][3]), "img/man/breeches-lin/walk-135-6.bmp");
    initTextureObject(&(to_return->breechesLin[0][5][4]), "img/man/breeches-lin/walk-180-6.bmp");
    initTextureObject(&(to_return->breechesLin[0][5][5]), "img/man/breeches-lin/walk-225-6.bmp");
    initTextureObject(&(to_return->breechesLin[0][5][6]), "img/man/breeches-lin/walk-270-6.bmp");
    initTextureObject(&(to_return->breechesLin[0][5][7]), "img/man/breeches-lin/walk-315-6.bmp");

    initTextureObject(&(to_return->breechesLin[1][0][0]), "img/man/breeches-lin/punch-0-1.bmp");
    initTextureObject(&(to_return->breechesLin[1][0][1]), "img/man/breeches-lin/punch-45-1.bmp");
    initTextureObject(&(to_return->breechesLin[1][0][2]), "img/man/breeches-lin/punch-90-1.bmp");
    initTextureObject(&(to_return->breechesLin[1][0][3]), "img/man/breeches-lin/punch-135-1.bmp");
    initTextureObject(&(to_return->breechesLin[1][0][4]), "img/man/breeches-lin/punch-180-1.bmp");
    initTextureObject(&(to_return->breechesLin[1][0][5]), "img/man/breeches-lin/punch-225-1.bmp");
    initTextureObject(&(to_return->breechesLin[1][0][6]), "img/man/breeches-lin/punch-270-1.bmp");
    initTextureObject(&(to_return->breechesLin[1][0][7]), "img/man/breeches-lin/punch-315-1.bmp");

    initTextureObject(&(to_return->breechesLin[1][1][0]), "img/man/breeches-lin/punch-0-2.bmp");
    initTextureObject(&(to_return->breechesLin[1][1][1]), "img/man/breeches-lin/punch-45-2.bmp");
    initTextureObject(&(to_return->breechesLin[1][1][2]), "img/man/breeches-lin/punch-90-2.bmp");
    initTextureObject(&(to_return->breechesLin[1][1][3]), "img/man/breeches-lin/punch-135-2.bmp");
    initTextureObject(&(to_return->breechesLin[1][1][4]), "img/man/breeches-lin/punch-180-2.bmp");
    initTextureObject(&(to_return->breechesLin[1][1][5]), "img/man/breeches-lin/punch-225-2.bmp");
    initTextureObject(&(to_return->breechesLin[1][1][6]), "img/man/breeches-lin/punch-270-2.bmp");
    initTextureObject(&(to_return->breechesLin[1][1][7]), "img/man/breeches-lin/punch-315-2.bmp");

    initTextureObject(&(to_return->breechesLin[1][2][0]), "img/man/breeches-lin/punch-0-3.bmp");
    initTextureObject(&(to_return->breechesLin[1][2][1]), "img/man/breeches-lin/punch-45-3.bmp");
    initTextureObject(&(to_return->breechesLin[1][2][2]), "img/man/breeches-lin/punch-90-3.bmp");
    initTextureObject(&(to_return->breechesLin[1][2][3]), "img/man/breeches-lin/punch-135-3.bmp");
    initTextureObject(&(to_return->breechesLin[1][2][4]), "img/man/breeches-lin/punch-180-3.bmp");
    initTextureObject(&(to_return->breechesLin[1][2][5]), "img/man/breeches-lin/punch-225-3.bmp");
    initTextureObject(&(to_return->breechesLin[1][2][6]), "img/man/breeches-lin/punch-270-3.bmp");
    initTextureObject(&(to_return->breechesLin[1][2][7]), "img/man/breeches-lin/punch-315-3.bmp");

    initTextureObject(&(to_return->breechesLin[1][3][0]), "img/man/breeches-lin/punch-0-4.bmp");
    initTextureObject(&(to_return->breechesLin[1][3][1]), "img/man/breeches-lin/punch-45-4.bmp");
    initTextureObject(&(to_return->breechesLin[1][3][2]), "img/man/breeches-lin/punch-90-4.bmp");
    initTextureObject(&(to_return->breechesLin[1][3][3]), "img/man/breeches-lin/punch-135-4.bmp");
    initTextureObject(&(to_return->breechesLin[1][3][4]), "img/man/breeches-lin/punch-180-4.bmp");
    initTextureObject(&(to_return->breechesLin[1][3][5]), "img/man/breeches-lin/punch-225-4.bmp");
    initTextureObject(&(to_return->breechesLin[1][3][6]), "img/man/breeches-lin/punch-270-4.bmp");
    initTextureObject(&(to_return->breechesLin[1][3][7]), "img/man/breeches-lin/punch-315-4.bmp");

    initTextureObject(&(to_return->breechesLin[1][4][0]), "img/man/breeches-lin/punch-0-5.bmp");
    initTextureObject(&(to_return->breechesLin[1][4][1]), "img/man/breeches-lin/punch-45-5.bmp");
    initTextureObject(&(to_return->breechesLin[1][4][2]), "img/man/breeches-lin/punch-90-5.bmp");
    initTextureObject(&(to_return->breechesLin[1][4][3]), "img/man/breeches-lin/punch-135-5.bmp");
    initTextureObject(&(to_return->breechesLin[1][4][4]), "img/man/breeches-lin/punch-180-5.bmp");
    initTextureObject(&(to_return->breechesLin[1][4][5]), "img/man/breeches-lin/punch-225-5.bmp");
    initTextureObject(&(to_return->breechesLin[1][4][6]), "img/man/breeches-lin/punch-270-5.bmp");
    initTextureObject(&(to_return->breechesLin[1][4][7]), "img/man/breeches-lin/punch-315-5.bmp");

    initTextureObject(&(to_return->breechesLin[1][5][0]), "img/man/breeches-lin/punch-0-6.bmp");
    initTextureObject(&(to_return->breechesLin[1][5][1]), "img/man/breeches-lin/punch-45-6.bmp");
    initTextureObject(&(to_return->breechesLin[1][5][2]), "img/man/breeches-lin/punch-90-6.bmp");
    initTextureObject(&(to_return->breechesLin[1][5][3]), "img/man/breeches-lin/punch-135-6.bmp");
    initTextureObject(&(to_return->breechesLin[1][5][4]), "img/man/breeches-lin/punch-180-6.bmp");
    initTextureObject(&(to_return->breechesLin[1][5][5]), "img/man/breeches-lin/punch-225-6.bmp");
    initTextureObject(&(to_return->breechesLin[1][5][6]), "img/man/breeches-lin/punch-270-6.bmp");
    initTextureObject(&(to_return->breechesLin[1][5][7]), "img/man/breeches-lin/punch-315-6.bmp");

    initTextureObject(&(to_return->breechesLin[2][0][0]), "img/man/breeches-lin/gather-0-1.bmp");
    initTextureObject(&(to_return->breechesLin[2][0][1]), "img/man/breeches-lin/gather-45-1.bmp");
    initTextureObject(&(to_return->breechesLin[2][0][2]), "img/man/breeches-lin/gather-90-1.bmp");
    initTextureObject(&(to_return->breechesLin[2][0][3]), "img/man/breeches-lin/gather-135-1.bmp");
    initTextureObject(&(to_return->breechesLin[2][0][4]), "img/man/breeches-lin/gather-180-1.bmp");
    initTextureObject(&(to_return->breechesLin[2][0][5]), "img/man/breeches-lin/gather-225-1.bmp");
    initTextureObject(&(to_return->breechesLin[2][0][6]), "img/man/breeches-lin/gather-270-1.bmp");
    initTextureObject(&(to_return->breechesLin[2][0][7]), "img/man/breeches-lin/gather-315-1.bmp");

    initTextureObject(&(to_return->breechesLin[2][1][0]), "img/man/breeches-lin/gather-0-2.bmp");
    initTextureObject(&(to_return->breechesLin[2][1][1]), "img/man/breeches-lin/gather-45-2.bmp");
    initTextureObject(&(to_return->breechesLin[2][1][2]), "img/man/breeches-lin/gather-90-2.bmp");
    initTextureObject(&(to_return->breechesLin[2][1][3]), "img/man/breeches-lin/gather-135-2.bmp");
    initTextureObject(&(to_return->breechesLin[2][1][4]), "img/man/breeches-lin/gather-180-2.bmp");
    initTextureObject(&(to_return->breechesLin[2][1][5]), "img/man/breeches-lin/gather-225-2.bmp");
    initTextureObject(&(to_return->breechesLin[2][1][6]), "img/man/breeches-lin/gather-270-2.bmp");
    initTextureObject(&(to_return->breechesLin[2][1][7]), "img/man/breeches-lin/gather-315-2.bmp");

    initTextureObject(&(to_return->breechesLin[2][2][0]), "img/man/breeches-lin/gather-0-3.bmp");
    initTextureObject(&(to_return->breechesLin[2][2][1]), "img/man/breeches-lin/gather-45-3.bmp");
    initTextureObject(&(to_return->breechesLin[2][2][2]), "img/man/breeches-lin/gather-90-3.bmp");
    initTextureObject(&(to_return->breechesLin[2][2][3]), "img/man/breeches-lin/gather-135-3.bmp");
    initTextureObject(&(to_return->breechesLin[2][2][4]), "img/man/breeches-lin/gather-180-3.bmp");
    initTextureObject(&(to_return->breechesLin[2][2][5]), "img/man/breeches-lin/gather-225-3.bmp");
    initTextureObject(&(to_return->breechesLin[2][2][6]), "img/man/breeches-lin/gather-270-3.bmp");
    initTextureObject(&(to_return->breechesLin[2][2][7]), "img/man/breeches-lin/gather-315-3.bmp");

    initTextureObject(&(to_return->breechesLin[2][3][0]), "img/man/breeches-lin/gather-0-4.bmp");
    initTextureObject(&(to_return->breechesLin[2][3][1]), "img/man/breeches-lin/gather-45-4.bmp");
    initTextureObject(&(to_return->breechesLin[2][3][2]), "img/man/breeches-lin/gather-90-4.bmp");
    initTextureObject(&(to_return->breechesLin[2][3][3]), "img/man/breeches-lin/gather-135-4.bmp");
    initTextureObject(&(to_return->breechesLin[2][3][4]), "img/man/breeches-lin/gather-180-4.bmp");
    initTextureObject(&(to_return->breechesLin[2][3][5]), "img/man/breeches-lin/gather-225-4.bmp");
    initTextureObject(&(to_return->breechesLin[2][3][6]), "img/man/breeches-lin/gather-270-4.bmp");
    initTextureObject(&(to_return->breechesLin[2][3][7]), "img/man/breeches-lin/gather-315-4.bmp");

    initTextureObject(&(to_return->breechesLin[2][4][0]), "img/man/breeches-lin/gather-0-5.bmp");
    initTextureObject(&(to_return->breechesLin[2][4][1]), "img/man/breeches-lin/gather-45-5.bmp");
    initTextureObject(&(to_return->breechesLin[2][4][2]), "img/man/breeches-lin/gather-90-5.bmp");
    initTextureObject(&(to_return->breechesLin[2][4][3]), "img/man/breeches-lin/gather-135-5.bmp");
    initTextureObject(&(to_return->breechesLin[2][4][4]), "img/man/breeches-lin/gather-180-5.bmp");
    initTextureObject(&(to_return->breechesLin[2][4][5]), "img/man/breeches-lin/gather-225-5.bmp");
    initTextureObject(&(to_return->breechesLin[2][4][6]), "img/man/breeches-lin/gather-270-5.bmp");
    initTextureObject(&(to_return->breechesLin[2][4][7]), "img/man/breeches-lin/gather-315-5.bmp");

    initTextureObject(&(to_return->breechesLin[2][5][0]), "img/man/breeches-lin/gather-0-6.bmp");
    initTextureObject(&(to_return->breechesLin[2][5][1]), "img/man/breeches-lin/gather-45-6.bmp");
    initTextureObject(&(to_return->breechesLin[2][5][2]), "img/man/breeches-lin/gather-90-6.bmp");
    initTextureObject(&(to_return->breechesLin[2][5][3]), "img/man/breeches-lin/gather-135-6.bmp");
    initTextureObject(&(to_return->breechesLin[2][5][4]), "img/man/breeches-lin/gather-180-6.bmp");
    initTextureObject(&(to_return->breechesLin[2][5][5]), "img/man/breeches-lin/gather-225-6.bmp");
    initTextureObject(&(to_return->breechesLin[2][5][6]), "img/man/breeches-lin/gather-270-6.bmp");
    initTextureObject(&(to_return->breechesLin[2][5][7]), "img/man/breeches-lin/gather-315-6.bmp");
    return to_return;
}

struct textures *init_textures()
{
    struct textures *to_return = malloc(sizeof(struct textures));

    initTextureObject(&(to_return->he1), "img/textures/he1.bmp");
    initTextureObject(&(to_return->he2), "img/textures/he2.bmp");
    initTextureObject(&(to_return->he3), "img/textures/he3.bmp");
    initTextureObject(&(to_return->he4), "img/textures/he4.bmp");
    initTextureObject(&(to_return->he5), "img/textures/he5.bmp");

    initTextureObject(&(to_return->sa1), "img/textures/sa1.bmp");
    initTextureObject(&(to_return->sa2), "img/textures/sa2.bmp");
    initTextureObject(&(to_return->sa3), "img/textures/sa3.bmp");

    initTextureObject(&(to_return->ea1), "img/textures/ea1.bmp");
    initTextureObject(&(to_return->ea2), "img/textures/ea2.bmp");
    initTextureObject(&(to_return->ea3), "img/textures/ea3.bmp");

    initTextureObject(&(to_return->te1), "img/textures/te1.bmp");
    initTextureObject(&(to_return->te2), "img/textures/te2.bmp");
    initTextureObject(&(to_return->te3), "img/textures/te3.bmp");

    initTextureObject(&(to_return->ne1), "img/textures/ne1.bmp");
    initTextureObject(&(to_return->ne2), "img/textures/ne2.bmp");
    initTextureObject(&(to_return->ne3), "img/textures/ne3.bmp");

    initTextureObject(&(to_return->gr1), "img/textures/gr1.bmp");
    initTextureObject(&(to_return->gr2), "img/textures/gr2.bmp");

    initTextureObject(&(to_return->bl1), "img/textures/bl1.bmp");
    initTextureObject(&(to_return->bl2), "img/textures/bl2.bmp");
    initTextureObject(&(to_return->bl3), "img/textures/bl3.bmp");
    initTextureObject(&(to_return->w1), "img/textures/wall.bmp");

    initTextureObject(&(to_return->granit), "img/textures/granit.bmp");
    initTextureObject(&(to_return->basalt), "img/textures/basalt.bmp");
    initTextureObject(&(to_return->calcaire), "img/textures/calcaire.bmp");
    initTextureObject(&(to_return->gres), "img/textures/gres.bmp");
    initTextureObject(&(to_return->marbre), "img/textures/marbre.bmp");
    initTextureObject(&(to_return->schiste), "img/textures/schiste.bmp");
    
    initTextureObject(&(to_return->fond), "img/textures/fond.bmp");

    return to_return;
}

struct gui_sprite *init_gui_sprite()
{
    struct gui_sprite *to_return = malloc(sizeof(struct gui_sprite));
    initTextureObject(&(to_return->croix), "img/gui/croix.bmp");
    initTextureObject(&(to_return->croix_inverse), "img/gui/croix2.bmp");
    initTextureObject(&(to_return->demarcation), "img/gui/demarcation.bmp");
    initTextureObject(&(to_return->plus), "img/gui/buttons/plus.bmp");
    initTextureObject(&(to_return->moins), "img/gui/buttons/moins.bmp");
    initTextureObject(&(to_return->elipse), "img/gui/elipse.bmp");
    initTextureObject(&(to_return->selecteur), "img/gui/selected.bmp");
    initTextureObject(&(to_return->main_menu_button), "img/gui/buttons/main_menu.bmp");
    initTextureObject(&(to_return->pressed_main_menu_button), "img/gui/buttons/pressed_main_menu.bmp");
    initTextureObject(&(to_return->pressed_sound_button), "img/gui/buttons/no_sound.bmp");
    initTextureObject(&(to_return->sound_button), "img/gui/buttons/sound.bmp");
    initTextureObject(&(to_return->lines), "img/gui/buttons/lines.bmp");
    initTextureObject(&(to_return->square), "img/gui/buttons/square.bmp");
    initTextureObject(&(to_return->triangle), "img/gui/buttons/triangle.bmp");
    initTextureObject(&(to_return->splited_lines), "img/gui/buttons/splitted.bmp");
    initTextureObject(&(to_return->pressed_lines), "img/gui/buttons/pressed_lines.bmp");
    initTextureObject(&(to_return->pressed_square), "img/gui/buttons/pressed_square.bmp");
    initTextureObject(&(to_return->pressed_triangle), "img/gui/buttons/pressed_triangle.bmp");
    initTextureObject(&(to_return->pressed_splited_lines), "img/gui/buttons/pressed_splitted.bmp");
    return to_return;
}

struct img *init_img()
{
    struct img *ret = malloc(sizeof(struct img));
    ret->t = init_textures();
    ret->s = init_skin();
    ret->g = init_gui_sprite();
    return ret;
}
