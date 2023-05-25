#ifndef BOARD_HPP
#define BOARD_HPP

class board {
    private:
        bool slots[5]; //true for filled
        int numBalls; //number of balls on board
    public:
        board(bool s = false, int num = 33);

        //get
        bool getSlotState(int p);
        int getNumBalls();

        //set
        void setSlotState(int p, bool tf);
        void setNumBalls(int num);
        
        //methods
        void addNumBalls();
};

#endif