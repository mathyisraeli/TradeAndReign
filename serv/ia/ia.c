#include "ia.h"


void ia(void)
{
    for (int i = 0; i < list.maxid;i++)
    {
        if (list.data[i].is_active == 1 && list.data[i].online == '0')
        {
            if (list.data[i].skin[1] == '1')
            {
                ia_arbre(&list.data[i]);
            }
            else if (list.data[i].skin[1] == '2')
                printf("ia_flag\n");
            else
                ia_man(&list.data[i]);
        }
    }
    for (struct building *parcour = list_building; parcour != NULL; parcour = parcour->next)
    {
        if (parcour->skin[1] == '3')
            ia_ship(parcour);
    }
}
