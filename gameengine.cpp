/**************
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
    logic = new game();
    db = new database();
    error = 0; 
    //time = new timer();
    
    //setup variables
    dbConnection = false; //no connection to database
    debugger = false; //debugger defaults to off
    mouseShow = true; //mouse is turned on
    error = 0; //no error messages
    id = 0; //database member id
        
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
    if (!menu->loadGraphics(GAMEWIDTH, GAMEHEIGHT))
        error = 100; //menu graphics failed to load
    
    //load the graphics for the game
    graphics->loadGraphics();
    
    //load the graphics for movies
    movie->loadMovies();
    
    //load the sounds for music
    music->loadMusic();
    
    //done loading, show the initial menu
    menu->setScreen(NEWGAMESCREEN);    

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
* Purpose: respond to all game input
* Precondition: none
* Postcondition: game has responded accordingly
**************/
void gameengine::input()
{
    keyInput(); //respond to keyboard input
    mouseInput(); //respond to mouse input   
    
    exitError(); //exit if there was an error
}

/**************
* Purpose: respond to keyboard input
* Precondition: none
* Postcondition: game has responded to keyboard accordingly
**************/
void gameengine::keyInput()
{
    
    /**********
    * QUITTING THE GAME
    *
    * they are hitting the ESC key
    **********/
    if (key[KEY_ESC])
    {
        if (quit())
        {
            //deallocate used up space
            exitEngine();
        
            //exit allegro now
            exit(1);
        }
    }
    
    /**********
    * TOGGLE THE DEBUGGER
    *
    * they are hitting the ESC key
    **********/
    if (key[KEY_F6])
        debug(!debugger);
    
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
            
            //hit enter key on top part of startup menus
            if (key[KEY_ENTER] && menu->selector.y == (GAMEWIDTH/3) + 37 && enterPressed == false)
            {
                
                //hit enter on story mode
                //!!this must be above the other one or it shows when the screen is swapped!!  
                if (menu->currentScreen() == GAMEMODESCREEN)
                    //menu->setScreen(NOMENU); //show the pick character screen
                    alert("PLEX", NULL, "unimplemented feature", "&Ok", NULL, 'y', NULL);
                    
                //hit enter on start a new game
                if (menu->currentScreen() == NEWGAMESCREEN)
                    menu->setScreen(GAMEMODESCREEN); //show the new screen
                    
                enterPressed = true;
            }   
            
            //hit enter key on the bottom startup menu
            if (key[KEY_ENTER] && menu->selector.y == (GAMEWIDTH/3) + 37 + moveamt && enterPressed == false)
            {
                //hit enter on the build mode
                //!!this must be above the other one or it shows when the screen is swapped!! 
                if (menu->currentScreen() == GAMEMODESCREEN)
                    menu->setScreen(BUILDLOGINSCREEN); //show the pick character screen, FIX THIS
                    
                //they hit enter to load a game
                if (menu->currentScreen() == NEWGAMESCREEN)
                    menu->setScreen(LOADGAMESCREEN); //show the new screen
                
                menu->selector.display = false; //turn off the selector 
                enterPressed = true;
            }   
             
        } //end if they are picking a new game or a game mode screen
        
        //they are picking their character to play the game as
        
        //they are logging into build mode
        
        //they are loading a game saved to a file
        
        //they are buying things from the store
        
        //they are pausing the game
        
        //they are trying to save their game
        
    } //end picking a menu
    
    //toggle keypress states
    if (!key[KEY_ENTER])
        enterPressed = false;
    
    if (!key[KEY_UP])
        upPressed = false;
    
    if (!key[KEY_DOWN])
        downPressed = false;
        
    if (!key[KEY_RIGHT])
        rightPressed = false;
        
    if (!key[KEY_LEFT])
        leftPressed = false;
}

