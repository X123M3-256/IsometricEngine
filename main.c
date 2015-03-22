#include <stdio.h>
#include <stdlib.h>
#include "sprite_list.h"
#include "scene.h"
#include "viewport.h"


void printfps()
{
static int milliseconds=0;
int newmilliseconds=SDL_GetTicks();
printf("FPS: %.1f\n",1000.0/(newmilliseconds-milliseconds));
milliseconds=newmilliseconds;
}

int main(int argc,char* argv[])
{
SDL_Init(SDL_INIT_VIDEO);
atexit(SDL_Quit);
SDL_Surface* screen=SDL_SetVideoMode(640,480,32,0);

sprite_list_t sprite_list=sprite_list_new();
//int terrain_sprites=
sprite_list_load(&sprite_list,"tiles.bmp");
sprite_list_add_sprite(&sprite_list,0,0,0,64,64,-32,-32);
sprite_list_add_sprite(&sprite_list,0,0,64,64,64,-32,-32);
sprite_list_add_sprite(&sprite_list,0,0,128,64,64,-32,-32);

scene_t scene;
scene_new(&scene,&sprite_list);

int i,j;
    for(i=0;i<100;i++)
    for(j=0;j<100;j++)
    {
    scene_add_object(&scene,2,i*32,j*32,0);
    }

viewport_t viewport;
viewport_new(&viewport,&scene,0,0,0,screen->w/2,screen->h/2);
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
    SDL_Flip(screen);
    printfps();
    }
return 0;
}
