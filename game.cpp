#ifndef GAME_CPP
#define GAME_CPP

#include "game.hpp"

#include <iostream>
#include <sstream>
#include <chrono>
#include <thread>
#include <fstream>
#include <vector>
#include <utility> //std::pair


game::game(board* b, die* c, opponent* d, player* e, int num, int who) {
    tabuleiro = b;
    dado = c;
    oponente = d;
    jogador = e;
    numRounds = num;
    whoseTurn = who;
}

game::~game() {
    delete jogador;
    delete tabuleiro;
    delete oponente;
    delete dado;
    delete this;
}

//get
int game::getRounds() {return numRounds;}

//filemanip
void game::saveScore() {
    string filename = "scores.txt";
    ifstream infile(filename);
    string name = jogador->getName();
    int score = numRounds;
    if (infile.good()) { //if file exists
        vector<pair<string, int>> scores; //dynamic array of pairs of names and scores
        string scoreLine;
        while(getline(infile, scoreLine)) { //read all score entries
            stringstream ss(scoreLine);
            string oldName;
            int oldScore;
            ss >> oldName >> oldScore;
            scores.push_back(make_pair(oldName, oldScore)); //new entry at last index + 1
        }
        for (int i = 0; i < 10 && i < (signed)scores.size(); i++) { //find where new score should go, up to the 10th rank
            if (score < scores[i].second) {
                scores.insert(scores.begin() + i /*like doing *a + i to access an array at index i*/, make_pair(name, score));
                break;
            }
        }
        ofstream outfile(filename, ios::trunc);
        for (int i = 0; i < (signed)scores.size() && i < 10; i++) { //write scores back into file
            outfile << scores[i].first << " " << scores[i].second << endl;
        }
        outfile.close();
    } else { //if file doesn't exist, make new file
        infile.close();
        ofstream outfile(filename, ios::trunc);
        outfile << name << " " << score << endl;
        outfile.close();
    }
}

bool game::getScores() {
    string filename = "scores.txt";
    ifstream infile(filename);
    string name;
    int score;
    if (infile.good()) {
        string scoreLine;
        vector<pair<string, int>> scores; //dynamic array of pairs of names and scores
        while (getline(infile, scoreLine)) { //read all score entries
            stringstream ss(scoreLine);
            ss >> name >> score;
            scores.push_back(make_pair(name, score));
        }
        cout << "--- TOP 10 HIGHSCORES ---" << endl;
        for (int i = 0; i < (signed)scores.size(); i++) {
            cout << i+1 << ") " << scores[i].first << " | Rounds: " << scores[i].second << endl;
        }
        infile.close();
        return true;
    } else {
        infile.close();
        return false;
    }
}

//methods
bool game::initGame() {
    cout << "Welcome to Speculate! Type R for the rules, P to begin play, or H to see highscores." << endl;
    while (1) {
        char key;
        cin >> key;
        if (key == 'H' || key == 'h') {
            if (!getScores()) cout << "Looks like no-one won a game yet. Check back later!" << endl;
            cout << "Type P to play or R to check the rules." << endl;
            cin >> key;
        }
        if (key == 'R'|| key == 'r') { //show rules
            cout << "Speculate is a game played with a board that has 6 numbered slots and a depression, a die, two or more players, and 33 balls." << endl << endl
                << "At the start of the game, three balls are placed on slots 1, 3, and 5 of the board. The remaining balls are distributed evenly among players." << endl << endl
                << "On each player's turn, that player may roll the die up to however many balls they still have. The number you roll tells you which slot" << endl
                << "you should put one of your balls in. If that slot is already filled, you pick up the ball instead. If you roll a 6, drop the ball in the cavity, and it'll slide" << endl
                << "to the center of the board! Then roll the die again. Once you're done rolling, the turn passes to the next player." << endl << endl
                << "A player wins once they have placed all their balls (including any they've picked up from the slots) into the board, ending the game!" << endl << endl
                << "In this version of Speculate, you will be playing against one opponent, the Computer, and it follows one strict rule: It will always roll the most it can!" << endl << endl
                << "That's it for the rules. When you're ready, type P to begin!" << endl;
            cin  >> key;
        }
        if (key == 'P' || key == 'p') { //begin game
            cout << "Please insert your name: ";
            jogador->setName();
            cout << endl << "Welcome " << jogador->getName() << "! Let's begin." << endl << endl;
            //update who has how many balls
            jogador->setNumBalls(15);
            oponente->setNumBalls(15);
            tabuleiro->setNumBalls(0);
            //update slot states for remaining 3 balls
            tabuleiro->setSlotState(0, true);
            tabuleiro->setSlotState(2, true);
            tabuleiro->setSlotState(4, true);
            //begin game
            return true;
        } else {
            cout << "I don't know what that means. Try H, P, or R please!" << endl;
        }
    }
    return false;
}

void game::display() {
    //set up "board"
    cout << "----------" << " ROUND " << numRounds << " -----------" << endl;
    cout << "[" << jogador->getName() << ": " << jogador->getNumBalls() << " Balls Left]" << endl;
    cout << "[" << "Computer: " << oponente->getNumBalls() << " Balls Left]" << endl;
    if (whoseTurn == 1) cout << jogador->getName() << "'s Turn!" << endl << endl;
    else cout << "Computer's Turn!" << endl << endl;
    cout << "SLOT       1       2       3       4       5" << endl;
    cout << "           ";
    for (int i = 0; i < 5; i++) {
        if (tabuleiro->getSlotState(i)) cout << "x"; else cout << "o";
        if (i < 4) cout << "       ";
    }
    cout << endl << endl;
    cout << "Balls on board: " << tabuleiro->getNumBalls() << endl << endl;
}

