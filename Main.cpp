#include <iostream>
#include <string>
#include "Deck.h"
#include "Player.h"
using namespace std;

int main() {
  cout << "Welcome to Monte Carlo War!\n";
  Player p1;
  Player p2;
  Deck deck(p1, p2);
  cout << "\n\nFirst deck:\n";
  for(int i = 0; i < 30; i++){
    cout << p1.deck.front().print() + ", ";
    p1.deck.pop();
  }
  cout << "\n\nNext Deck:\n";
  for(int i = 0; i < 30; i++){
    cout << p2.deck.front().print() + ", ";
    p2.deck.pop();
  }
  return 0;
}
