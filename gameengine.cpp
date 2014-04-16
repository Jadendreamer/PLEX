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
    scrolling = false; //not scrolling the screen
    scrollmax = 0; //scrolling increment value
    id = 0; //database member id
    
    //set the mouse block selector defaults
    mousex = 0;
    mousey = 0;
        
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
    
    //rest(5000);
    
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
    //get rid of freezing problem
    Sleep(3);
    
    //short and so sweet
    return buffer;
}

/**************
* Purpose: respond to all game input
* Precondition: none
* Postcondition: game has responded accordingly
**************/
void gameengine::input()
{
    if (!scrolling) //not scrolling the screen
    {               //so taking input is okay

        keyInput(); //respond to keyboard input
        mouseInput(); //respond to mouse input 
        
        if (logic->getMode() == STORYMODE || logic->getMode() == BUILDMODE)
            caluclateMouseBlock(); //figure out where mouse is to display the selector
    }
    
    exitError(); //exit if there was an error
}

/**************
* Purpose: respond to keyboard input
* Precondition: none
* Postcondition: game has responded to keyboard accordingly
**************/
void gameengine::keyInput()
{
    //used for checking bounds
    int max = 10;
       
    /**********
    * QUITTING THE GAME
    *
    * they are hitting the ESC key
    **********/
    if (key[KEY_ESC])
    {
        if (quit())
        {
            //deallocate used space
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
        
    if (key[KEY_F2] && !F2Pressed)
    {
        music->sound = !music->sound;
        
        //turn music off if its playing
        if (!music->sound)
            music->stop();
        else
            music->playing = false;
            
        F2Pressed = true;
    }
    
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
                {
                    setMode(STORYMODE);
                    music->playing = false;
                }
                    
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
    
    /**********
    * BUILD MODE OR STORY MODE
    *
    * they are playing in build mode
    **********/
    if (logic->getMode() == BUILDMODE || logic->getMode() == STORYMODE)
    {
        
        if (key[KEY_UP] && !upPressed) //moving up
        {
            if (logic->x > 0)
            {
                        
                //increment position of the character        
                if (logic->validMove(-1, 0)) 
                    logic->x--;
                else //play error sound
                    music->play(ERRORMOVE, 255, 128, 1000, 0); 
  
            } //end within entire map bounds
            
            upPressed = true;
            
        } //end up key pressed
        
        if (key[KEY_DOWN] && !downPressed) //moving down
        {
            //if (logic->getMode() == STORYMODE)
            //    max = SMAP_HEIGHT;
            //else
            //    max = BMAP_HEIGHT;
                
            if (logic->x < max)
            {
      
                //increment position of the character
                if (logic->validMove(1, 0))
                    logic->x++;                
                else //play error sound
                    music->play(ERRORMOVE, 255, 128, 1000, 0);
                    
            } //end within entire map bounds
            
            downPressed = true; 
             
        } //end down key pressed
        
        
        if (key[KEY_LEFT] && !leftPressed) //moving left
        {
            if (logic->y > 0)
            {
                
                //increment position of the character
                if (logic->validMove(0, -1))
                    logic->y--;
                else //play error sound
                    music->play(ERRORMOVE, 255, 128, 1000, 0);
                
            } //end within entire map bounds
            
            leftPressed = true;  
            
        } //end left key pressed
        
        if (key[KEY_RIGHT] && !rightPressed) //moving right
        {
            //if (logic->getMode() == STORYMODE)
            //    max = SMAP_WIDTH;
            //else
            //    max = BMAP_WIDTH;
                
            if (logic->y < max)
            {
                //increment position of the character
                if (logic->validMove(0, 1))
                    logic->y++;
                else //play error sound
                    music->play(ERRORMOVE, 255, 128, 1000, 0);
                    
            } //end within entire map bounds
            
            rightPressed = true; 
             
        } //end right key pressed
        
    } //end in build mode
    
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
        
    if (!key[KEY_F2])
        F2Pressed = false;
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
                {
                    setMode(STORYMODE);
                    music->playing = false;
                }
                    
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
        
        //they are buying things from the store
        
        //they are pausing the game
        
        //they are trying to save their game
        
    } //end picking a menu
    
    /**********
    * BUILD MODE
    *
    * they are playing in build mode
    **********/
    if (logic->getMode() == BUILDMODE || logic->getMode() == STORYMODE)
    {
        //textprintf_ex(buffer, font, 200, 200, makecol(255, 255, 255), 0, "Clicked");
            
        // left click
        if ((mouse_b & 1) && lmPressed == false)
        {
            
            /**********************
            * UNIMPLEMENTED FEATURE
            *
            * they are clicking on a character standing on a block
            * this shouldn't do anything at the moment
            * later on this might be used for trading or chatting
            * with whatever character is standing here
            **********************/
            //clickCharacter(mouse_x, mouse_y);
    
            //they are clicking on a block on the board
            //they can't click on the block a character is standing on
            clickBlock(mouse_x, mouse_y);
            
            /* && !characterOnBlock(logic->selectedblockx, logic->selectedblocky))
            {
                //do whatever with the block  
            }
                
            //they want to open the store menu
            if (clickStore())
            {
                //open the store menu
            }
                
            //they want to open the save game menu
            if (clickSaveStar())
            {
                //open the save menu
            }*/
                
            lmPressed = true;
                
        } //end mouse left click
            
    } //end in build mode
    
    //toggle mouse press states
    if (!mouse_b & 2)
        rmPressed = false;
    
    if (!mouse_b & 1)
        lmPressed = false;
}

/**************
* Purpose: show the selector on the screen
* Precondition: mouse x and y coordinates have been calculated (mousex, mousey)
* Postcondition: selector is drawn on the screen
**************/
void gameengine::drawSelector()
{
    int depthoffset = 0;
    int blockx, blocky;
    
    //figure out where they are based on position in the entire map
    blockx = mousex;
    blocky = mousey;
    
    if (logic->x > 5)
        blockx += logic->x;
        
    if (logic->y > 5)
        blocky += logic->y;       
    
    //figure out the depth to draw the selector based on blocks being there
    if (logic->getBlock(blockx, blocky, 0) == NOBLOCK)
        depthoffset = 43;
     
    //draw the selector
    blit(graphics->selectimg, buffer, 0, 0, (mousey * BLOCKWIDTH)+BOARDOFFSETX+10, 
        (mousex * BLOCKHEIGHT)+BOARDOFFSETY-(BLOCKHEIGHT)+depthoffset, BLOCKWIDTH, BLOCKHEIGHT);
}

/**************
* Purpose: calculate the x and y position of the block the mouse is on
* Precondition: none
* Postcondition: mousex holds block x position, mousey holds block y position
**************/
void gameengine::caluclateMouseBlock()
{
      //selecting a block in bounds
    int newx, newy, xoffset, yoffset, x, y;
    mousex = 0; mousey = 0;
    x = mouse_x;
    y = mouse_y;
    xoffset = BLOCKWIDTH;
    yoffset = BLOCKHEIGHT;
    
    for (int i = y-BOARDOFFSETY-20; i > 0; i-= yoffset)
        mousex++;
    
    for (int i = x-BOARDOFFSETX-BLOCKWIDTH; i > 0; i-= xoffset)
        mousey++;
}

/**************
* Purpose: play the game, draw things to the buffer
* Precondition: none
* Postcondition: game is ready to be played
**************/	
void gameengine::play()
{
    
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
            sprintf(query, "SELECT characterid FROM members WHERE id='%d'", id);
            logic->character = intQuery(query);
            
            //position them on the board
            sprintf(query, "SELECT x FROM members WHERE id='%d'", id);
            logic->x = intQuery(query);
            
            sprintf(query, "SELECT y FROM members WHERE id='%d'", id);
            logic->y = intQuery(query);
            
            sprintf(query, "SELECT depth FROM members WHERE id='%d'", id);
            logic->depth = intQuery(query);
            
            //load the online game board AROUND their current position
            sprintf(query, "SELECT * FROM board WHERE x >=%d-%d AND x <= %d+%d AND y >=%d-%d AND y <= %d+%d", 
                    logic->x, DRAWBOARDMAXOFFSET, logic->x, DRAWBOARDMAXOFFSET, 
                    logic->y, DRAWBOARDMAXOFFSET, logic->y, DRAWBOARDMAXOFFSET);
            logic->loadBuildBoard(db->query(query));
            
            //position their character in a free space
            //otherwise set them at one that is open for them
            logic->checkForFreeSpace(logic->x, logic->y, depth);
            
            //update their position in the database
            sprintf(query, "UPDATE members SET x='%d', y='%d', depth='%d' WHERE id='%d'", 
                    logic->x, logic->y, logic->depth, id);
            db->updateQuery(query);
            
            //update the local x and y values (remember that they're flipped)
            // = logic->y % 6;
            //localy = logic->x % 5;
            
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
            buildBoard();
            
            //draw their character above the store picture
            drawCharacter(logic->character, 50, 150, SCALEDOWN);
            
            int depthoffset;
            
            drawCharacter(logic->character, (logic->y * BLOCKWIDTH)+BOARDOFFSETX, 
                    (logic->x * BLOCKHEIGHT)+BOARDOFFSETY-(BLOCKHEIGHT*2), 1);
            
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
            textprintf_ex(buffer, font, 45, 68, 0, -1, "%d", logic->yellow);
            textprintf_ex(buffer, font, 45, 98, 0, -1, "%d", logic->blue);
            textprintf_ex(buffer, font, 45, 128, 0, -1, "%d", logic->green);
            
            //draw the info on how many blocks, dynamite, and shovels they have
            textprintf_ex(buffer, font, 70, 68, 0, -1, "Ramps: %d", -1);
            textprintf_ex(buffer, font, 70, 88, 0, -1, "Blocks: %d", -1);
            textprintf_ex(buffer, font, 70, 108, 0, -1, "Bombs: %d", -1);
            textprintf_ex(buffer, font, 70, 128, 0, -1, "Shovels: %d", -1);            
            
            //draw their character's health hearts around them
            
            //draw the game board for the first time
            
            //draw the other online characters on the board  
            
        }
        
    }
    
    //FIX THIS!!!!!!!!!!!!! check to see which map they're on
    if (logic->currentMap == -1)
    {
        logic->currentMap = MERCYVALLEY;
        
        //load the board into the game
        bool waserror;
        waserror = logic->parseMapFile("maps/alex_landslide.plex");
         
        if (!waserror)
            error = 100;
        
    }
    
    /**********
    * STORY MODE
    *
    * they are in story mode, show the appropriate screens
    **********/
    if (logic->getMode() == STORYMODE)
    {
        //setup character's position on the board
        localx = logic->x;
        localy = logic->y;
        
        if (menu->currentScreen() != NOMENU)
        {
            menu->setScreen(NOMENU);
            menu->selector.display = false;
            logic->character = ALEX; //set character to ALEX by default
        }
        
        //load the build background screen
        blit(graphics->bgimg, buffer, 0, 0, 0, 0, GAMEWIDTH, GAMEHEIGHT);
               
        //draw the board for the first time
        buildBoard();
            
        //draw their character above the store picture
        drawCharacter(logic->character, 50, 150, SCALEDOWN);
        
        //character's position on the SCREEN versus his position on the game window
        localx = localx % 6;
        localy = localy % 6;
        
        int depthoffset;
        
        switch(logic->depth)
        {
            case 0: depthoffset = 0;
                    break;
            case 1: depthoffset = 30;
                    break;    
        }
        
        drawSelector(); //show the selector there
         
        //draw the character on the screen   
        drawCharacter(logic->character, (localy * BLOCKWIDTH)+BOARDOFFSETX+10, 
                (localx * BLOCKHEIGHT)+BOARDOFFSETY-(BLOCKHEIGHT*2)+depthoffset, 1);
         
        //check to see if they are standing by a tall block
        blockOver();
            
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
        textprintf_ex(buffer, font, 45, 68, 0, -1, "%d", logic->yellow);
        textprintf_ex(buffer, font, 45, 98, 0, -1, "%d", logic->blue);
        textprintf_ex(buffer, font, 45, 128, 0, -1, "%d", logic->green);
            
        //draw the info on how many blocks, dynamite, and shovels they have
        textprintf_ex(buffer, font, 70, 68, 0, -1, "Ramps: %d", -1);
        textprintf_ex(buffer, font, 70, 88, 0, -1, "Blocks: %d", -1);
        textprintf_ex(buffer, font, 70, 108, 0, -1, "Bombs: %d", -1);
        textprintf_ex(buffer, font, 70, 128, 0, -1, "Shovels: %d", -1);            
            
        //draw their character's health hearts around them
            
        //draw the other online characters on the board
        
    }
    
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
    * MUSIC CONTROL
    *
    * figure this out once everything has been drawn to the screen
    ***********/
    if (!music->playing)
    {
        music->stop();
        
        //not on a map yet
        if (logic->getMode() != STORYMODE && logic->getMode() != BUILDMODE)
        {
            music->play(THEME, 255, 128, 1000, 1);
            music->playing = true;
        }
        
        if (logic->getMode() == STORYMODE)
        {
            //switch depending on their current location
            if (logic->currentMap == WATERVILLE)
            {
                music->play(WATERVILLE, 255, 128, 1000, 1);
                music->playing = true;
            }
                
            if (logic->currentMap == ASHCANYON)
                music->play(ASHCANYON, 255, 128, 1000, 1);
                
            if (logic->currentMap == LANDSLIDE)
                music->play(LANDSLIDE, 255, 128, 1000, 1);
                
            if (logic->currentMap == HAYMARKET)
                music->play(HAYMARKET, 255, 128, 1000, 1);
                
            if (logic->currentMap == BOULDERCANYON)
                music->play(BOULDERCANYON, 255, 128, 1000, 1);
                
            if (logic->currentMap == BUILDERSGUILD)
                music->play(BUILDERSGUILD, 255, 128, 1000, 1);
            
            if (logic->currentMap == STONECASTLE)
                music->play(STONECASTLE, 255, 128, 1000, 1);
            
            if (logic->currentMap == FUZZYLAND)
                music->play(FUZZYLAND, 255, 128, 1000, 1);
            
            if (logic->currentMap == MERRYFIELD)
                music->play(MERRYFIELD, 255, 128, 1000, 1);
                
            if (logic->currentMap == MERCYVALLEY)
                music->play(MERCYVALLEY, 255, 128, 1000, 1);
                
            if (logic->currentMap == WISHINGWELLFALLS)
                music->play(WISHINGWELLFALLS, 255, 128, 1000, 1);
              
        }
        
        music->playing = true;
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
        int over = 620; //how far over they should be offset
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
            textprintf_ex(buffer, font, over, down*multi++, makecol(255, 255, 255), 0, "Character: %d", logic->character);
            textprintf_ex(buffer, font, over, down*multi++, makecol(255, 255, 255), 0, "X: %d", logic->x);
            textprintf_ex(buffer, font, over, down*multi++, makecol(255, 255, 255), 0, "Y: %d", logic->y);
            textprintf_ex(buffer, font, over, down*multi++, makecol(255, 255, 255), 0, "Depth: %d", logic->depth);
            
            textprintf_ex(buffer, font, over, down*multi++, makecol(255, 255, 255), 0, "Local X: %d", localx);
            textprintf_ex(buffer, font, over, down*multi++, makecol(255, 255, 255), 0, "Local Y %d", localy);
                     
            //textprintf_ex(buffer, font, over, down*multi++, makecol(255, 255, 255), 0, "Scrolling: %d", scrolling);
        }
        
        if (logic->getMode() == STORYMODE)
        {
            textprintf_ex(buffer, font, over, down*multi++, makecol(255, 255, 255), 0, "0,0,0: %d", logic->getBlock(0, 0, 0));
            textprintf_ex(buffer, font, over, down*multi++, makecol(255, 255, 255), 0, "X: %d", logic->x);
            textprintf_ex(buffer, font, over, down*multi++, makecol(255, 255, 255), 0, "Y: %d", logic->y);
            textprintf_ex(buffer, font, over, down*multi++, makecol(255, 255, 255), 0, "Z: %d", logic->depth);                
            textprintf_ex(buffer, font, over, down*multi++, makecol(255, 255, 255), 0, "Mousex: %d", mousex);
            textprintf_ex(buffer, font, over, down*multi++, makecol(255, 255, 255), 0, "Mousey: %d", mousey);
            textprintf_ex(buffer, font, over, down*multi++, makecol(255, 255, 255), 0, "Block x: %d", logic->selectedblockx);
            textprintf_ex(buffer, font, over, down*multi++, makecol(255, 255, 255), 0, "Block y: %d", logic->selectedblocky);
        }
        
    }//end debugger is on
    
    //exit if there was an error
    exitError(); 
        
}

