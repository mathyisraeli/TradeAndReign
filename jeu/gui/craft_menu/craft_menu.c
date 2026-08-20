#include "craft_menu.h"

void craft_menu(void)
{
    for (int i = 0; 10 > i; i++)
    {
        if (moi->items_cnt[i] <= 0 || (moi->items[i][0] == '.' && moi->items[i][1] == '\0'))
            main_menu->menuCraft->selector->options[i][0] = '\0';
        else
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
    if (wooden_board == 1)
    {
        initTextInfo(&main_menu->menuCraft->result_craft, "wooden-stick 4", littleFont, 600, 100, 0, (SDL_Color){255, 0, 255, 255}, 0, 0, 0);
        drawTextInfo(renderer, &main_menu->menuCraft->result_craft);
        if (lettres->keystates[SDL_SCANCODE_O])
        {
            sprintf (ordre + strlen(ordre), "0 %d 16 1 wooden-board 0 %d 16 +4 wooden-stick", moi->id, moi->id);
        }
    }
    else if (wooden_board == 9)
    {
        initTextInfo(&main_menu->menuCraft->result_craft, "wooden-pillar", littleFont, 600, 100, 0, (SDL_Color){255, 255, 255, 255}, 0, 0, 0);
        drawTextInfo(renderer, &main_menu->menuCraft->result_craft); 
        if (lettres->keystates[SDL_SCANCODE_O])
        {
            sprintf (ordre + strlen(ordre), "0 %d 18 0 ", moi->id);
        }
    }   
}