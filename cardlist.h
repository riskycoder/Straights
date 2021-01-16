#ifndef __CARDLIST_H__
#define __CARDLIST_H__
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>

class Card {
  public:
    Card(char s, char r);
    const char suite;
    const char rank;
    char nextSuite();
    char nextRank();
    char previousRank();
};

class Cardlist {
  bool printSuite;
  std::vector<Card*> list;

  public:
    Cardlist();
    Cardlist(bool printSuite);
    ~Cardlist();
    int length() ;                            //Returns length of the list
    int score();                              //Returns the sum of scores of cards
    void clear();                             //Deletes all cards in the list
                                              //(Cards in the list can no longer be accessed)
    Card* bottom() ;                          //Returns the address to the card in the front of the list
    Card* top() ;                             //Returns the address to the card in the back of the list
    void addToTop(Card* c);                   //Adds the pointer to card to the end of the list
    void addToBottom(Card* c);                //Adds the pointer to card to the front of the list
    void remove(Card* c);                     //Removes the pointer to card from the list if it exists
    Card* search(Card* c) ;                   //Returns address of the card if it exists, nullptr otherwise
    Card* search(char s, char r) ;            //Returns address of the card if it exists, nullptr otherwise
    void shuffle();                           //Shuffles the cardlsit
    Cardlist subset(int b, int e);            //Returns a Cardlist containing all cards from b (inclusive) to e
                                              //If b or e are out of the range, an empty list is returned
    Cardlist intersect(Cardlist &&l) ;        //Returns a Cardlist containing cards from both the lists
    Cardlist & operator+=(const Cardlist &c); //Adding two cardlists

    friend std::ostream & operator<<( std::ostream & out, const Cardlist &c );
};

std::ostream & operator<<( std::ostream & out, const Cardlist &c );

#endif
