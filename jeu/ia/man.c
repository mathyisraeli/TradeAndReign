#include "man.h"

typedef struct {
    int dx;
    int dy;
} Direction;

uint8_t house1[4][3] = {{3,3,0}, {1, 1, 1},{1, 1, 1},{1, 1, 1}};
uint8_t house2[7][6] = {{6,6,0}, {1, 1, 1,1,1,1},{1, 0, 0,0,0,1},{1, 0, 0,0,0,1},{1, 0, 0,0,0,1},{1, 0, 0,0,0,1},{1, 1, 1,1,1,1}};

char have_ground_in_inventory(struct linked_item *e)
{
    if (exist_in_linked_item(e, "herbe") != NULL)
        return 1;
    if (exist_in_linked_item(e, "sable") != NULL)
        return 1;
    return 0;

}

unsigned int how_much_food(struct linked_item *e)
{
    unsigned int ret = 0;
    for (struct linked_item *p = e; p != NULL; p = p->next)
    {
        if (strcmp(p->nom, "fruit") == 0)
            ret += FOOD_VALUE_FRUIT * p->count;
        else if (strcmp(p->nom, "vegetable") == 0)
            ret += FOOD_VALUE_VEGETABLE * p->count;
        else if (strcmp(p->nom, "meat") == 0)
            ret += FOOD_VALUE_MEAT * p->count;
        else if (strcmp(p->nom, "spice") == 0)
            ret += FOOD_VALUE_SPICE * p->count;
    }
    return ret;
}

void eat(struct personnages *perso)
{
    for (struct linked_item *p = perso->i_list; p != NULL; p = p->next)
    {
        if (strcmp(p->nom, "fruit") == 0)
        {
            sprintf(ordre+strlen(ordre), "%d 16 1 fruit %d 07 %d ", perso->id, perso->id, FOOD_VALUE_FRUIT);
            return;
        }
        else if (strcmp(p->nom, "vegetable") == 0)
        {
            sprintf(ordre+strlen(ordre), "%d 16 1 vegetable %d 07 %d ", perso->id, perso->id, FOOD_VALUE_VEGETABLE);
            return;
        }
        else if (strcmp(p->nom, "meat") == 0)
        {
            sprintf(ordre+strlen(ordre), "%d 16 1 meat %d 07 %d ", perso->id, perso->id, FOOD_VALUE_MEAT);
            return;
        }
        else if (strcmp(p->nom, "spice") == 0)
        {
            sprintf(ordre+strlen(ordre), "%d 16 1 spice %d 07 %d ", perso->id, perso->id, FOOD_VALUE_SPICE);
            return;
        }
    }
}


int avverage_alt(struct personnages *p)
{
    int sum = 0;
    for (int i = 0; i < house2[0][0]; i++)
        for (int j = 0; j < house2[0][1]; j++)
            sum += ground_altitude [i * max_x + j - p->house_id];
    return sum / (house2[0][0] * house2[0][1]);
}


int findnext(struct personnages *p)
{
    int px = (int)p->x;
    int py = (int)p->y;
    char next = 0;
    for (int i = 0; i < house2[0][0]; i++)
    {
        for (int j = 0; j < house2[0][1]; j++)
        {
            if (next == 1)
                return i * max_x + j - p->house_id;
            else if (px + py * max_x == -p->house_id + i * max_x + j)
                next = 1;
        }    
    }
    return -p->house_id;
}

char check_watter_house(struct personnages *p)
{
    for (int i = 0; i < house2[0][0]; i++)
        for (int j = 0; j < house2[0][1]; j++)
            if (ground_texture[i * max_x + j - p->house_id] == img->t->ea1 || ground_texture[i * max_x + j - p->house_id] == img->t->ea2 || ground_texture[i * max_x + j - p->house_id] == img->t->ea3)
                return 1;
    return 0;
}

/*
char go_to_top(struct personnages *p, int top)
{
    int start = -p->house_id - 1 - max_x;
    for (int i = 0; i < house2[0][0]+2; i++)
    {
        for (int j = 0; j < house2[0][1]+2; j++)
        {
            int x = start%max_x + j;
            int y = start/max_x + i;
            if (x < max_x && 0 <= x && y < max_y && 0 <= y && building_id[x + y * max_x] == -1 && ground_altitude[x + y * max_x] > top)
            {
                if (p->x == x && p->y == y)
                    return 1;
                p->ordrex = x;
                p->ordrey = y;
                if (findpath(p) == 1)
                    return 2;
            }
        }
    }
    return 3;
}*/

