#include "ground.h"

static const char *texture_string[]= { "lim", "lii", "lis", "qua", "qui", "qug","qus","quz","qzc","qzg","qzs","bas","bai", "bac", "bal", 
    "gra", "gri", "grc", "grt", "grd", "grs", "san", "sai", "sag", "sha", "shv", "shs", "shg", "sht", "shl", "shc", "shi", "mar", 
    "mai", "gys", "gyp", "wat", "soi", "coa", "sal", "snd", "dus", "sno", "gLi", "gqa", "gqz", "gba", "ggr","gsa","gsh","gma","ggy"};
uint8_t *ground_marked;
int *index_check_altitude;
int *index_check_altitude_local;
int *mountain_indices;
int *water_indices;
int *snow_indices;


void recursive_print_ground(struct linked_ground *p)
{
    if (p->next != NULL)
        recursive_print_ground(p->next);
    printf ("%s%d", texture_string[p->texture],p->altitude);
}

void fprint_ground(FILE *fichier, struct linked_ground *p)
{
    int depth = 0;
    for (struct linked_ground *q = p; q != NULL; q = q->next)
        depth++;
    struct linked_ground **stack = malloc(depth * sizeof(struct linked_ground *));
    int i = 0;
    for (struct linked_ground *q = p; q != NULL; q = q->next)
        stack[i++] = q;
    while (i > 0)
    {
        i--;
        fprintf (fichier, "%s%d", texture_string[stack[i]->texture], stack[i]->altitude);
    }
    free(stack);
}

void ground_to_string(void)
{
    for (int i = 0; i < max_y; i++)
    {
        for (int j = 0; j < max_x; j++)
        {
            recursive_print_ground(ground[i*max_x+j]);  
            putchar(' ');
        }
        putchar('\n');
    }
}

int altitude(int index)
{
    int ret = 0;
    for (struct linked_ground *p = ground[index]; p != NULL; p = p->next)
        ret += p->altitude;
    return ret;
}

void print_ground(int index)
{
    for (struct linked_ground *p = ground[index]; p != NULL; p = p->next)
        printf ("%d %d\n", p->texture, p->altitude);
}

int diff_alt(int index ,int index2)
{
    if (ground[index]->texture == wat  && ground[index2]->texture != wat)
    {
        int ret = altitude(index) - altitude(index2);
        if (ret > 1)
            return ret;
        return ret-ground[index]->altitude;
    }
    else if (ground[index2]->texture == wat  && ground[index]->texture != wat)
    {
        int ret = altitude(index) - altitude(index2);
        if (-1 > ret)
            return ret;
        return ret+ground[index2]->altitude;
    }
    return altitude(index) - altitude(index2);
}

int maximum_diff(int index)
{
    switch (ground[index]->texture)
    {
        case wat:
            return 1;
        case snd:
            return 5;
        case dus:
            return 4;
        case soi:
            return 26;
        case sno:
            return 24;
        default:
            return 50;
    }
    return 50;
}

static inline void will_handle_altitude(int index)
{
    if (ground_marked[index])
        return;
    ground_marked[index] = 1;
    index_check_altitude[n_ground_altitude++] = index;
}

void handle_altitude_right(int index)
{
    if (index % max_x != max_x - 1 && (building_id[index+1] == -1 || ground[index]->texture == wat))
    {
        int diff1 = diff_alt(index, index+1);
        if (diff1 < 0 && maximum_diff(index+1) < -diff1)
        {
            will_handle_altitude(index +1);
        }        
        else if (diff1 > 0 && maximum_diff(index) < diff1)
        {
            //if (rand() % 100 < 90 - ((diff1 - 2) * 80) / 48)
            //    will_handle_altitude(index);
            //else
            //{
                add_1_pixel(index+1, ground[index]->texture);
                remove_1_pixel(index);
            //}
        }
    }
}

