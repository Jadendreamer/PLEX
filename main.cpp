/**************
*
*     P  L  E  X
*
* File Name: main.cpp
* Author: G. J. Krafsig
* Date: August 23rd, 2007
* Purpose: implementation of the game
**************/

/**************
*
*  MY WEEKLY GOALS
*
*  1) When a person tries to login they will be placed on the board where 
*     they last stopped unless
*      * some other character is currently in that spot
*      * that spot is no longer a valid spot for it to stand (water block or 
*        lower then boxed in by higher blocks)
*
*  2) They will be able to walk around the game board (game logic rules permitting)
*
*  3) They can select a block and move it to a new spot (game logic rules permitting)
*
*  4) They can select a pattern from the list of patterns they can create in a certain area
*
*  5) If they create a valid pattern, then they are awarded jewels on their account
*
*  6) They can buy blocks and items from the store with the jewels they have
*
*  7) They can block up blocks and obstacles if they have the  proper blocks or items
**************/

#include <stdio.h>
#include <process.h>
#include <allegro.h>
#include <winalleg.h>
#include "gameengine.h"

/**************
* Purpose: toggle the debugger:
*  1 turns it on
*  0 turns it off
**************/
#define DEBUG 1

/***************
*         !!!! IMPORTANT !!!!
* 
* DO NOT USE A ROOT LOGIN TO CONNECT
* TO AN ONLINE DATABASE. THIS IS FOR A 
* CONNECTION TO AN OFFLINE DATABASE FOR
* TESTING PURPOSES ONLY!
***************/
#define HOST "localhost"
#define USER "root"
#define PASS ""
#define DATABASE "plex"

/**************
* Purpose: Function prototypes
**************/
void init(); //allegro start
void deinit(); //allegro end
int checkLogin(char *name, char *pass); //login for build screen

/**************
* Purpose: Global Variables
**************/
char name[32]; //build login name
char pass[32]; //build login password
gameengine *plex; //game engine
BITMAP *buffer; //game doublebuffering
SAMPLE *theme;

/***********
* Purpose: check the login from the GUI login button
* Precondition: gameengine plex is declared
* Postcondition: 
        login valid: return control to the game engine & start the game
        otherwise: ask them to login again
***********/
int check_login_proc(int msg, DIALOG *d, int c)
{
    int ret;

    //call the parent object
    ret = d_button_proc(msg, d, c);

    //check the return value
    if (ret == D_EXIT)
    {
        //see if they gave the correct login
        checkLogin(name, pass);
        
        //login is incorrect
        if (!plex->getId())
        {
            alert("INCORRECT LOGIN", NULL, "Please try again...", "OK", NULL, 'y', NULL);   
            return D_REDRAW;
        }
        else //correct login
        {
            //change the game mode
            plex->setMode(BUILDMODE);
            
            //otherwise stop the dialogs
            return D_CLOSE;
        }
    }
    
    return ret;
}

/***********
* Purpose: launch the url for the create an account GUI button
* Precondition: dialog button
* Postcondition: open the browser to the specified url
***********/
int launch_url_proc1(int msg, DIALOG *d, int c)
{
      int ret;

      //call the parent object
      ret = d_button_proc(msg, d, c);

      //open window for the create account button
      if (ret == D_EXIT)
      {
        ShellExecute(NULL, "open", "rundll32", 
            "url.dll, FileProtocolHandler http://www.whiteoakstables.net/create", 
            "", SW_SHOWNOACTIVATE);
            
        return D_REDRAW;
     }

      //otherwise return the screen
      return ret;
}

/***********
* Purpose: launch the url for the lost password GUI button
* Precondition: dialog button
* Postcondition: open the browser to the specified url
***********/
int launch_url_proc2(int msg, DIALOG *d, int c)
{
      int ret;

      //call the parent object
      ret = d_button_proc(msg, d, c);

      //open window for the create account button
      if (ret == D_EXIT)
      {
        ShellExecute(NULL, "open", "rundll32", 
            "url.dll, FileProtocolHandler http://www.whiteoakstables.net/lost", 
            "", SW_SHOWNOACTIVATE);
            
        return D_REDRAW;
     }

      //otherwise return the screen
      return ret;
}

/***********
* Purpose: launch the url for the help GUI button
* Precondition: dialog button
* Postcondition: open the browser to the specified url
***********/
int launch_url_proc3(int msg, DIALOG *d, int c)
{
      int ret;

      //call the parent object
      ret = d_button_proc(msg, d, c);

      //open window for the create account button
      if (ret == D_EXIT)
      {
        ShellExecute(NULL, "open", "rundll32", 
            "url.dll, FileProtocolHandler http://www.whiteoakstables.net/help", 
            "", SW_SHOWNOACTIVATE);
            
        return D_REDRAW;
     }

      //otherwise return the screen
      return ret;
}

