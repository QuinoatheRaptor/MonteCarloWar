#include <iostream>
#include <string>
#include <queue>
#include "Deck.h"
#include "Player.h"
using namespace std;

int getBets(Player& lowerSuit, Player& higherSuit){
  int raise;
  cout << lowerSuit.name + ", enter your bet: ";
  cin >> raise;
  while(raise <= 0 || raise > lowerSuit.deck.size() || raise > higherSuit.deck.size()){
    cout << "Your bet must be greater than 0 and less than or equal to the number of cards either player has left. Enter a new bet: ";
    cin >> raise;
  }
  lowerSuit.bet += raise;
  while(higherSuit.bet != lowerSuit.bet){
    while(higherSuit.bet < lowerSuit.bet && raise != 0){
      cout << higherSuit.name + ", you must raise until you match or surpass " + lowerSuit.name + "'s bet or enter 0 to fold. Your current bet is " + to_string(higherSuit.bet) + ". How much do you want to raise your bet by? ";
      cin >> raise;
      while(higherSuit.bet + raise > higherSuit.deck.size() || higherSuit.bet + raise > lowerSuit.deck.size()){
        cout << "Your bet has exceeded a player's deck size. Please enter a lower bet: ";
        cin >> raise;
      }
      while(raise < 0){
        cout << "Your bet cannot be negative. Try again: ";
        cin >> raise;
      }
      higherSuit.bet += raise;
    }
    if(raise == 0){
      return -1;
    }
    while(lowerSuit.bet < higherSuit.bet && raise != 0){
      cout << lowerSuit.name + ", you must raise until you match or surpass " + higherSuit.name + "'s bet or enter 0 to fold. Your current bet is " + to_string(lowerSuit.bet) + ". How much do you want to raise your bet by? ";
      cin >> raise;
      while(lowerSuit.bet + raise > higherSuit.deck.size() || lowerSuit.bet + raise > lowerSuit.deck.size()){
        cout << "Your bet has exceeded a player's deck size. Please enter a lower bet: ";
        cin >> raise;
      }
      while(raise < 0){
        cout << "Your bet cannot be negative. Try again: ";
        cin >> raise;
      }
      lowerSuit.bet += raise;
    }
    if(raise == 0){
      return -1;
    }
  }
  return higherSuit.bet;
}

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
    int bet = 0;
    if(p1Card.suitNum > p2Card.suitNum){
      bet = getBets(p2, p1);
    }
    else{
      bet = getBets(p1, p2);
    }
    if(bet < 0){
      if(p1.bet < p2.bet){
        winner = &p2;
        for(int i = 0; i < p1.bet; i++){
          p2.deck.push(p1.deck.front());
          p1.deck.pop();
        }
      }
      else{
        winner = &p1;
        for(int i = 0; i < p2.bet; i++){
          p1.deck.push(p2.deck.front());
          p2.deck.pop();
        }
      }
    }
    else{
      winner = compareCards(p1, p2);
      if(winner == &p1){
        for(int i = 0; i < p2.bet; i++){
          p1.deck.push(p2.deck.front());
          p2.deck.pop();
        }
      }
      else{
        for(int i = 0; i < p1.bet; i++){
          p2.deck.push(p1.deck.front());
          p1.deck.pop();
        }
      }
    }
    p1.bet = 0;
    p2.bet = 0;
    //Pseudocode for placing bets:
    //The player with the worse suit bets first
    //Second player must match, raise or fold
    //This continues in loop until someone matches or folds
    //Each player:
    //Pop top card (card for war)
    //Pop bet and add to array
    //Compare war cards
    //Winner takes pot 
    winner->deck.push(p1Card);
    winner->deck.push(p2Card);//These are the war cards so their values are the same
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




