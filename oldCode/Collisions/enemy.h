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
        //the dimensions of the enemy
        static const int ENEMY_WIDTH = 40;
        static const int ENEMY_HEIGHT = 40;
   //Maximum axis velocity of the dot
        static const int DOT_VEL = 10;
        //Initializes the variables
        Enemy(int, int, int, int, int, int, int, int);
        //moves the enemy
        virtual void move(SDL_Rect*) = 0;
        void mapCollision(int , SDL_Rect);
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

        LTexture enemyTexture; //every enemy will HAVE a texture
        SDL_Rect enemySpriteClips[6];//arbitrsy number

        //initialize sprite sheet
        void initSprite();
        //determine which sprite to use
        //virtual void decideFrame() = 0;
};
#endif
