#include "Overloads.h"

static const chrono::milliseconds TIME_CONST(500); 

int main(){
	// Be sure to start your program with this for rng to work properly
	// The seed will be based on the second the program is executed on.
	srand(time(0)); 
	vector<Card> deck = createDeck();
	auto hand1 = drawCards(deck, 5);
	auto hand2 = drawCards(deck, 5);
	cout << hand1 - 2 << endl;

	cout << hand1 + hand2 << endl;
	cout << paintCards(hand1, -1);
	cout << paintStacked(hand1, -1, 1);
	cout << paintStacked(hand1, -1, 1, false);
	//cout << hand;

	// cout << hand << endl;

}

