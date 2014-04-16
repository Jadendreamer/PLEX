/***8***********
* File Name: gameengine.cpp
* Author: G. J. Krafsig
* Date: July 3rd, 2007
* Purpose: implementation for game engine
**************/
#include "gameengine.h"

/**************
* Purpose: default constructor, initialize all the values for use
* Precondition: none
* Postcondition: none
**************/
gameengine::gameengine(BITMAP *gbuffer)
{
        //initilize the game engine object
        menu = new gamemenu();
        movie = new gamemovie();
        music = new gamemusic();
        graphics = new gamegraphics();
        db = new database();
        error = 0; 
        //time = new timer();
        
        //set the default game mode
        gamemode = CHARACTERMODE;
        
        //show the mouse
        mouse(true);
        
        //create the buffer
        buffer = gbuffer;
        clear(buffer);
}

/**************
* Purpose: load all the graphics, movie and music files
* Precondition: none
* Postcondition: all data has been loaded
**************/
bool gameengine::loading()
{
    //load the graphics for the menu screens
    if (!menu->loadgraphics(GAMEWIDTH, GAMEHEIGHT))
        error = 100; //menu graphics failed to load
    
    //load the graphics for the blocks
    
    //load the graphics for the characters
    
    //load the graphics for the backgrounds
    
    //load the graphics for movies
    
    //load the sounds for music
    
    return true;
}

/**************
* Purpose: return the buffer
* Precondition: buffer exists
* Postcondition: buffer returned
**************/
BITMAP *gameengine::draw()
{
    return buffer;
}

/**************
* Purpose: load all the music in the game
* Precondition: none
* Postcondition: music has been loaded
**************/
bool gameengine::loadmusic()
{
    //have the music class load all the music files
    //music->loadmusic();
    return true;   
}

/**************
* Purpose: load any video files in the game
* Precondition: none
* Postcondition: video has been loaded
**************/
bool gameengine::loadmovie()
{
    //have the movie class load all the video files
    //movie->loadmovie();
    return true;
}

/**************
* Purpose: respond to all game input
* Precondition: none
* Postcondition: game has responded accordingly
**************/
void gameengine::input()
{
    keyinput(); //respond to keyboard input
    mouseinput(); //respond to mouse input   
    
    exitError(); //exit if there was an error
}

/**************
* Purpose: respond to keyboard input
* Precondition: none
* Postcondition: game has responded to keyboard accordingly
**************/
void gameengine::keyinput()
{
    
    /**********
    * MENUS
    *
    * they are doing something on a menu screen
    **********/
    if (menu->currentScreen() != NOMENU)
    {
        //they are picking to start or load a new game
        //or they are picking the mode of their game
        if (menu->currentScreen() == NEWGAMESCREEN || menu->currentScreen() == GAMEMODESCREEN)
        {
            int moveamt = 55;
            
            //move the selector up if its not at the top
            if (key[KEY_UP] && menu->selector.y > (GAMEWIDTH/3) + 37)
            {
                blit(menu->getScreen(0), buffer, menu->selector.x, menu->selector.y, menu->selector.x, 
                    menu->selector.y, menu->selector.w, menu->selector.h);
                    
                menu->setSelectorY(-moveamt);
            }
            
            //move the selector down if its at the bottom   
            if (key[KEY_DOWN] && menu->selector.y < (GAMEWIDTH/3) + 37 + moveamt)
            {
                blit(menu->getScreen(0), buffer, menu->selector.x, menu->selector.y, menu->selector.x, 
                    menu->selector.y, menu->selector.w, menu->selector.h);
            
                menu->setSelectorY(moveamt);
            }
            
            //they hit enter to start a new game
            if (key[KEY_ENTER] && menu->selector.y == (GAMEWIDTH/3) + 37 && enterpressed == false)
            {
                if (menu->currentScreen() == NEWGAMESCREEN)
                    menu->setScreen(GAMEMODESCREEN); //show the new screen
                
                enterpressed = true;
            }   
            
            //they hit enter on the story mode
            if (key[KEY_ENTER] && menu->selector.y == (GAMEWIDTH/3) + 37 && enterpressed == false)
            {
                if (menu->currentScreen() == GAMEMODESCREEN)
                    menu->setScreen(0); //show the pick character screen, FIX THIS
                
                enterpressed = true;
            }  
            
            //they hit enter to load a game
            if (key[KEY_ENTER] && menu->selector.y == (GAMEWIDTH/3) + 37 + moveamt && enterpressed == false)
            {
                if (menu->currentScreen() == NEWGAMESCREEN)
                {
                    menu->setScreen(LOADGAMESCREEN); //show the new screen
                    menu->selector.display = false; //turn off the selector
                }
                
                enterpressed = true;
            }   
            
            //they hit enter on the build mode
            if (key[KEY_ENTER] && menu->selector.y == (GAMEWIDTH/3) - 18 && enterpressed == false)
            {
                if (menu->currentScreen() == GAMEMODESCREEN)
                    menu->setScreen(0); //show the pick character screen, FIX THIS
                
                enterpressed = true;
            }  
        } //end if they are picking a new game or a game mode screen
        
        //they are picking their character to play the game as
        
        //they are logging into build mode
        
        //they are loading a game saved to a file
        
        //they are buying things from the store
        
        //they are pausing the game
        
        //they are trying to save their game
        
    } //end picking a menu
    
    enterpressed = false;
    uppressed = false;
    downpressed = false;
    rightpressed = false;
    leftpressed = false;
}

