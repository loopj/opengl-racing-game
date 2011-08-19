#include "global.h"
#include "game.h"
#include "menu.h"
#include "main.h"
#include "terrain.h"
#include "textures.h"
#include "hud.h"
#include "timing.h"
#include "messages.h"
#include "audio.h"
#include "camera.h"

#include "../data/models/ship.mdl"			/* Ship Model */

/* Game Variables */
float xdis,oldx,zdis,oldz;				/* Speedo Variables */
float fps;						/* Initial FPS (Stops divide by 0) */
float rotplus;

int initgame(){
  loadtexture("all",		 "pz.jpg",	4,0,8);
  loadtexture("all",		 "speed.jpg",	4,0,11);
  loadtexture(course[loadc].dir, "lf.jpg",	4,0,2);
  loadtexture(course[loadc].dir, "rt.jpg",	4,0,3);
  loadtexture(course[loadc].dir, "dn.jpg",	4,0,4);
  loadtexture(course[loadc].dir, "up.jpg",	4,0,5);
  loadtexture(course[loadc].dir, "ft.jpg",	4,0,6);
  loadtexture(course[loadc].dir, "bk.jpg",	4,0,7);
  loadtexture(course[loadc].dir, "terrain.jpg",	4,0,9);
  loadtexture(course[loadc].dir, "map.bmp",	4,0,13);
  loadmap    (&course[loadc]);
  
  player.rotvel	=  0;
  player.vel 	=  0;
  player.dir 	=  0;
  player.rotdir =  0;
  player.rot 	=  180;
  player.x   	= -600;
  player.z   	= -1000;

  debugf("Reset Player Variables");
  playmusic("data/music/growler.mp3");
  newgame = 0;
  timestart = SDL_GetTicks();
  printf("\nLoaded Map:\n  %s (data/%s)\n  %s\n\n",
          course[loadc].name, course[loadc].dir,
	  course[loadc].description);

  return 1;
}

int skybox(float width, float height, float length){
  float x=-500,y=-height/2,z=-500;
  int   i,j,vi;
 
  float sb_vertices[8][3] = {
  {x,y,z},{x,y+height,z},{x+width,y+height,z},{x+width,y,z},{x,y,z+length},
  {x+width,y,z+length},{x,y+height,z+length},{x+width,y+height,z+length}};
  
  int sb_texcoords[4][2] = {{1,1},{1,0},{0,0},{0,1}};
  int sb_faces[6][4] = {{3,2,1,0},{4,6,7,5},{0,4,5,3},
                        {6,1,2,7},{0,1,6,4},{5,7,2,3}};
  for(i=0;i<6;i++){
    glBindTexture(GL_TEXTURE_2D, texture[i+2]);
    glBegin (GL_QUADS);
    for(j=0;j<4;j++){
      vi = sb_faces[i][j];
      glTexCoord2f(sb_texcoords[j][0],sb_texcoords[j][1]);
      glVertex3f  (sb_vertices[vi][0],sb_vertices[vi][1],sb_vertices[vi][2]);
    }
    glEnd();
  }

  return 1;
}

int ship(void){
  glTranslatef(-player.x,player.y,-player.z);
    glRotatef(player.xtilt,         1.0f,0.0f,0.0f);	/* Rotate Around X-Axis */
    glRotatef(player.rot + rotplus, 0.0f,1.0f,0.0f);	/* Rotate Around Y-Axis */
    glRotatef(player.ztilt,         0.0f,0.0f,1.0f);	/* Rotate Around Z-Axis */

    glScalef(0.5,0.5,0.5);				/* Squish the Model to half size */
    glBindTexture(GL_TEXTURE_2D, texture[8]);
  
    glBegin (GL_TRIANGLES);
    for(i=0; i<sizeof(face_indicies) / sizeof(face_indicies[0]); i++){
      for(j=0; j<3; j++){
        vi = face_indicies[i][j];
        ti = face_indicies[i][j+3];
      
        /* Ship Boundaries */
        if(vertices[vi][0] > player.xmax) player.xmax = vertices[vi][0];
        if(vertices[vi][2] > player.zmax) player.zmax = vertices[vi][2];
        if(vertices[vi][0] < player.xmin) player.xmin = vertices[vi][0];
        if(vertices[vi][2] < player.zmin) player.zmin = vertices[vi][2];
     
        glTexCoord2f(textures[ti][0], textures[ti][1]);
        glVertex3f(vertices[vi][0], vertices[vi][1], vertices[vi][2]);
      }
    }
    glEnd();
    glScalef(1,1,1);
  glLoadIdentity();

  return 1;
}

int gamedraw(void){

  /* Calculate Timings for this Frame */
  timeframe();

  /* Set up a Blank Screen To Draw on */
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  /* Set the camera focusing on player 10 units away */
  camera(player,10);

  /* Begin Drawing the Level */
  skybox(5000,3000,5000);
  drawmap(&course[loadc]);

  /* Draw the Ship */
  ship();

  /* Draw The HUD Items */
  drawhud();

  /* Draw it to the screen */
  SDL_GL_SwapBuffers();
  return 1;
}

