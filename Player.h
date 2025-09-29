#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <queue>
#include "Deck.h"
using namespace std;

class Player{
    public:
        queue<Card> deck;
        Player();
        void setDeck(queue<Card> d);
};

#endif