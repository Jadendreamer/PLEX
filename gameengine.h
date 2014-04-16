/**************
* File Name: gameengine.h
* Author: G. J. Krafsig
* Date: July 3rd, 2007
* Purpose: header files for game engine
**************/
#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <cstdlib> //c stardard library
#include <cmath> //math library
#include <allegro.h> //allegro library
#include <winalleg.h> //override windows info
#include "graphics.h" //graphic files
#include "music.h" //music files
//#include "timer.h" //game timer files
#include "movie.h" //game movie files
#include "menu.h" //game menu files
#include "database.h" //database files
#include "game.h" //game logic files

//default window width and height settings
#define GAMEWIDTH 800
#define GAMEHEIGHT 600

class gameengine
{
	public:
        gameengine(BITMAP *gbuffer); //default class constructor
        
		//Game related functions
		BITMAP *draw(); //draw the buffer to the screen
		bool loading(); //load the game graphics
		bool exitEngine(); //destroy the game graphics
		
		//input handling
		void input(); //respond to game input
		void keyinput(); //respond to key input
		void mouseinput(); //respond to mouse input
		
		//gameplay status
		void play(); //play the game, show everything to the screen
		bool pause(); //pause the game play, they are away from the computer
		bool resume(); //resume the game play
		bool reset(); //reset the game back to start status
		int getMode(); //returns the games current mode
		
		//debugging and error functions
		void debug(bool show); //turn debugging info on or off
		void exitError(); //exits the game if an error turns up
		
		//game win/loose checking
		bool gameover(); //they lost the game
		bool gamewon(); //they won the game
		
		//Menu related options
		BITMAP *showmenu(int type); //show the appropriate menu screen
		BITMAP *selector(int x, int y); //show the selector
		int selected(int menu, int x, int y); //they have selected something on a menu
		
		//Movie related options
		bool loadmovie(); //load any video files
		int playmovie(int num); //setup and play the appropriate movie
		bool pausemovie(); //pause the movie
		bool resumemovie(); //unpause the movie
		bool stopmovie(); //go to the end of the movie (ie don't want to watch the movie)
		
		//Music related options
		bool loadmusic(); //load the game music
		int playmusic(int num); //play the appropriate music
		int volume(int change); //change the volume
		bool mute(); //mute the sound
		bool unmute(); //turn mute off
		bool stopmusic(int num); //stop whatever music is playing
		
		//Graphic related options
        bool mouse(bool show); //show the mouse (or not)
        bool getMouse(); //return the status of the mouse (on or off)
        bool clearscreen(); //clear the screen
        
        //Database related options
        int connect(char *host, char *db, char *user, char *pass);
        bool disconnect();
        char *stringquery();
        int intquery();
        
    private:	
        
        //variables used in the game
        bool debugger;
        bool gamemode;
        bool mouseShow;
        int error;
        
        //objects used in the game
        gamemenu *menu;
        gamemovie *movie;
        BITMAP *buffer;
        gamemusic *music;
        gamegraphics *graphics;
        database *db; 
        //timer *time;
        
        //keydown codes used for input
        bool uppressed;
        bool downpressed;
        bool rightpressed;
        bool leftpressed;
        bool enterpressed;
        bool rightmousepressed;
        bool leftmousepressed;
        
};

#endif
