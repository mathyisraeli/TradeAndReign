#include "building.h"


int parse_building(struct building *b, char *line)
{
    int i;
    sscanf(line, "%s %d %d %d %d %c %c %n", b->skin, &b->id, &b->pv, &b->x, &b->y, &b->angle, &b->state, &i);
    return i;
}

int append_building(char *line)
{
    struct building *new = malloc(sizeof(struct building));
    int ret = parse_building(new, line);
    actualise_stat_building(new);
    actualise_building_altitude(new);
    new->next = NULL;
    if (list_building == NULL || list_building->id > new->id)
    {
        new->next = list_building;
        list_building = new;
    }
    else
    {
        struct building *parcour = list_building;
        while (parcour->next != NULL && new->id > parcour->next->id)
            parcour = parcour->next;
        new->next = parcour->next;
        parcour->next = new;
    }
    should_i_call_my_computer_work = '1';
    return ret;
}

struct building *find_building_by_id(int id)
{
	struct building *parcour = list_building;
	while (parcour != NULL)
	{
		if (parcour->id == id)
		{
			return parcour;
		}
		parcour = parcour->next;
	}
	return NULL;
}

struct building *destruction(void)
{
	struct building *tmp = list_building;
	struct building *prev;
	while (tmp != NULL && tmp->pv <= 0)
	{
        list_disp = deleteKey(tmp->id);
		list_building = list_building->next;
		remove_building_altitude(tmp);
		free(tmp);
		tmp = list_building;
        should_i_call_my_computer_work = '1';

	}
	while (tmp != NULL)
	{
		while (tmp != NULL && tmp->pv > 0)
		{
			prev = tmp;
			tmp = tmp->next;
		}
		if (tmp == NULL)
			return list_building;
        list_disp = deleteKey(tmp->id);
		prev->next = tmp->next;
		remove_building_altitude(tmp);
        free(tmp);
		tmp = prev->next;
		should_i_call_my_computer_work = '1';
	}
	return list_building;
}

