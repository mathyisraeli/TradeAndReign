#include "building.h"

int max(int a, int b)
{
    if (a > b)
        return a;
    return b;
}

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
                        if ((r != moiy || c != moix) && (building_id[r * max_x + c] == -1 || strcmp(find_building_by_id(building_id[r * max_x + c])->skin,"141") != 0))
                        {
                            printf ("%d %d\n", c,r);
                            all = 0;
                        }
                    }
                }
                if (all == 1)
                {
                    sprintf (ordre + strlen(ordre), "-112 -1 500 %d %d a a\n", i+2 , j+2);
                    for (int r = j; r < j +3; r++)
                    {
                        for (int c = i; c < i +3; c++)
                        {
                            if (r != moiy || c != moix)
                            {
                                printf ("dellete\n");
                                sprintf (ordre + strlen(ordre), "%d 00 0 ", building_id[r * max_x + c]);
                            }
                        }
                    }
                    return;
                }
            }
        }
    }

    //EMPTY 6X6
    /*     rows, cols = len(tab), len(tab[0])

    # Parcours de tous les coins possibles du carré 6x6
    for j in range(max(0, y - 5), min(y + 1, rows - 5)):
        for i in range(max(0, x - 5), min(x + 1, cols - 5)):
            # (x, y) doit être sur le bord du carré
            if (x == i or x == i + 5 or y == j or y == j + 5):              
                erreurs = 0  # compteur de cases != 1

                # Lignes verticales
                for col in range(i, i + 6):
                    if ((col != x or j != y) and tab[j][col] != 1) or ((col != x or j + 5!= y) and tab[j+5][col] != 1):
                        erreurs += 1
                        break
                if erreurs > 0:
                    continue

                # Colonnes gauche et droite (sans les coins déjà testés)
                for row in range(j + 1, j + 5):
                    if ((row != y or i != x) and tab[row][x] != 1) or ((row != y or i + 5 != x) and tab[row][i+1] != 1):
                            erreurs += 1
                            break
                    if erreurs > 0:
                        break

                if erreurs == 0:
                    return True*/

    for (int j = max(0, moiy-5); j < min(moiy+1,max_y-5); j++)
    {
        for (int i = max(0, moix - 5); i <min(moix + 1, max_x - 5);i++)
        {
            if (moix == i || moix == i + 5 || moiy == j || moiy == j + 5)
            {
                uint8_t err = 0;
                for (int col = i; col < i + 6; col++)
                {
                    if (((col != moix || j != moiy) && (building_id[j * max_x + col] == -1 || strcmp(find_building_by_id(building_id[j * max_x + col])->skin,"141") != 0)) || ((col != moix || j + 5!= moiy) && (building_id[(j+5) * max_x + col] == -1 || strcmp(find_building_by_id(building_id[(j+5) * max_x + col])->skin,"141") != 0)))
                    {
                        err += 1;
                        break;
                    }
                }
                if (err > 0)
                    continue;
                for (int row = j+1; row < j + 5; row++)
                {
                    if (((row != moiy || i != moix) && (building_id[row * max_x + i] == -1 || strcmp(find_building_by_id(building_id[row * max_x + i])->skin,"141") != 0)) || ((row != moiy || i + 5!= moix) && (building_id[(i+5) + max_x * row] == -1 || strcmp(find_building_by_id(building_id[(i+5) + max_x * row])->skin,"141") != 0)))
                    {
                        err += 1;
                        break;
                    }
                }
                if (err > 0)
                    continue;
                sprintf (ordre + strlen(ordre), "-113 -1 500 %d %d a a\n", i+5 , j+5);
                for (int r = j; r < j +6; r++)
                {
                    for (int c = i; c < i +6; c++)
                    {
                        if ((r != moiy || c != moix) && building_id[r * max_x + c] != -1)
                        {
                            printf ("dellete\n");
                            sprintf (ordre + strlen(ordre), "%d 00 0 ", building_id[r * max_x + c]);
                        }
                    }
                }
                return;
            }
        }
    }

    sprintf (ordre + strlen(ordre), "-141 -1 5 %d %d a a\n", moix , moiy);
    return;
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
        if (parcour->angle == 'a')
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
        else if (parcour->angle=='b')
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
        else if (parcour->angle == 'k') // k
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
        else if (parcour->angle == 'e') // e
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
        if (parcour->angle == 'a')
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
        else if (parcour->angle=='b')
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
        else if (parcour->angle == 'k') // k
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
        else if (parcour->angle == 'e') // e
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