/**************
* Purpose: figure out which block they are clicking on with the mouse
* Precondition: the mouse x and y position when they clicked 
* Postcondition: changes logic->selectedblockx and logic->selectedblocky
*                to reflect the block they were clicking on
*                if they clicked outside of the game board, then both x and y
*                are set to NOBLOCK and returns false; otherwise returns true
**************/
bool gameengine::clickBlock(int x, int y)
{
    
    //selecting a block in bounds
    int newx, newy, xoffset, yoffset;
    newx = newy = 0;
    xoffset = BLOCKWIDTH;
    yoffset = BLOCKHEIGHT;
    
    for (int i = y-BOARDOFFSETY-20; i > 0; i-= yoffset)
        newx++;
    
    for (int i = x-BOARDOFFSETX-BLOCKWIDTH; i > 0; i-= xoffset)
        newy++;
        
    //selecting a block out of bounds
    if (x < BOARDOFFSETX || y < BOARDOFFSETY-BLOCKHEIGHT) //not on the block board
    {
        logic->selectedblockx = logic->selectedblocky = NOBLOCK;  
        return false;
    } 
    
    //block they're trying to move to is outside of first frame on the screen
    if (logic->selectedblockx > 5)
        newx += logic->x;
            
    if (logic->selectedblocky > 5)
        newy += logic->y;
        
    //placing a selected block
    if (logic->selectedblockx != NOBLOCK && logic->selectedblocky != NOBLOCK)
    {
        bool success;
        
        //try to move the block
        success = logic->placeBlock(newx, newy); 
        
        if (success) //play moveblock sound
            music->play(BLOCKFALL, 255, 128, 1000, 0);
        else //play error sound
            music->play(ERRORMOVE, 255, 128, 1000, 0);
            
        logic->selectedblockx = NOBLOCK;
        logic->selectedblocky = NOBLOCK;
        
        return true;
    }
    
    //selecting a block to move
    logic->selectedblockx = newx;
    logic->selectedblocky = newy;
    
    //block they're trying to select is outside of the first frame
    if (logic->x > 5)
        logic->selectedblockx += logic->x;
        
    if (logic->y > 5)
        logic->selectedblocky += logic->y;
    
    return true;

}