void remove_building_altitude(struct building *parcour)
{
    if (strcmp(parcour->skin, "111") == 0)
    {   
        building_id[(int)(parcour->y) * max_x + (int)(parcour->x)] =  -1;
        building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x)] = -1;
        building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x)] = -1;
        building_id[(int)(parcour->y) * max_x + (int)(parcour->x-2)] = -1;
        building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-2)] = -1;
        building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x-2)] = -1;
        building_id[(int)(parcour->y) * max_x + (int)(parcour->x)-1] = -1;
        building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x)-1] = -1;
        building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x)-1] = -1;
    }
    else if (strcmp(parcour->skin, "125") == 0)
    {
        building_id[(int)(parcour->y) * max_x + (int)(parcour->x)] =  -1;
        building_id[(int)(parcour->y) * max_x + (int)(parcour->x+1)] = -1;
        building_id[(int)(parcour->y) * max_x + (int)(parcour->x+2)] = -1;
        building_id[(int)(parcour->y) * max_x + (int)(parcour->x+3)] = -1;
        building_id[(int)(parcour->y) * max_x + (int)(parcour->x+4)] = -1;
    }
    else if (strcmp(parcour->skin, "131")  == 0)
    {
        if (parcour->angle == 'd')
        {
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x+1)] = -1;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x+1)] = -1;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x+1)] = -1;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x+1)] = -1;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x+1)] = -1;
            building_id[(int)(parcour->y-3) * max_x + (int)(parcour->x+1)] = -1;
            building_id[(int)(parcour->y+3) * max_x + (int)(parcour->x)] = -1;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x)] = -1;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x)] = -1;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x)] = -1;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x)] = -1;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x)] = -1;
            building_id[(int)(parcour->y-3) * max_x + (int)(parcour->x)] = -1;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x-1)] = -1;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x-1)] = -1;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x-1)] = -1;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-1)] = -1;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x-1)] = -1;
            building_id[(int)(parcour->y-3) * max_x + (int)(parcour->x-1)] = -1;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x+2)] = -1;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x+2)] = -1;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x+2)] = -1;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x+2)] = -1;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x+2)] = -1;
            building_id[(int)(parcour->y-3) * max_x + (int)(parcour->x+2)] = -1;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x-2)] = -1;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x-2)] = -1;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x-2)] = -1;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-2)] = -1;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x-2)] = -1;
            building_id[(int)(parcour->y-3) * max_x + (int)(parcour->x-2)] = -1;
            building_id[(int)(parcour->y-4) * max_x + (int)(parcour->x+1)] = -1;
            building_id[(int)(parcour->y-4) * max_x + (int)(parcour->x)] = -1;
            building_id[(int)(parcour->y-4) * max_x + (int)(parcour->x-1)] = -1;
            building_id[(int)(parcour->y+3) * max_x + (int)(parcour->x+1)] = -1;
            building_id[(int)(parcour->y+4) * max_x + (int)(parcour->x)] = -1;
            building_id[(int)(parcour->y+3) * max_x + (int)(parcour->x-1)] = -1;
        }
        else if (parcour->angle=='h')
        {
            building_id[(int)(parcour->y+3) * max_x + (int)(parcour->x+2)] = -1;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x+2)] = -1;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x+2)] = -1;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x+2)] = -1;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x+2)] = -1;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x+2)] = -1;
            building_id[(int)(parcour->y+3) * max_x + (int)(parcour->x-2)] = -1;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x-2)] = -1;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x-2)] = -1;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x-2)] = -1;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-2)] = -1;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x-2)] = -1;
            building_id[(int)(parcour->y+4) * max_x + (int)(parcour->x+1)] = -1;
            building_id[(int)(parcour->y+4) * max_x + (int)(parcour->x)] = -1;
            building_id[(int)(parcour->y+4) * max_x + (int)(parcour->x-1)] = -1;
            building_id[(int)(parcour->y+3) * max_x + (int)(parcour->x-1)] = -1;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x-1)] = -1;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x-1)] = -1;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x-1)] = -1;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-1)] = -1;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x-1)] = -1;
            building_id[(int)(parcour->y+3) * max_x + (int)(parcour->x)] = -1;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x)] = -1;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x)] = -1;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x)] = -1;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x)] = -1;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x)] = -1;
            building_id[(int)(parcour->y-3) * max_x + (int)(parcour->x)] = -1;
            building_id[(int)(parcour->y+3) * max_x + (int)(parcour->x+1)] = -1;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x+1)] = -1;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x+1)] = -1;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x+1)] = -1;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x+1)] = -1;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x+1)] = -1;
            building_id[(int)(parcour->y-3) * max_x + (int)(parcour->x+1)] = -1;
            building_id[(int)(parcour->y-3) * max_x + (int)(parcour->x-1)] = -1;
            building_id[(int)(parcour->y-4) * max_x + (int)(parcour->x)] = -1;  
        }
        else if (parcour->angle == 'f') // k
        {
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x-2)] = -1;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x-1)] = -1;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x)] = -1;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x+1)] = -1;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x+2)] = -1;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x+3)] = -1;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x-3)] = -1;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x-2)] = -1;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x-1)] = -1;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x)] = -1;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x+1)] = -1;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x+2)] = -1;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x+3)] = -1;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-2)] = -1;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-1)] = -1;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x)] = -1;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x+1)] = -1;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x+2)] = -1;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x+3)] = -1;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x-3)] = -1;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x-4)] = -1;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-3)] = -1;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x+4)] = -1;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x+4)] = -1;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x+4)] = -1;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x+3)] = -1;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x+2)] = -1;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x+1)] = -1;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x)] = -1;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x-1)] = -1;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x-2)] = -1;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x+3)] = -1;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x+2)] = -1;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x+1)] = -1;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x)] = -1;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x-1)] = -1;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x-2)] = -1;

        }
        else if (parcour->angle == 'b') // e
        {
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x-3)] = -1;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x-2)] = -1;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x-1)] = -1;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x)] = -1;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x+1)] = -1;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x+2)] = -1;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x-3)] = -1;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x-2)] = -1;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x-1)] = -1;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x)] = -1;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x+1)] = -1;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x+2)] = -1;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x+3)] = -1;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-3)] = -1;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-2)] = -1;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-1)] = -1;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x)] = -1;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x+1)] = -1;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x+2)] = -1;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x+3)] = -1;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x+4)] = -1;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x+3)] = -1;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x-4)] = -1;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x-4)] = -1;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-4)] = -1;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x+2)] = -1;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x+1)] = -1;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x)] = -1;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x-1)] = -1;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x-2)] = -1;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x-3)] = -1;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x+2)] = -1;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x+1)] = -1;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x)] = -1;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x-1)] = -1;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x-2)] = -1;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x-3)] = -1;
        }
    }
}

