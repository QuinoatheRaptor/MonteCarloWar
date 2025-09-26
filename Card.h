#include <string>
#ifndef CARD_H
#define CARD_H

class Card {
    public:
        int number;
        int suit;//1 - Hearts, 2 - Clubs, 3 - Diamonds, 4 - Spades
        std::string name;
        Card(int n, int s, std::string name);
        std::string print();
        //int compareTo(Card other);
};

#endif