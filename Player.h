#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <queue>
#include "Deck.h"
using namespace std;

class Player{
    public:
        queue<Card> deck;
        string name;
        Player(string name);
        Player();
        void setDeck(queue<Card> d);
};

#endif