void actualise_building_altitude(struct building *parcour)
{    
    
    if (strcmp(parcour->skin, "111") == 0)
    {   
        building_id[(int)(parcour->y) * max_x + (int)(parcour->x)] =  parcour->id;
        building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x)] = parcour->id;
        building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x)] = parcour->id;
        building_id[(int)(parcour->y) * max_x + (int)(parcour->x-2)] = parcour->id;
        building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-2)] = parcour->id;
        building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x-2)] = parcour->id;
        building_id[(int)(parcour->y) * max_x + (int)(parcour->x)-1] = parcour->id;
        building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x)-1] = parcour->id;
        building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x)-1] = parcour->id;
    
        building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x)][0] = 10;
        building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x)][0] = 10;
        building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x)][0] = 10;
        building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-2)][0] = 11;
        building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-2)][0] = 11;
        building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-2)][0] = 11;
        building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x)-1][0] = 01;
        building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x)-1][0] = 11;
        building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x)-1][0] = 11;

        building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x)][1] = 10;
        building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x)][1] = 10;
        building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-2)][1] = 11;
        building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-2)][1] = 11;
        building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-2)][1] = 11;
        building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x)-1][1] = 01;
        building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x)-1][1] = 11;
        building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x)-1][1] = 11;

        building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x)][2] = 1;
        building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-2)][2] = 1;
        building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-2)][2] = 1;
        building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-2)][2] = 1;
        building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x)-1][2] = 01;
        building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x)-1][2] = 1;
        building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x)-1][2] = 1;

        building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-2)][3] = 1;
        building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-2)][3] = 1;
        building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-2)][3] = 1;
        building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x)-1][3] = 01;
        building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x)-1][3] = 1;
        building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x)-1][3] = 1;

        building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-1)][4] = 2;
    }

    else if (strcmp(parcour->skin, "125") == 0)
    {
        building_id[(int)(parcour->y) * max_x + (int)(parcour->x)] =  parcour->id;
        building_id[(int)(parcour->y) * max_x + (int)(parcour->x+1)] = parcour->id;
        building_id[(int)(parcour->y) * max_x + (int)(parcour->x+2)] = parcour->id;
        building_id[(int)(parcour->y) * max_x + (int)(parcour->x+3)] = parcour->id;
        building_id[(int)(parcour->y) * max_x + (int)(parcour->x+4)] = parcour->id;
        
        building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x)][0] = 1;
        building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+4)][0] = 1;
        building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x)][1] = 1;
        building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+4)][1] = 1;
        building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x)][2] = 1;
        building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+4)][2] = 1;
        building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x)][3] = 1;
        building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+4)][3] = 1;
        building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x)][4] = 1;
        building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+1)][4] = 1;
        building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+2)][4] = 1;
        building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+3)][4] = 1;
        building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+4)][4] = 1;
        
    }
    else if (strcmp(parcour->skin, "131")  == 0)
    {
        if (parcour->angle == 'd')
        {
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x+1)] = parcour->id;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x+1)] = parcour->id;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x+1)] = parcour->id;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x+1)] = parcour->id;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x+1)] = parcour->id;
            building_id[(int)(parcour->y-3) * max_x + (int)(parcour->x+1)] = parcour->id;
            building_id[(int)(parcour->y+3) * max_x + (int)(parcour->x)] = parcour->id;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x)] = parcour->id;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x)] = parcour->id;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x)] = parcour->id;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x)] = parcour->id;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x)] = parcour->id;
            building_id[(int)(parcour->y-3) * max_x + (int)(parcour->x)] = parcour->id;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x-1)] = parcour->id;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x-1)] = parcour->id;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x-1)] = parcour->id;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-1)] = parcour->id;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x-1)] = parcour->id;
            building_id[(int)(parcour->y-3) * max_x + (int)(parcour->x-1)] = parcour->id;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x+2)] = parcour->id;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x+2)] = parcour->id;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x+2)] = parcour->id;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x+2)] = parcour->id;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x+2)] = parcour->id;
            building_id[(int)(parcour->y-3) * max_x + (int)(parcour->x+2)] = parcour->id;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x-2)] = parcour->id;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x-2)] = parcour->id;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x-2)] = parcour->id;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-2)] = parcour->id;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x-2)] = parcour->id;
            building_id[(int)(parcour->y-3) * max_x + (int)(parcour->x-2)] = parcour->id;
            building_id[(int)(parcour->y-4) * max_x + (int)(parcour->x+1)] = parcour->id;
            building_id[(int)(parcour->y-4) * max_x + (int)(parcour->x)] = parcour->id;
            building_id[(int)(parcour->y-4) * max_x + (int)(parcour->x-1)] = parcour->id;
            building_id[(int)(parcour->y+3) * max_x + (int)(parcour->x+1)] = parcour->id;
            building_id[(int)(parcour->y+4) * max_x + (int)(parcour->x)] = parcour->id;
            building_id[(int)(parcour->y+3) * max_x + (int)(parcour->x-1)] = parcour->id;
        }
        else if (parcour->angle=='h')
        {
            building_id[(int)(parcour->y+3) * max_x + (int)(parcour->x+2)] = parcour->id;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x+2)] = parcour->id;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x+2)] = parcour->id;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x+2)] = parcour->id;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x+2)] = parcour->id;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x+2)] = parcour->id;
            building_id[(int)(parcour->y+3) * max_x + (int)(parcour->x-2)] = parcour->id;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x-2)] = parcour->id;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x-2)] = parcour->id;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x-2)] = parcour->id;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-2)] = parcour->id;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x-2)] = parcour->id;
            building_id[(int)(parcour->y+4) * max_x + (int)(parcour->x+1)] = parcour->id;
            building_id[(int)(parcour->y+4) * max_x + (int)(parcour->x)] = parcour->id;
            building_id[(int)(parcour->y+4) * max_x + (int)(parcour->x-1)] = parcour->id;
            building_id[(int)(parcour->y+3) * max_x + (int)(parcour->x-1)] = parcour->id;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x-1)] = parcour->id;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x-1)] = parcour->id;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x-1)] = parcour->id;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-1)] = parcour->id;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x-1)] = parcour->id;
            building_id[(int)(parcour->y+3) * max_x + (int)(parcour->x)] = parcour->id;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x)] = parcour->id;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x)] = parcour->id;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x)] = parcour->id;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x)] = parcour->id;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x)] = parcour->id;
            building_id[(int)(parcour->y-3) * max_x + (int)(parcour->x)] = parcour->id;
            building_id[(int)(parcour->y+3) * max_x + (int)(parcour->x+1)] = parcour->id;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x+1)] = parcour->id;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x+1)] = parcour->id;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x+1)] = parcour->id;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x+1)] = parcour->id;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x+1)] = parcour->id;
            building_id[(int)(parcour->y-3) * max_x + (int)(parcour->x+1)] = parcour->id;
            building_id[(int)(parcour->y-3) * max_x + (int)(parcour->x-1)] = parcour->id;
            building_id[(int)(parcour->y-4) * max_x + (int)(parcour->x)] = parcour->id;  
        }
        else if (parcour->angle == 'f') // k
        {
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x-2)] = parcour->id;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x-1)] = parcour->id;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x)] = parcour->id;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x+1)] = parcour->id;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x+2)] = parcour->id;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x+3)] = parcour->id;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x-3)] = parcour->id;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x-2)] = parcour->id;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x-1)] = parcour->id;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x)] = parcour->id;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x+1)] = parcour->id;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x+2)] = parcour->id;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x+3)] = parcour->id;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-2)] = parcour->id;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-1)] = parcour->id;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x)] = parcour->id;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x+1)] = parcour->id;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x+2)] = parcour->id;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x+3)] = parcour->id;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x-3)] = parcour->id;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x-4)] = parcour->id;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-3)] = parcour->id;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x+4)] = parcour->id;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x+4)] = parcour->id;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x+4)] = parcour->id;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x+3)] = parcour->id;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x+2)] = parcour->id;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x+1)] = parcour->id;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x)] = parcour->id;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x-1)] = parcour->id;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x-2)] = parcour->id;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x+3)] = parcour->id;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x+2)] = parcour->id;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x+1)] = parcour->id;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x)] = parcour->id;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x-1)] = parcour->id;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x-2)] = parcour->id;

        }
        else if (parcour->angle == 'b') 
        {
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x-3)] = parcour->id;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x-2)] = parcour->id;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x-1)] = parcour->id;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x)] = parcour->id;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x+1)] = parcour->id;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x+2)] = parcour->id;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x-3)] = parcour->id;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x-2)] = parcour->id;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x-1)] = parcour->id;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x)] = parcour->id;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x+1)] = parcour->id;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x+2)] = parcour->id;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x+3)] = parcour->id;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-3)] = parcour->id;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-2)] = parcour->id;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-1)] = parcour->id;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x)] = parcour->id;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x+1)] = parcour->id;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x+2)] = parcour->id;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x+3)] = parcour->id;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x+4)] = parcour->id;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x+3)] = parcour->id;
            building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x-4)] = parcour->id;
            building_id[(int)(parcour->y) * max_x + (int)(parcour->x-4)] = parcour->id;
            building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-4)] = parcour->id;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x+2)] = parcour->id;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x+1)] = parcour->id;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x)] = parcour->id;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x-1)] = parcour->id;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x-2)] = parcour->id;
            building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x-3)] = parcour->id;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x+2)] = parcour->id;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x+1)] = parcour->id;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x)] = parcour->id;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x-1)] = parcour->id;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x-2)] = parcour->id;
            building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x-3)] = parcour->id;
        }
    }
    else if (strcmp(parcour->skin, "141") == 0)
        building_id[(int)(parcour->y) * max_x + (int)(parcour->x)] = parcour->id;

}