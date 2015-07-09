#ifndef GOOMBA_H
#define GOOMBA_H

#include <SDL2/SDL.h>
#include <SDL/SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "globalVars.h"
#include "Ltexture.h"
#include "enemy.h"
using namespace std;

class Goomba: public Enemy{
	public:  
		Goomba(int, int, int, int, int, int, int, int);
		void move(SDL_Rect*);
		void decideFrame();
};

#endif
