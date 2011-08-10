#include "global.h"
#include "init.h"
#include "main.h"
#include "terrain.h"
#include "hud.h"
#include "messages.h"
#include "audio.h"

int videoFlags;

int initsdl(void){
  const SDL_VideoInfo *videoInfo;

  if(SDL_Init(SDL_INIT_VIDEO) < 0)
    error("Video initialization failed");

  videoInfo = SDL_GetVideoInfo();

  if(!videoInfo)
    error("Video Query Failed");

  videoFlags  = SDL_OPENGL;
  videoFlags |= SDL_GL_DOUBLEBUFFER;
  videoFlags |= SDL_HWPALETTE;
  videoFlags |= SDL_RESIZABLE;
  
  if(fullscreen == 1)
    videoFlags |= SDL_FULLSCREEN;

  if(videoInfo->hw_available)
    videoFlags |= SDL_HWSURFACE;
  else
    videoFlags |= SDL_SWSURFACE;
  
  if(videoInfo->blit_hw)
    videoFlags |= SDL_HWACCEL;
  
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  surface = SDL_SetVideoMode(xres,yres,bpp,videoFlags);
  SDL_WM_SetCaption(TITLE, VERSION);

  if(!surface)
    error("Set Video Mode Failed");

  resize(xres, yres);

  return 1;
}

int initgl(void){
  glEnable(GL_TEXTURE_2D);
  glShadeModel(GL_SMOOTH);
  glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
  glClearDepth(1.0f);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_ALPHA_TEST);
  glAlphaFunc(GL_GEQUAL, 0.5);
  glDepthFunc(GL_LEQUAL);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

  return 1;
}
