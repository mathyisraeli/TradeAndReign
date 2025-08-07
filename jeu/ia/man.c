#include "man.h"

typedef struct {
    int dx;
    int dy;
} Direction;

Direction directions[] = {
    {1, 0},   // ➡ droite
    {-1, 0},  // ⬅ gauche
    {0, -1},  // ⬆ haut
    {0, 1},   // ⬇ bas
    {1, -1},  // ↗ haut-droite
    {-1, -1}, // ↖ haut-gauche
    {1, 1},   // ↘ bas-droite
    {-1, 1}   // ↙ bas-gauche
};


void ia_man(struct personnages *p)
{
    if (p->faim < 0)
        sprintf (ordre + strlen(ordre), "%d 00 -1 ", p->id);
    if (p->animation_2 == 1)
	{
		if (p->animation >= 3)
			sprintf (ordre + strlen(ordre), "%d 22 0 %d 21 0 ", p->id, p->id);
		else
			sprintf(ordre + strlen(ordre), "%d 21 %d ",p->id, p->animation +1 );
        return;
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
                sprintf (ordre + strlen(ordre), "%d 01 +%f %d 05 d %d 21 %d ", p->id, p->vitesse_dep, p->id, p->id, (p->animation+1)%5);
            else if (src - 1 == dst)
                sprintf (ordre + strlen(ordre), "%d 01 -%f %d 05 h %d 21 %d ", p->id, p->vitesse_dep, p->id, p->id, (p->animation+1)%5); 
            else if (src - max_x == dst)
                sprintf (ordre + strlen(ordre), "%d 02 -%f %d 05 b %d 21 %d ", p->id, p->vitesse_dep, p->id, p->id, (p->animation+1)%5);
            else if (src + max_x == dst)
                sprintf (ordre + strlen(ordre), "%d 02 +%f %d 05 f %d 21 %d ", p->id, p->vitesse_dep, p->id, p->id, (p->animation+1)%5);
            else if (src + 1 + max_x == dst)
                sprintf (ordre + strlen(ordre), "%d 01 +%f %d 02 +%f %d 05 e %d 21 %d ", p->id, p->vitesse_dep*0.707, p->id,p->vitesse_dep*0.707, p->id, p->id, (p->animation+1)%5);
            else if (src + 1 - max_x == dst)
                sprintf (ordre + strlen(ordre), "%d 01 +%f %d 02 -%f %d 05 c %d 21 %d ", p->id, p->vitesse_dep*0.707, p->id,p->vitesse_dep*0.707, p->id, p->id, (p->animation+1)%5);
            else if (src - 1 + max_x == dst)
                sprintf (ordre + strlen(ordre), "%d 01 -%f %d 02 +%f %d 05 g %d 21 %d ", p->id, p->vitesse_dep*0.707, p->id,p->vitesse_dep*0.707, p->id, p->id, (p->animation+1)%5);
            else if (src -1 - max_x == dst)
                sprintf (ordre + strlen(ordre), "%d 01 -%f %d 02 -%f %d 05 a %d 21 %d ", p->id, p->vitesse_dep*0.707, p->id,p->vitesse_dep*0.707, p->id, p->id, (p->animation+1)%5);
            else
            {
                if (p->ordrex > p->x)
                    sprintf (ordre + strlen(ordre), "%d 01 +%f %d 05 b %d 21 %d ", p->id, p->vitesse_dep, p->id, p->id, (p->animation+1)%5);
                else if (p->ordrex < p->x)
                    sprintf (ordre + strlen(ordre), "%d 01 -%f %d 05 b %d 21 %d ", p->id, p->vitesse_dep, p->id, p->id, (p->animation+1)%5);
                if (p->ordrey > p->y)
                    sprintf (ordre + strlen(ordre), "%d 02 +%f %d 05 d %d 21 %d ", p->id, p->vitesse_dep, p->id, p->id, (p->animation+1)%5);
                else if (p->ordrey < p->y)
                    sprintf (ordre + strlen(ordre), "%d 02 -%f %d 05 e %d 21 %d ", p->id, p->vitesse_dep, p->id, p->id, (p->animation+1)%5);
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
                if (p->house_id == -1)
                {
                    for (struct building *parcour = list_building; parcour != NULL; parcour = parcour->next)
                    {
                        if (strcmp(parcour->skin, "141") == 0 && (parcour->x - p->x)*(parcour->x - p->x) + (parcour->y - p->y) * (parcour->y - p->y) < 400)
                        {
                            sprintf (ordre + strlen(ordre), "%d 32 -%d ",p->id, parcour->x + parcour->y * max_x);
                            break;
                        }
                    }
                }
                if (count_item(p->i_list, "wooden-board") >= 9) //si j'ai dans mon inventaire de quoi placer des fondations 
                {
                    int moix = (int)p->x;
                    int moiy = (int)p->y;
                    char cond = 0;
                    for (int d = 0; d < 8 && !cond; d++) 
                    {
                        int dx = directions[d].dx;
                        int dy = directions[d].dy;

                        int x1 = moix + dx;
                        int y1 = moiy + dy;
                        int x2 = moix + 2 * dx;
                        int y2 = moiy + 2 * dy;

                        // --- Cas 1 : voisin immédiat occupé
                        if (x1 >= 0 && x1 < max_x && y1 >= 0 && y1 < max_y) 
                        {
                            int idx1 = x1 + y1 * max_x;
                            if (building_id[idx1] != -1 && strcmp(find_building_by_id(building_id[idx1])->skin, "141") == 0)
                            {
                                // ➤ Si direction orthogonale : tester les deux diagonales autour
                                if (dx == 0 || dy == 0) 
                                {
                                    int cx1 = moix + dx + (dy == 0 ? 0 : 1);
                                    int cy1 = moiy + dy + (dx == 0 ? 0 : 1);
                                    int cx2 = moix + dx - (dy == 0 ? 0 : 1);
                                    int cy2 = moiy + dy - (dx == 0 ? 0 : 1);

                                    // Diagonale 1
                                    if (cx1 >= 0 && cx1 < max_x && cy1 >= 0 && cy1 < max_y && building_id[cx1 + cy1 * max_x] == -1)
                                    {
                                        sprintf(ordre + strlen(ordre), "%d 32 -%d ", p->id, cx1 + cy1 * max_x);
                                        add_wood_pillar_or_wood_house(cx1, cy1);
                                        sprintf (ordre + strlen(ordre), "%d 16 9 wooden-board ", p->id);
                                        cond = 1;
                                        break;
                                    }

                                    // Diagonale 2
                                    if (cx2 >= 0 && cx2 < max_x && cy2 >= 0 && cy2 < max_y && building_id[cx2 + cy2 * max_x] == -1)
                                    {
                                        sprintf(ordre + strlen(ordre), "%d 32 -%d ", p->id, cx2 + cy2 * max_x);
                                        add_wood_pillar_or_wood_house(cx2, cy2);
                                        sprintf (ordre + strlen(ordre), "%d 16 9 wooden-board ", p->id);
                                        cond = 1;
                                        break;
                                    }
                                }
                                // ➤ Si direction diagonale : tester les deux orthogonaux autour
                                else
                                {
                                    int sx = moix + dx;
                                    int sy = moiy;

                                    if (sx >= 0 && sx < max_x && sy >= 0 && sy < max_y && building_id[sx + sy * max_x] == -1)
                                    {
                                        sprintf(ordre + strlen(ordre), "%d 32 -%d ", p->id, sx + sy * max_x);
                                        add_wood_pillar_or_wood_house(sx, sy);
                                        sprintf (ordre + strlen(ordre), "%d 16 9 wooden-board ", p->id);
                                        cond = 1;
                                        break;
                                    }

                                    sx = moix;
                                    sy = moiy + dy;

                                    if (sx >= 0 && sx < max_x && sy >= 0 && sy < max_y && building_id[sx + sy * max_x] == -1)
                                    {
                                        sprintf(ordre + strlen(ordre), "%d 32 -%d ", p->id, sx + sy * max_x);
                                        add_wood_pillar_or_wood_house(sx, sy);
                                        sprintf (ordre + strlen(ordre), "%d 16 9 wooden-board ", p->id);
                                        cond = 1;
                                        break;
                                    }
                                }
                            }
                        }

                        // --- Cas 2 : deux cases plus loin pleine, celle entre vide
                        if (x2 >= 0 && x2 < max_x && y2 >= 0 && y2 < max_y && x1 >= 0 && x1 < max_x && y1 >= 0 && y1 < max_y)
                        {
                            int idx2 = x2 + y2 * max_x;
                            int idx1 = x1 + y1 * max_x;

                            if (building_id[idx2] != -1 && strcmp(find_building_by_id(building_id[idx2])->skin, "141") == 0 && building_id[idx1] == -1)
                            {
                                sprintf(ordre + strlen(ordre), "%d 32 -%d ", p->id, x1 + y1 * max_x);
                                add_wood_pillar_or_wood_house(x1, y1);
                                sprintf (ordre + strlen(ordre), "%d 16 9 wooden-board ", p->id);
                                cond = 1;
                                break;
                            }
                        }
                    }
                    if (cond == 0 && p->house_id < -1)
                    {
                        int bx = -p->house_id%max_x;
                        int by = -p->house_id/max_x;
                        int a = rand() % 4;
                        if (a == 0 && bx > 1 &&  building_id[bx - 1 + by * max_x] == -1 && building_id[bx - 2 + by * max_x] == -1)
                        {
                            sprintf (ordre + strlen(ordre), "%d 03 %f %d 04 %f ", p->id, bx -1+0.5, p->id, by+0.5);
                            cond = 1;
                        }
                        if (a == 1 && bx < max_x - 2 &&  building_id[bx + 1 + by * max_x] == -1 && building_id[bx + 2 + by * max_x] == -1)
                        {
                            sprintf (ordre + strlen(ordre), "%d 03 %f %d 04 %f ", p->id, bx +1+0.5, p->id, by+0.5);
                            cond = 1;
                        }
                        if (a == 2 && by > 1 &&  building_id[bx - max_x + by * max_x] == -1 && building_id[bx + (by-2) * max_x] == -1)
                        {
                            sprintf (ordre + strlen(ordre), "%d 03 %f %d 04 %f ", p->id, bx+0.5, p->id, by-1+0.5);
                            cond = 1;
                        }
                        if (a == 3 && by < max_y - 2 &&  building_id[bx + max_x + by * max_x] == -1 && building_id[bx + (2 + by) * max_x] == -1)
                        {
                            sprintf (ordre + strlen(ordre), "%d 03 %f %d 04 %f ", p->id, bx+0.5, p->id, by+1+0.5);
                            cond = 1;
                        }
                    }
                    else if (cond == 0 && moix > 0 && building_id[moix - 1 + moiy * max_x] == -1)
                    {
                        add_wood_pillar_or_wood_house(moix-1, moiy);
                        sprintf(ordre + strlen(ordre), "%d 32 -%d ", p->id, moix-1 + moiy * max_x);
                        sprintf (ordre + strlen(ordre), "%d 16 9 wooden-board ", p->id);

                        cond = 1;
                    }
                    else if (cond == 0 && moix < max_x - 1 && building_id[moix + 1 + moiy * max_x] == -1)
                    {
                        add_wood_pillar_or_wood_house(moix+1, moiy);
                        sprintf (ordre + strlen(ordre), "%d 16 9 wooden-board ", p->id);
                        sprintf(ordre + strlen(ordre), "%d 32 -%d ", p->id, moix+1 + moiy * max_x);
                        cond = 1;
                    }
                    else if (cond == 0 && moiy > 0 && building_id[moix - max_x + moiy * max_x] == -1)
                    {
                        add_wood_pillar_or_wood_house(moix, moiy-1);
                        sprintf (ordre + strlen(ordre), "%d 16 9 wooden-board ", p->id);
                        sprintf(ordre + strlen(ordre), "%d 32 -%d ", p->id, moix-max_x + moiy * max_x);
                        cond = 1;
                    }
                    else if (cond == 0 && moiy < max_y - 1 && building_id[moix + max_x + moiy * max_x] == -1)
                    {
                        add_wood_pillar_or_wood_house(moix, moiy+1);
                        sprintf (ordre + strlen(ordre), "%d 16 9 wooden-board ", p->id);
                        sprintf(ordre + strlen(ordre), "%d 32 -%d ", p->id, moix+max_x + moiy * max_x);
                        cond = 1;
                    }
                }
                else // got cut three
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
                        sprintf (ordre + strlen(ordre), "%d 22 1 %d 21 0 ", p->id, p->id);
                        if (a_tree->pv -  p->dom >= 4)
                            sprintf(ordre + strlen(ordre), "%d 00 -%d ", a_tree->id, p->dom);
                        else if (can_add("wooden-board", 1, p->i_list) == 1)
                            sprintf(ordre + strlen(ordre), "%d 00 -1 %d 16 +1 wooden-board ", a_tree->id, p->id);
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
    if (strcmp(p->echange_player, "none") != 0)
    {
        sprintf (ordre + strlen(ordre), "%d 20 votre proposition est ininteressante\037 %d 17 none none 0 none 0 ", p->id, p->id);
        p->speak_timer = 1350;
    }
    if (p->faim == 50)
    {
        struct linked_item *a = exist_in_linked_item(p->i_list, "fruit");
        if (a != NULL)
            use(a, p);
        else
        {
            sprintf (ordre + strlen(ordre), "%d 20 [J ai faim et je n ai rien a manger] ", p->id);
            p->speak_timer = 1350;
        }
    }
    if (p->speak_timer > 0)
        p->speak_timer --;
    else if (p->speak_timer <= 0 && p->speak[0] != 0)
        sprintf (ordre + strlen(ordre), "%d 20 \037 ", p->id);
}
