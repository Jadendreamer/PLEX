/**************
* File Name: game.h
* Author: G. J. Krafsig
* Date: June 28th, 2007
* Purpose: game logic header file
**************/

#ifndef GAME_H
#define GAME_H

//define playing modes
#define CHARACTERMODE 0 //picking a character
#define STORYMODE     1 //playing game in story mode
#define TUTORIALMODE  2 //taking the game tutorial
#define BUILDMODE     3 //playing game in online-multiplayer mode

//normal block type definitions
#define WOOD     9
#define WATER    8
#define THOUSE   7
#define HOUSE    6
#define TSTONE   5
#define STONE    4
#define GRAY     3
#define GRASS    2
#define DIRT     1
#define BROWN    0
#define NOBLOCK -1

//house block type definitions
#define WINDOW        10
#define CLOSEDDOOR    11
#define OPENDOOR      12
#define ROOFNORTH     13
#define ROOFNORTHEAST 14
#define ROOFEAST      15
#define ROOFSOUTHEAST 16
#define ROOFSOUTH     17
#define ROOFSOUTHWEST 18
#define ROOFWEST      19
#define ROOFNORTHWEST 20

//landscape block type definitions
#define TALLTREE 21
#define SHRUB    22
#define BUSH     23
#define ROCK     24

//ramp block type definitions
#define RAMPNORTH 25
#define RAMPSOUTH 26
#define RAMPEAST  27
#define RAMPWEST  28

//gem block type definitions
#define BLUEGEM   0 
#define YELLOWGEM 1
#define GREENGEM  2

//character type definitions
#define ALEX  0
#define KITTY 1
#define TANYA 2
#define LISA  3
#define RAVEN 4
#define BELLA 5

//character maximum health
#define MAXHEALTH 6

//size of story map dimensions (always 5 deep)
#define SMAP_HEIGHT 10 //down
#define SMAP_WIDTH  14 //across

//size of build map dimensions (always 5 deep)
#define BMAP_HEIGHT 100 //down
#define BMAP_WIDTH  100 //across

//block info
#define BLOCKWIDTH  101
#define BLOCKHEIGHT 85
#define MAPLEVELS   5

//included files
#include <cstdlib>
#include <cmath>
#include <allegro.h>
#include <winalleg.h>
#include <iostream.h>
#include <fstream.h>
#include <string>
#include "map.h"
#include "mysql/mysql.h"

using namespace std;

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
		void fillArray(int map[SMAP_HEIGHT][SMAP_WIDTH]); //fill story array with 
		int tallBlock(int x, int y, int level); //see if there is a tall block under this level
		int waterBlock(int x, int y, int level); //see if there is a water block in this position
		int noBlock(int x, int y, int level); //see if there is a water block in this position
		
		//game functions
		bool gameOver(); //returns true if game is over
		int loadGame(char *filename); //load a game from a file
		bool loadMapFile(char *filename); //load a map from a file
		bool loadPlayerFile(char *filename); //load player info from a file
		bool loadNPCFile(char *filename);
		int saveGame(char *filename); //save a game to a file with
		                                     //the given filename
		bool encryptFile(char *filename); //encrypt this file so they can't open it
		                              //and mess with the data inside
		bool decryptFile(char *filename); //decrypt an encrypted file
		char *getMapFile(int currentMap); //returns the filename for the map
		                                  //they are currently on
		
		//parsing functions
		bool parseSavedFile(char *filename); //figure out saved files for this game
		bool parseMapFile(char *filename); //load map data into map array
		
        //game mode functions
		void setMode(int newmode); //set the game play mode
		int  getMode(); //returns the game play mode
		
		//character & block movement
		bool validMove(int x, int y);
		bool placeBlock(int newx, int newy); 
		bool characterOnBlock(); //return false if there isn't a character on this block
		
		//build mode related funtions
		bool checkForFreeSpace(int x, int y, int depth);
		bool loadBuildBoard(MYSQL_RES *resultquery);
		
		//variables
		int  id; //the id of the member
		char *name; //their playing name
        int  character; //they character they're playing with
        int  x; //their x position
        int  y; //their y position
        int  depth; //their depth on the board
        int  yellow; //their yellow jewels
        int  blue; //their blue jewels
        int  green; //their green jewels
        int  selectedblockx; //the x position of the block they clicked on
        int  selectedblocky; //the y position of the block they clicked on
        char *playerdata; //data file for player info on load/save of a game
        char *npcdata; //data file for NPC characters on load/save of a game
        char *map; //data file for the current game map
        int  currentMap; //the map they are currently on in story mode
        int  moves; //number of moves they've made
        int  health; //their character's health
        bool over; //set to true if the game is over
        int  keys; //the number of keys they have
        int  mode; //the mode they are playing the game in (story/build)  
        
        //map *worldmap; //the maps in the game
		
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
        
};

#endif
