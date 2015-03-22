#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED
#include "sprite_list.h"
#define MAX_OBJECTS 16000

typedef struct
{
int sprite;
int x,y,z;
}object_t;

typedef struct
{
sprite_list_t* sprite_list;
object_t objects[MAX_OBJECTS];
int num_objects;
}scene_t;



void scene_new(scene_t* scene,sprite_list_t* sprite_list);
void scene_add_object(scene_t* scene,int sprite,int x,int y,int z);

#endif //SCENE_H_INCLUDED