/***********
* Purpose: check to see if the login and password are found in the database
* Precondition: login button was pressed, plex & buffer already initilized
* Postcondition: checking to see if the login is valid
*   if valid: return 1, login correct
*   otherwise: return 0, login incorrect
***********/
int checkLogin(char *name, char *pass)
{
    //alert("Checking login...", NULL, NULL, "OK", NULL, 'y', NULL);
    
    //starting build mode, connect to the server
    if (name && pass && plex->connect(HOST, DATABASE, USER, PASS) == SUCCESS)
    {
        char query[500];
        sprintf(query, "SELECT id FROM members WHERE name='%s' AND pass='%s'", name, pass);
        
        plex->setId(plex->intQuery(query)); //query the database for the member id
        
    }
    else //connection error
    {
        alert("PLEX ERROR", NULL, "Database Connection Error", "OK", NULL, 'y', NULL);
        plex->exitEngine();
    }
    
    //connnection or login failed
    return 0; 
}

/***********
* Purpose: main game loop
* Precondition: plex game class declared, game variables all global
* Postcondition: game is over, memory used has been freed
***********/
int main()
{
    //initilize allegro
	init(); 
	
	//create the buffer and start the game engine
	buffer = create_bitmap(SCREEN_W, SCREEN_H);
    plex = new gameengine(buffer);
    
    //build login dialog
    DIALOG dlg[] =
    {   

    //    (proc)       (x)   (y)  (w)  (h) (fg) (bg) (key) (flags) (d1) (d2) (dp)  (dp2) (dp3)
       
    //login name textbox
    { d_box_proc,        380, 251, 160, 20, 0, 0xffffff, 0, D_EXIT,  0, NULL,        NULL, NULL, NULL },
    { d_edit_proc, (380 + 8), 258, 150, 50, 0, 16777215, 0,      0, 20,    0, (void*)name, NULL, NULL },
   
    //password textbox
    { d_box_proc,       380,  291, 160, 20, 0, 0xffffff, 0, D_EXIT,  0, 0,        NULL, NULL, NULL },
    { d_edit_proc, (380 + 8), 298, 150, 50, 0, 16777215, 0,      0, 20, 0, (void*)pass, NULL, NULL },
   
    //button to submit login
    { check_login_proc,  630, 255, 100, 50, 0, 0xffffff, 0, D_EXIT, NULL, NULL, (void*)"Go Play >>", NULL, NULL },
   
    //create an account
    { d_text_proc,       30, 240, 140, 20, 0,        -1, 0,      0,    0, NULL, (void*)"Not a member yet?", NULL, NULL },
    { launch_url_proc1,  26, 251, 140, 20, 0,  0xffffff, 0, D_EXIT, NULL, NULL, (void*)"Create An Account", NULL, NULL },
   
    //lost password
    { d_text_proc,       30, 295, 140, 20, 0,       -1, 0,      0, 0, NULL, (void*)"Incorrect login?", NULL, NULL },
    { launch_url_proc2,  26, 305, 140, 20, 0, 0xffffff, 0, D_EXIT, 0, NULL,     (void*)"Get Password", NULL, NULL },
   
    //help forum
    { d_text_proc,      40, 345, 140, 20, 0,       -1, 0,      0, 0, NULL, (void*)"Feeling lost?", NULL, NULL },
    { launch_url_proc3, 26, 355, 140, 20, 0, 0xffffff, 0, D_EXIT, 0, NULL,    (void*)"Help Forum", NULL, NULL },
   
    //always end the dialog with a null 
    { NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, NULL }};
    
    //load the game graphics
    while (!plex->loading())
        ;
        
    //main loop of the game
	while (!plex->gameOver())
    {
        //hide the mouse
        scare_mouse(); 
        
        //start the debugger if its on
        #ifdef DEBUG
            plex->debug(DEBUG);
        #endif
        
        //gameplay action
        plex->play(); 
		
		//remove flicker
		vsync(); 
		
		//lock the screen for drawing
		acquire_screen(); 
		
		//show the mouse if its on
		if (plex->getMouse()) 
		  show_mouse(screen);
		
		//draw buffer to the screen
		blit(plex->draw(), screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H); 
		
		//unlock the screen
		release_screen(); 
		
		//show the login gui if the game is in build mode
		if (plex->currentMenu() == BUILDLOGINSCREEN)
		  do_dialog(dlg, -1);
		  
		//show the mouse
		unscare_mouse(); 
	}

    //release all the game shared memory
    plex->exitEngine();
    
    //shutdown allegro
	deinit();
	
	//close the game
	return 0;
}
END_OF_MAIN()

/***********
* Purpose: setup allegro so its ready to use
* Precondition: none
* Postcondition: allegro is ready to go,
*       timer is setup, sound and keyboard and timer
*       are installed
***********/
void init()
{
	int depth, res;
	
	//initilize allegro
	allegro_init();
	
	//setup the color depth
	depth = desktop_color_depth();
	
	//no depth returned, default is 32
	if (!depth)
        depth = 32;
        
    //set the depth on allegro
	set_color_depth(depth);
	
	//setup the game resolution and window size
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0);

    //install the timer, keyboard, and mouse
	install_timer();
	install_keyboard();
	install_mouse();
	install_sound(DIGI_AUTODETECT, MIDI_NONE, NULL);
	
	//setup the GUI dialog colors
    gui_fg_color = makecol(255, 255, 255); //white text
    gui_mg_color = makecol(128, 128, 128); //grayed out dialog box
    gui_bg_color = makecol(102, 51, 51); //background color
}

/***********
* Purpose: free up any used memory
* Precondition: none
* Postcondition: memory used for the game have
*                been released
***********/
void deinit()
{
    //clear the keyboard buffer
	clear_keybuf();
}
