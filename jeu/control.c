#include "control.h"
extern struct lettres *lettres;

void deplacement(struct personnages *moi)
{
	if (moi->faim < 0)
	{
		sprintf (ordre + strlen(ordre), "O %d 00 -1 ", moi->id);
	}
	if (moi->animation > 4)
		sprintf (ordre + strlen(ordre), "0 %d 22 0 0 %d 21 0 ", moi->id, moi->id);
	else if (moi->animation_2 > 0)
		sprintf(ordre + strlen(ordre), "0 %d 21 %d ",moi->id, moi->animation +1 );
	else if (lettres->Mouse_Lclick == 1 && lettres->Mouse_Rclick == 1)
	{
		sprintf (ordre + strlen(ordre), "0 %d 22 1 0 %d 21 0 ", moi->id, moi->id);
		struct personnages *closestt = NULL;
		struct building *closest_building = NULL;
		float reach_sq = moi->porte_dom > 0 ? moi->porte_dom * moi->porte_dom : 4.0f;
		float closest = reach_sq;
		float closest_building_dist = reach_sq;
		for (struct linked_list *parcour = list; parcour != NULL; parcour = parcour->next)
		{
			if (parcour->p == moi)
				continue;
			float distx = parcour->p->x - moi->x;
			float disty = parcour->p->y - moi->y;
			float dist = distx * distx + disty * disty;	
			int in_cone = 0;
			/* same tile or adjacent: allow hit regardless of facing (continuous positions) */
			if (dist < 2.5f)
				in_cone = 1;
			else if (moi->angle == 'e') /* +0.7x -0.7y */
				in_cone = (distx > 0 && fabs(disty) <= distx * 1.5f);
			else if (moi->angle == 'a') /* -0.7x +0.7y */
				in_cone = (distx < 0 && fabs(disty) <= -distx * 1.5f);
			else if (moi->angle == 'c') /* -0.7x -0.7y */
				in_cone = (distx < 0 && disty < 0 && distx / (disty + 0.001f) > 0.4f && disty / (distx + 0.001f) > 0.4f);
			else if (moi->angle == 'g') /* +0.7x +0.7y */
				in_cone = (distx > 0 && disty > 0 && distx / (disty + 0.001f) > 0.4f && disty / (distx + 0.001f) > 0.4f);
			else if (moi->angle == 'b') /* -speed in x */
				in_cone = (distx < 0 && fabs(disty) <= -distx * 1.5f);
			else if (moi->angle == 'd') /* -speed in y */
				in_cone = (disty < 0 && fabs(distx) <= -disty * 1.5f);
			else if (moi->angle == 'f') /* +speed in x */
				in_cone = (distx > 0 && fabs(disty) <= distx * 1.5f);
			else if (moi->angle == 'h') /* +speed in y */
				in_cone = (disty > 0 && fabs(distx) <= disty * 1.5f);
			if (in_cone && dist < closest)
			{
				closest = dist;
				closestt = parcour->p;
			}
		}
		/* also check buildings (use continuous moi->x/y, buildings are tile-based) */
		for (struct building *b = list_building; b != NULL; b = b->next)
		{
			/* building center: use tile center (b->x+0.5, b->y+0.5) for same-tile fairness */
			float bx = (float)b->x + 0.5f, by = (float)b->y + 0.5f;
			float distx = bx - moi->x;
			float disty = by - moi->y;
			float dist = distx * distx + disty * disty;
			if (dist > reach_sq)
				continue;
			int in_cone = 0;
			if (dist < 2.5f) /* same tile or adjacent */
				in_cone = 1;
			else if (moi->angle == 'e')
				in_cone = (distx > 0 && fabs(disty) <= distx * 1.5f);
			else if (moi->angle == 'b')
				in_cone = (distx < 0 && fabs(disty) <= -distx * 1.5f);
			else if (moi->angle == 'h')
				in_cone = (disty > 0 && fabs(distx) <= disty * 1.5f);
			else if (moi->angle == 'g')
				in_cone = (distx > 0 && disty > 0 && distx / (disty + 0.001f) > 0.4f && disty / (distx + 0.001f) > 0.4f);
			else if (moi->angle == 'a' || moi->angle == 'c')
				in_cone = (distx < 0 && disty < 0 && distx / (disty + 0.001f) > 0.4f && disty / (distx + 0.001f) > 0.4f);
			else if (moi->angle == 'd')
				in_cone = (disty < 0 && fabs(distx) <= -disty * 1.5f);
			else if (moi->angle == 'f')
				in_cone = (distx > 0 && fabs(disty) <= distx * 1.5f);
			if (in_cone && dist < closest_building_dist)
			{
				closest_building_dist = dist;
				closest_building = b;
			}
		}

		/* choose closest target among personnages and buildings */
		if (closestt || closest_building)
		{
			if (closestt && (!closest_building || closest <= closest_building_dist))
			{
				/* hit personnage (including trees, skin[1]=='1') */
				if (closestt->skin[1] == '1')
				{
					if (closestt->pv -  moi->dom >= 4)
						sprintf(ordre + strlen(ordre), "0 %d 00 -%d ", closestt->id, moi->dom);
					else if (can_add("wooden-board", 1, moi->items, moi->items_cnt) == 1)
						sprintf(ordre + strlen(ordre), "0 %d 00 -1 0 %d 16 +1 wooden-board ", closestt->id, moi->id);
				}
				else
					sprintf(ordre + strlen(ordre), "0 %d 00 -%d ", closestt->id, moi->dom);
			}
			else if (closest_building)
			{
				/* hit building */
				sprintf(ordre + strlen(ordre), "1 %d 00 -%d ", closest_building->id, moi->dom);
			}
		}
	}
	else
	{
		if(lettres->keystates[SDL_SCANCODE_D])//droite
			sprintf (ordre + strlen(ordre), "0 %d 01 +%f 0 %d 02 -%f 0 %d 05 e 0 %d 21 %d ", moi->id, moi->vitesse_dep * 0.707, moi->id, moi->vitesse_dep * 0.707, moi->id, moi->id, moi->animation+1);
		if(lettres->keystates[SDL_SCANCODE_A])
			sprintf (ordre + strlen(ordre), "0 %d 01 -%f 0 %d 02 +%f 0 %d 05 a 0 %d 21 %d ", moi->id, moi->vitesse_dep * 0.707, moi->id, moi->vitesse_dep * 0.707, moi->id, moi->id, moi->animation+1);
		if(lettres->keystates[SDL_SCANCODE_W])
			sprintf (ordre + strlen(ordre), "0 %d 01 -%f 0 %d 02 -%f 0 %d 05 c 0 %d 21 %d ", moi->id, moi->vitesse_dep * 0.707, moi->id, moi->vitesse_dep * 0.707, moi->id, moi->id, moi->animation+1);
		if(lettres->keystates[SDL_SCANCODE_X])
			sprintf (ordre + strlen(ordre), "0 %d 01 +%f 0 %d 02 +%f 0 %d 05 g 0 %d 21 %d ", moi->id, moi->vitesse_dep * 0.707, moi->id, moi->vitesse_dep * 0.707, moi->id, moi->id, moi->animation+1);
		if(lettres->keystates[SDL_SCANCODE_Q])
			sprintf (ordre + strlen(ordre), "0 %d 01 -%f 0 %d 05 b 0 %d 21 %d ", moi->id, moi->vitesse_dep, moi->id, moi->id, moi->animation+1); 
		if(lettres->keystates[SDL_SCANCODE_E])
			sprintf (ordre + strlen(ordre), "0 %d 02 -%f 0 %d 05 d 0 %d 21 %d ", moi->id, moi->vitesse_dep, moi->id, moi->id, moi->animation+1);
		if(lettres->keystates[SDL_SCANCODE_C])
			sprintf (ordre + strlen(ordre), "0 %d 01 +%f 0 %d 05 f 0 %d 21 %d ", moi->id, moi->vitesse_dep, moi->id, moi->id, moi->animation+1);
		if(lettres->keystates[SDL_SCANCODE_Z])
			sprintf (ordre + strlen(ordre), "0 %d 02 +%f 0 %d 05 h 0 %d 21 %d ", moi->id, moi->vitesse_dep, moi->id, moi->id, moi->animation+1);
		if(lettres->keystates[SDL_SCANCODE_SPACE])
			sprintf (ordre + strlen(ordre), "0 %d 31 +3 0 %d 21 %d ", moi->id, moi->id, moi->animation+1);
		if(lettres->keystates[SDL_SCANCODE_V])
		{
			struct building *b = find_building_by_id(building_id[(int)moi->x + (int)moi->y*max_x]);
			if (b != NULL)
			{
				if (b->state == '0')
					sprintf (ordre + strlen(ordre), "1 %d 04 1 ", b->id);
				else
					sprintf (ordre + strlen(ordre), "1 %d 04 0 ", b->id);
			}
		}
		if(lettres->keystates[SDL_SCANCODE_F])
		{
			struct building *b = find_building_by_id(building_id[(int)moi->x + (int)moi->y*max_x]);
			if (b != NULL)
				sprintf (ordre + strlen(ordre), "1 %d 04 2 ", b->id);
		}
		if(lettres->keystates[SDL_SCANCODE_R])
		{
			struct building *b = find_building_by_id(building_id[(int)moi->x + (int)moi->y*max_x]);
			if (b != NULL)
				sprintf (ordre + strlen(ordre), "1 %d 04 3 ", b->id);
		}
		if(lettres->keystates[SDL_SCANCODE_S])
		{
				if (10 > n_item(moi->items) && ground_altitude[((int)moi->y - start_y) * (end_x - start_x) + (int)moi->x - start_x] > 0 && find_building_by_id(building_id[(int)moi->x + ((int)moi->y)*max_x]) == NULL)
				{
					SDL_Texture *t = ground_texture[((int)moi->y - start_y) * (end_x - start_x) + (int)moi->x - start_x];
					if (t == img->t->he1 || t == img->t->he2 || t == img->t->he3 || t == img->t->he4 || t == img->t->he5)
						sprintf (ordre + strlen(ordre), "0 %d 16 +1 herbe 0 %d 08 %d 0 %d 22 2 0 %d 21 0 ", moi->id, moi->id, (int)moi->x + ((int)moi->y)*max_x, moi->id, moi->id);
					else if (t == img->t->sa1 || t == img->t->sa2 || t == img->t->sa3)
						sprintf (ordre + strlen(ordre), "0 %d 16 +1 sable 0 %d 08 %d 0 %d 22 2 0 %d 21 0 ", moi->id, moi->id, (int)moi->x + ((int)moi->y)*max_x, moi->id, moi->id);
					else if (t == img->t->ne1 || t == img->t->ne2 || t == img->t->ne3)
						sprintf (ordre + strlen(ordre), "0 %d 08 %d 0 %d 13 %d ea1 ", moi->id, (int)moi->x + ((int)moi->y)*max_x, moi->id, (int)moi->x + ((int)moi->y)*max_x);
					else if (t == img->t->granit && (strcmp(moi->items[12], "wood pickaxe") == 0 || strcmp(moi->items[12], "stone pickaxe") == 0 || strcmp(moi->items[12], "bronze pickaxe") == 0 || strcmp(moi->items[12], "iron pickaxe") == 0 || strcmp(moi->items[12], "steel pickaxe") == 0))
						sprintf (ordre + strlen(ordre), "0 %d 16 +1 granit 0 %d 08 %d ", moi->id, moi->id, (int)moi->x + ((int)moi->y)*max_x);
					else if (t == img->t->basalt && (strcmp(moi->items[12], "wood pickaxe") == 0 || strcmp(moi->items[12], "stone pickaxe") == 0 || strcmp(moi->items[12], "bronze pickaxe") == 0 || strcmp(moi->items[12], "iron pickaxe") == 0 || strcmp(moi->items[12], "steel pickaxe") == 0))
						sprintf (ordre + strlen(ordre), "0 %d 16 +1 basalt 0 %d 08 %d ", moi->id, moi->id, (int)moi->x + ((int)moi->y)*max_x);
					else if (t == img->t->calcaire && (strcmp(moi->items[12], "wood pickaxe") == 0 || strcmp(moi->items[12], "stone pickaxe") == 0 || strcmp(moi->items[12], "bronze pickaxe") == 0 || strcmp(moi->items[12], "iron pickaxe") == 0 || strcmp(moi->items[12], "steel pickaxe") == 0))
						sprintf (ordre + strlen(ordre), "0 %d 16 +1 calcaire 0 %d 08 %d ", moi->id, moi->id, (int)moi->x + ((int)moi->y)*max_x);
					else if (t == img->t->gres && (strcmp(moi->items[12], "wood pickaxe") == 0 || strcmp(moi->items[12], "stone pickaxe") == 0 || strcmp(moi->items[12], "bronze pickaxe") == 0 || strcmp(moi->items[12], "iron pickaxe") == 0 || strcmp(moi->items[12], "steel pickaxe") == 0))
						sprintf (ordre + strlen(ordre), "0 %d 16 +1 gres 0 %d 08 %d ", moi->id, moi->id, (int)moi->x + ((int)moi->y)*max_x);
					else if (t == img->t->marbre && (strcmp(moi->items[12], "wood pickaxe") == 0 || strcmp(moi->items[12], "stone pickaxe") == 0 || strcmp(moi->items[12], "bronze pickaxe") == 0 || strcmp(moi->items[12], "iron pickaxe") == 0 || strcmp(moi->items[12], "steel pickaxe") == 0))
						sprintf (ordre + strlen(ordre), "0 %d 16 +1 marbre 0 %d 08 %d ", moi->id, moi->id, (int)moi->x + ((int)moi->y)*max_x);
					else if (t == img->t->schiste && (strcmp(moi->items[12], "wood pickaxe") == 0 || strcmp(moi->items[12], "stone pickaxe") == 0 || strcmp(moi->items[12], "bronze pickaxe") == 0 || strcmp(moi->items[12], "iron pickaxe") == 0 || strcmp(moi->items[12], "steel pickaxe") == 0))
						sprintf (ordre + strlen(ordre), "0 %d 16 +1 schiste 0 %d 08 %d ", moi->id, moi->id, (int)moi->x + ((int)moi->y)*max_x);


				}
				//counter_use_item = 0;
			//}
			//counter_use_item += 1;
		}

	}
	if (moi->speak[0] != 0)
	{
        moi->speak_timer --;
    	if (moi->speak_timer <= 0)
        	sprintf (ordre + strlen(ordre), "0 %d 20 \037 ", moi->id);
	}
}