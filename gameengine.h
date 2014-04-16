/**************
* File Name: gameengine.h
* Author: G. J. Krafsig
* Date: July 3rd, 2007
* Purpose: header files for game engine
**************/
#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <cstdlib> //c stardard library
#include <stdio.h>
#include <cmath> //math library
#include <allegro.h> //allegro library
#include <winalleg.h> //override windows info
#include <process.h>
#include <string.h>
#include "map.h" //map files
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

#define DRAWBOARDMINOFFSET 3 //the minimum offset when the board blocks are
                             //drawn to the screen in drawBuildBoard
#define DRAWBOARDMAXOFFSET 6 //the maxium offset when the board blocks are
                             //drawn to the screen in drawBuildBoard
                             
//offset the build board on the screen
#define BOARDOFFSETX 170
#define BOARDOFFSETY 180
                             
#define SCALEDOWN 1.68 //the amount to scale down character images 
                       //on the side bar

class gameengine
{
	public:
        //default class constructor
        gameengine(BITMAP *gbuffer); 
        
		//Game related functions
		BITMAP *draw(); //draw the buffer to the screen
		bool   loading(); //load the game graphics
		void   scrollBoard(); //scroll the screen
		bool   exitEngine(); //destroy the game graphics
		
		//input handling
		void input(); //respond to game input
		void keyInput(); //respond to key input
		void mouseInput(); //respond to mouse input
		void showSelector(); //show the selector on the screen
		
		//gameplay status
		void play(); //play the game, show everything to the screen
		bool pause(); //pause the game play, they are away from the computer
		bool resume(); //resume the game play
		bool reset(); //reset the game back to start status
		void setMode(int newmode); //set the game's current mode
		int  getMode(); //returns the games current mode
		
		//debugging and error functions
		void debug(bool show); //turn debugging info on or off
		void exitError(); //exits the game if an error turns up
		
		//game win/loose checking
		bool gameOver(); //they lost the game
		bool gameWon(); //they won the game
		int  quit(); //quit the game
		
		//Menu related options
		int currentMenu(); //returns the current menu in use
		
		//Movie related options
		int  playMovie(int num); //setup and play the appropriate movie
		bool pauseMovie(); //pause the movie
		bool resumeMovie(); //unpause the movie
		bool stopMovie(); //go to the end of the movie (ie don't want to watch the movie)
		
		//Music related options
		int  volume(int change); //change the volume
		bool mute(); //mute the sound
		bool unmute(); //turn mute off
		bool stopMusic(int num); //stop whatever music is playing
		
		//Block related functions
		bool clickBlock(int x, int y); //figure out which block they are clicking on
		                               //from given mouse x and y position
		void caluclateMouseBlock(); //figures out the x and y for the block the mouse is over
		
		//Graphic related options
        bool mouse(bool show); //show the mouse (or not)
        bool getMouse(); //return the status of the mouse (on or off)
        bool clearScreen(); //clear the screen
        void drawCharacter(int id, int x, int y, float scale); //draw a character
        void drawBuildBoard(int x, int y); //draw the board on the screen
        bool calculateBlitPosition(int dir); //figure out how big of an area to blit
        void blockOver(); //draw block over the character if they are behind a tall block
        void drawSelector(); //draw the block selector (not menu selector)
        
        //Build mode related options
        void buildBoard(); //update board database info the board as the
                           //player moves around the screen
        
        //Database related options
        int  connect(char *host, char *db, char *user, char *pass);
        bool disconnect();
        char *stringQuery(char *query);
        int  intQuery(char *query);
        //bool boolQuery();
        void setId(int newid); //set game member id
        int  getId(); //return database member id
        
        //internet related functions
        int openWindow(char *url); //open the specified url in a browser window
        
    private:	
        
        //variables used in the game
        bool debugger; //debugger status
        bool mouseShow; //mouse visibility
        bool dbConnection; //database connection status
        int  error; //error code
        bool scrolling; //scrolling the screen
        int  scrollmax; //scrolling incrementer
        int  localx; //x position on the smaller screen
        int  localy; //y position on the smaller screen
        int  mousex; //where the mouse block position is on the screen for x
        int  mousey; //where the mouse block position is on the screen for y
        int  id; //database member id
        
        //objects used in the game
        gamemenu     *menu;
        gamemovie    *movie;
        BITMAP       *buffer;
        gamemusic    *music;
        gamegraphics *graphics;
        database     *db; 
        game         *logic;
        //timer        *time;
        
        //keydown codes used for input
        bool upPressed;
        bool downPressed;
        bool rightPressed;
        bool leftPressed;
        bool enterPressed;
        bool rmPressed;
        bool lmPressed;
        bool F2Pressed;
        
};

#endif
