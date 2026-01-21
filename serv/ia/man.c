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
            remove_from_inventory("fruit", perso->i_list, 1);
            perso->faim += FOOD_VALUE_FRUIT;
            perso->a_bouger += 1;
            return;
        }
        else if (strcmp(p->nom, "vegetable") == 0)
        {
            remove_from_inventory("vegetable", perso->i_list, 1);
            perso->faim += FOOD_VALUE_VEGETABLE;
            perso->a_bouger += 1;
            return;
        }
        else if (strcmp(p->nom, "meat") == 0)
        {
            remove_from_inventory("meat", perso->i_list, 1);
            perso->faim += FOOD_VALUE_MEAT;
            perso->a_bouger += 1;
            return;
        }
        else if (strcmp(p->nom, "spice") == 0)
        {
            remove_from_inventory("spice", perso->i_list, 1);
            perso->faim += FOOD_VALUE_SPICE;
            perso->a_bouger += 1;
            return;
        }
    }
}


int avverage_alt(struct personnages *p)
{
    int sum = 0;
    for (int i = 0; i < house2[0][0]; i++)
        for (int j = 0; j < house2[0][1]; j++)
            sum += altitude(i * max_x + j - p->house_id);
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
            if (ground[i * max_x + j - p->house_id]->texture == ea1 || ground[i * max_x + j - p->house_id]->texture == ea2 || ground[i * max_x + j - p->house_id]->texture == ea3)
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
        remove_from_inventory("herbe", p->i_list, 1);
        add_1_pixel((int)p->x + (int)p->y*max_x, he1);
        p->a_bouger += 1;
        return;
    }
    if (exist_in_linked_item(p->i_list, "sable") != NULL)
    {
        remove_from_inventory("sable", p->i_list, 1);
        add_1_pixel((int)p->x + (int)p->y*max_x, sa1);
        p->a_bouger += 1;
        return ;
    }
}