/**************
* Purpose: respond to mouse input
* Precondition: none
* Postcondition: game has responded to mouse accordingly
**************/
void gameengine::mouseinput()
{
    /**********
    * MENUS
    *
    * they are doing something on a menu screen
    **********/
    if (menu->currentScreen() != NOMENU)
    {
        //they are picking to start or load a new game
        //or they are picking the mode of their game
        if (menu->currentScreen() == NEWGAMESCREEN || menu->currentScreen() == GAMEMODESCREEN)
        {
            int moveamt = 55;
            
            //move the selector up if mouse is up on new game
            if (mouse_x >= 343 && mouse_y >= 300 && mouse_y <= 321 && mouse_x <= 470
            && menu->selector.y > (GAMEWIDTH/3) + 37)
            {
                blit(menu->getScreen(0), buffer, menu->selector.x, menu->selector.y, menu->selector.x, 
                    menu->selector.y, menu->selector.w, menu->selector.h);
            
                menu->setSelectorY(-moveamt);
            }
                
            if (debugger) //show clickable area for right click below
                rect(buffer, 343, 300, 470, 321, makecol(255, 255, 255));
            
            //right clicked on start a new game
            if (mouse_x >= 343 && mouse_y >= 300 && mouse_y <= 321 && mouse_x <= 470 
            && (mouse_b & 1) && rightmousepressed == false)
            {
                menu->setScreen(GAMEMODESCREEN); //show the new screen
                rightmousepressed = true;
            }
            
            //move the selector down if mouse is down on load game
            if (mouse_x >= 343 && mouse_y >= 350 && mouse_y <= 380 && mouse_x <= 470 
            && menu->selector.y < (GAMEWIDTH/3) + 37 + moveamt)
            {
                blit(menu->getScreen(0), buffer, menu->selector.x, menu->selector.y, menu->selector.x, 
                    menu->selector.y, menu->selector.w, menu->selector.h);
                    
                menu->setSelectorY(moveamt);
            }
            
            if (debugger) //show clickable area for right click below
                rect(buffer, 343, 350, 470, 380, makecol(255, 255, 255));
                
            //right clicked to load a game   
            if (mouse_x >= 343 && mouse_y >= 350 && mouse_y <= 380 && mouse_x <= 470 
            && (mouse_b & 1) && rightmousepressed == false)
            {
                menu->setScreen(LOADGAMESCREEN); //show the new screen
                menu->selector.display = false; //turn off the selector
                leftmousepressed = true;
            }
            
        } //end if they are picking a new game or a game mode screen
        
        //they are picking their character to play the game as
        
        //they are loading a game saved to a file
        
        //they are in build mode
        
        
        //they are buying things from the store
        
        //they are pausing the game
        
        //they are trying to save their game
        
    } //end picking a menu
    
    rightmousepressed = false;
    leftmousepressed = false;
}

