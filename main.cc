#include <iostream>
#include <string>
#include "controller.h"

void printTurnStart(Controller *ctr){
    //Text at the start of each turn
    std::cout << "Cards on the table:" << std::endl;
    std::cout << "Clubs: " << ctr->getStack(0) << std::endl;
    std::cout << "Diamonds: " << ctr->getStack(1) << std::endl;
    std::cout << "Hearts: " << ctr->getStack(2) << std::endl;
    std::cout << "Spades: " << ctr->getStack(3) << std::endl;
    std::cout << "Your hand: " << ctr->hand() << std::endl;
    std::cout << "Legal plays: " << ctr->legal() << std::endl;
}

int main(int argc, char **argv) {

    int seed = -1;

    if(argc == 2){
        std::string tmp(argv[1]);
        try{
            seed = std::stoi(tmp);
            if(seed < 0){
                std::cout << "Seed must be non-negative: set randomly" << std::endl;
                seed = -1;
            }
        } catch(...){
            std::cout << "Invalid seed: set randomly" << std::endl;
        }
    }

    Controller *ctr = new Controller(seed == -1? time(0) : seed);
    std::string cmd;
    char suite;
    char rank;

    //Initializing players
    int ind = ctr->getCurrentPlayer();
    ctr->setCurrentPlayer(0);
    for(int i = 0; i < 4; i++){
        char p;
        std::cout<< "Is " << ctr->currentPlayer() << " a human (h) or a computer (c)?" << std::endl;
        std::cout<< ">";
        std::cin >> p;
        if('c' == p){
            ctr->setToComputer();
        }
        ctr->incrementPlayer();
    }
    ctr->setCurrentPlayer(ind);

    //Game loop

    while(true){
        std::cout << "A new round begins. It's " << ctr->currentPlayer() << "'s turn to play." << std::endl;
        printTurnStart(ctr);

        while (true){

            if(0 == ctr->currentPlayer().getHand().length()){break;}

            std::cout << ">";

            if(ctr->currentPlayer().isHuman()){

                if(!(std::cin >> cmd)){break;}

                if(cmd == "play"){
                    std::cin >> suite;
                    std::cin >> rank;
                    try{
                        ctr->play(suite, rank); //This line could throw an exception
                        std::cout << ctr->currentPlayer() << " plays " << suite << rank << '.' << std::endl;
                        ctr->incrementPlayer();
                    }
                    catch(const char e[]){
                        std::cerr << e << std::endl;
                        std::cout << ">";
                        continue;
                    }
                }else if (cmd == "discard") {
                    std::cin >> suite;
                    std::cin >> rank;
                    try{
                        ctr->discard(suite, rank); //This line could throw an exception
                        std::cout << ctr->currentPlayer() << " discards " << suite << rank << '.' << std::endl;
                        ctr->incrementPlayer();
                    }
                    catch(const char e[]){
                        std::cerr << e << std::endl;
                        std::cout << ">";
                        continue;
                    }

                }else if (cmd == "deck") {
                    std::cout << ctr->getDeck() << std::endl;
                    continue;
                }else if (cmd == "ragequit") {
                    ctr->setToComputer();
                }else if (cmd == "quit") {
                    break;
                } else {
                    std::cerr << "Invalid command." << std::endl;
                }
            }
            //This segment of the code gets executed if the current player is supposed to be a computer
            else{
                Cardlist hand = ctr->hand();
                Cardlist legal = ctr->legal();
                if(legal.length()){
                    suite = legal.bottom()->suite;
                    rank = legal.bottom()->rank;
                    ctr->play(legal.bottom()->suite, legal.bottom()->rank);
                    std::cout << ctr->currentPlayer() << " plays " << suite << rank << '.' << std::endl;
                    ctr->incrementPlayer();
                }
                else{
                    suite = hand.bottom()->suite;
                    rank = hand.bottom()->rank;
                    ctr->discard(hand.bottom()->suite, hand.bottom()->rank);
                    std::cout << ctr->currentPlayer() << " discards " << suite << rank << '.' << std::endl;
                    ctr->incrementPlayer();
                }
            }
            printTurnStart(ctr);
        }

        //If there are cards in the hand, control reached here because player wanted to quit
        if(0 == ctr->currentPlayer().getHand().length()){break;}

        //If that is not the case we calculate the scores
        ctr->setCurrentPlayer(0);
        for(int i = 0; i < 4; i++){
            int prScore = ctr->currentPlayer().points;
            int discards = ctr->currentPlayer().getDiscards().score();
            
            std::cout << ctr->currentPlayer() << "'s discards: " 
                << ctr->currentPlayer().getDiscards() << std::endl;
            std::cout << ctr->currentPlayer() << "'s score: " << prScore << " + " 
                << discards << " = " << std::endl;
        }
    }    
}
