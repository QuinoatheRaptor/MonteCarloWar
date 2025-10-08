# Monte Carlo War
A C++ program that simulates a spin on classic card game War by introducing a betting aspect during wars.

## Features
The code creates a deck of cards and evenly divides it among the two players. Each player has their own deck which is a queue so that cards can be added and drawn easily. It then simulates rounds of war by popping the top card of each player's deck and comparing them. The method is recursive so that in the event of a war a secondary (or more) round can be played by drawing and comparing more cards.

The code also has several methods to manage the process of collecting player's bets during a war. These methods ensure that players make a bet equal to or greater than opposing player's bet, or that the bet is zero if a player chooses to fold. The methods also ensure that players don't make bets beyond the size of either player's deck.

## Usage
The game is entirely text-based. When the code is run an explanation of the rules pops up. Afterwards, both players enter their names and then the game begins. Every round the code prints each player's card, which player won the round, and how many cards each player has remaining in their deck. In the event of a war, the player with the lower suit (the hierarchy being Hearts, Clubs, Diamonds, Spades) makes their bet first. Then the other player has the option to match or raise their bet, or to fold in which case they automatically lose the war. Once the players' bets match, a second round of cards is played. It's worth noting that the card used in this second round is not the card after all the bet cards have been drawn but rather the card before it (from the top of the deck). Whichever player has the higher card captures both player's bets. More information about usage is given in the instructions printed at the start of the code.
