#include "global.h"
#include "vector.h"

/******************************************
 * foobar's phj34rsome vector library     *
 *                                        *
 * posvector:                             *
 * Make a position vector from two points *
 *                                        *
 * magnitude :                            *
 * Find the Magnitude of a vector         *  
 *                                        *
 * dotproduct:                            *
 * Take the dot product of two vectors    * 
 *                                        *
 * crossproduct:                          *
 * Take the cross product of two vectors  *
 *                                        * 
 * makeplane:                             *
 * Make a Plane from a point & its normal *
 *                                        * 
 * makenormal:                            *
 * Make a Normal Vector from a Plane      *
 *                                        *  
 * vectorangle:                           *
 * Find the angle between two vectors     * 
 *                                        * 
 * planeheight:                           *
 * Find the Height of plane at (x,z)      *
 ******************************************/

VECTOR posvector(VERTEX a, VERTEX b){
  VECTOR vector;
  
  vector.x = b.x - a.x;
  vector.y = b.y - a.y;
  vector.z = b.z - a.z;
  
  return vector;
}

float magnitude(VECTOR vector){
  return sqrt(pow(vector.x,2)+pow(vector.y,2)+pow(vector.z,2));
}

float dotproduct(VECTOR a, VECTOR b){
  return a.x*b.x + a.y*b.y + a.z*b.z;
}

VECTOR crossproduct(VECTOR a, VECTOR b){
  VECTOR product;

  product.x = (a.y*b.z - a.z*b.y);
  product.y = (a.z*b.x - a.x*b.z);
  product.z = (a.x*b.y - a.y*b.x);

  return product;
}

PLANE makeplane(VERTEX a, VECTOR normal){
  PLANE pi;

  pi.a = normal.x;
  pi.b = normal.y;
  pi.c = normal.z;
  
  pi.d = (normal.x * a.x) + 
         (normal.y * a.y) + 
	 (normal.z * a.z);
  
  return pi;
}

VECTOR makenormal(PLANE pi){
  VECTOR normal;
  
  normal.x = pi.a;
  normal.y = pi.b;
  normal.z = pi.c;
  
  return normal;
}

float vectorangle(VECTOR a, VECTOR b){
  float angle;
  float product;
  float maga, magb;

  product = dotproduct(a, b);
  maga    = magnitude(a);
  magb    = magnitude(b);

  angle   = acos(product / (maga * magb) );
  
  return radtodeg * angle;

}

float planeheight(PLANE pi, GLfloat x, GLfloat z){
  return (pi.d - (pi.a * x) - (pi.c * z)) / pi.b;
}
