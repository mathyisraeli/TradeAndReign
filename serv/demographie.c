#include "demographie.h"

void make_child(int p1, int p2)
{
	int new = append_empty_perso();
	list.data[new].x = (list.data[p1].x + list.data[p2].x) / 2;
	list.data[new].y = (list.data[p1].y + list.data[p2].y) / 2;
	list.data[new].altitude = (float)altitude((int)list.data[new].x + (int)list.data[new].y * max_x);
	list.data[new].angle = 'a';
	list.data[new].faim = 99999;
	list.data[new].pv = 10;
	list.data[new].ordrex = -1;
	list.data[new].skin[0] = '0'; list.data[new].skin[1] = 0;
	if (rand() & 1)
		list.data[new].physique[0] = list.data[p1].physique[0];
	else
		list.data[new].physique[0] = list.data[p2].physique[0];
	if (rand() & 1)
		list.data[new].physique[1] = list.data[p1].physique[1];
	else
		list.data[new].physique[1] = list.data[p2].physique[1];
	if (rand() & 1)
		list.data[new].physique[2] = list.data[p1].physique[2];
	else
		list.data[new].physique[2] = list.data[p2].physique[2];
	if (rand() & 1)
		list.data[new].physique[3] = list.data[p1].physique[3];
	else
		list.data[new].physique[3] = list.data[p2].physique[3];
	if (rand() & 1)
		list.data[new].physique[4] = list.data[p1].physique[4];
	else
		list.data[new].physique[4] = list.data[p2].physique[4];
	if (rand() & 1)
		list.data[new].physique[5] = list.data[p1].physique[5];
	else
		list.data[new].physique[5] = list.data[p2].physique[5];
    size_t len1 = strlen(list.data[p2].nom);
    size_t len2 = strlen(list.data[p1].nom);

    size_t half1 = len1 / 2;
    size_t half2 = len2 - (len2 / 2);

    memcpy(list.data[new].nom, list.data[p1].nom, half1);
    memcpy(list.data[new].nom + half1, list.data[p2].nom + (len2 / 2), half2);

    list.data[new].nom[half1 + half2] = '\0';
	list.data[new].nom_superieur[0] = '.'; list.data[new].nom_superieur[1] = 0;
	list.data[new].nom_de_compte[0] = '.'; list.data[new].nom_de_compte[1] = 0;
	list.data[new].is_active = 1;
	list.data[new].pv = 10;
	list.data[new].skin[0] = '0'; 	list.data[new].skin[1] = 0;
		list.data[new].items[0][0] = '.';
	list.data[new].items[1][0] = '.';
	list.data[new].items[2][0] = '.';
	list.data[new].items[3][0] = '.';
	list.data[new].items[4][0] = '.';
	list.data[new].items[5][0] = '.';
	list.data[new].items[6][0] = '.';
	list.data[new].items[7][0] = '.';
	list.data[new].items[8][0] = '.';
	list.data[new].items[9][0] = '.';
	list.data[new].items[10][0] = '.';
	list.data[new].items[11][0] = '.';
	list.data[new].items[12][0] = '.';
	list.data[new].items[13][0] = '.';
	list.data[new].items[14][0] = '.';
	list.data[new].items[15][0] = '.';
	list.data[new].items[16][0] = '.';
	list.data[new].items[17][0] = '.';
	list.data[new].house_id = -1;
	list.data[new].inside = -1;
	list.data[new].inside = -1;
	append_perso_bioms(new, (int)(list.data[new].y * 0.04f) * max_x_biom + (int)(list.data[new].x * 0.04f));
}

