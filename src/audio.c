#include "global.h"
#include "main.h"
#include "messages.h"

int initaudio(void){
  if(SDL_InitSubSystem(SDL_INIT_AUDIO) == -1)
    error("Could not initialize audio subsystem");
  else
    debugf("Initialised Audio Subsytem");

  if(Mix_OpenAudio(22060,AUDIO_S16SYS,2,512) < 0){
    warning("Disabling audio (%s)",SDL_GetError());
    audio = 0;
  }else
    debugf("Opened Audio Channel");
  
  return 1;
}

int playsound(char *sound, int repeat){

  if(audio){
    if(sound == NULL){
      Mix_HaltChannel(1);
      Mix_FreeChunk(chunk);
      chunk = NULL;
    }

    if(chunk){
      Mix_HaltChannel(1);
      Mix_FreeChunk(chunk);
      chunk = NULL;
    }

    chunk = Mix_LoadWAV(sound);

    if(chunk == NULL)
      warning("Failed to load sound: %s",sound);
    else
      debugf("Playing Sound: %s",sound);

    Mix_PlayChannel(-1,chunk,repeat);
  }
  
  return 1;
}

int playmusic(char *musicfile){
  if(audio){
    music = Mix_LoadMUS(musicfile);
  
    if(music == NULL)
      warning("Failed to load music: %s",musicfile);
    else
      debugf("Playing Music: %s",musicfile);
  
    Mix_PlayMusic(music, -1);
  }
  
  return 1;
}

int haltmusic(){
  if(audio){
    Mix_HaltMusic();
    Mix_FreeMusic(music);
  }
  
  return 1;
}
