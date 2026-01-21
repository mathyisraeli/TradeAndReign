#include "collision.h"

float coo_circle(struct personnages *perso)
{
    if (perso->skin[0] == '0')
    {
        if (perso->skin[1] == 0)
            return 0.1;
        else if (perso->skin[1]  == '1')
            return 0.1;
    }
    return 0.1;
}

void collision(void)
{
    for (int i = 0; i <= list.maxid; i++)
    {
        if (list.data[i].pv <= 0)
            continue;
        if (list.data[i].a_bouger == 1)
        {
            float alt = allowed_to_move(&list.data[i], list.data[i].x, list.data[i].y, list.data[i].moved_x, list.data[i].moved_y);
            if (alt != -1)
            {
                list.data[i].x += list.data[i].moved_x;
                list.data[i].y += list.data[i].moved_y;
                list.data[i].altitude = alt;
            }
            else
            {
                list.data[i].chemin_is_set = 0;
                list.data[i].moved_x = 0;
                list.data[i].moved_y = 0;
            }

        }
    }
    for (int i = 0; i <= list.maxid; i++)
    {
        if (list.data[i].pv <= 0)
            continue;
        for (int j = i + 1; j <= list.maxid; j++)
        {
            if (list.data[j].pv <= 0)
                continue;
            if (list.data[i].a_bouger ||  list.data[j].a_bouger)
            {
                float d = ( list.data[j].x - list.data[i].x)*( list.data[j].x - list.data[i].x) + ( list.data[j].y - list.data[i].y)*( list.data[j].y - list.data[i].y);
                if (d < (coo_circle(&list.data[j])+coo_circle(&list.data[i]))*(coo_circle(&list.data[j])+coo_circle(&list.data[i])))
                {
                    if (d <= ( list.data[j].x -  list.data[j].moved_x - list.data[i].x + list.data[i].moved_x)*( list.data[j].x -  list.data[j].moved_x - list.data[i].x + list.data[i].moved_x) + ( list.data[j].y -  list.data[j].moved_y - list.data[i].y + list.data[i].moved_y)*( list.data[j].y -  list.data[j].moved_y - list.data[i].y + list.data[i].moved_y))
                    {
                        float alt = allowed_to_move(&list.data[i], list.data[i].x, list.data[i].y,  list.data[j].moved_x,  list.data[j].moved_y);
                        if (alt != -1)
                        {
                            list.data[i].x +=  list.data[j].moved_x; //  list.data[j].weight / list.data[i].weight;
                            list.data[i].y +=  list.data[j].moved_y; //  list.data[j].weight / list.data[i].weight
                            list.data[i].altitude = alt;
                            list.data[i].a_bouger = 1; 
                        }
                        alt = allowed_to_move(&list.data[j],  list.data[j].x,  list.data[j].y, list.data[i].moved_x, list.data[i].moved_y);
                        if (alt != -1)
                        {
                             list.data[j].x += list.data[i].moved_x; //  list.data[i].weight /  list.data[j].weight
                             list.data[j].y += list.data[i].moved_y; //  list.data[i].weight /  list.data[j].weight
                             list.data[j].altitude = alt;
                             list.data[j].a_bouger = 1;   
                        }
                    }
                }
            }
        }
        list.data[i].moved_x = 0;
        list.data[i].moved_y = 0;
        
    }
    for (int i = 0; i <= list.maxid; i++)
    {
        if (list.data[i].pv <= 0)
            continue;
        if (list.data[i].a_bouger == 1)
        {
            int src = (int)list.data[i].y * max_x + (int)list.data[i].x;
	        int ga = (altitude(src)/38)*2;
           // printf ("%d %f %d %d\n",p->inside, list.data[i].altitude, (int)(p->altitude*2)-ga, building_altitude[src][(int)(p->altitude*2)-ga]);
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
