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
            if (ship->angle == 'h')
            {
                if (ship->y < max_y - 5 && 
                ground[(ship->y + 5)*max_x + ship->x]->texture == wat &&
                ground[(ship->y + 4)*max_x + ship->x + 1]->texture == wat &&
                ground[(ship->y + 3)*max_x + ship->x + 2]->texture == wat &&
                ground[(ship->y + 4)*max_x + ship->x - 1]->texture == wat &&
                ground[(ship->y + 3)*max_x + ship->x - 2]->texture == wat &&
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
                        remove_building_altitude(ship);
                        ship->y += 1;
                        add_building_altitude(ship);
                    }
                }
                
            }
            else if (ship->angle == 'd')
            {
                if (ship->y > 4 && 
                ground[(ship->y - 5)*max_x + ship->x]->texture == wat  &&
                ground[(ship->y - 4)*max_x + ship->x + 1]->texture == wat &&
                ground[(ship->y - 3)*max_x + ship->x + 2]->texture == wat &&
                ground[(ship->y - 4)*max_x + ship->x - 1]->texture == wat &&
                ground[(ship->y - 3)*max_x + ship->x - 2]->texture == wat &&
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
                        remove_building_altitude(ship);
                        ship->y -= 1;
                        add_building_altitude(ship);
                    }
                }

            }
            else if (ship->angle == 'b')
            {
                if (ship->x > 4 && 
                ground[(ship->y)*max_x + ship->x - 5]->texture == wat &&
                ground[(ship->y + 1)*max_x + ship->x - 4]->texture == wat &&
                ground[(ship->y + 2)*max_x + ship->x - 3]->texture == wat &&
                ground[(ship->y - 1)*max_x + ship->x - 4]->texture == wat &&
                ground[(ship->y - 2)*max_x + ship->x - 3]->texture == wat &&
                building_id[(ship->y )*max_x + ship->x - 5] == -1 && building_id[(ship->y + 1)*max_x + ship->x - 4] == -1 && building_id[(ship->y + 2)*max_x + ship->x - 3] == -1 && building_id[(ship->y - 1)*max_x + ship->x - 4] == -1 && building_id[(ship->y - 2)*max_x + ship->x - 3] == -1)
                { 
                    for (int i = 0; i < list.maxid;i++)
                    {
                        if (list.data[i].is_active == 1 && building_id[(int)list.data[i].x + (int)list.data[i].y*max_x] == ship->id)
                        {
                            list.data[i].x -= 1;
                            list.data[i].a_bouger = 1;
                            cnt += 1;
                        }
                    }
                    if (cnt == 0)
                        ship->state = 0;
                    else
                    {
                        ship->a_bouger = 1;
                        remove_building_altitude(ship);
                        ship->x -= 1;
                        add_building_altitude(ship);
                    }
                }
            }
            else
            {
                if (ship->x < max_x-5 &&
                ground[(ship->y)*max_x + ship->x + 5]->texture == wat &&
                ground[(ship->y + 1)*max_x + ship->x + 4]->texture == wat &&
                ground[(ship->y + 2)*max_x + ship->x + 3]->texture == wat &&
                ground[(ship->y - 1)*max_x + ship->x + 4]->texture == wat &&
                ground[(ship->y - 2)*max_x + ship->x + 3]->texture == wat &&
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
                        remove_building_altitude(ship);
                        ship->x += 1;
                        add_building_altitude(ship);
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
                remove_building_altitude(ship);
                ship->angle = 'h';
                add_building_altitude(ship);
                ship->state = 0;
                ship->a_bouger = 1;
                /*for (int i = 0; i < list.maxid;i++)
                {
                    if (list.data[i].is_active == 1 && building_id[(int)list.data[i].x + (int)list.data[i].y*max_x] == ship->id)
                    {
                        float dx = ship->x - list.data[i].x;
                        float dy = ship->x - list.data[i].y;
                        list.data[i].x = ship->x - dy;
                        list.data[i].y = ship->y - dx;
                    }
                }*/
            }
            else if (ship->angle == 'h')
            {
                remove_building_altitude(ship);
                ship->angle = 'f';
                add_building_altitude(ship);
                ship->state = 0;
                ship->a_bouger = 1;
                /*for (int i = 0; i < list.maxid;i++)
                {
                    if (list.data[i].is_active == 1 && building_id[(int)list.data[i].x + (int)list.data[i].y*max_x] == ship->id)
                    {
                        float dx = ship->x - list.data[i].x;
                        float dy = ship->x - list.data[i].y;
                        list.data[i].x = ship->x + dy;
                        list.data[i].y = ship->y + dx;
                    }
                }*/
            }
            else if (ship->angle == 'f')
            {
                remove_building_altitude(ship);
                ship->angle = 'd';
                add_building_altitude(ship);
                ship->state = 0;
                ship->a_bouger = 1;
                /*for (int i = 0; i < list.maxid;i++)
                {
                    if (list.data[i].is_active == 1 && building_id[(int)list.data[i].x + (int)list.data[i].y*max_x] == ship->id)
                    {
                        float dx = ship->x - list.data[i].x;
                        float dy = ship->x - list.data[i].y;
                        list.data[i].x = ship->x + dy;
                        list.data[i].y = ship->y - dx;
                    }
                }*/
            }
            else if (ship->angle == 'd')
            {
                                printf ("test2\n");
                remove_building_altitude(ship);
                ship->angle = 'b';
                add_building_altitude(ship);
                ship->state = 0;
                ship->a_bouger = 1;
                /*for (int i = 0; i < list.maxid;i++)
                {
                    if (list.data[i].is_active == 1 && building_id[(int)list.data[i].x + (int)list.data[i].y*max_x] == ship->id)
                    {
                        float dx = ship->x - list.data[i].x;
                        float dy = ship->x - list.data[i].y;
                        list.data[i].x = ship->x - dy;
                        list.data[i].y = ship->y + dx;
                    }
                } */
            }
        }
        else if (ship->state == '3')//sens des aiguilles d'une montre
        {
            if (ship->angle == 'b')
            {
                remove_building_altitude(ship);
                ship->angle = 'd';
                add_building_altitude(ship);
                ship->state = 0;
                ship->a_bouger = 1;
                /*for (int i = 0; i < list.maxid;i++)
                {
                    if (list.data[i].is_active == 1 && building_id[(int)list.data[i].x + (int)list.data[i].y*max_x] == ship->id)
                    {
                        float dx = ship->x - list.data[i].x;
                        float dy = ship->x - list.data[i].y;
                        list.data[i].x = ship->x - dy;
                        list.data[i].y = ship->y - dx;
                    }
                }*/
            }
            else if (ship->angle == 'd')
            {
                printf ("test1\n");
                remove_building_altitude(ship);
                ship->angle = 'f';
                add_building_altitude(ship);
                ship->state = 0;
                ship->a_bouger = 1;
                /*for (int i = 0; i < list.maxid;i++)
                {
                   if (list.data[i].is_active == 1 && building_id[(int)list.data[i].x + (int)list.data[i].y*max_x] == ship->id)
                   {
                        float dx = ship->x - list.data[i].x;
                        float dy = ship->x - list.data[i].y;
                        list.data[i].x = ship->x - dy;
                        list.data[i].y = ship->y + dx;
                   }
                }*/
            }
            else if (ship->angle == 'f')
            {
                remove_building_altitude(ship);
                ship->angle = 'h';
                add_building_altitude(ship);
                ship->state = 0;
                ship->a_bouger = 1;
                /*for (int i = 0; i < list.maxid;i++)
                {
                    if (list.data[i].is_active == 1 && building_id[(int)list.data[i].x + (int)list.data[i].y*max_x] == ship->id)
                    {
                        float dx = ship->x - list.data[i].x;
                        float dy = ship->x - list.data[i].y;
                        list.data[i].x = ship->x + dy;
                        list.data[i].y = ship->y + dx;
                    }
                }*/
            }
            else if (ship->angle == 'h')
            {
                remove_building_altitude(ship);
                ship->angle = 'b';
                add_building_altitude(ship);
                ship->state = 0;
                ship->a_bouger = 1;
                /*for (int i = 0; i < list.maxid;i++)
                {
                    if (list.data[i].is_active == 1 && building_id[(int)list.data[i].x + (int)list.data[i].y*max_x] == ship->id)
                    {
                        float dx = ship->x - list.data[i].x;
                        float dy = ship->x - list.data[i].y;
                        list.data[i].x = ship->x + dy;
                        list.data[i].y = ship->y - dx;
                    }
                }*/
            }
        }
    }
}