/**************
* Purpose: respond to mouse input
* Precondition: none
* Postcondition: game has responded to mouse accordingly
**************/
void gameengine::mouseInput()
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
                //blit the current screen as you move the selector
                blit(menu->getScreen(0), buffer, menu->selector.x, menu->selector.y, menu->selector.x, 
                    menu->selector.y, menu->selector.w, menu->selector.h);
            
                menu->setSelectorY(-moveamt);
            }
            
            //move the selector down if mouse is down on load game
            if (mouse_x >= 343 && mouse_y >= 350 && mouse_y <= 380 && mouse_x <= 470 
            && menu->selector.y < (GAMEWIDTH/3) + 37 + moveamt)
            {
                //blit the current screen as you move the selector
                blit(menu->getScreen(0), buffer, menu->selector.x, menu->selector.y, menu->selector.x, 
                    menu->selector.y, menu->selector.w, menu->selector.h);
                    
                menu->setSelectorY(moveamt);
            }
                
            if (debugger) //show clickable area for left click below
                rect(buffer, 343, 300, 470, 321, makecol(255, 255, 255));
            
            //top part of startup menus
            if (mouse_x >= 343 && mouse_y >= 300 && mouse_y <= 321 && mouse_x <= 470 
            && (mouse_b & 1) && lmPressed == false)
            {
                
                //clicked on story mode
                if (menu->currentScreen() == GAMEMODESCREEN)
                    alert("PLEX", NULL, "unimplemented feature", "&Ok", NULL, 'y', NULL);
                    
                //clicked on start a new game
                if (menu->currentScreen() == NEWGAMESCREEN)
                    menu->setScreen(GAMEMODESCREEN); 
                
                lmPressed = true;
            }
            
            if (debugger) //show clickable area for left click below
                rect(buffer, 343, 350, 470, 380, makecol(255, 255, 255));
                
            //bottom part of startup menus
            if (mouse_x >= 343 && mouse_y >= 350 && mouse_y <= 380 && mouse_x <= 470 
            && (mouse_b & 1) && lmPressed == false)
            {
                //right clicked to build mode 
                if (menu->currentScreen() == GAMEMODESCREEN)
                    menu->setScreen(BUILDLOGINSCREEN);
                    
                //right clicked to load a game
                if (menu->currentScreen() == NEWGAMESCREEN)
                    menu->setScreen(LOADGAMESCREEN); //show the new screen
            
                menu->selector.display = false; //turn off the selector
                lmPressed = true;
            }
            
        } //end if they are picking a new game or a game mode screen
        
        //they are picking their character to play the game as
        
        //they are loading a game saved to a file
        
        //they are in build mode
        
        //they are buying things from the store
        
        //they are pausing the game
        
        //they are trying to save their game
        
    } //end picking a menu
    
    //toggle mouse press states
    if (!mouse_b & 2)
        rmPressed = false;
    
    if (!mouse_b & 1)
        lmPressed = false;
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
    * BUILD MODE
    *
    * they are in build mode, show the appropriate screens
    **********/
    
    //show a menu if one is set, only display it once
    if (logic->getMode() == BUILDMODE)
    {
        //remove the build login screen, they've logged in okay
        if (menu->currentScreen() != NOMENU)
        {
            menu->setScreen(NOMENU);
            menu->selector.display = false;
            
            //load database information into the game object
            int x, y, depth;
            char query[500];
            x = y = depth = 0;            
            
            //set their member name
            sprintf(query, "SELECT name FROM members WHERE id='%d'", id);
            logic->name = stringQuery(query);
            
            //set their character 
            sprintf(query, "SELECT character FROM members WHERE id='%d'", id);
            logic->character = intQuery(query);
            
            //position them on the board
            sprintf(query, "SELECT x FROM members WHERE id='%d'", id);
            x = intQuery(query);
            
            sprintf(query, "SELECT y FROM members WHERE id='%d'", id);
            y = intQuery(query);
            
            sprintf(query, "SELECT depth FROM members WHERE id='%d'", id);
            depth = intQuery(query);
            
            //load the online game board AROUND their current position
            
            sprintf(query, "SELECT * FROM board WHERE x >=%d-6 AND x <= %d+6 AND y >=%d-6 AND y <= %d+6", 
                    x, x, y, y);
            logic->loadBuildBoard(db->query(query));
            
            //position their character in a free space
            //otherwise set them at one that is open for them
            logic->checkForFreeSpace(x, y, depth);
            
            //update their position in the database
            sprintf(query, "UPDATE members SET x='%d', y='%d', depth='%d' WHERE id='%d'", 
                    logic->x, logic->y, logic->depth, id);
            db->updateQuery(query);
            
            //load their game money
            sprintf(query, "SELECT yellow FROM members WHERE id='%d'", id);
            logic->yellow = intQuery(query);
            
            sprintf(query, "SELECT blue FROM members WHERE id='%d'", id);
            logic->blue = intQuery(query);
            
            sprintf(query, "SELECT green FROM members WHERE id='%d'", id);
            logic->green = intQuery(query);            
        
            //load the build background screen
            blit(graphics->bgimg, buffer, 0, 0, 0, 0, GAMEWIDTH, GAMEHEIGHT);
            
            //draw the board for the first time
            drawBuildBoard(logic->x, logic->y);
            
            //draw their character above the store picture
            drawCharacter(id, 50, 150);
            
            //draw the store on the screen
            draw_sprite(buffer, graphics->storeimg, 10, 285);
            
            //draw the text box on the bottom
            draw_sprite(buffer, graphics->talkboximg, 5, 410);
            
            //draw the list of gems at the top of the screen
            stretch_sprite(buffer, graphics->yellowjewelimg, 15, 45, 
                graphics->yellowjewelimg->w/4, graphics->yellowjewelimg->h/4);
                
            stretch_sprite(buffer, graphics->bluejewelimg, 15, 75, 
                graphics->bluejewelimg->w/4, graphics->bluejewelimg->h/4);
                
            stretch_sprite(buffer, graphics->greenjewelimg, 15, 105, 
                graphics->greenjewelimg->w/4, graphics->greenjewelimg->h/4);
            
            //write how many gems they have
            
            //draw the info on how many blocks, dynamite, and shovels they have
            
            //draw their character's health hearts around them
            
            //draw the game board for the first time
            
            //draw the other online characters on the board  
            
        }
    }
    
    /**********
    * STORY MODE
    *
    * they are in story mode, show the appropriate screens
    **********/
    if (logic->getMode() == STORYMODE)
    {
        
    }
    
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
        int down = 15; //how much to move new debugger lines down
        int over = 650; //how far over they should be offset
        int multi = 1; //a way to nicely format them so they don't run each
                       //other over and look nasty
        
        //debugger title information
        textprintf_ex(buffer, font, over, 2, makecol(255, 255, 255), 0, " PLEX DEBUGGER");
        
        //show selector information
        if (menu->selector.display == true)
            textprintf_ex(buffer, font, over, down*multi++, makecol(255, 255, 255), 0, "Selector Y: %d", menu->selector.y);

        //show mouse information
        if (getMouse())
            textprintf_ex(buffer, font, over, down*multi++, makecol(255, 255, 255), 0, "Mouse: %d, %d", mouse_x, mouse_y);
        
        //show the menu information
        if (menu->currentScreen())
            textprintf_ex(buffer, font, over, down*multi++, makecol(255, 255, 255), 0, "Menu: %d", menu->currentScreen());
            
        //show the game mode
        if (logic->getMode() == STORYMODE)
            textprintf_ex(buffer, font, over, down*multi++, makecol(255, 255, 255), 0, "Game Mode: Story");
        
        //show the game mode    
        if (logic->getMode() == BUILDMODE)
            textprintf_ex(buffer, font, over, down*multi++, makecol(255, 255, 255), 0, "Game Mode: Build");
            
        //connected to the database
        if (dbConnection)  
            textprintf_ex(buffer, font, over, down*multi++, makecol(255, 255, 255), 0, "Database Result: %d", logic->id);
            
        //logged into build mode
        if (logic->getMode() == BUILDMODE)  
        {
            //textprintf_ex(buffer, font, over, down*multi++, makecol(255, 255, 255), 0, "Free Space: %d", (logic->checkForFreeSpace(logic->x, logic->y, logic->depth)));
            textprintf_ex(buffer, font, over, down*multi++, makecol(255, 255, 255), 0, "X: %d", logic->x);
            textprintf_ex(buffer, font, over, down*multi++, makecol(255, 255, 255), 0, "Y: %d", logic->y);
            textprintf_ex(buffer, font, over, down*multi++, makecol(255, 255, 255), 0, "Depth: %d", logic->depth);
        }
        
    }//end debugger is on
    
    //exit if there was an error
    exitError(); 
        
}

