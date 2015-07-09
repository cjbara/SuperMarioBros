//This is the header file for the mushroom class

#ifndef MUSHROOM_H
#define MUSHROOM_H

#include <SDL2/SDL.h>
#include <SDL/SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "globalVars.h"

using namespace std;

class Mushroom{
   public:
      //initializes the variables
      Mushroom(int, int);
      void move(SDL_Rect*);
      void mapCollision(int, SDL_Rect);
      int marioCollision(int, SDL_Rect);

      //show the enemy on the screen
      void render(int, int);

      //accessor functions
      int getPosX();
      int getPosY();
      SDL_Rect getHitBox();
      int frame;


      bool isActive();
      void setActive();

   private:
      int mPosX, mPosY, initY;
      SDL_Rect hitBox;
      int mVelX, mVelY;

      bool active; //tells if activated/collided with Mario 
      bool goinUp;
      int hitCount;

      SDL_Rect objectSpriteClips[2];
      SDL_Rect spriteLocation;
      void initSprite();
};
#endif
