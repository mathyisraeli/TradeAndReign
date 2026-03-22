#include "man.h"

typedef struct {
    int dx;
    int dy;
} Direction;

uint8_t house1[4][3] = {{3,3,0}, {1, 1, 1},{1, 1, 1},{1, 1, 1}};
uint8_t house2[7][6] = {{6,6,0}, {1, 1, 1,1,1,1},{1, 0, 0,0,0,1},{1, 0, 0,0,0,1},{1, 0, 0,0,0,1},{1, 0, 0,0,0,1},{1, 1, 1,1,1,1}};

char have_ground_in_inventory(struct personnages *p)
{
    if (find_index_in_inventory("herbe", p->items) != -1)
        return 1;
    if (find_index_in_inventory("sable", p->items) != -1)
        return 1;
    return 0;
}

unsigned int how_much_food(struct personnages *p)
{
    unsigned int ret = 0;
    for (int i = 0; 10 > i; i++)
    {
        if (strcmp(p->items[i], "fruit") == 0)
            ret += FOOD_VALUE_FRUIT * p->items_cnt[i];
        else if (strcmp(p->items[i], "vegetable") == 0)
            ret += FOOD_VALUE_VEGETABLE * p->items_cnt[i];
        else if (strcmp(p->items[i], "meat") == 0)
            ret += FOOD_VALUE_MEAT * p->items_cnt[i];
        else if (strcmp(p->items[i], "spice") == 0)
            ret += FOOD_VALUE_SPICE * p->items_cnt[i];
    }
    return ret;
}

void eat(struct personnages *p)
{
    for (int i = 0; 10 > i; i++)
    {
        if (strcmp(p->items[i], "fruit") == 0)
        {
            remove_from_inventory("fruit", 1, p->items, p->items_cnt);
            p->faim += FOOD_VALUE_FRUIT;
            p->a_bouger += 1;
            return;
        }
        else if (strcmp(p->items[i], "vegetable") == 0)
        {
            remove_from_inventory("vegetable", 1, p->items, p->items_cnt);
            p->faim += FOOD_VALUE_VEGETABLE;
            p->a_bouger += 1;
            return;
        }
        else if (strcmp(p->items[i], "meat") == 0)
        {
            remove_from_inventory("meat", 1, p->items, p->items_cnt);
            p->faim += FOOD_VALUE_MEAT;
            p->a_bouger += 1;
            return;
        }
        else if (strcmp(p->items[i], "spice") == 0)
        {
            remove_from_inventory("spice", 1, p->items, p->items_cnt);
            p->faim += FOOD_VALUE_SPICE;
            p->a_bouger += 1;
            return;
        }
    }
}

void move_somewhere_random(struct personnages *p)
{
    int a = rand () % 4;
    if (a == 0 && (int)p->x > 10)
    {
        p->ordrex = (int)p->x - 10;
        p->ordrey = (int)p->y;
    }
    else if (a == 1 && max_x - 10  > (int)p->x)
    {
        p->ordrex = (int)p->x + 10;
        p->ordrey = (int)p->y;
    }
    else if (a == 2 && (int)p->y > 10)
    {
        p->ordrex = (int)p->x;
        p->ordrey = (int)p->y - 10;
    }
    else if (a == 3 && max_y - 10 > (int)p->y)
    {
        p->ordrex = (int)p->x;
        p->ordrey = (int)p->y + 10;
    }
    p->a_bouger = 1;
}

int avverage_alt(struct personnages *p)
{
    float sum = 0;
    for (int i = 0; i < house2[0][0]; i++)
        for (int j = 0; j < house2[0][1]; j++)
            sum += altitude(i * max_x + j - p->house_id);
    return round(sum / ((float)house2[0][0] * (float)house2[0][1]));
}


