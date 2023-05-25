#ifndef GAME_HPP
#define GAME_HPP

#include "board.hpp"
#include "die.hpp"
#include "opponent.hpp"
#include "player.hpp"

class game {
    private:
        board* tabuleiro;
        die* dado;
        opponent* oponente;
        player* jogador;
        int numRounds;
        int whoseTurn;
    public:
        game(board* b = new board, die* c = new die, opponent* d = new opponent, player* e = new player, int num = 0, int who = 1);
        ~game();
        //get
        int getRounds();

        //filemanip
        void saveScore();
        bool getScores();

        //methods
        bool initGame();
        void display();
        bool checkEnd();
        void round();


};

#endif