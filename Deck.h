#include <string>
//#include "Player.h"
//#include <queue>
//using namespace std;
#ifndef DECK_H
#define DECK_H

class Player;

class Deck{
    public:
        //queue<Card> cards;
        Deck(Player& p1, Player& p2);
        void print();
};

class Card {
    public:
        int number;
        int suitNum;//1 - Hearts, 2 - Clubs, 3 - Diamonds, 4 - Spades
        std::string name;
        std::string suit;
        Card(int n, int s, std::string name);
        Card();
        std::string print();
        //int compareTo(Card other);
};

#endif