void put_ground(struct personnages *p)
{
    if (exist_in_linked_item(p->i_list, "herbe") != NULL)
    {
        sprintf(ordre+strlen(ordre), "%d 16 1 herbe %d 13 %d he1 ", p->id, p->id, (int)p->x + (int)p->y*max_x);
        return;
    }
    if (exist_in_linked_item(p->i_list, "sable") != NULL)
    {
        sprintf(ordre+strlen(ordre), "%d 16 1 sable %d 13 %d sa1 ", p->id, p->id, (int)p->x + (int)p->y*max_x);
        return ;
    }
}

int find_extreme_altitude_house(struct personnages *p, int *lowgo, int *highgo)
{
    p = p;
    int lowest = ground_altitude[-p->house_id];
    int highest = ground_altitude[-p->house_id];
    *lowgo = -p->house_id;
    *highgo =  -p->house_id;
    for (int i = 1; i < house2[0][0]+1; i++)
    {
        for (int j = 0; j < house2[0][1]; j++)
        {
            if (lowest >= ground_altitude[-p->house_id+(i-1)*max_x + j])
            {
                *lowgo = -p->house_id+(i-1)*max_x + j;
                lowest = ground_altitude[-p->house_id+(i-1)*max_x + j];
            }
            else if (ground_altitude[-p->house_id+(i-1)*max_x + j] >= highest)
            {
                *highgo = -p->house_id+(i-1)*max_x + j;
                highest = ground_altitude[-p->house_id+(i-1)*max_x + j];
            }
        }
    }
    if (highest == lowest + 1)
        return highest;
    return -1;
}


char can_walk_near_this_place(struct personnages *p, int coo)
{
    if (building_id[coo + 1] == -1)
    {
        p->ordrex = (coo+1)%max_x;
        p->ordrey = (coo+1)/max_x;
        if (findpath(p) == 1)
            return 1;
    }
    else if (building_id[coo + 1 + max_x] == -1)
    {
        p->ordrex = (coo+1+max_x)%max_x;
        p->ordrey = (coo+1+max_x)/max_x;
        if (findpath(p) == 1)
            return 1;
    }
    else if (building_id[coo + max_x] == -1)
    {
        p->ordrex = (coo+max_x)%max_x;
        p->ordrey = (coo+max_x)/max_x;
        if (findpath(p) == 1)
            return 1;
    }
    else if (building_id[coo - 1 + max_x] == -1)
    {
        p->ordrex = (coo-1+max_x)%max_x;
        p->ordrey = (coo-1+max_x)/max_x;
        if (findpath(p) == 1)
            return 1;
    }
    else if (building_id[coo - 1] == -1)
    {
        p->ordrex = (coo-1)%max_x;
        p->ordrey = (coo-1)/max_x;
        if (findpath(p) == 1)
            return 1;
    }
    else if (building_id[coo - 1 - max_x] == -1)
    {
        p->ordrex = (coo-1-max_x)%max_x;
        p->ordrey = (coo-1-max_x)/max_x;
        if (findpath(p) == 1)
            return 1;
    }
    else if (building_id[coo - max_x] == -1)
    {
        p->ordrex = (coo-max_x)%max_x;
        p->ordrey = (coo-max_x)/max_x;
        if (findpath(p) == 1)
            return 1;
    }
    else if (building_id[coo + 1 - max_x] == -1)
    {
        p->ordrex = (coo+1-max_x)%max_x;
        p->ordrey = (coo+1-max_x)/max_x;
        if (findpath(p) == 1)
            return 1;
    }
    p->ordrex = -1;
    return 0;
}


int find_where_to_build(struct personnages *p)
{
    for (int i = 1; i < house2[0][0]+1; i++)
    {
        for (int j = 0; j < house2[0][1]; j++)
        {
            if (house2[i][j] == 1)
            {
                int coo = -p->house_id + (i - 1) * max_x + j;
                if (building_id[coo] == -1 || strcmp(find_building_by_id(building_id[coo])->skin, "141") != 0)
                    return coo;
            }
        }
    }
    printf ("error\n");
    return -1;
}

