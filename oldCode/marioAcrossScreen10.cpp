/* CORY, work on the arial physics more, i.e. when Mario is moving one direction in the air, and the other directional key is clicked */


/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include <SDL2/SDL.h>
#include <SDL/SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 520;
const int blockSize = 40;

class LTexture{
  public:
        LTexture();
        ~LTexture();
        bool loadFromFile(std::string path );
        void free(); //deallocates texture
        //renders texture at given point
        void render(int x, int y, SDL_Rect* clip = NULL, SDL_Rect* stretchClip = NULL);
        int getWidth();
        int getHeight();
        private:
        SDL_Texture* mTexture;
        int mWidth;
        int mHeight;
};
                                                          

class Enemy{
   public:
        //the dimensions of the enemy
        static const int ENEMY_WIDTH = 40;
        static const int ENEMY_HEIGHT = 40;
   //Maximum axis velocity of the dot
        static const int DOT_VEL = 10;
        //Initializes the variables
        Enemy();
        //moves the enemy
        void move();
        //shows the enemy on the screen
        void render(SDL_Rect*, SDL_Rect*);
        private:
        //the x and y positions of the enemy
        int mPosX, mPosY;
        //velocity  of the dot
        int mVelX, mVelY;
        
};

//Scene Sprites
const int ENEMY_ANIMATION_FRAMES = 3;
SDL_Rect enemySpriteClips[ENEMY_ANIMATION_FRAMES];
LTexture enemyTexture;
                                       
//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image as texture
SDL_Texture* loadTexture( std::string path );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Current displayed texture
SDL_Texture* gTexture = NULL;

//Ltexture functions
LTexture::LTexture(){
   mTexture = NULL;
   mWidth = 0;
   mHeight = 0;
}

LTexture::~LTexture(){
   free();
}

bool LTexture::loadFromFile(std::string path ){
  //Get rid of preexisting texture
  free();
  SDL_Texture* newTexture = NULL;

  SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str() );
  if(loadedSurface == NULL){
      printf ("Unable to load image\n");
  }else{
      //Color hey image
      //SDL_SetColorKey(loadedSurface, SDL_True, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

      //create texture from surface pixels
      newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
      if(newTexture == NULL){
         printf("Unable to create texture from\n");
      }else {
         //get image dimensions
         mWidth = loadedSurface->w;
         mHeight = loadedSurface->h;
      }
      //get rid of old loaded surface
      SDL_FreeSurface(loadedSurface);
  }
  //return success
  mTexture = newTexture;
  return mTexture != NULL;
}

void LTexture::free(){
  if(mTexture !=NULL){
     SDL_DestroyTexture(mTexture);
     mTexture = NULL;
     mWidth = 0;
     mHeight = 0;
  }
}

void LTexture::render(int x, int y, SDL_Rect* clip, SDL_Rect* stretchClip){
   //set rendering space and render to screen
   stretchClip->x = x;
   stretchClip->y = y;

   SDL_RenderCopy(gRenderer, mTexture, clip, stretchClip );
}

int LTexture::getWidth(){
   return mWidth;
}

int LTexture::getHeight(){
   return mHeight;
}

//Enemy class functions
Enemy::Enemy(){
        //initializes the offsets
        mPosX = 0;
        mPosY = 200;
        //initialzes the velocity
        mVelX = 5;
        mVelY = 0;
}

void Enemy::move(){
   //move the enemy loeft or right
   mPosX += mVelX;

   //if the dot went too far to the left or right
   if( (mPosX < 0) || (mPosX + ENEMY_WIDTH > SCREEN_WIDTH) ){
      //Move back
     mVelX = mVelX*(-1);
   }

   //move the enemy up or down
   mPosY += mVelY;
   //if the enemy went too far up or down
   if( (mPosY < 0) || (mPosY + ENEMY_HEIGHT > SCREEN_HEIGHT) ){
      //move back
      mPosY -= mVelY*(-1);
   }
}

void Enemy::render(SDL_Rect* clip, SDL_Rect* stretchClip){
   //show the dot
   enemyTexture.render(mPosX, mPosY, clip, stretchClip);
}



bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load PNG texture
	gTexture = loadTexture( "smb_mario_sheet.bmp" );
	if( gTexture == NULL )
	{
		printf( "Failed to load texture image!\n" );
		success = false;
	}
        //Load enemy Texture
        if(!enemyTexture.loadFromFile("smb_enemy_sheet.bmp")){
          printf("Failed to load enemy texture image\n");
          success = false;
        } else{
           enemySpriteClips[0].x = 0;
           enemySpriteClips[0].y = 0;
           enemySpriteClips[0].w = 17;
           enemySpriteClips[0].h = 20;

           enemySpriteClips[1].x = 30;
           enemySpriteClips[1].y = 0;
           enemySpriteClips[1].w = 17;
           enemySpriteClips[1].h = 20;

           enemySpriteClips[2].x = 60;
           enemySpriteClips[2].y = 0;
           enemySpriteClips[2].w = 17;
           enemySpriteClips[2].h = 20;
        }

	return success;
}

void close()
{
	//Free loaded image
	SDL_DestroyTexture( gTexture );
	gTexture = NULL;

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

SDL_Texture* loadTexture( std::string path )
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), SDL_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
}

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;
                        
                        //the enemy that will move around the screen
                        Enemy goomba;

                       //current animation frame
                       int frame = 0;
			
SDL_Rect marioSprites[12];
enum {standr,runr1,runr2,runr3,skidr,jumpr};
//clip sprit sheet
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

			SDL_Rect clip;
                        clip.x = 50;
                        clip.y = 200;
                        clip.w = 40;
                        clip.h = 40;

                        //stretch enemy
                        SDL_Rect enemyClip;
		        enemyClip.x = 50;
                        enemyClip.y = 200;
                        enemyClip.w = 40;
                        enemyClip.h = 40;

			SDL_RendererFlip flipType = SDL_FLIP_NONE;
			//While application is running
			enum{left, right};
		    	int i=0;
			int j=0;
			int running = 0;
			double xpos = 50;
			double ypos = 200;
			double yvel = 0;
			double xvel = 0;
			int xdirection = right;
			double xaccel = 0;
			double xmaxSpeed = 0;
			
			//const static variables
			const double minWalkSpeed = 0.185546875;
			const double maxRunSpeed = 6.40625;
			const double maxWalkSpeed = 3.90625;
			const double walkAccel = 0.092773438;
			const double runAccel = 0.139160156;
			const double gravity[3] = { 1.09375, 0.9375, 1.40625 };
			const double aGravity[3] = { 0.3125, 0.29296875, 0.390625 };
			const double initialYAccel[3] = { 10, 10, 12.5 };
			const double runDecel = 0.25390625;
			const double releaseDecel = 0.126953125;
			const double skidDecel = 0.25390625;
			const double skidTurn = 1.40625;
			
			//these are used for running and slowing to a walk
 			int stoppedRunningAt=0,framesPast=0;
			
			//This is used to make sure Mario only jumps once
			int alreadyJumped = 0;
			
			int moving = 0;
			int onGround = 1;
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0)
				{
				  switch(e.key.keysym.sym){
					//User requests quit
					case SDLK_ESCAPE:
						quit = true;
						break;
				  }
				}

//work on key states as opposed to key presses
const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
//This block is for the jump key (currently S, but that could change easily)
  //decide which gravity and initial acceleration to use (depends on Mario's speed)
  int gravIndex;
  if(xvel < 2.5) gravIndex=0; 
  else if(xvel >=2.5 && xvel <=5.780639648) gravIndex=1;
  else gravIndex=2;
