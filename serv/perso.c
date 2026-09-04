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
    char line[9999];
    char filename[96];
    sprintf (filename, "%.*s_%d.txt", (int)(strlen(map_path) - 4), map_path, n);
    FILE *fichier = fopen(filename, "w"); // "w" pour écrire (écrase si existe déjà)

    if (fichier == NULL) {
        perror("Erreur lors de la sauvegarde de la liste des personnages");
        return;
    }

    for (int i = 0; i <= list.maxid; i++)
    {
        if (list.data[i].is_active != 1 || list.data[i].pv <= 0)
            continue;
        struct personnages *pa = &list.data[i];
        sprintf(line, "%s %d %d %d %d %d %d %d %d %c %s %s %s %s %d %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d %s %s %s %s %s %s %s %f %f %f %f %f [",
            pa->skin, i, pa->pv, pa->nb_vassaux, pa->faim, pa->inside, pa->house_id, pa->animation, pa->animation_2, pa->angle, pa->physique, pa->nom_de_compte, pa->nom, pa->nom_superieur, pa->echange_player,
            pa->items_cnt[0], pa->items[0], pa->items_cnt[1], pa->items[1], pa->items_cnt[2], pa->items[2], pa->items_cnt[3], pa->items[3], pa->items_cnt[4], pa->items[4], pa->items_cnt[5], pa->items[5],
            pa->items_cnt[6], pa->items[6], pa->items_cnt[7], pa->items[7], pa->items_cnt[8], pa->items[8], pa->items_cnt[9], pa->items[9], pa->items_cnt[10], pa->items[10], pa->items_cnt[11], pa->items[11],
            pa->items[12], pa->items[13], pa->items[14], pa->items[15], pa->items[16], pa->items[17], pa->x, pa->y, pa->altitude, pa->ordrex, pa->ordrey);
        for (struct linked_enemie *p = pa->e_list; p != NULL; p = p->next)
        {
            if (p->next != NULL)
                sprintf (line + strlen(line), "%s %d ", p->nom, p->rang);
            else
                sprintf (line + strlen(line), "%s %d", p->nom, p->rang);
        }
        sprintf(line + strlen(line), "] [%s]%s\n", pa->skill, pa->speak);
        fputs(line, fichier);
    }

    for (struct building *pa = list_building; pa != NULL; pa = pa->next)
    {
        if (pa->pv <= 0)
            continue;
        sprintf(line, "%s %d %d %d %d %c %c\n", pa->skin, pa->id, pa->pv, pa->x, pa->y, pa->angle, pa->state);
        fputs(line, fichier);
    }

    fclose(fichier);
}
