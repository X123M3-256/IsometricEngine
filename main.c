#include <stdio.h>
#include <stdlib.h>
#include "sprite_list.h"
#include "scene.h"
#include "viewport.h"




int main(int argc,char* argv[])
{
SDL_Init(SDL_INIT_VIDEO);
atexit(SDL_Quit);
SDL_Surface* screen=SDL_SetVideoMode(640,480,32,0);

sprite_list_t sprite_list=sprite_list_new();
sprite_list_load(&sprite_list,"orange_box.bmp",-32,-16);
sprite_list_load(&sprite_list,"blue_box.bmp",-32,-16);
sprite_list_load(&sprite_list,"green_box.bmp",-32,-16);


scene_t scene;
scene_new(&scene,&sprite_list);

scene_add_object(&scene,2,64,-64,0);
scene_add_object(&scene,2,32,-64,0);
scene_add_object(&scene,2,0,-64,0);
scene_add_object(&scene,1,64,-32,0);
scene_add_object(&scene,1,32,-32,4);
scene_add_object(&scene,1,0,-32,8);
scene_add_object(&scene,0,64,0,0);
scene_add_object(&scene,1,64,0,16);
scene_add_object(&scene,0,32,0,8);
scene_add_object(&scene,0,0,0,16);
scene_add_object(&scene,1,64,64,0);
scene_add_object(&scene,1,32,64,0);
scene_add_object(&scene,1,0,64,0);
scene_add_object(&scene,2,64,32,0);
scene_add_object(&scene,2,32,32,4);
scene_add_object(&scene,2,0,32,8);

viewport_t viewport;
viewport_new(&viewport,&scene,0,0,0,screen->w,screen->h);
int sp=0,pp=0,mp=0;
    while(!SDL_GetKeyState(NULL)[SDLK_q])
    {
    SDL_PumpEvents();
    SDL_FillRect(screen,NULL,100);
    viewport_render(&viewport,&sprite_list,screen,0,0);
        if(SDL_GetKeyState(NULL)[SDLK_LEFT])viewport_set_position(&viewport,viewport.x-1,viewport.y-1,0);
        else if(SDL_GetKeyState(NULL)[SDLK_RIGHT])viewport_set_position(&viewport,viewport.x+1,viewport.y+1,0);
        if(SDL_GetKeyState(NULL)[SDLK_UP])viewport_set_position(&viewport,viewport.x+1,viewport.y-1,0);
        else if(SDL_GetKeyState(NULL)[SDLK_DOWN])viewport_set_position(&viewport,viewport.x-1,viewport.y+1,0);

        if(SDL_GetKeyState(NULL)[SDLK_SPACE]&&!sp)viewport_rotate(&viewport),sp=1;
        else if(!SDL_GetKeyState(NULL)[SDLK_SPACE])sp=0;

        if(SDL_GetKeyState(NULL)[SDLK_EQUALS]&&!pp)viewport_zoom_in(&viewport),pp=1;
        else if(!SDL_GetKeyState(NULL)[SDLK_EQUALS])pp=0;

        if(SDL_GetKeyState(NULL)[SDLK_MINUS]&&!mp)viewport_zoom_out(&viewport),mp=1;
        else if(!SDL_GetKeyState(NULL)[SDLK_MINUS])mp=0;
    usleep(5000);
    SDL_Flip(screen);
    }
return 0;
}
