#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>

using namespace std;

class player {
    private:
        string name;
        int numBalls; //num balls in hand
        bool activePlayer;
    public:
        player(string nam = "", int balls = 15);

        //get
        string getName();
        int getNumBalls();

        //set
        void setName();
        void setNumBalls(int n);

        //methods
        void gainBall();
        void loseBall();
};

#endif