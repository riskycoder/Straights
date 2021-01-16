#ifndef __PILE_H__
#define __PILE_H__
#include <iostream>
#include <string>
#include <vector>
#include "cardlist.h"

class Pile {
    char suite;
    Cardlist stack;

  public:
    Pile(char s);
    ~Pile();
    //Returns a character representing the suite of the card
    char getSuite();
    //Returns a character representing the next suite
    char nextSuite();
    //Returns a cardlist containing all the legal cards that can be placed onto the pile from the deck
    Cardlist getLegal(Cardlist &deck);
    //Adds the card to the pile if valid - if invalid throws excaption with strong guarantee
    void add(Card* c);

    friend std::ostream & operator<<(std::ostream & out, const Pile &c);
};

std::ostream & operator<<(std::ostream & out, const Pile &c);

#endif
