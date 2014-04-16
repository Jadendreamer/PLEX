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
    
    //clear the story map so its empty
    for (int i = 0; i < SMAP_HEIGHT; i++)
        for (int j = 0; j < SMAP_WIDTH; j++) 
        {
            storymap4[i][j] = NOBLOCK; //highest level of the map
            storymap3[i][j] = NOBLOCK; 
            storymap2[i][j] = NOBLOCK;
            storymap1[i][j] = NOBLOCK;
            storymap0[i][j] = NOBLOCK; //lowest level of the map
        }
        
    //clear the build map so its empty
    for (int i = 0; i < BMAP_HEIGHT; i++)
        for (int j = 0; j < BMAP_WIDTH; j++) 
        {
            buildmap4[i][j] = NOBLOCK; //highest level of the map
            buildmap3[i][j] = NOBLOCK; 
            buildmap2[i][j] = NOBLOCK;
            buildmap1[i][j] = NOBLOCK;
            buildmap0[i][j] = NOBLOCK; //lowest level of the map
        }  
}

/***********
* Purpose: return the info for this map block
* Precondition: x value, y value, map level
* Postcondition: returns the block for that map
***********/
int game::getBlock(int i, int j, int level)
{
    if (mode == STORYMODE)
    {
        switch (level)
        {
            case 0: return storymap0[i][j];
                break;
                
            case 1: return storymap1[i][j];
                break;
                
            case 2: return storymap2[i][j];
                break;
            
            case 3: return storymap3[i][j];
                break;
                
            case 4: return storymap4[i][j];
                break;
                
            default: return NOBLOCK;
        }
    } //end story mode
    else
    {
    
        switch (level)
        {
            case 0: return buildmap0[i][j];
                break;
                
            case 1: return buildmap1[i][j];
                break;
                
            case 2: return buildmap2[i][j];
                break;
            
            case 3: return buildmap3[i][j];
                break;
                
            case 4: return buildmap4[i][j];
                break;
                
            default: return NOBLOCK;
        }   
    }
}

/***********
* Purpose: make blocks fall down
* Precondition: none
* Postcondition: blocks are at their lowest level
***********/
void game::gravity()
{
    
    //story map
    for (int x = 0; x < MAPLEVELS; x++)
        for (int i = 0; i < SMAP_HEIGHT; i++)
            for (int j = 0; j < SMAP_WIDTH; j++) 
            {
                
                if (storymap4[i][j] != NOBLOCK && storymap3[i][j] == NOBLOCK && (storymap2[i][j] != THOUSE && storymap2[i][j] != TSTONE))
                {
                    storymap3[i][j] = storymap4[i][j];
                    storymap4[i][j] = NOBLOCK;
                }
                
                if (storymap3[i][j] != NOBLOCK && storymap2[i][j] == NOBLOCK && (storymap1[i][j] != THOUSE && storymap1[i][j] != TSTONE))
                {
                    storymap2[i][j] = storymap3[i][j];
                    storymap3[i][j] = NOBLOCK;
                }
            
                if (storymap2[i][j] != NOBLOCK && storymap1[i][j] == NOBLOCK && (storymap0[i][j] != THOUSE && storymap0[i][j] != TSTONE))
                {
                    storymap1[i][j] = storymap2[i][j];
                    storymap2[i][j] = NOBLOCK;
                }
                
                if (storymap1[i][j] != NOBLOCK && storymap0[i][j] == NOBLOCK)
                {
                    storymap0[i][j] = storymap1[i][j];
                    storymap1[i][j] = NOBLOCK;
                }
        }
     
     //build map   
     for (int x = 0; x < MAPLEVELS; x++)
        for (int i = 0; i < BMAP_HEIGHT; i++)
            for (int j = 0; j < BMAP_WIDTH; j++) 
            {
                
                if (buildmap4[i][j] != NOBLOCK && buildmap3[i][j] == NOBLOCK && (buildmap2[i][j] != THOUSE && buildmap2[i][j] != TSTONE))
                {
                    buildmap3[i][j] = buildmap4[i][j];
                    buildmap4[i][j] = NOBLOCK;
                }
                
                if (buildmap3[i][j] != NOBLOCK && buildmap2[i][j] == NOBLOCK && (buildmap1[i][j] != THOUSE && buildmap1[i][j] != TSTONE))
                {
                    buildmap2[i][j] = buildmap3[i][j];
                    buildmap3[i][j] = NOBLOCK;
                }
            
                if (buildmap2[i][j] != NOBLOCK && buildmap1[i][j] == NOBLOCK && (buildmap0[i][j] != THOUSE && buildmap0[i][j] != TSTONE))
                {
                    buildmap1[i][j] = buildmap2[i][j];
                    buildmap2[i][j] = NOBLOCK;
                }
                
                if (buildmap1[i][j] != NOBLOCK && buildmap0[i][j] == NOBLOCK)
                {
                    buildmap0[i][j] = buildmap1[i][j];
                    buildmap1[i][j] = NOBLOCK;
                }
        }   
}

