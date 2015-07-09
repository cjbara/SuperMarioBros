/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include <SDL2/SDL.h>
#include <SDL/SDL_image.h>
#include <stdio.h>
#include <string>

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

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

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

//texture class functions
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
   //SDL_Rect renderQuad = {x, y, mWidth, mHeight};
   stretchClip->x = x;
   stretchClip->y = y;

   //set clip rendering dimensions
   //if(clip != NULL){
   //   stretchClip->w = clip->w;
   //   stretchClip->h = clip->h;
   //}

   SDL_RenderCopy(gRenderer, mTexture, clip, stretchClip );
}

int LTexture::getWidth(){
   return mWidth;
}

int LTexture::getHeight(){
   return mHeight;
}

//enemy class functions
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
        //Load enemy texture
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
        enemyTexture.free();

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

                        //Current animation frame
                        int frame = 0;
			
SDL_Rect marioSprites[12];
enum {standr,runr1,runr2,runr3,stopr,jumpr,standl,runl1,runl2,runl3,stopl,jumpl};
//clip sprit sheet
marioSprites[standr].x = 210;
marioSprites[standr].y = 0;
marioSprites[standr].w = 17;
marioSprites[standr].h = 18;

marioSprites[runr1].x = 238;
marioSprites[runr1].y = 0;
marioSprites[runr1].w = 17;
marioSprites[runr1].h = 18;

marioSprites[runr3].x = 267;
marioSprites[runr3].y = 0;
marioSprites[runr3].w = 17;
marioSprites[runr3].h = 18;

marioSprites[runr2].x = 298;
marioSprites[runr2].y = 0;
marioSprites[runr2].w = 17;
marioSprites[runr2].h = 18;

marioSprites[jumpr].x = 359;
marioSprites[jumpr].y = 0;
marioSprites[jumpr].w = 17;
marioSprites[jumpr].h = 18;

marioSprites[standr].x = 210;
marioSprites[standr].y = 0;
marioSprites[standr].w = 16;
marioSprites[standr].h = 18;

marioSprites[standr].x = 210;
marioSprites[standr].y = 0;
marioSprites[standr].w = 16;
marioSprites[standr].h = 18;

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

			//While application is running
		    	int i=0;
			float yvel = 0;
			float yaccel = 0;
			float xvel = 7;
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0)
				{
					//User requests quit
					if( e.key.keysym.sym == SDLK_ESCAPE )
					{
						quit = true;
					}
					if( e.key.keysym.sym == SDLK_b )
                                        {
                                                printf("JUMP\n");
						yvel = -10;
						yaccel = 1;
                                        }
				}

                                //Move the enemy
                                goomba.move();

				//Clear screen
		                SDL_SetRenderDrawColor( gRenderer, 100, 180, 255, 0xFF );
                		SDL_RenderClear( gRenderer );
				int sprite;
				if(clip.y <200) sprite = jumpr;
				else sprite = runr1 + i;

				//Render sprite 1
				SDL_RenderCopy( gRenderer, gTexture, &marioSprites[sprite],&clip );
			

                                //render Current Enemy frame
                               // SDL_Rect* enemyClip = &enemySpriteClips[frame/2];
                                
                                goomba.render(&enemySpriteClips[frame/2], &enemyClip);

                          	//Update screen
                     
				SDL_RenderPresent( gRenderer );
                                // go to next frame
                                ++frame;
                                //Cycle animation
                                if(frame / 2 >= (ENEMY_ANIMATION_FRAMES - 1)){
                                   frame = 0;
                                }
				i++;
				if(i>=3) i=0;

				printf("yvel: %f xvel: %f yaccel: %f\n",yvel,xvel,yaccel);
				yvel += yaccel;
				if(clip.y > 200){ yvel =0; yaccel=0; clip.y=200;} 
				clip.y += yvel;
				clip.x += xvel;
				printf("yvel: %f xvel: %f yaccel: %f clip.y: %i\n",yvel,xvel,yaccel,clip.y);
				if( clip.x>=SCREEN_WIDTH ) clip.x=0;
				SDL_Delay(100);
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
