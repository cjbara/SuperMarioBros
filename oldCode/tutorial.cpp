#include <SDL2/SDL.h>
#include "SDL/SDL.h"
#include <stdio.h>
#include <string>


//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


//Key press surfaces constants
enum KeyPressSurfaces{
   KEY_PRESS_SURFACE_DEFAULT,
   KEY_PRESS_SURFACE_UP,
   KEY_PRESS_SURFACE_DOWN,
   KEY_PRESS_SURFACE_LEFT,
   KEY_PRESS_SURFACE_RIGHT,
   KEY_PRESS_SURFACE_TOTAL,
   KEY_PRESS_SURFACE_RIGHT_TWO,
   KEY_PRESS_SURFACE_RIGHT_THREE,
   KEY_PRESS_SURFACE_LEFT_TWO,
   KEY_PRESS_SURFACE_LEFT_THREE
};

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads Individual image
SDL_Surface* loadSurface( std::string path );

//the windows willbe rendered to null
SDL_Window* gWindow = NULL;

//the surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//the images that correspond to a keypress
SDL_Surface* gKeyPressSurfaces[ KEY_PRESS_SURFACE_TOTAL ];

//current displayed image
SDL_Surface* gCurrentSurface = NULL;

SDL_Surface* loadSurface( std::string path ){
   //Load image at specified path
   SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str() );
   if( loadedSurface == NULL ){
      printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
   }

   return loadedSurface;
}

bool init(){
   bool success = true;

   if( SDL_Init(SDL_INIT_VIDEO) < 0){
      printf( "SDL could not initialize! SDL_Error: %s\n",SDL_GetError() );
      success = false;
   } else {

      gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
      if( gWindow == NULL){
         printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
         success =false;
      } else {
         gScreenSurface = SDL_GetWindowSurface( gWindow );
      }
   }

   return success;
}

bool loadMedia(){
   bool success = true;

   //Load default surface
   gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("bigMr.bmp");
   if( gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT ] == NULL){
      printf("Failed to load a default image!\n");
      success = false;
   }
   //Load up surface
   gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("bigMrUp.bmp");
   if( gKeyPressSurfaces[KEY_PRESS_SURFACE_UP ] == NULL){
      printf("Failed to load a up image!\n");
      success = false;
   }
   //Load down surface
   gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("bifMrDwn.bmp");
   if( gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN ] == NULL){
      printf("Failed to load a down image!\n");
      success = false;
   }
   //Load left surface
   gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("bigMl.bmp");
   if( gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT ] == NULL){
      printf("Failed to load a left image!\n");
      success = false;
   }
   //Load right surface
   gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("bigMr.bmp");
   if( gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT ] == NULL){
      printf("Failed to load a right image!\n");
      success = false;
   }

   gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT_TWO] = loadSurface("bigMltwo.bmp");
   if( gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT_TWO ] == NULL){
      printf("Failed to load a left image!\n");
      success = false;
   }

   gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT_THREE] = loadSurface("bigMlthree.bmp");
   if( gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT_THREE ] == NULL){
      printf("Failed to load a left image!\n");
      success = false;
   }

   gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT_TWO] = loadSurface("bigMrtwo.bmp");
   if( gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT_TWO ] == NULL){
      printf("Failed to load a right image!\n");
      success = false;
   }

   gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT_THREE] = loadSurface("bigMrthree.bmp");
   if( gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT_THREE ] == NULL){
      printf("Failed to load a right image!\n");
      success = false;
   }

   
   return success;
}

void close(){

   SDL_FreeSurface( gCurrentSurface );
   gCurrentSurface = NULL;

   SDL_DestroyWindow(gWindow);
   gWindow = NULL;

    SDL_Quit();

}

int main( int argc, char* args[] ){
   int left = 0;
   int right = 0;

   if( !init() ){
      printf("Failed to initialize\n");
   } else {
      if( !loadMedia() ){
         printf("Failed to load media\n");
      }else {
         //Main loop flag
         bool quit = false;
         //Event Handler
         SDL_Event e;
   
         // Set default current surface
         gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];

         //While application is running
         while( !quit ){
            //Handle events on queue
            while( SDL_PollEvent( &e ) != 0 ){
               //User requests to quit
               if(e.type == SDL_QUIT){
                  quit = true;
               }
               //USer presses a key
               else if(e.type == SDL_KEYDOWN ){
                  //select surfaces based on key press
                  switch(e.key.keysym.sym) {

                     case SDLK_UP:
                     gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ];
                     break;

                     case SDLK_DOWN:
                     gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ];
                     break;

                     case SDLK_RIGHT:
                        if(right%3 == 0) gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ];
                        if(right%3 == 1) gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT_TWO]; 
                        if(right%3 == 2) gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT_THREE];
                        right++; 
                     break;

                     case SDLK_LEFT:
                        if(left%3 == 0) gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ];
                        if(left%3 == 1) gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT_TWO ];
                        if(left%3 == 2) gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT_THREE ];
                        left++;
                     break;

                     default:
                     gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];
                     break;

                     
                  }
               }
            }
            //Apply the current image
            SDL_Rect stretchRect;
	    stretchRect.x = 0;
	    stretchRect.y = 0;
	    stretchRect.w = SCREEN_WIDTH;
	    stretchRect.h = SCREEN_HEIGHT;
	    SDL_BlitScaled( gCurrentSurface, NULL, gScreenSurface, &stretchRect );

            //Update the surface
            SDL_UpdateWindowSurface( gWindow );
         }
      }
   }

   close();

   return 0;
}