/**************
* Purpose: draw the build board to the buffer
* Precondition: x and y position of the character so we known how much
                of the board to show at any time
* Postcondition: board is drawn to the buffer
**************/	
void gameengine::drawBuildBoard(int xpos, int ypos)
{
    int x, y, maxx, maxy;
    x = 180;
    y = 170;
    
    if (xpos - 3 <= 0)
        maxx = 4;
    else
        maxx = 4;
    
    for (int i = xpos-3; i < xpos+maxx; i++)
        for (int j = ypos-3; j < ypos+6; j++)
        {
            
            if (logic->getBlock(i, j, 0)!= NOBLOCK)
                draw_sprite(buffer, graphics->getBlock(logic->getBlock(i, j, 0)), (BLOCKWIDTH * j)+x, (BLOCKHEIGHT * i)+y);
            
            if (logic->getBlock(i, j, 1)!= NOBLOCK)
                draw_sprite(buffer, graphics->getBlock(logic->getBlock(i, j, 1)), (BLOCKWIDTH * j)+x, (BLOCKHEIGHT * i)+y-45);
            
            if (logic->getBlock(i, j, 2)!= NOBLOCK)
                draw_sprite(buffer, graphics->getBlock(logic->getBlock(i, j, 2)), (BLOCKWIDTH * j)+x, (BLOCKHEIGHT * i)+y-90);
                
            if (logic->getBlock(i, j, 3)!= NOBLOCK)
                draw_sprite(buffer, graphics->getBlock(logic->getBlock(i, j, 3)), (BLOCKWIDTH * j)+x, (BLOCKHEIGHT * i)+y-133);
                
            //if (logic->getBlock(i, j, 4)!= NOBLOCK)
            //    draw_sprite(buffer, graphics->getBlock(logic->getBlock(i, j, 4)), (BLOCKWIDTH * j)+x, (BLOCKHEIGHT * i)+y-180);

        }
    
}

