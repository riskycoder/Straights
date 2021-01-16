#include "controller.h"

Controller::Controller(int seed)
: firstTurn{true}
{
    //Set seed
    std::srand( (unsigned)seed );

    //Create deck
    deck.addToTop(new Card('C', 'A')); //First card in the deck
    for(int i = 1; i < 52; i++){
        if('K' == deck.top()->rank){
            deck.addToTop(new Card(deck.top()->nextSuite(), deck.top()->nextRank()));
        }else{
            deck.addToTop(new Card(deck.top()->suite, deck.top()->nextRank()));
        }        
    }

    //Shuffle deck
    deck.shuffle();

    //Create piles
    stacks.emplace_back(Pile('C')); //First pile
    for(int i = 1; i < 4; i++){
        stacks.emplace_back(Pile(stacks.back().nextSuite()));
    }

    //Create players
    players.emplace_back(Player(deck.subset(0,13), "Player1"));
    players.emplace_back(Player(deck.subset(13,26), "Player2"));
    players.emplace_back(Player(deck.subset(26,39), "Player3"));
    players.emplace_back(Player(deck.subset(39,52), "Player4"));

    //Determining current player
    for(int i = 0; i < 4; i++){
        if(players[i].has(deck.search('S', '7'))){
            current = i;
        }
    }
}

Controller::~Controller() {
    //Destroy deck
    deck.clear();
}

void Controller::play(char s, char r){
    int index = -1;

    if(firstTurn && ('S' != s || '7' != r)){
        throw "Must start with 7S";
    }

    for(int i = 0; i < 4; i++){
        if(s == stacks[i].getSuite()){
            index = i;
            break;
        }
    }
    if(-1 == index){
        throw "Invalid suite";
    }
    players[current].play(deck.search(s,r), stacks[index]);
    firstTurn = false;
}

void Controller::discard(char s, char r){
    Card *discarded = deck.search(s,r);
    if(0 != legal().length()){
        throw "Legal card(s) exist and must be played";
    }
    if(!discarded){
        throw "Invalid card";
    }
    players[current].discard(deck.search(s,r));
}

int Controller::getCurrentPlayer(){
    return current;
}

void Controller::setCurrentPlayer(int i){
    if(i < 0 || i >= 4){
        throw "Player set to invalid index";
    }
    current = i;
}

void Controller::incrementPlayer(){
    ++current %= 4;
}

void Controller::setToComputer(){
    players[current].setToComputer();
}

Player Controller::currentPlayer(){
    return players[current];
}

Cardlist Controller::getDeck(){
    return deck;
}

Pile Controller::getStack(int i){
    return stacks[i];
}

Cardlist Controller::hand(){
    return players[current].getHand();
}

Cardlist Controller::legal(){
    Cardlist tmp;

    if(firstTurn){
        tmp.addToTop(deck.search('S','7'));
        return tmp;
    }

    for(int i = 0; i < 4; i++){
        tmp += stacks[i].getLegal(deck);
    }
    tmp = tmp.intersect(players[current].getHand());
    return tmp;
}
