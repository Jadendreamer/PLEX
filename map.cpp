/**************
* File Name: map.cpp
* Author: G. J. Krafsig
* Date: February 2nd, 2008
* Purpose: implementation for the map file
**************/
#include "map.h"

map::map()
{
    //don't do anything  
}

map::map(int character)
{
    //setup all the default values based on the 
    //character they've selected to play the game as
    
    switch (character)
    {
        case 0: //alex
            landslide = "maps/alex_landslide.plex";
            waterville = "maps/alex_waterville.plex";
            haymarket = "maps/alex_haymarket.plex";
            stonecastle = "maps/alex_stonecastle.plex";
            mercyvalley = "maps/alex_mercyvalley.plex";
            fuzzyland = "maps/alex_fuzzyland.plex";
            wishingwellfalls = "maps/alex_wishingwellfalls.plex";
            bouldercanyon = "maps/alex_lboundercanyon.plex";
            merryfield = "maps/alex_merryfield.plex";
            ashcanyon = "maps/alex_ashcanyon.plex";
            buildersguild = "maps/alex_buildersguild.plex";
            break;
        case 1: //kitty
            break;
        case 2: //tanya
            break;
        case 3: //lisa
            break;
        case 4: //raven
            break;
        case 5: //bella
            break;
    }
}

/***********
* Purpose: return the file name for the map
* Precondition: map to lookup
* Postcondition: file name returned
***********/
bool map::getMapFilename(int map)
{
    switch(map)
    {
        case LANDSLIDE: return landslide;
            break;
        case WATERVILLE: return waterville;
            break;
        case HAYMARKET: return haymarket;
            break;
        case STONECASTLE: return stonecastle;
            break;
        case MERCYVALLEY: return mercyvalley;
            break;
        case FUZZYLAND: return fuzzyland;
            break;
        case WISHINGWELLFALLS: return wishingwellfalls;
            break;
        case BOULDERCANYON: return bouldercanyon;
            break;
        case MERRYFIELD: return merryfield;
            break;
        case ASHCANYON: return ashcanyon;
            break;
        case BUILDERSGUILD: return buildersguild;
            break;
        
        default: return false;
            break;   
    }
    
    return true;
}

/***********
* Purpose: set the filename for this particular map
* Precondition: map to set, filename of the map
* Postcondition: map filename is set
***********/
int map::setMapFilename(int map, char *filename)
{
    if (!map)
        return 107; //error code, no map selected
        
    if (!filename)
        return 108; //no filename to set
}