/***********
* Purpose: randomly fill the map
* Precondition: none
* Postcondition: map game is filled with blocks
***********/
void game::randomMap()
{
    //seed the random number generator
    srand(time(NULL) + rand());
    
    for (int i = 0; i < SMAP_HEIGHT; i++)
        for (int j = 0; j < SMAP_WIDTH; j++) 
        {
            
            int random = (rand() % 11) -1;
            if (random == 5 || random == 7)
                random++;
                
            storymap0[i][j] = random; //lowest level of the map
            
            srand(time(NULL) + rand());
            random = (rand() % 11) -1;
            if (random == 5 || random == 7)
                random++;
            
            //make sure the block below isn't 2 tall
            if (storymap0[i][j] != THOUSE && storymap0[i][j] != TSTONE)
                storymap1[i][j] = random; //highest level of the map
             
            srand(time(NULL) + rand());   
            random = (rand() % 11) -1;
            if (random == 5 || random == 7)
                random++;
                
            //make sure the block below isn't 2 tall
            if (storymap1[i][j] != THOUSE && storymap1[i][j] != TSTONE)
                storymap2[i][j] = random; //highest level of the map
             
            srand(time(NULL) + rand());   
            random = (rand() % 11) -1;
            if (random == 5 || random == 7)
                random++;
                
            //make sure the block below isn't 2 tall
            if (storymap2[i][j] != THOUSE && storymap2[i][j] != TSTONE)
                storymap3[i][j] = random; //highest level of the map

        } 
        
        //seed the random number generator
    srand(time(NULL) + rand());
    
    for (int i = 0; i < BMAP_HEIGHT; i++)
        for (int j = 0; j < BMAP_WIDTH; j++) 
        {
            
            int random = (rand() % 11) -1;
            if (random == 5 || random == 7)
                random++;
                
            buildmap0[i][j] = random; //lowest level of the map
            
            srand(time(NULL) + rand());
            random = (rand() % 11) -1;
            if (random == 5 || random == 7)
                random++;
            
            //make sure the block below isn't 2 tall
            if (buildmap0[i][j] != THOUSE && buildmap0[i][j] != TSTONE)
                buildmap1[i][j] = random; //highest level of the map
             
            srand(time(NULL) + rand());   
            random = (rand() % 11) -1;
            if (random == 5 || random == 7)
                random++;
                
            //make sure the block below isn't 2 tall
            if (buildmap1[i][j] != THOUSE && buildmap1[i][j] != TSTONE)
                buildmap2[i][j] = random; //highest level of the map
             
            srand(time(NULL) + rand());   
            random = (rand() % 11) -1;
            if (random == 5 || random == 7)
                random++;
                
            //make sure the block below isn't 2 tall
            if (buildmap2[i][j] != THOUSE && buildmap2[i][j] != TSTONE)
                buildmap3[i][j] = random; //highest level of the map

        } 
        
        //move all blocks down if there is no block below it
        gravity();
}

/***********
* Purpose: adds a single block to the map
* Precondition: none
* Postcondition: map has one additional block
***********/
void game::addBlock()
{
    //seed the random number generator
    srand(time(NULL) + rand());
            
    int random = (rand() % 10);
    if (random == 5 || random == 7)
        random++;
        
    int i, j;
    i = rand() % SMAP_HEIGHT;
    j = rand() % SMAP_WIDTH;
                
    storymap4[i][j] = random; //lowest level of the 
    
    //seed the random number generator
    srand(time(NULL) + rand());
            
    random = (rand() % 10);
    if (random == 5 || random == 7)
        random++;
        
    i = rand() % BMAP_HEIGHT;
    j = rand() % BMAP_WIDTH;
                
    buildmap4[i][j] = random; //lowest level of the map
        
    //move the block down to the lowest level
    gravity();
}

