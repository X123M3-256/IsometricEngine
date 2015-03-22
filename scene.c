#include "scene.h"
#include "sprite_list.h"

void scene_new(scene_t* scene,sprite_list_t* sprite_list)
{
scene->sprite_list=sprite_list;
scene->num_objects=0;
}

void scene_add_object(scene_t* scene,int sprite,int x,int y,int z)
{
object_t object;
object.sprite=sprite;
object.x=x;
object.y=y;
object.z=z;
scene->objects[scene->num_objects]=object;
scene->num_objects++;
}

