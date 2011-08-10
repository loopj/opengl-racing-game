#ifndef _VECTOR_H_
#define _VECTOR_H_

#include "global.h"

float planeheight(PLANE pi,GLfloat x,GLfloat z);
int angle();
float vectorangle(VECTOR a,VECTOR b);
VECTOR makenormal(PLANE pi);
PLANE makeplane(VERTEX a,VECTOR normal);
VECTOR crossproduct(VECTOR a,VECTOR b);
float dotproduct(VECTOR a,VECTOR b);
float magnitude(VECTOR vector);
VECTOR posvector(VERTEX a,VERTEX b);
#endif
