/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include <SDL2/SDL.h>
#include <SDL/SDL_image.h>
#include <fstream>
#include "init.h"
#include "Mario.h"
#include "NonMoving.h"
#include "Brick.h"
#include "Pipe.h"
#include "Question.h"
#include "Ground.h"
#include "Stair.h"
#include "globalVars.h"
#include "Ltexture.h"
#include "enemy.h"
#include "goomba.h"
#include "koopa.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <deque>
using namespace std;

//Screen dimension constants 
const int SCREEN_WIDTH = 640; 
const int SCREEN_HEIGHT = 520; 
const int blockSize = 40; 
const int LEVEL_WIDTH = 200 * blockSize; 
const int LEVEL_HEIGHT = 520; 
 
//The window we'll be rendering to 
SDL_Window* gWindow = NULL; 
 
//The window renderer 
SDL_Renderer* gRenderer = NULL; 
 
//Declare new textures 
SDL_Texture* marioSheet = NULL; 
SDL_Texture* blockSheet = NULL; 

//=========================================================================
//Begin main program
int main( int argc, char* args[] )
{
   //enemies
   Goomba shroom(3, 0, 0, 17, 20, 30, 200, 11*blockSize);
   Koopa shell(4, 150, 0, 17, 23, 30, 300, 11*blockSize);
  //Start up SDL and create window
  if( !init() ) {
	printf( "Failed to initialize!\n" );
	return 1;
  }
  //Load media
  if( !loadMedia() ) {
	printf( "Failed to load media!\n" );
	return 2;
  }
  if( !shroom.loadTexture("smb_enemies_sheet.bmp") ){
     printf( "Failed to laod media!\n");
     return 2;
  }
  if( !shell.loadTexture("smb_enemies_sheet.bmp") ){
     printf( "Failed to laod media!\n");
     return 2;
  }

  //Main loop flag
  bool quit = false;

  //Event handler, only accepts the esc key to quit program
  //all other events are processed by Mario's class
  SDL_Event e;

  //loop counter, to determine timing and such
  int i=0;

  //declare Mario
  Mario mario;

  //create list of nonmoving elements
  deque<NonMoving*> nonmoving;

  //Create the level using the world1-1.txt file
  ifstream world11;
  world11.open("world1-1.txt");
  if(!world11){ printf("The world 1-1 file didn't open"); }
  int xcoord, ycoord;
  
  //create the ground (remove the missing blocks in the next while loop)
  for(int k = 1; k<=220; k++){
    nonmoving.push_back(new Ground(k, 13));
  }
  int erasedBlocks = 0;
  string blockType;
  while(!world11.eof()){
    world11 >> blockType;
    world11 >> xcoord;
    world11 >> ycoord;
	if(blockType == "brick")
		nonmoving.push_back(new Brick(xcoord, ycoord));
	else if(blockType == "question")
		nonmoving.push_back(new Question(xcoord, ycoord));
	else if(blockType == "pipe")
		nonmoving.push_back(new Pipe(xcoord, ycoord));
	else if(blockType == "stair")
		nonmoving.push_back(new Stair(xcoord, ycoord));
	else if(blockType == "noGround"){//erase a ground block
		nonmoving.erase(nonmoving.begin() + xcoord - erasedBlocks);
		erasedBlocks++;
	}
  }

  //create the camera
  SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

//==================================================================================================
  //Start the game loop
  while( !quit ){
	//Handle events on queue (quit or no quit)
	while( SDL_PollEvent( &e ) != 0) {
		if(e.key.keysym.sym == SDLK_ESCAPE) { //User requests quit
			quit = true;
			break;
		}
	}

//==================================================================================================
  //handle Mario's input from the 
  mario.handleInput(i);

//===============================================================================================

  //Move Mario function 
  //This next block updates Mario's position
  i++;//increment the loopcount
  mario.move(i,camera.x);  
  shroom.move(&camera);
  shell.move(&camera);

  //Check for collisions
  for(int j = 0; j < nonmoving.size(); j++){
     mario.mapCollision(camera.x, nonmoving[j]->getPos());
  }
  mario.enemyCollision(shroom.getHitBox());
  mario.enemyCollision(shell.getHitBox());
  
//===============================================================================================
//Rendering function
  //Clear screen
  SDL_SetRenderDrawColor( gRenderer, 100, 180, 255, 0xFF );
  SDL_RenderClear( gRenderer );

  if(mario.xposition() > 0){
     camera.x = (mario.xposition() + (blockSize/2)) - SCREEN_WIDTH/2;
  }

  //Keep the camera in bounds
  if( camera.x < 0 )
  { 
    camera.x = 0;
  }
 
  //render Mario to the screen 
  mario.render();
  for(int j=0; j<nonmoving.size(); j++){
	nonmoving[j]->render(camera.x, camera.y);
  }
  
  shroom.render(camera.x, camera.y);
  shell.render(camera.x, camera.y);

  //Update screen
  SDL_RenderPresent( gRenderer );
//===============================================================================================
  //this makes the question block into a deleted question block
  if(i>100) nonmoving[4]->collision();
  //delays to set proper framerate
  SDL_Delay(12);
  }

//Free resources and close SDL
close();

return 0;
}
