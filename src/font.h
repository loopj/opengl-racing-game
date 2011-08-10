#ifndef _FONT_H_
#define _FONT_H_

#include "global.h"

int fontprint(GLint x,GLint y,char *string,int face,float scale,int bold);
int fontbuild(void);
#endif
