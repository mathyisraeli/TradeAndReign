#include "collision.h"

float coo_circle(struct personnages *perso)
{
    if (perso->skin[0] == '0')
    {
        if (perso->skin[1] == 0)
            return 0.2;
        else if (perso->skin[1]  == '1')
            return 0.2;
    }
    return 0.2;
}

void print_bioms(void)
{
    int mon_biomx = list.data[28].x / 25; 
    int mon_biomy = list.data[28].y / 25;
    int mon_biomindex = mon_biomx + mon_biomy * max_x_biom;
    for (int i = 0; i < list_bioms[mon_biomindex].size; i++)
    {
        struct personnages *p2 = &list.data[list_bioms[mon_biomindex].data[i]];
        printf ("%d %f %f\n", list_bioms[mon_biomindex].data[i], p2->x, p2->y);
    }
    printf ("-------------------\n");

}

void collision(void)
{
    int offsets[4][2] = {
        {0,0},  // même biom
        {1,0},  // droite
        {0,1},  // bas
        {1,1}   // bas-droite
    };


    
    //printf ("%f %f\n", list.data[0].moved_x, list.data[0].moved_y);
    for (int itteration = 0; itteration < 2; itteration++)
    {
        for (int ybiom = 0; ybiom < max_y_biom; ybiom++)
        {
            for (int xbiom = 0; xbiom < max_x_biom; xbiom++)
            {
                for (int i = 0; i < list_bioms[xbiom + ybiom * max_x_biom].size; i++)
                {
                    struct personnages *p = &list.data[list_bioms[xbiom + ybiom * max_x_biom].data[i]];
                    for (int n = 0; n < 4; n++)
                    {
                        int nx = xbiom + offsets[n][0];
                        int ny = ybiom + offsets[n][1];
                        if (nx >= max_x_biom || ny >= max_y_biom)
                            continue;
                        for (int j = (n == 0) * (i + 1); j < list_bioms[nx + ny * max_x_biom].size; j++)
                        {
                            struct personnages *p2 = &list.data[list_bioms[nx + ny * max_x_biom].data[j]];
                            if (p2->moved_x != 0 || p2->moved_y != 0 || p->moved_x != 0 || p->moved_y != 0)
                            {
                                float ax = p->x + p->moved_x;
                                float ay = p->y + p->moved_y;
                                float bx = p2->x + p2->moved_x;
                                float by = p2->y + p2->moved_y;
                                float dx = bx - ax;
                                float dy = by - ay;
                                float d = dx*dx + dy*dy;
                                if (d < (coo_circle(p2)+coo_circle(p))*(coo_circle(p2)+coo_circle(p)))
                                {
                                    float alt = allowed_to_move(p, ax, ay,  p2->moved_x,  p2->moved_y);
                                    if (alt != -1 && 0 < -dx * p2->moved_x - dy * p2->moved_y)
                                    {
                                        p->moved_x += p2->moved_x;
                                        p->moved_y += p2->moved_y;
                                        p->altitude = alt;
                                    }
                                    alt = allowed_to_move(p2,  bx,  by, p->moved_x, p->moved_y);
                                    if (alt != -1 && 0 < dx * p->moved_x + dy * p->moved_y)
                                    {
                                        p2->moved_x += p->moved_x; //  p->weight /  p2->weight
                                        p2->moved_y += p->moved_y; //  p->weight /  p2->weight
                                        p2->altitude = alt;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    for (int i = 0; i <= list.maxid; i++)
    {
        if (list.data[i].is_active == 1 && (list.data[i].moved_x != 0 || list.data[i].moved_y != 0))
        {
            float alt = allowed_to_move(&list.data[i], list.data[i].x, list.data[i].y, list.data[i].moved_x, list.data[i].moved_y);
            if (alt != -1)
            {
                float newx = list.data[i].x + list.data[i].moved_x;
                float newy = list.data[i].y + list.data[i].moved_y;
                list.data[i].a_bouger = 1;
                list.data[i].altitude = alt;
                int prev_biome_id = (int)(list.data[i].y * 0.04f) * max_x_biom + (int)(list.data[i].x * 0.04f);
                int biome_id = (int)(newy * 0.04f) * max_x_biom + (int)(newx     * 0.04f);
                if (prev_biome_id != biome_id)
                {
                    //printf ("%d %d %d\n", i, prev_biome_id, biome_id);
                    //printf ("%f %f %f %f \n", list.data[i].x,list.data[i].y,  list.data[i].x + list.data[i].moved_x,  list.data[i].y + list.data[i].moved_y);
                    remove_perso_bioms(i, prev_biome_id);
                    append_perso_bioms(i, biome_id);
                }
                list.data[i].x = newx;
                list.data[i].y = newy;
            }
            list.data[i].moved_x = 0;
            list.data[i].moved_y = 0;
            int src = (int)list.data[i].y * max_x + (int)list.data[i].x;
	        int ga = (altitude(src)/38)*2;
	        if (list.data[i].inside == -1) 
	        {
		        if ((building_altitude[src][(int)(list.data[i].altitude*2)-ga]/10) % 10 == 1) 
		        {
			        list.data[i].inside = building_id[src]; 
		        }
            }
	        else if (building_id[src] == -1 || (building_altitude[src][(int)(list.data[i].altitude*2)-ga]/10) % 10 == 0)
			    list.data[i].inside = -1; 
        }
    }
}


float allowed_to_move(struct personnages *perso, float x, float y, float mvx, float mvy) //>=0 altitude you should be -1 not allowed 
{
    float r = coo_circle(perso);
    if (x + mvx - r < 0 || x + mvx + r > max_x || y + mvy - r < 0 || y + mvy + r > max_y)
            return -1;

    int src = (int)(y) * max_x + (int)(x);
    int dst = (int)(y + mvy) * max_x + (int)(x + mvx);
    int ga = altitude(dst)/19;

    
    if (perso->inside == -1)
    {
        if (building_id[dst] == -1)
        {
            if (ground[dst]->texture == ea1 || ground[dst]->texture == ea2 || ground[dst]->texture == ea3)
                return -1;
            if (perso->altitude < (float)altitude(dst)/38- 1)
                return -1;
            //if (perso->altitude > (float)altitude(dst)/38)
              //  return perso->altitude - 0.026;
            return (float)altitude(dst)/38;
        }
        if ((perso->altitude < (float)altitude(dst)/38- 2 && building_altitude[dst][0] == 1) || perso->altitude < (float)altitude(dst)/38- 1)
            return -1;
        if (building_altitude[dst][(int)(perso->altitude*2)+1-ga]/100 == 1 || building_altitude[dst][(int)(perso->altitude*2)+2-ga]/100 == 1 || building_altitude[dst][(int)(perso->altitude*2)+3-ga]/100 == 1 || 
        (building_altitude[dst][(int)(perso->altitude*2)-ga]/100 == 1 && (building_altitude[dst][(int)(perso->altitude*2)+4-ga]/100 == 1 || (building_altitude[src] != NULL && building_altitude[src][(int)(perso->altitude*2)+4-ga]/100 == 1))))
            return -1;
        for (int i = (int)(perso->altitude*2); i-ga>=0; i -= 1)
        {
            if (building_altitude[dst][i-ga]/100  != 0)
            {
                return (float)i/2 + 0.5;
            }
        }
        return (float)altitude(dst)/38;
    }
    else {
        if (building_id[dst] != perso->inside && (building_altitude[src][(int)(perso->altitude*2)+1-ga]/100 == 1 || building_altitude[src][(int)(perso->altitude*2)+2-ga]/100 == 1 || building_altitude[src][(int)(perso->altitude*2)+3-ga]/100 == 1))
            return -1;
        if (building_id[dst] == -1)
        {
            if (perso->altitude < (float)altitude(dst)/38- 1)
                return -1;
            return (float)altitude(dst)/38;
        }
        if (building_altitude[dst][(int)(perso->altitude*2)+1-ga]%10 == 1 || building_altitude[dst][(int)(perso->altitude*2)+2-ga]%10 == 1 || building_altitude[dst][(int)(perso->altitude*2)+3-ga]%10 == 1 || 
        (building_altitude[dst][(int)(perso->altitude*2)-ga]%10 == 1 && (building_altitude[dst][(int)(perso->altitude*2)+4-ga]%10 == 1 || (building_altitude[src] != NULL && building_altitude[src][(int)(perso->altitude*2)+4-ga]%10 == 1))))
            return -1;
        for (int i = (int)(perso->altitude*2); i-ga>=0; i -= 1)
            if (building_altitude[dst][i-ga]%10  != 0)
                return (float)i/2 + 0.5;
        return (float)altitude(dst)/38;
    }
    /*else {
         if (building_id[(int)(y + mvy) * max_x + (int)(x + mvx)] != perso->inside)
            return 0;
    }*/
    return 1;
}
