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
    mode = CHARACTERMODE; //default to story mode
    character = 0; //haven't picked one yet
    health = MAXHEALTH; //set it all the way up
    selectedblockx = NOBLOCK;
    selectedblocky = NOBLOCK;
    depth = 1;
    currentMap = -1;
    x = 0;
    y = 0;
    
    //create the game map object
    //worldmap = new map();
    
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
            } //end for
     
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
            } //end for 
} //end function

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
* Purpose: check to see if they're making a valid move
* Precondition: value of 1 in newx adds to the x coordinate, -1 subtracts
*               value of 1 in newy adds to the y coordinate, -1 subtracts
* Postcondition: returns true if they can move there
***********/
bool game::validMove(int newx, int newy)
{
    int localx, localy;
    
    newx = x + newx;
    newy = y + newy;
    
    //there is a tall block there
    if (tallBlock(newx, newy, depth))
        return 0;     
     
    //can't walk on water blocks   
    if (waterBlock(newx, newy, depth))
        return 0;
     
    //can't walk where there aren't any blocks   
    if (noBlock(newx, newy, depth))
        return 0;
     
    //can't move on blocks that have something on top of them at that depth   
    if (depth != 0 && getBlock(newx, newy, depth-1) != NOBLOCK)
        return 0;
        
    //if (getBlock(localx, localy, depth) == NOBLOCK)
    //    return 0;
        
    return 1;
}

