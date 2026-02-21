#include "perso.h"

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

void kill(struct personnages *p)
{
	free_linked_enemie(p->e_list);
	struct personnages *s = find_perso_by_name(p->nom_superieur);
    if (s != NULL)
    {
    	s->nb_vassaux -= 1;
        s->a_bouger = 1;
    }
}

struct personnages *find_perso_by_name(char *name)
{
    for (int i = 0; i <= list.maxid; i++)
        if (0 < list.data[i].pv && strcmp(list.data[i].nom, name) == 0)
            return &list.data[i];
    return NULL;
}

void save_map(int n)
{
    /*
    char line[9999];
    char filename[20];
    sprintf (filename, "map-%d.txt", n);
    FILE *fichier = fopen(filename, "w"); // "w" pour écrire (écrase si existe déjà)

    if (fichier == NULL) {
        perror("Erreur lors de la sauvegarde de la liste des personnages");
        return;
    }


    for (int i = 0; i <= list.maxid; i++)
    {
        if (list.data[i].pv <= 0)
            continue;
        struct personnages* pa = &list.data[i];
        sprintf(line, "%s %d %d %s %f %f %f %f %f %c %d %d %d %s %s %s %s %d %s %s %d %s %d %d %d %d %s %s %s %s %s %s %d %s [", pa->skin, pa->id, pa->pv, pa->nom_de_compte, pa->x, pa->y, pa->altitude
            , pa->ordrex, pa->ordrey, pa->angle, pa->timer_dom, pa->faim, pa->inside, pa->nom, pa->nom_superieur, pa->titre, pa->religion, pa->nb_vassaux, pa->echange_player, pa->item1, pa->count_item1, pa->item2, pa->count_item2, pa->animation, pa->animation_2, pa->chemin_is_set, pa->left_hand,pa->right_hand, pa->headgear, pa->tunic, pa->pant, pa->shoes, pa->house_id, pa->physique);
		for (struct linked_enemie *p = pa->e_list; p != NULL; p = p->next)
		{
		    if (p->next != NULL)
		        sprintf (line + strlen(line), "%s %d ", p->nom, p->rang);
		    else
		        sprintf (line + strlen(line), "%s %d", p->nom, p->rang);
		}
		strcat(line, "] [");
		for (struct linked_item *p = pa->i_list; p != NULL; p =p->next)
		{
			if (p->next != NULL)
                sprintf (line + strlen(line), "%s %d ", p->nom, p->count);
            else
                sprintf (line + strlen(line), "%s %d", p->nom, p->count);
        }
		sprintf(line + strlen(line),  "] [%s] %s\n", pa->skill, pa->speak);
        fputs(line, fichier);
       // printf ("%s\n",line);
    }

    for (struct building *pa = list_building; pa != NULL; pa = pa->next)
    {
        sprintf(line, "%s %d %d %d %d %c %c\n", pa->skin, pa->id, pa->pv, pa->x, pa->y, pa->angle,pa->state);
        fputs(line, fichier);
    }

    fclose(fichier); 
    */ n = n;
}

int find_smalest_valid_id_perso(int from)
{
    for (int j = from; j <= list.capacity;j++)
        if (list.data[j].is_active == 0)
            return j;
    return -1;
}