/**************
* Purpose: play the game, draw things to the buffer
* Precondition: none
* Postcondition: game is ready to be played
**************/	
void gameengine::play()
{
    /**********
    * INPUT
    *
    * respond to keyboard and mouse usage
    **********/
    
    input(); 
    
    /**********
    * MENUS
    *
    * menus should be on top of everything except the selector
    **********/
    
    //show a menu if one is set, only display it once
    if (menu->currentScreen() != NOMENU && !menu->shown)
    {
        blit(menu->getScreen(0), buffer, 0, 0, 0, 0, GAMEWIDTH, GAMEHEIGHT);
        menu->shown = true;
        
        /**********
        * TEXT FOR LOADING SCREEN
        *
        * only show while the game data is loading
        **********/
        
        if (menu->currentScreen() == LOADINGSCREEN)
            textout_ex(buffer, font, "Loading...", GAMEWIDTH/2 - 50, GAMEHEIGHT/2 + 120,
            makecol(255, 255, 255), -1);
        
    }
    
    /**********
    * SELECTOR
    * 
    * always draw the selector over the menu
    **********/
    
    //display the selector once until its moved
    if (menu->selector.display && !menu->selector.show)
    {            
        draw_sprite(buffer, menu->getSelector(), menu->selector.x, menu->selector.y);
        menu->selector.show = true;
    }
    
    /**********
    * DEBUGGING INFORMATION
    * 
    * last thing to show, wheee!
    **********/
    
    //display the selector once until its moved
    if (debugger)
    {
        textprintf_centre_ex(buffer, font, 65, 0, makecol(255, 255, 255), 0, "Selector Y: %d", menu->selector.y);
        textprintf_centre_ex(buffer, font, 65, 25, makecol(255, 255, 255), 0, "Mouse: %d, %d", mouse_x, mouse_y);
        //textprintf_centre_ex(buffer, font, 65, 25, makecol(255, 255, 255), 0, "Timer: %d", time->getTime());
    }
    
    exitError(); //exit if there was an error
        
}

/**************
* Purpose: exit the game if an error comes up
* Precondition: none
* Postcondition: the game displays an error message box then exits
*                instead of continuing on after fatal error is caught
**************/	
void gameengine::exitError()
{
    //some kind of error has occurred
    if (error)
    {
        char *message;
        
        switch(error)
        {
            case 100: message = "ERROR 100: could not load menu graphics";
                break;
            case 101: message = "ERROR 101: could not load";
                break;
                
            default: message = "ERROR: unspecified error";
                break;
        }
                
        //show the message in a popup box
        allegro_message(message);
        
        //deallocate used up space
        exitEngine();
        
        //exit allegro now
        exit(1);
        
    }
}

/**************
* Purpose: pause the game, player is away from the computer
* Precondition: none
* Postcondition: the game has stopped where they were, 
*                will resume once they return
**************/
bool gameengine::pause()
{
    
    return false;
}

/**************
* Purpose: resume the game from where it stopped, reset or restart 
*          appropriate values or variables if necessary
* Precondition: none
* Postcondition: the game is playing again
**************/
bool gameengine::resume()
{
    return false;   
}

/**************
* Purpose: reset the entire game back to the 
*          beginning to the new game screen
* Precondition: none
* Postcondition: the game is back at the beginning, variables are reset and 
*                ready for the game to start being played again
**************/
bool gameengine::reset()
{
    return false;
}

/**************
* Purpose: toggle the debug information
* Precondition: true turns it on, false turns it off
* Postcondition: the debug information is now on/off
**************/
void gameengine::debug(bool show)
{
    debugger = show;
}

/**************
* Purpose: returns the game's mode
* Precondition: none
* Postcondition: game mode returned
**************/
int gameengine::getMode()
{
    return gamemode;
}

/**************
* Purpose: they lost the game
* Precondition: none
* Postcondition: showing a game over screen
**************/
bool gameengine::gameover()
{
    return false;  
} 

/**************
* Purpose: they won the game
* Precondition: none
* Postcondition: showing a congratulations screen
**************/
bool gameengine::gamewon()
{
    return false;  
}
		