int findnext(struct personnages *p, int av)
{
    int px = (int)p->x;
    int py = (int)p->y;
    char next = 0;
    for (int i = 0; i < house2[0][0]; i++)
    {
        for (int j = 0; j < house2[0][1]; j++)
        {
            if (next == 1 && altitude(i * max_x + j - p->house_id) != av)
                return i * max_x + j - p->house_id;
            else if (px + py * max_x == -p->house_id + i * max_x + j)
                next = 1;
        }    
    }
    return -p->house_id;
}

int imInHouse(struct personnages *p)
{
    int px = (int)p->x;
    int py = (int)p->y;
    for (int i = 1; i < house2[0][0]+1; i++)
    {
        for (int j = 0; j < house2[0][1]; j++)
        {
                if (px + py * max_x == -p->house_id + (i - 1) * max_x + j)
                {
                    return 1;
                }
    
        }
    }
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
    if (find_index_in_inventory( "herbe", p->items) != -1)
    {
        remove_from_inventory("herbe", 1, p->items, p->items_cnt);
        add_1_pixel((int)p->x + (int)p->y*max_x, he1);
        p->a_bouger += 1;
        return;
    }
    if (find_index_in_inventory("sable", p->items) != -1)
    {
        remove_from_inventory("sable", 1, p->items, p->items_cnt);
        add_1_pixel((int)p->x + (int)p->y*max_x, sa1);
        p->a_bouger += 1;
        return ;
    }
}

