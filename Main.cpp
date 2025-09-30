#include <iostream>
#include <string>
#include "Deck.h"
#include "Player.h"
using namespace std;

// void compareCards(Player& p1, Player& p2){//the cards are compared in a method that can be used recursively during wars
//   //cout << to_string(onec) + ", " + to_string(twoc) + "\n";
// }

Player* compareCards(Player& p1, Player& p2){
  cin.get();
  Card p1Card = p1.deck.front();
  cout << p1.name + " plays the " + p1Card.print() + "\n";
  p1.deck.pop();
  Card p2Card = p2.deck.front();
  cout << p2.name + " plays the " + p2Card.print() + "\n";
  p2.deck.pop();
  Player* winner;
  if(p1Card.number > p2Card.number){
    cout << p1.name + " wins!\n";
    p1.deck.push(p1Card);
    p1.deck.push(p2Card);
    winner = &p1;
  }
  else if(p2Card.number > p1Card.number){
    cout << p2.name + " wins!\n";
    p2.deck.push(p2Card);
    p2.deck.push(p1Card);
    winner = &p2;
  }
  else{
    cout << "We have a war!\n";
    winner = compareCards(p1, p2);
    winner->deck.push(p1Card);
    winner->deck.push(p2Card);
  }
  cout << to_string(p1.deck.size()) + ", " + to_string(p2.deck.size()) + "\n";
  return winner;
}

int main() {
  cout << "Welcome to Monte Carlo War!\n";
  string name;
  cout << "Player 1 enter your name: ";
  cin >> name;
  Player p1(name);
  cout << "Player 2 enter your name: ";
  cin >> name;
  Player p2(name);
  Deck deck(p1, p2);

  //The actual gameplay code
  while(!p1.deck.empty() && !p2.deck.empty()){
    compareCards(p1, p2);
  }
  if(p1.deck.empty()){
    cout << p2.name + " wins the game!";
  }
  else{
    cout << p1.name + " wins the game!";
  }
  

  return 0;
}
