#ifndef BOARD_CPP
#define BOARD_CPP

#include "board.hpp"

board::board(bool s, int num) {
    for (int i = 0; i < 5; i++) slots[i] = s;
    numBalls = num;
}

//get
bool board::getSlotState(int p)             {return slots[p];}
int board::getNumBalls()                    {return numBalls;}

//set
void board::setSlotState(int p, bool tf)    {slots[p] = tf;}
void board::setNumBalls(int num)            {numBalls = num;}
        
//methods
void board::addNumBalls()                   {numBalls++;}

#endif