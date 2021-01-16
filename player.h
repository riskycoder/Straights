#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <iostream>
#include <string>
#include <vector>
#include "cardlist.h"
#include "pile.h"

class Player {
    std::string name;
    bool human;
    Cardlist hand;
    Cardlist discarded;
  public:
    int points;
    Player(Cardlist c, std::string name);
    ~Player();
    Cardlist getHand();
    Cardlist getDiscards();
    bool has(Card *c);              //Returns true is player has the card, false otherwise
    void play(Card *c, Pile &p);    //Removes card from hand and places into pile if operation is valid
                                    //Throws exception if the operation is invalid - offers strong guarantee
    void discard(Card *c);          //Moves the given pile from hand to discard
                                    //Throws exception if the operation is invalid - offers strong guarantee
    bool isHuman();
    void setToComputer();
    
    friend std::ostream & operator<<( std::ostream & out, const Player &p );
};

std::ostream & operator<<( std::ostream & out, const Player &p );

#endif
