#ifndef ENEMY_H
#define ENEMY_H


#include <SDL2/SDL.h>
#include <SDL/SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "globalVars.h"
#include "Ltexture.h"
using namespace std;

//extern const int LEVEL_WIDTH;
//extern const int SCREEN_WIDTH;
//extern const int SCREEN_HEIGHT;
//extern const int blockSize;

class Enemy{
   public:
        //Initializes the variables
        Enemy( int, int);
        //moves the enemy
        virtual void move(SDL_Rect*) = 0;
        void mapCollision(int , SDL_Rect);
        virtual int marioCollision(int, SDL_Rect, double) = 0; //detect getting killed by mario 
        int topCollision(int, SDL_Rect, double); //detect getting hit from above
           //this funciton makes the enemy class abstract
           //this is the only virtual one, because the only thing 
           //enemies will do differently is move differently
        
	//shows the enemy on the screen
        void render(int, int);
        
	//accessor functions
        int getPosX();
        int getPosY();
        SDL_Rect getHitBox();

        bool loadTexture(std:: string path );
        
	//determine which sprite to use
        virtual void decideFrame() = 0;

        int getDeathCount(); //return how long enemy has been dead for
        int getAlive();

        protected:
        //the x and y positions of the enemy
        int mPosX, mPosY;
        SDL_Rect hitBox; //this will be used for collisions
        //velocit of x and y positions
        int mVelX, mVelY;      

        //sprite sheets numbers
        int spriteNum; //number of sprites enemy will have
        int spriteXInit; //initial x position
        int spriteYInit; //initial y position on sprite sheet
        int spriteW;
        int spriteH;
        int spriteOffset; //distance between sprites

        int frame; //alternates between 0 and some number for motion
        int frameDelay; //this will be used to slow down rate you rotate
                        //through the sprite clips

        bool alive; //flag that enemy is alive/dead
        int deathCount; //will be used to keep enemy on screen for just a bit after they are dead        

        LTexture enemyTexture; //every enemy will HAVE a texture
        SDL_Rect enemySpriteClips[6];//arbitrsy number

        //initialize sprite sheet
        virtual void initSprite() = 0;

};
#endif
