#include "building.h"

int parse_new_building(struct building *b, char *line, char *skin, int id)
{
    int i;
    sscanf(line, "%d %d %d %c %c %n",&b->pv, &b->x, &b->y, &b->angle,&b->state,&i);
    if(id == -1)
        b->id = find_smalest_valid_id_building(0);
    else
        b->id = id;
    strcpy(b->skin ,skin);
    return i + 1;
}

struct building *get_ptr_from_id_building(int id)
{
    struct building *parcour = list_building;
    while (parcour != NULL)
    {
        if (parcour->id == id)
            return parcour;
        parcour = parcour->next;
    }
    return NULL;
}

int append_building(char *line, char *skin, int id)
{
    struct building *new = malloc(sizeof(struct building));
    int ret = parse_new_building(new, line, skin, id);
    new->next = NULL;
    new->a_bouger = 1;
    if (list_building == NULL)
        list_building = new;
    else
    {
		struct building *parcour = list_building;
		while (parcour->next != NULL)
			parcour = parcour->next;
        parcour->next = new;
    }
    printf ("%d\n", ret);
    return ret;
}

void create_building(int x, int y,char angle, char state, char skin[4], int pv)
{
    struct building *new = malloc(sizeof(struct building));
    if (list_building == NULL)
        list_building = new;
    else
    {
		struct building *parcour = list_building;
		while (parcour->next != NULL)
			parcour = parcour->next;
        parcour->next = new;
    }
    new->id = find_smalest_valid_id_building(0);
    new->a_bouger = 1;
    new->x = x;
    new->y = y;
    new->angle = angle;
    new->state = state;
    strcpy(new->skin, skin);
    new->pv = pv;
}

