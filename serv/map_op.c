#include "map_op.h"

struct personnages *init_map(void)
{
    FILE *acount = fopen("map.txt", "r+");
    char line[500];
    size_t len = 500;
    while (fgets(line, len, acount))
    {
        if (line[0] == '1')
            append_building(line);
        else
            append_perso(line);
    }

    return list;
}