char check_can_build(struct personnages *p, int x, int y)
{
    p = p;
    for (int i = 1; i < house2[0][0]+1; i++)
    {
        for (int j = 0; j < house2[0][1]; j++)
        {
            if (house2[i][j] == 1)
            {
                int coo = x + (i - 1 + y) * max_x + j;
                if (building_id[coo] != -1)
                    return 0;
            }
        }
    }
    return 1;
}


char check_if_surface_is_flat(struct personnages *p, int coo)
{
    p = p;
    for (int i = 1; i < house2[0][0]+1; i++)
        for (int j = 0; j < house2[0][1]; j++)
            if (ground_altitude[coo + (i-1)*max_x + j] != ground_altitude[coo])
                return 0;
    return 1;
}


void ia_man(struct personnages *p)
{
    if (p->faim < 0)
        sprintf (ordre + strlen(ordre), "%d 00 -1 ", p->id);
    
    if (p->animation_2 > 0)
	{
		if (p->animation >= 3)
			sprintf (ordre + strlen(ordre), "%d 22 0 %d 21 0 ", p->id, p->id);
		else
			sprintf(ordre + strlen(ordre), "%d 21 %d ",p->id, p->animation +1 );
        return;
	}

    if (how_much_food(p->i_list) <= 1000)
    {

        struct personnages *a_tree = NULL;
        float mindist = 99999;
        for (struct linked_list *parcour = list; parcour != NULL; parcour = parcour->next)
        {
            if (strcmp(parcour->p->skin, "01") == 0 && (parcour->p->x - p->x)*(parcour->p->x - p->x) + (parcour->p->y - p->y) * (parcour->p->y - p->y) < 4 && exist_in_linked_item(parcour->p->i_list, "fruit") != NULL)
            {
                a_tree = parcour->p;
                break;
            }
        }
        if (a_tree == NULL)
        {
            for (struct linked_list *parcour = list; parcour != NULL; parcour = parcour->next)
            {
                if (strcmp(parcour->p->skin, "01") == 0 && (parcour->p->x - p->x)*(parcour->p->x - p->x) + (parcour->p->y - p->y) * (parcour->p->y - p->y) < mindist && exist_in_linked_item(parcour->p->i_list, "fruit") != NULL)
                {
                    a_tree = parcour->p;
                    mindist = (parcour->p->x - p->x)*(parcour->p->x - p->x) + (parcour->p->y - p->y) * (parcour->p->y - p->y);
                }
            }
            if (a_tree != NULL)
            {
                sprintf(ordre + strlen(ordre), "%d 03 %f %d 04 %f ", p->id, a_tree->x+1, p->id, a_tree->y);
            }
        }
        else
        {
            if (can_add("wooden-board", 1, p->i_list) == 0)
                put_ground(p);
            else
                sprintf(ordre + strlen(ordre), "%d 16 1 fruit %d 16 +1 fruit ", a_tree->id, p->id);
        }
    }
    else
    {
        if (p->faim < 50)
        {
            eat(p);
        }

        if (p->ordrex > 0)
        {
            if (pow(p->ordrex - p->x,2) +  pow(p->ordrey - p->y,2) < p->vitesse_dep )
            {
                sprintf (ordre + strlen(ordre), "%d 03 -1 %d 01 %f %d 02 %f ", p->id, p->id, p->ordrex, p->id, p->ordrey);
                p->chemin_is_set = 0;
            }
            else if (p->chemin_is_set == 1 || findpath(p) == 1)
            {
                int src = (int)p->y * max_x + (int)p->x;
                int dst = p->chemin[src].prev;

                if (src + 1 == dst)
                    sprintf (ordre + strlen(ordre), "%d 01 +%f %d 05 f %d 21 %d ", p->id, p->vitesse_dep, p->id, p->id, (p->animation+1)%5);
                else if (src - 1 == dst)
                    sprintf (ordre + strlen(ordre), "%d 01 -%f %d 05 b %d 21 %d ", p->id, p->vitesse_dep, p->id, p->id, (p->animation+1)%5); 
                else if (src - max_x == dst)
                    sprintf (ordre + strlen(ordre), "%d 02 -%f %d 05 d %d 21 %d ", p->id, p->vitesse_dep, p->id, p->id, (p->animation+1)%5);
                else if (src + max_x == dst)
                    sprintf (ordre + strlen(ordre), "%d 02 +%f %d 05 h %d 21 %d ", p->id, p->vitesse_dep, p->id, p->id, (p->animation+1)%5);
                else if (src + 1 + max_x == dst)
                    sprintf (ordre + strlen(ordre), "%d 01 +%f %d 02 +%f %d 05 g %d 21 %d ", p->id, p->vitesse_dep*0.707, p->id,p->vitesse_dep*0.707, p->id, p->id, (p->animation+1)%5);
                else if (src + 1 - max_x == dst)
                    sprintf (ordre + strlen(ordre), "%d 01 +%f %d 02 -%f %d 05 e %d 21 %d ", p->id, p->vitesse_dep*0.707, p->id,p->vitesse_dep*0.707, p->id, p->id, (p->animation+1)%5);
                else if (src - 1 + max_x == dst)
                    sprintf (ordre + strlen(ordre), "%d 01 -%f %d 02 +%f %d 05 a %d 21 %d ", p->id, p->vitesse_dep*0.707, p->id,p->vitesse_dep*0.707, p->id, p->id, (p->animation+1)%5);
                else if (src -1 - max_x == dst)
                    sprintf (ordre + strlen(ordre), "%d 01 -%f %d 02 -%f %d 05 c %d 21 %d ", p->id, p->vitesse_dep*0.707, p->id,p->vitesse_dep*0.707, p->id, p->id, (p->animation+1)%5);
                else
                {
                    if (p->ordrex > p->x)
                        sprintf (ordre + strlen(ordre), "%d 01 +%f %d 05 f %d 21 %d ", p->id, p->vitesse_dep, p->id, p->id, (p->animation+1)%5);
                    else if (p->ordrex < p->x)
                        sprintf (ordre + strlen(ordre), "%d 01 -%f %d 05 b %d 21 %d ", p->id, p->vitesse_dep, p->id, p->id, (p->animation+1)%5);
                    if (p->ordrey > p->y)
                        sprintf (ordre + strlen(ordre), "%d 02 +%f %d 05 h %d 21 %d ", p->id, p->vitesse_dep, p->id, p->id, (p->animation+1)%5);
                    else if (p->ordrey < p->y)
                        sprintf (ordre + strlen(ordre), "%d 02 -%f %d 05 d %d 21 %d ", p->id, p->vitesse_dep, p->id, p->id, (p->animation+1)%5);
                    }

            }
            else
            {
                sprintf (ordre + strlen(ordre), "%d 03 -1 ", p->id);
                p->chemin_is_set = 0;
            }
        }
        else 
        {
            struct personnages *closest = NULL;
            int mind = 900;
            for (struct linked_enemie *e = p->e_list; e != NULL; e = e->next)
            {
                struct personnages *ee = find_perso_by_name(e->nom);
                if (ee == NULL)
                {
                    sprintf(ordre + strlen(ordre), "%d 15 %s ", p->id, e->nom);
                }
                else
                {
                    float square_dist = (ee->x  - p->x)*(ee->x  - p->x)+(ee->y  - p->y)*(ee->y  - p->y);
                    if (square_dist < mind)
                    {
                        mind = square_dist;
                        closest = ee;
                    }
                }
            }
            if (closest != NULL)
            {
                if (mind < p->porte_dom*p->porte_dom)
                    sprintf (ordre + strlen(ordre), "%d 22 1 %d 21 0 %d 00 -%d ", p->id, p->id, closest->id, p->dom);
                else
                    sprintf (ordre + strlen(ordre), "%d 03 %f %d 04 %f ", p->id, closest->x, p->id, closest->y);
                    
            }
            else if (p->house_id < 0) // i dont have a house
            {
                struct building *a_house  = NULL;
                for (struct building *parcour = list_building; parcour != NULL; parcour = parcour->next)
                {
                    if (parcour->skin[1] == '1' && (parcour->x - p->x)*(parcour->x - p->x) + (parcour->y - p->y) * (parcour->y - p->y) < 400) // there is a house in his field of view
                    {
                        char nobody = 1;
                        for (struct linked_list *pa = list; pa != NULL; pa = pa->next)
                        {
                            if (pa->p->house_id == parcour->id)
                            {
                                pa = NULL;
                                nobody = 0;
                            }
                        }
                        if (nobody == 1)
                        {
                            a_house = parcour;
                            break;
                        }
                    }
                }
                if (a_house != NULL)
                {
                    sprintf (ordre + strlen(ordre), "%d 32 %d ",p->id, a_house->id);
                }
                else // i should build a house
                {
                    int moix = (int)p->x;
                    int moiy = (int)p->y;
                    int whereiam = moix + moiy * max_x;
                    if (p->house_id == -1 || check_watter_house(p) == 1)
                    {
                        /*for (struct building *parcour = list_building; parcour != NULL; parcour = parcour->next)
                        {
                            if (strcmp(parcour->skin, "141") == 0 && (parcour->x - p->x)*(parcour->x - p->x) + (parcour->y - p->y) * (parcour->y - p->y) < 400)
                            {
                                sprintf (ordre + strlen(ordre), "%d 32 -%d ",p->id, parcour->x + parcour->y * max_x);
                                break;
                            }
                        }*/
                        if (moix > 0 && building_id[moix - 1 + moiy * max_x] == -1 && check_can_build(p,moix - 1, moiy))
                            sprintf(ordre + strlen(ordre), "%d 32 -%d ", p->id, moix-1 + moiy * max_x);
                        else if (moix < max_x - 1 && building_id[moix + 1 + moiy * max_x] == -1 && check_can_build(p,moix + 1, moiy))
                            sprintf(ordre + strlen(ordre), "%d 32 -%d ", p->id, moix+1 + moiy * max_x);
                        else if (moiy > 0 && building_id[moix - max_x + moiy * max_x] == -1 && check_can_build(p,moix, moiy-1))
                            sprintf(ordre + strlen(ordre), "%d 32 -%d ", p->id, moix-max_x + moiy * max_x);
                        else if (moiy < max_y - 1 && building_id[moix + max_x + moiy * max_x] == -1 && check_can_build(p,moix, moiy+1))
                            sprintf(ordre + strlen(ordre), "%d 32 -%d ", p->id, moix+max_x + moiy * max_x);
                    }
                    else 
                    {
                        int highgo;
                        int lowgo;
                        find_extreme_altitude_house(p, &lowgo, &highgo);
                        if (ground_altitude[highgo] != ground_altitude[lowgo])
                        {
                            int av = avverage_alt(p);
                            if (ground_altitude[whereiam] > av && 10 > n_item(p->i_list))
                            {
                                SDL_Texture *t = ground_texture[whereiam];
                                if (t == img->t->he1 || t == img->t->he2 || t == img->t->he3 || t == img->t->he4 || t == img->t->he5)
                                    sprintf (ordre + strlen(ordre), "%d 16 +1 herbe %d 08 %d %d 22 2 %d 21 0 ", p->id, p->id, moix + (moiy)*max_x, p->id, p->id);
                                else if (t == img->t->sa1 || t == img->t->sa2 || t == img->t->sa3)
                                    sprintf (ordre + strlen(ordre), "%d 16 +1 sable %d 08 %d %d 22 2 %d 21 0 ", p->id, p->id, moix + (moiy)*max_x, p->id, p->id);
                                else if (t == img->t->ne1 || t == img->t->ne2 || t == img->t->ne3)
                                    sprintf (ordre + strlen(ordre), "%d 08 %d %d 13 %d ea1 ", p->id, moix + (moiy)*max_x, p->id, moix + (moiy)*max_x); 
                            }
                            
                            else if (av > ground_altitude[whereiam] && have_ground_in_inventory(p->i_list))
                            {
                                put_ground(p);
                            }
                            else if (10 == n_item(p->i_list))
                            {
                                if (whereiam == lowgo)
                                    put_ground(p);
                                else
                                    sprintf(ordre + strlen(ordre), "%d 03 %f %d 04 %f ", p->id, (lowgo%max_x)+0.5, p->id, (lowgo/max_x)+0.5);
                            }
                            else
                            {
                                int wheretogo = findnext(p);
                                int togox = wheretogo%max_x;
                                int togoy = wheretogo/max_x;
                                //printf ("%d %d %d\n%d %d %d\n%d %d %d\n_____\n", ground_altitude[-p->house_id], ground_altitude[-p->house_id+1],ground_altitude[-p->house_id+2],ground_altitude[-p->house_id+max_x], ground_altitude[-p->house_id+1+max_x], ground_altitude[-p->house_id+2+max_x],ground_altitude[-p->house_id+2*max_x], ground_altitude[-p->house_id+2*max_x+1],ground_altitude[-p->house_id+2*max_x+2]);
                                sprintf(ordre + strlen(ordre), "%d 03 %f %d 04 %f ", p->id, togox+0.5, p->id, togoy+0.5);
                            }
                        }
                        else
                        {
                            if (count_item(p->i_list, "wooden-board") >= 9) //si j'ai dans mon inventaire de quoi placer des fondations
                            {
                                int coo = find_where_to_build(p);
                                int bx = coo%max_x;
                                int by = coo/max_x;
                                if ((p->x - bx)*(p->x - bx) + (p->y - by) * (p->y - by) < 4)
                                {
                                    add_wood_pillar_or_wood_house(bx, by);
                                    sprintf (ordre + strlen(ordre), "%d 16 9 wooden-board ", p->id);
                                }
                                else if (can_walk_near_this_place(p, coo) != 1)
                                    printf ("can't aproach house");
                            }
                            else
                            {
                                struct personnages *a_tree = NULL;
                                float mindist = 99999;
                                for (struct linked_list *parcour = list; parcour != NULL; parcour = parcour->next)
                                {
                                    if (strcmp(parcour->p->skin, "01") == 0 && (parcour->p->x - p->x)*(parcour->p->x - p->x) + (parcour->p->y - p->y) * (parcour->p->y - p->y) < 4)
                                    {
                                        a_tree = parcour->p;
                                        break;
                                    }
                                }
                                if (a_tree == NULL)
                                {
                                    for (struct linked_list *parcour = list; parcour != NULL; parcour = parcour->next)
                                    {
                                        if (strcmp(parcour->p->skin, "01") == 0 && (parcour->p->x - p->x)*(parcour->p->x - p->x) + (parcour->p->y - p->y) * (parcour->p->y - p->y) < mindist)
                                        {
                                            a_tree = parcour->p;
                                            mindist = (parcour->p->x - p->x)*(parcour->p->x - p->x) + (parcour->p->y - p->y) * (parcour->p->y - p->y);
                                        }
                                    }
                                    if (a_tree != NULL)
                                    {
                                        sprintf(ordre + strlen(ordre), "%d 03 %f %d 04 %f ", p->id, a_tree->x+1, p->id, a_tree->y);
                                    }
                                }
                                else
                                {
                                    if (n_item(p->i_list) > 9)
                                    {
                                        if (have_ground_in_inventory(p->i_list))
                                            put_ground(p);
                                        else
                                            eat(p);
                                    }
                                    else
                                    {
                                        if (n_item(a_tree->i_list) > 0)
                                            sprintf(ordre + strlen(ordre), "%d 16 1 fruit %d 16 +1 fruit ", a_tree->id, p->id);
                                        else
                                        {
                                            sprintf (ordre + strlen(ordre), "%d 22 1 %d 21 0 ", p->id, p->id);
                                            if (a_tree->pv -  p->dom >= 4)
                                                sprintf(ordre + strlen(ordre), "%d 00 -%d ", a_tree->id, p->dom);
                                            else if (can_add("wooden-board", 1, p->i_list) == 1)
                                                sprintf(ordre + strlen(ordre), "%d 00 -1 %d 16 +1 wooden-board ", a_tree->id, p->id);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else 
            {
                if (find_building_by_id(p->house_id) == NULL)
                    sprintf (ordre + strlen(ordre), "%d 32 -1 ",p->id);
            }
        }
    }
    if (strcmp(p->echange_player, "none") != 0)
    {
        sprintf (ordre + strlen(ordre), "%d 20 votre proposition est ininteressante\037 %d 17 none none 0 none 0 ", p->id, p->id);
        p->speak_timer = 1350;
    }

    if (p->speak_timer > 0)
        p->speak_timer --;
    else if (p->speak_timer <= 0 && p->speak[0] != 0)
        sprintf (ordre + strlen(ordre), "%d 20 \037 ", p->id);
}
