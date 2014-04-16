/**************
* File Name: menu.h
* Author: G. J. Krafsig
* Date: July 3rd, 2007
* Purpose: header files for game menus
**************/
#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <cstdlib>
#include <cmath>
#include <allegro.h>
#include <winalleg.h>
#include "graphics.h"

//images used for the menu
#define LOADINGIMAGE        "images/loadingdata.pcx"
#define NEWGAMEIMAGE        "images/introduction.pcx"
#define GAMEMODEIMAGE       "images/modescreen.pcx"
#define PAUSEIMAGE          "images/pause.pcx"
#define STOREIMAGE          "images/store.pcx"
#define LOADGAMEIMAGE       "images/loadgame.pcx"
#define SAVEGAMEIMAGE       "images/loadgame.pcx"
#define SELECTORIMAGE       "images/smallbluegem.pcx"
#define BUILDLOGINIMAGE     "images/buildlogin.pcx"

//game menu screens
#define NOMENU 0
#define LOADINGSCREEN 1
#define NEWGAMESCREEN 2
#define GAMEMODESCREEN 3
#define PAUSESCREEN 4
#define STORESCREEN 5
#define LOADGAMESCREEN 6
#define SAVEGAMESCREEN 7
#define BUILDLOGINSCREEN 8
#define CHARACTERSCREEN 9

class gamemenu
{
	public:
		gamemenu(); // class constructor
		bool loadgraphics(int width, int height); //load the graphics for the different screens
		void destorygraphics(); //destroy the graphics that were loaded
		int currentScreen(); //returns int screen
		bool setScreen(int num); //set the screen to something else
		BITMAP *getScreen(int num); //returns the bitmap for the appropriate num, or the bitmap for
		                            //the current value of int screen
		                            
		//selector related options
		BITMAP *getSelector(); //return the selector image
		SPRITE selector; //select things from the game map
		void setSelectorY(int amount); //change the selector y value
		void setSelectorX(int amount); //change the selector x value
		bool shown; //the screen was shown on the screen	
		
	private:
        gamegraphics *graphics; //start the game graphics class
        BITMAP *loading; //loading data/graphics screen
        BITMAP *newload; //load a new game screen
        BITMAP *gameplay; //select the gameplay mode screen
        BITMAP *pause; //the pasued game screen
        BITMAP *store; //the store menu screen
        BITMAP *loadgame; //the loadgame menu screen
        BITMAP *savegame; //the save a game menu screen
        BITMAP *select; //the selector jewel
        BITMAP *build; //the build login screen
        int screen; //the menu screen that they're on

};
#endif
