#include "Mario.h"
#include "globalVars.h"
using namespace std;

//declare all of the static variables here
//const static variables
const double Mario::minWalkSpeed = 0.185546875;
const double Mario::maxRunSpeed = 6.40625;
const double Mario::maxWalkSpeed = 3.90625;
const double Mario::walkAccel = 0.092773438;
const double Mario::runAccel = 0.139160156;
const double Mario::gravity[3] = { 1.09375, 0.9375, 1.40625 };
const double Mario::aGravity[3] = { 0.3125, 0.29296875, 0.390625 };
const double Mario::initialYAccel[3] = { 10, 10, 12.5 };
const double Mario::runDecel = 0.25390625;
const double Mario::releaseDecel = 0.126953125;
const double Mario::skidDecel = 0.25390625;
const double Mario::skidTurn = 1.40625;
const double Mario::airSkidDecel[3] = {0.109863281, 0.09765625, 0.063476563};

//==============================================================================================
//The default constructor
Mario::Mario(){
  //start by clipping sprite sheet correctly
  enum {standr,runr1,runr2,runr3,skidr,jumpr,death};
  //clip sprit sheet for small Mario
  marioSprites[standr].x = 210;
  marioSprites[standr].y = 0;
  marioSprites[standr].w = 17;
  marioSprites[standr].h = 18;

  marioSprites[runr1].x = 238;
  marioSprites[runr1].y = 0;
  marioSprites[runr1].w = 17;
  marioSprites[runr1].h = 18;

  marioSprites[runr2].x = 298;
  marioSprites[runr2].y = 0;
  marioSprites[runr2].w = 17;
  marioSprites[runr2].h = 18;

  marioSprites[runr3].x = 267;
  marioSprites[runr3].y = 0;
  marioSprites[runr3].w = 17;
  marioSprites[runr3].h = 18;

  marioSprites[skidr].x = 330;
  marioSprites[skidr].y = 0;
  marioSprites[skidr].w = 16;
  marioSprites[skidr].h = 17;

  marioSprites[jumpr].x = 359;
  marioSprites[jumpr].y = 0;
  marioSprites[jumpr].w = 17;
  marioSprites[jumpr].h = 18;

  marioSprites[death].x = 389; 
  marioSprites[death].y = 15;
  marioSprites[death].w = 16;
  marioSprites[death].h = 16;

  //clip sprites for big Mario
  marioSprites[standr+7].x = 209;
  marioSprites[standr+7].y = 51;
  marioSprites[standr+7].w = 17;
  marioSprites[standr+7].h = 35;

  marioSprites[runr1+7].x = 238;
  marioSprites[runr1+7].y = 51;
  marioSprites[runr1+7].w = 17;
  marioSprites[runr1+7].h = 35;

  marioSprites[runr3+7].x = 270;
  marioSprites[runr3+7].y = 51;
  marioSprites[runr3+7].w = 17;
  marioSprites[runr3+7].h = 34;

  marioSprites[runr2+7].x = 299;
  marioSprites[runr2+7].y = 51;
  marioSprites[runr2+7].w = 18;
  marioSprites[runr2+7].h = 35;

  marioSprites[skidr+7].x = 329;
  marioSprites[skidr+7].y = 52;
  marioSprites[skidr+7].w = 17;
  marioSprites[skidr+7].h = 35;

  marioSprites[jumpr+7].x = 359;
  marioSprites[jumpr+7].y = 51;
  marioSprites[jumpr+7].w = 18;
  marioSprites[jumpr+7].h = 35;

  marioSprites[death+7].x = 389; 
  marioSprites[death+7].y = 15;
  marioSprites[death+7].w = 16;
  marioSprites[death+7].h = 16;

  //initialize rendering values
  flipType = SDL_FLIP_NONE;

  spriteLocation.x = 1*blockSize;
  spriteLocation.y = 11*blockSize;
  spriteLocation.w = blockSize;
  spriteLocation.h = blockSize;

  hitBox.x = 55;
  hitBox.y = 205;
  hitBox.w = blockSize-10;
  hitBox.h = blockSize-10;
  
  //initialize movement values
  running = 0;
  skidding = 0;
  xpos = 1*blockSize; //MAKE THIS WHATEVER YOU NEED MARIO'S INITIAL POSITION TO BE!
  ypos = 11*blockSize;
  xvel = 0;
  yvel = 0;
  xdirection = right;
  xaccel = 0;
  xmaxSpeed = 0;
  xinitialJumpVel = 0;
  stoppedRunningAt = 0;
  framesPast = 0;
  alreadyJumped = 0;
  onGround = 1;
  invincible = 0;
  for(int i=0; i<4; i++)
	mapCollide[i]=0;
 
  spriteOffset = 0;//start off small

  //mario start off alive
  alive = 1;
  lifeCount = 3; //mario starts off with three lives
}
//==============================================================================================
void Mario::move(int i, int camerax){
  //Move Mario function 
  if(alive){
     //This next block updates Mario's position
     i++;
     //This is to set invincibility status
     if(invincible >0 && invincible <25){
	invincible++;
     } else {
	invincible = 0;
     }
     //reset the collision status
     for(int iter=0; iter<4; iter++)
       mapCollide[iter]=0;  

     if(i%3 == 0 && running) runningSprite++;
     else if(i%5 == 0 && !running) runningSprite++;//walking Mario's sprites transition at a rate of 3/5 * running Mario's sprites
     if(runningSprite>=3) runningSprite=0;

     //update y position and check if Mario is on the ground       
     ypos += yvel;
     //if(ypos >= 11*blockSize) { ypos = 11*blockSize; onGround = 1; }
     onGround = 0;

     //Update the x position
     xpos += xvel;
     //Don't let mario go back in the level
     if( xpos < camerax){
        xpos -=xvel;//keep xpos, and camera position the same
        xvel = 0; //don't let mario move
     }
  }else{
     ypos+=yvel;
  }
  // This renders Mario's bottom left at the ypos (for better control of where Mario is)
  spriteLocation.y = ypos+5;
  //spriteLocation.y = ypos;
  spriteLocation.x = xpos - camerax;

  //update hitbox
  hitBox.x = xpos+5;//tyr to make hitbox match sprite size
  hitBox.y = ypos+5;

  //this next line prints Mario's current values
  //printf("yvel: %f xvel: %f spriteLocation.y: %i spriteLocation.x:%i running:%i onGround:%i\n",yvel,xvel,spriteLocation.y,spriteLocation.x,running,onGround);
}
//==============================================================================================
void Mario::render(){
  //Mario's Rendering function 
  //Render sprite texture to screen
  //cout << ypos << " " << sprite() + spriteOffset << endl;
  SDL_RenderCopyEx( gRenderer, marioSheet, &marioSprites[sprite() + spriteOffset],&spriteLocation,0,NULL,flipType);
}
//==============================================================================================
int Mario::sprite(){
     //sprite function
     //decide what spriteLocation to render
  int sprite;
  //if he is big and holding down
//  const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
//  if( currentKeyStates[ SDL_SCANCODE_DOWN ] && big ){
//    if(onGround){
//	sprite = death; //offset for pushup Mario sprite
//    }
//    return sprite;
//  }
	
  if(alive){
     //first determine the x direction, default is the direction they were facing
     if(xdirection == left) { flipType = SDL_FLIP_HORIZONTAL; }
     else if(xdirection == right) { flipType = SDL_FLIP_NONE; }

     //now decide the type of sprite to render
     if(!onGround) sprite = jumpr;//off the ground
     else if(xvel==0) {sprite = standr; runningSprite=0; }
     else if((xvel > 0 && xdirection == left) || (xvel < 0 && xdirection == right)) {
       sprite = skidr;
     } else sprite = runr1 + runningSprite;
  }else{
     ypos+=yvel;
     sprite = death;
  }
  //return the sprite value
  return sprite;
}
//==============================================================================================
void Mario::handleInput(int i){
  //Start of event handling function
  //This function processes all input for Mario, and updates the velocity values accordingly
  //Does not move Mario's position
  /* Values this funcation affects:
   * running
   * skidding
   * many more
  
  */
  
  const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
  //This block is for the jump key (currently S, but that could change easily)
    //decide which gravity and initial acceleration to use (depends on Mario's speed)
    int gravIndex;
    if(xvel < 2.5) gravIndex=0;
    else if(xvel >=2.5 && xvel <=5.780639648) gravIndex=1;
    else gravIndex=2;

  //This block is for the jump key (S)
  if( currentKeyStates[ SDL_SCANCODE_S ] ){
    //This means Mario is jumping
    //now update his velocity accordingly
    if(onGround && alreadyJumped == 0 ){
      alreadyJumped = 1;
      xinitialJumpVel = xvel;
      yvel -= initialYAccel[gravIndex];
    } else {
      yvel += aGravity[gravIndex];
    }
  } else { //jump button is not being pressed
    if(onGround){//if Mario is on the ground, yvel = 0
      yvel = 0;
      //only when Mario makes it to the ground is he allowed to jump again
      alreadyJumped = 0;
    } else { //else, fall at normal speed
      yvel += gravity[gravIndex];
    }
  }
  
  //This block sets the running flag to 1 or 0
  //The running flag will be used for the left and right motion
  //Mario's horizontal physics change if he is in the air vs. on ground
  //if Mario is not on the ground, then the sprint button doesn't matter, only current speed does
  if(!onGround){
    if(xvel < maxWalkSpeed){
      xaccel = walkAccel;
    } else {
      xaccel = runAccel;
    }
  //if he's on the ground, check the sprint button
  } else if( currentKeyStates[ SDL_SCANCODE_A ] ){
    running = 1;
    xmaxSpeed = maxRunSpeed;
    xaccel = runAccel;
  } else if(running == 1 ){ //Mario keeps running for 10 frames, then slows immediately to a walk
    //check if stoppedRunningAt has been set, if it hasn't, set it
    if(!stoppedRunningAt){
      stoppedRunningAt = i;
    }
    framesPast = i - stoppedRunningAt;
    if(framesPast >= 10){//if frames past greater than 10, stop running (decel starts next loop)
      running = 0;
    }
  } else { //Mario is not running, just walking
    //framesPast = 0;//make sure if he was running, this variable is reset
    stoppedRunningAt = 0;
    running = 0;
    //When the run button is released, Mario only changes his speed when he is on the ground
    if(onGround){
      xmaxSpeed = maxWalkSpeed;
      xaccel = walkAccel;
    }
  }
  
  //This next block is for the right arrow key
  if( currentKeyStates[ SDL_SCANCODE_RIGHT ] ){
    if(onGround){ xdirection = right; }//only change direction when on the ground
    //if he is moving slower than max, add the acceleration
    if(xvel < xmaxSpeed){
      if(xvel < 0){ //he's moving left, initiate skid
        skidding = 1;
        if(!onGround){//Mario is in the air, initiate arial physics for skidding
          if(xvel > maxWalkSpeed){
             xvel += airSkidDecel[0];
          } else {
            if(xinitialJumpVel >= 2.5){
                  xvel += airSkidDecel[0];
            } else {
                  xvel += airSkidDecel[0];
            }
          }
        }
        if(xvel > -1*skidTurn){ // if x is less than the turnaround speed, set xvel to 0
          xvel = minWalkSpeed;
        } else if(onGround) { // else slow him down
          xvel += skidDecel;
        }
      } else if(xvel > 0 && xvel < minWalkSpeed){//This is just moving very slowly right
          skidding = 0;
          xvel = minWalkSpeed;
      } else {
          skidding = 0;
          xvel += xaccel;
      }
    }
    //make sure the speed is not greater than the max run speed
    if(xvel > xmaxSpeed){
      xvel = xmaxSpeed;
    }
  } else { //This means the right key is not being pressed
    //only decelerate when Mario is on the ground
    if(xvel >= minWalkSpeed && onGround){
      if(skidding){ //if he was skidding and button is released, he cintinues to slow at skid pace
          xvel -= skidDecel;
      } else { // else he decelerates at normal pace
          xvel -= releaseDecel;
      }
    } else if(xvel < minWalkSpeed && xvel > 0 && onGround){
      //the min 
      xvel = 0;
    }
  }
  
  //This next block is for the left arrow key
  if( currentKeyStates[ SDL_SCANCODE_LEFT ] ){
    if(onGround){ xdirection = left; }//only change direction when on the ground
    //if he is moving slower than max, add the acceleration
    if(xvel > -1*xmaxSpeed){
      if(xvel > 0){ //he's moving right, initiate skid
        skidding = 1;
        if(!onGround){//Mario is in the air, initiate arial physics for skidding
          if(xvel < -1*maxWalkSpeed){
             xvel -= airSkidDecel[0];
          } else {
            if(xinitialJumpVel <= -2.5){
                  xvel -= airSkidDecel[0];
            } else {
                  xvel -= airSkidDecel[0];
            }
          }
        }
        if(xvel < skidTurn){ // if x is less than the turnaround speed, set xvel to 0
          xvel = -1*minWalkSpeed;
        } else if(onGround){ // else slow him down
          xvel -= skidDecel;
        }
      } else if(xvel < 0 && xvel > -1*minWalkSpeed){//This is just moving very slowly right
          skidding = 0;
          xvel = -1*minWalkSpeed;
      } else {
          skidding = 0;
          xvel -= xaccel;
      }
    }
    //make sure the speed is not less than the negative max run speed
    if(xvel < -1*xmaxSpeed){
      xvel = -1*xmaxSpeed;
    }
  } else { //This means the left key is not being pressed
    //only decelerate when Mario is on the ground
    if(xvel <= -1*minWalkSpeed && onGround){
      if(skidding){ //if he was skidding and button is released, he cintinues to slow at skid pace
          xvel += skidDecel;
      } else { // else he decelerates at normal pace
          xvel += releaseDecel;
      }
    } else if(xvel > -1*minWalkSpeed && xvel < 0 && onGround){
      //the min 
      xvel = 0;
    }
  }
  
  //if both left and right are held, go nowhere
  if( currentKeyStates[ SDL_SCANCODE_LEFT ] && currentKeyStates[ SDL_SCANCODE_RIGHT ] ){
    if(xvel < -1*minWalkSpeed){//going left
      skidding = 0;
      if(onGround) xdirection = right;
      xvel += releaseDecel;
    } else if(xvel > minWalkSpeed){//going right
      skidding = 0;
      if(onGround) xdirection = left;
      xvel -= releaseDecel;
    } else {
      if(onGround) xdirection = right;
      xvel = 0;
    }
  }

}
//==============================================================================================
int Mario::mapCollision(int camerax, SDL_Rect object){
  int collisionType=0;
  int Mtop = ypos;			//Mario's top
  int Mbottom = ypos + spriteLocation.h;//Mario's bottom
  int Mleft = xpos;			//Mario's left
  int Mright = xpos + blockSize;	//Mario's right
  //object's coordinates (easier to work with)
  int Otop = object.y;			//Object's top
  int Obottom = object.y + object.h;	//Object's bottom
  int Oleft = object.x;			//Object's left
  int Oright = object.x + object.w;	//Object's right

  int above = 0, below = 0, left = 0, right = 0;//Mario is  _____ the object

  if(Mtop > Obottom) below = 1; //Mario is below object
  if(Mbottom < Otop) above = 1; //Mario is above object
  if(Mleft > Oright) right = 1; //Mario is right of object
  if(Mright < Oleft) left = 1; //Mario is left of object
  if(above || below || left || right){
	return 0; //There is no collision
  }

  //top collision  
  if( Mbottom >= Otop && Mtop < Otop && !mapCollide[topCollision] && yvel>=0){
    if( !left && !right ){
	onGround = 1;
	ypos = Otop - spriteLocation.h;
	mapCollide[topCollision] = 1;
	collisionType = 1;
    }
  }

  //bottom collision
  if( Mtop <= Obottom && Mbottom > Obottom && !mapCollide[bottomCollision]){
    if( !left && !right ){
        ypos = Obottom;
        yvel *= -1;
	mapCollide[bottomCollision] = 1;
	collisionType = 2;
    }
  }

   //collide into right
   if(  ((xpos+blockSize) >= object.x) && (xpos < object.x) ){
      if(  ((ypos > object.y) || ( (ypos+spriteLocation.h) > (object.y) ) ) && ( (ypos < (object.y + object.h)) || ( (ypos+spriteLocation.h) < (object.y + object.h) ) )   ){
   //if( Mright >= Oleft && Mleft < Oleft && xvel >0 ){
      //if(!above && !below){
   //if(  ((Mright) >= Oleft) && (Mleft < Oleft) ){
      //if(  ((Mtop > Otop) || ( (Mbottom) > (Otop) ) ) && ( (Mtop < (Obottom)) || ( (Mbottom) < (Obottom) ) )   ){
         xpos -=xvel;
         xvel = 0;
	 mapCollide[rightCollision] = 1;
       }
   }

   //collide into left
   if(  ((xpos) <= (object.x+object.w)) && ( (xpos+blockSize) > (object.x+object.w) ) ) {
      if(  ((ypos > object.y) || ( (ypos+spriteLocation.h) > (object.y) ) ) && ( (ypos < (object.y + object.h)) || ( (ypos+spriteLocation.h) < (object.y + object.h) ) )   ){
   //if( Mleft <= Oright && Mright > Oright && xvel <0 ){
      //if(!above && !below){
   //if(  (Mleft <= Oright) && ( Mright > Oright ) ) {
     // if(  (Mtop > Otop) || ( Mbottom > Otop )  && ( Mtop < Obottom) || ( Mbottom < Obottom )) {
         xpos -=xvel;
         xvel = 0;
	 mapCollide[leftCollision] = 1;
      }
   }

   //update hitbox
   hitBox.x = xpos + 5;
   hitBox.y = ypos + 5;
   return collisionType;
}
//==============================================================================================
void Mario::enemyCollision(SDL_Rect object){
  int Mtop = ypos;			//Mario's top
  int Mbottom = ypos + spriteLocation.h;//Mario's bottom
  int Mleft = xpos;			//Mario's left
  int Mright = xpos + blockSize;	//Mario's right
  //object's coordinates (easier to work with)
  int enemyTop = object.y;			//Object's top
  int enemyBottom = object.y + object.h;	//Object's bottom
  int enemyLeft = object.x;			//Object's left
  int enemyRight = object.x + object.w;	//Object's right
  
     if(enemyTop <= Mbottom && enemyBottom > Mbottom && yvel > 0){
         if( (Mright >= enemyLeft && Mleft <= enemyLeft) || (Mleft <= enemyRight && Mright >= enemyRight) ){
            return;
         }
      }

  //collide into right
  if(Mright >= enemyLeft && Mleft < enemyLeft){
     if( (Mbottom >= enemyTop && Mtop <= enemyTop) || (Mtop <= enemyBottom && Mbottom >= enemyBottom ) ){
        if(big){
		getSmall();
		invincible = 1;
	} else if(!invincible){
		alive = 0;
        	lifeCount--;
	}
     }
  }

  //collide into left
  if(Mleft <= enemyRight && Mright > enemyRight ){
     if( (Mbottom >= enemyTop && Mtop <= enemyTop) || (Mtop <= enemyBottom && Mbottom >= enemyBottom) ){
        if(big){
		getSmall();
		invincible = 1;
	} else if(!invincible){
		alive = 0;
        	lifeCount--;
	}
     }
  }

}
//==============================================================================================
double Mario::xposition(){
  return xpos;
}
double Mario::xvelocity(){
  return xvel;
}

