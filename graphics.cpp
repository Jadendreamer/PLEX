/**************
* File Name: graphics.cpp
* Author: G. J. Krafsig
* Date: August 2nd, 2007
* Purpose: implementation for game graphic functions
**************/
#include "graphics.h"

/**************
* Purpose: default constructor, initialize class values
* Precondition: none
* Postcondition: none
**************/
gamegraphics::gamegraphics()
{
    //maybe this will do something later...
    boardimg = NULL;
}

/**************
* Purpose: load game related graphics
* Precondition: none
* Postcondition: graphics loaded excluding menu graphics, 
*                movie graphics, and music graphics
**************/
void gamegraphics::loadGraphics()
{
    //load the background image
    bgimg = load_bitmap(BGIMAGE, NULL);
    
    //load side menu graphics
    talkboximg = load_bitmap(TALKBOXIMAGE, NULL);
    talkbubbleimg = load_bitmap(TALKBUBBLEIMAGE, NULL);
    storeimg = load_bitmap(STOREIMAGE, NULL);
    keyimg = load_bitmap(KEYIMAGE, NULL);
    heartimg = load_bitmap(HEARTIMAGE, NULL);
    starimg = load_bitmap(STARIMAGE, NULL);
    
    //load character graphics
    aleximg = load_bitmap(ALEXIMAGE, NULL);
    kittyimg = load_bitmap(KITTYIMAGE, NULL);
    tanyaimg = load_bitmap(TANYAIMAGE, NULL);
    lisaimg = load_bitmap(LISAIMAGE, NULL);
    ravenimg = load_bitmap(RAVENIMAGE, NULL);
    bellaimg = load_bitmap(BELLAIMAGE, NULL);
    
    //load the jewel images
    greenjewelimg = load_bitmap(GREENJEWELIMAGE, NULL);
    bluejewelimg = load_bitmap(BLUEJEWELIMAGE, NULL);
    yellowjewelimg = load_bitmap(YELLOWJEWELIMAGE, NULL);
    
    //load the regular blocks
    grassimg = load_bitmap(GRASSIMAGE, NULL);
    woodimg = load_bitmap(WOODIMAGE, NULL);
    waterimg = load_bitmap(WATERIMAGE, NULL);
    thouseimg = load_bitmap(THOUSEIMAGE, NULL);
    houseimg = load_bitmap(HOUSEIMAGE, NULL);
    tstoneimg = load_bitmap(TSTONEIMAGE, NULL);
    stoneimg = load_bitmap(STONEIMAGE, NULL);
    grayimg = load_bitmap(GRAYIMAGE, NULL);
    dirtimg = load_bitmap(DIRTIMAGE, NULL);
    brownimg = load_bitmap(BROWNIMAGE, NULL);
        
    //load the house blocks
    windowimg = load_bitmap(WINDOWIMAGE, NULL);
    closeddoorimg = load_bitmap(CLOSEDDOORIMAGE, NULL);
    opendoorimg = load_bitmap(OPENDOORIMAGE, NULL);
    roofnorthimg = load_bitmap(ROOFNORTHIMAGE, NULL);
    roofnortheastimg = load_bitmap(ROOFNORTHEASTIMAGE, NULL);
    roofeastimg = load_bitmap(ROOFEASTIMAGE, NULL);
    roofsoutheastimg = load_bitmap(ROOFSOUTHEASTIMAGE, NULL);
    roofsouthimg = load_bitmap(ROOFSOUTHIMAGE, NULL);
    roofnorthwestimg = load_bitmap(ROOFNORTHWESTIMAGE, NULL);
        
    //obstacle blocks
    shrubimg = load_bitmap(SHRUBIMAGE, NULL);
    talltreeimg = load_bitmap(TALLTREEIMAGE, NULL);
    bushimg = load_bitmap(BUSHIMAGE, NULL);
    rockimg = load_bitmap(ROCKIMAGE, NULL);
            
    //ramp blocks
    rampnorthimg = load_bitmap(RAMPNORTHIMAGE, NULL);
    rampsouthimg = load_bitmap(RAMPSOUTHIMAGE, NULL);
    rampeastimg = load_bitmap(RAMPEASTIMAGE, NULL);
    rampwestimg = load_bitmap(RAMPWESTIMAGE, NULL);

}

