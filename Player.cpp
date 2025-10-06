#include "Player.h"
#include "Deck.h"
#include <queue>
using namespace std;

Player::Player(string name){
    this->name = name;
    bet = 0;
}
Player::Player(){
    bet = 0;
}
void Player::setDeck(queue<Card> d){
    deck = d;
}