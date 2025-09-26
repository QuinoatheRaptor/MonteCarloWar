#include <iostream>
#include <string>
#include "Card.h"
using namespace std;

Card::Card(int n, int s, string name){
    number = n;
    suit = s;
    this->name = name;
}

string print(){
    return name + " of " + suit;
}