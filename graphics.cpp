/**************
* File Name: graphics.cpp
* Author: G. J. Krafsig
* Date: August 2nd, 2007
* Purpose: implementation for game graphic functions
**************/
#include "graphics.h"

/**************
* Purpose: default constructor, initialize class values
* Precondition: none
* Postcondition: none
**************/
gamegraphics::gamegraphics()
{
    //maybe this will do something later...
}

/**************
* Purpose: make the image centered on a black screen
* Precondition: the image to center, x and y position, width and height
* Postcondition: returns the image centered on a black background
**************/
BITMAP *gamegraphics::blitBigger(BITMAP *image, int x, int y, int width, int height)
{
    //clear the temporary image
    BITMAP *temp = create_bitmap(width, height);
    clear(temp);
    blit(image, temp, 0, 0, x, y, image->w, image->h);
    
    //now copy the buffer image back into the intro image (to make the smaller image centered in the screen
    //for blitting later)
    image = create_bitmap(SCREEN_W, SCREEN_H);
    blit(temp, image, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
      
    //destory the temp image, return the bigger one 
    destroy_bitmap(temp);
    return image;
}
