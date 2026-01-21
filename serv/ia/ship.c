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
                (ground[(ship->y + 5)*max_x + ship->x]->texture == ea1 || ground[(ship->y + 5)*max_x + ship->x]->texture == ea2 || ground[(ship->y + 5)*max_x + ship->x]->texture == ea3) &&
                (ground[(ship->y + 4)*max_x + ship->x + 1]->texture == ea1 || ground[(ship->y + 4)*max_x + ship->x + 1]->texture == ea2 || ground[(ship->y + 4)*max_x + ship->x + 1]->texture == ea3) &&
                (ground[(ship->y + 3)*max_x + ship->x + 2]->texture == ea1 || ground[(ship->y + 3)*max_x + ship->x + 2]->texture == ea2 || ground[(ship->y + 3)*max_x + ship->x + 2]->texture == ea3) &&
                (ground[(ship->y + 4)*max_x + ship->x - 1]->texture == ea1 || ground[(ship->y + 4)*max_x + ship->x - 1]->texture == ea2 || ground[(ship->y + 4)*max_x + ship->x - 1]->texture == ea3) &&
                (ground[(ship->y + 3)*max_x + ship->x - 2]->texture == ea1 || ground[(ship->y + 3)*max_x + ship->x - 2]->texture == ea2 || ground[(ship->y + 3)*max_x + ship->x - 2]->texture == ea3) &&
                building_id[(ship->y + 5)*max_x + ship->x] == -1 && building_id[(ship->y + 4)*max_x + ship->x - 1] == -1 && building_id[(ship->y + 3)*max_x + ship->x - 2] == -1 && building_id[(ship->y + 4)*max_x + ship->x + 1] == -1 && building_id[(ship->y + 3)*max_x + ship->x + 2] == -1)
                { 
                    for (int i = 0; i < list.maxid;i++)
                    {
                        if (list.data[i].is_active == 1 && building_id[(int)list.data[i].x + (int)list.data[i].y*max_x] == ship->id)
                        {
                            list.data[i].y += 1;
                            list.data[i].a_bouger = 1;
                            cnt += 1;
                        }
                    }
                    if (cnt == 0)
                        ship->state = 0;
                    else
                    {
                        ship->a_bouger = 1;
                        ship->y += 1;
                    }
                }
                
            }
            else if (ship->angle == 'b')
            {
                if (ship->y > 4 && 
                (ground[(ship->y - 5)*max_x + ship->x]->texture == ea1 || ground[(ship->y - 5)*max_x + ship->x]->texture == ea2 || ground[(ship->y - 5)*max_x + ship->x]->texture == ea3) &&
                (ground[(ship->y - 4)*max_x + ship->x + 1]->texture == ea1 || ground[(ship->y - 4)*max_x + ship->x + 1]->texture == ea2 || ground[(ship->y - 4)*max_x + ship->x + 1]->texture == ea3) &&
                (ground[(ship->y - 3)*max_x + ship->x + 2]->texture == ea1 || ground[(ship->y - 3)*max_x + ship->x + 2]->texture == ea2 || ground[(ship->y - 3)*max_x + ship->x + 2]->texture == ea3) &&
                (ground[(ship->y - 4)*max_x + ship->x - 1]->texture == ea1 || ground[(ship->y - 4)*max_x + ship->x - 1]->texture == ea2 || ground[(ship->y - 4)*max_x + ship->x - 1]->texture == ea3) &&
                (ground[(ship->y - 3)*max_x + ship->x - 2]->texture == ea1 || ground[(ship->y - 3)*max_x + ship->x - 2]->texture == ea2 || ground[(ship->y - 3)*max_x + ship->x - 2]->texture == ea3) &&
                building_id[(ship->y - 5)*max_x + ship->x] == -1 && building_id[(ship->y - 4)*max_x + ship->x - 1] == -1 && building_id[(ship->y - 3)*max_x + ship->x - 2] == -1 && building_id[(ship->y - 4)*max_x + ship->x + 1] == -1 && building_id[(ship->y - 3)*max_x + ship->x + 2] == -1)
                { 
                    for (int i = 0; i < list.maxid;i++)
                    {
                        if (list.data[i].is_active == 1 && building_id[(int)list.data[i].x + (int)list.data[i].y*max_x] == ship->id)
                        {
                            list.data[i].y -= 1;
                            list.data[i].a_bouger = 1;
                            cnt += 1;
                        }
                    }
                    if (cnt == 0)
                        ship->state = 0;
                    else
                    {
                        ship->a_bouger = 1;
                        ship->y -= 1;
                    }
                }

            }
            else if (ship->angle == 'k')
            {
                if (ship->x > 4 && 
                (ground[(ship->y)*max_x + ship->x - 5]->texture == ea1 || ground[(ship->y)*max_x + ship->x - 5]->texture == ea2 || ground[(ship->y)*max_x + ship->x - 5]->texture == ea3) &&
                (ground[(ship->y + 1)*max_x + ship->x - 4]->texture == ea1 || ground[(ship->y + 1)*max_x + ship->x - 4]->texture == ea2 || ground[(ship->y + 1)*max_x + ship->x - 4]->texture == ea3) &&
                (ground[(ship->y + 2)*max_x + ship->x - 3]->texture == ea1 || ground[(ship->y + 2)*max_x + ship->x - 3]->texture == ea2 || ground[(ship->y + 2)*max_x + ship->x - 3]->texture == ea3) &&
                (ground[(ship->y - 1)*max_x + ship->x - 4]->texture == ea1 || ground[(ship->y - 1)*max_x + ship->x - 4]->texture == ea2 || ground[(ship->y - 1)*max_x + ship->x - 4]->texture == ea3) &&
                (ground[(ship->y - 2)*max_x + ship->x - 3]->texture == ea1 || ground[(ship->y - 2)*max_x + ship->x - 3]->texture == ea2 || ground[(ship->y - 2)*max_x + ship->x - 3]->texture == ea3) &&
                building_id[(ship->y )*max_x + ship->x - 5] == -1 && building_id[(ship->y + 1)*max_x + ship->x - 4] == -1 && building_id[(ship->y + 2)*max_x + ship->x - 3] == -1 && building_id[(ship->y - 1)*max_x + ship->x - 4] == -1 && building_id[(ship->y - 2)*max_x + ship->x - 3] == -1)
                { 
                    for (int i = 0; i < list.maxid;i++)
                    {
                        if (list.data[i].is_active == 1 && building_id[(int)list.data[i].x + (int)list.data[i].y*max_x] == ship->id)
                        {
                            list.data[i].y -= 1;
                            list.data[i].a_bouger = 1;
                            cnt += 1;
                        }
                    }
                    if (cnt == 0)
                        ship->state = 0;
                    else
                    {
                        ship->a_bouger = 1;
                        ship->x -= 1;
                    }
                }
            }
            else
            {
                if (ship->x < max_x-5 &&
                (ground[(ship->y)*max_x + ship->x + 5]->texture == ea1 || ground[(ship->y)*max_x + ship->x + 5]->texture == ea2 || ground[(ship->y)*max_x + ship->x + 5]->texture == ea3) &&
                (ground[(ship->y + 1)*max_x + ship->x + 4]->texture == ea1 || ground[(ship->y + 1)*max_x + ship->x + 4]->texture == ea2 || ground[(ship->y + 1)*max_x + ship->x + 4]->texture == ea3) &&
                (ground[(ship->y + 2)*max_x + ship->x + 3]->texture == ea1 || ground[(ship->y + 2)*max_x + ship->x + 3]->texture == ea2 || ground[(ship->y + 2)*max_x + ship->x + 3]->texture == ea3) &&
                (ground[(ship->y - 1)*max_x + ship->x + 4]->texture == ea1 || ground[(ship->y - 1)*max_x + ship->x + 4]->texture == ea2 || ground[(ship->y - 1)*max_x + ship->x + 4]->texture == ea3) &&
                (ground[(ship->y - 2)*max_x + ship->x + 3]->texture == ea1 || ground[(ship->y - 2)*max_x + ship->x + 3]->texture == ea2 || ground[(ship->y - 2)*max_x + ship->x + 3]->texture == ea3) &&
                building_id[(ship->y )*max_x + ship->x + 5] == -1 && building_id[(ship->y + 1)*max_x + ship->x + 4] == -1 && building_id[(ship->y + 2)*max_x + ship->x + 3] == -1 && building_id[(ship->y - 1)*max_x + ship->x + 4] == -1 && building_id[(ship->y - 2)*max_x + ship->x + 3] == -1) 
                {    
                    for (int i = 0; i < list.maxid;i++)
                    {
                        if (list.data[i].is_active == 1 && building_id[(int)list.data[i].x + (int)list.data[i].y*max_x] == ship->id)
                        {
                            list.data[i].x += 1;
                            list.data[i].a_bouger = 1;
                            cnt += 1;
                        }
                    }
                    if (cnt == 0)
                        ship->state = 0;
                    else
                    {
                        ship->a_bouger = 1;
                        ship->x += 1;
                    }
                }
            }
        }