void handle_altitude_left(int index)
{
    if (index % max_x != 0 && (building_id[index-1] == -1  || ground[index]->texture == wat))
    {
        int diff2 = diff_alt(index, index-1);
        if (diff2 < 0 && maximum_diff(index-1) < -diff2)
        {
            will_handle_altitude(index -1);
        }
        else if (diff2 > 0 && maximum_diff(index) < diff2)
        {
            //if (rand() % 100 < 90 - ((diff2 - 2) * 80) / 48)
            //    will_handle_altitude(index);
            //else
            //{
                add_1_pixel(index-1, ground[index]->texture);
                remove_1_pixel(index);
            //}
        }
    }
}

void handle_altitude_down(int index)
{
    if (index + max_x < max_x * max_y && (building_id[index+max_x] == -1 || ground[index]->texture == wat))
    {
        int diff3 = diff_alt(index, index+max_x);
        if (diff3 < 0 && maximum_diff(index+max_x) < -diff3)
        {
            will_handle_altitude(index +max_x);

        }
        else if (diff3 > 0 && maximum_diff(index) < diff3)
        {
            //if (rand() % 100 < 90 - ((diff3 - 2) * 80) / 48)
            //    will_handle_altitude(index);
            //else
            //{
                add_1_pixel(index+max_x, ground[index]->texture);
                remove_1_pixel(index);
            //}
        }
    }
}

void handle_altitude_up(int index)
{
    if (index - max_x >= 0 && (building_id[index-max_x] == -1 || ground[index]->texture == wat ))
    {
        int diff4 = diff_alt(index, index-max_x);
        if (diff4 < 0 && maximum_diff(index-max_x) < -diff4)
        {
            will_handle_altitude(index -max_x);
        }
        else if (diff4 > 0 && maximum_diff(index) < diff4)
        {
           // if (rand() % 100 < 90 - ((diff4 - 2) * 80) / 48)
           //     will_handle_altitude(index);
           // else
            //{
                add_1_pixel(index-max_x, ground[index]->texture);
                remove_1_pixel(index);
            //}
        }
    }
}


enum Texture texture_from_string(char *str)
{
    for (long unsigned int i = 0; i < sizeof(texture_string)/ sizeof(texture_string[0]); i++) 
        if (strncmp(str, texture_string[i], 3) == 0)
            return (enum Texture)i;
    return -1;
}

void remove_1_pixel(int index)
{
    if (ground[index] == NULL)
        return;
    if (ground[index]->altitude > 1)
    {
        ground[index]->altitude -= 1;
        will_handle_altitude(index);
    }
    else if (ground[index]->next != NULL)
    {
        struct linked_ground *to_rem = ground[index];
        ground[index] = ground[index]->next;
        free(to_rem);
        will_handle_altitude(index);
    }
}

void add_1_pixel_at_bottom(int index, enum Texture texture)
{
    if (ground[index] == NULL)
        return;
    struct linked_ground *parcour =  ground[index];
    while (parcour->next != NULL)
        parcour = parcour->next;
    if (parcour->texture == texture)
        parcour->altitude += 1;
    else
    {
        struct linked_ground *to_add = malloc(sizeof(struct linked_ground));
        to_add->next = NULL;
        to_add->altitude = 1;
        to_add->texture = texture;
        parcour->next = to_add;
    }  
}

void add_1_pixel(int index, enum Texture texture)
{
    //if (index == 0)
    //    printf ("add %d\n", index);
    if (ground[index] == NULL)
        return;
    if (ground[index]->texture == texture)
        ground[index]->altitude += 1;
    else if (ground[index]->texture == wat)
    {
        if (ground[index]->next != NULL && ground[index]->next->texture == texture)
            ground[index]->next->altitude += 1;
        else
        {
            struct linked_ground *to_add = malloc(sizeof(struct linked_ground));
            to_add->next = ground[index]->next;
            to_add->altitude = 1;
            to_add->texture = texture;
            ground[index]->next = to_add;
        }
    }
    else
    {
        struct linked_ground *to_add = malloc(sizeof(struct linked_ground));
        to_add->next = ground[index];
        to_add->altitude = 1;
        to_add->texture = texture;
        ground[index] = to_add;
    }
    will_handle_altitude(index);
    //printf ("add 2\n");
}

