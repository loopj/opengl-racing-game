#ifndef _TEXTURES_H_
#define _TEXTURES_H_

#include "global.h"

int loadtexture(char *dir, char *file,int filter,int scale,int id);
int getfilter(int filter);
int getalpha(int alpha);

#endif
