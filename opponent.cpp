#ifndef OPPONENT_CPP
#define OPPONENT_CPP

#include "opponent.hpp"

opponent::opponent(int num) {
    numBalls = num;
}

//get
int opponent::getNumBalls()             {return numBalls;}

//set
void opponent::setNumBalls(int n)       {numBalls = n;}

//methods
void opponent::gainBall()               {numBalls++;}
void opponent::loseBall()               {numBalls--;}

#endif