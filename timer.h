/**************
* File Name: timer.h
* Author: G. J. Krafsig
* Date: July 3rd, 2007
* Purpose: timer functions for the game
**************/

#ifndef G_TIMER
#define G_TIMER

volatile int gtimer = 0;
void increase_time();

class timer
{
    public:
        timer();
        void init();
        void reset();
        int getTime();  
        
}; 
#endif

timer::timer()
{
    //setup the timer and timer functions
    LOCK_VARIABLE(gtimer);
    LOCK_FUNCTION(increase_time);
    install_int_ex(increase_time, SECS_TO_TIMER(1));  
}

void timer::reset()
{
    gtimer = 0;
}

int timer::getTime()
{
    return gtimer;   
}

void increase_time()
{
   gtimer++;
}END_OF_FUNCTION(increase_time)

/*


void init_timer();
void increase_time();
void timer_reset();

void init_timer()
{
    //setup the timer and timer functions
    LOCK_VARIABLE(timer);
    LOCK_FUNCTION(increase_time);
    install_int_ex(increase_time, SECS_TO_TIMER(1));
}
*/

/***********
* Purpose: reset the timer
* Precondition: none
* Postcondition: timer reset to zero
***********/
/*
void timer_reset()
{
    timer = 0;
}
*/

/***********
* Purpose: timer interupt handler
* Precondition: none
* Postcondition: none
***********/
/*
void increase_time(void)
{
   timer++;
}
END_OF_FUNCTION(increase_time)
*/
