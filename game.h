/**************
* File Name: timer.h
* Author: G. J. Krafsig
* Date: June 28th, 2007
* Purpose: game logic
**************/

#ifndef GAME_H
#define GAME_H

//define playing mode
#define CHARACTERMODE 0
#define STORYMODE 1
#define BUILDMODE 2

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
#define WINDOW 1
#define CLOSEDDOOR 2
#define OPENDOOR 3
#define ROOFNORTH 4
#define ROOFNORTHEAST 5
#define ROOFEAST 6
#define ROOFSOUTHEAST 7
#define ROOFSOUTH 8
#define ROOFSOUTHWEST 9
#define ROOFWEST 10
#define ROOFNORTHWEST 11

//gem block type definitions
#define BLUEGEM 1
#define YELLOWGEM 2
#define GREENGEM 3

//landscape block type definitions
#define TALLTREE 1
#define SHRUB 2
#define BUSH 3
#define ROCK 4

//ramp block type definitions
#define RAMPNORTH 1
#define RAMPSOUTH 2
#define RAMPEAST 3
#define RAMPWEST 4

//character type definitions
#define ALEX 1
#define KITTY 2
#define TANYA 3
#define LISA 4
#define RAVEN 5
#define BELLA 6

//character maximum health
#define MAXHEALTH 6

//the size of the plex map
#define MAP_HEIGHT 4 //down
#define MAP_WIDTH 8 //across

//block info
#define BLOCKWIDTH 101
#define BLOCKHEIGHT 85
#define MAPLEVELS 5

//included files
#include <cstdlib>
#include <cmath>
#include <allegro.h>

class game
{
	public:
		game(); // class constructor
		void randommap(); //randomize the map
		bool gameover(); //returns true if game is over
		int getblock(int i, int j, int level); //returns the block at that spot
		void gravity(); //make blocks fall down
		void addblock(); //adds a block to the highest map level
		void filllevel(int level); //fill a level with blocks
		void fillarray(int map[MAP_HEIGHT][MAP_WIDTH]); //fill this array with blocks
		void loadgame(char filename[]); //load a game from a file
		void setmode(int newmode); //set the game play mode
		int getmode(); //returns the game play mode
		
	private:
        int map4[MAP_HEIGHT][MAP_WIDTH]; //highest level of the map
        int map3[MAP_HEIGHT][MAP_WIDTH]; 
        int map2[MAP_HEIGHT][MAP_WIDTH];
        int map1[MAP_HEIGHT][MAP_WIDTH];
        int map0[MAP_HEIGHT][MAP_WIDTH]; //bottom level of the map
        
        int moves; //number of moves they've made
        int character; //the character they are playing with
        int health; //their character's health
        bool over; //set to true if the game is over
        int keys; //the number of keys they have
        int mode; //the mode they are playing the game in
        
};

#endif
