#include <stdarg.h>
#include "global.h"
#include "main.h"

int debugf(char *message, ... ){
  if(debug){
    va_list args;
    va_start(args, message);
      printf("# Debug: ");
      vprintf(message, args);
      printf("\n");
    va_end(args);
  }
  
  return 1;
}

int error(char *message, ... ){
  va_list args;
  va_start(args, message);
    fprintf(stderr, "ERROR: ");
    vfprintf(stderr, message, args);
    fprintf(stderr, "\n  (%s)\n", SDL_GetError());
  va_end(args);
  killgame(0);

  return 1;
}

int warning(char *message, ... ){
  va_list args;
  va_start(args, message);
    printf("# Warning: ");
    vprintf(message, args);
    printf("\n");
  va_end(args);

  return 1;
}
