#include "sprite_list.h"

sprite_list_t sprite_list_new()
{
sprite_list_t sprite_list;
sprite_list.num_sprites=0;
return sprite_list;
}

//From http://sdl.beuc.net/sdl.wiki/Pixel_Access
Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
int bpp = surface->format->BytesPerPixel;
/* Here p is the address to the pixel we want to retrieve */
Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
    switch(bpp)
    {
    case 1:
        return *p;
        break;
    case 2:
        return *(Uint16 *)p;
        break;
    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
        break;
    case 4:
        return *(Uint32 *)p;
        break;
    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }
}
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
int bpp = surface->format->BytesPerPixel;
/* Here p is the address to the pixel we want to set */
Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
    switch(bpp)
    {
    case 1:
        *p = pixel;
        break;
    case 2:
        *(Uint16 *)p = pixel;
        break;
    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;
    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
}

SDL_Surface* scale_down(SDL_Surface* surface)
{
SDL_Surface* scaled_surface=SDL_CreateRGBSurface(surface->flags,surface->w/2,surface->h/2,surface->format->BitsPerPixel,surface->format->Rmask,surface->format->Gmask,surface->format->Bmask,surface->format->Amask);
SDL_SetColorKey(scaled_surface,SDL_SRCCOLORKEY,SDL_MapRGB(scaled_surface->format,0,0,0));
int x,y;
    for(y=0;y<scaled_surface->h;y++)
    for(x=0;x<scaled_surface->w;x++)
    {
    putpixel(scaled_surface,x,y,getpixel(surface,x*2,y*2));
    }
return scaled_surface;
}

void sprite_list_load(sprite_list_t* sprite_list,const char* filename,int offset_x,int offset_y)
{
sprite_t sprite;
sprite.bitmap=SDL_LoadBMP(filename);
SDL_SetColorKey(sprite.bitmap,SDL_SRCCOLORKEY,SDL_MapRGB(sprite.bitmap->format,0,0,0));
sprite.offset_x=offset_x;
sprite.offset_y=offset_y;
sprite_list->sprites[0][sprite_list->num_sprites]=sprite;
int i;
    for(i=1;i<SCALE_LEVELS;i++)
    {
    sprite_list->sprites[i][sprite_list->num_sprites].bitmap=scale_down(sprite_list->sprites[i-1][sprite_list->num_sprites].bitmap);
    sprite_list->sprites[i][sprite_list->num_sprites].offset_x=sprite_list->sprites[i-1][sprite_list->num_sprites].offset_x/2;
    sprite_list->sprites[i][sprite_list->num_sprites].offset_y=sprite_list->sprites[i-1][sprite_list->num_sprites].offset_y/2;
    }
sprite_list->num_sprites++;
}
