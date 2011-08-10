#ifndef _MAIN_H_
#define _MAIN_H_

#include "global.h"

int main(int argc,char **argv);
int events(void);
int resize(int width,int height);
void killgame(int returnCode);

extern int videoFlags;

#endif
