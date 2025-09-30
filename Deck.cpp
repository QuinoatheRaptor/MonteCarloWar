#include <iostream>
#include <queue>
#include <string>
#include <cstdlib>
#include <cstdlib>
#include <ctime>
#include "Deck.h"
#include "Player.h"
using namespace std;

Deck::Deck(Player& p1, Player& p2){
    //The deck constructor makes two decks and assigns them both to one of the players
    //So first we need to make a full deck of cards
    Card fullDeck[52];
    int counter = -1;
    for(int i = 1; i <= 4; i++){
        for(int j = 2; j <= 14; j++){
            counter++;
            string name;
            if(j <= 10){
                name = to_string(j);
            }
            else if(j == 11){
                name = "Jack";
            }
            else if(j == 12){
                name = "Queen";
            }
            else if(j == 13){
                name = "King";
            }
            else{
                name = "Ace";
            }
            fullDeck[counter] = Card(j, i, name);
        }
    }
    // for(int i = 0; i < 52; i++){
    //     cout << fullDeck[i].print() + ", ";
    // } Print the deck if necessary
    //Then we shuffle the deck
    srand(time(0));   // seed with current time
    for(int i = 0; i < 52; i++){
        int random = std::rand() % 52;  // random between 0 and 51
        Card temp = fullDeck[i];
        fullDeck[i] = fullDeck[random];
        fullDeck[random] = temp;
    }
    queue<Card> p1deck;
    for(int i = 0; i < 26; i++){
        p1deck.push(fullDeck[i]);
    }
    p1.setDeck(p1deck);
    queue<Card> p2deck;
    for(int i = 26; i < 52; i++){
        p2deck.push(fullDeck[i]);
    }
    p2.setDeck(p2deck);
}


Card::Card(int n, int s, string name){
    number = n;
    suitNum = s;
    this->name = name;
    if(suitNum == 1){
        suit = "Hearts";
    }
    else if(suitNum == 2){
        suit = "Clubs";
    }
    else if(suitNum == 3){
        suit = "Diamonds";
    }
    else{
        suit = "Spades";
    }
}

Card::Card(){

}

string Card::print(){
    return name + " of " + suit;
}