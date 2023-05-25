#ifndef OPPONENT_HPP
#define OPPONENT_HPP

//  Regras do oponente:
//      Lança o dado X vezes, onde X é o número de bolas que ainda tem
//      OPCIONAL: comenta quando ganha ou perde

class opponent {
    private:
        int numBalls; //num balls in hand
        bool activePlayer;
        //string winLines[10];
        //string loseLines[10];
    public:
        opponent(int num = 15);

        //get
        int getNumBalls();

        //set
        void setNumBalls(int n);

        //methods
        void gainBall();
        void loseBall();
};

#endif