/**************
* Purpose: show the appropriate menu screen
* Precondition: none
* Postcondition: menu screen is on the buffer
**************/
BITMAP *gameengine::showmenu(int type)
{
        
    return NULL; 
}

/**************
* Purpose: show the selector at these coordinates
* Precondition: none
* Postcondition: the selector is on the buffer
**************/
BITMAP *gameengine::selector(int x, int y)
{
    
    return NULL;
    
}

/**************
* Purpose: they selected something on a menu
* Precondition: the menu they were on, the position of the selector
* Postcondition: respond to the menu selection
**************/
int gameengine::selected(int menu, int x, int y)
{
    return 0;  
} 
		
/**************
* Purpose: setup and play the appropriate movie
* Precondition: the movie to play
* Postcondition: the movie is being played
**************/
int gameengine::playmovie(int num)
{
    return 0;
}

/**************
* Purpose: pause the movie that is playing
* Precondition: the movie is already playing
* Postcondition: the movie has paused
**************/
bool gameengine::pausemovie()
{
    return false;
} 

/**************
* Purpose: resume the paused movie
* Precondition: movie is paused
* Postcondition: movie is playing again
**************/
bool gameengine::resumemovie()
{
    return false;
}

/**************
* Purpose: stop/skip the movie, they don't want to watch it
* Precondition: a movie is playing
* Postcondition: the screen/video after the current movie is not set to start
**************/
bool gameengine::stopmovie()
{
    return false;
} 
		
/**************
* Purpose: play the appropriate music
* Precondition: the number of the music to be played 
* Postcondition: the music is playing
**************/
int gameengine::playmusic(int num)
{
    return 0;
}

/**************
* Purpose: change the volume
* Precondition: postive or negative change
* Postcondition: volume is changed, volume is not below 0 or above max
**************/
int gameengine::volume(int change)
{
    return 0;
}

/**************
* Purpose: mute the sound
* Precondition: none
* Postcondition: volume is set to 0
**************/
bool gameengine::mute()
{
    return false;
} 

/**************
* Purpose: turn the volume back on
* Precondition: none
* Postcondition: volume is set to mid range
**************/
bool gameengine::unmute()
{
    return false;
}

/**************
* Purpose: stop whatever music is playing
* Precondition: the number of the music
* Postcondition: music has stopped
**************/
bool gameengine::stopmusic(int num)
{
    return false;
}
		
/**************
* Purpose: toggle the view of the mouse
* Precondition: true to show the mouse, false to not show it
* Postcondition: the mouse is on (true) or off (false) the screen
**************/
bool gameengine::mouse(bool show)
{
    mouseShow = show;
    return show;
}

/**************
* Purpose: return the view of the mouse
* Precondition: none
* Postcondition: returns the display of the mouse
**************/
bool gameengine::getMouse()
{
    return mouseShow;
}

/**************
* Purpose: clear the buffer screen
* Precondition: none
* Postcondition: the buffer has been cleared
**************/
bool gameengine::clearscreen()
{
    //clear the buffer
    clear(buffer);
    
    return 1;
} 
        
/**************
* Purpose: connect to the database
* Precondition: the host, database, user and pass
* Postcondition: the game has connected to the database
**************/
int gameengine::connect(char *host, char *db, char *user, char *pass)
{
    int errormsg = 0;
        
    db;
    return errormsg;
}

/**************
* Purpose: disconnect from the database
* Precondition: none
* Postcondition: connection is broken
**************/
bool gameengine::disconnect()
{
    return false;
}

/**************
* Purpose: query the database for a string result
* Precondition: the query
* Postcondition: the results of the query in string format
**************/
char *gameengine::stringquery()
{
    return NULL;
}

/**************
* Purpose: query the database for a integer result
* Precondition: the query
* Postcondition: the results of the query in int format
**************/
int gameengine::intquery()
{
    return 0;
}

/**************
* Purpose: destory all the graphics used in the game
* Precondition: none
* Postcondition: memory used by graphics have been released
**************/
bool gameengine::exitEngine()
{
    //deallocate all the menu images
    menu->destorygraphics();
    
    return 1;
}
