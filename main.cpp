#include "game.hpp"

int main() {
    game* jogo = new game;
    jogo->initGame();
    jogo->round();
    delete jogo;
    return 0;
}