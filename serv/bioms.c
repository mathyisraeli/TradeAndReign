#include "bioms.h"

void init_bioms(void)
{
    max_x_biom = max_x / 25;
    max_y_biom = max_y / 25;
    int nbioms = max_x_biom*max_y_biom;
    list_bioms = malloc(sizeof(struct dynamic_char_bioms_list)*nbioms);
    for (int i = 0; i < nbioms; i++)
    {
        list_bioms[i].data = malloc(sizeof(int)*5);
        list_bioms[i].size = 0;
        list_bioms[i].capacity = 5;
    }
}


void append_perso_bioms(int p, int biom)
{
    if (list_bioms[biom].capacity == list_bioms[biom].size)
    {
        list_bioms[biom].capacity *= 2;
        list_bioms[biom].data = realloc(list_bioms[biom].data, list_bioms[biom].capacity * sizeof(int));
    }
    list_bioms[biom].data[list_bioms[biom].size] = p;
    list_bioms[biom].size += 1;
}

void remove_perso_bioms(int p, int biom)
{
    for (int i = 0; i < list_bioms[biom].size ;i++)
    {
        if (list_bioms[biom].data[i] == p)
        {
            list_bioms[biom].data[i] = list_bioms[biom].data[list_bioms[biom].size - 1];
            list_bioms[biom].size -= 1;
            if (list_bioms[biom].size * 2 < list_bioms[biom].capacity && 10 < list_bioms[biom].capacity)
            {
                list_bioms[biom].capacity /= 2;
                list_bioms[biom].data = realloc(list_bioms[biom].data, list_bioms[biom].capacity * sizeof(int));
            }
            return;
        }
    }
    printf ("error %d %d\n", p, biom); 
}