#include <SDL2/SDL.h>
#include <iostream>
#include <SDL/SDL_image.h>
#include "init.h"
#include "globalVars.h"
#include "enemy.h"
#include "Ltexture.h"
#include <string>
#include <stdio.h>
using namespace std;

//============================================================================
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

//============================================================================
bool loadMedia()
{
        //Loading success flag
        bool success = true;

        //Load Mario texture
        marioSheet = loadTexture( "mario.bmp" );
        if( marioSheet == NULL )
        {
                printf( "Failed to load texture image!\n" );
                success = false;
        }
	
	//load Blocks texture
	blockSheet = loadTexture( "smb_sprites.bmp" );
	if( blockSheet == NULL )
        {
                printf( "Failed to load texture image!\n" );
                success = false;
        }
        
        return success;
}

//============================================================================
void close()
{
        //Free loaded image
        SDL_DestroyTexture( marioSheet );
        marioSheet = NULL;
        SDL_DestroyTexture( blockSheet );
        blockSheet = NULL;

        //Destroy window        
        SDL_DestroyRenderer( gRenderer );
        SDL_DestroyWindow( gWindow );
        gWindow = NULL;
        gRenderer = NULL;

        //Quit SDL subsystems
        SDL_Quit();
}
//============================================================================
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


