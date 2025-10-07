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

    char filepath[100];
    char sexe[2][6] = {"man", "woman"};
    char couleur[10][10] = {"ivory", "marble", "sand", "gold", "leather", "oak", "bronze", "coffee", "chocolate", "ebony"};
    char animation2[3][10] = {"walk", "punch", "gather"};

    for (int i = 0; i < 2   ; i++) // sexe
    {
        for (int j = 0; j < 10; j++) // couleur de peau
        {
            for (int k = 0; k < 3; k++) // animation2
            {
                for (int l = 0; l < 6; l++) // animation
                {
                    for (int m = 0; m < 8; m++) // angle
                    {
                        sprintf (filepath, "img/%s/%s/%s-%d-%d.bmp", sexe[i], couleur[j], animation2[k],m, l+1);
                        initTextureObject(&(to_return->Man[i][j][k][l][m]), filepath);
                    }
                }
            }
        }
    }

    for (int k = 0; k < 3; k++) // animation2
    {
        for (int l = 0; l < 6; l++) // animation
        {
            for (int m = 0; m < 8; m++) // angle
            {
                sprintf (filepath, "img/man/breeches-lin/%s-%d-%d.bmp", animation2[k],m, l+1);
                //printf ("%s\n", filepath); //debug
                initTextureObject(&(to_return->breechesLin[k][l][m]), filepath);
            }
        }
    }
    for (int k = 0; k < 3; k++) // animation2
    {
        for (int l = 0; l < 6; l++) // animation
        {
            for (int m = 0; m < 8; m++) // angle
            {
                sprintf (filepath, "img/woman/shift-lin/%s-%d-%d.bmp", animation2[k],m, l+1);
                initTextureObject(&(to_return->shiftLin[k][l][m]), filepath);
            }
        }
    }
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