/**************
* Purpose: draw the given character to the buffer
* Precondition: correct character id, x and y position, width and height of image
* Postcondition: the character is drawn to the buffer
**************/	
void gameengine::drawCharacter(int id, int x, int y)
{        
    switch(id)
    {
        
        case ALEX: 
            stretch_sprite(buffer, graphics->aleximg, x, y, 
                floor(graphics->aleximg->w/1.68), floor(graphics->aleximg->h/1.68));
                break;
                
        case KITTY: 
            stretch_sprite(buffer, graphics->kittyimg, x, y, 
                floor(graphics->kittyimg->w/1.68), floor(graphics->kittyimg->h/1.68));
                break;
                
        case BELLA: 
            stretch_sprite(buffer, graphics->bellaimg, x, y, 
                floor(graphics->bellaimg->w/1.68), floor(graphics->bellaimg->h/1.68));
                break;
                
        case RAVEN: 
            stretch_sprite(buffer, graphics->ravenimg, x, y, 
                floor(graphics->ravenimg->w/1.68), floor(graphics->ravenimg->h/1.68));
                break;
                
        case TANYA: 
            stretch_sprite(buffer, graphics->tanyaimg, x, y, 
                floor(graphics->tanyaimg->w/1.68), floor(graphics->tanyaimg->h/1.68));
                break;
                
        case LISA: 
            stretch_sprite(buffer, graphics->lisaimg, x, y, 
                floor(graphics->lisaimg->w/1.68), floor(graphics->lisaimg->h/1.68));
                break;
        
    }    
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
    if (error != 0)
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
    return logic->getMode();
}

/**************
* Purpose: sets the game's mode
* Precondition: the game mode
* Postcondition: mode has been set
**************/
void gameengine::setMode(int newmode)
{
    logic->setMode(newmode);
}

/**************
* Purpose: they lost the game
* Precondition: none
* Postcondition: showing a game over screen
**************/
bool gameengine::gameOver()
{
    return false;  
} 

