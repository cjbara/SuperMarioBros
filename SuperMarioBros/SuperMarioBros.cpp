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
#include "Flag.h"
#include "globalVars.h"
#include "Ltexture.h"
#include "enemy.h"
#include "goomba.h"
#include "koopa.h"
#include "mushroom.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <deque>
#include <vector>
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
SDL_Texture* itemSheet = NULL;
//=========================================================================
//Begin main program
int main( int argc, char* args[] )
{
   bool gameover = 0; //use to detec if mario lost three lives and the game is over

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

  //declare Mario
  Mario mario;

  //create list of nonmoving elements
  deque<NonMoving*> nonmoving;
  //create list of enemies
  deque<Enemy*> enemies;
  
  deque<Mushroom*> mushrooms;
  
  //This bigger loop will allow for multiple lives
  while(!gameover){
     //Main loop flag
     bool quit = false;
     bool endgame = 0; //use this to detect if mario lost a life
     bool wingame = 0;

     //Event handler, only accepts the esc key to quit program
     //all other events are processed by Mario's class
     SDL_Event e;


     //loop counter, to determine timing and such
     int i=0;

       //Display Intro screen with lives
       //Rendering function
       //Clear screen
       SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0xFF );
       SDL_RenderClear( gRenderer );
       SDL_RenderPresent( gRenderer );
       //delays to set proper framerate
       SDL_Delay(2000);
     

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
	   else if(blockType == "flag")
		   nonmoving.push_back(new Flag(xcoord, ycoord));
	   else if(blockType == "noGround"){//erase a ground block
		   nonmoving.erase(nonmoving.begin() + xcoord - erasedBlocks);
		   erasedBlocks++;
	   } else if(blockType == "goomba"){
                   enemies.push_back(new Goomba( xcoord*blockSize, ycoord*blockSize));
           } else if(blockType == "koopa"){
		   enemies.push_back(new Koopa( xcoord*blockSize, ycoord*blockSize));
           } else if(blockType =="mushroom"){
                   mushrooms.push_back(new Mushroom((xcoord-1)*blockSize, (ycoord-1)*blockSize));
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
                           gameover = 1; //exit out of the game completely
			   quit = true;
			   break;
		   }
	   }

//==================================================================================================
        //handle Mario's input from the 
        mario.handleInput(i);

//===============================================================================================

       //Rendering function
       //Clear screen
       SDL_SetRenderDrawColor( gRenderer, 100, 180, 255, 0xFF );
       SDL_RenderClear( gRenderer );

       if(mario.xposition() > (camera.x+ SCREEN_WIDTH/2)){
           //camera.x = (mario.xposition() + (blockSize/2) )- SCREEN_WIDTH/2;
           camera.x = ( (mario.xposition() + (blockSize/2)) - SCREEN_WIDTH/2)+ mario.xvelocity();
       }
       if(mario.xposition() > 0){
          camera.x = (mario.xposition() + (blockSize/2)) - SCREEN_WIDTH/2;
       }

       //Keep the camera in bounds
       if( camera.x < 0 )
       { 
         camera.x = 0;
       }
       if( camera.x > LEVEL_WIDTH - camera.w )
       {
         camera.x = LEVEL_WIDTH - camera.w;
       }
  
       mario.render();
       //shroom.render(camera.x, camera.y);
       for(int j = 0; j < mushrooms.size();j++){
          mushrooms[j]->render(camera.x, camera.y);
       }
       for(int j=0; j<nonmoving.size(); j++){
	     nonmoving[j]->render(camera.x, camera.y);
       }
       for( int j = 0; j < enemies.size(); j++){
            enemies[j]->render(camera.x, camera.y);
       }
       //Update screen
       SDL_RenderPresent( gRenderer );
