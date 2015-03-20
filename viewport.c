#include "viewport.h"

inline int viewport_project_x(viewport_t* viewport,int x,int y)
{
return (viewport->projection[0]*x+viewport->projection[1]*y)/256+viewport->width/2;
}
inline int viewport_project_y(viewport_t* viewport,int x,int y)
{
return (viewport->projection[2]*x+viewport->projection[3]*y)/256+viewport->height/2;
}

int viewport_is_in_view(viewport_t* viewport,object_t* object)
{
sprite_t* sprite=viewport->scene->sprite_list->sprites+object->sprite;
int sprite_x=viewport_project_x(viewport,object->x-viewport->x,object->y-viewport->y)+sprite->offset_x;
int sprite_y=viewport_project_y(viewport,object->x-viewport->x,object->y-viewport->y)-(object->z>>viewport->scale)+sprite->offset_y;
return sprite_x+sprite->bitmap->w>0&&sprite_y+sprite->bitmap->h>0&&sprite_x<viewport->width&&sprite_y<viewport->height;
}

void viewport_refresh_objects(viewport_t* viewport)
{
int i;
viewport->num_objects=0;
    for(i=0;i<viewport->scene->num_objects;i++)
    {
    object_t* object=viewport->scene->objects+i;
        if(viewport_is_in_view(viewport,object))
        {
        viewport->objects[viewport->num_objects]=viewport->scene->objects[i];
        viewport->num_objects++;
        }
    }
}

void viewport_new(viewport_t* viewport,scene_t* scene,int x,int y,int z,int width,int height)
{
viewport->x=0;
viewport->y=0;
viewport->width=width;
viewport->height=height;
viewport->scale=0;
viewport->projection[0]=256;
viewport->projection[1]=256;
viewport->projection[2]=-128;
viewport->projection[3]=128;
viewport->scene=scene;
viewport_refresh_objects(viewport);
}

void viewport_set_position(viewport_t* viewport,int x,int y,int z)
{
viewport->x=x;
viewport->y=y;
viewport_refresh_objects(viewport);
}
void viewport_zoom_out(viewport_t* viewport)
{
    if(viewport->scale>=SCALE_LEVELS-1)return;
viewport->scale++;
viewport->projection[0]/=2;
viewport->projection[1]/=2;
viewport->projection[2]/=2;
viewport->projection[3]/=2;
viewport_refresh_objects(viewport);
}

void viewport_zoom_in(viewport_t* viewport)
{
    if(viewport->scale<=0)return;
viewport->scale--;
viewport->projection[0]*=2;
viewport->projection[1]*=2;
viewport->projection[2]*=2;
viewport->projection[3]*=2;
viewport_refresh_objects(viewport);
}


void viewport_rotate(viewport_t* viewport)
{
float temp=viewport->projection[0];
viewport->projection[0]=viewport->projection[1];
viewport->projection[1]=-temp;
temp=viewport->projection[2];
viewport->projection[2]=viewport->projection[3];
viewport->projection[3]=-temp;
viewport_refresh_objects(viewport);
}


//Sort array. Insertion sort is chosen because it's simple and adaptive, in future, maybe replace with adaptive merge sort
void viewport_sort(viewport_t* viewport)
{
//Length of the sorted portion of the array. Since 1 element is always sorted, we start this at 1
int sorted_length;
    for(sorted_length=1;sorted_length<viewport->num_objects;sorted_length++)
    {
    int i;
    object_t object=viewport->objects[sorted_length];
        for(i=sorted_length;i>0;i--)
        {
        //Comparison
        int a_y=viewport_project_y(viewport,object.x,object.y);
        int b_y=viewport_project_y(viewport,viewport->objects[i-1].x,viewport->objects[i-1].y);
            if(a_y>b_y||(a_y==b_y&&object.z>viewport->objects[i-1].z))break;
        viewport->objects[i]=viewport->objects[i-1];
        viewport->objects[i-1]=object;
        }
    }
}

void viewport_render(viewport_t* viewport,sprite_list_t* sprite_list,SDL_Surface* surface,int x,int y)
{
int i;
viewport_sort(viewport);

SDL_Rect clip_rect;
clip_rect.x=x;
clip_rect.y=y;
clip_rect.w=viewport->width;
clip_rect.h=viewport->height;
SDL_SetClipRect(surface,&clip_rect);

SDL_FillRect(surface,&clip_rect,0);

SDL_Rect dst_rect;
    for(i=0;i<viewport->num_objects;i++)
    {
    object_t* object=viewport->objects+i;
    sprite_t* sprite=sprite_list->sprites[viewport->scale]+object->sprite;

    dst_rect.x=x+viewport_project_x(viewport,object->x-viewport->x,object->y-viewport->y)+sprite->offset_x;
    dst_rect.y=y+viewport_project_y(viewport,object->x-viewport->x,object->y-viewport->y)-(object->z>>viewport->scale)+sprite->offset_y;
    SDL_BlitSurface(sprite->bitmap,NULL,surface,&dst_rect);
    }

SDL_SetClipRect(surface,NULL);
}