/**************
* Purpose: they won the game
* Precondition: none
* Postcondition: showing a congratulations screen
**************/
bool gameengine::gameWon()
{
    return false;  
}
		
/**************
* Purpose: returns the current menu the game is using
* Precondition: none
* Postcondition: menu id (NOT BITMAP) returned
**************/
int gameengine::currentMenu()
{
   return menu->currentScreen();
}   
		
/**************
* Purpose: setup and play the appropriate movie
* Precondition: the movie to play
* Postcondition: the movie is being played
**************/
int gameengine::playMovie(int num)
{
    return 0;
}

/**************
* Purpose: pause the movie that is playing
* Precondition: the movie is already playing
* Postcondition: the movie has paused
**************/
bool gameengine::pauseMovie()
{
    return false;
} 

/**************
* Purpose: resume the paused movie
* Precondition: movie is paused
* Postcondition: movie is playing again
**************/
bool gameengine::resumeMovie()
{
    return false;
}

/**************
* Purpose: stop/skip the movie, they don't want to watch it
* Precondition: a movie is playing
* Postcondition: the screen/video after the current movie is not set to start
**************/
bool gameengine::stopMovie()
{
    return false;
} 
		
/**************
* Purpose: play the appropriate music
* Precondition: the number of the music to be played 
* Postcondition: the music is playing
**************/
int gameengine::playMusic(int num)
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
bool gameengine::stopMusic(int num)
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
bool gameengine::clearScreen()
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
int gameengine::connect(char *host, char *table, char *user, char *pass)
{
    int errormsg = 0; //catch any database errors
    dbConnection = true; //connection started, toggle flag
    
    //connect to the database
    errormsg = db->openConnection(host, table, user, pass);
        
    //return the database message
    return errormsg;
}

/**************
* Purpose: disconnect from the database
* Precondition: none
* Postcondition: connection is broken
**************/
bool gameengine::disconnect()
{
    dbConnection = false;
    return false;
}

/**************
* Purpose: set the database member id
* Precondition: id to set it to
* Postcondition: member id has been set
**************/
void gameengine::setId(int newid)
{
    id = newid; 
    
    //set this member as being online now
    if (id && dbConnection)
    {    
        char query[500]; //query string  
        logic->id = id;
        sprintf(query, "UPDATE members SET online='1' WHERE id='%d'", id);
        db->updateQuery(query);
    }
}

/**************
* Purpose: return the database member id
* Precondition: none
* Postcondition: member id returned, or 0 if none
**************/
int gameengine::getId()
{
    return id;   
}

/**************
* Purpose: query the database for a string result
* Precondition: the query
* Postcondition: the results of the query in string format
**************/
char *gameengine::stringQuery(char *query)
{
    return NULL;
}

/**************
* Purpose: query the database for a integer result
* Precondition: the query
* Postcondition: the results of the query in int format
**************/
int gameengine::intQuery(char *query)
{    
    return db->intQuery(query);
}

/**************
* Purpose: destory all the graphics used in the game
* Precondition: none
* Postcondition: memory used by graphics have been released
**************/
bool gameengine::exitEngine()
{
    //shutdown the db info if it exists
    if (dbConnection)
    {
        char query[500]; //query string
        
        //player is logging out
        sprintf(query, "UPDATE members SET online='0' WHERE id='%d'", id);
        db->updateQuery(query);
        
        disconnect();
    }
        
    //deallocate all the menu images
    menu->destoryGraphics();
    
    return 1;
}

/**************
* Purpose: open a browser window to the specified url
* Precondition: the url to open
* Postcondition: window has been opened
**************/
int gameengine::openWindow(char *url)
{
    char call[250];
    sprintf(call, "url.dll, FileProtocolHandler %s", url);
    ShellExecute(NULL, "open", "rundll32", call, "", SW_SHOWNOACTIVATE);
    return 0;
}

/**************
* Purpose: ask the user if they want to exit the game
* Precondition: none
* Postcondition: memory used by graphics have been released
**************/
int gameengine::quit(void)
{
   if (alert("PLEX", NULL, "Are you sure you want to quit?", "&Yes", "&No", 'y', 'n') == 1)
   {
      return 1;
   }
   else
      return 0;
}

