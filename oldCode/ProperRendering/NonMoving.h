//This is the interface for the nonmoving class (virtual)
#include "SDL2/SDL.h"

#ifndef NONMOVING_H
#define NONMOVING_H

class NonMoving{

  public:
	NonMoving(int, int);//Constructor takes top left corner x,y as inputs
	virtual void render(int, int); //renders the block to the screen
	SDL_Rect getPos();	//returns the value of the position
	virtual void collision()=0;

  protected:
        SDL_Rect renderPosition;
	SDL_Rect position;
	SDL_Rect sprite;
	int size;

};

#endif