//1st 1 if it's colider outside
//2nd 1 if we can ignore outisde colider
//3rd 1 if it's colider inside
void actualise_building_altitude(void)
{
    for (struct building *parcour = list_building; parcour != NULL; parcour = parcour->next)
    {     
        if (parcour->a_bouger != 0)
        {
            if (strcmp(parcour->skin, "141") == 0)
            {
                building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x)][0] = 101;
                building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x)][1] = 101;
                building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x)][2] = 101;
                building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x)][3] = 101;
                building_id[(int)(parcour->y) * max_x + (int)(parcour->x)] = parcour->id;


            }

            if (strcmp(parcour->skin, "111") == 0)
            {
                building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x)][0] = 101;
                building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x)][0] = 101;
                building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x)][0] = 101;
                building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-2)][0] = 110;
                building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-2)][0] = 110;
                building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-2)][0] = 110;
                building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x)-1][0] = 10;
                building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x)-1][0] = 110;
                building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x)-1][0] = 110;

                building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x)][1] = 101;
                building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x)][1] = 101;
                building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-2)][1] = 110;
                building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-2)][1] = 110;
                building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-2)][1] = 110;
                building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x)-1][1] = 10;
                building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x)-1][1] = 110;
                building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x)-1][1] = 110;

                building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x)][2] = 101;
                building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-2)][2] = 110;
                building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-2)][2] = 110;
                building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-2)][2] = 110;
                building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x)-1][2] = 10;
                building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x)-1][2] = 110;
                building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x)-1][2] = 110;

                building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-2)][3] = 110;
                building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-2)][3] = 110;
                building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-2)][3] = 110;
                building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x)-1][3] = 10;
                building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x)-1][3] = 110;
                building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x)-1][3] = 110;

                building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-1)][4] = 210;

                building_id[(int)(parcour->y) * max_x + (int)(parcour->x-2)] = parcour->id;
                building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-2)] = parcour->id;
                building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x-2)] = parcour->id;
                building_id[(int)(parcour->y) * max_x + (int)(parcour->x)-1] = parcour->id;
                building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x)-1] = parcour->id;
                building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x)-1] = parcour->id;
                building_id[(int)(parcour->y) * max_x + (int)(parcour->x)] = parcour->id;
                building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x)] = parcour->id;
                building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x)] = parcour->id;
            }
            if (strcmp(parcour->skin, "113") == 0)
            {
                building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-5)][0] = 110;
                building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-5)][1] = 110;
                building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-5)][2] = 110;
                building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-5)][3] = 110;
                building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-5)][4] = 110;

                building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-1)][0] = 110;
                building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-1)][1] = 110;
                building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-1)][2] = 110;
                building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-1)][3] = 110;
                building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-1)][4] = 110;

                building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-2)][0] = 110;
                building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-2)][1] = 110;
                building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-2)][2] = 110;
                building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x)-2][3] = 110;
                building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x)-2][4] = 110;

                building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x)-3][0] = 110;
                building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x)-3][1] = 110;
                building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x)-3][2] = 110;
                building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x)-3][3] = 110;
                building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x)-3][4] = 110;

                building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x)-4][0] = 110;
                building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x)-4][1] = 110;
                building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x)-4][2] = 110;
                building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x)-4][3] = 110;
                building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x)-4][4] = 110;

                building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x)][0] = 10;
                building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x)][1] = 10;
                building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x)][2] = 10;
                building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x)][3] = 10;
                building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x)][4] = 210;

                building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x)][0] = 110;
                building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x)][1] = 110;
                building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x)][2] = 110;
                building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x)][3] = 110;
                building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x)][4] = 110;
                building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x)][5] = 110;

                building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-1)][0] = 10;
                building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-1)][1] = 10;
                building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-1)][2] = 10;
                building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-1)][3] = 10;
                building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-1)][4] = 10;
                building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-1)][5] = 101;

                building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-2)][0] = 10;
                building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-2)][1] = 10;
                building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-2)][2] = 10;
                building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-2)][3] = 10;
                building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-2)][4] = 10;
                building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-2)][5] = 101;

                building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-3)][0] = 10;
                building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-3)][1] = 10;
                building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-3)][2] = 10;
                building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-3)][3] = 10;
                building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-3)][4] = 10;
                building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-3)][5] = 101;

                building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-4)][0] = 10;
                building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-4)][1] = 10;
                building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-4)][2] = 10;
                building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-4)][3] = 10;
                building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-4)][4] = 10;
                building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-4)][5] = 101;

                building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-5)][0] = 110;
                building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-5)][1] = 110;
                building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-5)][2] = 110;
                building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-5)][3] = 110;
                building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-5)][4] = 110;
                building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-5)][5] = 110;

                building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x)][0] = 110;
                building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x)][1] = 110;
                building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x)][2] = 110;
                building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x)][3] = 110;
                building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x)][4] = 110;
                building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x)][5] = 110;
                building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x)][6] = 110;

                building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-1)][0] = 10;
                building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-1)][1] = 10;
                building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-1)][2] = 10;
                building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-1)][3] = 10;
                building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-1)][4] = 10;
                building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-1)][5] = 101;
                building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-1)][6] = 110;

                building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-2)][0] = 10;
                building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-2)][1] = 10;
                building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-2)][2] = 10;
                building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-2)][3] = 10;
                building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-2)][4] = 10;
                building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-2)][5] = 101;
                building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-2)][6] = 110;

                building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-3)][0] = 10;
                building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-3)][1] = 10;
                building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-3)][2] = 10;
                building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-3)][3] = 10;
                building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-3)][4] = 10;
                building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-3)][5] = 101;
                building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-3)][6] = 110;

                building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-4)][0] = 10;
                building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-4)][1] = 10;
                building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-4)][2] = 10;
                building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-4)][3] = 10;
                building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-4)][4] = 10;
                building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-4)][5] = 101;
                building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-4)][6] = 110;

                building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-5)][0] = 110;
                building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-5)][1] = 110;
                building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-5)][2] = 110;
                building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-5)][3] = 110;
                building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-5)][4] = 110;
                building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-5)][5] = 110;
                building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-5)][6] = 110;
                
                building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x)][0] = 110;
                building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x)][1] = 110;
                building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x)][2] = 110;
                building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x)][3] = 110;
                building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x)][4] = 110;
                building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x)][5] = 110;

                building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x-1)][0] = 10;
                building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x-1)][1] = 10;
                building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x-1)][2] = 10;
                building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x-1)][3] = 10;
                building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x-1)][4] = 10;
                building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x-1)][5] = 101;

                building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x-2)][0] = 10;
                building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x-2)][1] = 10;
                building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x-2)][2] = 10;
                building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x-2)][3] = 10;
                building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x-2)][4] = 10;
                building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x-2)][5] = 101;

                building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x-3)][0] = 10;
                building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x-3)][1] = 10;
                building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x-3)][2] = 10;
                building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x-3)][3] = 10;
                building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x-3)][4] = 10;
                building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x-3)][5] = 101;

                building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x-4)][0] = 10;
                building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x-4)][1] = 10;
                building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x-4)][2] = 10;
                building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x-4)][3] = 10;
                building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x-4)][4] = 10;
                building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x-4)][5] = 101;

                building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x-5)][0] = 110;
                building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x-5)][1] = 110;
                building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x-5)][2] = 110;
                building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x-5)][3] = 110;
                building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x-5)][4] = 110;
                building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x-5)][5] = 110;
                
                building_altitude[(int)(parcour->y-4) * max_x + (int)(parcour->x)][0] = 110;
                building_altitude[(int)(parcour->y-4) * max_x + (int)(parcour->x)][1] = 110;
                building_altitude[(int)(parcour->y-4) * max_x + (int)(parcour->x)][2] = 110;
                building_altitude[(int)(parcour->y-4) * max_x + (int)(parcour->x)][3] = 110;
                building_altitude[(int)(parcour->y-4) * max_x + (int)(parcour->x)][4] = 110;
                building_altitude[(int)(parcour->y-4) * max_x + (int)(parcour->x)][5] = 110;

                building_altitude[(int)(parcour->y-4) * max_x + (int)(parcour->x-1)][0] = 10;
                building_altitude[(int)(parcour->y-4) * max_x + (int)(parcour->x-1)][1] = 10;
                building_altitude[(int)(parcour->y-4) * max_x + (int)(parcour->x-1)][2] = 10;
                building_altitude[(int)(parcour->y-4) * max_x + (int)(parcour->x-1)][3] = 10;
                building_altitude[(int)(parcour->y-4) * max_x + (int)(parcour->x-1)][4] = 10;
                building_altitude[(int)(parcour->y-4) * max_x + (int)(parcour->x-1)][5] = 101;

                building_altitude[(int)(parcour->y-4) * max_x + (int)(parcour->x-2)][0] = 10;
                building_altitude[(int)(parcour->y-4) * max_x + (int)(parcour->x-2)][1] = 10;
                building_altitude[(int)(parcour->y-4) * max_x + (int)(parcour->x-2)][2] = 10;
                building_altitude[(int)(parcour->y-4) * max_x + (int)(parcour->x-2)][3] = 10;
                building_altitude[(int)(parcour->y-4) * max_x + (int)(parcour->x-2)][4] = 10;
                building_altitude[(int)(parcour->y-4) * max_x + (int)(parcour->x-2)][5] = 101;

                building_altitude[(int)(parcour->y-4) * max_x + (int)(parcour->x-3)][0] = 10;
                building_altitude[(int)(parcour->y-4) * max_x + (int)(parcour->x-3)][1] = 10;
                building_altitude[(int)(parcour->y-4) * max_x + (int)(parcour->x-3)][2] = 10;
                building_altitude[(int)(parcour->y-4) * max_x + (int)(parcour->x-3)][3] = 10;
                building_altitude[(int)(parcour->y-4) * max_x + (int)(parcour->x-3)][4] = 10;
                building_altitude[(int)(parcour->y-4) * max_x + (int)(parcour->x-3)][5] = 101;

                building_altitude[(int)(parcour->y-4) * max_x + (int)(parcour->x-4)][0] = 10;
                building_altitude[(int)(parcour->y-4) * max_x + (int)(parcour->x-4)][1] = 10;
                building_altitude[(int)(parcour->y-4) * max_x + (int)(parcour->x-4)][2] = 10;
                building_altitude[(int)(parcour->y-4) * max_x + (int)(parcour->x-4)][3] = 10;
                building_altitude[(int)(parcour->y-4) * max_x + (int)(parcour->x-4)][4] = 10;
                building_altitude[(int)(parcour->y-4) * max_x + (int)(parcour->x-4)][5] = 101;

                building_altitude[(int)(parcour->y-4) * max_x + (int)(parcour->x-5)][0] = 110;
                building_altitude[(int)(parcour->y-4) * max_x + (int)(parcour->x-5)][1] = 110;
                building_altitude[(int)(parcour->y-4) * max_x + (int)(parcour->x-5)][2] = 110;
                building_altitude[(int)(parcour->y-4) * max_x + (int)(parcour->x-5)][3] = 110;
                building_altitude[(int)(parcour->y-4) * max_x + (int)(parcour->x-5)][4] = 110;
                building_altitude[(int)(parcour->y-4) * max_x + (int)(parcour->x-5)][5] = 110;

                building_altitude[(int)(parcour->y-5) * max_x + (int)(parcour->x-5)][0] = 110;
                building_altitude[(int)(parcour->y-5) * max_x + (int)(parcour->x-5)][1] = 110;
                building_altitude[(int)(parcour->y-5) * max_x + (int)(parcour->x-5)][2] = 110;
                building_altitude[(int)(parcour->y-5) * max_x + (int)(parcour->x-5)][3] = 110;
                building_altitude[(int)(parcour->y-5) * max_x + (int)(parcour->x-5)][4] = 110;

                building_altitude[(int)(parcour->y-5) * max_x + (int)(parcour->x-1)][0] = 110;
                building_altitude[(int)(parcour->y-5) * max_x + (int)(parcour->x-1)][1] = 110;
                building_altitude[(int)(parcour->y-5) * max_x + (int)(parcour->x-1)][2] = 110;
                building_altitude[(int)(parcour->y-5) * max_x + (int)(parcour->x-1)][3] = 110;
                building_altitude[(int)(parcour->y-5) * max_x + (int)(parcour->x-1)][4] = 110;

                building_altitude[(int)(parcour->y-5) * max_x + (int)(parcour->x-2)][0] = 110;
                building_altitude[(int)(parcour->y-5) * max_x + (int)(parcour->x-2)][1] = 110;
                building_altitude[(int)(parcour->y-5) * max_x + (int)(parcour->x-2)][2] = 110;
                building_altitude[(int)(parcour->y-5) * max_x + (int)(parcour->x)-2][3] = 110;
                building_altitude[(int)(parcour->y-5) * max_x + (int)(parcour->x)-2][4] = 110;

                building_altitude[(int)(parcour->y-5) * max_x + (int)(parcour->x)-3][0] = 110;
                building_altitude[(int)(parcour->y-5) * max_x + (int)(parcour->x)-3][1] = 110;
                building_altitude[(int)(parcour->y-5) * max_x + (int)(parcour->x)-3][2] = 110;
                building_altitude[(int)(parcour->y-5) * max_x + (int)(parcour->x)-3][3] = 110;
                building_altitude[(int)(parcour->y-5) * max_x + (int)(parcour->x)-3][4] = 110;

                building_altitude[(int)(parcour->y-5) * max_x + (int)(parcour->x)-4][0] = 110;
                building_altitude[(int)(parcour->y-5) * max_x + (int)(parcour->x)-4][1] = 110;
                building_altitude[(int)(parcour->y-5) * max_x + (int)(parcour->x)-4][2] = 110;
                building_altitude[(int)(parcour->y-5) * max_x + (int)(parcour->x)-4][3] = 110;
                building_altitude[(int)(parcour->y-5) * max_x + (int)(parcour->x)-4][4] = 110;

                building_altitude[(int)(parcour->y-5) * max_x + (int)(parcour->x)][0] = 110;
                building_altitude[(int)(parcour->y-5) * max_x + (int)(parcour->x)][1] = 110;
                building_altitude[(int)(parcour->y-5) * max_x + (int)(parcour->x)][2] = 110;
                building_altitude[(int)(parcour->y-5) * max_x + (int)(parcour->x)][3] = 110;
                building_altitude[(int)(parcour->y-5) * max_x + (int)(parcour->x)][4] = 110;

                building_id[(int)(parcour->y) * max_x + (int)(parcour->x)] = parcour->id;
                building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x)] = parcour->id;
                building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x)] = parcour->id;
                building_id[(int)(parcour->y-3) * max_x + (int)(parcour->x)] = parcour->id;
                building_id[(int)(parcour->y-4) * max_x + (int)(parcour->x)] = parcour->id;
                building_id[(int)(parcour->y-5) * max_x + (int)(parcour->x)] = parcour->id;
                building_id[(int)(parcour->y) * max_x + (int)(parcour->x-1)] = parcour->id;
                building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-1)] = parcour->id;
                building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x-1)] = parcour->id;
                building_id[(int)(parcour->y-3) * max_x + (int)(parcour->x-1)] = parcour->id;
                building_id[(int)(parcour->y-4) * max_x + (int)(parcour->x-1)] = parcour->id;
                building_id[(int)(parcour->y-5) * max_x + (int)(parcour->x-1)] = parcour->id;
                building_id[(int)(parcour->y) * max_x + (int)(parcour->x-2)] = parcour->id;
                building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-2)] = parcour->id;
                building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x-2)] = parcour->id;
                building_id[(int)(parcour->y-3) * max_x + (int)(parcour->x-2)] = parcour->id;
                building_id[(int)(parcour->y-4) * max_x + (int)(parcour->x-2)] = parcour->id;
                building_id[(int)(parcour->y-5) * max_x + (int)(parcour->x-2)] = parcour->id;
                building_id[(int)(parcour->y) * max_x + (int)(parcour->x-3)] = parcour->id;
                building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-3)] = parcour->id;
                building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x-3)] = parcour->id;
                building_id[(int)(parcour->y-3) * max_x + (int)(parcour->x-3)] = parcour->id;
                building_id[(int)(parcour->y-4) * max_x + (int)(parcour->x-3)] = parcour->id;
                building_id[(int)(parcour->y-5) * max_x + (int)(parcour->x-3)] = parcour->id;
                building_id[(int)(parcour->y) * max_x + (int)(parcour->x-4)] = parcour->id;
                building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-4)] = parcour->id;
                building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x-4)] = parcour->id;
                building_id[(int)(parcour->y-3) * max_x + (int)(parcour->x-4)] = parcour->id;
                building_id[(int)(parcour->y-4) * max_x + (int)(parcour->x-4)] = parcour->id;
                building_id[(int)(parcour->y-5) * max_x + (int)(parcour->x-4)] = parcour->id;
                building_id[(int)(parcour->y) * max_x + (int)(parcour->x-5)] = parcour->id;
                building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-5)] = parcour->id;
                building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x-5)] = parcour->id;
                building_id[(int)(parcour->y-3) * max_x + (int)(parcour->x-5)] = parcour->id;
                building_id[(int)(parcour->y-4) * max_x + (int)(parcour->x-5)] = parcour->id;
                building_id[(int)(parcour->y-5) * max_x + (int)(parcour->x-5)] = parcour->id;
                
            }

            else if (strcmp(parcour->skin, "125") == 0)
            {
                
                building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x)][0] = 100;
                building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+4)][0] = 100;
                building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x)][1] = 100;
                building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+4)][1] = 100;
                building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x)][2] = 100;
                building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+4)][2] = 100;
                building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x)][3] = 100;
                building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+4)][3] = 100;
                building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x)][4] = 100;
                building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+1)][4] = 100;
                building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+2)][4] = 100;
                building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+3)][4] = 100;
                building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+4)][4] = 100;

                building_id[(int)(parcour->y) * max_x + (int)(parcour->x)] = parcour->id;
                building_id[(int)(parcour->y) * max_x + (int)(parcour->x)+1] = parcour->id;
                building_id[(int)(parcour->y) * max_x + (int)(parcour->x)+2] = parcour->id;
                building_id[(int)(parcour->y) * max_x + (int)(parcour->x)+3] = parcour->id;
                building_id[(int)(parcour->y) * max_x + (int)(parcour->x)+4] = parcour->id;
                
            }
            else if (strcmp(parcour->skin, "131") == 0)
            { 
                if (parcour->a_bouger == 4)
                {
                    building_id[(int)(parcour->y-4) * max_x + (int)(parcour->x-2)] = -1;
                    building_id[(int)(parcour->y-5) * max_x + (int)(parcour->x-1)] = -1;
                    building_id[(int)(parcour->y-5) * max_x + (int)(parcour->x)] = -1;
                    building_id[(int)(parcour->y-5) * max_x + (int)(parcour->x+1)] = -1;
                    building_id[(int)(parcour->y-4) * max_x + (int)(parcour->x+2)] = -1;
                    for (int i = 0; i < 40; i++)
                    {
                        building_altitude[(int)(parcour->y-4) * max_x + (int)(parcour->x-2)][i] = 0;
                        building_altitude[(int)(parcour->y-5) * max_x + (int)(parcour->x-1)][i] = 0;
                        building_altitude[(int)(parcour->y-5) * max_x + (int)(parcour->x)][i] = 0;
                        building_altitude[(int)(parcour->y-5) * max_x + (int)(parcour->x+1)][i] = 0;
                        building_altitude[(int)(parcour->y-4) * max_x + (int)(parcour->x+2)][i] = 0;
                    }
                }
                else if (parcour->a_bouger == 5)
                {
                    building_id[(int)(parcour->y+4) * max_x + (int)(parcour->x-2)] = -1;
                    building_id[(int)(parcour->y+5) * max_x + (int)(parcour->x-1)] = -1;
                    building_id[(int)(parcour->y+5) * max_x + (int)(parcour->x)] = -1;
                    building_id[(int)(parcour->y+5) * max_x + (int)(parcour->x+1)] = -1;
                    building_id[(int)(parcour->y+4) * max_x + (int)(parcour->x+2)] = -1;
                    for (int i = 0; i < 40; i++)
                    {
                        building_altitude[(int)(parcour->y+4) * max_x + (int)(parcour->x-2)][i] = 0;
                        building_altitude[(int)(parcour->y+5) * max_x + (int)(parcour->x-1)][i] = 0;
                        building_altitude[(int)(parcour->y+5) * max_x + (int)(parcour->x)][i] = 0;
                        building_altitude[(int)(parcour->y+5) * max_x + (int)(parcour->x+1)][i] = 0;
                        building_altitude[(int)(parcour->y+4) * max_x + (int)(parcour->x+2)][i] = 0;
                    }
                }
                else if (parcour->a_bouger == 2)
                {
                    building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x-4)] = -1;
                    building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x-5)] = -1;
                    building_id[(int)(parcour->y) * max_x + (int)(parcour->x-5)] = -1;
                    building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-5)] = -1;
                    building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x-4)] = -1;
                    for (int i = 0; i < 40; i++)
                    {
                        building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x-4)][i] = 0;
                        building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x-5)][i] = 0;
                        building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-5)][i] = 0;
                        building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-5)][i] = 0;
                        building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-4)][i] = 0;
                    }
                }
                else if (parcour->a_bouger == 3)
                {
                    building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x+4)] = -1;
                    building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x+5)] = -1;
                    building_id[(int)(parcour->y) * max_x + (int)(parcour->x+5)] = -1;
                    building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x+5)] = -1;
                    building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x+4)] = -1;
                    for (int i = 0; i < 40; i++)
                    {
                        building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x+4)][i] = 0;
                        building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x+5)][i] = 0;
                        building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+5)][i] = 0;
                        building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x+5)][i] = 0;
                        building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x+4)][i] = 0;
                    }
                }
                else if (parcour->a_bouger == 6) //a
                {
                    building_id[(int)(parcour->y+3) * max_x + (int)(parcour->x+2)] = -1;
                    building_id[(int)(parcour->y+3) * max_x + (int)(parcour->x+1)] = -1;
                    building_id[(int)(parcour->y+3) * max_x + (int)(parcour->x)] = -1;
                    building_id[(int)(parcour->y+3) * max_x + (int)(parcour->x-1)] = -1;
                    building_id[(int)(parcour->y+3) * max_x + (int)(parcour->x-2)] = -1;
                    building_id[(int)(parcour->y+4) * max_x + (int)(parcour->x+2)] = -1;
                    building_id[(int)(parcour->y+4) * max_x + (int)(parcour->x+1)] = -1;
                    building_id[(int)(parcour->y+4) * max_x + (int)(parcour->x)] = -1;
                    building_id[(int)(parcour->y+4) * max_x + (int)(parcour->x-1)] = -1;
                    building_id[(int)(parcour->y+4) * max_x + (int)(parcour->x-2)] = -1;
                    
                    building_id[(int)(parcour->y-3) * max_x + (int)(parcour->x+2)] = -1;
                    building_id[(int)(parcour->y-3) * max_x + (int)(parcour->x+1)] = -1;
                    building_id[(int)(parcour->y-3) * max_x + (int)(parcour->x)] = -1;
                    building_id[(int)(parcour->y-3) * max_x + (int)(parcour->x-1)] = -1;
                    building_id[(int)(parcour->y-3) * max_x + (int)(parcour->x-2)] = -1;
                    building_id[(int)(parcour->y-4) * max_x + (int)(parcour->x+2)] = -1;
                    building_id[(int)(parcour->y-4) * max_x + (int)(parcour->x+1)] = -1;
                    building_id[(int)(parcour->y-4) * max_x + (int)(parcour->x)] = -1;
                    building_id[(int)(parcour->y-4) * max_x + (int)(parcour->x-1)] = -1;
                    building_id[(int)(parcour->y-4) * max_x + (int)(parcour->x-2)] = -1;
                }
                else if (parcour->a_bouger == 7) // b
                {
                    // Front SUD
                    building_id[(int)(parcour->y+3) * max_x + (int)(parcour->x+2)] = -1;
                    building_id[(int)(parcour->y+3) * max_x + (int)(parcour->x+1)] = -1;
                    building_id[(int)(parcour->y+3) * max_x + (int)(parcour->x)] = -1;
                    building_id[(int)(parcour->y+3) * max_x + (int)(parcour->x-1)] = -1;
                    building_id[(int)(parcour->y+3) * max_x + (int)(parcour->x-2)] = -1;
                    building_id[(int)(parcour->y+4) * max_x + (int)(parcour->x+2)] = -1;
                    building_id[(int)(parcour->y+4) * max_x + (int)(parcour->x+1)] = -1;
                    building_id[(int)(parcour->y+4) * max_x + (int)(parcour->x)] = -1;
                    building_id[(int)(parcour->y+4) * max_x + (int)(parcour->x-1)] = -1;
                    building_id[(int)(parcour->y+4) * max_x + (int)(parcour->x-2)] = -1;
                    
                    building_id[(int)(parcour->y-3) * max_x + (int)(parcour->x+2)] = -1;
                    building_id[(int)(parcour->y-3) * max_x + (int)(parcour->x+1)] = -1;
                    building_id[(int)(parcour->y-3) * max_x + (int)(parcour->x)] = -1;
                    building_id[(int)(parcour->y-3) * max_x + (int)(parcour->x-1)] = -1;
                    building_id[(int)(parcour->y-3) * max_x + (int)(parcour->x-2)] = -1;
                    building_id[(int)(parcour->y-4) * max_x + (int)(parcour->x+2)] = -1;
                    building_id[(int)(parcour->y-4) * max_x + (int)(parcour->x+1)] = -1;
                    building_id[(int)(parcour->y-4) * max_x + (int)(parcour->x)] = -1;
                    building_id[(int)(parcour->y-4) * max_x + (int)(parcour->x-1)] = -1;
                    building_id[(int)(parcour->y-4) * max_x + (int)(parcour->x-2)] = -1;
                }
                else if (parcour->a_bouger == 8) // k
                {
                    building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x+3)] = -1;
                    building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x+3)] = -1;
                    building_id[(int)(parcour->y) * max_x + (int)(parcour->x+3)] = -1;
                    building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x+3)] = -1;
                    building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x+3)] = -1;
                    building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x+4)] = -1;
                    building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x+4)] = -1;
                    building_id[(int)(parcour->y) * max_x + (int)(parcour->x+4)] = -1;
                    building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x+4)] = -1;
                    building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x+4)] = -1;
                    
                    building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x-3)] = -1;
                    building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x-3)] = -1;
                    building_id[(int)(parcour->y) * max_x + (int)(parcour->x-3)] = -1;
                    building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-3)] = -1;
                    building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x-3)] = -1;
                    building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x-4)] = -1;
                    building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x-4)] = -1;
                    building_id[(int)(parcour->y) * max_x + (int)(parcour->x-4)] = -1;
                    building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-4)] = -1;
                    building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x-4)] = -1;

                }
                else if (parcour->a_bouger == 9) // e
                {
                    building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x+3)] = -1;
                    building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x+3)] = -1;
                    building_id[(int)(parcour->y) * max_x + (int)(parcour->x+3)] = -1;
                    building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x+3)] = -1;
                    building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x+3)] = -1;
                    building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x+4)] = -1;
                    building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x+4)] = -1;
                    building_id[(int)(parcour->y) * max_x + (int)(parcour->x+4)] = -1;
                    building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x+4)] = -1;
                    building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x+4)] = -1;
                    
                    building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x-3)] = -1;
                    building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x-3)] = -1;
                    building_id[(int)(parcour->y) * max_x + (int)(parcour->x-3)] = -1;
                    building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-3)] = -1;
                    building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x-3)] = -1;
                    building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x-4)] = -1;
                    building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x-4)] = -1;
                    building_id[(int)(parcour->y) * max_x + (int)(parcour->x-4)] = -1;
                    building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-4)] = -1;
                    building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x-4)] = -1;
                }
                if (parcour->angle == 'a')
                {
                    //Bloc interne 3
                    building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x+1)] = parcour->id;
                    building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x+1)] = parcour->id;
                    building_id[(int)(parcour->y) * max_x + (int)(parcour->x+1)] = parcour->id;
                    building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x+1)] = parcour->id;
                    building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x+1)] = parcour->id;
                    building_id[(int)(parcour->y-3) * max_x + (int)(parcour->x+1)] = parcour->id;

                    //Bloc interne 3
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x+1)][1] = 110;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x+1)][2] = 110;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x+1)][3] = 110;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x+1)][0] = 110;

                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x+1)][1] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x+1)][2] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x+1)][3] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x+1)][0] = 110;

                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+1)][1] = 110;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+1)][2] = 110;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+1)][3] = 110;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+1)][0] = 110;

                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x+1)][1] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x+1)][2] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x+1)][3] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x+1)][0] = 110;

                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x+1)][1] = 110;
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x+1)][2] = 110;
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x+1)][3] = 110;
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x+1)][0] = 110;

                    building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x+1)][1] = 110;
                    building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x+1)][2] = 110;
                    building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x+1)][3] = 110;
                    building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x+1)][0] = 110;

                    //Bloc interne 2
                    building_id[(int)(parcour->y+3) * max_x + (int)(parcour->x)] = parcour->id;
                    building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x)] = parcour->id;
                    building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x)] = parcour->id;
                    building_id[(int)(parcour->y) * max_x + (int)(parcour->x)] = parcour->id;
                    building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x)] = parcour->id;
                    building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x)] = parcour->id;
                    building_id[(int)(parcour->y-3) * max_x + (int)(parcour->x)] = parcour->id;

                    //Bloc interne 2
                    building_altitude[(int)(parcour->y+3) * max_x + (int)(parcour->x)][1] = 110;
                    building_altitude[(int)(parcour->y+3) * max_x + (int)(parcour->x)][2] = 110;
                    building_altitude[(int)(parcour->y+3) * max_x + (int)(parcour->x)][3] = 110;
                    building_altitude[(int)(parcour->y+3) * max_x + (int)(parcour->x)][0] = 110;

                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x)][1] = 110;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x)][2] = 110;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x)][3] = 110;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x)][0] = 110;

                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x)][1] = 101;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x)][2] = 101;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x)][3] = 101;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x)][0] = 101;

                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x)][1] = 11;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x)][2] = 111;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x)][3] = 10;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x)][0] = 11;

                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x)][1] = 11;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x)][2] = 10;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x)][3] = 10;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x)][0] = 11;

                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x)][1] = 10;
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x)][2] = 10;
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x)][3] = 10;/////////////////////////////////
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x)][0] = 11;

                    building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x)][1] = 110;
                    building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x)][2] = 110;
                    building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x)][3] = 110;
                    building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x)][0] = 110;

                    //Bloc interne 1
                    building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x-1)] = parcour->id;
                    building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x-1)] = parcour->id;
                    building_id[(int)(parcour->y) * max_x + (int)(parcour->x-1)] = parcour->id;
                    building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-1)] = parcour->id;
                    building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x-1)] = parcour->id;
                    building_id[(int)(parcour->y-3) * max_x + (int)(parcour->x-1)] = parcour->id;

                    //Bloc interne 1
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x-1)][1] = 110;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x-1)][2] = 110;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x-1)][3] = 110;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x-1)][0] = 110;

                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x-1)][1] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x-1)][2] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x-1)][3] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x-1)][0] = 110;

                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-1)][1] = 110;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-1)][2] = 110;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-1)][3] = 110;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-1)][0] = 110;

                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-1)][1] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-1)][2] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-1)][3] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-1)][0] = 110;

                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-1)][1] = 110;
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-1)][2] = 110;
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-1)][3] = 110;
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-1)][0] = 110;

                    building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x-1)][1] = 110;
                    building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x-1)][2] = 110;
                    building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x-1)][3] = 110;
                    building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x-1)][0] = 110;

                    // Front SUD
                    building_id[(int)(parcour->y) * max_x + (int)(parcour->x+2)] = parcour->id;
                    building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x+2)] = parcour->id;
                    building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x+2)] = parcour->id;
                    building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x+2)] = parcour->id;
                    building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x+2)] = parcour->id;
                    building_id[(int)(parcour->y-3) * max_x + (int)(parcour->x+2)] = parcour->id;

                    // Front NORD
                    building_id[(int)(parcour->y) * max_x + (int)(parcour->x-2)] = parcour->id;
                    building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x-2)] = parcour->id;
                    building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x-2)] = parcour->id;
                    building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-2)] = parcour->id;
                    building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x-2)] = parcour->id;
                    building_id[(int)(parcour->y-3) * max_x + (int)(parcour->x-2)] = parcour->id;

                    // Front EST
                    building_id[(int)(parcour->y-4) * max_x + (int)(parcour->x+1)] = parcour->id;
                    building_id[(int)(parcour->y-4) * max_x + (int)(parcour->x)] = parcour->id;
                    building_id[(int)(parcour->y-4) * max_x + (int)(parcour->x-1)] = parcour->id;

                    // Front OUEST
                    building_id[(int)(parcour->y+3) * max_x + (int)(parcour->x+1)] = parcour->id;
                    building_id[(int)(parcour->y+4) * max_x + (int)(parcour->x)] = parcour->id;
                    building_id[(int)(parcour->y+3) * max_x + (int)(parcour->x-1)] = parcour->id;

                    // Front OUEST
                    building_altitude[(int)(parcour->y+3) * max_x + (int)(parcour->x+1)][1] = 110;
                    building_altitude[(int)(parcour->y+3) * max_x + (int)(parcour->x+1)][2] = 110;
                    building_altitude[(int)(parcour->y+3) * max_x + (int)(parcour->x+1)][3] = 110;
                    building_altitude[(int)(parcour->y+3) * max_x + (int)(parcour->x+1)][0] = 110;

                    building_altitude[(int)(parcour->y+4) * max_x + (int)(parcour->x)][1] = 110;
                    building_altitude[(int)(parcour->y+4) * max_x + (int)(parcour->x)][2] = 110;
                    building_altitude[(int)(parcour->y+4) * max_x + (int)(parcour->x)][3] = 110;
                    building_altitude[(int)(parcour->y+4) * max_x + (int)(parcour->x)][0] = 110;

                    building_altitude[(int)(parcour->y+3) * max_x + (int)(parcour->x-1)][1] = 110;
                    building_altitude[(int)(parcour->y+3) * max_x + (int)(parcour->x-1)][2] = 110;
                    building_altitude[(int)(parcour->y+3) * max_x + (int)(parcour->x-1)][3] = 110;
                    building_altitude[(int)(parcour->y+3) * max_x + (int)(parcour->x-1)][0] = 110;

                    // Front EST
                    building_altitude[(int)(parcour->y-4) * max_x + (int)(parcour->x+1)][1] = 110;
                    building_altitude[(int)(parcour->y-4) * max_x + (int)(parcour->x+1)][2] = 110;
                    building_altitude[(int)(parcour->y-4) * max_x + (int)(parcour->x+1)][3] = 110;
                    building_altitude[(int)(parcour->y-4) * max_x + (int)(parcour->x+1)][0] = 110;

                    building_altitude[(int)(parcour->y-4) * max_x + (int)(parcour->x)][1] = 110;
                    building_altitude[(int)(parcour->y-4) * max_x + (int)(parcour->x)][2] = 110;
                    building_altitude[(int)(parcour->y-4) * max_x + (int)(parcour->x)][3] = 110;
                    building_altitude[(int)(parcour->y-4) * max_x + (int)(parcour->x)][0] = 110;

                    building_altitude[(int)(parcour->y-4) * max_x + (int)(parcour->x-1)][1] = 110;
                    building_altitude[(int)(parcour->y-4) * max_x + (int)(parcour->x-1)][2] = 110;
                    building_altitude[(int)(parcour->y-4) * max_x + (int)(parcour->x-1)][3] = 110;
                    building_altitude[(int)(parcour->y-4) * max_x + (int)(parcour->x-1)][0] = 110;

                    // Front SUD
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+2)][1] = 110;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+2)][2] = 110;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+2)][3] = 110;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+2)][0] = 110;

                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x+2)][1] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x+2)][2] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x+2)][3] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x+2)][0] = 110;

                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x+2)][1] = 110;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x+2)][2] = 110;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x+2)][3] = 110;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x+2)][0] = 110;

                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x+2)][1] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x+2)][2] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x+2)][3] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x+2)][0] = 110;

                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x+2)][1] = 110;
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x+2)][2] = 110;
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x+2)][3] = 110;
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x+2)][0] = 110;

                    building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x+2)][1] = 110;
                    building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x+2)][2] = 110;
                    building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x+2)][3] = 110;
                    building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x+2)][0] = 110;

                    // Front NORD
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-2)][1] = 110;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-2)][2] = 110;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-2)][3] = 110;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-2)][0] = 110;

                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x-2)][1] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x-2)][2] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x-2)][3] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x-2)][0] = 110;

                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x-2)][1] = 110;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x-2)][2] = 110;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x-2)][3] = 110;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x-2)][0] = 110;

                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-2)][1] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-2)][2] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-2)][3] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-2)][0] = 110;

                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-2)][1] = 110;
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-2)][2] = 110;
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-2)][3] = 110;
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-2)][0] = 110;

                    building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x-2)][1] = 110;
                    building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x-2)][2] = 110;
                    building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x-2)][3] = 110;
                    building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x-2)][0] = 110;
                }
                else if (parcour->angle=='b')
                {
                    // Front SUD
                    building_id[(int)(parcour->y+3) * max_x + (int)(parcour->x+2)] = parcour->id;
                    building_id[(int)(parcour->y) * max_x + (int)(parcour->x+2)] = parcour->id;
                    building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x+2)] = parcour->id;
                    building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x+2)] = parcour->id;
                    building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x+2)] = parcour->id;
                    building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x+2)] = parcour->id;

                    // Front NORD
                    building_id[(int)(parcour->y+3) * max_x + (int)(parcour->x-2)] = parcour->id;
                    building_id[(int)(parcour->y) * max_x + (int)(parcour->x-2)] = parcour->id;
                    building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x-2)] = parcour->id;
                    building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x-2)] = parcour->id;
                    building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-2)] = parcour->id;
                    building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x-2)] = parcour->id;

                    // Front OUEST
                    building_id[(int)(parcour->y+4) * max_x + (int)(parcour->x+1)] = parcour->id;
                    building_id[(int)(parcour->y+4) * max_x + (int)(parcour->x)] = parcour->id;
                    building_id[(int)(parcour->y+4) * max_x + (int)(parcour->x-1)] = parcour->id;

                    //Bloc interne 1
                    building_id[(int)(parcour->y+3) * max_x + (int)(parcour->x-1)] = parcour->id;
                    building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x-1)] = parcour->id;
                    building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x-1)] = parcour->id;
                    building_id[(int)(parcour->y) * max_x + (int)(parcour->x-1)] = parcour->id;
                    building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-1)] = parcour->id;
                    building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x-1)] = parcour->id;

                    //Bloc interne 1
                    building_altitude[(int)(parcour->y+3) * max_x + (int)(parcour->x-1)][1] = 110;
                    building_altitude[(int)(parcour->y+3) * max_x + (int)(parcour->x-1)][2] = 110;
                    building_altitude[(int)(parcour->y+3) * max_x + (int)(parcour->x-1)][3] = 110;
                    building_altitude[(int)(parcour->y+3) * max_x + (int)(parcour->x-1)][0] = 110;

                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x-1)][1] = 110;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x-1)][2] = 110;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x-1)][3] = 110;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x-1)][0] = 110;

                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x-1)][1] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x-1)][2] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x-1)][3] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x-1)][0] = 110;

                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-1)][1] = 110;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-1)][2] = 110;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-1)][3] = 110;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-1)][0] = 110;

                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-1)][1] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-1)][2] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-1)][3] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-1)][0] = 110;

                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-1)][1] = 110;
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-1)][2] = 110;
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-1)][3] = 110;
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-1)][0] = 110;

                    //Bloc interne 2
                    building_id[(int)(parcour->y+3) * max_x + (int)(parcour->x)] = parcour->id;
                    building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x)] = parcour->id;
                    building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x)] = parcour->id;
                    building_id[(int)(parcour->y) * max_x + (int)(parcour->x)] = parcour->id;
                    building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x)] = parcour->id;
                    building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x)] = parcour->id;
                    building_id[(int)(parcour->y-3) * max_x + (int)(parcour->x)] = parcour->id;

                    //Bloc interne 2
                    building_altitude[(int)(parcour->y+3) * max_x + (int)(parcour->x)][1] = 110;
                    building_altitude[(int)(parcour->y+3) * max_x + (int)(parcour->x)][2] = 110;
                    building_altitude[(int)(parcour->y+3) * max_x + (int)(parcour->x)][3] = 110;
                    building_altitude[(int)(parcour->y+3) * max_x + (int)(parcour->x)][0] = 110;

                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x)][1] = 10;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x)][2] = 10;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x)][3] = 10;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x)][0] = 11;

                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x)][1] = 11;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x)][2] = 10;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x)][3] = 10;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x)][0] = 11;

                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x)][1] = 11;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x)][2] = 111;// Blocke de transition pour eviter que le perso tombe
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x)][3] = 10;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x)][0] = 11;

                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x)][1] = 101;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x)][2] = 101;//Block existe interieur/exterieur
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x)][3] = 101;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x)][0] = 101;

                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x)][2] = 110;//mur
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x)][3] = 110;
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x)][1] = 110;
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x)][0] = 110;


                    building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x)][1] = 110;
                    building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x)][2] = 110;
                    building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x)][3] = 110;
                    building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x)][0] = 110;

                    //Bloc interne 3
                    building_id[(int)(parcour->y+3) * max_x + (int)(parcour->x+1)] = parcour->id;
                    building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x+1)] = parcour->id;
                    building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x+1)] = parcour->id;
                    building_id[(int)(parcour->y) * max_x + (int)(parcour->x+1)] = parcour->id;
                    building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x+1)] = parcour->id;
                    building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x+1)] = parcour->id;

                    //Bloc interne 3
                    building_altitude[(int)(parcour->y+3) * max_x + (int)(parcour->x+1)][1] = 110;
                    building_altitude[(int)(parcour->y+3) * max_x + (int)(parcour->x+1)][2] = 110;
                    building_altitude[(int)(parcour->y+3) * max_x + (int)(parcour->x+1)][3] = 110;
                    building_altitude[(int)(parcour->y+3) * max_x + (int)(parcour->x+1)][0] = 110;

                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x+1)][1] = 110;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x+1)][2] = 110;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x+1)][3] = 110;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x+1)][0] = 110;

                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x+1)][1] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x+1)][2] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x+1)][3] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x+1)][0] = 110;

                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+1)][1] = 110;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+1)][2] = 110;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+1)][3] = 110;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+1)][0] = 110;

                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x+1)][1] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x+1)][2] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x+1)][3] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x+1)][0] = 110;

                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x+1)][1] = 110;
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x+1)][2] = 110;
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x+1)][3] = 110;
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x+1)][0] = 110;

                    // Front EST
                    building_id[(int)(parcour->y-3) * max_x + (int)(parcour->x+1)] = parcour->id;
                    building_id[(int)(parcour->y-3) * max_x + (int)(parcour->x-1)] = parcour->id;
                    building_id[(int)(parcour->y-4) * max_x + (int)(parcour->x)] = parcour->id;

                    // Front EST
                    building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x+1)][1] = 110;
                    building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x+1)][2] = 110;
                    building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x+1)][3] = 110;
                    building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x+1)][0] = 110;

                    building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x-1)][1] = 110;
                    building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x-1)][2] = 110;
                    building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x-1)][3] = 110;
                    building_altitude[(int)(parcour->y-3) * max_x + (int)(parcour->x-1)][0] = 110;

                    building_altitude[(int)(parcour->y-4) * max_x + (int)(parcour->x)][1] = 110;
                    building_altitude[(int)(parcour->y-4) * max_x + (int)(parcour->x)][2] = 110;
                    building_altitude[(int)(parcour->y-4) * max_x + (int)(parcour->x)][3] = 110;
                    building_altitude[(int)(parcour->y-4) * max_x + (int)(parcour->x)][0] = 110;


                    // Front SUD
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+2)][1] = 110;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+2)][2] = 110;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+2)][3] = 110;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+2)][0] = 110;

                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x+2)][1] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x+2)][2] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x+2)][3] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x+2)][0] = 110;

                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x+2)][1] = 110;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x+2)][2] = 110;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x+2)][3] = 110;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x+2)][0] = 110;

                    building_altitude[(int)(parcour->y+3) * max_x + (int)(parcour->x+2)][1] = 110;
                    building_altitude[(int)(parcour->y+3) * max_x + (int)(parcour->x+2)][2] = 110;
                    building_altitude[(int)(parcour->y+3) * max_x + (int)(parcour->x+2)][3] = 110;
                    building_altitude[(int)(parcour->y+3) * max_x + (int)(parcour->x+2)][0] = 110;

                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x+2)][1] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x+2)][2] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x+2)][3] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x+2)][0] = 110;

                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x+2)][1] = 110;
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x+2)][2] = 110;
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x+2)][3] = 110;
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x+2)][0] = 110;


                    // Front NORD
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-2)][1] = 110;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-2)][2] = 110;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-2)][3] = 110;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-2)][0] = 110;

                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x-2)][1] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x-2)][2] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x-2)][3] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x-2)][0] = 110;

                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x-2)][1] = 110;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x-2)][2] = 110;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x-2)][3] = 110;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x-2)][0] = 110;

                    building_altitude[(int)(parcour->y+3) * max_x + (int)(parcour->x-2)][1] = 110;
                    building_altitude[(int)(parcour->y+3) * max_x + (int)(parcour->x-2)][2] = 110;
                    building_altitude[(int)(parcour->y+3) * max_x + (int)(parcour->x-2)][3] = 110;
                    building_altitude[(int)(parcour->y+3) * max_x + (int)(parcour->x-2)][0] = 110;

                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-2)][1] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-2)][2] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-2)][3] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-2)][0] = 110;

                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-2)][1] = 110;
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-2)][2] = 110;
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-2)][3] = 110;
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-2)][0] = 110;

                    // Front OUEST
                    building_altitude[(int)(parcour->y+4) * max_x + (int)(parcour->x+1)][1] = 110;
                    building_altitude[(int)(parcour->y+4) * max_x + (int)(parcour->x+1)][2] = 110;
                    building_altitude[(int)(parcour->y+4) * max_x + (int)(parcour->x+1)][3] = 110;
                    building_altitude[(int)(parcour->y+4) * max_x + (int)(parcour->x+1)][0] = 110;

                    building_altitude[(int)(parcour->y+4) * max_x + (int)(parcour->x)][1] = 110;
                    building_altitude[(int)(parcour->y+4) * max_x + (int)(parcour->x)][2] = 110;
                    building_altitude[(int)(parcour->y+4) * max_x + (int)(parcour->x)][3] = 110;
                    building_altitude[(int)(parcour->y+4) * max_x + (int)(parcour->x)][0] = 110;

                    building_altitude[(int)(parcour->y+4) * max_x + (int)(parcour->x-1)][1] = 110;
                    building_altitude[(int)(parcour->y+4) * max_x + (int)(parcour->x-1)][2] = 110;
                    building_altitude[(int)(parcour->y+4) * max_x + (int)(parcour->x-1)][3] = 110;
                    building_altitude[(int)(parcour->y+4) * max_x + (int)(parcour->x-1)][0] = 110;

                }
                else if (parcour->angle == 'e')
                {
                    // BLOC INTERNE 1
                    building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x-3)] = parcour->id;
                    building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x-2)] = parcour->id;
                    building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x-1)] = parcour->id;
                    building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x)] = parcour->id;
                    building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x+1)] = parcour->id;
                    building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x+2)] = parcour->id;

                    // BLOC INTERNE 1
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x-3)][1] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x-3)][2] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x-3)][3] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x-3)][0] = 110;

                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x-2)][1] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x-2)][2] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x-2)][3] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x-2)][0] = 110;

                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x-1)][1] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x-1)][2] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x-1)][3] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x-1)][0] = 110;

                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x)][1] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x)][2] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x)][3] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x)][0] = 110;

                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x+1)][1] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x+1)][2] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x+1)][3] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x+1)][0] = 110;

                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x+2)][1] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x+2)][2] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x+2)][3] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x+2)][0] = 110;

                    // BLOC INTERNE 2
                    building_id[(int)(parcour->y) * max_x + (int)(parcour->x-3)] = parcour->id;
                    building_id[(int)(parcour->y) * max_x + (int)(parcour->x-2)] = parcour->id;
                    building_id[(int)(parcour->y) * max_x + (int)(parcour->x-1)] = parcour->id;
                    building_id[(int)(parcour->y) * max_x + (int)(parcour->x)] = parcour->id;
                    building_id[(int)(parcour->y) * max_x + (int)(parcour->x+1)] = parcour->id;
                    building_id[(int)(parcour->y) * max_x + (int)(parcour->x+2)] = parcour->id;
                    building_id[(int)(parcour->y) * max_x + (int)(parcour->x+3)] = parcour->id;


                    // BLOC INTERNE 2
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-3)][1] = 110;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-3)][2] = 110;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-3)][3] = 110;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-3)][0] = 110;

                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-2)][1] = 10;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-2)][2] = 10;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-2)][3] = 10;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-2)][0] = 11;

                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-1)][1] = 11;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-1)][2] = 10;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-1)][3] = 10;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-1)][0] = 11;

                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x)][1] = 11;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x)][2] = 111;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x)][3] = 10;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x)][0] = 11;

                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+1)][1] = 101;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+1)][2] = 101;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+1)][3] = 101;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+1)][0] = 101;

                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+2)][1] = 110;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+2)][2] = 110;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+2)][3] = 110;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+2)][0] = 110;

                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+3)][1] = 110;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+3)][2] = 110;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+3)][3] = 110;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+3)][0] = 110;

                    // BLOC INTERNE 3
                    building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-3)] = parcour->id;
                    building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-2)] = parcour->id;
                    building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-1)] = parcour->id;
                    building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x)] = parcour->id;
                    building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x+1)] = parcour->id;
                    building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x+2)] = parcour->id;

                    // BLOC INTERNE 3
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-3)][1] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-3)][2] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-3)][3] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-3)][0] = 110;

                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-2)][1] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-2)][2] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-2)][3] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-2)][0] = 110;

                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-1)][1] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-1)][2] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-1)][3] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-1)][0] = 110;

                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x)][1] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x)][2] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x)][3] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x)][0] = 110;

                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x+1)][1] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x+1)][2] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x+1)][3] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x+1)][0] = 110;

                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x+2)][1] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x+2)][2] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x+2)][3] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x+2)][0] = 110;

                    //FRONT SUD
                    building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x+3)] = parcour->id;
                    building_id[(int)(parcour->y) * max_x + (int)(parcour->x+4)] = parcour->id;
                    building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x+3)] = parcour->id;

                    // FRONT SUD
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x+3)][1] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x+3)][2] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x+3)][3] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x+3)][0] = 110;

                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+4)][1] = 110;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+4)][2] = 110;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+4)][3] = 110;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+4)][0] = 110;

                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x+3)][1] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x+3)][2] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x+3)][3] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x+3)][0] = 110;

                    //FRONT NORD
                    building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x-4)] = parcour->id;
                    building_id[(int)(parcour->y) * max_x + (int)(parcour->x-4)] = parcour->id;
                    building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-4)] = parcour->id;

                    // FRONT NORD
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x-4)][1] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x-4)][2] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x-4)][3] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x-4)][0] = 110;

                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-4)][1] = 110;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-4)][2] = 110;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-4)][3] = 110;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-4)][0] = 110;

                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-4)][1] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-4)][2] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-4)][3] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-4)][0] = 110;

                    //Front EST
                    building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x+2)] = parcour->id;
                    building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x+1)] = parcour->id;
                    building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x)] = parcour->id;
                    building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x-1)] = parcour->id;
                    building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x-2)] = parcour->id;
                    building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x-3)] = parcour->id;

                    // Front EST
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x+2)][1] = 110;
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x+2)][2] = 110;
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x+2)][3] = 110;
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x+2)][0] = 110;

                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x+1)][1] = 110;
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x+1)][2] = 110;
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x+1)][3] = 110;
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x+1)][0] = 110;

                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x)][1] = 110;
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x)][2] = 110;
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x)][3] = 110;
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x)][0] = 110;

                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-1)][1] = 110;
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-1)][2] = 110;
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-1)][3] = 110;
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-1)][0] = 110;

                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-2)][1] = 110;
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-2)][2] = 110;
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-2)][3] = 110;
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-2)][0] = 110;

                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-3)][1] = 110;
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-3)][2] = 110;
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-3)][3] = 110;
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-3)][0] = 110;

                    //Front OUEST
                    building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x+2)] = parcour->id;
                    building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x+1)] = parcour->id;
                    building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x)] = parcour->id;
                    building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x-1)] = parcour->id;
                    building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x-2)] = parcour->id;
                    building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x-3)] = parcour->id;

                    // Front OUEST
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x+2)][1] = 110;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x+2)][2] = 110;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x+2)][3] = 110;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x+2)][0] = 110;

                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x+1)][1] = 110;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x+1)][2] = 110;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x+1)][3] = 110;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x+1)][0] = 110;

                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x)][1] = 110;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x)][2] = 110;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x)][3] = 110;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x)][0] = 110;

                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x-1)][1] = 110;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x-1)][2] = 110;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x-1)][3] = 110;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x-1)][0] = 110;

                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x-2)][1] = 110;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x-2)][2] = 110;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x-2)][3] = 110;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x-2)][0] = 110;

                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x-3)][1] = 110;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x-3)][2] = 110;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x-3)][3] = 110;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x-3)][0] = 110;
                    
                }
                else if (parcour->angle== 'k')
                {
                    //BLOC INTERNE1
                    building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x-2)] = parcour->id;
                    building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x-1)] = parcour->id;
                    building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x)] = parcour->id;
                    building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x+1)] = parcour->id;
                    building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x+2)] = parcour->id;
                    building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x+3)] = parcour->id;

                    //BLOC INTERNE1
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x-2)][1] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x-2)][2] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x-2)][3] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x-2)][0] = 110;

                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x-1)][1] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x-1)][2] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x-1)][3] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x-1)][0] = 110;

                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x)][1] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x)][2] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x)][3] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x)][0] = 110;

                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x+1)][1] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x+1)][2] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x+1)][3] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x+1)][0] = 110;

                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x+2)][1] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x+2)][2] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x+2)][3] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x+2)][0] = 110;

                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x+3)][1] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x+3)][2] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x+3)][3] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x+3)][0] = 110;

                    //BLOC INTERNE2
                    building_id[(int)(parcour->y) * max_x + (int)(parcour->x-3)] = parcour->id;
                    building_id[(int)(parcour->y) * max_x + (int)(parcour->x-2)] = parcour->id;
                    building_id[(int)(parcour->y) * max_x + (int)(parcour->x-1)] = parcour->id;
                    building_id[(int)(parcour->y) * max_x + (int)(parcour->x)] = parcour->id;
                    building_id[(int)(parcour->y) * max_x + (int)(parcour->x+1)] = parcour->id;
                    building_id[(int)(parcour->y) * max_x + (int)(parcour->x+2)] = parcour->id;
                    building_id[(int)(parcour->y) * max_x + (int)(parcour->x+3)] = parcour->id;

                    //BLOC INTERNE2
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-3)][1] = 110;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-3)][2] = 110;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-3)][3] = 110;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-3)][0] = 110;

                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-2)][1] = 110;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-2)][2] = 110;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-2)][3] = 110;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-2)][0] = 110;

                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-1)][1] = 101;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-1)][2] = 101;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-1)][3] = 101;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-1)][0] = 101;

                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x)][1] = 11;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x)][2] = 111;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x)][3] = 10;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x)][0] = 11;

                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+1)][1] = 11;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+1)][2] = 10;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+1)][3] = 10;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+1)][0] = 11;

                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+2)][1] = 10;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+2)][2] = 10;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+2)][3] = 10;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+2)][0] = 11;

                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+3)][1] = 110;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+3)][2] = 110;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+3)][3] = 110;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+3)][0] = 110;

                    //BLOC INTERNE3
                    building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-2)] = parcour->id;
                    building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-1)] = parcour->id;
                    building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x)] = parcour->id;
                    building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x+1)] = parcour->id;
                    building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x+2)] = parcour->id;
                    building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x+3)] = parcour->id;

                    //BLOC INTERNE3
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-2)][1] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-2)][2] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-2)][3] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-2)][0] = 110;

                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-1)][1] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-1)][2] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-1)][3] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-1)][0] = 110;

                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x)][1] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x)][2] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x)][3] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x)][0] = 110;

                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x+1)][1] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x+1)][2] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x+1)][3] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x+1)][0] = 110;

                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x+2)][1] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x+2)][2] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x+2)][3] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x+2)][0] = 110;

                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x+3)][1] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x+3)][2] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x+3)][3] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x+3)][0] = 110;

                    //FRONT NORD
                    building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x-3)] = parcour->id;
                    building_id[(int)(parcour->y) * max_x + (int)(parcour->x-4)] = parcour->id;
                    building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x-3)] = parcour->id;

                    //FRONT NORD
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x-3)][1] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x-3)][2] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x-3)][3] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x-3)][0] = 110;

                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-4)][1] = 110;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-4)][2] = 110;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-4)][3] = 110;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x-4)][0] = 110;

                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-3)][1] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-3)][2] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-3)][3] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x-3)][0] = 110;

                    //FRONT SUD
                    building_id[(int)(parcour->y+1) * max_x + (int)(parcour->x+4)] = parcour->id;
                    building_id[(int)(parcour->y) * max_x + (int)(parcour->x+4)] = parcour->id;
                    building_id[(int)(parcour->y-1) * max_x + (int)(parcour->x+4)] = parcour->id;

                    //FRONT SUD
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x+4)][1] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x+4)][2] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x+4)][3] = 110;
                    building_altitude[(int)(parcour->y+1) * max_x + (int)(parcour->x+4)][0] = 110;

                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+4)][1] = 110;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+4)][2] = 110;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+4)][3] = 110;
                    building_altitude[(int)(parcour->y) * max_x + (int)(parcour->x+4)][0] = 110;

                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x+4)][1] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x+4)][2] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x+4)][3] = 110;
                    building_altitude[(int)(parcour->y-1) * max_x + (int)(parcour->x+4)][0] = 110;


                    //Front EST
                    building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x+3)] = parcour->id;
                    building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x+2)] = parcour->id;
                    building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x+1)] = parcour->id;
                    building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x)] = parcour->id;
                    building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x-1)] = parcour->id;
                    building_id[(int)(parcour->y-2) * max_x + (int)(parcour->x-2)] = parcour->id;

                    // Front EST
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x+3)][1] = 110;
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x+3)][2] = 110;
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x+3)][3] = 110;
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x+3)][0] = 110;

                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x+2)][1] = 110;
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x+2)][2] = 110;
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x+2)][3] = 110;
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x+2)][0] = 110;

                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x+1)][1] = 110;
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x+1)][2] = 110;
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x+1)][3] = 110;
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x+1)][0] = 110;

                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x)][1] = 110;
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x)][2] = 110;
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x)][3] = 110;
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x)][0] = 110;

                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-1)][1] = 110;
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-1)][2] = 110;
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-1)][3] = 110;
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-1)][0] = 110;

                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-2)][1] = 110;
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-2)][2] = 110;
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-2)][3] = 110;
                    building_altitude[(int)(parcour->y-2) * max_x + (int)(parcour->x-2)][0] = 110;

                    //Front OUEST
                    building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x+3)] = parcour->id;
                    building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x+2)] = parcour->id;
                    building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x+1)] = parcour->id;
                    building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x)] = parcour->id;
                    building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x-1)] = parcour->id;
                    building_id[(int)(parcour->y+2) * max_x + (int)(parcour->x-2)] = parcour->id;

                    // Front OUEST
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x+3)][1] = 110;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x+3)][2] = 110;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x+3)][3] = 110;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x+3)][0] = 110;

                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x+2)][1] = 110;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x+2)][2] = 110;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x+2)][3] = 110;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x+2)][0] = 110;

                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x+1)][1] = 110;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x+1)][2] = 110;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x+1)][3] = 110;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x+1)][0] = 110;

                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x)][1] = 110;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x)][2] = 110;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x)][3] = 110;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x)][0] = 110;

                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x-1)][1] = 110;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x-1)][2] = 110;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x-1)][3] = 110;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x-1)][0] = 110;

                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x-2)][1] = 110;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x-2)][2] = 110;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x-2)][3] = 110;
                    building_altitude[(int)(parcour->y+2) * max_x + (int)(parcour->x-2)][0] = 110;

                }
            }
        }
    }
}

