#ifndef PIRANHA_H
#define PIRANHA_H

#include <SDL2/SDL.h>
#include <SDL/SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "globalVars.h"
#include "Ltexture.h"
#include "enemy.h"
using namespace std;

class Piranha: public Enemy{
   public:
      Piranha(int, int, int, int, int, int, int, int);
      void move(SDL_Rect*);
      void decideFrame();
   private:
      int initY; //this will be the point it moves around 
      //int mVelY;
};

#endif
