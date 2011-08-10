#include "global.h"
#include "terrain.h"
#include "main.h"
#include "init.h"
#include "vector.h"
#include "messages.h"

/* Maximum Value of Heightfield */
float max   = 16777215;

int getpixel(SDL_Surface *surface, int x, int y){
  int bpp = surface->format->BytesPerPixel;
  Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
  switch(bpp) {
    case 1:
      return *p;
    case 2:
      return *(Uint16 *)p;
    case 3:
      if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
        return p[0] << 16 | p[1] << 8 | p[2];
      else
        return p[0] | p[1] << 8 | p[2] << 16;
    case 4:
      return *(Uint32 *)p;
    default:
      return 0;
  }
}

/* Load a Map to the Terrain Array */
int loadmap(MAP *course){
  int x,z,id;
  char temp[50];
  SDL_Surface *mapimg;
  
  debugf("Started Loading Map (%s)",course->dir);
  
  sprintf(temp,"data/%s/%s",course->dir,"map.bmp");

  if(!(mapimg = IMG_Load(temp)))
    error("Missing Level Data");

  course->width  = mapimg->w;
  course->height = mapimg->h;

  if(!(course->y = malloc(sizeof(float)*course->width*(course->height-1))))
    error("Height malloc() Failed");
  else
    debugf("Height malloc() Success!");

  SDL_LockSurface(mapimg);
    for(id=0; id<(course->height-1)*course->width; id++){
      x  = (int)(id % course->width);
      z  = (int)(id / course->width);
      course->y[id] = YSCALE * (1/max) * getpixel(mapimg,x,z);
    }
  SDL_UnlockSurface(mapimg);
  SDL_FreeSurface(mapimg);

  debugf("Finished Loading Map");

  return 1;
}

/* Draw the Currently Loaded Map */
int drawmap(MAP *course){
  int x,z,ida,idb,idc,idd;
  float ua,ub,va,vb;

  /*
     foobar's 31337 quad-based map loading v2
     Draws the data loaded from terrain[id] to
     the screen. Also includes texture co-ords.

     A*****B A*****B
     *  1  * *  2  *
     *     * *     *
     D*****C D*****C
     A*****B A*****B
     *  3  * *  4  *
     *     * *     *
     D*****C D*****C

     Each pixel represents a quad with verteces ABCD
     The shade of the pixel gives rise to the height
     of A1. The Height of B1 = A2, C1 = D2 = B3 = A4 etc.
     Creating a smooth looking plane with stepping
     determined by the resolution of the map image.
  */

  glBindTexture(GL_TEXTURE_2D, texture[9]);
  for(z=0; z<course->height-2; z++){
    for(x=0; x<course->width-2; x++){

      ua  = (float)  x    / (course->width  - 1);
      ub  = (float) (x+1) / (course->width  - 1);
      va  = (float)  z    / (course->height - 1);
      vb  = (float) (z+1) / (course->height - 1);

      ida = ( z    * course->width) +  x   ;
      idb = ( z    * course->width) + (x+1);
      idc = ((z+1) * course->width) + (x+1);
      idd = ((z+1) * course->width) +  x   ;

      glBegin(GL_QUADS);
        /* Quad x,z Corner A */
        glTexCoord2f(ua, va);
        glVertex3f  (XSCALE*x, course->y[ida], ZSCALE*z);

        /* Quad x,z Corner B */	
        glTexCoord2f(ub, va);	
	glVertex3f  (XSCALE*(x+1), course->y[idb], ZSCALE*z);

        /* Quad x,z Corner C */		
        glTexCoord2f(ub, vb);
        glVertex3f  (XSCALE*(x+1), course->y[idc], ZSCALE*(z+1));

        /* Quad x,z Corner D */		
        glTexCoord2f(ua, vb);
        glVertex3f  (XSCALE*x, course->y[idd], ZSCALE*(z+1));
      glEnd();

    }
  }

  return 1;
}

/* Get the Equation of the plane at x,z from the Loaded Map */
PLANE getplane(float x, float z){
  PLANE pi;
  int xf,zf,ida,idb,idc;
  VERTEX a,b,c;
  VECTOR ab,bc,normal;

  xf  = floor(x / XSCALE);
  zf  = floor(z / ZSCALE);

  ida = ((zf)   * course[loadc].width) + (xf);
  idb = ((zf)   * course[loadc].width) + (xf+1);
  idc = ((zf+1) * course[loadc].width) + (xf+1);

  a.x = xf;			b.x = xf + 1;
  a.y = course[loadc].y[ida];	b.y = course[loadc].y[idb];
  a.z = zf;			b.z = zf;

  c.x = xf + 1;
  c.y = course[loadc].y[idc];
  c.z = zf + 1;

  ab     = posvector(a,b);
  bc     = posvector(b,c);
  normal = crossproduct(ab,bc);
  pi     = makeplane(a,normal);

  return pi;
}

/* Get the height at x,z from the Loaded Map */
float getheight(float x, float z){
  PLANE alpha;
  float currentheight,xloc,zloc;

  xloc  = x / XSCALE;
  zloc  = z / ZSCALE;
  alpha = getplane(x,z);

  currentheight = planeheight(alpha,xloc,zloc);
  
  return currentheight+5;
}

