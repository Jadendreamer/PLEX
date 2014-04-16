/**************
* File Name: menu.cpp
* Author: G. J. Krafsig
* Date: July 3rd, 2007
* Purpose: implementation for game menus
**************/
#include "menu.h"

/**************
* Purpose: default constructor, initialize class values
* Precondition: none
* Postcondition: none
**************/
gamemenu::gamemenu()
{
    setScreen(LOADINGSCREEN); //loading the game images and data
}

/**************
* Purpose: loads the graphics for the game screens
* Precondition: width and height of the images
* Postcondition: returns true once all graphics are loaded
**************/
bool gamemenu::loadgraphics(int width, int height)
{
    //loading the game graphics
    loading = graphics->blitBigger(load_bitmap(LOADINGIMAGE, NULL), width/6, height/6, width, height);
    
    //starting a new game screen
    newload = graphics->blitBigger(load_bitmap(NEWGAMEIMAGE, NULL), width/6, height/6, width, height);
    
    //selecting the game mode
    gameplay = graphics->blitBigger(load_bitmap(GAMEMODEIMAGE, NULL), width/6, height/6, width, height);
    
    //pause = graphics->blitBigger(load_bitmap(PAUSEIMAGE, NULL), width/6, height/6, width, height);
    
    //store = graphics->blitBigger(load_bitmap(STOREIMAGE, NULL), width/6, height/6, width, height);
    
    loadgame = graphics->blitBigger(load_bitmap(LOADGAMEIMAGE, NULL), width/6, height/6, width, height);
    
    savegame = graphics->blitBigger(load_bitmap(SAVEGAMEIMAGE, NULL), width/6, height/6, width, height);
    
    build = load_bitmap(BUILDLOGINIMAGE, NULL);
    
    //the selector image
    select = load_bitmap(SELECTORIMAGE, NULL);
    
    //setup the selector
    selector.x = (width/3) + 50; //selector x position
    selector.y = (width/3) + 37; //selector y position
    selector.w = select->w; //selector width
    selector.h = select->h; //selector height 
    
    return true;
}

/**************
* Purpose: returns the current game screen
* Precondition: none
* Postcondition: current screen returned
**************/
int gamemenu::currentScreen()
{
   return screen; 
}

/**************
* Purpose: returns the current game screen
* Precondition: none
* Postcondition: current screen returned
**************/
bool gamemenu::setScreen(int num)
{
    screen = num;
    shown = false;
    selector.show = false;
    selector.display = true;
    
    //don't show the selector for loading screen
    if (num == 1)
        selector.display = false;
        
}

/**************
* Purpose: change the x position of the selector
* Precondition: amount to move selector
* Postcondition: selector positions changed, selector shown value updated
**************/
void gamemenu::setSelectorY(int amount)
{
    selector.y += amount;
    selector.show = false;
}

/**************
* Purpose: change the y position of the selector
* Precondition: amount to move selector
* Postcondition: selector positions changed, selector shown value updated
**************/
void gamemenu::setSelectorX(int amount)
{
    selector.x += amount;
    selector.show = false;   
}

/**************
* Purpose: returns the game selector image
* Precondition: selector image is open
* Postcondition: selector image returned
**************/
BITMAP *gamemenu::getSelector()
{
    return select;
}

/**************
* Purpose: returns a specific bitmap screen when requested, otherwise 
*          it returns the current game screen
* Precondition: number of the screen to return
* Postcondition: requested bitmap is returned or current screen bitmap is
*                returned if no specific bitmap was requested
**************/
BITMAP *gamemenu::getScreen(int num)
{

    if (num) //requesting a specific one
        switch (num)
        {
            case LOADINGSCREEN: return loading; //loading data and images
                break;
                
            case NEWGAMESCREEN: return newload; //loading a new game 
                break;
                
            case GAMEMODESCREEN: return gameplay; //selecting the gameplay mode
                break;
                
            case PAUSESCREEN: return pause; //showing the pause screen
                break;
                
            case STORESCREEN: return store; //showing the store screen
                break;
                
            case LOADGAMESCREEN: return loadgame; //loading a previous game screen
                break;
                
            case SAVEGAMESCREEN: return savegame; //saving a game screen
                break;
            
            case BUILDLOGINSCREEN: return build; //build login screen
                break;
                
            default: return NULL;
                break;   
        }
    else //return the screen currently being used
        switch (screen) 
        {
            case LOADINGSCREEN: return loading; //loading data and images
                break;
                
            case NEWGAMESCREEN: return newload; //loading a new game 
                break;
                
            case GAMEMODESCREEN: return gameplay; //selecting the gameplay mode
                break;
                
            case PAUSESCREEN: return pause; //showing the pause screen
                break;
                
            case STORESCREEN: return store; //showing the store screen
                break;
                
            case LOADGAMESCREEN: return loadgame; //loading a previous game screen
                break;
                
            case SAVEGAMESCREEN: return savegame; //saving a game screen
                break;
                
            case BUILDLOGINSCREEN: return build; //build login screen
                break;
                
            default: return NULL;
                break; 
        }
}

/**************
* Purpose: free up the memory allocated in this object
* Precondition: images already exist
* Postcondition: memory is released
**************/
void gamemenu::destorygraphics()
{
    destroy_bitmap(loading);
    destroy_bitmap(newload);
    destroy_bitmap(gameplay);
    //destroy_bitmap(pause);
    //destroy_bitmap(store);
    destroy_bitmap(loadgame);
    destroy_bitmap(savegame);
    destroy_bitmap(select);
    destroy_bitmap(build);
}
