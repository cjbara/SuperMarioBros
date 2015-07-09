#include <SDL2/SDL.h>
#include <SDL/SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "Ltexture.h"
#include "enemy.h"
#include "globalVars.h"
#include "goomba.h"
using namespace std;

Goomba::Goomba(int num, int x, int y, int w, int h, int offset, int startX, int startY): Enemy(num, x, y, w, h, offset, startX, startY){
              //all the constructor has to do
              //is construct an enemy class
              //goombas are basic and have no extra requirements
}

void Goomba::move(SDL_Rect* camera){
   //move the enemy loeft or right
   mPosX += mVelX;

   //if object reaches the end of the screen then bounce back
   if( (mPosX + ENEMY_WIDTH > LEVEL_WIDTH) || (mPosX < 0) ){
      mVelX*=(-1);
   }

   frame++; //each time move is called, proress goombas frame count
   decideFrame(); //decide what frame  the sprite should be on
                          //this will differentiate for 
                          //different enemies

   //update hitbox
   hitBox.x = mPosX;
   hitBox.y = mPosY;

}

void Goomba::decideFrame(){
   if((frame/frameDelay) >= (spriteNum - 1)){
      frame = 0;
   }

}
