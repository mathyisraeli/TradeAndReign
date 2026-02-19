#include "initWorld.h"


void create_array(void)
{
	uint16_t size;
    memcpy(&size, ground_buffer , sizeof(size)); // 2 octets altitude
    size = ntohs(size); 
	uint16_t offset = 2;
	for (uint16_t i = 0; i < size/3; i++)
	{
		switch (ground_buffer[offset++])
		{
			case 0:
				ground_texture[i] = img->t->ea1;
				break;
			case 1:
				ground_texture[i] = img->t->ea2;
				break;
			case 2:
				ground_texture[i] = img->t->ea3;
				break;
			case 3:
				ground_texture[i] = img->t->te1;
				break;
			case 4:
				ground_texture[i] = img->t->te2;
				break;
			case 5:
				ground_texture[i] = img->t->te3;
				break;
			case 6:
				ground_texture[i] = img->t->he1;
				break;
			case 7:
				ground_texture[i] = img->t->he2;
				break;
			case 8:
				ground_texture[i] = img->t->he3;
				break;
			case 9:
				ground_texture[i] = img->t->he4;
				break;
			case 10:
				ground_texture[i] = img->t->he5;
				break;
			case 11:
				ground_texture[i] = img->t->sa1;
				break;
			case 12:
				ground_texture[i] = img->t->sa2;
				break;
			case 13:
				ground_texture[i] = img->t->sa3;
				break;
			case 14:
				ground_texture[i] = img->t->bl1;
				break;
			case 15:
				ground_texture[i] = img->t->bl2;
				break;
			case 16:
				ground_texture[i] = img->t->bl3;
				break;
			case 17:
				ground_texture[i] = img->t->ne1;
				break;
			case 18:
				ground_texture[i] = img->t->ne2;
				break;
			case 19:
				ground_texture[i] = img->t->ne3;
				break;
			case 20:
				ground_texture[i] = img->t->gr1;
				break;
			case 21:
				ground_texture[i] = img->t->gr2;
				break;
			case 22:
				ground_texture[i] = img->t->granit;
				break;
			case 23:
				ground_texture[i] = img->t->basalt;
				break;
			case 24:
				ground_texture[i] = img->t->calcaire;
				break;
			case 25:
				ground_texture[i] = img->t->schiste;
				break;
			case 26:
				ground_texture[i] = img->t->gres;
				break;
			case 27:
				ground_texture[i] = img->t->marbre;
				break;	
		}

		uint16_t alt;
        memcpy(&alt, ground_buffer + offset, sizeof(alt)); // 2 octets altitude
        ground_altitude[i] = ntohs(alt);           // convert network -> host
        offset += sizeof(alt);
	}		
}

