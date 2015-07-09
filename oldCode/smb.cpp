/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include <SDL2/SDL.h>
#include <SDL/SDL_image.h>
#include "init.h"
#include "Mario.h"
#include "globalVars.h"
#include "Ltexture.h"
#include "enemy.h"
#include "goomba.h"
#include "koopa.h"
#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

//Screen dimension constants 
const int SCREEN_WIDTH = 640; 
const int SCREEN_HEIGHT = 540; 
const int blockSize = 40; 
 
//The window we'll be rendering to 
SDL_Window* gWindow = NULL; 
 
//The window renderer 
SDL_Renderer* gRenderer = NULL; 
 
//Current displayed texture 
SDL_Texture* marioSheet = NULL; 

//=========================================================================
//Begin main program
int main( int argc, char* args[] )
{
        //declare enemies
        Goomba mushroom(3, 0, 0, 17, 20, 30, 200, 420);
        Koopa turtle(4, 150, 0, 17, 25, 30, 300, 420);

	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia(&mushroom) )
		{
			printf( "Failed to load media!\n" );
		}
                if( !loadMedia(&turtle) ){
                        printf("Failed to load media!\n");
                }
		else
		{	
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

                        //the camera are
                        SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

			int i=0;
			Mario mario;
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

//==================================================================================================

mario.handleInput(i);

mushroom.move(&camera);
turtle.move(&camera);

//===============================================================================================

//Rendering function
  //Clear screen
  SDL_SetRenderDrawColor( gRenderer, 100, 180, 255, 0xFF );
  SDL_RenderClear( gRenderer );

  mario.render();
  mushroom.render(camera.x, camera.y);
  turtle.render(camera.x, camera.y);

  //Update screen
  SDL_RenderPresent( gRenderer );
//===============================================================================================

//Move Mario function 
  //This next block updates Mario's position
  i++;//increment the loopcount
  mario.move(i);  

  //delays to set proper framerate
  SDL_Delay(16);
  }
  }
}

//Free resources and close SDL
close();

return 0;
}
