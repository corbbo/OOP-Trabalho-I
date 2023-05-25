#ifndef PLAYER_CPP
#define PLAYER_CPP

#include "player.hpp"
#include <iostream>

player::player(string nam, int balls) {
    name = nam;
    numBalls = balls;
}

//get
string player::getName()            {return name;}
int player::getNumBalls()           {return numBalls;}

//set
void player::setName()              {cin >> name;}
void player::setNumBalls(int n)     {numBalls = n;}

//methods
void player::gainBall()             {numBalls++;}
void player::loseBall()             {numBalls--;}

#endif