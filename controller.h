#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__
#include <iostream>
#include <string>
#include <vector>
#include "pile.h"
#include "cardlist.h"
#include "player.h"

class Controller {
    std::vector<Pile> stacks;
    Cardlist deck;
    std::vector<Player> players;
    int current;                        //Indicates the index of the current player
    bool firstTurn;

  public:
    Controller(int seed);
    ~Controller();
    void play(char s, char r);
    void discard(char s, char r);
    int getCurrentPlayer();
    void setCurrentPlayer(int i);
    void incrementPlayer();
    void setToComputer();
    Player currentPlayer();
    Cardlist getDeck();
    Pile getStack(int i);
    Cardlist hand();
    Cardlist legal(); 
};

#endif
