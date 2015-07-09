#include <SDL2/SDL.h>
#include <SDL/SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "Ltexture.h"
#include "enemy.h"
#include "globalVars.h"
using namespace std;

Enemy::Enemy( int startX, int startY ){
        //nitializes the positions
        mPosX = startX;
        mPosY = startY;
	
        //make the hit box smaller to match the pistuce size
        hitBox.x = mPosX+5;
        hitBox.y = mPosY;
        hitBox.h = blockSize;
        hitBox.w = blockSize-5;

        //movement of enemies
        mVelX = -1;
        mVelY = 5; //enemy will be moving downward

        //clip sprite sheet
        frame = 0;
        frameDelay = 4; 

        //enemy is initially alive
        alive = 1;
        deathCount = 0;

	loadTexture("smb_enemies_sheet.bmp");
}

void Enemy::render(int camX, int camY){
   //show the dot if in the camera window
   if( mPosX >= camX && mPosX <= camX+SCREEN_WIDTH && deathCount <= 25){
      enemyTexture.render(mPosX - camX, mPosY - camY, &enemySpriteClips[frame/4]);
      //cout << camY << " " << mPosY << endl;
   }
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

SDL_Rect Enemy::getHitBox(){
   return hitBox;
}
void Enemy::mapCollision(int camerax, SDL_Rect object){
   //left and right collisions
   if( ( (mPosX+hitBox.w >= object.x) && (mPosX < object.x) ) || ( (mPosX <= object.x+object.w)  &&  (mPosX+hitBox.w > object.x+object.w) ) ){ 
      if(  ((mPosY+hitBox.h > object.y) || ( (mPosY) > (object.y) ) ) && ( (mPosY+hitBox.h < (object.y + object.h)) || ( (mPosY) < (object.y + object.h) ) )   ) {
       mPosX -=mVelX;
       mVelX*=(-1);
      }
   }

   //collide.check if on ground
   if( mPosY+hitBox.h >= object.y && mPosY < object.y){
      if( !(mPosX+hitBox.w < object.x) && !(mPosX > object.x+object.w) ){
         //mPosY = object.y-blockSize; //keep goomba on top of block
         //mPosY-=mVelY; //move it back to where it was
         mVelY = 0; //don't want to fall
      }
   }
}

int Enemy::getDeathCount(){
   return deathCount;
}

int Enemy::topCollision(int cameraX, SDL_Rect mario, double MvelY){

   if(mPosX >= cameraX && mPosX < cameraX+SCREEN_WIDTH){ //if enemy is on screen

      //for readability
      //enemy coordinates
      int enemyTop = mPosY;
      int enemyBottom = mPosY+blockSize;
      int enemyLeft = mPosX;
      int enemyRight = mPosX+blockSize;
      //mariocoordinate
      int Mtop = mario.y;
      int Mbottom = mario.y+blockSize;
      int Mleft = mario.x;
      int Mright = mario.x+blockSize;

      //The enemy is _____ Mario
      int above = 0, below = 0, right = 0, left = 0;
      if(enemyTop > Mbottom) below = 1; //enemy is below mario
      if(enemyBottom < Mtop) above = 1; //enemy is above mario
      if(enemyLeft > Mright) right = 1; //enemy is right of mario
      if(enemyRight < Mleft) left = 1; //enemy is left of mario
      if( above || below || left || right){
         return 0; //There is no collision
      }

      //Check if mario is on top of enemy
      //aka if enemy has bottom collision with
      //mario
      if(enemyTop <= Mbottom && enemyBottom > Mbottom && MvelY > 0){
         if( (Mright >= enemyLeft && Mleft <= enemyLeft) || (Mleft <= enemyRight && Mright >= enemyRight) ){
            return 1;
         }
      }
   }
   return 0;
}
int Enemy::getAlive(){
   return alive;
}
