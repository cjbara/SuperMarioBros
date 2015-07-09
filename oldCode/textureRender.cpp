#include <SDL2/SDL.h>
#include <SDL/SDL_image.h> 
#include <iostream>
#include <string>
using namespace std;

//global variables for the screen and window
SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Renderer* renderer = NULL;
  
int screenHeight = 520;
int screenWidth = 640;

//Starts up SDL and creates window
int init();
//Frees media and shuts down SDL
void close();
//loads an SDL_surface
SDL_Texture* loadTexture(string);

//------------------------------------------------------------------------------------------------//
int init(){
  //initialize SDL, check to make sure it initializes
  if(SDL_Init(SDL_INIT_VIDEO)<0) { cout << "Did not initialize" << endl << "Error " << SDL_GetError() << endl; return 1; }

  if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ){cout << "No linear Textures" << endl; }

  //create window
  window = SDL_CreateWindow("First Crack at Mario Bros", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
  if(window==NULL) { cout << "Window didn't initialize" << endl; return 2; }
/*
  //initialize png loading
  int flags=IMG_INIT_JPG|IMG_INIT_PNG;
  int initted=IMG_Init(flags);
  if(initted&flags != flags) {
	cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
  }  
*/
  screenSurface = SDL_GetWindowSurface(window);

  return 1;
}
//------------------------------------------------------------------------------------------------//
//Loads a texture for rendering
SDL_Surface* loadSurface(string path){
  SDL_Surface* optimizedSurface;
  //load surface on loadedSurface
  SDL_Surface* loadedSurface = NULL;
  loadedSurface = SDL_LoadBMP(path.c_str());
  if(loadedSurface==NULL) {cout << "Error:" << IMG_GetError() << endl; }

  //create texture from surface and return it
  //SDL_Texture* newTexture = NULL;
  //newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
  //if(newTexture == NULL ) { cout << "Texture is null" << endl;}

  optimizedSurface = SDL_ConvertSurface( loadedSurface, screenSurface->format, NULL );
  if(optimizedSurface == NULL){cout << "Not optimized" << endl;}
  //Get rid of loadedSurface
  SDL_FreeSurface(loadedSurface);
  
  return optimizedSurface;
}
//------------------------------------------------------------------------------------------------//
void close(){
  //destroy surface and quit SDL
  SDL_DestroyWindow(window);
  //SDL_DestroyRenderer(renderer);
  SDL_Quit();
}
//------------------------------------------------------------------------------------------------//

int main(){
  //initialize SDL
  init();
  //create renderer to load images with
 //Create window
// renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
// if(renderer == NULL) { cout << "Renderer is null" << SDL_GetError() << endl; }
  //Initialize renderer color
  //SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

  //load mario as a texture to the screen
  SDL_Surface* mario = NULL;
  mario = loadSurface("smb_mario_sheet.bmp");

  //stretch the image to full screen
 	SDL_Rect stretchRect;
	stretchRect.x = 0;
	stretchRect.y = 0;
	stretchRect.w = screenWidth;
	stretchRect.h = screenHeight;
	SDL_BlitScaled( mario, NULL, screenSurface, &stretchRect );
  SDL_UpdateWindowSurface(window);
/*
  SDL_Texture* enemies = NULL;
  enemies = SDL_CreateTextureFromSurface(renderer,loadedSurface);
  SDL_FreeSurface(loadedSurface);

  //now render it to the screen
  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, enemies, NULL, NULL);
  SDL_RenderPresent(renderer);
*/

 /* SDL_Rect* marioStandingLeft = NULL;
  marioStandingLeft->x=180;
  marioStandingLeft->y=0;
  marioStandingLeft->w=18;
  marioStandingLeft->h=18;

  //Holds offsets
    SDL_Rect* offset = NULL;
    
    //Get offsets
    offset->x = 0;
    offset->y = 0;

  SDL_BlitSurface(mario, marioStandingLeft, screenSurface, offset);
 */ //while the escape key is not hit
  SDL_Event e;
  int quit = 0;
  while(!quit){
    //handle input 
    while(SDL_PollEvent(&e)!=0){
      if(e.key.keysym.sym == SDLK_ESCAPE){
	quit=1;
      }
    }
    
    //clear screen
    //SDL_RenderClear(renderer);
    //render texture
    //SDL_RenderCopy(renderer, mario, NULL, NULL);
    //update screen
    //SDL_RenderPresent(renderer);
  }

  cout << "esc" << endl;
  SDL_FreeSurface(mario);
  close();
  return 0;

}



