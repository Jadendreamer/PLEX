/*******************
* File Name: game.cpp
* Author: G. J. Krafsig
* Date: June 21st, 2007
* Purpose: game logic for plex
*******************/
#include "game.h"

/***********
* Purpose: class constructor
* Precondition: none
* Postcondition: game is initilized and ready to begin
***********/
game::game()
{
    //setup the game to start
    over = false; //game isn't over yet
    moves = 0; //haven't made any moves yet
    keys = 0; //no keys yet
    mode = CHARACTERMODE; //default to story mod
    character = 0; //haven't picked one yet
    health = MAXHEALTH; //set it all the way up
    
    //clear the map so its empty
    for (int i = 0; i < MAP_HEIGHT; i++)
        for (int j = 0; j < MAP_WIDTH; j++) 
        {
            map4[i][j] = NOBLOCK; //highest level of the map
            map3[i][j] = NOBLOCK; 
            map2[i][j] = NOBLOCK;
            map1[i][j] = NOBLOCK;
            map0[i][j] = NOBLOCK; //lowest level of the map
        }  
}

/***********
* Purpose: return the info for this map block
* Precondition: x value, y value, map level
* Postcondition: returns the block for that map
***********/
int game::getblock(int i, int j, int level)
{
    switch (level)
    {
        case 0: return map0[i][j];
            break;
            
        case 1: return map1[i][j];
            break;
            
        case 2: return map2[i][j];
            break;
        
        case 3: return map3[i][j];
            break;
            
        case 4: return map4[i][j];
            break;
            
        default: return NOBLOCK;
    }
}

/***********
* Purpose: make blocks fall down
* Precondition: none
* Postcondition: blocks are at their lowest level
***********/
void game::gravity()
{
    for (int x = 0; x < MAPLEVELS; x++)
        for (int i = 0; i < MAP_HEIGHT; i++)
            for (int j = 0; j < MAP_WIDTH; j++) 
            {
                
                if (map4[i][j] != NOBLOCK && map3[i][j] == NOBLOCK && (map2[i][j] != THOUSE && map2[i][j] != TSTONE))
                {
                    map3[i][j] = map4[i][j];
                    map4[i][j] = NOBLOCK;
                }
                
                if (map3[i][j] != NOBLOCK && map2[i][j] == NOBLOCK && (map1[i][j] != THOUSE && map1[i][j] != TSTONE))
                {
                    map2[i][j] = map3[i][j];
                    map3[i][j] = NOBLOCK;
                }
            
                if (map2[i][j] != NOBLOCK && map1[i][j] == NOBLOCK && (map0[i][j] != THOUSE && map0[i][j] != TSTONE))
                {
                    map1[i][j] = map2[i][j];
                    map2[i][j] = NOBLOCK;
                }
                
                if (map1[i][j] != NOBLOCK && map0[i][j] == NOBLOCK)
                {
                    map0[i][j] = map1[i][j];
                    map1[i][j] = NOBLOCK;
                }
        }   
}

/***********
* Purpose: randomly fill the map
* Precondition: none
* Postcondition: map game is filled with blocks
***********/
void game::randommap()
{
    //seed the random number generator
    srand(time(NULL) + rand());
    
    for (int i = 0; i < MAP_HEIGHT; i++)
        for (int j = 0; j < MAP_WIDTH; j++) 
        {
            
            int random = (rand() % 11) -1;
            if (random == 5 || random == 7)
                random++;
                
            map0[i][j] = random; //lowest level of the map
            
            srand(time(NULL) + rand());
            random = (rand() % 11) -1;
            if (random == 5 || random == 7)
                random++;
            
            //make sure the block below isn't 2 tall
            if (map0[i][j] != THOUSE && map0[i][j] != TSTONE)
                map1[i][j] = random; //highest level of the map
             
            srand(time(NULL) + rand());   
            random = (rand() % 11) -1;
            if (random == 5 || random == 7)
                random++;
                
            //make sure the block below isn't 2 tall
            if (map1[i][j] != THOUSE && map1[i][j] != TSTONE)
                map2[i][j] = random; //highest level of the map
             
            srand(time(NULL) + rand());   
            random = (rand() % 11) -1;
            if (random == 5 || random == 7)
                random++;
                
            //make sure the block below isn't 2 tall
            if (map2[i][j] != THOUSE && map2[i][j] != TSTONE)
                map3[i][j] = random; //highest level of the map

        }  
        
        //move all blocks down if there is no block below it
        gravity();
}

/***********
* Purpose: adds a single block to the map
* Precondition: none
* Postcondition: map has one additional block
***********/
void game::addblock()
{
    //seed the random number generator
    srand(time(NULL) + rand());
            
    int random = (rand() % 10);
    if (random == 5 || random == 7)
        random++;
        
    int i, j;
    i = rand() % MAP_HEIGHT;
    j = rand() % MAP_WIDTH;
                
    map4[i][j] = random; //lowest level of the map
        
    //move the block down to the lowest level
    gravity();
}

/***********
* Purpose: fill a level with blocks
* Precondition: level to fill
* Postcondition: level is filled with blocks
***********/
void game::filllevel(int level)
{
    switch (level)
    {
        case 0: fillarray(map0);
            break;
            
        case 1: fillarray(map1);
            break;
            
        case 2: fillarray(map2);
            break;
        
        case 3: fillarray(map3);
            break;
        
        case 4: fillarray(map4);
            break;
            
        default:
                break;    
    }
}

/***********
* Purpose: fill am array with blocks
* Precondition: array to fill
* Postcondition: array is filled with blocks
***********/
void game::fillarray(int map[MAP_HEIGHT][MAP_WIDTH])
{
    for (int i = 0; i < MAP_HEIGHT; i++)
        for (int j = 0; j < MAP_WIDTH; j++) 
        {
            srand(time(NULL) + rand());
            int random = (rand() % 10);
            if (random == 5 || random == 7)
                random++;
                
            map[i][j] = random; //lowest level of the map
        }
}

/***********
* Purpose: set the game mode
* Precondition: mode is either story mode or build mode
* Postcondition: if mode is correct, then mode is set
***********/
void game::setmode(int newmode)
{
        mode = newmode;
}

/***********
* Purpose: returns the game mode
* Precondition: none
* Postcondition: game mode returned
***********/
int game::getmode()
{
    return mode;    
}

/***********
* Purpose: return true if the game is over
* Precondition: none
* Postcondition: returns over value
***********/
bool game::gameover()
{
    return over;    
}
