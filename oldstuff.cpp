#ifdef OLDSTUFF
/*

// IGNORE ALL OF THIS STUFF
// functions for testing game logic

bool loadgraphics();
void draw();
void drawmap();
void input();
void introcollision();
void debug();
void gameplay();
BITMAP *blitBigger(BITMAP *image, int x, int y);

//game variables
bool showlevelone = true;
bool showleveltwo = true;
bool showlevelthree = true;
bool showlevelfour = true;
bool showlevelfive = true;
bool intro = true;
bool newgame = false;
bool loadgame = false;
int errormsg;

//game graphics
BITMAP *buffer;
BITMAP *introduction[2];
BITMAP *introselector;
BITMAP *blocks[10];
BITMAP *background;
game *plex = new game();

//game sprites
SPRITE introscreen;
SPRITE selector;
SPRITE map;
SPRITE bg;
*/

/***********
* Purpose: show info about the game for debugging
* Precondition: none
* Postcondition: none
***********/
/*
void debug()
{
    textprintf_centre_ex(buffer, font, 50, 0, makecol(255, 255, 255), 0, "New Game: %d", newgame);
    textprintf_centre_ex(buffer, font, 50, 25, makecol(255, 255, 255), 0, "Load Game: %d", loadgame);
    textprintf_centre_ex(buffer, font, 50, 50, makecol(255, 255, 255), 0, "Game Mode: %d", plex->getmode());
    textprintf_centre_ex(buffer, font, 50, 75, makecol(255, 255, 255), 0, "Display: %d", map.display);
    textprintf_centre_ex(buffer, font, 50, 100, makecol(255, 255, 255), 0, "Showing: %d", map.show);
}
*/

/***********
* Purpose: check for user mouse and key input
* Precondition: none
* Postcondition: game responds to input
***********/
/*
void input()
{
    if (key[KEY_F1])
		showlevelone = !showlevelone;
		  
	if (key[KEY_F2])
		showleveltwo = !showleveltwo;
		  
	if (key[KEY_F3])
		showlevelthree = !showlevelthree;
		  
	if (key[KEY_F4])
		showlevelfour = !showlevelfour;
		  
	if (key[KEY_SPACE])
	{
	   plex->addblock();
	   //pressed = true;
    }
        
    if (key[KEY_ENTER])
    {
        if (intro)
        {
            if (!newgame) //haven't selected to start a new game
                if (selector.y == 400)
                {
                    newgame = true;
                    //rest(150);
                }
                else
                    loadgame = true;
            else //start the game
            {
                //set the game mode
                if (selector.y == 400)
                    plex->setmode(STORYMODE);
                else
                    plex->setmode(BUILDMODE);
                
                //turn off the intro screen
                intro = false;
                
                //turn off the selector
                selector.display = false;
                
                //show the game background
                bg.display = true;
                bg.show = true;
                
                //show the map    
                map.display = true;
                map.show = true;
            }
        }    
    }
        ;//pressed = false;
        
    if (key[KEY_UP])
    {
        if (intro)
        {
            if (newgame)
                blit(introduction[1], buffer, selector.x, selector.y, selector.x, selector.y, selector.w, selector.h);
            else
                blit(introduction[0], buffer, selector.x, selector.y, selector.x, selector.y, selector.w, selector.h);
            
            selector.y = 400;
            selector.show = true;
        }
    }
    
    if (key[KEY_DOWN])
    {
        if (intro)
        {
            if (newgame)
                blit(introduction[1], buffer, selector.x, selector.y, selector.x, selector.y, selector.w, selector.h);
            else
                blit(introduction[0], buffer, selector.x, selector.y, selector.x, selector.y, selector.w, selector.h);
            
            selector.y = 457;
            selector.show = true;
        }
    }
    
    //check to see if they clicked on new game or load game
    if (intro)
        introcollision(); 
}
*/

/***********
* Purpose: key & mouse detection during the introduction
* Precondition: intro screen is showing
* Postcondition: selected to start a new game or load a game
*               gameplay mode has been set if its a new game
***********/
/*
void introcollision()
{
    int newgamey = 400;    
    int loadgamey = 457;
    
    //they are selecting to start a new game or load a game
    if (!newgame)
    {
        if ((mouse_x >= 460 && mouse_x <= 575) &&
            (mouse_y >= newgamey && mouse_y <= newgamey + 25) && (mouse_b & 1))
        {
                newgame = true;
                selector.y = newgamey;
                //rest(150);
        } 
        if ((mouse_x >= 460 && mouse_x <= 575) &&
            (mouse_y >= loadgamey && mouse_y <= loadgamey + 25) && (mouse_b & 1))
                loadgame = true;
    }
    else //they are selecting a play mode
    {
        introscreen.show = true;
        
        if ((mouse_x >= 460 && mouse_x <= 575) &&
            (mouse_y >= newgamey && mouse_y <= newgamey + 25) && (mouse_b & 1))
        {
                plex->setmode(STORYMODE);
                
                //turn off the intro screen
                intro = false;
                
                //turn off the selector
                selector.display = false;
                
                //show the game background
                bg.display = true;
                bg.show = true;
                
                //show the map    
                map.display = true;
                map.show = true;
        }
                
        if ((mouse_x >= 460 && mouse_x <= 575) &&
            (mouse_y >= loadgamey && mouse_y <= loadgamey + 25) && (mouse_b & 1))
        {
                plex->setmode(BUILDMODE);
                
                //turn off the intro screen
                intro = false;
                
                //turn off the selector
                selector.display = false;
                
                //show the game background
                bg.display = true;
                bg.show = true;
                
                //show the map    
                map.display = true;
                map.show = true;
                
        }
    }
}
*/

