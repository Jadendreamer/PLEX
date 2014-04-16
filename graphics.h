/**************
* File Name: graphics.h
* Author: G. J. Krafsig
* Date: July 3rd, 2007
* Purpose: header files for game engine graphics
**************/
#ifndef GAMEGRAPHICS_H
#define GAMEGRAPHICS_H

#include <cstdlib>
#include <cmath>
#include <allegro.h>
#include "sprite.h"
#include "game.h"

//backgroung image
#define BGIMAGE         "images/bg.pcx" 

//character images
#define ALEXIMAGE       "images/person1.pcx" //pigtail boy
#define KITTYIMAGE      "images/person2.pcx" //cat girl
#define TANYAIMAGE      "images/person3.pcx" //pirate girl
#define LISAIMAGE       "images/person4.pcx" //flower girl
#define RAVENIMAGE      "images/person5.pcx" //pricess girl
#define BELLAIMAGE      "images/person6.pcx" //bunny girl

//character name images
#define ALEXNAMEIMAGE   ""
#define KITTYNAMEIMAGE  ""
#define TANYANAMEIMAGE  ""
#define LISANAMEIMAGE   ""
#define RAVENNAMEIMAGE  ""
#define BELLANAMEIMAE   ""

//game obstacles
#define ROCKIMAGE       "images/rock.pcx"
#define TALLTREEIMAGE   "images/tree2.pcx"
#define SHRUBIMAGE      "images/tree1.pcx"
#define BUSHIMAGE       "images/tree3.pcx"
#define BUGIMAGE        ""

//jewels
#define BLUEJEWELIMAGE   "images/gem1.pcx"
#define GREENJEWELIMAGE  "images/gem2.pcx"
#define YELLOWJEWELIMAGE "images/gem3.pcx"

//store items
#define SHOVELIMAGE     ""
#define DYNAMITEIMAGE   ""
#define FIRSTAIDIMAGE   ""

//side menu images
#define STARIMAGE       "images/star.pcx"
#define HEARTIMAGE      "images/heart.pcx"
#define KEYIMAGE        "images/key.pcx"
#define TALKBOXIMAGE    "images/talkbox.pcx"
#define TALKBUBBLEIMAGE "images/talkbubble.pcx"
#define STOREIMAGE      "images/store.pcx"

//ground block images
#define WOODIMAGE       "images/block10.pcx"
#define WATERIMAGE      "images/block9.pcx"
#define THOUSEIMAGE     "images/block8.pcx"
#define HOUSEIMAGE      "images/block7.pcx" 
#define TSTONEIMAGE     "images/block6.pcx"
#define STONEIMAGE      "images/block5.pcx" 
#define GRAYIMAGE       "images/block4.pcx" 
#define GRASSIMAGE      "images/block3.pcx"
#define DIRTIMAGE       "images/block2.pcx"
#define BROWNIMAGE      "images/block1.pcx"

//house block images
#define WINDOWIMAGE         "images/window.pcx"
#define CLOSEDDOORIMAGE     "images/closeddoor.pcx"
#define OPENDOORIMAGE       "images/dooropen.pcx"
#define ROOFNORTHIMAGE      "images/roof5.pcx"
#define ROOFNORTHEASTIMAGE  "images/roof4.pcx"
#define ROOFEASTIMAGE       "images/roof3.pcx"
#define ROOFSOUTHEASTIMAGE  "images/roof2.pcx"
#define ROOFSOUTHIMAGE      "images/roof1.pcx"
#define ROOFNORTHWESTIMAGE  "images/roof6.pcx"

//ramp block image
#define RAMPNORTHIMAGE  "images/ramp1.pcx"
#define RAMPSOUTHIMAGE  "images/ramp3.pcx"
#define RAMPEASTIMAGE   "images/ramp2.pcx"
#define RAMPWESTIMAGE   "images/ramp4.pcx"

//shadow images
#define SHADOWNORTHIMAGE        ""
#define SHADOWSOUTHIMAGE        ""
#define SHADOWEASTIMAGE         ""
#define SHADOWWESTIMAGE         ""
#define SHADOWNORTEASTIMAGE     ""
#define SHADOWNORTHWESTIMAGE    ""
#define SHADOWSOUTEASTIMAGE     ""
#define SHADOWSOUTHWESTIMAGE    ""

class gamegraphics
{
	public:
		gamegraphics(); //class constructor	
		
		/******************
        * Purpose: loading/destroying game graphics
		* EXCLUDING:
        *  menu graphics
        *  movie graphics
        *  and music graphics
        ******************/
		void   loadGraphics();
		void   destoryGraphics();
		
		//position an image on a larger screen
		BITMAP *blitBigger(BITMAP *image, int x, int y, int width, int height);
		BITMAP *blitSmaller(BITMAP *image, int width, int height, double divisor);
		
        //return the block image for this block number
        BITMAP *getBlock(int block);
		
        //background image
        BITMAP *bgimg;
        
        //character images
        BITMAP *aleximg;
        BITMAP *kittyimg;
        BITMAP *tanyaimg;
        BITMAP *lisaimg;
        BITMAP *ravenimg;
        BITMAP *bellaimg;
        
        //character name images
        BITMAP *alexnameimg;
        BITMAP *kittynameimg;
        BITMAP *tanyanameimg;
        BITMAP *lisanameimg;
        BITMAP *ravennameimg;
        BITMAP *bellanameimg;
        
        //game obstacles
        BITMAP *rockimg;
        BITMAP *talltreeimg;
        BITMAP *shrubimg;
        BITMAP *bushimg;
        BITMAP *bugimg;

        //jewels
        BITMAP *bluejewelimg;
        BITMAP *greenjewelimg;
        BITMAP *yellowjewelimg;

        //store items
        BITMAP *shovelimg;
        BITMAP *dynamiteimg;
        BITMAP *firstaidimg;

        //side menu images
        BITMAP *starimg;
        BITMAP *heartimg;
        BITMAP *keyimg;
        BITMAP *talkboximg;
        BITMAP *talkbubbleimg;
        BITMAP *storeimg;
        
        //ground block images
        BITMAP *woodimg;
        BITMAP *waterimg;
        BITMAP *thouseimg;
        BITMAP *houseimg;
        BITMAP *tstoneimg;
        BITMAP *stoneimg;
        BITMAP *grayimg;
        BITMAP *grassimg;
        BITMAP *dirtimg;
        BITMAP *brownimg;

        //house block images
        BITMAP *windowimg;
        BITMAP *closeddoorimg;
        BITMAP *opendoorimg;
        BITMAP *roofnorthimg;
        BITMAP *roofnortheastimg;
        BITMAP *roofeastimg;
        BITMAP *roofsoutheastimg;
        BITMAP *roofsouthimg;
        BITMAP *roofsouthwestimg;
        BITMAP *roofwestimg;
        BITMAP *roofnorthwestimg;

        //ramp block image
        BITMAP *rampnorthimg;
        BITMAP *rampsouthimg;
        BITMAP *rampeastimg;
        BITMAP *rampwestimg;

        //shadow images
        BITMAP *shadownorthimg;
        BITMAP *shadowsouthimg;
        BITMAP *shadoweastimag;
        BITMAP *shadowwestimg;
        BITMAP *shadownortheastimg;
        BITMAP *shadownorthwestimg;
        BITMAP *shadowsoutheastimg;
        BITMAP *shadowsouthwestimg;        

};

#endif