/***********
* Purpose: see if there is space for the character to stand here
* Precondition: x and y position, depth of the character
* Postcondition: returns true if character can start on the board here
***********/
bool game::checkForFreeSpace(int xpos, int ypos, int xdepth)
{
    
    if (xpos < x-3 || xpos > x+3)
        return 0;
        
    if (ypos < y-3 || ypos > y+3)
        return 0;

    switch (xdepth)
    {
        case 4:
            if (buildmap4[xpos][ypos] != NOBLOCK && !tallBlock(xpos, ypos, xdepth))
                checkForFreeSpace(xpos+1, ypos+1, xdepth);
            else 
            {
                x = xpos;
                y = ypos;
                depth = 4;
                return 1;
            }
            break;
            
        case 3:
            if (buildmap3[xpos][ypos] != NOBLOCK && !tallBlock(xpos, ypos, xdepth)) //move up one level
                return checkForFreeSpace(xpos, ypos, ++xdepth);
            else
            {
                x = xpos;
                y = ypos;
                depth = 3;
                return 1;
            }
            break;
            
        case 2:
            if (buildmap2[xpos][ypos] != NOBLOCK && !tallBlock(xpos, ypos, xdepth)) //move up one level
                return checkForFreeSpace(xpos, ypos, ++xdepth);
            else
            {
                x = xpos;
                y = ypos;
                depth = 2;
                return 1;
            }
            break;
            
        case 1:
            if (buildmap1[xpos][ypos] != NOBLOCK && !tallBlock(xpos, ypos, xdepth)) //move up one level
                return checkForFreeSpace(xpos, ypos, ++xdepth);
            else
            {
                x = xpos;
                y = ypos;
                depth = 1;
                return 1;
            }
            break;
            
        case 0: //they've fallen through the board, move them up a level
                return checkForFreeSpace(x, y, 4);
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

/***********
* Purpose: load this player's saved game
* Precondition: game file has been decrpted
* Postcondition: saved game has been restored
***********/
int game::loadGame(char *filename)
{
    int error = 0;
    
    //decrypt all files before loading them
    
    //redirect it to go here no matter what
    filename = "saved/testsave.plex";
    
    if (!filename) //invalid game file
        error = 102;
    
    //parse out the information
    error = parseSavedFile(filename);
    
    if (error) //error reading saved file
        return 103;
        
    //load the player file
    //error = loadPlayerFile(playerdata);
    
    if (error) //error reading player file
        return 104;
    
    //load the map file depending on where they currently are
    //error = loadMapFile(getMapFile(currentmap));
    
    if (error) //error reading map file
        return 105;
    
    //load the NPC file
    //error = loadNPCFile(npcdata);
    
    if (error) //error reading npc file
        return 106;
    
    //game has finished loading
    return true;
}

/***********
* Purpose: load the current map from a file
* Precondition: map file is decrypted
* Postcondition: map file has been loaded into the story map
***********/
bool game::loadMapFile(char *filename)
{
    //parse out the information from the file
    //and load it into the story map   
    
    //encrypt this file
    
    //load complete
    return true;
}

/***********
* Purpose: load player information into the game
* Precondition: player file is decrypted
* Postcondition: all the player information and game variables have 
*                been reset to their former position
***********/
bool game::loadPlayerFile(char *filename)
{
    //parse out the information from the file
    //and load it into the game, restoring variables
    //to their previous state
    
    //encrypt this file
    
    //load complete
    return true;
}

/***********
* Purpose: load NPC information into the game
* Precondition: NPC file is decrypted
* Postcondition: returns true if there is a tall block there, otherwise false
***********/
bool game::loadNPCFile(char *filename)
{
    //parse out information from the file
    //and load it into the game, restoring NPC
    //characters to their previous state
    
    //encrypt this file
    
    //load complete
    return true;
}

/***********
* Purpose: save the current game state
* Precondition: filename is valid
* Postcondition: all game state information has been saved
***********/
int game::saveGame(char *filename)
{
    //try to create this file
    
    //create the map files
    
    //create the player file
    
    //create the NPC file
    
    //encrypt all files
    
    //save complete
    return true;
}

/***********
* Purpose: encrypt file information
* Precondition: filename is valid
* Postcondition: file has been encrypted
***********/
bool game::encryptFile(char *filename)
{
   //encrypt this file
   
   //finished
   return true; 
}

/***********
* Purpose: decrypt file information
* Precondition: filename is valid
* Postcondition: file has been decrypted
***********/
bool game::decryptFile(char *filename)
{
    //decrypt this file
    
    //finished
}

/***********
* Purpose: return the filename for the data of the map the character is on
* Precondition: current map is valid
* Postcondition: maps filename is returned
***********/
char *game::getMapFile(int currentMap)
{
    //this may change if I make a map class!!!
    //(which i probably should, urrgh)
    switch(currentMap)
    {
        /*case 0: return map->landslide;
            break;
        case 1: return map->waterville;
            break;
        case 2: return map->haymarket;
            break;
        case 3: return map->stonecastle;
            break;
        case 4: return map->mercyvalley;
            break;
        case 5: return map->fuzzyland;
            break;
        case 6: return map->wishingwellfalls;
            break;
        case 7: return map->bouldercanyon;
            break;
        case 8: return map->merryfield;
            break;
        case 9: return map->ashcanyon;
            break;
        case 10: return map->buildersguild;
            break;*/
    }
    
}

/***********
* Purpose: parse a story map file
* Precondition: file is valid and decrypted
* Postcondition: map has been loaded into the story map array
***********/
bool game::parseMapFile(char *filename)
{
    ifstream file;
    char name[255], peek, block[2], x[3], y[3], z[3];
    int newblock = -1;
    
    file.open(filename);
    
    if (!file) //could not open the file
        return false;
    
    while (!file.eof())
    {
        file.get(x, 3, ','); //get first coordinate
        file.ignore();
        file.get(y, 3, ','); //get second coordinate
        file.ignore();
        file.get(z, 3, '\t'); //get third coordinate
 
        file.ignore();     
        file.get(block, 2, '\n'); //get the block
        file.ignore();
        
        int newz = atoi(z);
        int newx = atoi(x);
        int newy = atoi(y);
        
        if (block[0] == '-') //no block in that spot
            newblock = -1;
        else
            newblock = atoi(block);
        
        //covert coordinates to integers
        //fill the map array
        switch (newz)
        {
            
            case 0: storymap0[newx][newy] = newblock;
                break;
            case 1: storymap1[newx][newy] = newblock;
                break;
            case 2: storymap2[newx][newy] = newblock;
                break;
            case 3: storymap3[newx][newy] = newblock;
                break;
            case 4: storymap4[newx][newy] = newblock;
                break;
            default: 
                break;
        }
    }
    
    //FIX THIS!!!!!!!! //makes sure 0,0 is empty
    storymap0[0][0] = -1;
        
    return true;
}

/***********
* Purpose: parse a saved game file
* Precondition: file is valid and decrypted
* Postcondition: saved game file data has been loaded
***********/
bool game::parseSavedFile(char *filename)
{
    //parse out filenames from the gamefile
    ifstream file;
    char name[255];
    char delim[10];
    char value[255];
    char peek;
    string token[14] = {"playerdata", "npcdata", "landslide", "waterville",
                       "haymarket", "stonecastle", "mercyvalley", "fuzzyland",
                       "wishingwellfalls", "bouldercanyon", "merryfield",
                       "ashcanyon", "buildersguild"};
    int i = 0;
    
    file.open(filename);
    
    if (!file)
        return false;
        
    while (!file.eof())
    {
        file.get(name, 255, ' '); //pull off info to the first space
            
        if (!token[i].compare(name)) //matching value
        {
            
            peek = file.peek();
            if (peek == ' ')
                file.ignore(); //ignore white space
                
            file.get(delim, 10, ' '); //get more data up to next white space
            
            peek = file.peek();
            if (peek == ' ') //ignore white space
                file.ignore();
                
            file.get(value, 255); //the rest of the info
            
            peek = file.peek();
            if (peek == '\n')
                file.ignore();
            
            if (i == 0) //player data variable
                strcpy(playerdata, value);
            if (i == 1) //npc data variable
                strcpy(npcdata, value);
            /*if (i == 3)
                strcpy(map->landslide, value);
            if (i == 4)
                strcpy(map->waterville, value);
            if (i == 5)
                strcpy(map->haymarket, value);
            if (i == 6)
                strcpy(map->stonecastle, value);
            if (i == 7)
                strcpy(map->mercyvalley, value);
            if (i == 8)
                strcpy(map->fuzzyland, value);
            if (i == 9)
                strcpy(map->wishingwellfalls, value);
            if (i == 10)
                strcpy(map->bouldercanyon, value);
            if (i == 11)
                strcpy(map->merryfield, value);
            if (i == 12)
                strcpy(map->ashcanyon, value);
            if (i == 13)
                strcpy(map->buildersguild, value);   
                */
        }
        else
            return false; //token not found
            
        i++;
        
    }
     
     return true;
}

/***********
* Purpose: check to see if there is a tall block under this spot
* Precondition: the level to check under, the x and y position of the block
* Postcondition: returns true if there is a tall block there, otherwise false
***********/
int game::tallBlock(int x, int y, int level)
{
    if (mode == BUILDMODE)
    {
        switch (level)
        {
        
            case 3: if (buildmap3[x][y] == THOUSE || buildmap3[x][y] == TSTONE)
                        return true;
                    else
                        return false;
                    break;
            
            case 2: if (buildmap2[x][y] == THOUSE || buildmap2[x][y] == TSTONE)
                        return true;
                    else
                        return false;
                    break;  
                    
            case 1: if (buildmap1[x][y] == THOUSE || buildmap1[x][y] == TSTONE)
                        return true;
                    else
                        return false;
                    break;
            case 0: if (buildmap0[x][y] == THOUSE || buildmap0[x][y] == TSTONE)
                        return true;
                    else
                        return false;
                    break;
            default: return false;

        }  
    }
    else //storymode
    {
        switch (level)
        {
            case 3: if (storymap3[x][y] == THOUSE || storymap3[x][y] == TSTONE)
                        return true;
                    else
                        return false;
                    break;
            
            case 2: if (storymap2[x][y] == THOUSE || storymap2[x][y] == TSTONE)
                        return true;
                    else
                        return false;
                    break;  
                    
            case 1: if (storymap1[x][y] == THOUSE || storymap1[x][y] == TSTONE)
                        return true;
                    else
                        return false;
                    break;
            case 0: if (storymap0[x][y] == THOUSE || storymap0[x][y] == TSTONE)
                        return true;
                    else
                        return false;
                    break;
            default: return false;
        }
    } 
}

/***********
* Purpose: check to see if there is a water block here
* Precondition: the position and level to check
* Postcondition: returns true if a water block is there
***********/
int game::waterBlock(int x, int y, int level)
{
    if (mode == BUILDMODE)
    {
        switch (level)
        {
            case 4: if (buildmap4[x][y] == WATER)
                        return true;
                    else
                        return false;
                    break;
                    
            case 3: if (buildmap3[x][y] == WATER)
                        return true;
                    else
                        return false;
                    break;
            
            case 2: if (buildmap2[x][y] == WATER)
                        return true;
                    else
                        return false;
                    break;  
                    
            case 1: if (buildmap1[x][y] == WATER)
                        return true;
                    else
                        return false;
                    break;
            case 0: if (buildmap0[x][y] == WATER)
                        return true;
                    else
                        return false;
                    break;
        }  
    }
    else //storymode
    {
        switch (level)
        {
            case 4: if (storymap4[x][y] == WATER)
                        return true;
                    else
                        return false;
                    break;
            
            case 3: if (storymap3[x][y] == WATER)
                        return true;
                    else
                        return false;
                    break;
            
            case 2: if (storymap2[x][y] == WATER)
                        return true;
                    else
                        return false;
                    break;  
                    
            case 1: if (storymap1[x][y] == WATER)
                        return true;
                    else
                        return false;
                    break;
            case 0: if (storymap0[x][y] == WATER)
                        return true;
                    else
                        return false;
                    break;
        }
    } 
}

/***********
* Purpose: check to see if there is no block here
* Precondition: the position and level to check
* Postcondition: returns true if no block is there
***********/
int game::noBlock(int x, int y, int level)
{
    if (mode == BUILDMODE)
    {
        switch (level)
        {
            case 4: if (buildmap4[x][y] == NOBLOCK)
                        return true;
                    else
                        return false;
                    break;
                    
            case 3: if (buildmap3[x][y] == NOBLOCK)
                        return true;
                    else
                        return false;
                    break;
            
            case 2: if (buildmap2[x][y] == NOBLOCK)
                        return true;
                    else
                        return false;
                    break;  
                    
            case 1: if (buildmap1[x][y] == NOBLOCK)
                        return true;
                    else
                        return false;
                    break;
            case 0: if (buildmap0[x][y] == NOBLOCK)
                        return true;
                    else
                        return false;
                    break;
        }  
    }
    else //storymode
    {
        switch (level)
        {
            case 4: if (storymap4[x][y] == NOBLOCK)
                        return true;
                    else
                        return false;
                    break;
            
            case 3: if (storymap3[x][y] == NOBLOCK)
                        return true;
                    else
                        return false;
                    break;
            
            case 2: if (storymap2[x][y] == NOBLOCK)
                        return true;
                    else
                        return false;
                    break;  
                    
            case 1: if (storymap1[x][y] == NOBLOCK)
                        return true;
                    else
                        return false;
                    break;
            case 0: if (storymap0[x][y] == NOBLOCK)
                        return true;
                    else
                        return false;
                    break;
        }
    } 
}

/**************
* Purpose: move block here (if possible) and let it fall
* Precondition: x and y of block to move, new x and y to move it to
* Postcondition: moves block if possible, otherwise play error sound
**************/
bool game::placeBlock(int newx, int newy)
{
    //check to see if there's a block they can pick up at currentx,currenty
    int newdepth = -1;
    int block = NOBLOCK;

    //make sure they're not trying to move the block to its same position
    if (selectedblockx == newx && selectedblocky == newy)
        return false;
      
    //character on that block  
    if (characterOnBlock())
        return false;
      
    //tall block there  
    if (depth != 0)
        if (tallBlock(newx, newy, depth))
            return false;
        
    //can only move it one up or one down
    if (newx > selectedblockx+1 || newx < selectedblockx-1)
        return false;
      
    //can only move it one left or one right  
    if (newy > selectedblocky+1 || newy < selectedblocky-1)
        return false;
        
    //can't move the block on top of where they're standing
    if (newx == x && newy == y)
        return false;
    
    //trying this in story mode
    if (getMode() == STORYMODE)
    {
        //trying to move the block to a position thats already full
        if (storymap0[newx][newy] != NOBLOCK)
            return false;
        
        if (storymap0[selectedblockx][selectedblocky] != NOBLOCK) //block on very top level
        {
            block = storymap0[selectedblockx][selectedblocky];
            newdepth = 0;
        }
            
        if (newdepth == -1 && storymap1[selectedblockx][selectedblocky] != NOBLOCK) //no block on top level
        {
            block = storymap1[selectedblockx][selectedblocky];
            newdepth = 1;
        }
            
        if (newdepth == -1 && storymap2[selectedblockx][selectedblocky] != NOBLOCK) //second level
        {
            newdepth = 2;
            block = storymap2[selectedblockx][selectedblocky];
        }
            
        if (newdepth == -1 && storymap3[selectedblockx][selectedblocky] != NOBLOCK) //third level
        {
            block = storymap3[selectedblockx][selectedblocky];
            newdepth = 3;
        }
            
        if (newdepth != -1 && storymap4[selectedblockx][selectedblocky] != NOBLOCK) //fourth level
        {
            newdepth = 4;
            block = storymap4[selectedblockx][selectedblocky];
        }
            
        //no block exists at that position
        if (newdepth == -1) 
            return false;
            
        //they selected a tall block
        if (block == TSTONE || block == THOUSE)
            return false;
        
        //the selected block exists, try moving it to the new position
        //check to see if it can drop down to lower levels
        if (storymap0[newx][newy] == NOBLOCK)
        {
            if (storymap1[newx][newy] == NOBLOCK)
                if (storymap2[newx][newy] == NOBLOCK)
                    if (storymap3[newx][newy] == NOBLOCK)
                        if (storymap4[newx][newy] == NOBLOCK)
                            storymap4[newx][newy] = block;
                        else storymap3[newx][newy] = block;
                    else storymap2[newx][newy] = block;
                else storymap1[newx][newy] = block;
            else storymap0[newx][newy] = block;
        }
        else if (storymap1[newx][newy] == NOBLOCK)
        {
                if (storymap2[newx][newy] == NOBLOCK)
                    if (storymap3[newx][newy] == NOBLOCK)
                        if (storymap4[newx][newy] == NOBLOCK)
                            storymap4[newx][newy] = block;
                        else storymap3[newx][newy] = block;
                    else storymap2[newx][newy] = block;
                else storymap1[newx][newy] = block;
        }
        else if (storymap2[newx][newy] == NOBLOCK)
        {
                    if (storymap3[newx][newy] == NOBLOCK)
                        if (storymap4[newx][newy] == NOBLOCK)
                            storymap4[newx][newy] = block;
                        else storymap3[newx][newy] = block;
                    else storymap2[newx][newy] = block;
        }
        else if (storymap3[newx][newy] == NOBLOCK)
        {
                        if (storymap4[newx][newy] == NOBLOCK)
                            storymap4[newx][newy] = block;
                        else storymap3[newx][newy] = block;
        }
        else if (storymap4[newx][newy] == NOBLOCK)
            storymap4[newx][newy] = block;
        
        //remove this block from its old position
        switch(newdepth)
        {
            case 0: storymap0[selectedblockx][selectedblocky] = NOBLOCK;
                    break;
            case 1: storymap1[selectedblockx][selectedblocky] = NOBLOCK;
                    break;
            case 2: storymap2[selectedblockx][selectedblocky] = NOBLOCK;
                    break;
            case 3: storymap3[selectedblockx][selectedblocky] = NOBLOCK;
                    break;
            case 4: storymap4[selectedblockx][selectedblocky] = NOBLOCK;
                    break;   
            case -1: return false; //something went wrong
                    break;
        }
            
        //successful block movement
        return true;
    }
    else //trying this in build mode
    {
        //not working yet
        return false;
    }
    
    //successful block movement
    return false;
}

/**************
* Purpose: return true if their character (or any other) is on selected block 
* Precondition: selectedblockx and selectedblocky are valid
* Postcondition: returns true if their character (or any other) is here
**************/
bool game::characterOnBlock()
{
    //they are standing on this block
    if (selectedblockx == x && selectedblocky == y)
        return true;

    //check to see if a NPC is standing there
    if (mode == STORYMODE)
    { 
        
    }
    
    //check to see if another player is standing there
    if (mode == BUILDMODE) 
    {
       
    }
    
   return false;     
}