/**************
* Purpose: draw a block over the character if there is a tall block in front
*          of where they are currently standing
* Precondition: character has already been drawn to the board
* Postcondition: appropriate block is drawn to the buffer on top of 
*                the blited over the character
**************/
void gameengine::blockOver()
{
    int depthamt = 0;
    bool redraw = false;
    
    switch(logic->depth)
    {
        case 0: depthamt = 0;
            break;
        case 1: depthamt = 44;
            break;
        case 2: depthamt = 90;
            break;
        case 3: depthamt = 49;
            break;  
    }
    
        //draw the blocks below on top of the character
        //then draw the one underneat that
        // if the one underneath that is tall too, then draw the next one as wel          
            if (logic->tallBlock(logic->x+1, logic->y, logic->depth))
            {
                BITMAP* temp;
                temp = create_bitmap(BLOCKWIDTH, BLOCKHEIGHT + 5);
                clear(temp);
                
                blit(graphics->getBlock(logic->getBlock(logic->x+2, logic->y, logic->depth)), temp, 0, 0, 0, 0, BLOCKWIDTH, BLOCKHEIGHT+5);
                draw_sprite(buffer, graphics->getBlock(logic->getBlock(logic->x+1, logic->y, logic->depth)), (BLOCKWIDTH * localy)+BOARDOFFSETX+10, (BLOCKHEIGHT * localx+1)+BOARDOFFSETY-49 + depthamt);
                draw_sprite(buffer, temp, (BLOCKWIDTH * localy)+BOARDOFFSETX+10, (BLOCKHEIGHT * localx+2)+BOARDOFFSETY+35+depthamt);
           
                destroy_bitmap(temp);
            } 
            
            //check to see if they have a block on the depth above covering them up          
            if ((logic->depth != 0 && logic->getBlock(logic->x+1, logic->y, logic->depth-1) != NOBLOCK))
            {
                BITMAP* temp;
                temp = create_bitmap(BLOCKWIDTH, BLOCKHEIGHT + 5);
                clear(temp);
                
                //check if there is a block on the level above that needs to blit over
                if (logic->getBlock(logic->x+2, logic->y, logic->depth-1) != NOBLOCK)
                    blit(graphics->getBlock(logic->getBlock(logic->x+2, logic->y, logic->depth-1)), temp, 0, 0, 0, 0, BLOCKWIDTH, BLOCKHEIGHT+5);
                
                //check if there is a tall block on the level below
                else if (logic->getBlock(logic->x+2, logic->y, logic->depth) != NOBLOCK)
                    blit(graphics->getBlock(logic->getBlock(logic->x+2, logic->y, logic->depth)), temp, 0, 0, 0, 0, BLOCKWIDTH, BLOCKHEIGHT+5);
                
                //draw block below the character over the character  
                draw_sprite(buffer, graphics->getBlock(logic->getBlock(logic->x+1, logic->y, logic->depth-1)), (BLOCKWIDTH * localy)+BOARDOFFSETX+10, (BLOCKHEIGHT * localx+1)+BOARDOFFSETY-depthamt-5);
                
                //there is a block on the level above the character after the block drawn over them
                if (logic->getBlock(logic->x+2, logic->y, logic->depth-1) != NOBLOCK)
                    draw_sprite(buffer, temp, (BLOCKWIDTH * localy)+BOARDOFFSETX+10, (BLOCKHEIGHT * localx+2)+BOARDOFFSETY+depthamt-9);
                
                //there is a block on the same level as the character under the block drawn over them
                else if (logic->getBlock(logic->x+2, logic->y, logic->depth) != NOBLOCK)
                    draw_sprite(buffer, temp, (BLOCKWIDTH * localy)+BOARDOFFSETX+10, (BLOCKHEIGHT * localx+2)+BOARDOFFSETY+35+depthamt);
           
                destroy_bitmap(temp);
            } 
            
            //block selector is behind a taller block
            if ((logic->getBlock(mousex+1, mousey, 0) != NOBLOCK))  
            {
                BITMAP* temp;
                temp = create_bitmap(BLOCKWIDTH, BLOCKHEIGHT + 5);
                clear(temp);
                depthamt = 44;
                
                //check if there is a block on the level above that needs to blit over
                if (logic->getBlock(mousex+2, mousey, 1) != NOBLOCK)
                    blit(graphics->getBlock(logic->getBlock(mousex+2, mousey, 1)), temp, 0, 0, 0, 0, BLOCKWIDTH, BLOCKHEIGHT+5);
                
                //check if there is a tall block on the level below
                else if (logic->getBlock(mousex+2, mousey, 0) != NOBLOCK)
                    blit(graphics->getBlock(logic->getBlock(mousex+2, mousey, 0)), temp, 0, 0, 0, 0, BLOCKWIDTH, BLOCKHEIGHT+5);
                  
                //draw block below the character over the character  
                draw_sprite(buffer, graphics->getBlock(logic->getBlock(mousex+1, mousey, 0)), (BLOCKWIDTH * mousey)+BOARDOFFSETX+10, (BLOCKHEIGHT * mousex+1)+BOARDOFFSETY-depthamt-5);
                
                /*///there is a block on the level above the character after the block drawn over them
                if (logic->getBlock(mousex+2, mousey, 1) != NOBLOCK)
                    draw_sprite(buffer, temp, (BLOCKWIDTH * mousey)+BOARDOFFSETX+10, (BLOCKHEIGHT+mousex+2)+BOARDOFFSETY+depthamt-9);
                
                //there is a block on the same level as the character under the block drawn over them
                else if (logic->getBlock(mousex+2, mousey, 0) != NOBLOCK)
                    draw_sprite(buffer, temp, (BLOCKWIDTH * mousey)+BOARDOFFSETX+10, (BLOCKHEIGHT * mousex+2)+BOARDOFFSETY+35+depthamt);
           
                */
                destroy_bitmap(temp);
            }  
        
} 

