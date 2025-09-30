#include "Player.h"
#include "Deck.h"
#include <queue>
using namespace std;

Player::Player(string name){
    this->name = name;
}
Player::Player(){
    
}
void Player::setDeck(queue<Card> d){
    deck = d;
}