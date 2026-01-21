#include "tree.h"

char watter_around(int coo)
{
    int t1 = -1; int t2 = -1; int t3 = -1; int t4 = -1;
    if (coo % max_x != max_x - 1)
        t1 = ground[coo+1]->texture;
    if (coo % max_x != 0)
        t2 = ground[coo-1]->texture;
    if (max_x * max_y > coo + max_x)
        t3 = ground[coo+max_x]->texture;
    if (coo- max_x > 0)
        t4 = ground[coo-max_x]->texture;
    if (ground[coo]->texture == ea1 || ground[coo]->texture ==  ea2 || ground[coo]->texture == ea3)
        return 2;
    if (t1 == ea1 || t1 ==  ea2 || t1 == ea3 || t2 == ea1 || t2 == ea2 || t2 == ea3 || t3 == ea1 || t3 ==  ea2 || t3 == ea3 || t4 == ea1 || t4 ==  ea2 || t4 == ea3)
        return 1;
    return 0;
}

void ia_arbre(struct personnages *p)
{
    p->animation += 1; 
    if (p->animation > 60)
    {
        if (p->faim > 20)
        {
            char w = watter_around((int)p->x + ((int)p->y)*max_x);
            if (w == 2)
            {
                p->pv -= 1;
                p->a_bouger = 1;
            }
            if (w== 1)
            {   
                if (p->pv > 25)
                {
                    append_in_inventory("fruit", p->i_list, 1);
                    p->faim -= 21;
                    p->animation = 0; 
                    p->a_bouger = 1;
                }
                if (50 > p->pv)
                {
                    p->a_bouger = 1;
                    p->pv += 1;
                }
            }
        }
        else
        {
            p->faim += 1;
            p->animation = 0; 
        }
        if (count_item(p->i_list, "fruit") == 20)
        {
            int j = append_empty_perso();
            sprintf (list.data[j].skin, "01");
            list.data[j].pv = 50;
            sprintf (list.data[j].echange_player, "none");
            sprintf (list.data[j].item1, "none");
            sprintf (list.data[j].item2, "none");
            list.data[j].x = p->x + 1;
            list.data[j].y = p->y;
            list.data[j].count_item1 = 0;
            list.data[j].count_item2 = 0;
            list.data[j].angle = 'a';
            list.data[j].faim = 0;

        }
    }
    /*if (strcmp(p->echange_player, "none") != 0)
    {
        struct personnages *echange_player = find_perso_by_name(p->echange_player);
        if (echange_player != NULL && 9 > (echange_player->x - moi->x)*(echange_player->x - moi->x)+(echange_player->y - moi->y)*(echange_player->y - moi->y))
            echange_item(p, echange_player);
    } *///todo 
}
