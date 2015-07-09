#include "SDL2/SDL.h"
#include <iostream>
using namespace std;

#ifndef MARIO_H
#define MARIO_H

class Mario {
  public:
    Mario();
    void handleInput(int);
    void move(int,int);
    void render();
    double xposition();
    double xvelocity();
    int mapCollision(int, SDL_Rect);
    int enemyCollision(SDL_Rect); //see if mario dies!
    void deathAnimation();
    
    enum {standr,runr1,runr2,runr3,skidr,jumpr,death};	//enums to make indexing sprites easier
    enum{left, right};		//enums to make direction easier
    enum{topCollision, bottomCollision, rightCollision, leftCollision}; 

  private:
    double xpos, ypos;		//current x and y positions of Mario
    double xvel, yvel;		//current x and y velocities of Mario
    double xaccel;		//current x acceleration
    double xmaxSpeed;		//either set to maxRunSpeed or maxWalkSpeed, depending on circumstance
    double xinitialJumpVel;	//used to calculate how high Mario can jump, set to xvel at time of jump
    int running;		//1 if running, 0 if not running
    int skidding;		//1 if skidding, 0 if not skidding
    int xdirection;		//which direction is Mario facing (use left/right enum) used to determine sprite
    //these are used for running and slowing to a walk
    //Mario keeps running for 10 frames after a button is released
    int stoppedRunningAt, framesPast;

    int mapCollide[4];	//checks if Mario has map collisions

    //This is used to make sure Mario only jumps once
    int alreadyJumped;
    
    int onGround;		//1 if on the ground, 0 otherwise
    int runningSprite;		//alternates between 0, 1, and 2, and makes the Mario running animation
    
    SDL_Rect hitBox;

    SDL_RendererFlip flipType;
    SDL_Rect spriteLocation;	//allows the sprites to be stretched to blockSize
    SDL_Rect marioSprites[7];	//Holds the clips for each of the Mario sprites

    int sprite();		//determines which sprite to render

    //death and lives
    int lostLife;

    //The following values are static and const, and are the same for every Mario
    //They are declared in Mario.cpp, and the values are obtained from the physics sheet
    static const double 
		minWalkSpeed,	
		maxRunSpeed,
		maxWalkSpeed,
		walkAccel,
		runAccel,
		gravity[3],
		aGravity[3],
		initialYAccel[3],
		runDecel,
		releaseDecel,
		skidDecel,
		skidTurn,
		airSkidDecel[3];
};

#endif