//===============================================================================================
       //Move Mario function 
       //This next block updates Mario's position
       i++;//increment the loopcount
       mario.move(i,camera.x);
       for( int j = 0; j < enemies.size(); j++){
           enemies[j]->move(&camera);
       }
       for( int j = 0; j < mushrooms.size(); j++){
           mushrooms[j]->move(&camera);
       }
       //Check for collisions
       for(int k = 0; k < mushrooms.size(); k++){
          if(mushrooms[k]->marioCollision(camera.x,mario.getHitBox())){
		   mario.getBig();
          }
       }
       for(int j = 0; j < nonmoving.size(); j++){ //map collisions
          if(mario.mapCollision(camera.x, nonmoving[j]->getPos())==2){
		nonmoving[j]->collision();
                for(int l = 0; l <mushrooms.size(); l++){
                   if(mushrooms[l]->getPosX() == nonmoving[j]->getPos().x ){
                      if(mushrooms[l]->getPosY() == nonmoving[j]->getPos().y){
                         mushrooms[l]->setActive();
                      }
                   }
                }
	  }
          //shroom.mapCollision(camera.x, nonmoving[j]->getPos());
          for(int k = 0; k <mushrooms.size(); k++){
            mushrooms[k]->mapCollision(camera.x, nonmoving[j]->getPos());
          }
          for(int k = 0; k <enemies.size(); k++){
             enemies[k]->mapCollision(camera.x, nonmoving[j]->getPos());
          }
       }

       //enemy collisions including enemies bumpimng into enemies
       for(int j = 0; j <enemies.size(); j++){// see if mario squashed an enemy
          if(enemies[j]->marioCollision(camera.x,mario.getHitBox(), mario.yvelocity())){ //tried to give mario a bost when he jumps off enemies
	     	mario.bounceOffEnemy();
	  }
       }
       for(int j = 0; j < enemies.size(); j++){
          if(enemies[j]->getAlive()){
             mario.enemyCollision(enemies[j]->getHitBox());//check if mario got killed by an enemy
          }
          for(int k = 0; k <enemies.size(); k++){ //enemies can collide with each other
             if(j != k) enemies[j]->mapCollision(camera.x, enemies[k]->getHitBox());//avoid checkin gif enemy collides with itself
          }
       } 

       //check if mario is dead 
       if( !mario.getAlive()){
          //this will be the death animation basically
          int goingUp = 1;
          double deathY = mario.yposition();
          mario.setYvelocity(-1); //go up screen first
          while(mario.yposition() < 520){ //until mario is below the screen
             if(mario.yposition() > deathY-200 && goingUp){
                mario.move(i, camera.x);
             }
             if(mario.yposition() <= deathY-50){
                goingUp = 0;
                mario.setYvelocity(1); //mario starts going down
             }
             if(!goingUp){
               mario.move(i, camera.x);
             }
             //render mario and all current objects on the screen
             SDL_SetRenderDrawColor( gRenderer, 100, 180, 255, 0xFF );
             SDL_RenderClear( gRenderer );
             for(int j=0; j<nonmoving.size(); j++){
                nonmoving[j]->render(camera.x, camera.y);
             }
             for( int j = 0; j < enemies.size(); j++){
                enemies[j]->render(camera.x, camera.y);
             }
             mario.render();
             SDL_Delay(10);
        
             SDL_RenderPresent( gRenderer );
          }
          endgame = 1;
       }
       if(mario.yposition() >= 600){
          SDL_Delay(500); //just time to realize you fell
          mario.lostLife();
          endgame = 1;
       }
	if(mario.xposition() >= 198.4*blockSize){
		wingame = 1;
		endgame = 1;
		cout << "You Win!" << endl;
		SDL_Delay(5000);
	}

       if(endgame == 1){
          //prepare to initialize again
         mario.initialize();
         nonmoving.clear();
         mushrooms.clear();
         enemies.clear();
         world11.close();
         if(mario.getLifeCount() <= 0){
            gameover = 1;
         }
         //e = SDL;
         break;
       }

       //delays to set proper framerate
       if(mario.xposition()>100*blockSize) SDL_Delay(6);
	else SDL_Delay(10);	
    } //single life loop
    if(wingame) break;
  } //multiplife loop


//Free resources and close SDL
close();

return 0;
}
