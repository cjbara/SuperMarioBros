//This file just contains all of the global variables for the project
//include this in every file in the project
#include "SDL2/SDL.h"

//Screen dimension constants
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const int LEVEL_WIDTH;
extern const int LEVEL_HEIGHT;
extern const int blockSize;

//The window we'll be rendering to
extern SDL_Window* gWindow;

//The window renderer
extern SDL_Renderer* gRenderer;

//Current displayed texture
extern SDL_Texture* marioSheet;
extern SDL_Texture* blockSheet;
extern SDL_Texture* itemSheet;
