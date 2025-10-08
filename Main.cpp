#include <iostream>
#include <string>
#include <queue>
#include <limits>
#include "Deck.h"
#include "Player.h"
using namespace std;

struct RoundResult {
  Player* winner;
  Player* loser;
};

int verifyBets(Player& bettor, Player& other){
  int raise = 0;
  do{
    cout << bettor.name + ", you must raise until you match or surpass " + other.name + "'s bet or enter 0 to fold. Your current bet is " + to_string(bettor.bet) + ". How much do you want to raise your bet by? ";
    cin >> raise;
    while(bettor.bet + raise > bettor.deck.size() - 1 || bettor.bet + raise > other.deck.size() - 1){
      cout << "Your bet has exceeded a player's deck size. Please enter a lower bet: ";
      cin >> raise;
    }
    while(raise < 0){
      cout << "Your bet cannot be negative. Try again: ";
      cin >> raise;
    }
  } while(bettor.bet + raise < other.bet && raise != 0);
  return raise;
}

int getBets(Player& lowerSuit, Player& higherSuit){
  int raise;
  cout << lowerSuit.name + ", enter your bet: ";
  cin >> raise;
  while(raise <= 0 || raise > lowerSuit.deck.size() - 1 || raise > higherSuit.deck.size() - 1){
    cout << "Your bet must be greater than 0 and cannot empty a player's deck (one card must remain to settle the war). Enter a new bet: ";
    cin >> raise;
  }
  lowerSuit.bet += raise;
  while(higherSuit.bet != lowerSuit.bet){
    raise = verifyBets(higherSuit, lowerSuit);
    higherSuit.bet += raise;
    if(raise == 0){
      return -1;
    }
    if(higherSuit.bet == lowerSuit.bet){
      break;
    }
    raise = verifyBets(lowerSuit, higherSuit);
    lowerSuit.bet += raise;
    if(raise == 0){
      return -1;
    }
  }
  return higherSuit.bet;
}


RoundResult compareCards(Player& p1, Player& p2, bool war){
  cin.get();
  Card p1Card = p1.deck.front();
  cout << p1.name + " plays the " + p1Card.print() + "\n";
  p1.deck.pop();
  Card p2Card = p2.deck.front();
  cout << p2.name + " plays the " + p2Card.print() + "\n";
  p2.deck.pop();
  RoundResult result;
  if(p1Card.number > p2Card.number){
    cout << p1.name + " wins!\n";
    p1.deck.push(p1Card);
    p1.deck.push(p2Card);
    result.winner = &p1;
    result.loser = &p2;
  }
  else if(p2Card.number > p1Card.number){
    cout << p2.name + " wins!\n";
    p2.deck.push(p2Card);
    p2.deck.push(p1Card);
    result.winner = &p2;
    result.loser = &p1;
  }
  else if(p1.deck.size() <= 1 || p2.deck.size() <= 1){//the very niche situation where a player's last or second to last card is a war. In this case, they immediately lose due to an inability to make a bet and resolve the war
    result.winner = (p1.deck.empty()) ? &p2 : &p1;
    result.loser = (p2.deck.empty()) ? &p2 : &p1;
    cout << result.loser->name + " doesn't have enough cards to play the war. Therefore they automatically lose the game.\n";
    result.winner->deck.push(p1Card);
    result.winner->deck.push(p2Card);//order is irrelevant bc the game is over
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
    if(bet < 0 && p1.bet < p2.bet){
      result.winner = &p2;
      result.loser = &p1;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');//fixing bug where code jumped to next round after somebody folded
    }
    else if(bet < 0){
      result.winner = &p1;
      result.loser = &p2;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');//fixing bug where code jumped to next round after somebody folded
      //cin.get();
    }
    else{
      result = compareCards(p1, p2, true);
      //cin.get();
    }
    for(int i = 0; i < result.winner->bet; i++){
      result.winner->deck.push(result.winner->deck.front());
      result.winner->deck.pop();
    }
    for(int i = 0; i < result.loser->bet; i++){
      result.winner->deck.push(result.loser->deck.front());
      result.loser->deck.pop();
    }
    p1.bet = 0;
    p2.bet = 0;
    result.winner->deck.push(p1Card);
    result.winner->deck.push(p2Card);//These are the war cards so their values are the same, therefore adding order doesn't matter
  }
  if(!war){cout << p1.name << "'s deck size: " << p1.deck.size() << "\n";
    cout << p2.name << "'s deck size: " << p2.deck.size()<< "\n";}
  return result;
}

int main() {
  cout << "Welcome to Monte Carlo War!\n";
  cout << "This is a card game very similar to the classic card game War with one major difference. During a war, both players place a bet of cards. Whoever wins the war (played with the next card off the deck, before drawing your bet) takes the other player's bet. Players also have the option to fold to avoid losing more cards. If a player folds they lose automatically and their top card that would decide the war is returned to the top of their deck.\n\n";
  cout << "One strategy can be counting cards to figure out your chances at winning a war. To aid you in this end, it's helpful to know that cards are returned to the deck in the following order:\n";
  cout << "1. The cards that decide the war, with the higher card being returned first (this is also true of a round without a war)\n";
  cout << "2. The winning player's bet\n";
  cout << "3. The losing player's bet\n";
  cout << "4. The two equal cards that initiated the war\n\n";
  cout << "That's all you need to know. Let's begin!\n";
  string name;
  cout << "Player 1 enter your name: ";
  cin >> name;
  Player p1(name);
  cout << "Player 2 enter your name: ";
  cin >> name;
  Player p2(name);
  Deck deck(p1, p2);

  //The actual gameplay code
  int roundCount = 1;
  while(!p1.deck.empty() && !p2.deck.empty()){
    compareCards(p1, p2, false);
  }
  if(p1.deck.empty()){
    cout << p2.name + " wins the game!";
  }
  else{
    cout << p1.name + " wins the game!";
  }
  
  return 0;
}