void create_player(char *line)
{
	int new = append_empty_perso();
	list.data[new].x = rand() % max_x;
	list.data[new].y = rand() % max_y;
    list.data[new].ordrex = -1;

	list.data[new].altitude = altitude((int)list.data[new].x + (int)list.data[new].y * max_x);
	char sexe[20];
	char color[20];
	char size[20];
	list.data[new].house_id = -1;
	int i = 0;
	while (line[i] != ' ')
		i++;
	i++;
	sscanf (line+i, "%s %s %s %s %s\n", list.data[new].nom_de_compte, list.data[new].nom, sexe, color, size);
	if (strcmp(sexe, "man") == 0)
		list.data[new].physique[0] = '0';
	else if (strcmp(sexe, "woman") == 0)
		list.data[new].physique[0] = '1';
	if (strcmp(color, "ivory") == 0)
		list.data[new].physique[1] = '0';
	else if (strcmp(color, "marble") == 0)
		list.data[new].physique[1] = '1';
	else if (strcmp(color, "sand") == 0)
		list.data[new].physique[1] = '2';
	else if (strcmp(color, "gold") == 0)
		list.data[new].physique[1] = '3';
	else if (strcmp(color, "leather") == 0)
		list.data[new].physique[1] = '4';
	else if (strcmp(color, "oak") == 0)
		list.data[new].physique[1] = '5';
	else if (strcmp(color, "bronze") == 0)
		list.data[new].physique[1] = '6';
	else if (strcmp(color, "coffee") == 0)
		list.data[new].physique[1] = '7';
	else if (strcmp(color, "chocolate") == 0)
		list.data[new].physique[1] = '8';
	else if (strcmp(color, "ebony") == 0)
		list.data[new].physique[1] = '9';
	if (strcmp(size, "small") == 0)
		list.data[new].physique[2] = '0';
	if (strcmp(size, "medium") == 0)
		list.data[new].physique[2] = '1';
	if (strcmp(size, "large") == 0)
		list.data[new].physique[2] = '2';
	list.data[new].nom_superieur[0] = '.'; list.data[new].nom_superieur[1] = 0;	
	list.data[new].is_active = 1;
	list.data[new].pv = 10;
	list.data[new].skin[0] = '0'; 	list.data[new].skin[1] = 0;
	list.data[new].items[0][0] = '.';
	list.data[new].items[1][0] = '.';
	list.data[new].items[2][0] = '.';
	list.data[new].items[3][0] = '.';
	list.data[new].items[4][0] = '.';
	list.data[new].items[5][0] = '.';
	list.data[new].items[6][0] = '.';
	list.data[new].items[7][0] = '.';
	list.data[new].items[8][0] = '.';
	list.data[new].items[9][0] = '.';
	list.data[new].items[10][0] = '.';
	list.data[new].items[11][0] = '.';
	list.data[new].items[12][0] = '.';
	list.data[new].items[13][0] = '.';
	list.data[new].items[14][0] = '.';
	list.data[new].items[15][0] = '.';
	list.data[new].items[16][0] = '.';
	list.data[new].items[17][0] = '.';
	list.data[new].angle = 'a';
	list.data[new].faim = 99999;
	list.data[new].inside = -1;
	append_perso_bioms(new, (int)(list.data[new].y * 0.04f) * max_x_biom + (int)(list.data[new].x * 0.04f));
}


int count_pop(int world_id)
{
	
	int cnt = 0;
	for (int i = 0; list.maxid >= i; i++)
	{
		if (list.data[i].is_active == 1 && list.data[i].skin[0] == '0' && list.data[i].skin[1] == 0)
			cnt += 1;
	}
	cnt /= 2;

	FILE *file = fopen("request.txt", "r");
    if (!file) {
        perror("Erreur ouverture request.txt");
        return 0;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (!temp) {
        perror("Erreur ouverture temp.txt");
        fclose(file);
        return 0;
    }

    char line[1024];
    int found = 0;

    while (fgets(line, sizeof(line), file)) {
        int id;

        // Lire le numéro au début de la ligne
        if (sscanf(line, "%d", &id) == 1 && id == world_id) {
            // Ligne trouvée → on la lit (affiche ici en exemple)
            create_player(line);
            found += 1;
        }
		else
        	fputs(line, temp);
    }

    fclose(file);
    fclose(temp);

    // Remplacer l'ancien fichier par le nouveau
    remove("request.txt");
    rename("temp.txt", "request.txt");

	int i = 0;
	int j = list.maxid;
	while (cnt > found)
	{
		while (list.data[i].is_active != 1 || list.data[i].skin[0] != '0' || list.data[i].skin[1] != 0)
			i += 1;
		while (list.data[j].is_active != 1 || list.data[j].skin[0] != '0' || list.data[j].skin[1] != 0)
			j  -= 1;
		make_child(i,j);
		found += 1;
	}


    return found;
}