/**************
* Purpose: draw the board and the character as it moves around
*          get more block info from the database if it goes outside
*          of its current bounds
* Precondition: none
* Postcondition: board is drawn to the buffer with character sitting
*                on top of the board
**************/
void gameengine::buildBoard()
{
    if (logic->mode == BUILDMODE)
        ; //check to see if we need to load different data from the database 
        
    //draw the board for the first time
    drawBuildBoard(logic->x, logic->y);
 
}

/**************
* Purpose: draw the build board to the buffer and position the character at the
*          correct depth
* Precondition: x and y position of the character so we known how much
                of the board to show at any time
* Postcondition: board is drawn to the buffer
**************/	
void gameengine::drawBuildBoard(int xpos, int ypos)
{
    int x, y, LOW;
    x = y = 0;
    
    //modify the board so it only shows 6 x 6 blocks at a time
    if (xpos % 6 != 0)
        xpos -= (xpos % 6);
        
    if (ypos % 6 != 0)
        ypos -= (ypos % 6);  
       
    //draw the blocks on the screen
    for (int i = xpos; i < xpos+DRAWBOARDMAXOFFSET; i++)
    {
        for (int j = ypos; j < ypos+DRAWBOARDMAXOFFSET+1; j++)
        {
            
            /*if (logic->getBlock(i, j, 4) != NOBLOCK) //BOTTOM BLOCKS (draw these first)
                draw_sprite(buffer, graphics->getBlock(logic->getBlock(i, j, 4)), (BLOCKWIDTH * j)+BOARDOFFSETX, (BLOCKHEIGHT * i)+BOARDOFFSETY-180);
            
            if (logic->getBlock(i, j, 3) != NOBLOCK) 
                draw_sprite(buffer, graphics->getBlock(logic->getBlock(i, j, 3)), (BLOCKWIDTH * y)+BOARDOFFSETY, (BLOCKHEIGHT * x)+BOARDOFFSETX);
            
            if (logic->getBlock(i, j, 2)!= NOBLOCK)
                draw_sprite(buffer, graphics->getBlock(logic->getBlock(i, j, 2)), (BLOCKWIDTH * y)+BOARDOFFSETX+10, (BLOCKHEIGHT * x)+BOARDOFFSETY-45);
            */
             
            if (logic->getBlock(i, j, 1)!= NOBLOCK)
                draw_sprite(buffer, graphics->getBlock(logic->getBlock(i, j, 1)), (BLOCKWIDTH * y)+BOARDOFFSETX+10, (BLOCKHEIGHT * x)+BOARDOFFSETY-89); 

              
            if (logic->getBlock(i, j, 0)!= NOBLOCK) //TOP BLOCKS (draw these last)
                draw_sprite(buffer, graphics->getBlock(logic->getBlock(i, j, 0)), (BLOCKWIDTH * y)+BOARDOFFSETX+10, (BLOCKHEIGHT * x)+BOARDOFFSETY-133);
            
            y++; 
            
        }
        
        y = 0; //reset y value so blocks wrap around
        x++;
    }
    
}

