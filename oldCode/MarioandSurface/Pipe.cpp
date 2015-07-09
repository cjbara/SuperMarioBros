//Pipe intstantiation

#include "SDL2/SDL.h"
#include "Pipe.h"
#include "globalVars.h"

Pipe::Pipe(int xgrid, int ygrid)
        :NonMoving(xgrid, ygrid)
{
//size is special here because it is not the usual 40x40, it's 80x80
  size = blockSize*2;

//determine the height of the pipe
  height = 13 * blockSize - position.y;
  

//since the pipe has special width and height, redefine the width and height
  position.w = size;
  position.h = height;

//pipe sprite
  sprite.x = 614;
  sprite.y = 46;
  sprite.w = 32;
  sprite.h = 31;

//extra pipe sprite
  extraPipeSprite.x = 614;
  extraPipeSprite.y = 81;
  extraPipeSprite.w = 32;
  extraPipeSprite.h = 16;

//extra pipe position
  extraPipePosition.x = position.x;
  extraPipePosition.y = position.y + blockSize;
  extraPipePosition.w = 2 * blockSize;
  extraPipePosition.h = height - blockSize;

//render height and width are 2*blockSize
  renderPosition.h = 2*blockSize;
  renderPosition.w = size;
  extraRenderPosition.h = height - renderPosition.h;
  extraRenderPosition.w = renderPosition.w;
}

void Pipe::render(int camX, int camY){
  //we still need to keep rendering pipe if it's more than 2 blocks above ground
  extraRenderPosition.x = extraPipePosition.x - camX;
  extraRenderPosition.y = extraPipePosition.y - camY;
  if((height - (2 * blockSize)) != 0){
    SDL_RenderCopyEx( gRenderer, blockSheet, &extraPipeSprite, &extraRenderPosition, 0, NULL, SDL_FLIP_NONE );
  }

  //call the nonmoving class's render function
  NonMoving::render(camX, camY);

}

void Pipe::collision(){}

