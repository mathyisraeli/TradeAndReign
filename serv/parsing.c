#include "parsing.h"

int parse_new(struct personnages *p, char *line, char *skin)
{
    int i;
    int j;
    char tmpI[10];
    char tmpN[50];
    p->skill[0] = 0;
    sscanf(line, "%d %d %d %d %d %d %d %c %s %s %s %s %d %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %s %s %s %s %s %s %s %f %f %f %f %f %n",
    &p->pv, &p->nb_vassaux, &p->faim, &p->inside, &p->house_id, &p->animation, &p->animation_2, &p->angle, p->physique, p->nom_de_compte, p->nom, p->nom_superieur,
    &p->echange_player, &p->items_cnt[0], p->items[0], &p->items_cnt[1], p->items[1], &p->items_cnt[2], p->items[2], &p->items_cnt[3], p->items[3], &p->items_cnt[4], p->items[4],
    &p->items_cnt[5], p->items[5], &p->items_cnt[6], p->items[6], &p->items_cnt[7], p->items[7], &p->items_cnt[8], p->items[8], &p->items_cnt[9], p->items[9], &p->items_cnt[10], p->items[10],
    &p->items_cnt[11], p->items[11],  p->items[12],  p->items[13],  p->items[14],  p->items[15],  p->items[16],  p->items[17],  &p->x, &p->y, &p->altitude, &p->ordrex, &p->ordrey, &i);
    while (line[i] != ']')
    {
        i += 1;
        if (line[i] != ']')
        {
            j = 0;
            while (line[i] != ' ')
            {
                tmpN[j] = line[i];
                i++;
                j++;
            }
            tmpN[j] = 0;
            i++;
            j = 0;
            while (line[i] != ' ' && line[i] != ']')
            {
                tmpI[j] = line[i];
                i++;
                j++;
            }
            tmpI[j] = 0;
            p->e_list = append_enemie(tmpN, p->e_list, atoi(tmpI));
        }
    }
    i+= 3;
    j = 0;
    while (line[i] != ']')
    {
        p->skill[j] = line[i];
        i += 1;
        j += 1;
    }
    i += 1;
    j = 0;
    while (line[i] != '\n' && line[i] != 0)
    {
        p->speak[j] = line[i];
        i += 1;
        j += 1;
    }
    p->speak[j] = 0;
    strcpy (p->skin, skin);
    p->speak[j] = 0;
    p->moved_x = 0;
    p->moved_y = 0;
    p->vitesse_dep = 0.5;
    p->speak_timer = j;
    p->chemin_is_set = 0;
    p->online = 0;
    p->a_bouger = 0;
    p->is_active = 1;
    p->dom = 1; // to move;
    p->vitesse_dep = 1; // to move;
    return i;
}

int parse_new_building(struct building *b, char *line, char *skin, int id)
{
    int i;
    sscanf(line, "%d %d %d %c %c %n",&b->pv, &b->x, &b->y, &b->angle,&b->state,&i);
    if(id == -1)
        b->id = find_smalest_valid_id_building(0);
    else
        b->id = id;
    strcpy(b->skin ,skin);
    while (line[i] != '\n' && line[i] != 0)
        i++;
    return i;
}

