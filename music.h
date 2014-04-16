/**************
* File Name: music.h
* Author: G. J. Krafsig
* Date: July 3rd, 2007
* Purpose: header files for game music
**************/
#ifndef GAMEMUSIC_H
#define GAMEMUSIC_H

#include <cstdlib>
#include <cmath>
#include <allegro.h>
#include "map.h"

#define BLOCKFALL 12
#define ERRORMOVE 13
#define THEME     14

class gamemusic
{
	public:
        //class constructor
		gamemusic(); 
		
		bool loadMusic(); //load the game music
		bool destroyMusic(); //free the used memory
		bool playing; //playing the music (or not)
		bool play(int map, int volume, int pan, int rate, int loop); //play music for this map
		bool stop(); //stop current music
		bool sound;
		
		//variables for the sounds
        SAMPLE *blockfall;
        SAMPLE *errormove;
        SAMPLE *theme;
        SAMPLE *current; //current song playing
        
        SAMPLE *ashcanyon;
        SAMPLE *mercyvalley;
        SAMPLE *waterville;  
        SAMPLE *haymarket;
        SAMPLE *merryfield;
        SAMPLE *stonecastle;
        SAMPLE *buildersguild;
        SAMPLE *fuzzyland;
        SAMPLE *landslide;
        SAMPLE *wishingwellfalls;
        SAMPLE *bouldercanyon;
        
};

#endif
