/**************
*
*     P  L  E  X
*
* File Name: main.cpp
* Author: G. J. Krafsig
* Date: August 23rd, 2007
* Purpose: implementation of the game
**************/

#include <stdio.h>
#include <process.h>
#include <allegro.h>
#include <winalleg.h>
#include "gameengine.h"

//toggle the debugger
#define DEBUG 0

//allegro setup
void init(); //initilize allegro
void deinit(); //deinitilize allegro

/***********
* Purpose: main game loop
* Precondition: plex game class declared, game variables all global
* Postcondition: game is over, memory used has been freed
***********/
int main()
{
	init(); //initilize allegro
	
	BITMAP *buffer = create_bitmap(SCREEN_W, SCREEN_H);
    gameengine *plex = new gameengine(buffer);
    
    //load the game graphics
    while (!plex->loading())
        ;
        
    //main loop of the game
	while (!key[KEY_ESC])
    {
        scare_mouse(); //hide the mouse
        
        //start the debugger if its on
        #ifdef DEBUG
            plex->debug(DEBUG);
        #endif
        
        plex->play(); //gameplay action
		
		vsync(); //remove flicker
		
		acquire_screen(); //lock the screen for drawing
		
		if (plex->getMouse())
		  show_mouse(screen); //show the mouse
		
		blit(plex->draw(), screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H); //draw buffer to the screen
		
		release_screen(); //unlock the screen
		
		unscare_mouse(); //show the mouse
	}

    //release all the game shared memory
    plex->exitEngine();
    
    //shutdown allegro
	deinit();
	
	//close the application
	return 0;
}
END_OF_MAIN()

/***********
* Purpose: setup allegro so its ready to use
* Precondition: none
* Postcondition: allegro is ready to go,
*       timer is setup, sound and keyboard and timer
*       are installed
***********/
void init()
{
    //initilize allegro
	int depth, res;
	
	allegro_init();
	depth = desktop_color_depth();
	
	if (!depth)
        depth = 32;
        
	set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0);

	install_timer();
	install_keyboard();
	install_mouse();
	
}

/***********
* Purpose: free up any used memory
* Precondition: none
* Postcondition: memory used for the game have
*                been released
***********/
void deinit()
{
    //clear the keyboard buffer
	clear_keybuf();
}