void handle_altitude(void)
{
    for (int i = 0; i < n_ground_altitude; i++)
        index_check_altitude_local[i]= index_check_altitude[i];
    int n_ground_altitudee_local = n_ground_altitude;
    n_ground_altitude = 0;

    for (int i = 3; i > 0; i--) {
        int j = rand() % (i + 1); // index aléatoire entre 0 et i
        int temp = rdm_directions[i];
        rdm_directions[i] = rdm_directions[j];
        rdm_directions[j] = temp;
    }


    for (int i = 0; i < n_ground_altitudee_local; i++)
    {
        int index = index_check_altitude_local[i];
        ground_marked[index] = 0;
        //int a =  altitude(0);
        for (int i = 0; i <4 ;i++)
        {
            if (rdm_directions[i] == 1)
                handle_altitude_right(index);
            else if(rdm_directions[i] == 2)
                handle_altitude_left(index);
            else if(rdm_directions[i] == 3)
                handle_altitude_up(index);
            else if(rdm_directions[i] == 4)
                handle_altitude_down(index);
            else
            {
                printf ("qsdmfkj\n");
            }
        }
        //if (a != altitude(0))
        //    printf ("%d %d %d\n", index, a , altitude(0));   
        
    }
}

void create_array(char *ground_string)
{
    int i = 0;
    sscanf (ground_string, "%d %d", &max_x, &max_y);
    while (ground_string[i] != '\n')
        i++;
    i++;
    ground_marked = calloc(max_x * max_y, sizeof(uint8_t));
    index_check_altitude = calloc(max_x * max_y, sizeof(int));
    index_check_altitude_local = calloc(max_x * max_y, sizeof(int));
    mountain_indices = malloc(max_x * max_y * sizeof(int));
    water_indices = malloc(max_x * max_y * sizeof(int));
    snow_indices = malloc(max_x * max_y * sizeof(int));
    ground = calloc(max_x*max_y,sizeof(struct linked_ground*));
    building_altitude = calloc(max_x*max_y, sizeof(uint8_t*));
    building_id = malloc(sizeof(int)*max_x*max_y);
    int j = 0;
    while (j < max_x*max_y)
    {
        while (ground_string[i] != ' ' && ground_string[i] != '\n' && ground_string[i] != 0)
        {
            struct linked_ground *to_add = malloc(sizeof(struct linked_ground));
            to_add->next = NULL;
            to_add->texture = texture_from_string(ground_string + i);
            i += 3;
            to_add->altitude = atoi(ground_string + i);
            if (ground[j] == NULL)
                ground[j] = to_add;
            else
            {
                to_add->next = ground[j];
                ground[j] = to_add;
            }
            while (ground_string[i] >= '0' && '9' >= ground_string[i])
                i += 1;
        }
        
        building_id[j] = -1;
        building_altitude[j] = malloc(40* sizeof(uint8_t));
        while (ground_string[i] != ' ' && ground_string[i] != '\n' && ground_string[i] != 0)
            i++;
        i++;
        j++;
    }
    sprintf (size_background, "%d %d", max_x, max_y);
}

#define SNOW_ELEVATION_THRESHOLD 3200 /* raw altitude units, ~84.2 m */
float bottom_weights[] = {8.0, 1/100000000, 1/1000000, 12.0, 1/10000000, 1/100000000,1/100000000,5.0,1/100000000,1/1000000,1/1000000,22.0,1/100000, 1/10000000, 1/1000000, 
    20.0, 1/1000000, 1/10000000, 1/100000000, 1/1000000, 1/10000000, 6.0, 1/1000000, 1/100000000, 7.0, 1/100000000, 1/100000, 1/100000000, 1/10000000, 1/100000000, 1/10000000, 1/1000000, 10.0, 
    100000000, 1/10000, 3.0, 0, 0.3, 2.0, 2.0, 0.5, 0.2, 0, 0, 0, 0, 0, 0,0,0,0,0};
