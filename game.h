/**************
* File Name: game.h
* Author: G. J. Krafsig
* Date: June 28th, 2007
* Purpose: game logic header file
**************/

#ifndef GAME_H
#define GAME_H

//define playing mode
#define CHARACTERMODE 0
#define STORYMODE 1
#define TUTORIALMODE 
#define BUILDMODE 3

//normal block type definitions
#define WOOD 9
#define WATER 8
#define THOUSE 7
#define HOUSE 6
#define TSTONE 5
#define STONE 4
#define GRAY 3
#define GRASS 2
#define DIRT 1
#define BROWN 0
#define NOBLOCK -1

//house block type definitions
#define WINDOW 10
#define CLOSEDDOOR 11
#define OPENDOOR 12
#define ROOFNORTH 13
#define ROOFNORTHEAST 14
#define ROOFEAST 15
#define ROOFSOUTHEAST 16
#define ROOFSOUTH 17
#define ROOFSOUTHWEST 18
#define ROOFWEST 19
#define ROOFNORTHWEST 20

//landscape block type definitions
#define TALLTREE 21
#define SHRUB 22
#define BUSH 23
#define ROCK 24

//ramp block type definitions
#define RAMPNORTH 25
#define RAMPSOUTH 26
#define RAMPEAST 27
#define RAMPWEST 28

//gem block type definitions
#define BLUEGEM 1
#define YELLOWGEM 2
#define GREENGEM 3

//character type definitions
#define ALEX 1
#define KITTY 2
#define TANYA 3
#define LISA 4
#define RAVEN 5
#define BELLA 6

//character maximum health
#define MAXHEALTH 6

//size of story map dimensions (always 5 deep)
#define SMAP_HEIGHT 4 //down
#define SMAP_WIDTH 8 //across

//size of build map dimensions (always 5 deep)
#define BMAP_HEIGHT 100 //down
#define BMAP_WIDTH 100 //across

//block info
#define BLOCKWIDTH 101
#define BLOCKHEIGHT 85
#define MAPLEVELS 5

//included files
#include <cstdlib>
#include <cmath>
#include <allegro.h>
#include <winalleg.h>
#include "mysql/mysql.h"

class game
{
	public:
		game(); // class constructor
		
		//map functions
		void randomMap(); //randomize the map
		int  getBlock(int i, int j, int level); //returns the block at that spot
		void gravity(); //make blocks fall down
		void addBlock(); //adds a block to the highest map level
		void addBlock(int i, int j, int level); //add a block here (type doesn't matter)
		void addBlock(int i, int j, int level, int type); //put a block here
		void fillLevel(int level); //fill a story level with blocks
		void fillArray(int map[SMAP_HEIGHT][SMAP_WIDTH]); //fill story array with blocks
		
		//game functions
		bool gameOver(); //returns true if game is over
		void loadGame(char filename[]); //load a game from a file
		
        //game mode functions
		void setMode(int newmode); //set the game play mode
		int  getMode(); //returns the game play mode
		
		//build mode related funtions
		bool checkForFreeSpace(int x, int y, int depth);
		bool loadBuildBoard(MYSQL_RES *resultquery);
		
		//database information
		int  id; //the id of the member
		char *name; //their playing name
        int  character; //they character they're playing with
        int  x; //their x position
        int  y; //their y position
        int  depth; //their depth on the board
        int  yellow; //their yellow jewels
        int  blue; //their blue jewels
        int  green; //their green jewels
		
	private:
        //story maps
        int storymap4[SMAP_HEIGHT][SMAP_WIDTH]; //highest level of the map
        int storymap3[SMAP_HEIGHT][SMAP_WIDTH]; 
        int storymap2[SMAP_HEIGHT][SMAP_WIDTH];
        int storymap1[SMAP_HEIGHT][SMAP_WIDTH];
        int storymap0[SMAP_HEIGHT][SMAP_WIDTH]; //bottom level of the map
        
        //build maps
        int buildmap4[BMAP_HEIGHT][BMAP_WIDTH]; //highest level of the map
        int buildmap3[BMAP_HEIGHT][BMAP_WIDTH]; 
        int buildmap2[BMAP_HEIGHT][BMAP_WIDTH];
        int buildmap1[BMAP_HEIGHT][BMAP_WIDTH];
        int buildmap0[BMAP_HEIGHT][BMAP_WIDTH]; //bottom level of the map
        
        int  location; //the map they are currently on in story mode
        int  moves; //number of moves they've made
        int  health; //their character's health
        bool over; //set to true if the game is over
        int  keys; //the number of keys they have
        int  mode; //the mode they are playing the game in
        
};

#endif