/**************
* Purpose: draw the given character to the buffer
* Precondition: correct character id, x and y position, width and height of image
* Postcondition: the character is drawn to the buffer
**************/	
void gameengine::drawCharacter(int id, int x, int y, float scale)
{        
    switch(id)
    {
        
        case ALEX: 
            stretch_sprite(buffer, graphics->aleximg, x, y, 
                floor(graphics->aleximg->w/scale), floor(graphics->aleximg->h/scale));
                break;
                
        case KITTY: 
            stretch_sprite(buffer, graphics->kittyimg, x, y, 
                floor(graphics->kittyimg->w/scale), floor(graphics->kittyimg->h/scale));
                break;
                
        case BELLA: 
            stretch_sprite(buffer, graphics->bellaimg, x, y, 
                floor(graphics->bellaimg->w/scale), floor(graphics->bellaimg->h/scale));
                break;
                
        case RAVEN: 
            stretch_sprite(buffer, graphics->ravenimg, x, y, 
                floor(graphics->ravenimg->w/scale), floor(graphics->ravenimg->h/scale));
                break;
                
        case TANYA: 
            stretch_sprite(buffer, graphics->tanyaimg, x, y, 
                floor(graphics->tanyaimg->w/scale), floor(graphics->tanyaimg->h/scale));
                break;
                
        case LISA: 
            stretch_sprite(buffer, graphics->lisaimg, x, y, 
                floor(graphics->lisaimg->w/scale), floor(graphics->lisaimg->h/scale));
                break;
        
    }    
}