int gamekeys(void){
  /* Key Handling */
  while(SDL_PollEvent(&event)){
    events();
    switch(event.type){
      case SDL_KEYDOWN:
	switch (event.key.keysym.sym){
	  case SDLK_UP:
  	  case SDLK_w:
	    debugf("Key Pressed: Forward");
  	    player.dir = -1;
	    break;
          case SDLK_DOWN:
  	  case SDLK_s:
	    debugf("Key Pressed: Backward");
   	    player.dir = 1;
	    break;
	  case SDLK_LEFT:
   	  case SDLK_a:
	    debugf("Key Pressed: Left");
	    player.rotdir = 1;
	    break;
	  case SDLK_RIGHT:
  	  case SDLK_d:
	    debugf("Key Pressed: Right");
	    player.rotdir = -1;
	    break;
	  case SDLK_SPACE:
	    debugf("Key Pressed: Brake");
	    brakes = 1;
	    break;
	  case SDLK_ESCAPE:
	  case SDLK_q:
	    menu = 1;
	    initmenu();
	    break;
          default:
            break;
        }
	break;
      case SDL_KEYUP:
	switch (event.key.keysym.sym){
	  case SDLK_UP:					/* Forward */
          case SDLK_w: 
            player.dir = 0;
	    break; 
	  case SDLK_DOWN:				/* Backward */
	  case SDLK_s: 
            player.dir = 0;
	    break;
	  case SDLK_LEFT:	    
	  case SDLK_a:					/* Left */
	    if(player.rotdir == 1)			/* Avoid Keylock */
	      player.rotdir = 0;
	    break;
	  case SDLK_RIGHT:
	  case SDLK_d:					/* Right */
	    if(player.rotdir == -1)			/* Avoid Keylock */
	      player.rotdir = 0;
	    break;
	  case SDLK_SPACE:
	    brakes = 0;
	    break;
          default:
	    break;
	}
	break;
      case SDL_QUIT:
	done = 1;
	break;
      default:
	break;
    }
  }
  
  return 1;
}

int gamemove(void){
  float adjust  = (100.0/get_fps());			/* Framerate Correction */
  float scale   = 360;					/* m/s -> km/h */
  float hover   = sin(2*(SDL_GetTicks()/1000.0));

  /* Player Constants */
  player.maxvel = 1800 / scale;				/* Maximum Velocity */
  player.accel  = 5    / scale * adjust;		/* Acceleration */
  player.rotmax = 360  / scale;				/* Maximum Rotational Velocity */
  player.rotacc = 10   / scale * adjust;		/* Rotational Acceleration */

  if(player.rot >= 360)
    player.rot -= 360;
  if(player.rot <= 0)
    player.rot += 360;

    if(player.rotdir == 1){
      if(rotplus <= 30)
        rotplus += 1 * adjust;
    }else if(player.rotdir == -1){
      if(rotplus >= -30)
        rotplus -= 1 * adjust;
    }else{
      if(rotplus > 0)
        rotplus -= 1 * adjust;
      else if(rotplus < 0)
        rotplus += 1 * adjust;
    }

  /* Player Movement */
  player.x   += player.vel * sin(player.rot*degtorad) 	* adjust;
  player.y    = getheight(-player.x, -player.z) + hover + YSHIFT;
  player.z   += player.vel * cos(player.rot*degtorad) 	* adjust;
  player.rot += player.rotvel 				* adjust;

  if(brakes)
    player.dir = 0;

  /* Velocity Calculations */
  if(player.dir > 0){					/* Backward Motion */
    if(player.vel <= 0.5*player.maxvel)
      player.vel += player.accel * player.dir;		/* Accelerate to Max Speed */
  }else if(player.dir < 0){				/* Forward Motion */
    if(player.vel >= -player.maxvel)
      player.vel += player.accel * player.dir;		/* Accelerate to Max Speed */
  }else{
    if(player.vel > 5/scale)
      if(brakes)
        player.vel -= 3*player.accel;			/* Forward Deccel */
      else
        player.vel -= player.accel/2;
    else if(player.vel < -5/scale)
      if(brakes)
        player.vel += 3*player.accel;			/* Forward Deccel */
      else
        player.vel += player.accel/2;			/* Backward Deccel */
    else
      player.vel = 0;					/* Stop Moving */
  }
  
  /* Rotational Velocity Calculations */
  if(player.rotdir > 0){				/* Right Rotation */
    if(player.rotvel <= player.rotmax)
      player.rotvel += player.rotacc * player.rotdir;	/* Accelerate to Max Rotation */
  }else if(player.rotdir < 0){				/* Left Rotation */
    if(player.rotvel >= -player.rotmax)
      player.rotvel += player.rotacc * player.rotdir;	/* Accelerate to Max Rotation */
  }else{
    if(player.rotvel > 0)
      player.rotvel -= player.rotacc;			/* Left Deccel */
    else if (player.rotvel < 0)
      player.rotvel += player.rotacc;			/* Right Deccel */
    else
      player.rotvel = 0;				/* Stop Rotating*/
  }

  return 1;
}
