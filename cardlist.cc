#include "cardlist.h"

Card::Card(char s, char r)
: suite{s}, rank{r}
{}

char Card::nextSuite(){
    if('C' == suite){
        return 'D';
    } else if('D' == suite){
        return 'H';
    } else if('H' == suite){
        return 'S';
    } else if ('S' == suite){
        return 'C';
    }
    return '\0'; //Invalid suite received
}

char Card::nextRank(){
    if('2' <= rank && rank <= '8'){
        return rank + 1;
    } else if('A' == rank){
        return '2';
    } else if('9' == rank){
        return 'T';
    } else if('T' == rank){
        return 'J';
    } else if('J' == rank){
        return 'Q';
    } else if('Q' == rank){
        return 'K';
    } else if('K' == rank){
        return 'A';
    }
    return '\0'; //Invalid rank received
}

char Card::previousRank(){
    if('3' <= rank && rank <= '9'){
        return rank - 1;
    } else if('2' == rank){
        return 'A';
    } else if('T' == rank){
        return '9';
    } else if('J' == rank){
        return 'T';
    } else if('Q' == rank){
        return 'J';
    } else if('K' == rank){
        return 'Q';
    } else if ('A' == rank){
        return 'K';
    }
    return '\0'; //Invalid rank received
}

Cardlist::Cardlist()
: printSuite{true}
{}

Cardlist::Cardlist(bool printSuite)
: printSuite{printSuite}
{}

Cardlist::~Cardlist(){}

int Cardlist::length(){
    return list.size();
}

int Cardlist::score(){
    int s = 0;;
    char rank = (*i)->rank
    for(auto i : list){
        if('2' <= rank && rank <= '9'){
            s += rank  - '0';
        } else if('A' == rank){
           s += 1;
        } else if('T' == rank){
            s += 10;
        } else if('J' == rank){
            s += 11;
        } else if('Q' == rank){
            s += 12;
        } else if('K' == rank){
            s += 13;
        }
    }
    return s;
}

void Cardlist::clear(){
    for(Card *i: list){
        delete i;
    }
    list.clear();
}

Card* Cardlist::bottom(){
    return list[0];
}

Card* Cardlist::top(){
    return  list.size()? list[list.size() - 1] : nullptr;
}

void Cardlist::addToTop(Card *c){
    list.push_back(c);
}

void Cardlist::addToBottom(Card* c){
    list.insert(list.begin(), c);
}

void Cardlist::remove(Card *c){
    int length = list.size();
    for(int i = 0; i < length; i++){
        if(c == list[i]){
            list.erase(list.begin()+i);
        }
    }
    /* WHY DOES THIS NOT WORK
    for(auto i = list.begin(); i != list.end(); i++){
        if (*i == c){
            list.erase(i);
        }
    }
    */
}

Card* Cardlist::search(Card* c){
    for(auto i = list.begin(); i != list.end(); i++){
        if (*i == c){
            return *i;
        }
    }
    return nullptr;
}

Card* Cardlist::search(char s, char r){
    for(auto i = list.begin(); i != list.end(); i++){
        if ((*i)->suite == s && (*i)->rank == r){
            return *i;
        }
    }
    return nullptr;
}

Cardlist Cardlist::subset(int b, int e){
    Cardlist tmp;
    if(b < 0 || e <=0){
        return tmp;
    }
    b = (unsigned)b;
    e = (unsigned)e;
    if(b >= list.size() || e > list.size()){
        return tmp;
    }
    for(auto i = list.begin() + b; i != list.begin() + e; i++){
        tmp.addToTop(*i);
    }
    return tmp;
}

Cardlist Cardlist::intersect(Cardlist &&l){
    Cardlist tmp;
    for(auto i = list.begin(); i != list.end(); i++){
        if (l.search(*i)){
            tmp.addToTop(*i);
        }
    }
    return tmp;
}

void Cardlist::shuffle(){
    std::random_shuffle(list.begin(), list.end());
}

Cardlist& Cardlist::operator+=(const Cardlist &c){
    list.insert(list.end(), c.list.begin(), c.list.end());
    return *this;
}

std::ostream & operator<<( std::ostream & out, const Cardlist &c){
    unsigned int width = 1;
    if(c.printSuite){
        for(auto i = c.list.begin(); i != c.list.end(); i++, width++){
            out << (*i)->suite << (*i)->rank << " " 
            << (width % 13 == 0 && width != c.list.size()? "\n" : "");
        }
    } else{
        for(auto i = c.list.begin(); i != c.list.end(); i++, width++){
            out << (*i)->rank << " " 
            << (width % 13 == 0 && width != c.list.size()? "\n" : "");
        }
    }
    
    return out;
}
