#include "tree.h"

char watter_around(int coo)
{
    SDL_Texture *t1 = ground_texture[coo+1];
    SDL_Texture *t2 = ground_texture[coo-1];
    SDL_Texture *t3 = ground_texture[coo+max_x];
    SDL_Texture *t4 = ground_texture[coo-max_x];
    if (ground_texture[coo] == img->t->ea1 || ground_texture[coo] ==  img->t->ea2 || ground_texture[coo] == img->t->ea3)
        return 2;
    if (t1 == img->t->ea1 || t1 ==  img->t->ea2 || t1 == img->t->ea3 || t2 == img->t->ea1 || t2 == img->t->ea2 || t2 == img->t->ea3 || t3 == img->t->ea1 || t3 ==  img->t->ea2 || t3 == img->t->ea3 || t4 == img->t->ea1 || t4 ==  img->t->ea2 || t4 == img->t->ea3)
        return 1;
    return 0;
}

void ia_arbre(struct personnages *p)
{
    p->animation += 1; 
    if (p->animation > 60)
    {
        if (p->faim > 20)
        {
            char w = watter_around((int)p->x + ((int)p->y)*max_x);
            if (w == 2)
                sprintf(ordre+strlen(ordre), "%d 00 -1 ", p->id);
            if (w== 1)
            {   
                if (p->pv > 25)
                {
                    sprintf(ordre+strlen(ordre), "%d 16 +1 fruit %d 07 -21 ", p->id, p->id);
                    p->animation = 0; 
                }
                if (50 > p->pv)
                    sprintf(ordre+strlen(ordre), "%d 00 +1 ", p->id);
            }
        }
        else
        {
            sprintf (ordre + strlen(ordre), "%d 07 1 ", p->id);
            p->animation = 0; 
        }
        if (count_item(p->i_list, "fruit") == 20)
        {
            sprintf (ordre + strlen(ordre), "-1 50 none %f %f -1.0 -1.0 a 0 0 arbre1 none none none none 0 none none 0 none 0 3 0 0 empty empty empty empty empty empty [] [] \n%d 16 -20 fruit ", p->x + 1, p->y + 1, p->id);
        }
    }
    if (strcmp(p->echange_player, "none") != 0)
    {
        struct personnages *echange_player = find_perso_by_name(p->echange_player);
        if (echange_player != NULL && 9 > (echange_player->x - moi->x)*(echange_player->x - moi->x)+(echange_player->y - moi->y)*(echange_player->y - moi->y))
            echange_item(p, echange_player);
    }  
}
