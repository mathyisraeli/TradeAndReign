#include "trade_menu.h"

void echange_item(struct personnages *perso1, struct personnages *perso2)
{
	printf ("%s %s\n", perso1->nom, perso2->nom);
	printf ("%s %s\n", perso1->item1, perso1->item2);
	if (strcmp(perso1->item1, "none") == 0)
	{
		for (struct linked_item *p = perso1->i_list; p != NULL; p =p->next)
		{
			if (strcmp(p->nom, perso1->item2) == 0 && p->count >= perso1->count_item2)
			{

				sprintf (ordre + strlen(ordre), "0 %d 16 +%d %s 0 %d 16 %d %s 0 %d 17 none none 0 none 0 ", 
				perso2->id, perso1->count_item2, perso1->item2,
				perso1->id, perso1->count_item2, perso1->item2, 
				perso1->id);
				return;
			}
		}
		sprintf (ordre + strlen(ordre), "0 %d 17 none none 0 none 0 ", perso1->id);
	}
	else if (strcmp(perso1->item2, "none") == 0)
	{
		for (struct linked_item *p = perso2->i_list; p != NULL; p =p->next)
		{
			if (strcmp(p->nom, perso1->item1) == 0 && p->count >= perso1->count_item1)
			{

				sprintf (ordre + strlen(ordre), "0 %d 16 +%d %s 0 %d 16 %d %s 0 %d 17 none none 0 none 0 ", 
				perso1->id, perso1->count_item1, perso1->item1, 
				perso2->id, perso1->count_item1, perso1->item1,
				perso1->id);
				return;
			}
		}
		sprintf (ordre + strlen(ordre), "0 %d 17 none none 0 none 0 ", perso1->id);
	}
	else
	{
		char p1get=0; char p2get = 0;
		for (struct linked_item *p = perso1->i_list; p != NULL; p =p->next)
			if (strcmp(p->nom, perso1->item2) == 0 && p->count >= perso1->count_item2)
				p1get = 1;
		for (struct linked_item *p = perso2->i_list; p != NULL; p =p->next)
			if (strcmp(p->nom, perso1->item1) == 0 && p->count >= perso1->count_item1)
				p2get = 1;
		if (p1get == 1 && p2get == 1)
		{
			sprintf (ordre + strlen(ordre), "0 %d 16 +%d %s 0 %d 16 +%d %s 0 %d 16 %d %s 0 %d 16 %d %s 0 %d 17 none none 0 none 0 ", 
			perso1->id, perso1->count_item1, perso1->item1, 
			perso2->id, perso1->count_item2, perso1->item2,
			perso1->id, perso1->count_item2, perso1->item2, 
			perso2->id, perso1->count_item1, perso1->item1,
			perso1->id);
		}
		else
			sprintf (ordre + strlen(ordre), "0 %d 17 none none 0 none 0 ", perso1->id);
	}
	
}


