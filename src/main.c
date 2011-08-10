#include "global.h"
#include "init.h"
#include "audio.h"
#include "menu.h"
#include "game.h"
#include "fifo.h"
#include "font.h"
#include "messages.h"

void killgame(int returnCode){
  glDeleteLists(base,256);				/* Delete All 256 Display Lists */
  glDeleteTextures(NUM_TEXTURES, &texture[0]);		/* Clean up our textures */

  if(audio){
    Mix_FreeChunk(chunk);
    Mix_CloseAudio();
    SDL_QuitSubSystem(SDL_INIT_AUDIO);
  }

  SDL_Quit();						/* clean up the window */
  exit(returnCode);					/* Exit appropriately */
}

int resize(int width, int height){
  float ratio;					/* Height / width ratio */
  if(height == 0) height = 1;				/* Protect against a divide by zero */
  ratio = (GLfloat)width / (GLfloat)height;		/* Width to Height Ratio */
  glViewport(0,0,(GLint)width,(GLint)height);		/* Setup our viewport. */
  glMatrixMode(GL_PROJECTION);				/* projection matrix */
  glLoadIdentity();					/* Reset Projection Matrix */
  gluPerspective(70.0f, ratio, 0.1f, 10000.0f);		/* Set our perspective */
  glMatrixMode(GL_MODELVIEW);				/* Model view */
  glLoadIdentity();					/* Reset The View */
  
  return 1;
}

int events(void){
  switch(event.type){
    case SDL_VIDEORESIZE:
      surface = SDL_SetVideoMode(event.resize.w,event.resize.h,16,videoFlags);
      if(!surface)
  	error("Resize Failed");
      resize(event.resize.w,event.resize.h);
      break;
    case SDL_KEYDOWN:
      switch (event.key.keysym.sym){
        case SDLK_F1:
	  SDL_WM_ToggleFullScreen(surface);
	  break;
	default:
	  break;
      }
    default:
      break;
  }
  
  return 1;
}

int main(int argc, char **argv){

  /* Load me from a text file */
  course[0].dir		= "desert";
  course[0].name	= "Canyon Racer";
  course[0].description	= "A scenic drive through the canyons of Fooland";
  
  course[1].dir		= "sea";
  course[1].name	= "Dune Derby";
  course[1].description = "A frantic seaside race between the dunes.";
  
  course[2].dir		= "city";
  course[2].name	= "City Speed";
  course[2].description = "Speedy dash around the city of Foobopolis";

  printf("%s version %s\nCopyleft foobar and judeo (See COPYING for info)\n",TITLE,VERSION);

  loadconfig("config");
  
  if(!initsdl())	error("SDL Loading Failed");
  else			printf("  Loaded: SDL\n");
  
  if(audio){
    if(!initaudio())	error("Audio Loading Failed");
    else		printf("  Loaded: Audio\n");
  }
  
  if(!initgl())		error("OpenGL Loading Failed");
  else			printf("  Loaded: OpenGL\n");
  
  if(!fontbuild())	error("Font Building Failed");
  else			printf("  Loaded: Fonts\n");
  
  if(!loadmenu())	error("Game Initialisation Failed");
  else			printf("  Loaded: Menu\n");

  printf("Initial Loading Complete\n\n");
  
  /* Draw the Screen! */
  while (!done){
    /* Draw The Game */
    if(menu ==  1){
      menukeys();    
      menudraw();
    }else if(menu == 0){
      if(newgame){
        initgame(loadc);
      }else{
        gamedraw();    
        gamekeys();
        gamemove();
      }
    }else if(menu == 2){
      loading();
      menu = 0;
    }
  }

  /* Just in Case */
  error("User Forced Exit");
  return 0;
  
}