int find_smalest_valid_id_building(int from)
{
    for (struct building *l = list_building; l != NULL; l = l->next)
	{
		if (l->id == from)
		    return find_smalest_valid_id_building(from + 1);
	}
    return from;
}

void add_wood_pillar_or_wood_house(int moix, int moiy)
{
    // FULL 3X3
    for (int i = moix - 2; i < moix + 1; i++)
    {
        for (int j = moiy - 2; j < moiy + 1; j++)
        {
            if (0 <= i && i + 2 < max_x && 0 <= j && j + 2 < max_y)
            {
                char all = 1;
                for (int r = j; r < j +3; r++)
                {
                    for (int c = i; c < i +3; c++)
                    {
                        if ((r != moiy || c != moix) && (building_id[r * max_x + c] == -1 || strcmp(get_ptr_from_id_building(building_id[r * max_x + c])->skin,"141") != 0))
                        {
                            all = 0;
                        }
                    }
                }
                if (all == 1)
                {
                    create_building(i+2, j+2, 'a', 'a', "112", 500);
                    for (int r = j; r < j +3; r++)
                    {
                        for (int c = i; c < i +3; c++)
                        {
                            if (r != moiy || c != moix)
                            {
                                struct building *b = get_ptr_from_id_building(building_id[r * max_x + c]);
                                b->pv = 0;
                                b->a_bouger = 1;
                            }
                        }
                    }
                    return;
                }
            }
        }
    }


    for (int j = max(0, moiy-5); j < min(moiy+1,max_y-5); j++)
    {
        for (int i = max(0, moix - 5); i <min(moix + 1, max_x - 5);i++)
        {
            if (moix == i || moix == i + 5 || moiy == j || moiy == j + 5)
            {
                uint8_t err = 0;
                for (int col = i; col < i + 6; col++)
                {
                    if (((col != moix || j != moiy) && (building_id[j * max_x + col] == -1 || strcmp(get_ptr_from_id_building(building_id[j * max_x + col])->skin,"141") != 0)) || ((col != moix || j + 5!= moiy) && (building_id[(j+5) * max_x + col] == -1 || strcmp(get_ptr_from_id_building(building_id[(j+5) * max_x + col])->skin,"141") != 0)))
                    {
                        err += 1;
                        break;
                    }
                }
                if (err > 0)
                    continue;
                for (int row = j+1; row < j + 5; row++)
                {
                    if (((row != moiy || i != moix) && (building_id[row * max_x + i] == -1 || strcmp(get_ptr_from_id_building(building_id[row * max_x + i])->skin,"141") != 0)) || ((row != moiy || i + 5!= moix) && (building_id[(i+5) + max_x * row] == -1 || strcmp(get_ptr_from_id_building(building_id[(i+5) + max_x * row])->skin,"141") != 0)))
                    {
                        err += 1;
                        break;
                    }
                }
                if (err > 0)
                    continue;
                create_building(i+5, j+5, 'a', 'a', "113", 500);
                for (int r = j; r < j +6; r++)
                {
                    for (int c = i; c < i +6; c++)
                    {
                        if ((r != moiy || c != moix) && building_id[r * max_x + c] != -1)
                        {
                            struct building *b = get_ptr_from_id_building(building_id[r * max_x + c]);
                            b->pv = 0;
                            b->a_bouger = 1;
                        }
                    }
                }
                return;
            }
        }
    }
    create_building(moix, moiy, 'a', 'a', "141", 5);
    return;
}