/**************
* File Name: sprite.h
* Author: G. J. Krafsig
* Date: June 8, 2007
* Purpose: sprite structure
**************/

typedef struct SPRITE
{
    int x; //x pos
    int y; //y pos
    int w; //width
    int h; //height
    int cf; //current frame
    int nf; //next frame
    int fr; //frame rate
    int mf; //maximum frames
    int s; //speed
    bool d; //direction
    bool play; //play the animation or not
    bool display; //show on the screen (or not)
    bool show; //the sprite was displayed on the screen (so its not drawn again)
};
