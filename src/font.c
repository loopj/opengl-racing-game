#include "global.h"
#include "font.h"
#include "ortho.h"

int fontbuild(void){
  float cx,cy;
  
  base = glGenLists(256);
  for (i=0; i<256; i++){
    cx = 1-(float)(i%16) / 16.0f;
    cy = 1-(float)(i/16) / 16.0f;
    /* Start Building A List */
    glNewList(base + (255 - i), GL_COMPILE);
      glBegin(GL_QUADS);
        glTexCoord2f(cx-0.0625f,cy);		glVertex2i(0,0);
        glTexCoord2f(cx,        cy);		glVertex2i(32,0);
        glTexCoord2f(cx,        cy-0.0625f);	glVertex2i(32,32);
        glTexCoord2f(cx-0.0625f,cy-0.0625f);	glVertex2i(0,32);
      glEnd();
      glTranslated(20, 0, 0);
    glEndList();
  }
  
  return 1;
}

int fontprint(GLint x, GLint y, char *string, int face, float scale, int bold){
  orthosetup();
  
  if(face == 0)
    glBindTexture(GL_TEXTURE_2D, texture[0]);
  else
    glBindTexture(GL_TEXTURE_2D, texture[12]);
      
  glTranslated(x, y, 0);
  if(scale)
    glScalef(scale,scale,1.0f);
  glListBase(base - 32 + (128*bold));
  glCallLists(strlen(string),GL_BYTE,string);
  orthoreset();

  return 1;
}