//b -x
//d -y
//f +x
//h +y
        else if (ship->state == '2') //inverse des aiguilles d'une montre
        {
            if (ship->angle == 'b') // -x
            {
                ship->angle = 'h';
                ship->state = 0;
                ship->a_bouger = 1;
                for (int i = 0; i < list.maxid;i++)
                {
                    if (list.data[i].is_active == 1 && building_id[(int)list.data[i].x + (int)list.data[i].y*max_x] == ship->id)
                    {
                        float dx = ship->x - list.data[i].x;
                        float dy = ship->x - list.data[i].y;
                        list.data[i].x = ship->x - dy;
                        list.data[i].y = ship->y - dx;
                    }
                }
            }
            else if (ship->angle == 'h')
            {
                ship->angle = 'f';
                ship->state = 0;
                ship->a_bouger = 1;
                for (int i = 0; i < list.maxid;i++)
                {
                    if (list.data[i].is_active == 1 && building_id[(int)list.data[i].x + (int)list.data[i].y*max_x] == ship->id)
                    {
                        float dx = ship->x - list.data[i].x;
                        float dy = ship->x - list.data[i].y;
                        list.data[i].x = ship->x + dy;
                        list.data[i].y = ship->y + dx;
                    }
                }
            }
            else if (ship->angle == 'f')
            {
                ship->angle = 'd';
                ship->state = 0;
                ship->a_bouger = 1;
                for (int i = 0; i < list.maxid;i++)
                {
                    if (list.data[i].is_active == 1 && building_id[(int)list.data[i].x + (int)list.data[i].y*max_x] == ship->id)
                    {
                        float dx = ship->x - list.data[i].x;
                        float dy = ship->x - list.data[i].y;
                        list.data[i].x = ship->x + dy;
                        list.data[i].y = ship->y - dx;
                    }
                }
            }
            else if (ship->angle == 'd')
            {
                ship->angle = 'b';
                ship->state = 0;
                ship->a_bouger = 1;
                for (int i = 0; i < list.maxid;i++)
                {
                    if (list.data[i].is_active == 1 && building_id[(int)list.data[i].x + (int)list.data[i].y*max_x] == ship->id)
                    {
                        float dx = ship->x - list.data[i].x;
                        float dy = ship->x - list.data[i].y;
                        list.data[i].x = ship->x - dy;
                        list.data[i].y = ship->y + dx;
                    }
                } 
            }
        }
        else if (ship->state == '3')//sens des aiguilles d'une montre
        {
            if (ship->angle == 'h')
            {
                ship->angle = 'b';
                ship->state = 0;
                ship->a_bouger = 1;
                for (int i = 0; i < list.maxid;i++)
                {
                    if (list.data[i].is_active == 1 && building_id[(int)list.data[i].x + (int)list.data[i].y*max_x] == ship->id)
                    {
                        float dx = ship->x - list.data[i].x;
                        float dy = ship->x - list.data[i].y;
                        list.data[i].x = ship->x - dy;
                        list.data[i].y = ship->y - dx;
                    }
                }
            }
            else if (ship->angle == 'f')
            {
                ship->angle = 'h';
                ship->state = 0;
                ship->a_bouger = 1;
                for (int i = 0; i < list.maxid;i++)
                {
                   if (list.data[i].is_active == 1 && building_id[(int)list.data[i].x + (int)list.data[i].y*max_x] == ship->id)
                   {
                        float dx = ship->x - list.data[i].x;
                        float dy = ship->x - list.data[i].y;
                        list.data[i].x = ship->x - dy;
                        list.data[i].y = ship->y + dx;
                   }
                }
            }
            else if (ship->angle == 'd')
            {
                ship->angle = 'f';
                ship->state = 0;
                ship->a_bouger = 1;
                for (int i = 0; i < list.maxid;i++)
                {
                    if (list.data[i].is_active == 1 && building_id[(int)list.data[i].x + (int)list.data[i].y*max_x] == ship->id)
                    {
                        float dx = ship->x - list.data[i].x;
                        float dy = ship->x - list.data[i].y;
                        list.data[i].x = ship->x + dy;
                        list.data[i].y = ship->y + dx;
                    }
                }
            }
            else if (ship->angle == 'b')
            {
                ship->angle = 'd';
                ship->state = 0;
                ship->a_bouger = 1;
                for (int i = 0; i < list.maxid;i++)
                {
                    if (list.data[i].is_active == 1 && building_id[(int)list.data[i].x + (int)list.data[i].y*max_x] == ship->id)
                    {
                        float dx = ship->x - list.data[i].x;
                        float dy = ship->x - list.data[i].y;
                        list.data[i].x = ship->x + dy;
                        list.data[i].y = ship->y - dx;
                    }
                }
            }
        }
    }
}