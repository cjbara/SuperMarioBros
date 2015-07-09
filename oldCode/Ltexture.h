#ifndef LTEXTURE_H
#define LTEXTURE_H

#include <SDL2/SDL.h>
#include <SDL/SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "globalVars.h"
using namespace std;

//extern SDL_Renderer* gRenderer;
//extern SDL_Texture* gTexture;

class LTexture{
  public:
        LTexture();
        ~LTexture();
        bool loadFromFile(std::string path );
        void free(); //deallocates texture
        //renders texture at given point
        void render(int x, int y, SDL_Rect* clip = NULL);
        int getWidth();
        int getHeight();
        private:
        SDL_Texture* mTexture;
        int mWidth;
        int mHeight;
};

#endif
