/**************
* File Name: map.h
* Author: G. J. Krafsig
* Date: February 2nd, 2008
* Purpose: filenames about info to load for maps
**************/
#ifndef MAP_H
#define MAP_H

#define LANDSLIDE           1
#define WATERVILLE          2
#define HAYMARKET           3
#define STONECASTLE         4
#define MERCYVALLEY         5
#define FUZZYLAND           6
#define WISHINGWELLFALLS    7
#define BOULDERCANYON       8
#define MERRYFIELD          9
#define ASHCANYON           10
#define BUILDERSGUILD       11

#include <allegro.h> //allegro library
#include <winalleg.h> //override windows info
#include <string.h>


class map
{
    public:
        map(); //default constructor
        map(int character); //constructor, takes the ID of the character 
                            //they've decided to play as when they start a new game
        bool getMapFilename(int map); //return the filename for the particular map
        int setMapFilename(int map, char *filename); //set the filename for this map
        bool loadDefaultMaps(int character); //load files for default game for this
                                             //particular character
        
        //variables
        char *landslide; //data files for corresponding maps...
        char *waterville;
        char *haymarket;
        char *stonecastle;
        char *mercyvalley;
        char *fuzzyland;
        char *wishingwellfalls;
        char *bouldercanyon;
        char *merryfield;
        char *ashcanyon;
        char *buildersguild;
        
};
#endif
