#ifndef _AUDIO_H_
#define _AUDIO_H_

#include "global.h"

int initaudio(void);
int playsound(char *sound, int repeat);
int playmusic(char *musicfile);
int haltmusic();
#endif
