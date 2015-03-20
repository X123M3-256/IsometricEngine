#ifndef VIEWPORT_H_INCLUDED
#define VIEWPORT_H_INCLUDED
#include "scene.h"
#include "sprite_list.h"

typedef struct
{
int x,y;
int width,height;
int scale;
int projection[4];
int num_objects;
scene_t* scene;
object_t objects[MAX_OBJECTS];
}viewport_t;

void viewport_new(viewport_t* viewport,scene_t* scene,int x,int y,int z,int width,int height);
void viewport_render(viewport_t* viewport,sprite_list_t* sprite_list,SDL_Surface* surface,int x,int y);
void viewport_set_position(viewport_t* viewport,int x,int y,int z);
void viewport_rotate(viewport_t* viewport);
#endif // VIEWPORT_H_INCLUDED