int find_extreme_altitude_house(struct personnages *p, int *lowgo, int *highgo)
{
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

char check_can_build(struct personnages *p, int coohouse)
{
    p = p; 
    int housex = coohouse % max_x;
    int housey = coohouse / max_x;

    for (int i = 1; i < house2[0][0]+1; i++)
    {
        for (int j = 0; j < house2[0][1]; j++)
        {
            if (0 > housex + j || housex + j >= max_x || 0 > housey + i - 1 || housey + i - 1 >= max_y)
                return 0;
            if (ground[housex + (i - 1 + housey) * max_x + j]->texture == ea1 || ground[housex + (i - 1 + housey) * max_x + j]->texture == ea2 || ground[housex + (i - 1 + housey) * max_x + j]->texture == ea3)
                return 0;
            /*if (house2[i][j] == 1)
            {
                if (building_id[coo] != -1)
                    return 0;
            }*/
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

int find_something(int xbiom, int ybiom, char skin[4])
{
    int offsets[9][2] = {
        {-1,-1}, 
        {-1, 0},
        {-1, 1},
        {0, -1},
        {0,  0}, 
        {0,  1},
        {1, -1},
        {1,  0},
        {1,  1}
    };
    for (int n = 0; n < 9; n++)
    {
        int nx = xbiom + offsets[n][0];
        int ny = ybiom + offsets[n][1];
        if (nx >= max_x_biom || ny >= max_y_biom || nx < 0 || ny < 0)
            continue;
        for (int j = 0; j < list_bioms[nx + ny * max_x_biom].size; j++)
        {
            if (strcmp(list.data[list_bioms[nx + ny * max_x_biom].data[j]].skin, skin) == 0)
                return list_bioms[nx + ny * max_x_biom].data[j];
        }
    }
    return -1;
}

int find_something_closer_than(struct personnages *p, char skin[4], float maxdist)
{
    int xbiom = (int)(p->x*0.04);
    int ybiom = (int)(p->y*0.04);
    int offsets[9][2] = {
        {-1,-1}, 
        {-1, 0},
        {-1, 1},
        {0, -1},
        {0,  0}, 
        {0,  1},
        {1, -1},
        {1,  0}, 
        {1,  1}
    };

    for (int n = 0; n < 9; n++)
    {
        int nx = xbiom + offsets[n][0];
        int ny = ybiom + offsets[n][1];
        if (nx >= max_x_biom || ny >= max_y_biom || nx < 0 || ny < 0)
            continue;
        for (int j = 0; j < list_bioms[nx + ny * max_x_biom].size; j++)
        {
            struct personnages *pp = &list.data[list_bioms[nx + ny * max_x_biom].data[j]];
            if (strcmp(pp->skin, skin) == 0 && (pp->x - p->x)*(pp->x - p->x) + (pp->y - p->y) * (pp->y - p->y) < maxdist)
                return list_bioms[nx + ny * max_x_biom].data[j];
        }
    }
    return -1;
}

int find_something_closest(struct personnages *p, char skin[4])
{
    int xbiom = (int)(p->x*0.04);
    int ybiom = (int)(p->y*0.04);
    int offsets[9][2] = {
        {-1,-1}, 
        {-1, 0},
        {-1, 1},
        {0, -1},
        {0,  0}, 
        {0,  1},
        {1, -1},
        {1,  0}, 
        {1,  1}
    };

    int ret = -1;
    float mindist = 9999999;

    for (int n = 0; n < 9; n++)
    {
        int nx = xbiom + offsets[n][0];
        int ny = ybiom + offsets[n][1];
        if (nx >= max_x_biom || ny >= max_y_biom || nx < 0 || ny < 0)
            continue;
        for (int j = 0; j < list_bioms[nx + ny * max_x_biom].size; j++)
        {
            struct personnages *pp = &list.data[list_bioms[nx + ny * max_x_biom].data[j]];
            if (strcmp(pp->skin, skin) == 0)
            {
                float dist = (pp->x - p->x)*(pp->x - p->x) + (pp->y - p->y) * (pp->y - p->y);
                if (dist < mindist)
                {
                    ret = list_bioms[nx + ny * max_x_biom].data[j];
                    mindist = dist;
                }
            }

        }
    }
    return ret;
}

void ia_man(struct personnages *p)
{
    if (p->faim < 0)
    {
        p->pv -= 1;
        p->a_bouger = 1;
    }
    if (p->speak_timer > 0)
    {
        p->speak_timer --;
        if (p->speak_timer == 0 && p->speak[0] != 0)
        {
            p->speak[0] = 0;
            p->a_bouger = 1;
        }
    }    
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
    int moix = (int)p->x;
    int moiy = (int)p->y;
    int whereiam = moix + moiy * max_x;
    if (how_much_food(p) <= 1000)
    {

        int a_tree = -1;
        float mindist = 99999;
        for (int i = 0; i <= list.maxid; i++)
        {
            if (list.data[i].is_active == 0)
                continue;
            if (strcmp(list.data[i].skin, "01") == 0 && (list.data[i].x - p->x)*(list.data[i].x - p->x) + (list.data[i].y - p->y) * (list.data[i].y - p->y) < 4 && find_index_in_inventory("fruit", list.data[i].items) != -1)
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
                if (strcmp(list.data[i].skin, "01") == 0 && (list.data[i].x - p->x)*(list.data[i].x - p->x) + (list.data[i].y - p->y) * (list.data[i].y - p->y) < mindist && find_index_in_inventory("fruit", list.data[i].items) != -1)
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
            if (can_add("wooden-board", 1, p->items, p->items_cnt) == 0)
                put_ground(p);
            else
            {
                append_in_inventory("fruit",1, p->items, p->items_cnt);
                remove_from_inventory("fruit", 1, list.data[a_tree].items, list.data[a_tree].items_cnt);
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
            if ((int)p->ordrex == moix && (int)p->ordrey == moiy)
            {
                p->x = p->ordrex;
                p->y = p->ordrey;
                p->ordrex = -1;
                p->a_bouger = 1;
                p->chemin_is_set = 0;
            }
            else if (p->chemin_is_set == 1 || findpath(p) == 1)
            {
                int dst = (int)p->ordrey * max_x + (int)p->ordrex;                
                while (p->chemin[dst].prev != whereiam && p->chemin[dst].prev != -1)
                    dst = p->chemin[dst].prev;
                
                if (whereiam + 1 == dst)
                {
                    p->moved_x += p->vitesse_dep;
                    p->angle = 'f';
                }
                else if (whereiam - 1 == dst)
                {
                    p->moved_x -= p->vitesse_dep;
                    p->angle = 'b';
                }
                else if (whereiam - max_x == dst)
                {
                    p->moved_y -= p->vitesse_dep;
                    p->angle = 'd';
                }
                else if (whereiam + max_x == dst)
                {
                    p->moved_y += p->vitesse_dep;
                    p->angle = 'h';
                }
                else if (whereiam + 1 + max_x == dst)
                {
                    p->moved_y += p->vitesse_dep*0.707;
                    p->angle = 'g';
                    p->moved_x += p->vitesse_dep*0.707;
                }
                else if (whereiam + 1 - max_x == dst)
                {
                    p->moved_y -= p->vitesse_dep*0.707;
                    p->angle = 'e';
                    p->moved_x += p->vitesse_dep*0.707;
                }
                else if (whereiam - 1 + max_x == dst)
                {
                    p->moved_y += p->vitesse_dep*0.707;
                    p->angle = 'a';
                    p->moved_x -= p->vitesse_dep*0.707;
                }
                else if (whereiam -1 - max_x == dst)
                {
                    p->moved_x -= p->vitesse_dep*0.707;
                    p->angle = 'c';
                    p->moved_y -= p->vitesse_dep*0.707;
                }
                else if  (p->chemin[dst].prev == -1)
                {
                    /*while (p->chemin[dst2].prev != whereiam && p->chemin[dst2].prev != -1)
                    {
                        printf ("%d %d\n", dst2%max_x, dst2/max_x);
                        dst2 = p->chemin[dst2].prev;
                    }
                    printf ("1    %s %d %d %f %f %d %d \n", p->nom, moix, moiy, p->ordrex, p->ordrey, dst, whereiam);*/
                    p->chemin_is_set = 0;
                }
                else 
                    printf ("pathfinding not normal error\n");  
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
                    if (p->house_id == -1)
                    {
                        int a = moix - 50 + rand() % 100;
                        int b = moiy - 50 + rand() % 100;
                        if (check_can_build(p, a + b*max_x))
                            p->house_id = -(a + b*max_x);
                    }
                    else if (check_can_build(p, -(p->house_id)) == 0)
                        p->house_id = -1;
                    else
                    {
                        int highgo;
                        int lowgo;
                        find_extreme_altitude_house(p, &lowgo, &highgo);
                        if (altitude(highgo)!= altitude(lowgo))
                        {
                            int av = avverage_alt(p);
                            if (altitude(lowgo) == av && 10 == n_item(p->items))
                            {
                                if (imInHouse(p) || building_id[whereiam] != -1)
                                    move_somewhere_random(p);
                                else
                                    put_ground(p);
                            }
                            else if (altitude(highgo) == av && have_ground_in_inventory(p) == 0)
                            {
                                if (imInHouse(p) || building_id[whereiam] != -1)
                                    move_somewhere_random(p);
                                else
                                {
                                    if (ground[whereiam]->texture == he1 || ground[whereiam]->texture == he2 || ground[whereiam]->texture == he3 || ground[whereiam]->texture == he4 || ground[whereiam]->texture == he5)
                                    {
                                        append_in_inventory("herbe", 1, p->items, p->items_cnt);
                                        remove_1_pixel(whereiam);
                                        p->animation_2 = 2;
                                        p->animation = 0;
                                        p->a_bouger = 1;
                                    }
                                    else if (ground[whereiam]->texture == sa1 || ground[whereiam]->texture == sa2 || ground[whereiam]->texture == sa3)
                                    {
                                        append_in_inventory("sable", 1, p->items, p->items_cnt);
                                        remove_1_pixel(whereiam);
                                        p->animation_2 = 2;
                                        p->animation = 0;
                                        p->a_bouger = 1;
                                    }
                                    else
                                        move_somewhere_random(p);
                                }
                            }
                            else if (imInHouse(p) == 1 && altitude(whereiam) > av && 10 > n_item(p->items))
                            {
                                if (ground[whereiam]->texture == he1 || ground[whereiam]->texture == he2 || ground[whereiam]->texture == he3 || ground[whereiam]->texture == he4 || ground[whereiam]->texture == he5)
                                {
                                    append_in_inventory("herbe", 1, p->items, p->items_cnt);
                                    remove_1_pixel(whereiam);
                                    p->animation_2 = 2;
                                    p->animation = 0;
                                    p->a_bouger = 1;
                                }
                                else if (ground[whereiam]->texture == sa1 || ground[whereiam]->texture == sa2 || ground[whereiam]->texture == sa3)
                                {
                                    append_in_inventory("sable", 1, p->items, p->items_cnt);
                                    remove_1_pixel(whereiam);
                                    p->animation_2 = 2;
                                    p->animation = 0;
                                    p->a_bouger = 1;
                                }
                                else if (ground[whereiam]->texture == ne1 || ground[whereiam]->texture == ne2 || ground[whereiam]->texture == ne3)
                                {    
                                    remove_1_pixel(whereiam);
                                    add_1_pixel(moix + (moiy)*max_x,ea1);
                                }
                            }
                            else if (imInHouse(p) == 1 && have_ground_in_inventory(p) && av > altitude(whereiam) )
                                put_ground(p);
                            else
                            {
                                int wheretogo = findnext(p, av);
                                int togox = wheretogo%max_x;
                                int togoy = wheretogo/max_x;
                                p->ordrex = togox+0.5;
                                p->ordrey = togoy+0.5;
                            }
                        }
                        else
                        {
                            if (count_item("wooden-board", p->items, p->items_cnt) >= 9) //si j'ai dans mon inventaire de quoi placer des fondations
                            {
                                int coo = find_where_to_build(p);
                                int bx = coo%max_x;
                                int by = coo/max_x;
                                if ((p->x - bx)*(p->x - bx) + (p->y - by) * (p->y - by) < 4)
                                {
                                    add_wood_pillar_or_wood_house(bx, by);
                                    remove_from_inventory("wooden-board", 9, p->items, p->items_cnt);
                                    p->a_bouger = 1;
                                }
                                else if (can_walk_near_this_place(p, coo) != 1)
                                    printf ("can't aproach house");
                            }
                            else
                            {
                                int a_tree = find_something_closest(p, "01\0\0");
                                if (a_tree != -1)
                                {
                                    if ((list.data[a_tree].x - p->x)*(list.data[a_tree].x - p->x) + (list.data[a_tree].y - p->y) * (list.data[a_tree].y - p->y) < 4)
                                    {
                                        if (n_item(p->items) > 9)
                                        {
                                            if (have_ground_in_inventory(p))
                                                put_ground(p);
                                            else
                                                eat(p);
                                        }
                                        else
                                        {
                                            if (find_index_in_inventory("fruit", list.data[a_tree].items) != -1)
                                            {
                                                remove_from_inventory("fruit", 1, list.data[a_tree].items, list.data[a_tree].items_cnt);
                                                append_in_inventory("fruit", 1, p->items, p->items_cnt);
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
                                                else if (can_add("wooden-board", 1, p->items, p->items_cnt) == 1)
                                                {
                                                    list.data[a_tree].pv -= 1;
                                                    append_in_inventory("wooden-board",1, p->items, p->items_cnt);
                                                }
                                            }
                                        }
                                    }
                                    else
                                    {
                                        p->ordrex = list.data[a_tree].x+1;
                                        p->ordrey = list.data[a_tree].y;
                                        p->is_active = 1;
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
    if (p->echange_player != -1)
    {
        sprintf(p->speak, "votre proposition est ininteressante");
        sprintf(p->items[10], ".");
        sprintf(p->items[11], ".");
        p->speak_timer = 1350;
        p->a_bouger = 1;
    }
}
