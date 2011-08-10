#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#if defined(__APPLE__)
# include <OpenGL/gl.h>
# include <OpenGL/glu.h>
#else
# include <GL/gl.h>
# include <GL/glu.h>
#endif

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"

#define TITLE		"Race Game"
#define VERSION		"0.5"
#define NUM_TEXTURES	14				/* Number of textures to load */
#define radtodeg	57.295779513			/* 180 / pi */
#define degtorad	0.0174532925			/* pi / 180 */
#define MAP_WIDTH	64
#define MAP_HEIGHT	64
#define XSCALE		50
#define YSCALE		200
#define ZSCALE		50
#define YSHIFT		20
#define COURSES		3

typedef unsigned char  byte;
typedef unsigned short word;
typedef unsigned long dword;

typedef struct{
  GLfloat	x;
  GLfloat	y;
  GLfloat	z;
} VERTEX;

typedef struct{
  GLfloat 	x;
  GLfloat	y;
  GLfloat	z;
} VECTOR;

typedef struct{
  GLfloat	a;
  GLfloat	b;
  GLfloat	c;
  GLfloat	d;
} PLANE;

typedef struct{
  char  *dir;
  char  *name;
  char  *description;
  int	 width;
  int	 height;
  float *y;
  float *u;
  float *v;
} MAP;

typedef struct{
  GLfloat y,u,v;
} MODEL;

typedef struct{
  GLfloat 	x,y,z;					/* position co-ordinates  */
  GLfloat 	vel;					/* x and z velocity	  */
  GLfloat 	dir;					/* motion direction	  */
  GLfloat 	maxvel;					/* maximum velocity	  */
  GLfloat	accel;					/* ship acceleration	  */  
  GLfloat 	rot;					/* rotation (degrees)	  */
  GLfloat 	rotvel;					/* rotation velocity	  */
  GLfloat 	rotdir;					/* rotation direction	  */ 
  GLfloat 	rotmax;					/* maximum rotation rate  */
  GLfloat 	rotacc;					/* rotation acceleration  */
  GLfloat 	xmax,xmin;				/* x width range of ship  */
  GLfloat 	zmax,zmin;				/* z length range of ship */
  GLfloat	xtilt,ztilt;
} SHIP;

/* Config Variables */
int		xres;
int		yres;
int		fullscreen;
int		bpp;
int		debug;
int		audio;
int		showfps;

int		loadc;
int		timestart;
int		done;					/* Game Boolean */
int		menu;					/* Menu Boolean */
int 		light;					/* Light Boolean */
int 		brakes;					/* Light Boolean */
int		newgame;

SDL_Surface	*surface;				/* SDL surface */
SDL_Event       event;					/* Poll SDL Events */
GLuint		base;					/* Display List For Font */
GLuint		texture[NUM_TEXTURES];			/* Texture Memory */
GLint		i,j,vi,ti;				/* Loop Variables */
SHIP		player;					/* Player Ship */
Mix_Chunk	*chunk;					/* Audio */
Mix_Music	*music;					/* Music */
MAP		course[COURSES],loaded;

#endif