bool game::checkEnd() {
        switch(whoseTurn) {
            case 1: if (jogador->getNumBalls() == 0) return true;
                    else return false;
            case 2: if (oponente->getNumBalls() == 0) return true;
                    else return false;
    }
    return false;
}

void game::round() {
    display();
    //begin player's turn
    int rolling;
    while (true) {
        cout << "Type how many times you'd like to roll: ";
        cin >> rolling;
        if (rolling > jogador->getNumBalls()) {cout << "You can only roll up to the number of balls you have! Try again." << endl; continue;}
        if (rolling < 1)                      {cout << "Very funny. Try again." << endl; continue;}
        cout << "Let's roll!" << endl; break;
    }

    while (rolling) {
        int dieRoll = dado->roll();
        if (dieRoll == 6) {
            jogador->loseBall();
            tabuleiro->addNumBalls();
            display();
            cout << "Rolled a " << dieRoll << endl;
            cout << "Very nice! You lose a ball and roll again." << endl << endl;
            this_thread::sleep_for(std::chrono::seconds(2));
        } else if (tabuleiro->getSlotState(dieRoll - 1)) { //rolled filled slot
            jogador->gainBall();
            tabuleiro->setSlotState(dieRoll - 1, false);
            display();
            cout << "Rolled a " << dieRoll << endl;
            cout << "Oops! Bad luck, you gained a ball." << endl << endl;
            rolling--;
            this_thread::sleep_for(std::chrono::seconds(2));
        } else { //rolled empty slot
            jogador->loseBall();
            tabuleiro->setSlotState(dieRoll - 1, true);
            display();
            cout << "Rolled a " << dieRoll << endl;
            cout << "Yes! It's an empty slot." << endl << endl;
            rolling--;
            this_thread::sleep_for(std::chrono::seconds(2));
        }
    
        if (checkEnd()) { //check at the end of a die roll if game has ended
            rolling = 0;
            cout << "Congratulations! You won! You're welcome to play again after the program closes itself in: ";
            this_thread::sleep_for(std::chrono::seconds(1));
            cout << "5..." << endl;
            this_thread::sleep_for(std::chrono::seconds(1));
            cout << "4..." << endl;
            this_thread::sleep_for(std::chrono::seconds(1));
            cout << "3..." << endl;
            this_thread::sleep_for(std::chrono::seconds(1));
            cout << "2..." << endl;
            this_thread::sleep_for(std::chrono::seconds(1));
            cout << "1..." << endl;
            this_thread::sleep_for(std::chrono::seconds(1));
            saveScore();
            return;
        }
    }
    //if the game hasn't ended, it's the computer's turn
    cout << "Your rolls are done! The computer will start its turn in 3...";
    this_thread::sleep_for(std::chrono::seconds(1));
    cout << " 2...";
    this_thread::sleep_for(std::chrono::seconds(1));
    cout << " 1..." << endl;
    whoseTurn = 2;

    display();
    rolling = oponente->getNumBalls();

    while (rolling) {
        int dieRoll = dado->roll();
        if (dieRoll == 6) {
            oponente->loseBall();
            tabuleiro->addNumBalls();
            display();
            cout << "Rolled a " << dieRoll << endl;
            cout << "Oh no! The computer loses a ball and rolls again!" << endl << endl;
            this_thread::sleep_for(std::chrono::seconds(1));
        } else if (tabuleiro->getSlotState(dieRoll - 1)) {
            oponente->gainBall();
            tabuleiro->setSlotState(dieRoll - 1, false);
            display();
            cout << "Rolled a " << dieRoll << endl;
            cout << "Sensational! The computer gained a ball!" << endl << endl;
            rolling--;
            this_thread::sleep_for(std::chrono::seconds(1));
        } else {
            oponente->loseBall();
            tabuleiro->setSlotState(dieRoll - 1, true);
            display();
            cout << "Rolled a " << dieRoll << endl;
            cout << "Tarnation! It's an empty slot." << endl << endl;
            rolling--;
            this_thread::sleep_for(std::chrono::seconds(1));
        }
    
        if (checkEnd()) { //check at the end of a die roll if game has ended
            rolling = 0;
            cout << "Looks like it's a win for the Computer! You're welcome to play again after the program closes itself in: " << endl;
            this_thread::sleep_for(std::chrono::seconds(1));
            cout << "5...";
            this_thread::sleep_for(std::chrono::seconds(1));
            cout << " 4...";
            this_thread::sleep_for(std::chrono::seconds(1));
            cout << " 3...";
            this_thread::sleep_for(std::chrono::seconds(1));
            cout << " 2...";
            this_thread::sleep_for(std::chrono::seconds(1));
            cout << " 1..." << endl;
            this_thread::sleep_for(std::chrono::seconds(1));
            return;
        }
    }
    
    // if no one won yet, move on to next round
    cout << "Looks like no-one won yet! Moving on to the next round in: ";
    this_thread::sleep_for(std::chrono::seconds(1));
    cout << "3...";
    this_thread::sleep_for(std::chrono::seconds(1));
    cout << " 2...";
    this_thread::sleep_for(std::chrono::seconds(1));
    cout << " 1...";
    this_thread::sleep_for(std::chrono::seconds(1));
    whoseTurn = 1; //change back to player
    numRounds++; //new round
    cout << endl;
    round(); //recursively enter new round
}

#endif