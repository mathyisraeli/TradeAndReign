#include "display.h"
#include "shared_var.h"
#include "gui/gui.h"
//#include "SDL2/SDL2_gfxPrimitives.h"

/*void bubble_sort_perso()
{
	for (struct linked_list *par = list; par != NULL; par = par->next)
	{
		for (struct linked_list *par2 = list; par2->next != NULL; par2 = par2->next)
		{
			if ((int)par2->p->y > (int)par2->next->p->y || ((int)par2->p->y == (int)par2->next->p->y && par2->p->x > par2->next->p->x))
			{
				struct personnages *tmp = par2->p;
				par2->p = par2->next->p;
				par2->next->p = tmp;
			}
		}
	}
}*/


void display_ground(void)
{
    if (moi->inside != -1)
        return;

    /* --- Fenêtre de rendu --- */
    int start_x = (int)floor(moi->x) - 24;
    int start_y = (int)floor(moi->y) - 24;
    int end_x   = (int)floor(moi->x) + 24;
    int end_y   = (int)floor(moi->y) + 24;

    if (start_x < 0) start_x = 0;
    if (start_y < 0) start_y = 0;
    if (end_x > max_x) end_x = max_x;
    if (end_y > max_y) end_y = max_y;

    struct to_disp *parcour = list_disp;

    /* Avance jusqu’au premier objet visible */
        while (parcour && (((int)parcour->x - moi->x) * ((int)parcour->x - moi->x) + ((int)parcour->y - moi->y) * ((int)parcour->y - moi->y) > 441))
            parcour = parcour->next;

    int ii = 0;
    SDL_Rect position;

    for (int y = start_y; y < end_y; y++)
    {
        for (int x = start_x; x < end_x; x++)
        {
            float dx = x - moi->x;
            float dy = y - moi->y;

            if (dx*dx + dy*dy > 441)
            {
                ii++;
                continue;
            }

            position.x = (dx - dy) * 34 + 866;
            position.y = (dx + dy) * 17
                       + 450
                       - ground_altitude[ii]
                       + moi->altitude * 38;

            position.w = 68;
            position.h = 34;

            SDL_RenderCopy(renderer, ground_texture[ii], NULL, &position);

            position.y += 17;
            position.h = 89;
            SDL_RenderCopy(renderer, img->t->w1, NULL, &position);

            /* --- Objets / personnages --- */
            while (parcour &&
                   (int)parcour->x == x &&
                   (int)parcour->y == y)
            {
                SDL_QueryTexture(parcour->img, NULL, NULL,
                                 &position.w, &position.h);

                position.x = (parcour->x - moi->x - parcour->y + moi->y) * 34
                           + parcour->offset_x
                           - position.w / 2;

                position.y = (parcour->x - moi->x + parcour->y - moi->y) * 17
                           + parcour->offset_y
                           - position.h
                           - ground_altitude[ii]
                           + moi->altitude * 38;

                if (parcour->p && parcour->p->inside == -1)
                {
                    parcour->p->screenx = position.x;
                    parcour->p->screeny = position.y;
                    parcour->p->sizescreenx = position.w;
                    parcour->p->sizescreeny = position.h;
                }

                SDL_RenderCopy(renderer, parcour->img, NULL, &position);

                parcour = parcour->next;
                while (parcour &&
                      (((int)parcour->x - moi->x) * ((int)parcour->x - moi->x) +
                       ((int)parcour->y - moi->y) * ((int)parcour->y - moi->y) > 441))
                    parcour = parcour->next;
            }

            ii++;
        }
    }
}

		
	    
				
				
				//if (ground_altitude[x + y * max_x] > 5)
				//{
					/*Sint16 pointsx[4] = {position.x, position.x + 34, position.x + 34, position.x};
					Sint16 pointsy[4] = {position.y+17, position.y+34, position.y + 34 + ground_altitude[x + y * max_x], position.y + 17 + ground_altitude[x + y * max_x]};
					Sint16 pointsx2[4] = {position.x+34, position.x + 68, position.x + 68, position.x+34};
					Sint16 pointsy2[4] = {position.y+34, position.y+17, position.y + 17 + ground_altitude[x + y * max_x], position.y + 34 + ground_altitude[x + y * max_x]};
					
					filledPolygonRGBA(renderer, pointsx, pointsy, 4, 74, 71, 51,255);
					filledPolygonRGBA(renderer, pointsx2, pointsy2, 4, 74, 71, 51,255);*/
				//}
				//else
				//{*/
				//	for (int i = 0; i < ground_altitude[x + y * max_x]; i++)
				//	{	
				//		SDL_RenderDrawLine(renderer, position.x, position.y+i+17, position.x+34, position.y+34+i);
				//		SDL_RenderDrawLine(renderer, position.x+34, position.y+i+34, position.x+68, position.y+17+i);
				//	}
				//}
			//}
		
	



void display_all(void)
{/*
	SDL_Rect position;
	int yfrom = 0;
    int xfrom = -1;
	for (struct to_disp *parcour = list_disp; parcour != NULL; parcour=parcour->next)
	{
		int altitude = ground_altitude[(int)parcour->x + (int)parcour->y * max_x];
		if (parcour->p != NULL)
			altitude = parcour->p->altitude*38;
		if (moi->inside == -1)
		{
			//printf ("%d %d %d %d\n", xfrom, yfrom, (int)parcour->x, (int)parcour->y);
			display_ground(xfrom, yfrom, (int)parcour->x, (int)parcour->y);
		}
		xfrom = (int)parcour->x;
		yfrom = (int)parcour->y;
		if ((parcour->x  - moi->x)*(parcour->x  - moi->x) + (parcour->y  - moi->y)*(parcour->y  - moi->y) <= 441)
		{
			SDL_QueryTexture(parcour->img, NULL, NULL, &position.w, &position.h);
			position.x = (parcour->x - moi->x - parcour->y + moi->y) * 34 + parcour->offset_x - position.w/2;
			position.y = (parcour->x - moi->x + parcour->y - moi->y) * 17 + parcour->offset_y - position.h - altitude + 38 * (ground_texture[(int)parcour->x + (int)parcour->y * max_x] == img->t->ea1 || ground_texture[(int)parcour->x + (int)parcour->y * max_x] == img->t->ea2 || ground_texture[(int)parcour->x + (int)parcour->y * max_x] == img->t->ea3) + moi->altitude*38;
		//if (parcour->floor == 1 && moi->inside == -1)
		//	position.y -= altitude;
			if (parcour->p != NULL)
			{
				parcour->p->screenx = position.x;
				parcour->p->screeny = position.y;
				parcour->p->sizescreenx = position.w;
				parcour->p->sizescreeny = position.h;
				if (parcour->p->inside == moi->inside)		
					SDL_RenderCopy(renderer, parcour->img, NULL, &position);
			}
			else if (parcour->b->id == moi->inside || moi->inside == -1) 
			{
				SDL_RenderCopy(renderer, parcour->img, NULL, &position);
			
			}
		}

	}
	if (moi->inside == -1)
		display_ground(xfrom, yfrom, max_x-1, max_y-1);*/
	
}
