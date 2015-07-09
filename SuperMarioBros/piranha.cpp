#include <SDL2/SDL.h>
#include <SDL/SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "Ltexture.h"
#include "enemy.h"
#include "globalVars.h"
#include "piranha.h"
using namespace std;

Piranha::Piranha(int num, int x, int y, int w, int h, int offset, int startX, int startY): Enemy(num, x, y, w, h, offset, startX, startY){
   initY = startY; //the plant will oscillate around this point
   //mVelY = -1;
}

void Piranha::move(SDL_Rect* camera){
    //move the enemy up or down
    mPosY +=mVelY;

   //if the plant goes past it bounds upward then start moving back
   if( (mPosY < (initY - blockSize)) && (mVelY <= 0) ) {
      mVelY*=(-1);
   }
   if( (mPosY >= (initY)) && (mVelY > 0) ){
      mVelY*=(-1);
   }

   frame++;
   decideFrame();

   //update hitbox
   hitBox.x = mPosX;
   hitBox.y = mPosY;

}

void Piranha::decideFrame(){
   if( (frame/frameDelay) >= (spriteNum) ){
      frame = 0;
   }
}