if( currentKeyStates[ SDL_SCANCODE_S ] ){
  //This means Mario is jumping
  //now update his velocity accordingly
  if(onGround && alreadyJumped == 0 ){
    alreadyJumped = 1;
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
  xdirection = right;
  //if he is moving slower than max, add the acceleration
  if(xvel < xmaxSpeed){
    if(xvel < 0){ //he's moving left, initiate skid
      if(xvel > -1*skidTurn){ // if x is less than the turnaround speed, set xvel to 0
	xvel = minWalkSpeed;
      } else { // else slow him down
	xvel += skidDecel;
      }
    } else if(xvel > 0 && xvel < minWalkSpeed){//This is just moving very slowly right
	xvel = minWalkSpeed;
    } else {
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
    xvel -= releaseDecel;
  } else if(xvel < minWalkSpeed && xvel > 0 && onGround){
    //the min 
    xvel = 0;
  }
}

//This next block is for the left arrow key
if( currentKeyStates[ SDL_SCANCODE_LEFT ] ){
  xdirection = left;
  //if he is moving slower than max, add the acceleration
  if(xvel > -1*xmaxSpeed){
    if(xvel > 0){ //he's moving right, initiate skid
      if(xvel < skidTurn){ // if x is less than the turnaround speed, set xvel to 0
        xvel = -1*minWalkSpeed;
      } else { // else slow him down
        xvel -= skidDecel;
      }
    } else if(xvel < 0 && xvel > -1*minWalkSpeed){//This is just moving very slowly right
        xvel = -1*minWalkSpeed;
    } else {
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
    xvel += releaseDecel;
  } else if(xvel > -1*minWalkSpeed && xvel < 0 && onGround){
    //the min 
    xvel = 0;
  }
}
/*
//if both left and right are held, go nowhere
if( currentKeyStates[ SDL_SCANCODE_LEFT ] && currentKeyStates[ SDL_SCANCODE_RIGHT ] ){
  if(xvel < 0){//going left
    xvel += releaseDecel;
  } else if(xvel > 0){//going right
    xvel -= releaseDecel;
  } else {
    xvel = 0;
  }
}
*/				
                                 //move the enemy
                                 goomba.move();                               

                                 //Clear screen
		                SDL_SetRenderDrawColor( gRenderer, 100, 180, 255, 0xFF );
                		SDL_RenderClear( gRenderer );

//decide what clip to render
int sprite;
//first determine the x direction, default is the direction they were facing
if(xdirection == left) { flipType = SDL_FLIP_HORIZONTAL; }
else if(xdirection == right) { flipType = SDL_FLIP_NONE; }

//now decide the type of sprite to render
if(clip.y < 200) sprite = jumpr;
else if(xvel==0) {sprite = standr; j=0; }
else if((xvel > 0 && xdirection == left) || (xvel < 0 && xdirection == right)) {
  sprite = skidr;
} else sprite = runr1 + j;
                                //render current enemy frame
                                goomba.render(&enemySpriteClips[frame/2], &enemyClip);



				//Render sprite texture to screen
				SDL_RenderCopyEx( gRenderer, gTexture, &marioSprites[sprite],&clip,0,NULL,flipType );
				//render horizontal grid to screen
		                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0x00, 0xFF);
				for(int gridheight=1; gridheight<=SCREEN_HEIGHT/blockSize; gridheight ++){
			                SDL_RenderDrawLine( gRenderer, 0, gridheight*blockSize, SCREEN_WIDTH, gridheight*blockSize );
				}
				//Update screen
				SDL_RenderPresent( gRenderer );

                                //go to next frame
                                ++frame;
                                //cycle animation
                                if(frame/2 >= (ENEMY_ANIMATION_FRAMES -1)){
                                   frame = 0;
                                }


			 //This next block updates Mario's position
				i++;
				if(i%3 == 0 && running) j++;
				else if(i%5 == 0 && !running) j++;//walking Mario's sprites transition at a rate of 3/5 * running Mario's sprites
				if(j>=3) j=0;
			
 				//update y position and check if Mario is on the ground	
				ypos += yvel;
				if(ypos >= 200) { ypos = 200; onGround = 1; }
				else onGround = 0;

				//Update the x position
				xpos += xvel;
				if(xpos > SCREEN_WIDTH) xpos = 0;//if x is off right side of screen, move to left side of screen
				else if(xpos < -clip.w) xpos = SCREEN_WIDTH;//if x is off left, push to right

				clip.y = ypos;
				clip.x = xpos;
				printf("yvel: %f xvel: %f clip.y: %i clip.x:%i running:%i onGround:%i\n",yvel,xvel,clip.y,clip.x,running,onGround);
				SDL_Delay(16);
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
