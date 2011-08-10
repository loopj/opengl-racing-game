#ifndef _GAME_H_
#define _GAME_H_

#include "global.h"

int initgame();
int gamemove(void);
int gamekeys(void);
int drawmap();
int skybox(float width,float height,float length);
int ship(void);
int camera(SHIP ship,GLfloat distance);
int gamedraw(void);
extern float rotplus;
extern float fps;
extern float xdis,oldx,zdis,oldz;
#endif