int find_extreme_altitude_house(struct personnages *p, int *lowgo, int *highgo)
{
    p = p;
    int lowest = altitude(-p->house_id);
    int highest = altitude(-p->house_id);
    *lowgo = -p->house_id;
    *highgo =  -p->house_id;
    for (int i = 1; i < house2[0][0]+1; i++)
    {
        for (int j = 0; j < house2[0][1]; j++)
        {
            if (lowest >= altitude(-p->house_id+(i-1)*max_x + j))
            {
                *lowgo = -p->house_id+(i-1)*max_x + j;
                lowest = altitude(-p->house_id+(i-1)*max_x + j);
            }
            else if (altitude(-p->house_id+(i-1)*max_x + j) >= highest)
            {
                *highgo = -p->house_id+(i-1)*max_x + j;
                highest = altitude(-p->house_id+(i-1)*max_x + j);
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
                if (building_id[coo] == -1 || strcmp(get_ptr_from_id_building(building_id[coo])->skin, "141") != 0)
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
            if (altitude(coo + (i-1)*max_x + j) != altitude(coo))
                return 0;
    return 1;
}


void ia_man(struct personnages *p)
{
    printf ("%s %d\n", p->nom, p->id);
    if (p->faim < 0)
    {
        p->pv -= 1;
        p->a_bouger = 1;
    }
    if (p->speak_timer > 0)
        p->speak_timer --;
    if (p->animation_2 > 0)
	{
		if (p->animation >= 3)
        {
			p->animation_2 = 0;
            p->animation = 0;
            p->a_bouger = 1;
        }
		else
        {
            p->animation += 1;
        }
        return;
	}

    if (how_much_food(p->i_list) <= 1000)
    {

        int a_tree = -1;
        float mindist = 99999;
        for (int i = 0; i <= list.maxid; i++)
        {
            if (list.data[i].is_active == 0)
                continue;
            if (strcmp(list.data[i].skin, "01") == 0 && (list.data[i].x - p->x)*(list.data[i].x - p->x) + (list.data[i].y - p->y) * (list.data[i].y - p->y) < 4 && exist_in_linked_item(list.data[i].i_list, "fruit") != NULL)
            {
                a_tree = i;
                break;
            }
        }
        if (a_tree == -1)
        {
            for (int i = 0; i <= list.maxid; i++)
            {
                if (list.data[i].is_active == 0)
                    continue;
                if (strcmp(list.data[i].skin, "01") == 0 && (list.data[i].x - p->x)*(list.data[i].x - p->x) + (list.data[i].y - p->y) * (list.data[i].y - p->y) < mindist && exist_in_linked_item(list.data[i].i_list, "fruit") != NULL)
                {
                    a_tree = i;
                    mindist = (list.data[i].x - p->x)*(list.data[i].x - p->x) + (list.data[i].y - p->y) * (list.data[i].y - p->y);
                }
            }
            if (a_tree != -1)
            {
                p->ordrex = list.data[a_tree].x+1;
                p->ordrey = list.data[a_tree].y;
                p->a_bouger = 1;
            }
        }
        else
        {
            if (can_add("wooden-board", 1, p->i_list) == 0)
                put_ground(p);
            else
            {
                append_in_inventory("fruit", p->i_list, 1);
                remove_from_inventory("fruit", list.data[a_tree].i_list, 1);
                p->a_bouger = 1;
                list.data[a_tree].a_bouger = 1; 

            }
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
                p->ordrex = -1;
                p->x = p->ordrex;
                p->y = p->ordrey;
                p->a_bouger = 1;
                p->chemin_is_set = 0;
            }
            else if (p->chemin_is_set == 1 || findpath(p) == 1)
            {
                int src = (int)p->y * max_x + (int)p->x;
                int dst = p->chemin[src].prev;

                if (src + 1 == dst)
                {
                    p->x += p->vitesse_dep;
                    p->angle = 'f';
                }
                else if (src - 1 == dst)
                {
                    p->x -= p->vitesse_dep;
                    p->angle = 'b';
                }
                else if (src - max_x == dst)
                {
                    p->y -= p->vitesse_dep;
                    p->angle = 'd';
                }
                else if (src + max_x == dst)
                {
                    p->y += p->vitesse_dep;
                    p->angle = 'd';
                }
                else if (src + 1 + max_x == dst)
                {
                    p->y += p->vitesse_dep*0.707;
                    p->angle = 'd';
                    p->x += p->vitesse_dep*0.707;
                }
                else if (src + 1 - max_x == dst)
                {
                    p->y -= p->vitesse_dep*0.707;
                    p->angle = 'd';
                    p->x += p->vitesse_dep*0.707;
                }
                else if (src - 1 + max_x == dst)
                {
                    p->y += p->vitesse_dep*0.707;
                    p->angle = 'd';
                    p->x -= p->vitesse_dep*0.707;
                }
                else if (src -1 - max_x == dst)
                {
                    p->y -= p->vitesse_dep*0.707;
                    p->angle = 'd';
                    p->x -= p->vitesse_dep*0.707;
                }
                /*else
                {
                    if (p->ordrex > p->x)
                        sprintf(ordre + strlen(ordre), "0 %d 01 +%f 0 %d 05 f 0 %d 21 %d ", p->id, p->vitesse_dep, p->id, p->id, (p->animation+1)%5);
                    else if (p->ordrex < p->x)
                        sprintf(ordre + strlen(ordre), "0 %d 01 -%f 0 %d 05 b 0 %d 21 %d ", p->id, p->vitesse_dep, p->id, p->id, (p->animation+1)%5);
                    if (p->ordrey > p->y)
                        sprintf(ordre + strlen(ordre), "0 %d 02 +%f 0 %d 05 h 0 %d 21 %d ", p->id, p->vitesse_dep, p->id, p->id, (p->animation+1)%5);
                    else if (p->ordrey < p->y)
                        sprintf(ordre + strlen(ordre), "0 %d 02 -%f 0 %d 05 d 0 %d 21 %d ", p->id, p->vitesse_dep, p->id, p->id, (p->animation+1)%5);
                }*/
                p->a_bouger = 1;
            }
            else
            {
                p->ordrex = -1;
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
                    remove_enemie(e->nom, p->e_list);
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
                {
                    p->animation = 1;
                    p->animation_2 = 0;
                    closest->pv -= p->dom;
                    closest->a_bouger = 1;
                    p->a_bouger = 1;
                }
                else
                {
                    p->ordrex = closest->x;
                    p->ordrey = closest->y;
                }                    
            }
            else if (p->house_id < 0) // i dont have a house
            {
                struct building *a_house  = NULL;
                for (struct building *parcour = list_building; parcour != NULL; parcour = parcour->next)
                {
                    if (parcour->skin[1] == '1' && (parcour->x - p->x)*(parcour->x - p->x) + (parcour->y - p->y) * (parcour->y - p->y) < 400) // there is a house in his field of view
                    {
                        char nobody = 1;
                        for (int i = 0; i <= list.maxid; i++)
                        {
                            if (list.data[i].is_active == 1 && list.data[i].house_id == parcour->id)
                            {
                                nobody = 0;
                                break;
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
                    p->house_id = a_house->id;
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
                                sprintf(ordre + strlen(ordre), "0 %d 32 -%d ",p->id, parcour->x + parcour->y * max_x);
                                break;
                            }
                        }*/
                        if (moix > 0 && building_id[moix - 1 + moiy * max_x] == -1 && check_can_build(p,moix - 1, moiy))
                            p->house_id = -(moix-1 + moiy * max_x);
                        else if (moix < max_x - 1 && building_id[moix + 1 + moiy * max_x] == -1 && check_can_build(p,moix + 1, moiy))
                            p->house_id = -(moix+1 + moiy * max_x);
                        else if (moiy > 0 && building_id[moix - max_x + moiy * max_x] == -1 && check_can_build(p,moix, moiy-1))
                            p->house_id = -(moix-max_x + moiy * max_x);
                        else if (moiy < max_y - 1 && building_id[moix + max_x + moiy * max_x] == -1 && check_can_build(p,moix, moiy+1))
                            p->house_id = -(moix+max_x + moiy * max_x);
                    }
                    else 
                    {
                        int highgo;
                        int lowgo;
                        find_extreme_altitude_house(p, &lowgo, &highgo);
                        if (altitude(highgo) != altitude(lowgo))
                        {
                            int av = avverage_alt(p);
                            if (altitude(whereiam) > av && 10 > n_item(p->i_list))
                            {
                                if (ground[whereiam]->texture == he1 || ground[whereiam]->texture == he2 || ground[whereiam]->texture == he3 || ground[whereiam]->texture == he4 || ground[whereiam]->texture == he5)
                                {
                                    append_in_inventory("herbe", p->i_list, 1);
                                    remove_1_pixel(moix + (moiy)*max_x);
                                    p->animation_2 = 2;
                                    p->animation = 0;
                                    p->a_bouger = 1;
                                }
                                else if (ground[whereiam]->texture == sa1 || ground[whereiam]->texture == sa2 || ground[whereiam]->texture == sa3)
                                {
                                    append_in_inventory("sable", p->i_list, 1);
                                    remove_1_pixel(moix + (moiy)*max_x);
                                    p->animation_2 = 2;
                                    p->animation = 0;
                                    p->a_bouger = 1;
                                }
                                else if (ground[whereiam]->texture == ne1 || ground[whereiam]->texture == ne2 || ground[whereiam]->texture == ne3)
                                {    
                                    remove_1_pixel(moix + (moiy)*max_x);
                                    add_1_pixel(ea1, moix + (moiy)*max_x);
                                }
                            }
                            
                            else if (av > altitude(whereiam) && have_ground_in_inventory(p->i_list))
                            {
                                put_ground(p);
                            }
                            else if (10 == n_item(p->i_list))
                            {
                                if (whereiam == lowgo)
                                    put_ground(p);
                                else
                                {
                                    p->ordrex = (lowgo%max_x)+0.5;
                                    p->ordrey = (lowgo/max_x)+0.5;
                                }
                            }
                            else
                            {
                                int wheretogo = findnext(p);
                                int togox = wheretogo%max_x;
                                int togoy = wheretogo/max_x;
                                p->ordrex = togox+0.5;
                                p->ordrey = togoy+0.5;
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
                                    remove_from_inventory("wooden-board", p->i_list, 9);
                                    p->a_bouger = 1;
                                }
                                else if (can_walk_near_this_place(p, coo) != 1)
                                    printf ("can't aproach house");
                            }
                            else
                            {
                                int a_tree = -1;
                                float mindist = 99999;
                                for (int i = 0; i <= list.maxid; i++)
                                {
                                    if (list.data[i].is_active == 1 && strcmp(list.data[i].skin, "01") == 0 && (list.data[i].x - p->x)*(list.data[i].x - p->x) + (list.data[i].y - p->y) * (list.data[i].y - p->y) < 4)
                                    {
                                        a_tree = i;
                                        break;
                                    }
                                }
                                if (a_tree == -1)
                                {
                                    for (int i = 0; i <= list.maxid; i++)
                                    {
                                        if (list.data[i].is_active == 1  && strcmp(list.data[i].skin, "01") == 0 && (list.data[i].x - p->x)*(list.data[i].x - p->x) + (list.data[i].y - p->y) * (list.data[i].y - p->y) < mindist)
                                        {
                                            a_tree = i;
                                            mindist = (list.data[i].x - p->x)*(list.data[i].x - p->x) + (list.data[i].y - p->y) * (list.data[i].y - p->y);
                                        }
                                    }
                                    if (a_tree != -1)
                                    {
                                        p->ordrex = list.data[a_tree].x+1;
                                        p->ordrey = list.data[a_tree].y;
                                        p->is_active = 1;
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
                                        if (exist_in_linked_item(list.data[a_tree].i_list, "fruit") != NULL)
                                        {
                                            remove_from_inventory("fruit", list.data[a_tree].i_list, 1);
                                            append_in_inventory("fruit", p->i_list, 1);
                                            p->a_bouger = 1;
                                            list.data[a_tree].a_bouger = 1;
                                        }
                                        else
                                        {
                                            p->animation_2 = 1;
                                            p->animation = 0;
                                            p->a_bouger = 1;
                                            list.data[a_tree].a_bouger = 1; 
                                            if (list.data[a_tree].pv -  p->dom >= 4)
                                                list.data[a_tree].pv -= p->dom;
                                            else if (list.data[a_tree].pv > 4)
                                                list.data[a_tree].pv = 4;
                                            else if (can_add("wooden-board", 1, p->i_list) == 1)
                                            {
                                                list.data[a_tree].pv -= 1;
                                                append_in_inventory("wooden-board", p->i_list, 1);
                                            }
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
                if (get_ptr_from_id_building(p->house_id) == NULL)
                {
                    p->house_id = -1;
                    p->a_bouger = 1;
                }
            }
        }
    }
    if (strcmp(p->echange_player, "none") != 0)
    {
        sprintf(p->speak, "votre proposition est ininteressante");
        sprintf(p->item1, "none");
        sprintf(p->item2, "none");
        p->speak_timer = 1350;
        p->a_bouger = 1;
    }
    else if (p->speak_timer <= 0 && p->speak[0] != 0)
    {
        p->speak[0] = 0;
        p->a_bouger = 1;
    }    
    
}
