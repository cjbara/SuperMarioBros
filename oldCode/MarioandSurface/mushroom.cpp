//This file contains all of the functions that will be used to animate the mushroom

#include <SDL2/SDL.h>
#include <SDL/SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <iostream>
#include <string>
#include "mushroom.h"
#include "globalVars.h"

using namespace std;

Mushroom::Mushroom( int startX, int startY){
   //initialze variables
   mPosX = startX;
   mPosY = startY;
   initY = startY;

   //initialize hitbox
   hitBox.x = mPosX+5;
   hitBox.y = mPosY;
   hitBox.h = blockSize;
   hitBox.w = blockSize-5;

   spriteLocation.x = mPosX;
   spriteLocation.y = mPosY;
   spriteLocation.w = blockSize;
   spriteLocation.h = blockSize;

   //velocities
   mVelX = 3;
   mVelY = 0;

   active = 0;
   goinUp = 0;
   hitCount = 0;

   frame = 0;
   initSprite();
   objectSpriteClips[0].x = 180;
   objectSpriteClips[0].y = 30;
   objectSpriteClips[0].h = 20;
   objectSpriteClips[0].w = 20;
}

void Mushroom::move(SDL_Rect* camera){
   if(mPosX >= camera->x && mPosX <= camera->x+SCREEN_WIDTH && active){
      if(mPosY >= initY-blockSize && goinUp){
        mVelY = -2; //rise out of keep as two so next statement works
        mVelX = 0;
        if(mPosY == initY-blockSize) {
           goinUp = 0;
           mVelX = 3;
        }
      }
      mPosX+=mVelX;
      mPosY+=mVelY;
   }


   hitBox.x = mPosX;
   hitBox.y = mPosY+5;//idk why I need the 5 here but I do
   spriteLocation.y = mPosY+5;
   spriteLocation.x = mPosX-camera->x;

   mVelY = 8; //assume mushroom is always falling
}

void Mushroom::mapCollision(int camerax, SDL_Rect object){
   if(active){
      int shroomRight = hitBox.x+hitBox.w;
      int shroomLeft = hitBox.x;
      int shroomTop = hitBox.y;
      int shroomBottom = hitBox.y+hitBox.h;
      //object sides
      int Oright = object.x;
      int Oleft = object.x+object.w;
      int Otop = object.y;
      int Obottom = object.y+object.h;
      //check left and right collisions
      if( ( (mPosX+hitBox.w >= object.x) && (mPosX < object.x) ) || ( (mPosX <= object.x+object.w)  &&  (mPosX+hitBox.w > object.x+object.w) ) ){
         if(  ((mPosY+hitBox.h > object.y) || ( (mPosY) > (object.y) ) ) && ( (mPosY+hitBox.h < (object.y + object.h)) || ( (mPosY) < (object.y + object.h) ) )   ) {
          mPosX -=mVelX;
          mVelX*=(-1);
         }
      }
    //check if collide with ground
      if(shroomBottom >= Otop && shroomTop < Otop){
         if( (shroomRight >= Oleft && shroomLeft <= Oleft) || (shroomLeft <= Oright && shroomRight >= Oright) ){
            mVelY = 0;
         }
      }
   }
}

void Mushroom::render(int camX, int camY){
   if(mPosX >= camX && mPosX <= camX+SCREEN_WIDTH && active){
       SDL_RenderCopy(gRenderer, itemSheet, &objectSpriteClips[frame], &spriteLocation);
   }
}

int Mushroom::getPosX(){
   return mPosX;
}

int Mushroom::getPosY(){
   return mPosY;
}

SDL_Rect Mushroom::getHitBox(){
  return hitBox;
}

bool Mushroom::isActive(){
   return active;
}

void Mushroom::setActive(){
   active = 1;
   goinUp = 1; //for the mushroom to move
}

void Mushroom::initSprite(){
   for(int i = 0; i <1; i++){
      objectSpriteClips[i].x = 100;
      objectSpriteClips[i].y = 100;
      objectSpriteClips[i].w = 20;
      objectSpriteClips[i].h = 20;
   }
}

int Mushroom::marioCollision(int cameraX, SDL_Rect mario){
   bool collisionFlag = 1; //assume a collision
   if(hitBox.y+hitBox.h <= mario.y ) collisionFlag = 0;
   if(hitBox.y >= mario.y+mario.h) collisionFlag = 0;
   if(hitBox.x+hitBox.w <= mario.x) collisionFlag = 0;
   if(hitBox.x >= mario.x+mario.w) collisionFlag = 0;

   if(collisionFlag == 1 && active) {
         active = 0;
   	 return collisionFlag;
   }
   return 0;
}
