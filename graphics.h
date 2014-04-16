/**************
* File Name: graphics.h
* Author: G. J. Krafsig
* Date: July 3rd, 2007
* Purpose: header files for game engine graphics
**************/
#ifndef GAMEGRAPHICS_H
#define GAMEGRAPHICS_H

#include <cstdlib>
#include <cmath>
#include <allegro.h>
#include "sprite.h"

class gamegraphics
{
	public:
		gamegraphics(); //class constructor	
		//position an image on a larger screen
		BITMAP *blitBigger(BITMAP *image, int x, int y, int width, int height);

};

#endif
