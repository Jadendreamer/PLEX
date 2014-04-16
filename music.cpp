/**************
* File Name: music.h
* Author: G. J. Krafsig
* Date: July 3rd, 2007
* Purpose: header files for game music
**************/
#include "music.h"

gamemusic::gamemusic()
{
    playing = false;
    sound = false;
}

/**************
* Purpose: load all music
* Precondition: sound files exist
* Postcondition: sound files are loaded
**************/
bool gamemusic::loadMusic()
{
    blockfall = load_sample("sounds/blockfall.wav");
    errormove = load_sample("sounds/errormove.wav");
    theme = load_sample("sounds/theme.wav");
            
    ashcanyon = load_sample("sounds/ashcanyon.wav");
    mercyvalley = load_sample("sounds/mercyvalley.wav");
    waterville = load_sample("sounds/waterville.wav");
    landslide = load_sample("sounds/landslide.wav");
    merryfield = load_sample("sounds/merryfield.wav");
    fuzzyland = load_sample("sounds/fuzzyland.wav");
    bouldercanyon = load_sample("sounds/bouldercanyon.wav");
    wishingwellfalls = load_sample("sounds/wishingwellfalls.wav");
    stonecastle = load_sample("sounds/stonecastle.wav");
    haymarket = load_sample("sounds/haymarket.wav");
    buildersguild = load_sample("sounds/buildersguild.wav");

    return 0; 
}

/**************
* Purpose: free memory from music
* Precondition: sounds have been instantiated
* Postcondition: memory is now free again
**************/
bool gamemusic::destroyMusic()
{
    destroy_sample(blockfall);
    destroy_sample(errormove);
    destroy_sample(theme);
    destroy_sample(current);
    
    destroy_sample(ashcanyon);
    destroy_sample(mercyvalley);
    destroy_sample(waterville);
    destroy_sample(landslide);
    destroy_sample(haymarket);
    destroy_sample(merryfield);
    destroy_sample(fuzzyland);
    destroy_sample(stonecastle);
    destroy_sample(bouldercanyon);
    destroy_sample(buildersguild);
    destroy_sample(wishingwellfalls);
    
    return 0;   
}

/**************
* Purpose: load all music
* Precondition: sound files exist
* Postcondition: sound files are loaded
**************/
bool gamemusic::play(int map, int volume, int pan, int rate, int loop)
{
    if (sound) //only play something if the sound is on
    {
        
     switch(map)
     {
        case LANDSLIDE: play_sample(landslide, volume, pan, rate, loop);
                        current = landslide;
                        break;
                        
        case WATERVILLE: play_sample(waterville, volume, pan, rate, loop);
                        current = waterville;
                        break;
                        
        case HAYMARKET: play_sample(haymarket, volume, pan, rate, loop);
                        current = haymarket;
                        break;
                        
        case STONECASTLE: play_sample(stonecastle, volume, pan, rate, loop);
                        current = stonecastle;
                        break;
                        
        case MERCYVALLEY: play_sample(mercyvalley, volume, pan, rate, loop);
                        current = mercyvalley;
                        break;
                        
        case FUZZYLAND: play_sample(fuzzyland, volume, pan, rate, loop);
                        current = fuzzyland;
                        break;
                        
        case WISHINGWELLFALLS: play_sample(wishingwellfalls, volume, pan, rate, loop);
                        current = wishingwellfalls;
                        break;
                        
        case BOULDERCANYON: play_sample(bouldercanyon, volume, pan, rate, loop);
                        current = bouldercanyon;
                        break;
                        
        case MERRYFIELD: play_sample(merryfield, volume, pan, rate, loop);
                        current = merryfield;
                        break;
                        
        case ASHCANYON: play_sample(ashcanyon, volume, pan, rate, loop);
                        current = ashcanyon;
                        break;
                        
        case BUILDERSGUILD: play_sample(buildersguild, volume, pan, rate, loop);
                        current = buildersguild;
                        break;
                        
        case BLOCKFALL: play_sample(blockfall, volume, pan, rate, loop);
                        current = blockfall;
                        break;
                        
        case ERRORMOVE: play_sample(errormove, volume, pan, rate, loop);
                        current = errormove;
                        break;
                        
        case THEME: play_sample(theme, volume, pan, rate, loop);
                        current = theme;
                        break;
        
        default: play_sample(theme, volume, pan, rate, loop);
                 current = theme;
                 break;
     } //end switch map
    } //end sound is on
    
    return 0;
}

/**************
* Purpose: load all music
* Precondition: sound files exist
* Postcondition: sound files are loaded
**************/
bool gamemusic::stop()
{
    stop_sample(current);
    return 0;
}
