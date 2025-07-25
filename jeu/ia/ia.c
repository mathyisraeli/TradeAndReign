#include "ia.h"

//call when -> one player connect/disconect. One character create/delete
void my_computer_work(struct personnages *moi)
{   
    float nb_player = 0;
    float nb_ai = 0;
    float nb_ai_building;
    int nb_player_lower_id = 0;
    for (struct linked_list *l = list; l != NULL; l = l->next)
    {
        if (l->p->online != '1')
            nb_ai += 1;
        else
        {
            nb_player += 1;
            if (l->p->id < moi->id)
                nb_player_lower_id  += 1;
        }
    }
    for (struct building *par = list_building; par != NULL; par = par->next)
    {
        if (par->skin[1] == '3')
            nb_ai_building += 1;
    }
    int ai_per_player = ceil(nb_ai/nb_player);
    int ai_building_per_player = ceil(nb_ai_building/nb_player);

    int i = 0;
    for (struct linked_list *l = list; l != NULL; l = l->next)
    {
        if (l->p->online != '1')
        {
            if ( i >= nb_player_lower_id * ai_per_player && i < nb_player_lower_id * ai_per_player + ai_per_player)
            {
                l->p->my_computer_work = 1;
                //printf("1 : %s\n", l->p->nom);
            }
            else
            {
                l->p->my_computer_work = 0;
                //printf("0 : %s\n", l->p->nom);
            }
            i += 1;
        }
        else
            l->p->my_computer_work = 0;
    }
    i = 0;
    for (struct building *l = list_building; l != NULL; l = l->next)
    {
        if (l->skin[1] == '3')
        {
            if ( i >= nb_player_lower_id * ai_building_per_player && i < nb_player_lower_id * ai_building_per_player + ai_building_per_player)
            {
                l->my_computer_work = 1;
                //printf("1 : %s\n", l->p->nom);
            }
            else
            {
                l->my_computer_work = 0;
                //printf("0 : %s\n", l->p->nom);
            }
            i += 1;
        }
        else
            l->my_computer_work = 0;
    }
}

void ia(void)
{
    /**/
    for (struct linked_list *parcour = list; parcour != NULL; parcour = parcour->next)
    {
        if (parcour->p->my_computer_work == 1)
        {
            if (parcour->p->skin[1] == '1')
            {
                ia_arbre(parcour->p);
            }
            else if (parcour->p->skin[1] == '2')
                printf("ia_flag\n");
            else
                ia_man(parcour->p);
        }
    }
    for (struct building *parcour = list_building; parcour != NULL; parcour = parcour->next)
    {
        if (parcour->my_computer_work == 1)
        {
            if (parcour->skin[1] == '3')
                ia_ship(parcour);
        }
    }
}