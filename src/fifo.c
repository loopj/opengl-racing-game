#include "global.h"
#include "fifo.h"
#include "main.h"
#include "messages.h"

int readstr(FILE *f, char *string){

  do{
    fgets(string,255,f);
  }while((string[0] == '/') || (string[0] == '\n') || (string[0] == '#'));

  return 1;
}

int linecount(FILE *f){
  int number=0;
  char string[255];
  
  rewind(f);
  while(fgets(string,255,f)){
    if((string[0] != '\n') && (string[0] != '/') && (string[0] != '#'))
      number++;
  }
  rewind(f);
  
  return number;
}

int loadconfig(char *file){
  FILE *filein;
  int numlines,value,x;
  char line[255], option[255];
  
  if(!(filein=fopen(file,"rt")))	error("Missing Config File");
  
  numlines = linecount(filein);

  printf("  Loaded: Config File (%i Variables)\n",numlines);

  for(x=0; x<numlines; x++){  
    readstr(filein, line);
    sscanf (line, "%s = %i", option, &value);

    if     (*option == *"xres")       xres       = value;
    else if(*option == *"yres")       yres       = value;
    else if(*option == *"fullscreen") fullscreen = value;
    else if(*option == *"bpp")        bpp        = value;
    else if(*option == *"debug")      debug      = value;
    else if(*option == *"audio")      audio      = value;
    else if(*option == *"showfps")    showfps    = value;
    else   printf("    Warning: Unused Variable (%s)\n",option);
  }
  
  fclose(filein);
  
  return 1;
}
