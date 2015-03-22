#ifndef SPRITE_LIST_H_INCLUDED
#define SPRITE_LIST_H_INCLUDED
#include <SDL/SDL.h>

#define SCALE_LEVELS 5
#define MAX_SURFACES 32
#define MAX_SPRITES 32

typedef struct
{
SDL_Surface* bitmap;
SDL_Rect rect;
int offset_x;
int offset_y;
}sprite_t;


typedef struct
{
SDL_Surface* surfaces[SCALE_LEVELS][MAX_SURFACES];
sprite_t sprites[SCALE_LEVELS][MAX_SPRITES];
int num_sprites;
int num_surfaces;
}sprite_list_t;

sprite_list_t sprite_list_new();
int sprite_list_load(sprite_list_t* sprite_list,const char* filename);

#endif // SPRITE_LIST_H_INCLUDED
