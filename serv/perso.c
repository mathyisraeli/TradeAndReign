#include "perso.h"

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
