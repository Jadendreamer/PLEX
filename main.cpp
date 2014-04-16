/**************
*
*     P  L  E  X
*
* File Name: main.cpp
* Author: G. J. Krafsig
* Date: August 23rd, 2007
* Purpose: implementation of the game
**************/

#include <stdio.h>
#include <process.h>
#include <allegro.h>
#include <winalleg.h>
#include "gameengine.h"

//toggle the debugger
#define DEBUG 0

//allegro setup
void init(); //initilize allegro
void deinit(); //deinitilize allegro

//used for checking their login
int checkLogin(char *name, char *pass);
char name[32]; //used for the user login name
char pass[32]; //used for the user password
gameengine *plex;

/***********
* Purpose: check the login from the login button
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
      if (ret == D_EXIT) {
        
        if (checkLogin(name, pass))
            alert("Logging In", NULL, NULL, "OK", NULL, 'y', NULL);
        
        alert("INCORRECT LOGIN", NULL, "Please try again...", "OK", NULL, 'y', NULL);
         return D_REDRAW;
          
      }
      return ret;
}

/***********
* Purpose: launch the url for the create an account screen
* Precondition: dialog button for the create account
* Postcondition: open the browser to the specified url
***********/
int launch_url_proc1(int msg, DIALOG *d, int c)
{
      int ret;

      /* call the parent object */
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
* Purpose: launch the url for the lost password screen
* Precondition: dialog button for the lost password
* Postcondition: open the browser to the specified url
***********/
int launch_url_proc2(int msg, DIALOG *d, int c)
{
      int ret;

      /* call the parent object */
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
* Purpose: launch the url for the help screen
* Precondition: dialog button for the help page
* Postcondition: open the browser to the specified url
***********/
int launch_url_proc3(int msg, DIALOG *d, int c)
{
      int ret;

      /* call the parent object */
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
* Precondition: login button was pressed
* Postcondition: checking to see if the login is valid
*   if valid: return 1, login correct
*   otherwise: return 0, login incorrect
***********/
int checkLogin(char *name, char *pass)
{
    alert("Checking login...", NULL, NULL, "OK", NULL, 'y', NULL);
    return 0; 
}


/***********
* Purpose: main game loop
* Precondition: plex game class declared, game variables all global
* Postcondition: game is over, memory used has been freed
***********/
int main()
{
	init(); //initilize 
	
	BITMAP *buffer = create_bitmap(SCREEN_W, SCREEN_H);
    plex = new gameengine(buffer);
    
    DIALOG dlg[] =
{
   // (proc)      (x)  (y)  (w)  (h) (fg) (bg)      (key) (flags) (d1) (d2) (dp)                            (dp2) (dp3) 
   //login name textbox
   { d_box_proc,  380, 251, 160, 20,   0,  0xffffff,      0,      D_EXIT,  0,   NULL, NULL, NULL, NULL  },
   { d_edit_proc, (380 + 8), 258, 150, 50, 0,   16777215, 0,    0,      20,  0,   (void*)name, (void*)NULL, NULL },
   
   //password textbox
   { d_box_proc,  380, 291, 160, 20,   0,  0xffffff,    0,          D_EXIT,       0,   0,    NULL,                   NULL, NULL  },
   { d_edit_proc, (380 + 8), 298, 150, 50, 0,   16777215, 0,    0,      20,  0,   (void*)pass,                NULL, NULL },
   
   //button to submit login
   { check_login_proc,  630, 255, 100, 50,   0,  0xffffff,      0,      D_EXIT,  NULL,   NULL, (void*)"Go Play >>", NULL, NULL  },
   
   //create an account
   { d_text_proc,    30, 240, 140, 20,   0,  -1,      0,      0,  0,   NULL, (void*)"Not a member yet?", NULL, NULL  },
   { launch_url_proc1,  26, 251, 140, 20,   0,  0xffffff,      0,      D_EXIT,  NULL,  NULL, (void*)"Create An Account", NULL, NULL  },
   
   //lost password
   { d_text_proc,    30, 295, 140, 20,   0,  -1,      0,      0,  0,   NULL, (void*)"Incorrect login?", NULL, NULL  },
   { launch_url_proc2,  26, 305, 140, 20,   0,  0xffffff,      0,      D_EXIT,  0,   NULL, (void*)"Get Password", NULL, NULL  },
   
    //help forum
   { d_text_proc,    40, 345, 140, 20,   0,  -1,      0,      0,  0,   NULL, (void*)"Feeling lost?", NULL, NULL  },
   { launch_url_proc3,  26, 355, 140, 20,   0,  0xffffff,      0,      D_EXIT,  0,   NULL, (void*)"Help Forum", NULL, NULL  },
   
   //always end the dialog with a null 
   { NULL,        0,   0,   0,   0,  0,   0,        0,    0,      0,   0,   NULL,                           NULL, NULL }
};
    
    //load the game graphics
    while (!plex->loading())
        ;
        
    //main loop of the game
	while (!plex->gameover())
    {
        scare_mouse(); //hide the mouse
        
        //start the debugger if its on
        #ifdef DEBUG
            plex->debug(DEBUG);
        #endif
        
        plex->play(); //gameplay action
		
		vsync(); //remove flicker
		
		acquire_screen(); //lock the screen for drawing
		
		if (plex->getMouse())
		  show_mouse(screen); //show the mouse
		
		blit(plex->draw(), screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H); //draw buffer to the screen
		
		release_screen(); //unlock the screen
		
		if (plex->currentMenu() == BUILDLOGINSCREEN)
		  do_dialog(dlg, -1);
		  
		
		unscare_mouse(); //show the mouse
	}

    //release all the game shared memory
    plex->exitEngine();
    
    //shutdown allegro
	deinit();
	
	//close the application
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
    //initilize allegro
	int depth, res;
	
	allegro_init();
	depth = desktop_color_depth();
	
	if (!depth)
        depth = 32;
        
	set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0);

	install_timer();
	install_keyboard();
	install_mouse();
	
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
