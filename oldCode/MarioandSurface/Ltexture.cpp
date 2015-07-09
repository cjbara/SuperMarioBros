#include <SDL2/SDL.h>
#include <SDL/SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "Ltexture.h"
#include "globalVars.h"
using namespace std;

//quick stuff
//SDL_Renderer* gRenderer = NULL;
SDL_Texture* gTexture = NULL;

LTexture::LTexture(){
   mTexture = NULL;
   mWidth = 0;
   mHeight = 0;
}

LTexture::~LTexture(){
   free();
}
bool LTexture::loadFromFile(std::string path ){
   //bool success = true;

  //Get rid of preexisting texture
  free();
  SDL_Texture* newTexture = NULL;

  SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str() );
  if(loadedSurface == NULL){
      printf ("Unable to load image in Ltexture class %s! SDL Error: %s\n", "items.bmp", SDL_GetError() );
  }else{
      //Color hey image
      //SDL_SetColorKey(loadedSurface, SDL_True, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

      //create texture from surface pixels
      newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
      if(newTexture == NULL){
         printf("Unable to create texture from %s\n", SDL_GetError() );
      }else {
         //get image dimensions
         mWidth = loadedSurface->w;
         mHeight = loadedSurface->h;
      }
      //get rid of old loaded surface
      SDL_FreeSurface(loadedSurface);
  }
  //return success;
  mTexture = newTexture;
  return mTexture != NULL;
}

void LTexture::free(){
  if(mTexture !=NULL){
     SDL_DestroyTexture(mTexture);
     mTexture = NULL;
     mWidth = 0;
     mHeight = 0;
  }
}

void LTexture::render(int x, int y, SDL_Rect* clip){
   //set rendering space and render to screen
   SDL_Rect renderQuad = {x, y, mWidth, mHeight};

   //set CLip rendering dimensions
   if(clip!= NULL){
      renderQuad.w = 40;
      renderQuad.h = 40;
   }

   SDL_RenderCopy(gRenderer, mTexture, clip, &renderQuad );
}

int LTexture::getWidth(){
   return mWidth;
}

int LTexture::getHeight(){
   return mHeight;
}