/***********
* Purpose: draw game stuff to the screen
* Precondition: none
* Postcondition: appropriate things drawn to the screen
***********/
/*
void draw()
{
    if (bg.display && bg.show)
        blit(background, buffer, 0, 0, bg.x, bg.y, background->w, background->h);    
        
    if (map.display && map.show)
    {
        drawmap();
        map.show = false;
    }

    if (introscreen.display && introscreen.show && newgame)
    {
        blit(introduction[1], buffer, 0, 0, introscreen.x, introscreen.y, introduction[1]->w, introduction[1]->h);
        introscreen.show = false;
        selector.show = true;
    }
            
    if (introscreen.display && introscreen.show && !newgame)
    {
        blit(introduction[0], buffer, 0, 0, introscreen.x, introscreen.y, introduction[0]->w, introduction[0]->h);
        introscreen.show = false;
    }
    
    if (selector.display && selector.show)
    {
        draw_sprite(buffer, introselector, selector.x, selector.y);
        selector.show = false;
    }
            
}
*/

/***********
* Purpose: draw the map to the screen
* Precondition: none
* Postcondition: map is on the screen
***********/
/*
void drawmap()
{

    //draw all the blocks on the first level
    for (int i = 0; i < MAP_HEIGHT; i++)
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            
            if(showlevelone) 
                if (plex->getblock(i, j, 0) != NOBLOCK)
                    draw_sprite(buffer, blocks[plex->getblock(i, j, 0)], (BLOCKWIDTH * j)+map.x, (BLOCKHEIGHT * i)+map.y);
            
            if (showleveltwo)    
                if (plex->getblock(i, j, 1) != NOBLOCK)
                    draw_sprite(buffer, blocks[plex->getblock(i, j, 1)], (BLOCKWIDTH * j)+map.x, (BLOCKHEIGHT * i)+map.y-45);
            
            if (showlevelthree)    
                if (plex->getblock(i, j, 2) != NOBLOCK)
                    draw_sprite(buffer, blocks[plex->getblock(i, j, 2)], (BLOCKWIDTH * j)+map.x, (BLOCKHEIGHT * i)+map.y-90);
                    
            if (showlevelfour)  
                if (plex->getblock(i, j, 3) != NOBLOCK)
                    draw_sprite(buffer, blocks[plex->getblock(i, j, 3)], (BLOCKWIDTH * j)+map.x, (BLOCKHEIGHT * i)+map.y-135);

            if (showlevelfive)  
                if (plex->getblock(i, j, 4) != NOBLOCK)
                    draw_sprite(buffer, blocks[plex->getblock(i, j, 4)], (BLOCKWIDTH * j)+map.x, (BLOCKHEIGHT * i)+map.y-180);
        }
}
*/

/***********
* Purpose: draw an image to the buffer and then copy the result
* Precondition: image to use, x and y position of the image
* Postcondition: image is now at the position of the old buffer image
***********/
/*
BITMAP *blitBigger(BITMAP *image, int x, int y)
{
    //clear the buffer
    clear(buffer);
    blit(image, buffer, 0, 0, x, y, image->w, image->h);
    
    //now copy the buffer image back into the intro image (to make the smaller image centered in the screen
    //for blitting later)
    image = create_bitmap(SCREEN_W, SCREEN_H);
    blit(buffer, image, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    
    clear(buffer);    
    return image;
}
*/

/***********
* Purpose: load all of the game graphics
* Precondition: all graphics already defined
* Postcondition: buffer is created, graphics are loaded
***********/
/*
bool loadgraphics()
{
    //create the buffer
    buffer = create_bitmap(SCREEN_W, SCREEN_H);
    clear(buffer);
    
    //use to load files
    char name[20];
    
    //load the game blocks
    for (int i = 0; i < 10; i++)
    {
        sprintf(name, "images/block%d.pcx", i+1);
        blocks[i] = load_bitmap(name, NULL);
    }
    
    //setup the map sprite
    map.x = SCREEN_W-810;
    map.y = 333;
    map.display = false;
    map.show = true;
    
    //load the introduction screens
    introduction[0] = load_bitmap("images/introduction.pcx", NULL);
    introduction[1] = load_bitmap("images/modescreen.pcx", NULL);
    
    //setup the introscreen sprite
    introscreen.x = 250;
    introscreen.y = 200;
    introscreen.w = introduction[0]->w;
    introscreen.h = introduction[0]->h;
    introscreen.display = true;
    introscreen.show = true;
    
    introselector = load_bitmap("images/smallbluegem.pcx", NULL);
    
    selector.x = 435;
    selector.y = 400;
    selector.w = introselector->w;
    selector.h = introselector->h;
    selector.display = true;
    selector.show = true;
    
    //load the playing mode screen
    //draw the mode screen to the buffer
    introduction[0] = blitBigger(introduction[0], introscreen.x, introscreen.y);
    introduction[1] = blitBigger(introduction[1], introscreen.x, introscreen.y);
    
    //reset the x and y position of the introscreen
    introscreen.x = 0;
    introscreen.y = 0;
    
    //load the background screen
    background = load_bitmap("images/bg.pcx", NULL);
    
    bg.x = 0;
    bg.y = 0;
    bg.display = false;
    bg.show = true;
    
    return true;
}
*/

#endif
