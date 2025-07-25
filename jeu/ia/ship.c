#include "ship.h"

void ia_ship(struct building *ship)
{
    int cnt = 0;
    ship->counter += 1;
    if (ship->counter >= 9)
    {
        ship->counter = 0;
        if (ship->state == '1')
        {
            if (ship->angle == 'a')
            {
                if (ship->y < max_y - 5 && 
                (ground_texture[(ship->y + 5)*max_x + ship->x] == img->t->ea1 || ground_texture[(ship->y + 5)*max_x + ship->x] == img->t->ea2 || ground_texture[(ship->y + 5)*max_x + ship->x] == img->t->ea3) &&
                (ground_texture[(ship->y + 4)*max_x + ship->x + 1] == img->t->ea1 || ground_texture[(ship->y + 4)*max_x + ship->x + 1] == img->t->ea2 || ground_texture[(ship->y + 4)*max_x + ship->x + 1] == img->t->ea3) &&
                (ground_texture[(ship->y + 3)*max_x + ship->x + 2] == img->t->ea1 || ground_texture[(ship->y + 3)*max_x + ship->x + 2] == img->t->ea2 || ground_texture[(ship->y + 3)*max_x + ship->x + 2] == img->t->ea3) &&
                (ground_texture[(ship->y + 4)*max_x + ship->x - 1] == img->t->ea1 || ground_texture[(ship->y + 4)*max_x + ship->x - 1] == img->t->ea2 || ground_texture[(ship->y + 4)*max_x + ship->x - 1] == img->t->ea3) &&
                (ground_texture[(ship->y + 3)*max_x + ship->x - 2] == img->t->ea1 || ground_texture[(ship->y + 3)*max_x + ship->x - 2] == img->t->ea2 || ground_texture[(ship->y + 3)*max_x + ship->x - 2] == img->t->ea3) &&
                building_id[(ship->y + 5)*max_x + ship->x] == -1 && building_id[(ship->y + 4)*max_x + ship->x - 1] == -1 && building_id[(ship->y + 3)*max_x + ship->x - 2] == -1 && building_id[(ship->y + 4)*max_x + ship->x + 1] == -1 && building_id[(ship->y + 3)*max_x + ship->x + 2] == -1)
                { 
                    for (struct linked_list *parcour = list; parcour != NULL; parcour = parcour->next)
                        if (building_id[(int)parcour->p->x + (int)parcour->p->y*max_x] == ship->id)
                        {
                            sprintf (ordre + strlen(ordre), "%d 02 +1 ", parcour->p->id);
                            cnt += 1;
                        }
                    if (cnt == 0)
                        sprintf (ordre + strlen(ordre), "%d 04 0 ", ship->id);
                    else
                        sprintf (ordre + strlen(ordre), "%d 02 +1 ", ship->id);
                }
                
            }
            else if (ship->angle == 'b')
            {
                if (ship->y > 4 && 
                (ground_texture[(ship->y - 5)*max_x + ship->x] == img->t->ea1 || ground_texture[(ship->y - 5)*max_x + ship->x] == img->t->ea2 || ground_texture[(ship->y - 5)*max_x + ship->x] == img->t->ea3) &&
                (ground_texture[(ship->y - 4)*max_x + ship->x + 1] == img->t->ea1 || ground_texture[(ship->y - 4)*max_x + ship->x + 1] == img->t->ea2 || ground_texture[(ship->y - 4)*max_x + ship->x + 1] == img->t->ea3) &&
                (ground_texture[(ship->y - 3)*max_x + ship->x + 2] == img->t->ea1 || ground_texture[(ship->y - 3)*max_x + ship->x + 2] == img->t->ea2 || ground_texture[(ship->y - 3)*max_x + ship->x + 2] == img->t->ea3) &&
                (ground_texture[(ship->y - 4)*max_x + ship->x - 1] == img->t->ea1 || ground_texture[(ship->y - 4)*max_x + ship->x - 1] == img->t->ea2 || ground_texture[(ship->y - 4)*max_x + ship->x - 1] == img->t->ea3) &&
                (ground_texture[(ship->y - 3)*max_x + ship->x - 2] == img->t->ea1 || ground_texture[(ship->y - 3)*max_x + ship->x - 2] == img->t->ea2 || ground_texture[(ship->y - 3)*max_x + ship->x - 2] == img->t->ea3) &&
                building_id[(ship->y - 5)*max_x + ship->x] == -1 && building_id[(ship->y - 4)*max_x + ship->x - 1] == -1 && building_id[(ship->y - 3)*max_x + ship->x - 2] == -1 && building_id[(ship->y - 4)*max_x + ship->x + 1] == -1 && building_id[(ship->y - 3)*max_x + ship->x + 2] == -1)
                { 
                    
                    for (struct linked_list *parcour = list; parcour != NULL; parcour = parcour->next)
                        if (building_id[(int)parcour->p->x + (int)parcour->p->y*max_x] == ship->id)
                        {
                            cnt += 1;
                            sprintf (ordre + strlen(ordre), "%d 02 -1 ", parcour->p->id);
                        }
                    if (cnt == 0)
                        sprintf (ordre + strlen(ordre), "%d 04 0 ", ship->id);
                    else
                        sprintf (ordre + strlen(ordre), "%d 02 -1 ", ship->id);
                }

            }
            else if (ship->angle == 'k')
            {
                if (ship->x > 4 && 
                (ground_texture[(ship->y)*max_x + ship->x - 5] == img->t->ea1 || ground_texture[(ship->y)*max_x + ship->x - 5] == img->t->ea2 || ground_texture[(ship->y)*max_x + ship->x - 5] == img->t->ea3) &&
                (ground_texture[(ship->y + 1)*max_x + ship->x - 4] == img->t->ea1 || ground_texture[(ship->y + 1)*max_x + ship->x - 4] == img->t->ea2 || ground_texture[(ship->y + 1)*max_x + ship->x - 4] == img->t->ea3) &&
                (ground_texture[(ship->y + 2)*max_x + ship->x - 3] == img->t->ea1 || ground_texture[(ship->y + 2)*max_x + ship->x - 3] == img->t->ea2 || ground_texture[(ship->y + 2)*max_x + ship->x - 3] == img->t->ea3) &&
                (ground_texture[(ship->y - 1)*max_x + ship->x - 4] == img->t->ea1 || ground_texture[(ship->y - 1)*max_x + ship->x - 4] == img->t->ea2 || ground_texture[(ship->y - 1)*max_x + ship->x - 4] == img->t->ea3) &&
                (ground_texture[(ship->y - 2)*max_x + ship->x - 3] == img->t->ea1 || ground_texture[(ship->y - 2)*max_x + ship->x - 3] == img->t->ea2 || ground_texture[(ship->y - 2)*max_x + ship->x - 3] == img->t->ea3) &&
                building_id[(ship->y )*max_x + ship->x - 5] == -1 && building_id[(ship->y + 1)*max_x + ship->x - 4] == -1 && building_id[(ship->y + 2)*max_x + ship->x - 3] == -1 && building_id[(ship->y - 1)*max_x + ship->x - 4] == -1 && building_id[(ship->y - 2)*max_x + ship->x - 3] == -1)
                { 
                    for (struct linked_list *parcour = list; parcour != NULL; parcour = parcour->next)
                        if (building_id[(int)parcour->p->x + (int)parcour->p->y*max_x] == ship->id)
                        {
                            sprintf (ordre + strlen(ordre), "%d 01 -1 ", parcour->p->id);
                            cnt += 1;
                        }
                    if (cnt == 0)
                        sprintf (ordre + strlen(ordre), "%d 04 0 ", ship->id);
                    else
                        sprintf (ordre + strlen(ordre), "%d 01 -1 ", ship->id);
                }
            }
            else
            {
                if (ship->x < max_x-5 &&
                (ground_texture[(ship->y)*max_x + ship->x + 5] == img->t->ea1 || ground_texture[(ship->y)*max_x + ship->x + 5] == img->t->ea2 || ground_texture[(ship->y)*max_x + ship->x + 5] == img->t->ea3) &&
                (ground_texture[(ship->y + 1)*max_x + ship->x + 4] == img->t->ea1 || ground_texture[(ship->y + 1)*max_x + ship->x + 4] == img->t->ea2 || ground_texture[(ship->y + 1)*max_x + ship->x + 4] == img->t->ea3) &&
                (ground_texture[(ship->y + 2)*max_x + ship->x + 3] == img->t->ea1 || ground_texture[(ship->y + 2)*max_x + ship->x + 3] == img->t->ea2 || ground_texture[(ship->y + 2)*max_x + ship->x + 3] == img->t->ea3) &&
                (ground_texture[(ship->y - 1)*max_x + ship->x + 4] == img->t->ea1 || ground_texture[(ship->y - 1)*max_x + ship->x + 4] == img->t->ea2 || ground_texture[(ship->y - 1)*max_x + ship->x + 4] == img->t->ea3) &&
                (ground_texture[(ship->y - 2)*max_x + ship->x + 3] == img->t->ea1 || ground_texture[(ship->y - 2)*max_x + ship->x + 3] == img->t->ea2 || ground_texture[(ship->y - 2)*max_x + ship->x + 3] == img->t->ea3) &&
                building_id[(ship->y )*max_x + ship->x + 5] == -1 && building_id[(ship->y + 1)*max_x + ship->x + 4] == -1 && building_id[(ship->y + 2)*max_x + ship->x + 3] == -1 && building_id[(ship->y - 1)*max_x + ship->x + 4] == -1 && building_id[(ship->y - 2)*max_x + ship->x + 3] == -1) 
                {    
                    for (struct linked_list *parcour = list; parcour != NULL; parcour = parcour->next)
                        if (building_id[(int)parcour->p->x + (int)parcour->p->y*max_x] == ship->id)
                        {
                            sprintf (ordre + strlen(ordre), "%d 01 +1 ", parcour->p->id);
                            cnt += 1;
                        }
                    if (cnt == 0)
                        sprintf (ordre + strlen(ordre), "%d 04 0 ", ship->id);
                    else
                        sprintf (ordre + strlen(ordre), "%d 01 +1 ", ship->id);
                }
            }
        }
        else if (ship->state == '2')
        {
            if (ship->angle == 'a')
            {
                sprintf (ordre + strlen(ordre), "%d 03 k %d 04 0 ", ship->id,  ship->id);  //ggauche
                for (struct linked_list *p = list; p != NULL; p = p->next)
                {
                    if ((int)p->p->x == ship->x && (int)p->p->y == ship->y + 4)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-4, p->p->id,ship->y);
                    
                    else if ((int)p->p->x == ship->x-1 && (int)p->p->y == ship->y + 3)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-3, p->p->id,ship->y-1);
                    else if ((int)p->p->x == ship->x && (int)p->p->y == ship->y + 3)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-3, p->p->id,ship->y);
                    else if ((int)p->p->x == ship->x+1 && (int)p->p->y == ship->y + 3)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-3, p->p->id,ship->y+1);

                    else if ((int)p->p->x == ship->x-2 && (int)p->p->y == ship->y + 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-2, p->p->id,ship->y-2);
                    else if ((int)p->p->x == ship->x-1 && (int)p->p->y == ship->y + 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-2, p->p->id,ship->y-1);
                    else if ((int)p->p->x == ship->x && (int)p->p->y == ship->y + 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-2, p->p->id,ship->y);
                    else if ((int)p->p->x == ship->x+1 && (int)p->p->y == ship->y + 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-2, p->p->id,ship->y+1);
                    else if ((int)p->p->x == ship->x+2 && (int)p->p->y == ship->y + 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-2, p->p->id,ship->y+2);

                    else if ((int)p->p->x == ship->x-2 && (int)p->p->y == ship->y + 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-1, p->p->id,ship->y-2);
                    else if ((int)p->p->x == ship->x-1 && (int)p->p->y == ship->y + 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-1, p->p->id,ship->y-1);
                    else if ((int)p->p->x == ship->x && (int)p->p->y == ship->y + 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-1, p->p->id,ship->y);
                    else if ((int)p->p->x == ship->x+1 && (int)p->p->y == ship->y + 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-1, p->p->id,ship->y+1);
                    else if ((int)p->p->x == ship->x+2 && (int)p->p->y == ship->y + 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-1, p->p->id,ship->y+2);

                    else if ((int)p->p->x == ship->x-2 && (int)p->p->y == ship->y)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x, p->p->id,ship->y-2);
                    else if ((int)p->p->x == ship->x-1 && (int)p->p->y == ship->y)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x, p->p->id,ship->y-1);
                    else if ((int)p->p->x == ship->x && (int)p->p->y == ship->y)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x, p->p->id,ship->y);
                    else if ((int)p->p->x == ship->x+1 && (int)p->p->y == ship->y)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x, p->p->id,ship->y+1);
                    else if ((int)p->p->x == ship->x+2 && (int)p->p->y == ship->y)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x, p->p->id,ship->y+2);

                    else if ((int)p->p->x == ship->x-2 && (int)p->p->y == ship->y - 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+1, p->p->id,ship->y-2);
                    else if ((int)p->p->x == ship->x-1 && (int)p->p->y == ship->y - 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+1, p->p->id,ship->y-1);
                    else if ((int)p->p->x == ship->x && (int)p->p->y == ship->y - 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+1, p->p->id,ship->y);
                    else if ((int)p->p->x == ship->x+1 && (int)p->p->y == ship->y - 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+1, p->p->id,ship->y+1);
                    else if ((int)p->p->x == ship->x+2 && (int)p->p->y == ship->y - 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+1, p->p->id,ship->y+2);

                    else if ((int)p->p->x == ship->x-2 && (int)p->p->y == ship->y - 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+2, p->p->id,ship->y-2);
                    else if ((int)p->p->x == ship->x-1 && (int)p->p->y == ship->y - 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+2, p->p->id,ship->y-1);
                    else if ((int)p->p->x == ship->x && (int)p->p->y == ship->y - 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+2, p->p->id,ship->y);
                    else if ((int)p->p->x == ship->x+1 && (int)p->p->y == ship->y - 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+2, p->p->id,ship->y+1);
                    else if ((int)p->p->x == ship->x+2 && (int)p->p->y == ship->y - 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+2, p->p->id,ship->y+2);

                    else if ((int)p->p->x == ship->x-2 && (int)p->p->y == ship->y - 3)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+3, p->p->id,ship->y-2);
                    else if ((int)p->p->x == ship->x-1 && (int)p->p->y == ship->y - 3)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+3, p->p->id,ship->y-1);
                    else if ((int)p->p->x == ship->x && (int)p->p->y == ship->y - 3)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+3, p->p->id,ship->y);
                    else if ((int)p->p->x == ship->x+1 && (int)p->p->y == ship->y - 3)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+3, p->p->id,ship->y+1);
                    else if ((int)p->p->x == ship->x+2 && (int)p->p->y == ship->y - 3)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+3, p->p->id,ship->y+2);

                    else if ((int)p->p->x == ship->x-1 && (int)p->p->y == ship->y - 4)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+4, p->p->id,ship->y-1);
                    else if ((int)p->p->x == ship->x && (int)p->p->y == ship->y - 4)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+4, p->p->id,ship->y);
                    else if ((int)p->p->x == ship->x+1 && (int)p->p->y == ship->y - 4)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+4, p->p->id,ship->y+1);
                }
            }
            else if (ship->angle == 'b')
            {
                sprintf (ordre + strlen(ordre), "%d 03 e %d 04 0 ", ship->id, ship->id);
                for (struct linked_list *p = list; p != NULL; p = p->next)
                {
                    if ((int)p->p->x == ship->x && (int)p->p->y == ship->y - 4)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+4, p->p->id,ship->y);
                    
                    else if ((int)p->p->x == ship->x+1 && (int)p->p->y == ship->y - 3)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+3, p->p->id,ship->y+1);
                    else if ((int)p->p->x == ship->x && (int)p->p->y == ship->y - 3)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+3, p->p->id,ship->y);
                    else if ((int)p->p->x == ship->x-1 && (int)p->p->y == ship->y - 3)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+3, p->p->id,ship->y-1);

                    else if ((int)p->p->x == ship->x+2 && (int)p->p->y == ship->y - 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+2, p->p->id,ship->y+2);
                    else if ((int)p->p->x == ship->x+1 && (int)p->p->y == ship->y - 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+2, p->p->id,ship->y+1);
                    else if ((int)p->p->x == ship->x && (int)p->p->y == ship->y - 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+2, p->p->id,ship->y);
                    else if ((int)p->p->x == ship->x-1 && (int)p->p->y == ship->y - 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+2, p->p->id,ship->y-1);
                    else if ((int)p->p->x == ship->x-2 && (int)p->p->y == ship->y - 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+2, p->p->id,ship->y-2);

                    else if ((int)p->p->x == ship->x+2 && (int)p->p->y == ship->y - 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+1, p->p->id,ship->y+2);
                    else if ((int)p->p->x == ship->x+1 && (int)p->p->y == ship->y - 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+1, p->p->id,ship->y+1);
                    else if ((int)p->p->x == ship->x && (int)p->p->y == ship->y - 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+1, p->p->id,ship->y);
                    else if ((int)p->p->x == ship->x-1 && (int)p->p->y == ship->y - 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+1, p->p->id,ship->y-1);
                    else if ((int)p->p->x == ship->x-2 && (int)p->p->y == ship->y - 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+1, p->p->id,ship->y-2);

                    else if ((int)p->p->x == ship->x+2 && (int)p->p->y == ship->y)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x, p->p->id,ship->y+2);
                    else if ((int)p->p->x == ship->x+1 && (int)p->p->y == ship->y)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x, p->p->id,ship->y+1);
                    else if ((int)p->p->x == ship->x && (int)p->p->y == ship->y)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x, p->p->id,ship->y);
                    else if ((int)p->p->x == ship->x-1 && (int)p->p->y == ship->y)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x, p->p->id,ship->y-1);
                    else if ((int)p->p->x == ship->x-2 && (int)p->p->y == ship->y)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x, p->p->id,ship->y-2);

                    else if ((int)p->p->x == ship->x+2 && (int)p->p->y == ship->y + 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-1, p->p->id,ship->y+2);
                    else if ((int)p->p->x == ship->x+1 && (int)p->p->y == ship->y + 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-1, p->p->id,ship->y+1);
                    else if ((int)p->p->x == ship->x && (int)p->p->y == ship->y + 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-1, p->p->id,ship->y);
                    else if ((int)p->p->x == ship->x-1 && (int)p->p->y == ship->y + 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-1, p->p->id,ship->y-1);
                    else if ((int)p->p->x == ship->x-2 && (int)p->p->y == ship->y + 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-1, p->p->id,ship->y-2);

                    else if ((int)p->p->x == ship->x+2 && (int)p->p->y == ship->y + 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-2, p->p->id,ship->y+2);
                    else if ((int)p->p->x == ship->x+1 && (int)p->p->y == ship->y + 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-2, p->p->id,ship->y+1);
                    else if ((int)p->p->x == ship->x && (int)p->p->y == ship->y + 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-2, p->p->id,ship->y);
                    else if ((int)p->p->x == ship->x-1 && (int)p->p->y == ship->y + 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-2, p->p->id,ship->y-1);
                    else if ((int)p->p->x == ship->x-2 && (int)p->p->y == ship->y + 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-2, p->p->id,ship->y-2);

                    else if ((int)p->p->x == ship->x+2 && (int)p->p->y == ship->y + 3)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-3, p->p->id,ship->y+2);
                    else if ((int)p->p->x == ship->x+1 && (int)p->p->y == ship->y + 3)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-3, p->p->id,ship->y+1);
                    else if ((int)p->p->x == ship->x && (int)p->p->y == ship->y + 3)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-3, p->p->id,ship->y);
                    else if ((int)p->p->x == ship->x-1 && (int)p->p->y == ship->y + 3)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-3, p->p->id,ship->y-1);
                    else if ((int)p->p->x == ship->x-2 && (int)p->p->y == ship->y + 3)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-3, p->p->id,ship->y-2);

                    else if ((int)p->p->x == ship->x+1 && (int)p->p->y == ship->y + 4)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-4, p->p->id,ship->y+1);
                    else if ((int)p->p->x == ship->x && (int)p->p->y == ship->y + 4)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-4, p->p->id,ship->y);
                    else if ((int)p->p->x == ship->x-1 && (int)p->p->y == ship->y + 4)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-4, p->p->id,ship->y-1);
                }
            }
            else if (ship->angle == 'e')
            {
                sprintf (ordre + strlen(ordre), "%d 03 a %d 04 0 ", ship->id, ship->id);
                for (struct linked_list *p = list; p != NULL; p = p->next)
                {
                    if ((int)p->p->x == ship->x+4 && (int)p->p->y == ship->y)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x, p->p->id,ship->y+4);
                    
                    else if ((int)p->p->x == ship->x+3 && (int)p->p->y == ship->y - 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+1, p->p->id,ship->y+3);
                    else if ((int)p->p->x == ship->x+3 && (int)p->p->y == ship->y)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x, p->p->id,ship->y+3);
                    else if ((int)p->p->x == ship->x+3 && (int)p->p->y == ship->y + 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-1, p->p->id,ship->y+3);

                    else if ((int)p->p->x == ship->x+2 && (int)p->p->y == ship->y - 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+2, p->p->id,ship->y+2);
                    else if ((int)p->p->x == ship->x+2 && (int)p->p->y == ship->y - 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+1, p->p->id,ship->y+2);
                    else if ((int)p->p->x == ship->x+2 && (int)p->p->y == ship->y )
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x, p->p->id,ship->y+2);
                    else if ((int)p->p->x == ship->x+2 && (int)p->p->y == ship->y + 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-1, p->p->id,ship->y+2);
                    else if ((int)p->p->x == ship->x+2 && (int)p->p->y == ship->y + 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-2, p->p->id,ship->y+2);

                    else if ((int)p->p->x == ship->x+1 && (int)p->p->y == ship->y - 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+2, p->p->id,ship->y+1);
                    else if ((int)p->p->x == ship->x+1 && (int)p->p->y == ship->y - 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+1, p->p->id,ship->y+1);
                    else if ((int)p->p->x == ship->x+1 && (int)p->p->y == ship->y)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x, p->p->id,ship->y+1);
                    else if ((int)p->p->x == ship->x+1 && (int)p->p->y == ship->y + 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-1, p->p->id,ship->y+1);
                    else if ((int)p->p->x == ship->x+1 && (int)p->p->y == ship->y + 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-2, p->p->id,ship->y+1);

                    else if ((int)p->p->x == ship->x && (int)p->p->y == ship->y-2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+2, p->p->id,ship->y);
                    else if ((int)p->p->x == ship->x && (int)p->p->y == ship->y-1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+1, p->p->id,ship->y);
                    else if ((int)p->p->x == ship->x && (int)p->p->y == ship->y)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x, p->p->id,ship->y);
                    else if ((int)p->p->x == ship->x && (int)p->p->y == ship->y+1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-1, p->p->id,ship->y);
                    else if ((int)p->p->x == ship->x && (int)p->p->y == ship->y+2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-2, p->p->id,ship->y);

                    else if ((int)p->p->x == ship->x-1 && (int)p->p->y == ship->y - 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+2, p->p->id,ship->y-1);
                    else if ((int)p->p->x == ship->x-1 && (int)p->p->y == ship->y - 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+1, p->p->id,ship->y-1);
                    else if ((int)p->p->x == ship->x && (int)p->p->y == ship->y )
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x, p->p->id,ship->y-1);
                    else if ((int)p->p->x == ship->x-1 && (int)p->p->y == ship->y + 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-1, p->p->id,ship->y-1);
                    else if ((int)p->p->x == ship->x-1 && (int)p->p->y == ship->y + 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-2, p->p->id,ship->y-1);

                    else if ((int)p->p->x == ship->x-2 && (int)p->p->y == ship->y - 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+2, p->p->id,ship->y-2);
                    else if ((int)p->p->x == ship->x-2 && (int)p->p->y == ship->y - 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+1, p->p->id,ship->y-2);
                    else if ((int)p->p->x == ship->x-2 && (int)p->p->y == ship->y )
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x, p->p->id,ship->y-2);
                    else if ((int)p->p->x == ship->x-2 && (int)p->p->y == ship->y + 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-1, p->p->id,ship->y-2);
                    else if ((int)p->p->x == ship->x-2 && (int)p->p->y == ship->y + 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-2, p->p->id,ship->y-2);

                    else if ((int)p->p->x == ship->x-3 && (int)p->p->y == ship->y - 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+2, p->p->id,ship->y-3);
                    else if ((int)p->p->x == ship->x-3 && (int)p->p->y == ship->y - 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+1, p->p->id,ship->y-3);
                    else if ((int)p->p->x == ship->x-3 && (int)p->p->y == ship->y )
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x, p->p->id,ship->y-3);
                    else if ((int)p->p->x == ship->x-3 && (int)p->p->y == ship->y + 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-1, p->p->id,ship->y-3);
                    else if ((int)p->p->x == ship->x-3 && (int)p->p->y == ship->y + 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-2, p->p->id,ship->y-3);

                    else if ((int)p->p->x == ship->x-4 && (int)p->p->y == ship->y - 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+1, p->p->id,ship->y-4);
                    else if ((int)p->p->x == ship->x-4 && (int)p->p->y == ship->y )
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x, p->p->id,ship->y-4);
                    else if ((int)p->p->x == ship->x-4 && (int)p->p->y == ship->y + 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-1, p->p->id,ship->y-4);
                }
            }
            else if (ship->angle == 'k')
            {
                sprintf (ordre + strlen(ordre), "%d 03 b %d 04 0 ", ship->id, ship->id);
                for (struct linked_list *p = list; p != NULL; p = p->next)
                {
                    if ((int)p->p->x == ship->x-4 && (int)p->p->y == ship->y)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x, p->p->id,ship->y-4);
                    
                    else if ((int)p->p->x == ship->x-3 && (int)p->p->y == ship->y - 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-1, p->p->id,ship->y-3);
                    else if ((int)p->p->x == ship->x-3 && (int)p->p->y == ship->y)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x, p->p->id,ship->y-3);
                    else if ((int)p->p->x == ship->x-3 && (int)p->p->y == ship->y + 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+1, p->p->id,ship->y-3);

                    else if ((int)p->p->x == ship->x-2 && (int)p->p->y == ship->y - 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-2, p->p->id,ship->y-2);
                    else if ((int)p->p->x == ship->x-2 && (int)p->p->y == ship->y - 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-1, p->p->id,ship->y-2);
                    else if ((int)p->p->x == ship->x-2 && (int)p->p->y == ship->y )
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x, p->p->id,ship->y-2);
                    else if ((int)p->p->x == ship->x-2 && (int)p->p->y == ship->y + 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+1, p->p->id,ship->y-2);
                    else if ((int)p->p->x == ship->x-2 && (int)p->p->y == ship->y + 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+2, p->p->id,ship->y-2);

                    else if ((int)p->p->x == ship->x-1 && (int)p->p->y == ship->y - 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-2, p->p->id,ship->y-1);
                    else if ((int)p->p->x == ship->x-1 && (int)p->p->y == ship->y - 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-1, p->p->id,ship->y-1);
                    else if ((int)p->p->x == ship->x-1 && (int)p->p->y == ship->y)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x, p->p->id,ship->y-1);
                    else if ((int)p->p->x == ship->x-1 && (int)p->p->y == ship->y + 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+1, p->p->id,ship->y-1);
                    else if ((int)p->p->x == ship->x-1 && (int)p->p->y == ship->y + 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+2, p->p->id,ship->y-1);

                    else if ((int)p->p->x == ship->x && (int)p->p->y == ship->y-2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-2, p->p->id,ship->y);
                    else if ((int)p->p->x == ship->x && (int)p->p->y == ship->y-1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-1, p->p->id,ship->y);
                    else if ((int)p->p->x == ship->x && (int)p->p->y == ship->y)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x, p->p->id,ship->y);
                    else if ((int)p->p->x == ship->x && (int)p->p->y == ship->y+1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+1, p->p->id,ship->y);
                    else if ((int)p->p->x == ship->x && (int)p->p->y == ship->y+2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+2, p->p->id,ship->y);

                    else if ((int)p->p->x == ship->x+1 && (int)p->p->y == ship->y - 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-2, p->p->id,ship->y+1);
                    else if ((int)p->p->x == ship->x+1 && (int)p->p->y == ship->y - 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-1, p->p->id,ship->y+1);
                    else if ((int)p->p->x == ship->x+1 && (int)p->p->y == ship->y )
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x, p->p->id,ship->y+1);
                    else if ((int)p->p->x == ship->x+1 && (int)p->p->y == ship->y + 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+1, p->p->id,ship->y+1);
                    else if ((int)p->p->x == ship->x+1 && (int)p->p->y == ship->y + 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+2, p->p->id,ship->y+1);

                    else if ((int)p->p->x == ship->x+2 && (int)p->p->y == ship->y - 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-2, p->p->id,ship->y+2);
                    else if ((int)p->p->x == ship->x+2 && (int)p->p->y == ship->y - 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-1, p->p->id,ship->y+2);
                    else if ((int)p->p->x == ship->x+2 && (int)p->p->y == ship->y )
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x, p->p->id,ship->y+2);
                    else if ((int)p->p->x == ship->x+2 && (int)p->p->y == ship->y + 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+1, p->p->id,ship->y+2);
                    else if ((int)p->p->x == ship->x+2 && (int)p->p->y == ship->y + 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+2, p->p->id,ship->y+2);

                    else if ((int)p->p->x == ship->x+3 && (int)p->p->y == ship->y - 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-2, p->p->id,ship->y+3);
                    else if ((int)p->p->x == ship->x+3 && (int)p->p->y == ship->y - 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-1, p->p->id,ship->y+3);
                    else if ((int)p->p->x == ship->x+3 && (int)p->p->y == ship->y )
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x, p->p->id,ship->y+3);
                    else if ((int)p->p->x == ship->x+3 && (int)p->p->y == ship->y + 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+1, p->p->id,ship->y+3);
                    else if ((int)p->p->x == ship->x+3 && (int)p->p->y == ship->y + 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+2, p->p->id,ship->y+3);

                    else if ((int)p->p->x == ship->x+4 && (int)p->p->y == ship->y - 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-1, p->p->id,ship->y+4);
                    else if ((int)p->p->x == ship->x+4 && (int)p->p->y == ship->y )
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x, p->p->id,ship->y+4);
                    else if ((int)p->p->x == ship->x+4 && (int)p->p->y == ship->y + 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+1, p->p->id,ship->y+4);
                } 
            }
        }
        else if (ship->state == '3')
        {
            if (ship->angle == 'a')
            {
                sprintf (ordre + strlen(ordre), "%d 03 e %d 04 0 ", ship->id, ship->id);
                for (struct linked_list *p = list; p != NULL; p = p->next)
                {
                    if ((int)p->p->x == ship->x && (int)p->p->y == ship->y + 4)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+4, p->p->id,ship->y);
                    
                    else if ((int)p->p->x == ship->x-1 && (int)p->p->y == ship->y + 3)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+3, p->p->id,ship->y+1);
                    else if ((int)p->p->x == ship->x && (int)p->p->y == ship->y + 3)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+3, p->p->id,ship->y);
                    else if ((int)p->p->x == ship->x+1 && (int)p->p->y == ship->y + 3)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+3, p->p->id,ship->y-1);

                    else if ((int)p->p->x == ship->x-2 && (int)p->p->y == ship->y + 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+2, p->p->id,ship->y+2);
                    else if ((int)p->p->x == ship->x-1 && (int)p->p->y == ship->y + 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+2, p->p->id,ship->y+1);
                    else if ((int)p->p->x == ship->x && (int)p->p->y == ship->y + 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+2, p->p->id,ship->y);
                    else if ((int)p->p->x == ship->x+1 && (int)p->p->y == ship->y + 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+2, p->p->id,ship->y-1);
                    else if ((int)p->p->x == ship->x+2 && (int)p->p->y == ship->y + 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+2, p->p->id,ship->y-2);

                    else if ((int)p->p->x == ship->x-2 && (int)p->p->y == ship->y + 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+1, p->p->id,ship->y+2);
                    else if ((int)p->p->x == ship->x-1 && (int)p->p->y == ship->y + 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+1, p->p->id,ship->y+1);
                    else if ((int)p->p->x == ship->x && (int)p->p->y == ship->y + 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+1, p->p->id,ship->y);
                    else if ((int)p->p->x == ship->x+1 && (int)p->p->y == ship->y + 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+1, p->p->id,ship->y-1);
                    else if ((int)p->p->x == ship->x+2 && (int)p->p->y == ship->y + 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+1, p->p->id,ship->y-2);

                    else if ((int)p->p->x == ship->x-2 && (int)p->p->y == ship->y)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x, p->p->id,ship->y+2);
                    else if ((int)p->p->x == ship->x-1 && (int)p->p->y == ship->y)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x, p->p->id,ship->y+1);
                    else if ((int)p->p->x == ship->x && (int)p->p->y == ship->y)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x, p->p->id,ship->y);
                    else if ((int)p->p->x == ship->x+1 && (int)p->p->y == ship->y)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x, p->p->id,ship->y-1);
                    else if ((int)p->p->x == ship->x+2 && (int)p->p->y == ship->y)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x, p->p->id,ship->y-2);

                    else if ((int)p->p->x == ship->x-2 && (int)p->p->y == ship->y - 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-1, p->p->id,ship->y+2);
                    else if ((int)p->p->x == ship->x-1 && (int)p->p->y == ship->y - 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-1, p->p->id,ship->y+1);
                    else if ((int)p->p->x == ship->x && (int)p->p->y == ship->y - 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-1, p->p->id,ship->y);
                    else if ((int)p->p->x == ship->x+1 && (int)p->p->y == ship->y - 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-1, p->p->id,ship->y-1);
                    else if ((int)p->p->x == ship->x+2 && (int)p->p->y == ship->y - 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-1, p->p->id,ship->y-2);

                    else if ((int)p->p->x == ship->x-2 && (int)p->p->y == ship->y - 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-2, p->p->id,ship->y+2);
                    else if ((int)p->p->x == ship->x-1 && (int)p->p->y == ship->y - 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-2, p->p->id,ship->y+1);
                    else if ((int)p->p->x == ship->x && (int)p->p->y == ship->y - 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-2, p->p->id,ship->y);
                    else if ((int)p->p->x == ship->x+1 && (int)p->p->y == ship->y - 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-2, p->p->id,ship->y-1);
                    else if ((int)p->p->x == ship->x+2 && (int)p->p->y == ship->y - 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-2, p->p->id,ship->y-2);

                    else if ((int)p->p->x == ship->x-2 && (int)p->p->y == ship->y - 3)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-3, p->p->id,ship->y+2);
                    else if ((int)p->p->x == ship->x-1 && (int)p->p->y == ship->y - 3)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-3, p->p->id,ship->y+1);
                    else if ((int)p->p->x == ship->x && (int)p->p->y == ship->y - 3)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-3, p->p->id,ship->y);
                    else if ((int)p->p->x == ship->x+1 && (int)p->p->y == ship->y - 3)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-3, p->p->id,ship->y-1);
                    else if ((int)p->p->x == ship->x+2 && (int)p->p->y == ship->y - 3)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-3, p->p->id,ship->y-2);

                    else if ((int)p->p->x == ship->x-1 && (int)p->p->y == ship->y - 4)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-4, p->p->id,ship->y+1);
                    else if ((int)p->p->x == ship->x && (int)p->p->y == ship->y - 4)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-4, p->p->id,ship->y);
                    else if ((int)p->p->x == ship->x+1 && (int)p->p->y == ship->y - 4)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-4, p->p->id,ship->y-1);
                }
            }
            else if (ship->angle == 'b')
            {
                sprintf (ordre + strlen(ordre), "%d 03 k %d 04 0 ", ship->id, ship->id);
                for (struct linked_list *p = list; p != NULL; p = p->next)
                {
                    if ((int)p->p->x == ship->x && (int)p->p->y == ship->y - 4)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-4, p->p->id,ship->y);
                    
                    else if ((int)p->p->x == ship->x+1 && (int)p->p->y == ship->y - 3)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-3, p->p->id,ship->y-1);
                    else if ((int)p->p->x == ship->x && (int)p->p->y == ship->y - 3)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-3, p->p->id,ship->y);
                    else if ((int)p->p->x == ship->x-1 && (int)p->p->y == ship->y - 3)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-3, p->p->id,ship->y+1);

                    else if ((int)p->p->x == ship->x+2 && (int)p->p->y == ship->y - 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-2, p->p->id,ship->y-2);
                    else if ((int)p->p->x == ship->x+1 && (int)p->p->y == ship->y - 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-2, p->p->id,ship->y-1);
                    else if ((int)p->p->x == ship->x && (int)p->p->y == ship->y - 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-2, p->p->id,ship->y);
                    else if ((int)p->p->x == ship->x-1 && (int)p->p->y == ship->y - 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-2, p->p->id,ship->y+1);
                    else if ((int)p->p->x == ship->x-2 && (int)p->p->y == ship->y - 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-2, p->p->id,ship->y+2);

                    else if ((int)p->p->x == ship->x+2 && (int)p->p->y == ship->y - 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-1, p->p->id,ship->y-2);
                    else if ((int)p->p->x == ship->x+1 && (int)p->p->y == ship->y - 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-1, p->p->id,ship->y-1);
                    else if ((int)p->p->x == ship->x && (int)p->p->y == ship->y - 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-1, p->p->id,ship->y);
                    else if ((int)p->p->x == ship->x-1 && (int)p->p->y == ship->y - 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-1, p->p->id,ship->y+1);
                    else if ((int)p->p->x == ship->x-2 && (int)p->p->y == ship->y - 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-1, p->p->id,ship->y+2);

                    else if ((int)p->p->x == ship->x+2 && (int)p->p->y == ship->y)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x, p->p->id,ship->y-2);
                    else if ((int)p->p->x == ship->x+1 && (int)p->p->y == ship->y)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x, p->p->id,ship->y-1);
                    else if ((int)p->p->x == ship->x && (int)p->p->y == ship->y)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x, p->p->id,ship->y);
                    else if ((int)p->p->x == ship->x-1 && (int)p->p->y == ship->y)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x, p->p->id,ship->y+1);
                    else if ((int)p->p->x == ship->x-2 && (int)p->p->y == ship->y)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x, p->p->id,ship->y+2);

                    else if ((int)p->p->x == ship->x+2 && (int)p->p->y == ship->y + 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+1, p->p->id,ship->y-2);
                    else if ((int)p->p->x == ship->x+1 && (int)p->p->y == ship->y + 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+1, p->p->id,ship->y-1);
                    else if ((int)p->p->x == ship->x && (int)p->p->y == ship->y + 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+1, p->p->id,ship->y);
                    else if ((int)p->p->x == ship->x-1 && (int)p->p->y == ship->y + 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+1, p->p->id,ship->y+1);
                    else if ((int)p->p->x == ship->x-2 && (int)p->p->y == ship->y + 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+1, p->p->id,ship->y+2);

                    else if ((int)p->p->x == ship->x+2 && (int)p->p->y == ship->y + 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+2, p->p->id,ship->y-2);
                    else if ((int)p->p->x == ship->x+1 && (int)p->p->y == ship->y + 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+2, p->p->id,ship->y-1);
                    else if ((int)p->p->x == ship->x && (int)p->p->y == ship->y + 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+2, p->p->id,ship->y);
                    else if ((int)p->p->x == ship->x-1 && (int)p->p->y == ship->y + 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+2, p->p->id,ship->y+1);
                    else if ((int)p->p->x == ship->x-2 && (int)p->p->y == ship->y + 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+2, p->p->id,ship->y+2);

                    else if ((int)p->p->x == ship->x+2 && (int)p->p->y == ship->y + 3)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+3, p->p->id,ship->y-2);
                    else if ((int)p->p->x == ship->x+1 && (int)p->p->y == ship->y + 3)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+3, p->p->id,ship->y-1);
                    else if ((int)p->p->x == ship->x && (int)p->p->y == ship->y + 3)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+3, p->p->id,ship->y);
                    else if ((int)p->p->x == ship->x-1 && (int)p->p->y == ship->y + 3)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+3, p->p->id,ship->y+1);
                    else if ((int)p->p->x == ship->x-2 && (int)p->p->y == ship->y + 3)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+3, p->p->id,ship->y+2);

                    else if ((int)p->p->x == ship->x+1 && (int)p->p->y == ship->y + 4)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+4, p->p->id,ship->y-1);
                    else if ((int)p->p->x == ship->x && (int)p->p->y == ship->y + 4)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+4, p->p->id,ship->y);
                    else if ((int)p->p->x == ship->x-1 && (int)p->p->y == ship->y + 4)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+4, p->p->id,ship->y+1);
                }
            }
            else if (ship->angle == 'e')
            {
                sprintf (ordre + strlen(ordre), "%d 03 b %d 04 0 ", ship->id, ship->id);
                for (struct linked_list *p = list; p != NULL; p = p->next)
                {
                    if ((int)p->p->x == ship->x+4 && (int)p->p->y == ship->y)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x, p->p->id,ship->y-4);
                    
                    else if ((int)p->p->x == ship->x+3 && (int)p->p->y == ship->y - 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+1, p->p->id,ship->y-3);
                    else if ((int)p->p->x == ship->x+3 && (int)p->p->y == ship->y)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x, p->p->id,ship->y-3);
                    else if ((int)p->p->x == ship->x+3 && (int)p->p->y == ship->y + 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-1, p->p->id,ship->y-3);

                    else if ((int)p->p->x == ship->x+2 && (int)p->p->y == ship->y - 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+2, p->p->id,ship->y-2);
                    else if ((int)p->p->x == ship->x+2 && (int)p->p->y == ship->y - 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+1, p->p->id,ship->y-2);
                    else if ((int)p->p->x == ship->x+2 && (int)p->p->y == ship->y )
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x, p->p->id,ship->y-2);
                    else if ((int)p->p->x == ship->x+2 && (int)p->p->y == ship->y + 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-1, p->p->id,ship->y-2);
                    else if ((int)p->p->x == ship->x+2 && (int)p->p->y == ship->y + 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-2, p->p->id,ship->y-2);

                    else if ((int)p->p->x == ship->x+1 && (int)p->p->y == ship->y - 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+2, p->p->id,ship->y-1);
                    else if ((int)p->p->x == ship->x+1 && (int)p->p->y == ship->y - 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+1, p->p->id,ship->y-1);
                    else if ((int)p->p->x == ship->x+1 && (int)p->p->y == ship->y)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x, p->p->id,ship->y-1);
                    else if ((int)p->p->x == ship->x+1 && (int)p->p->y == ship->y + 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-1, p->p->id,ship->y-1);
                    else if ((int)p->p->x == ship->x+1 && (int)p->p->y == ship->y + 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-2, p->p->id,ship->y-1);

                    else if ((int)p->p->x == ship->x && (int)p->p->y == ship->y-2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+2, p->p->id,ship->y);
                    else if ((int)p->p->x == ship->x && (int)p->p->y == ship->y-1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+1, p->p->id,ship->y);
                    else if ((int)p->p->x == ship->x && (int)p->p->y == ship->y)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x, p->p->id,ship->y);
                    else if ((int)p->p->x == ship->x && (int)p->p->y == ship->y+1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-1, p->p->id,ship->y);
                    else if ((int)p->p->x == ship->x && (int)p->p->y == ship->y+2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-2, p->p->id,ship->y);

                    else if ((int)p->p->x == ship->x-1 && (int)p->p->y == ship->y - 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+2, p->p->id,ship->y+1);
                    else if ((int)p->p->x == ship->x-1 && (int)p->p->y == ship->y - 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+1, p->p->id,ship->y+1);
                    else if ((int)p->p->x == ship->x && (int)p->p->y == ship->y )
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x, p->p->id,ship->y+1);
                    else if ((int)p->p->x == ship->x-1 && (int)p->p->y == ship->y + 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-1, p->p->id,ship->y+1);
                    else if ((int)p->p->x == ship->x-1 && (int)p->p->y == ship->y + 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-2, p->p->id,ship->y+1);

                    else if ((int)p->p->x == ship->x-2 && (int)p->p->y == ship->y - 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+2, p->p->id,ship->y+2);
                    else if ((int)p->p->x == ship->x-2 && (int)p->p->y == ship->y - 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+1, p->p->id,ship->y+2);
                    else if ((int)p->p->x == ship->x-2 && (int)p->p->y == ship->y )
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x, p->p->id,ship->y+2);
                    else if ((int)p->p->x == ship->x-2 && (int)p->p->y == ship->y + 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-1, p->p->id,ship->y+2);
                    else if ((int)p->p->x == ship->x-2 && (int)p->p->y == ship->y + 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-2, p->p->id,ship->y+2);

                    else if ((int)p->p->x == ship->x-3 && (int)p->p->y == ship->y - 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+2, p->p->id,ship->y+3);
                    else if ((int)p->p->x == ship->x-3 && (int)p->p->y == ship->y - 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+1, p->p->id,ship->y+3);
                    else if ((int)p->p->x == ship->x-3 && (int)p->p->y == ship->y )
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x, p->p->id,ship->y+3);
                    else if ((int)p->p->x == ship->x-3 && (int)p->p->y == ship->y + 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-1, p->p->id,ship->y+3);
                    else if ((int)p->p->x == ship->x-3 && (int)p->p->y == ship->y + 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-2, p->p->id,ship->y+3);

                    else if ((int)p->p->x == ship->x-4 && (int)p->p->y == ship->y - 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+1, p->p->id,ship->y+4);
                    else if ((int)p->p->x == ship->x-4 && (int)p->p->y == ship->y )
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x, p->p->id,ship->y+4);
                    else if ((int)p->p->x == ship->x-4 && (int)p->p->y == ship->y + 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-1, p->p->id,ship->y+4);
                }
            }
            else if (ship->angle == 'k')
            {
                sprintf (ordre + strlen(ordre), "%d 03 a %d 04 0 ", ship->id, ship->id);
                for (struct linked_list *p = list; p != NULL; p = p->next)
                {
                    if ((int)p->p->x == ship->x-4 && (int)p->p->y == ship->y)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x, p->p->id,ship->y+4);
                    
                    else if ((int)p->p->x == ship->x-3 && (int)p->p->y == ship->y - 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+1, p->p->id,ship->y+3);
                    else if ((int)p->p->x == ship->x-3 && (int)p->p->y == ship->y)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x, p->p->id,ship->y+3);
                    else if ((int)p->p->x == ship->x-3 && (int)p->p->y == ship->y + 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-1, p->p->id,ship->y+3);

                    else if ((int)p->p->x == ship->x-2 && (int)p->p->y == ship->y - 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+2, p->p->id,ship->y+2);
                    else if ((int)p->p->x == ship->x-2 && (int)p->p->y == ship->y - 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+1, p->p->id,ship->y+2);
                    else if ((int)p->p->x == ship->x-2 && (int)p->p->y == ship->y )
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x, p->p->id,ship->y+2);
                    else if ((int)p->p->x == ship->x-2 && (int)p->p->y == ship->y + 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-1, p->p->id,ship->y+2);
                    else if ((int)p->p->x == ship->x-2 && (int)p->p->y == ship->y + 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-2, p->p->id,ship->y+2);

                    else if ((int)p->p->x == ship->x-1 && (int)p->p->y == ship->y - 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+2, p->p->id,ship->y+1);
                    else if ((int)p->p->x == ship->x-1 && (int)p->p->y == ship->y - 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+1, p->p->id,ship->y+1);
                    else if ((int)p->p->x == ship->x-1 && (int)p->p->y == ship->y)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x, p->p->id,ship->y+1);
                    else if ((int)p->p->x == ship->x-1 && (int)p->p->y == ship->y + 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-1, p->p->id,ship->y+1);
                    else if ((int)p->p->x == ship->x-1 && (int)p->p->y == ship->y + 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-2, p->p->id,ship->y+1);

                    else if ((int)p->p->x == ship->x && (int)p->p->y == ship->y-2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+2, p->p->id,ship->y);
                    else if ((int)p->p->x == ship->x && (int)p->p->y == ship->y-1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+1, p->p->id,ship->y);
                    else if ((int)p->p->x == ship->x && (int)p->p->y == ship->y)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x, p->p->id,ship->y);
                    else if ((int)p->p->x == ship->x && (int)p->p->y == ship->y+1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-1, p->p->id,ship->y);
                    else if ((int)p->p->x == ship->x && (int)p->p->y == ship->y+2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-2, p->p->id,ship->y);

                    else if ((int)p->p->x == ship->x+1 && (int)p->p->y == ship->y - 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+2, p->p->id,ship->y-1);
                    else if ((int)p->p->x == ship->x+1 && (int)p->p->y == ship->y - 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+1, p->p->id,ship->y-1);
                    else if ((int)p->p->x == ship->x+1 && (int)p->p->y == ship->y )
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x, p->p->id,ship->y-1);
                    else if ((int)p->p->x == ship->x+1 && (int)p->p->y == ship->y + 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-1, p->p->id,ship->y-1);
                    else if ((int)p->p->x == ship->x+1 && (int)p->p->y == ship->y + 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-2, p->p->id,ship->y-1);

                    else if ((int)p->p->x == ship->x+2 && (int)p->p->y == ship->y - 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+2, p->p->id,ship->y-2);
                    else if ((int)p->p->x == ship->x+2 && (int)p->p->y == ship->y - 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+1, p->p->id,ship->y-2);
                    else if ((int)p->p->x == ship->x+2 && (int)p->p->y == ship->y )
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x, p->p->id,ship->y-2);
                    else if ((int)p->p->x == ship->x+2 && (int)p->p->y == ship->y + 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-1, p->p->id,ship->y-2);
                    else if ((int)p->p->x == ship->x+2 && (int)p->p->y == ship->y + 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-2, p->p->id,ship->y-2);

                    else if ((int)p->p->x == ship->x+3 && (int)p->p->y == ship->y - 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+2, p->p->id,ship->y-3);
                    else if ((int)p->p->x == ship->x+3 && (int)p->p->y == ship->y - 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+1, p->p->id,ship->y-3);
                    else if ((int)p->p->x == ship->x+3 && (int)p->p->y == ship->y )
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x, p->p->id,ship->y-3);
                    else if ((int)p->p->x == ship->x+3 && (int)p->p->y == ship->y + 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-1, p->p->id,ship->y-3);
                    else if ((int)p->p->x == ship->x+3 && (int)p->p->y == ship->y + 2)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-2, p->p->id,ship->y-3);

                    else if ((int)p->p->x == ship->x+4 && (int)p->p->y == ship->y - 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x+1, p->p->id,ship->y-4);
                    else if ((int)p->p->x == ship->x+4 && (int)p->p->y == ship->y )
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x, p->p->id,ship->y-4);
                    else if ((int)p->p->x == ship->x+4 && (int)p->p->y == ship->y + 1)
                        sprintf (ordre + strlen(ordre), "%d 01 %d %d 02 %d ", p->p->id, ship->x-1, p->p->id,ship->y-4);
                }
            }
        }
    }
}