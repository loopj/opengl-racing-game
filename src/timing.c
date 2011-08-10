#include "global.h"
#include <time.h>

#define FRAME_COUNT 10

static int	then = 0;
static int	frames = 0;
static int	timeinit = 0;
static float	fps = 300;

int timeframe(){
  int now = SDL_GetTicks();

  if (!timeinit) { 
    then = SDL_GetTicks();
    timeinit = 1;
  }

  frames++;
    
  if(frames >= FRAME_COUNT){
    float seconds = (float)(now-then)/1000.0;

    now = SDL_GetTicks();
    fps = (float)frames / seconds;
    frames = 0;
    then = now;
  }

  return 1;
}

int get_fps(){
  return fps;
}
