#include <SDL2/SDL.h>
#include <SDL/SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "Ltexture.h"
#include "enemy.h"
#include "globalVars.h"
using namespace std;

Enemy::Enemy(int Spritenum , int x, int y, int w, int h, int offset, int startX, int startY ){
        //nitializes the positions
        mPosX = startX;
        mPosY = startY;
        hitBox.x = mPosX;
        hitBox.y = mPosY;
        hitBox.h = blockSize-3;
        hitBox.w = blockSize-3;

        //movement of enemies
        mVelX = 1;
        mVelY = -1;

        //clip sprite sheet
        spriteNum = Spritenum;
        spriteXInit = x;
        spriteYInit = y;
        spriteW = w;
        spriteH = h;
        spriteOffset = offset;
        initSprite();
        frame = 0;
        frameDelay = 4; 

	loadTexture("smb_enemies_sheet.bmp");
}

void Enemy::render(int camX, int camY){
   //show the dot
   enemyTexture.render(mPosX - camX, mPosY - camY, &enemySpriteClips[frame/4]);
}

int Enemy::getPosX(){
   return mPosX;
}

int Enemy::getPosY(){
   return mPosY;
}

bool Enemy::loadTexture(std:: string path){
   //use function already in existence in Ltexture class
   return enemyTexture.loadFromFile(path);

}

void Enemy::initSprite(){
   for(int i = 0; i < spriteNum; i++){
      enemySpriteClips[i].x = spriteXInit + i*(spriteOffset);
      enemySpriteClips[i].y = spriteYInit;
      enemySpriteClips[i].w = spriteW;
      enemySpriteClips[i].h = spriteH; 
   }
}
SDL_Rect Enemy::getHitBox(){
   return hitBox;
}
void Enemy::mapCollision(int camerax, SDL_Rect object){
   int a = 0, b = 0;
   //left and right collisions
   if( ( (mPosX+hitBox.w >= object.x) && (mPosX < object.x) ) || ( (mPosX <= object.x+object.w)  &&  (mPosX+hitBox.w > object.x+object.w) ) ) a = 1; 
   if(  ((mPosY+hitBox.h > object.y) || ( (mPosY) > (object.y) ) ) && ( (mPosY+hitBox.h < (object.y + object.h)) || ( (mPosY) < (object.y + object.h) ) )   ) b = 1;
   if( (a==1) && (b==1) ){
cout<<mPosY<<" "<<mPosY+hitBox.h<<" "<<object.y<< " "<<object.y+object.h<<" "<<endl;
       mPosX -=mVelX;
       mVelX*=(-1);
   }
}
