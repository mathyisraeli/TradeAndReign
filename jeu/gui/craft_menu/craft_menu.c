#include "craft_menu.h"

void craft_menu(void)
{
    int moix;
    int moiy;
    switch (moi->angle)
    {
        case 'a':
            moix = (int)moi->x - 1;
            moiy = (int)moi->y - 1;
            break;
        case 'b':
            moix = (int)moi->x;
            moiy = (int)moi->y - 1;
            break;
        case 'c':
            moix = (int)moi->x + 1;
            moiy = (int)moi->y - 1;
            break;        
        case 'd':
            moix = (int)moi->x + 1;
            moiy = (int)moi->y;
            break;
        case 'e':
            moix = (int)moi->x + 1;
            moiy = (int)moi->y + 1;
            break;
        case 'f':
            moix = (int)moi->x;
            moiy = (int)moi->y + 1;
            break;
        case 'g':
            moix = (int)moi->x - 1;
            moiy = (int)moi->y + 1;
            break;
        case 'h':
            moix = (int)moi->x - 1;
            moiy = (int)moi->y;
            break;
    }
    for (int i = 0; 10 > i; i++)
    {
        sprintf(main_menu->menuCraft->selector->options[i], "%s %d", moi->items[i], moi->items_cnt[i]);
    }

    drawSelector(renderer, main_menu->menuCraft->selector);
    
    if (lettres->keystates[SDL_SCANCODE_ESCAPE])
        main_menu->menuCraft->on = 0;
    if (lettres->keystates[SDL_SCANCODE_S] || lettres->keystates[SDL_SCANCODE_DOWN])
        main_menu->menuCraft->selector->selectedOption = (main_menu->menuCraft->selector->selectedOption + 1) % main_menu->menuCraft->selector->numOptions;
    if (lettres->keystates[SDL_SCANCODE_Z] || lettres->keystates[SDL_SCANCODE_UP])
        main_menu->menuCraft->selector->selectedOption = (main_menu->menuCraft->selector->selectedOption - 1 + main_menu->menuCraft->selector->numOptions) % main_menu->menuCraft->selector->numOptions;
    if (lettres->keystates[SDL_SCANCODE_RETURN])
        main_menu->menuCraft->selector->selectedOptionArray[main_menu->menuCraft->selector->selectedOption] *= -1;
    
    // wooden pillar
    int wooden_board = 0;
    for (int i = 0; i < 10; i++)
        if (main_menu->menuCraft->selector->selectedOptionArray[i] == 1 && strncmp(main_menu->menuCraft->selector->options[i], "wooden-board", 12) == 0)
            wooden_board += 1;
    if (wooden_board == 9)
    {
        initTextInfo(&main_menu->menuCraft->result_craft, "wooden-pillar", littleFont, 600, 100, 0, (SDL_Color){255, 255, 255, 255}, 0, 0, 0);
        drawTextInfo(renderer, &main_menu->menuCraft->result_craft); 
        if (lettres->keystates[SDL_SCANCODE_O])
        {
            sprintf (ordre + strlen(ordre), "0 %d 16 9 wooden-board ", moi->id);
            //Tester au maximum les 9 carrés possibles qui peuvent contenir (x, y)
            printf ("todo %s %d %d\n", "add_wood_pillar_or_wood_house(", moix,moiy);
        }
    }   
}