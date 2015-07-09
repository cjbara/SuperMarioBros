//this is the Pipe class, used to render Pipes

#include "NonMoving.h"
#include "SDL2/SDL.h"

#ifndef PIPE_H
#define PIPE_H

class Pipe: public NonMoving{
  public:
        Pipe(int, int);//constructor
	virtual void render(int, int); //render function must be modified
        void collision();//collision animation
  private:
	int height; //height of the pipe (varies from pipe to pipe)
	SDL_Rect extraPipeSprite;
	SDL_Rect extraPipePosition;
        SDL_Rect extraRenderPosition;

};

#endif