float top_weights[] = {1.5, 1/100000000, 1/1000000, 0.1, 1/10000000, 1/100000000,1/100000000,0.3,1/100000000,1/1000000,1/1000000,0.8,1/100000, 1/10000000, 1/1000000, 
    0.6, 1/1000000, 1/10000000, 1/100000000, 1/1000000, 1/10000000, 1.0, 1/1000000, 1/100000000, 0.4, 1/100000000, 1/100000, 1/100000000, 1/10000000, 1/100000000, 1/10000000, 1/1000000, 0.05, 
    1/100000000, 1/10000, 0.2, 0, 5.02, 0.03, 2.0, 5.0, 3.0, 0, 0, 0, 0, 0, 0,0,0,0,0};

enum Texture weighted_random_index(const float weights[], int size)
{
    float total = 0.0f;
    for (int i = 0; i < size; i++)
        total += weights[i];
    float random = ((float)rand() / (float)RAND_MAX) * total;
    for (int i = 0; i < size; i++)
    {
        if (random < weights[i])
            return i;
        random -= weights[i];
    }
    return size - 1;
}


/* No mountain tile can receive the new snow, so the melt -> evaporate ->
 * snow cycle has nowhere to close: cancel it entirely for this call and
 * deposit a bottom/intermediate/top layer (ground_gen.py-style) on every
 * tile that isn't currently covered by water instead. */
static void deposit_sediment_layers(void)
{
    int total = max_x * max_y;
    for (int i = 0; i < total; i++)
    {
        if (ground[i]->texture == wat)
            continue;
        add_1_pixel_at_bottom(i, weighted_random_index(bottom_weights, sizeof(bottom_weights) / sizeof(bottom_weights[0])));
        add_1_pixel(i, weighted_random_index(top_weights, sizeof(top_weights) / sizeof(top_weights[0])));
    }
}

void melt_snow()
{
    int mountain_count = 0;
    int water_count = 0;
    int snow_count = 0;

    for (int i = 0; i < max_x*max_y; i++)
    {
        if (ground[i]->texture == wat)
            water_indices[water_count++] = i;
        else if (altitude(i) > SNOW_ELEVATION_THRESHOLD)
            mountain_indices[mountain_count++] = i;
        else if (ground[i]->texture == sno)
            snow_indices[snow_count++] = i;
    }

    if (mountain_count < 200)
    {
        deposit_sediment_layers();
    }
    int total = min(water_count, mountain_count);
    for (int i = 0; i < total; i++)
    {
        if ((rand() & 127) == 0)
        {
            remove_1_pixel(water_indices[i]);
            add_1_pixel(mountain_indices[i], sno);
        }
    }
    for (int i = 0; i < snow_count; i++)
    {
        if ((rand() & 127) == 0)
        {
            remove_1_pixel(snow_indices[i]);
            add_1_pixel(snow_indices[i], wat);
        }
    }
}

void save_ground(int n)
{
    printf ("save ground in\n");
    char filename[96];
    sprintf (filename, "%.*s_%d.txt", (int)(strlen(ground_path) - 4), ground_path, n);
    FILE *fichier = fopen(filename, "w"); // "w" pour écrire (écrase si existe déjà)
    if (fichier == NULL) {
        perror("Erreur lors de la sauvegarde du sol");
        return;
    }
    fprintf (fichier, "%d %d\n", max_x, max_y);

    for (int i = 0; i < max_y; i++)
    {
        for (int j = 0; j < max_x; j++)
        {
            fprint_ground(fichier, ground[i*max_x+j]);
            fputc(j == max_x - 1 ? '\n' : ' ', fichier);
        }
    }
    fclose(fichier);
    printf ("save ground aout\n");
}