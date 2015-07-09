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

Goomba::Goomba( int startX, int startY): Enemy( startX, startY){
   spriteNum = 3;
   spriteXInit = 0;
   spriteYInit = 0;
   spriteW = 17;
   spriteH = 20;
   spriteOffset = 30;
   initSprite();
   alive = 1;

}

void Goomba::initSprite(){
   for(int i = 0; i < spriteNum; i++){
      enemySpriteClips[i].x = spriteXInit + i*(spriteOffset);
      enemySpriteClips[i].y = spriteYInit;
      enemySpriteClips[i].w = spriteW;
      enemySpriteClips[i].h = spriteH; 
   }
}
void Goomba::move(SDL_Rect* camera){
   //move the enemy loeft or right
   if( mPosX >= camera->x && mPosX <=camera->x+SCREEN_WIDTH){
      mPosX += mVelX;

   //if object reaches the end of the screen then bounce back
      if( (mPosX + blockSize > LEVEL_WIDTH) || (mPosX < 0) ){
         mVelX*=(-1);
      }
      
      //move the enemy vertifcally
      mPosY+=mVelY;

      frame++; //each time move is called, proress goombas frame count
      decideFrame(); //decide what frame  the sprite should be on
                          //this will differentiate for 
                          //different enemies
   }
   //update hitbox
   hitBox.x = mPosX;
   hitBox.y = mPosY;

   mVelY = 5; //assume goomba is always falling

}

void Goomba::decideFrame(){
   if(alive){
      if((frame/frameDelay) >= (spriteNum - 1)){
         frame = 0;
      }
   }else{
      frame = (3*frameDelay)-2; //this should make the sprite the squish
      deathCount++; //increment time its been dead
      /*if(deathCount >= 23){
         alive = 2; //just some flag value
      }*/
   }

}

int Goomba::marioCollision(int cameraX, SDL_Rect  mario, double Myvelocity){

   if(mPosX >= cameraX && mPosX < cameraX+SCREEN_WIDTH){
      if(alive){
         if(topCollision(cameraX, mario, Myvelocity)){
cout<<"mario killed enemy"<<endl;
            alive = 0;
            mPosX-=mVelX;
            mVelX = 0;
            hitBox.h-=10;//make lil goomba appear on ground
            return 1; // make mario hop up a bit
         }
      }
   }
   return 0;
}
