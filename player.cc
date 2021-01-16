#include "player.h"

Player::Player(Cardlist c, std::string name)
: name{name}, points{0}, human{true}, hand{c}
{}

Player::~Player(){};

Cardlist Player::getHand(){
    return hand;
}

Cardlist Player::getDiscards(){
    return discard;
}

bool Player::has(Card *c){
    return (bool)hand.search(c);
}

void Player::play(Card *c, Pile &p){
    Card *play = hand.search(c);
    if(!hand.search(c)){
        throw "Player does not have the card";
    }
    p.add(play);
    hand.remove(play);
}

void Player::discard(Card *c){
    Card *play = hand.search(c);
    if(!hand.search(c)){
        throw "Player does not have the card";
    }
    discarded.addToTop(play);
    hand.remove(play);
}

bool Player::isHuman(){
    return human;
}

void Player::setToComputer(){
    human = false;
}

std::ostream & operator<<( std::ostream & out, const Player &p ){
    out << p.name;
    return out;
}
