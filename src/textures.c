#include "global.h"
#include "messages.h"

int getfilter(int filter){
  switch(filter){
    case 0:
      return GL_NEAREST;
    case 1:
      return GL_LINEAR;
    case 2: 
      return GL_NEAREST_MIPMAP_NEAREST;
    case 3: 
      return GL_LINEAR_MIPMAP_NEAREST;
    case 4: 
      return GL_NEAREST_MIPMAP_LINEAR;
    case 5: 
      return GL_LINEAR_MIPMAP_LINEAR;
    default:
      return GL_LINEAR_MIPMAP_NEAREST;
  }
}

int getalpha(int alpha){
  switch(alpha){
    case 3:
      return GL_RGB;
    case 4:
      return GL_RGBA;
    default:
      return GL_RGB;
  }
}

int loadtexture(char *dir, char *file, int filter, int repeat, int id){
  SDL_Surface	*image;
  char		location[6+strlen(dir)+strlen(file)];
  
  sprintf(location,"data/%s/%s",dir,file);

  if((image = IMG_Load(location))){
    glGenTextures(1, &texture[id]);
    glBindTexture(GL_TEXTURE_2D, texture[id]);

    if(repeat){
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }else{
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    }
    
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, getfilter(filter));
    gluBuild2DMipmaps(GL_TEXTURE_2D, getalpha(image->format->BytesPerPixel),
    		      image->w, image->h, getalpha(image->format->BytesPerPixel),
		      GL_UNSIGNED_BYTE, image->pixels);
 
  }else{
    error("Failed to Load Texture");
  }
  
  SDL_FreeSurface(image);
  
  return 1;
}