void parse_order(char *line)
{
    int i = 0;
    int j;
    char tmpC[50];
    while (line[i] != 0)
    {
        tmpC[0] = line[i];
        i += 2;
        int id = atoi(&line[i]);
        while (line[i] != ' ')
            i+= 1;
        i += 1;
        int idaction = atoi(&line[i]);
        i += 3;
        if (tmpC[0] == '0') // living
        {
            struct personnages *p = &list.data[id];
            switch(idaction)
            {
                case 0:
                    if (line[i] == '+')
                    {
                        i++;
                        p->pv += atoi(&line[i]);
                    }
                    else if (line[i] == '-')
                    {
                        i++;
                        p->pv -= atoi(&line[i]);
                    }
                    else
                    {
                        i++;
                        p->pv = atoi(&line[i]);
                    }
                    while(line[i] != ' ')
                        i++;
                    i++;
                    break;
                case 1:
                    if (line[i] == '+')
                    {
                        i++;
                        p->moved_x += atof(&line[i]);
                        p->faim -= 1;
                    }
                    else if (line[i] == '-')
                    {
                        i++;
                        p->moved_x -= atof(&line[i]);
                        p->faim -= 1;
                    }
                    else
                        p->x = atof(&line[i]);
                    while(line[i] != ' ')
                        i++;
                    i++;
                    break;
                case 2:
                    if (line[i] == '+')
                    {
                        i++;
                        p->moved_y += atof(&line[i]);
                        p->faim -= 1;
                    }
                    else if (line[i] == '-')
                    {
                        i++;
                        p->moved_y -= atof(&line[i]);
                        p->faim -= 1;
                    }
                    else
                        p->y = atof(&line[i]);
                    while(line[i] != ' ')
                        i++;
                    i++;
                    break;
                case 3:
                    p->ordrex = atof(&line[i]);
                    while(line[i] != ' ')
                        i++;
                    i++;
                    break;
                case 4:
                    p->ordrey = atof(&line[i]);
                    while(line[i] != ' ')
                        i++;
                    i++;
                    break;
                case 5:
                    p->angle = line[i];
                    i += 2;
                    break;
                case 6:
                    p->timer_dom = atoi(&line[i]);
                    while(line[i] != ' ')
                        i++;
                    i++;
                    break;
                case 7:
                    p->faim += atoi(&line[i]);
                    while(line[i] != ' ')
                        i++;
                    i++;
                    break;
                case 8:
                    remove_1_pixel(atoi(&line[i]));
                    while(line[i] != ' ')
                        i++;
                    i++;
                    break;
                case 9:
                    p->inside = atoi(&line[i]);
                    while(line[i] != ' ')
                    {
                        i++;
                    }
                    i++;
                    break;
                case 10:
                    j = 0;
                    while(line[i] != ' ')
                    {
                        p->nom_superieur[j] = line[i];
                        i++;
                        j++;
                    }
                    p->nom_superieur[j] = 0;
                    i++;
                    break;

                case 13:
                    int index = atoi(&line[i]);
                    while(line[i] != ' ')
                        i++;
                    i++;
                    add_1_pixel(index, texture_from_string(line + i));
                    i += 4;
                    break;
                case 14:
                    if (line[i] == '+')
                    {
                        i++;
                        p->nb_vassaux += atoi(&line[i]);
                    }
                    else if (line[i] == '-')
                    {
                        i++;
                        p->nb_vassaux -= atoi(&line[i]);
                    }
                    else
                        p->nb_vassaux = atof(&line[i]);
                    while(line[i] != ' ')
                        i++;
                    i++;
                    break;
                case 15:// Modifie enemie
                    if (line[i] == '+') // Rajoute enemie
                    {
                        i++;
                        int n = atoi(&line[i]);
                        while (line[i] != ' ')
                            i++;
                        i++;
                        j = 0;
                        while (line[i] != ' ')
                        {
                            tmpC[j] = line[i];
                            j++;
                            i++;
                        }
                        tmpC[j] = 0;
                        i++;
                        p->e_list = append_enemie(tmpC, p->e_list, n);
                    }
                    else // enleve enemie
                    {
                        j = 0;
                        while (line[i] != ' ')
                        {
                            tmpC[j] = line[i];
                            j++;
                            i++;
                        }
                        tmpC[j] = 0;
                        i++;
                        p->e_list = remove_enemie(tmpC, p->e_list);
                    }
                    break;
                case 16: // pas sur
                    if (line[i] == '+')
                    {
                        i++;
                        int n = atoi(&line[i]);
                        while (line[i] != ' ')
                            i++;
                        i++;
                        j = 0;
                        while (line[i] != ' ')
                        {
                            tmpC[j] = line[i];
                            j++;
                            i++;
                        }
                        tmpC[j] = 0;
                        i++;
                        append_in_inventory(tmpC,n , p->items, p->items_cnt);
                    }
                    else
                    {
                        int n = atoi(&line[i]);
                        while (line[i] != ' ')
                            i++;
                        i++;
                        j = 0;
                        while (line[i] != ' ')
                        {
                            tmpC[j] = line[i];
                            j++;
                            i++;
                        }
                        tmpC[j] = 0;
                        i++;
                        remove_from_inventory(tmpC, n, p->items, p->items_cnt);
                    }
                    break;
                case 17:
                    p->echange_player = atoi(&line[i]);
                    while (line[i] != ' ')
                    {
                        i++;
                    }
                    i++;
                    j = 0;
                    while (line[i] != ' ')
                    {
                        p->items[10][j] = line[i];
                        i++;
                        j++;
                    }
                    p->items[10][j] = 0;
                    i++;
                    p->items_cnt[10] = atoi(&line[i]);
                    while(line[i] != ' ')
                        i++;
                    i++;
                    j = 0;
                    while (line[i] != ' ')
                    {
                        p->items[11][j] = line[i];
                        i++;
                        j++;
                    }
                    p->items[11][j] = 0;
                    i++;
                    p->items_cnt[11] = atoi(&line[i]);
                    while(line[i] != ' ')
                        i++;
                    i++;
                    break;
                case 18:
                {
                    int idfonction = atoi(&line[i]);
                    while (line[i] != ' ')
                        i++;
                    i++;
                    if (idfonction == 0) // add_wood_pillar_or_wood_house
                    {
                        if (count_item("wooden-board", p->items, p->items_cnt) >= 9)
                        {
                            int moix;
                            int moiy;
                            switch (p->angle)
                            {
                                case 'a':
                                    moix = (int)p->x - 1;
                                    moiy = (int)p->y - 1;
                                    break;
                                case 'b':
                                    moix = (int)p->x;
                                    moiy = (int)p->y - 1;
                                    break;
                                case 'c':
                                    moix = (int)p->x + 1;
                                    moiy = (int)p->y - 1;
                                    break;
                                case 'd':
                                    moix = (int)p->x + 1;
                                    moiy = (int)p->y;
                                    break;
                                case 'e':
                                    moix = (int)p->x + 1;
                                    moiy = (int)p->y + 1;
                                    break;
                                case 'f':
                                    moix = (int)p->x;
                                    moiy = (int)p->y + 1;
                                    break;
                                case 'g':
                                    moix = (int)p->x - 1;
                                    moiy = (int)p->y + 1;
                                    break;
                                case 'h':
                                    moix = (int)p->x - 1;
                                    moiy = (int)p->y;
                                    break;
                            }
                            add_wood_pillar_or_wood_house(moix, moiy);
                            remove_from_inventory("wooden-board", 9, p->items, p->items_cnt);
                        }
                    }
                    break;
                }
                case 20: // pas sur
                    j = 0;
                    while (line[i] != 31)
                    {
                        p->speak[j] = line[i];
                        i++;
                        j++;
                    }
                    p->speak[j] = 0;
                    i += 2;
                    break;
                case 21:
                    p->animation = atoi(&line[i]);
                    while(line[i] != ' ')
                        i++;
                    i++;
                    break;
                case 22:
                    p->animation_2 = atoi(&line[i]);
                    while (line[i] != ' ')
                        i++;
                    i++;
                    break;
                case 23:
                    p->chemin_is_set = line[i] - '0';
                    i += 2;
                    break;
                case 24:
                    j = 0;
                    while(line[i] != ' ')
                    {
                        p->items[12][j] = line[i];
                        i++;
                        j++;
                    }
                    p->items[12][j] = 0;
                    i++;
                    break;
                case 25:
                    j = 0;
                    while(line[i] != ' ')
                    {
                        p->items[13][j] = line[i];
                        i++;
                        j++;
                    }
                    p->items[13][j] = 0;
                    i++;
                    break;
                case 26:
                    j = 0;
                    while(line[i] != ' ')
                    {
                        p->items[14][j] = line[i];
                        i++;
                        j++;
                    }
                    p->items[14][j] = 0;
                    i++;
                    break;
                case 27:
                    j = 0;
                    while(line[i] != ' ')
                    {
                        p->items[15][j] = line[i];
                        i++;
                        j++;
                    }
                    p->items[15][j] = 0;
                    i++;
                    break;
                case 28:
                    j = 0;
                    while(line[i] != ' ')
                    {
                        p->items[16][j] = line[i];
                        i++;
                        j++;
                    }
                    p->items[16][j] = 0;
                    i++;
                    break;
                case 29:
                    j = 0;
                    while(line[i] != ' ')
                    {
                        p->items[17][j] = line[i];
                        i++;
                        j++;
                    }
                    p->items[17][j] = 0;
                    i++;
                    break;
                case 31:
                    if (line[i] == '+')
                    {
                        i++;
                        p->altitude += atoi(&line[i]);
                    }
                    else if (line[i] == '-')
                    {
                        i++;
                        p->altitude -= atoi(&line[i]);
                    }
                    else
                    {
                        i++;
                        p->altitude = atoi(&line[i]);
                    }
                    while(line[i] != ' ')
                        i++;
                    i++;
                    break;
                case 32:
                    p->house_id = atoi(&line[i]);
                    while(line[i] != ' ')
                        i++;
                    i++;
                    break;
            }
            p->a_bouger = 1;
        }
        else if (tmpC[0] == '1') // building
        {
            struct building *b = get_ptr_from_id_building(id);
            switch(idaction)
            {
                case 0:
                    if (line[i] == '+')
                    {
                        i++;
                        b->pv += atoi(&line[i]);
                    }
                    else if (line[i] == '-')
                    {
                        i++;
                        b->pv -= atoi(&line[i]);
                    }
                    else
                    {
                        b->pv = atoi(&line[i]);
                    }
                    while(line[i] != ' ')
                        i++;
                    i++;
                    break;
                case 1:
                    if (line[i] == '+')
                    {
                        b->a_bouger = 2;
                        i++;
                        b->x += atof(&line[i]);
                    }
                    else if (line[i] == '-')
                    {
                        b->a_bouger = 3;
                        i++;
                        b->x -= atof(&line[i]);
                    }
                    else
                        b->x = atof(&line[i]);
                    while(line[i] != ' ')
                        i++;
                    i++;
                    break;
                case 2:
                    if (line[i] == '+')
                    {
                        b->a_bouger = 4;
                        i++;
                        b->y += atof(&line[i]);
                    }
                    else if (line[i] == '-')
                    {
                        b->a_bouger = 5;
                        i++;
                        b->y -= atof(&line[i]);
                    }
                    else
                        b->y = atof(&line[i]);
                    while(line[i] != ' ')
                        i++;
                    i++;
                    break;
                case 3:
                    if (b->angle == 'a')
                        b->a_bouger = 6;
                    else if (b->angle == 'b')
                        b->a_bouger = 7;
                    else if (b->angle == 'k')
                        b->a_bouger = 8;
                    else if (b->angle == 'e')
                        b->a_bouger = 9;
                    b->angle = line[i];
                    i += 2;
                    break;
                case 4:
                    b->state = line[i];
                    i += 2;
                    break;
            }
            b->a_bouger = 1;
        }
    }
}