/**************
* Purpose: deallocate the memory used by game graphics
* Precondition: none
* Postcondition: memory free
**************/
void gamegraphics::destoryGraphics()
{
    //destroy the bg image
    destroy_bitmap(bgimg);
    
    //destroy character images
    destroy_bitmap(aleximg);
    destroy_bitmap(kittyimg);
    destroy_bitmap(tanyaimg);
    destroy_bitmap(lisaimg);
    destroy_bitmap(ravenimg);
    destroy_bitmap(bellaimg);
    
    //destroy side menu images
    destroy_bitmap(talkboximg);
    destroy_bitmap(talkbubbleimg);
    destroy_bitmap(storeimg);
    destroy_bitmap(keyimg);
    destroy_bitmap(starimg);
    destroy_bitmap(heartimg);
    
    //destroy jewel images
    destroy_bitmap(greenjewelimg);
    destroy_bitmap(bluejewelimg);
    destroy_bitmap(yellowjewelimg);
    
    //destroy regular block images
    destroy_bitmap(grassimg);
    destroy_bitmap(woodimg);
    destroy_bitmap(waterimg);
    destroy_bitmap(thouseimg);
    destroy_bitmap(houseimg);
    destroy_bitmap(tstoneimg);
    destroy_bitmap(stoneimg);
    destroy_bitmap(grayimg);
    destroy_bitmap(dirtimg);
    destroy_bitmap(brownimg);
        
    //load the house blocks
    destroy_bitmap(windowimg);
    destroy_bitmap(closeddoorimg);
    destroy_bitmap(opendoorimg);
    destroy_bitmap(roofnorthimg);
    destroy_bitmap(roofnortheastimg);
    destroy_bitmap(roofeastimg);
    destroy_bitmap(roofsoutheastimg);
    destroy_bitmap(roofsouthimg);
    destroy_bitmap(roofsouthwestimg);
    destroy_bitmap(roofwestimg);
    destroy_bitmap(roofnorthwestimg);
        
    //obstacle blocks
    destroy_bitmap(shrubimg);
    destroy_bitmap(talltreeimg);
    destroy_bitmap(bushimg);
    destroy_bitmap(rockimg);
            
    //ramp blocks
    destroy_bitmap(rampnorthimg);
    destroy_bitmap(rampsouthimg);
    destroy_bitmap(rampeastimg);
    destroy_bitmap(rampwestimg);

}

/**************
* Purpose: make the image centered on a black screen
* Precondition: the image to center, x and y position, width and height
* Postcondition: returns the image centered on a black background
**************/
BITMAP *gamegraphics::blitBigger(BITMAP *image, int x, int y, int width, int height)
{
    //clear the temporary image
    BITMAP *temp = create_bitmap(width, height);
    clear(temp);
    blit(image, temp, 0, 0, x, y, image->w, image->h);
    
    //now copy the buffer image back into the intro image (to make the smaller image centered in the screen
    //for blitting later)
    image = create_bitmap(SCREEN_W, SCREEN_H);
    blit(temp, image, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
      
    //destory the temp image, return the bigger one 
    destroy_bitmap(temp);
    return image;
}

/**************
* Purpose: make the image smaller with transparent background
* Precondition: the image to shrink, x and y position, width and height, and divisor
* Postcondition: returns the image with width and height divided by the divisor
**************/
BITMAP *gamegraphics::blitSmaller(BITMAP *image, int width, int height, double divisor)
{
    //create a bitmap for the new image
    BITMAP *temp = create_bitmap(width, height);
    
    //make any extra space it has in the background transparent
    clear_to_color(temp, makecol(255, 0, 255));
    
    stretch_blit(image, temp, 0, 0, image->w, image->h,
                   0, 0, floor(image->w/divisor), floor(image->h/divisor));
                   
    return temp;
}

/**************
* Purpose: return the graphic for the block with this number
* Precondition: the number of the block to get an image for
* Postcondition: return the bitmap for this block
**************/
BITMAP *gamegraphics::getBlock(int block)
{
    switch(block)
    {
        //regular blocks
        case NOBLOCK: return NULL; break;
        case WOOD: return woodimg; break;
        case WATER: return waterimg; break;
        case THOUSE: return thouseimg; break;
        case HOUSE: return houseimg; break;
        case TSTONE: return tstoneimg; break;
        case STONE: return stoneimg; break;
        case GRAY: return grayimg; break;
        case GRASS: return grassimg; break;
        case DIRT: return dirtimg; break;
        case BROWN: return brownimg; break;
        
        //house blocks
        case WINDOW: return windowimg; break;
        case CLOSEDDOOR: return closeddoorimg; break;
        case OPENDOOR: return opendoorimg; break;
        case ROOFNORTH: return roofnorthimg; break;
        case ROOFNORTHEAST: return roofnortheastimg; break;
        case ROOFEAST: return roofeastimg; break;
        case ROOFSOUTHEAST: return roofsoutheastimg; break;
        case ROOFSOUTH: return roofsouthimg; break;
        case ROOFNORTHWEST: return roofnorthwestimg; break;
        
        //obstacle blocks
        case SHRUB: return shrubimg; break;
        case TALLTREE: return talltreeimg; break;
        case BUSH: return bushimg; break;
        case ROCK: return rockimg; break;
            
        //ramp blocks
        case RAMPNORTH: return rampnorthimg; break;
        case RAMPSOUTH: return rampsouthimg; break;
        case RAMPEAST: return rampeastimg; break;
        case RAMPWEST: return rampwestimg; break;
    }
}
