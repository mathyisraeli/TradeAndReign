#include "select_sprite.h"

char how_display(char *skin)
{
	if (strcmp(skin, "ship1") == 0 /*|| strcmp(skin, "tour") == 0*/)
		return 1;
	if (strcmp(skin, "tour") == 0)
		return 2;
	return 0;
}

SDL_Texture *select_good_img(int skin, char angle, int animation, int animation2)
{
	switch(skin)
	{
		case 21:
			return img->s->tree1Standing;
			break;
		case 22:
			return img->s->tree1Felled;
			break;
		case 3:
            return img->s->drapeauBlanc[angle - 'a'];
			break;
		case 12:
			if (animation2 == 0)
			{
				animation = animation % 6;
				return img->s->littleManEmptyStuff_walking[animation][angle - 'a'];
			}
			else if (animation2 == 1)
			{
				animation = animation % 4;
				return img->s->littleManEmptyStuff_punching[animation][angle - 'a'];
			}
			break;
		case 11:
		    animation = animation % 5;
			return img->s->hoAr[animation][angle - 'a'];
			break;
		case 13:
		    animation = animation % 5;
			return img->s->hoFa[animation][angle - 'a'];
			break;
	}
	return NULL;
}
