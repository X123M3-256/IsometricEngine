#ifndef SPRITE_LIST_H_INCLUDED
#define SPRITE_LIST_H_INCLUDED
#include <SDL/SDL.h>

#define SCALE_LEVELS 5
#define MAX_SPRITES 32

typedef struct
{
SDL_Surface* bitmap;
int offset_x;
int offset_y;
}sprite_t;


typedef struct
{
sprite_t sprites[SCALE_LEVELS][MAX_SPRITES];
int num_sprites;
}sprite_list_t;

sprite_list_t sprite_list_new();
void sprite_list_load(sprite_list_t* sprite_list,const char* filename,int offset_x,int offset_y);

#endif // SPRITE_LIST_H_INCLUDED
