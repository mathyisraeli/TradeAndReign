#include "dynamic_characters_list.h"

int append_perso(char *line, char *skin ,int id)
{
    while (list.capacity <= id)
    {
        list.capacity *= 2;
        list.data = realloc(list.data, list.capacity * sizeof(struct personnages));
    }
    int ret = parse_new(&list.data[id], line, skin, id);
    list.data[id].online = '0';
    list.data[id].e_list = NULL;
    list.data[id].i_list = NULL;
    list.data[id].is_active = 1;

    if (id > list.maxid)
        list.maxid = id;
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
    list.data[id].online = '0';
    list.data[id].e_list = NULL;
    list.data[id].i_list = NULL;
    list.data[id].is_active = 1;
    return id;
}

void death(void)
{
    for (int i = list.maxid; i >= 0;i--)
    {
        if (list.data[i].is_active == 1 && list.data[i].pv <= 0)
        {
            kill(&list.data[i]);
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
}

void init_map(void)
{
    list.data = malloc(10 *sizeof(struct personnages));
    list.capacity = 10;
    list.maxid = 0;
    FILE *acount = fopen("map.txt", "r+");
    char line[500];
    size_t len = 500;
    while (fgets(line, len, acount))
    {
        parse_order(line);
    }
}
