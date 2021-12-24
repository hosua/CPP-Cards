#include "Overloads.h"

static const chrono::milliseconds TIME_CONST(500); 

int main(){
	// Be sure to start your program with this for rng to work properly
	// The seed will be based on the second the program is executed on.
	srand(time(0)); 
	vector<Card> deck = createDeck(1, false);	
	shuffleCards(deck, false, true);
	auto hand1 = drawCards(deck, 5);
	auto hand2 = drawCards(deck, 5);

	cout << Card(King, Diamond) + Card(Ace, Spade);

	for (int i = 0; i < hand1.size(); i++)
		cout << hand1[i].getInfo() << " " << endl;
	cout << endl;
	hand1 -= Card(King, Diamond);
	// cout << hand1;
	cout << paintSingle(hand1[0]);
	//cout << hand;

	// cout << hand << endl;

}

