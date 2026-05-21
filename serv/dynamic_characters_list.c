#include "dynamic_characters_list.h"

int append_perso(char *line, char *skin ,int id)
{
    while (list.capacity <= id)
    {
        list.capacity *= 2;
        list.data = realloc(list.data, list.capacity * sizeof(struct personnages));
    }
    list.data[id].online = '0';
    list.data[id].e_list = NULL;
    list.data[id].is_active = 1;
    int ret = parse_new(&list.data[id], line, skin);
    append_perso_bioms(id, (int)(list.data[id].y * 0.04f) * max_x_biom + (int)(list.data[id].x * 0.04f));
    if (id > list.maxid)
        list.maxid = id;
    if (skin[0] == '0' && skin[1] == 0)
        list.data[id].chemin = malloc(sizeof(struct path)*max_x*max_y);
    //printf ("%d %d\n", id, list.maxid);
    return ret;
}

int append_empty_perso(void)
{
    int id = find_smalest_valid_id_perso(0);
    while (list.capacity <= id)
    {
        list.capacity *= 2;
        list.data = realloc(list.data, list.capacity * sizeof(struct personnages));
    }
    if (id > list.maxid)
        list.maxid = id;
    list.data[id].online = '0';
    list.data[id].e_list = NULL;
    list.data[id].is_active = 1;
    return id;
}

void death(void)
{
    for (int i = list.maxid; i >= 0;i--)
    {
        if (list.data[i].is_active == 1 && list.data[i].pv <= 0)
        {
            free_linked_enemie(list.data[i].e_list);
            remove_perso_bioms(i, (int)(list.data[i].y * 0.04f) * (max_x / 25) + (int)(list.data[i].x * 0.04f));
            struct personnages *s = find_perso_by_name(list.data[i].nom_superieur);
            if (s != NULL)
            {
                s->nb_vassaux -= 1;
                s->a_bouger = 1;
            }
            list.data[i].is_active = 0;
            if (i == list.maxid)
                list.maxid -= 1;
        }
    }
    if (list.maxid * 4 < list.capacity)
    {
        list.capacity /= 2;
        list.data = realloc(list.data, list.capacity * sizeof(struct personnages));
    }
    struct building *tmp = list_building;
	struct building *prev;
	while (tmp != NULL && tmp->pv <= 0)
	{
		list_building = list_building->next;
		remove_building_altitude(tmp);
		free(tmp);
		tmp = list_building;
	}
	while (tmp != NULL)
	{
		while (tmp != NULL && tmp->pv > 0)
		{
			prev = tmp;
			tmp = tmp->next;
		}
		if (tmp == NULL)
			return;
		prev->next = tmp->next;
		remove_building_altitude(tmp);
        free(tmp);
		tmp = prev->next;
	}
}

void init_map(const char *map_path)
{
    list.data = calloc(10, sizeof(struct personnages));
    list.capacity = 10;
    list.maxid = 0;
    FILE *acount = fopen(map_path, "r+");
    char line[500];
    size_t len = 500;
    char skin[5];
    int id;
    while (fgets(line, len, acount))
    {
        int i = 0;
        while (line[i] != ' ')
        {
            skin[i] = line[i];
            i++;
        }
        skin[i] = 0;
        i++;
        id = atoi(&line[i]);
        while (line[i] != ' ')
            i++;
        if (skin[0] == '0')
            append_perso(line + i + 1, skin, id);
        if (skin[0] == '1')
            append_building(line + i + 1, skin, id);
    }
}