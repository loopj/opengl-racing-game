#ifndef _TERRAIN_H_
#define _TERRAIN_H_

#include "global.h"

float getheight(float x,float z);
PLANE getplane(float x,float z);
int drawmap(MAP *course);
int loadmap(MAP *course);
int getpixel(SDL_Surface *surface,int x,int y);
extern float max;
#endif
