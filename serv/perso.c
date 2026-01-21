#include "perso.h"

int parse_new(struct personnages *p, char *line, char *skin, int id)
{
    int i;
    int j;
    char tmpI[10];
    char tmpN[50];
    sscanf(line, "%d %s %f %f %f %f %f %c %d %d %d %s %s %s %s %d %s %s %d %s %d %d %d %c %s %s %s %s %s %s %d %s %n", 
    &p->pv,    p->nom_de_compte, &p->x, &p->y, &p->altitude, &p->ordrex, &p->ordrey, &p->angle, &p->timer_dom, &p->faim, &p->inside, p->nom, 
    p->nom_superieur, p->titre, p->religion, &p->nb_vassaux, p->echange_player, p->item1, &p->count_item1, p->item2, &p->count_item2, &p->animation, &p->animation_2, 
    &p->chemin_is_set, p->left_hand, p->right_hand, p->headgear, p->tunic, p->pant, p->shoes, &p->house_id, p->physique, &i);
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
    i += 2;
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
            append_in_inventory(tmpN, p->i_list, atoi(tmpI));
        }
    }
    i += 3;
    j = 0;
    while (line[i] != ']')
    {
        p->skill[j] = line[i];
        i += 1;
        j += 1;
    }
    i += 2;
    p->skill[j] = 0;
    j = 0;
    while (line[i] != '\n' && line[i] != 0)
    {
        p->speak[j] = line[i];
        i += 1;
        j += 1;
    }
    if(id == -1)
        p->id = find_smalest_valid_id_perso(0);
    else
        p->id = id;
    strcpy (p->skin, skin); 
    p->speak[j] = 0;
    p->moved_x = 0;
    p->moved_y = 0;
    p->vitesse_dep = 0.5;
    return i;
}

void kill(struct personnages *p)
{
	free_linked_enemie(p->e_list);
    free_linked_item(p->i_list);
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
}

int find_smalest_valid_id_perso(int from)
{
    for (int j = from; j <= list.capacity;j++)
        if (list.data[j].is_active == 0)
            return j;
    return -1;
}