/**************
* Purpose: move the board on the screen
* Precondition: none
* Postcondition: board has been moved
**************/	
void gameengine::scrollBoard()
{
    
    if (logic->getMode() == BUILDMODE)
    {
        char query[500];
        
        //they've walked off the edge of the visible board
        if ((logic->x != 0 && logic->y != 0) && (logic->x % DRAWBOARDMAXOFFSET == 0 || logic->y % (DRAWBOARDMAXOFFSET-1) == 0))
        {
            //load more data from the database
            sprintf(query, "SELECT * FROM board WHERE x >=%d-%d AND x <= %d+%d AND y >=%d-%d AND y <= %d+%d", 
                        logic->x, DRAWBOARDMAXOFFSET, logic->x, DRAWBOARDMAXOFFSET, 
                        logic->y, DRAWBOARDMAXOFFSET, logic->y, DRAWBOARDMAXOFFSET);
            
            //put that data into the game array            
            logic->loadBuildBoard(db->query(query));
            
            //turn on the scrolling feature
            scrolling = true;
            
        }
          
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
            case 100: message = "ERROR 100: gameengine:loading() could not load menu graphics";
                break;
            case 101: message = "ERROR 101: database:connect() could not connect to database";
                break;
            case 102: message = "ERROR 102: game::loadGame() could not load a game";
                break;
            case 103: message = "ERROR 103: game::loadGame() could not load saved game file";
                break;
            case 104: message = "ERROR 104: game::loadGame() could not load a player file";
                break;
            case 105: message = "ERROR 105: game::loadGame() could not load a map file";
                break;
            case 106: message = "ERROR 106: game::loadGame() could not load a npc file";
                break;
            case 107: message = "ERROR 107: map::setMapFilename() no map selected";
                break;
            case 108: message = "ERROR 108: map::setMapFile() no filename";
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
    music->destroyMusic();
    
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
