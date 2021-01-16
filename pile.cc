#include "pile.h"

Pile::Pile(char s)
: suite{s}, stack{false}
{}

Pile::~Pile(){}

char Pile::getSuite(){
    return suite;
}

char Pile::nextSuite(){
    Card tmp(suite, 'A');
    return tmp.nextSuite();
}

Cardlist Pile::getLegal(Cardlist &deck){
    Cardlist tmp;
    if(0 == stack.length()){
        tmp.addToTop(deck.search(suite,'7'));
        return tmp;
    }
    if('A' != (stack.bottom())->rank){
        tmp.addToTop(deck.search(suite, (stack.bottom())->previousRank()));
    }
    if('K' != (stack.top())->rank){
        tmp.addToTop(deck.search(suite, (stack.top())->nextRank()));
    }
    return tmp;
}

void Pile::add(Card* c){
    Card tmp{suite, '\0'};
    if(suite == c->suite && 0 == stack.length() && '7' == c->rank){
        //throw "If 1 threw";
        stack.addToTop(c);
    } else if(suite == c->suite && 0 != stack.length() && stack.top()->nextRank() == c->rank){
        //throw "If 2 threw";
        stack.addToTop(c);
    } else if(suite == c->suite && 0 != stack.length() && stack.bottom()->previousRank()  == c->rank){
        //throw "If 3 threw";
        stack.addToBottom(c);
    } else{
        throw "Card cannot be added to the pile";
    }
}

std::ostream & operator<<(std::ostream & out, const Pile &c){
    out << c.stack;
    return out;
}