/***********
* Purpose: fill a level with blocks
* Precondition: level to fill
* Postcondition: level is filled with blocks
***********/
void game::fillLevel(int level)
{
    switch (level)
    {
        case 0: fillArray(storymap0);
            break;
            
        case 1: fillArray(storymap1);
            break;
            
        case 2: fillArray(storymap2);
            break;
        
        case 3: fillArray(storymap3);
            break;
        
        case 4: fillArray(storymap4);
            break;
            
        default:
                break;    
    }
}

/***********
* Purpose: fill an array with blocks
* Precondition: array to fill
* Postcondition: array is filled with blocks
***********/
void game::fillArray(int map[SMAP_HEIGHT][SMAP_WIDTH])
{
    for (int i = 0; i < SMAP_HEIGHT; i++)
        for (int j = 0; j < SMAP_WIDTH; j++) 
        {
            srand(time(NULL) + rand());
            int random = (rand() % 10);
            if (random == 5 || random == 7)
                random++;
                
            storymap0[i][j] = random; //lowest level of the map
        }
}

/***********
* Purpose: set the game mode
* Precondition: mode is either story mode or build mode
* Postcondition: if mode is correct, then mode is set
***********/
void game::setMode(int newmode)
{
        mode = newmode;
}

/***********
* Purpose: returns the game mode
* Precondition: none
* Postcondition: game mode returned
***********/
int game::getMode()
{
    return mode;    
}

/***********
* Purpose: return true if the game is over
* Precondition: none
* Postcondition: returns over value
***********/
bool game::gameOver()
{
    return over;    
}

/***********
* Purpose: see if there is space for the character to stand here
* Precondition: x and y position, depth of the character
* Postcondition: returns true if character can start on the board here
***********/
bool game::checkForFreeSpace(int xpos, int ypos, int depth)
{
    
    if (xpos < x-3 || xpos > x+3)
        return 0;
        
    if (ypos < y-3 || ypos > y+3)
        return 0;

    switch (depth)
    {
        case 4:
            if (buildmap4[xpos][ypos] != NOBLOCK)
                checkForFreeSpace(xpos+1, ypos+1, depth);
            else
            {
                x = xpos;
                y = ypos;
                depth = 4;
                return 1;
            }
            break;
            
        case 3:
            if (buildmap3[xpos][ypos] != NOBLOCK) //move up one level
                checkForFreeSpace(xpos, ypos, ++depth);
            else
            {
                x = xpos;
                y = ypos;
                depth = 3;
                return 1;
            }
            break;
            
        case 2:
            if (buildmap2[xpos][ypos] != NOBLOCK) //move up one level
                checkForFreeSpace(xpos, ypos, ++depth);
            else
            {
                x = xpos;
                y = ypos;
                depth = 2;
                return 1;
            }
            break;
            
        case 1:
            if (buildmap1[xpos][ypos] != NOBLOCK) //move up one level
                checkForFreeSpace(xpos, ypos, ++depth);
            else
            {
                x = xpos;
                y = ypos;
                depth = 4;
                return 1;
            }
            break;
            
        case 0: //they've fallen through the board, move them up a level
                checkForFreeSpace(x, y, 4);
            break;    
    }
}

/***********
* Purpose: load the build map into the array
* Precondition: the data from the database, characters x and y position
* Postcondition: load this section of the board into the build map array
***********/
bool game::loadBuildBoard(MYSQL_RES *resultquery)
{
    MYSQL_ROW row;
    int id, x, y, depth, type;
    
    while (row = mysql_fetch_row(resultquery))
    {
        //store the values from this row
        id = atoi(row[0]);      //id of the database entry
        x = atoi(row[1]);       //x position
        y = atoi(row[2]);       //y position
        depth = atoi(row[3]);   //depth of block
        type = atoi(row[4]);    //type of block

        //put the results from the query into the array
        switch (depth)
        {
            //highest level of the map
            case 4: buildmap4[x][y] = type;
                break;
            case 3: buildmap3[x][y] = type;
                break;
            case 2: buildmap2[x][y] = type;
                break;
            case 1: buildmap1[x][y] = type;
                break;
            case 0: buildmap0[x][y] = type;
                break;
            //lowest level in the map
    
        } //end switch 
    } //end while
    
}