double Mario::yposition(){
   return ypos;
}

double Mario::yvelocity(){
   return yvel;
}

void Mario::setYvelocity(double newYvel){
   yvel = newYvel;
}

SDL_Rect Mario::getHitBox(){
   return hitBox;
}

void Mario::setYVel(double newYVel){
   yvel = newYVel;
}

bool Mario::getAlive(){
   return alive;
}

int Mario::getLifeCount(){
   return lifeCount;
}

void Mario::lostLife(){
   lifeCount--;
}

void Mario::initialize(){
  //initialize rendering values
  flipType = SDL_FLIP_NONE;

  spriteLocation.x = 1*blockSize;
  spriteLocation.y = 11*blockSize;
  spriteLocation.w = blockSize;
  spriteLocation.h = blockSize;

  hitBox.x = 50;
  hitBox.y = 200;
  hitBox.w = blockSize-10;
  hitBox.h = blockSize-10;

  //initialize movement values
  running = 0;
  skidding = 0;
  xpos = 1*blockSize; //MAKE THIS WHATEVER YOU NEED MARIO'S INITIAL POSITION TO BE!
  ypos = 11*blockSize;
  xvel = 0;
  yvel = 0;
  xdirection = right;
  xaccel = 0;
  xmaxSpeed = 0;
  xinitialJumpVel = 0;
  stoppedRunningAt = 0;
  framesPast = 0;
  alreadyJumped = 0;
  onGround = 1;
  for(int i=0; i<4; i++)
        mapCollide[i]=0;

  //mario start off alive
  alive = 1;
  spriteOffset = 0;
}

void Mario::getBig(){
  //make Mario Big Mario
  big = 1;
  ypos -= blockSize;
  hitBox.y = ypos + 5;
  hitBox.h = 2*blockSize-5;
  spriteLocation.y = ypos + 5;
  spriteLocation.h = 2*blockSize;
  spriteOffset = 7;
}

void Mario::getSmall(){
  big = 0;
  ypos += blockSize;
  hitBox.y = ypos + 5;
  hitBox.h = blockSize-10;
  spriteLocation.y = ypos + 5;
  spriteLocation.h = blockSize;
  spriteOffset = 0;
}

void Mario::bounceOffEnemy(){
    yvel *= -1;
}
