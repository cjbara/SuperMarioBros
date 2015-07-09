//includes global variables and initialization for SDL2
#include <string>
using namespace std;

//SDL functions
//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image as texture
extern SDL_Texture* loadTexture( std::string path );