void menu_trade(void)
{
    struct personnages *chosen = NULL;
    float distance_chosen = 9;
    TextInfo echange_player = {NULL, littleFont, 600, 10, 0, (SDL_Color){0, 255, 0, 255}, 0, 0, 0};
    for (struct linked_list *l = list; l != NULL; l=l->next)
    {
        if (l->p != moi)
        {
            float s_distance = (l->p->x - moi->x)*(l->p->x - moi->x)+(l->p->y - moi->y)*(l->p->y - moi->y);
            if (s_distance < distance_chosen)
            {
                char is_enemie = 0;
                for (struct linked_enemie *ll = l->p->e_list; ll != NULL; ll=ll->next)
                    if (strcmp(ll->nom, moi->nom) == 0)
                        is_enemie = 1;
                if (is_enemie == 0)
                {
                    chosen = l->p;
                    distance_chosen = s_distance;
                }
            }
        }
    }
    if (chosen != NULL)
    {
        echange_player.text =  chosen->nom;
        drawTextInfo(renderer, &echange_player);
        int j = 0;
        for (struct linked_item *i = moi->i_list; i != NULL; i = i->next)
        {
            sprintf(main_menu->menuInv->selector->options[j], "%s %d/%d", i->nom, min(main_menu->menuTrad->count1, i->count), i->count);
            j += 1;
        }
        while (j < 10)
        {
            strcpy(main_menu->menuInv->selector->options[j], "empty slot");
            j+=1;
        }
        drawSelector(renderer, main_menu->menuInv->selector);
        j = 0;
        for (struct linked_item *i = chosen->i_list; i != NULL; i = i->next)
        {
            sprintf(main_menu->menuTrad->selector2->options[j], "%s %d/%d", i->nom, min(main_menu->menuTrad->count2, i->count), i->count);
            j += 1;
        }
        while (j < 10)
        {
            strcpy(main_menu->menuTrad->selector2->options[j], "empty slot");
            j+=1;
        }
        drawSelector(renderer, main_menu->menuTrad->selector2);
        if (lettres->keystates[SDL_SCANCODE_ESCAPE])
            main_menu->menuTrad->on = 0;
        if (main_menu->menuTrad->tab == -1)
        {
            if (lettres->keystates[SDL_SCANCODE_S] || lettres->keystates[SDL_SCANCODE_DOWN])
                main_menu->menuInv->selector->selectedOption = (main_menu->menuInv->selector->selectedOption + 1) % main_menu->menuInv->selector->numOptions;
            if (lettres->keystates[SDL_SCANCODE_Z] || lettres->keystates[SDL_SCANCODE_UP])
    	        main_menu->menuInv->selector->selectedOption = (main_menu->menuInv->selector->selectedOption - 1 + main_menu->menuInv->selector->numOptions) % main_menu->menuInv->selector->numOptions;
            if (lettres->keystates[SDL_SCANCODE_D] || lettres->keystates[SDL_SCANCODE_RIGHT])
                main_menu->menuTrad->count1 += 1;
            if (lettres->keystates[SDL_SCANCODE_Q] || lettres->keystates[SDL_SCANCODE_LEFT])
                main_menu->menuTrad->count1 -= 1;
        }
        else
        {
            if (lettres->keystates[SDL_SCANCODE_S] || lettres->keystates[SDL_SCANCODE_DOWN])
                main_menu->menuTrad->selector2->selectedOption = (main_menu->menuTrad->selector2->selectedOption + 1) % main_menu->menuTrad->selector2->numOptions;
            if (lettres->keystates[SDL_SCANCODE_Z] || lettres->keystates[SDL_SCANCODE_UP])
    	        main_menu->menuTrad->selector2->selectedOption = (main_menu->menuTrad->selector2->selectedOption - 1 + main_menu->menuTrad->selector2->numOptions) % main_menu->menuTrad->selector2->numOptions;
            if (lettres->keystates[SDL_SCANCODE_D] || lettres->keystates[SDL_SCANCODE_RIGHT])
                main_menu->menuTrad->count2 += 1;
            if (lettres->keystates[SDL_SCANCODE_Q] || lettres->keystates[SDL_SCANCODE_LEFT])
                main_menu->menuTrad->count2 -= 1;
        }
        if (lettres->keystates[SDL_SCANCODE_TAB])
            main_menu->menuTrad->tab *= -1;
        if (lettres->keystates[SDL_SCANCODE_RETURN])
        {
            struct linked_item *i = moi->i_list;
            int a = 0;
            while (a < main_menu->menuInv->selector->selectedOption && i != NULL)
            {
                a += 1;
                i = i->next;
            }
            a = 0;
            struct linked_item *i2 = chosen->i_list;
            while (a < main_menu->menuTrad->selector2->selectedOption && i2 != NULL)
            {
                a += 1;
                i2 = i2->next;
            }
            if (i != NULL && i2 != NULL)
                sprintf (ordre + strlen(ordre), "0 %d 17 %s %s %d %s %d ", chosen->id, moi->nom, i->nom, min(i->count, main_menu->menuTrad->count1), i2->nom, min(i2->count, main_menu->menuTrad->count2));
            else if (i != NULL)
                sprintf (ordre + strlen(ordre), "0 %d 17 %s %s %d none 0 ", chosen->id, moi->nom, i->nom, min(i->count, main_menu->menuTrad->count1));
            else if (i2 != NULL)
                sprintf (ordre + strlen(ordre), "0 %d 17 %s none 0 %s %d ", chosen->id, moi->nom, i2->nom, min(i2->count, main_menu->menuTrad->count2));
        }
    }
    else
        main_menu->menuTrad->on = 0;

}

void accept_trade(void)
{
    struct personnages *echange_player = find_perso_by_name(moi->echange_player);
    if (echange_player == NULL || (echange_player->x - moi->x)*(echange_player->x - moi->x)+(echange_player->y - moi->y)*(echange_player->y - moi->y) > 9)
    {
        sprintf (ordre + strlen(ordre), "0 %d 17 none none 0 none 0 ", moi->id); // decline
        menu_cond->acceptTrade = -1;
    }
    if (lettres->keystates[SDL_SCANCODE_ESCAPE])
        menu_cond->acceptTrade = -1;
    drawTextBox(renderer, &menu_cond->bgEventTextBox, false);
    char text[300];
    sprintf (text, "%s propose you to trade %d %s against %d %s", moi->echange_player, moi->count_item1, moi->item1, moi->count_item2, moi->item2);
    TextInfo text_display = {text,  littleFont, 200, 150,0,{255, 255, 255, 255}, 0,0,0};
    drawSelector(renderer, menu_cond->selector_accept_trade);
    drawTextInfo(renderer, &text_display);
    if (lettres->keystates[SDL_SCANCODE_S] || lettres->keystates[SDL_SCANCODE_DOWN])
    	menu_cond->selector_accept_trade->selectedOption = (menu_cond->selector_accept_trade->selectedOption + 1) % menu_cond->selector_accept_trade->numOptions;
    if (lettres->keystates[SDL_SCANCODE_Z] || lettres->keystates[SDL_SCANCODE_UP])
	    menu_cond->selector_accept_trade->selectedOption = (menu_cond->selector_accept_trade->selectedOption - 1 + menu_cond->selector_accept_trade->numOptions) % menu_cond->selector_accept_trade->numOptions;
    if (lettres->keystates[SDL_SCANCODE_RETURN] == 1)
    {
        if(menu_cond->selector_accept_trade->selectedOption == 0)
            echange_item(moi, find_perso_by_name(moi->echange_player));
        else if(menu_cond->selector_accept_trade->selectedOption == 1)
            sprintf (ordre + strlen(ordre), "0 %d 17 none none 0 none 0 ", moi->id); // decline
        else
        {
            sprintf (ordre + strlen(ordre), "0 %d 17 none none 0 none 0 ", moi->id); // decline
            main_menu->on.isPressed = 1;
            main_menu->menuTrad->on = 1;
        }
        menu_cond->acceptTrade = -1;
    }
}