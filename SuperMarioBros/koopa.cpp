#include <SDL2/SDL.h>
#include <SDL/SDL_image.h>
#include "Ltexture.h"
#include "enemy.h"
#include "globalVars.h"
#include "koopa.h"
using namespace std;

Koopa::Koopa( int startX, int startY): Enemy( startX, startY){
	//koopas are basic too, nothing else special to them
   spriteNum = 6;
   spriteXInit = 150;
   spriteYInit = 0;
   spriteW = 17;
   spriteH = 23;
   spriteOffset = 30;
   initSprite();

   hitCount = 0;
}

void Koopa::initSprite(){
   //load first four basic motion parts
   for(int i = 0; i < (spriteNum-2); i++){
      enemySpriteClips[i].x = spriteXInit + i*(spriteOffset);
      enemySpriteClips[i].y = spriteYInit;
      enemySpriteClips[i].w = spriteW;
      enemySpriteClips[i].h = spriteH; 
   }

   //load two shell parts
   int secondInit = 330;
   for(int i = 4, j = 0; i < spriteNum; i++, j++){
      enemySpriteClips[i].x = secondInit + j*(spriteOffset);
      enemySpriteClips[i].y = spriteYInit;
      enemySpriteClips[i].w = spriteW;
      enemySpriteClips[i].h = spriteH;
   } 
}


void Koopa::move(SDL_Rect *camera){
   //move enemy to the left or right
   if( mPosX >= camera->x && mPosX <= camera->x+SCREEN_WIDTH){
      mPosX += mVelX;

      //if object reaches the end of the screen then change direction
      //this set up will be used for object collision
      if( (mPosX + blockSize > LEVEL_WIDTH) || (mPosX < 0) ){
         mVelX *=(-1);
      }

      //move vertically
      mPosY+=mVelY;

      frame++;
      decideFrame();

   }   

   //update hitbox
   hitBox.x = mPosX;
   hitBox.y = mPosY;

   mVelY=5; //assume the koopa is always falling

}

void  Koopa::decideFrame(){
   if(hitCount < 1){
   if(mVelX < 0){
      if( (frame/frameDelay) >= (spriteNum-4)){
         frame = 0;
      }
   } if(mVelX >= 0){
      if( (frame/frameDelay) >= spriteNum-2){
         frame = 2*frameDelay;//4 is the delay number
                     //if went back to 2 it would be on
                     //sprite 0 actually
      }
   }
   }else{
      //deathCount++;
      if( hitCount < 2){
      frame = (6*frameDelay)-1; //this should display the 6th sprite, the shell
      }
      if(hitCount >= 2){
         frame = (6*frameDelay)-1;//always stay in shell
      }
   }
}

int Koopa::marioCollision(int cameraX, SDL_Rect mario, double Myvelocity){
   if(mPosX >= cameraX && mPosX < cameraX+SCREEN_WIDTH){
      if(alive || hitCount >= 1){
         if(topCollision(cameraX, mario, Myvelocity)){
            alive = 0;
            hitCount++;
            mPosX -=mVelX;
            if(hitCount < 2){
               mVelX = 0; //shell stops in place
               hitBox.h-=10; //make lil shell appear on the ground
            }else if(hitCount == 2){
               mVelX = 7; //shell zooms fast across screen
               //alive = 0;
            }
            return 1; //make mario bounce up a bit
         }
       }
   }
   return 0;
}
