#include "Overloads.h"
#include <chrono>
#include <thread>

static const chrono::milliseconds TIME_CONST(500); 

int main(){
	// Not a very good way to generate random numbers but whatever
	srand(time(0)); 

	vector<Card> deck = createDeck();
	vector<Card> hand = drawCards(deck, 5);
	
	vector<Card> hand1 = drawCards(deck);
	/*
	hand1 += hand;
	hand1.push_back(Card(King, Diamond));

	hand1 += Card(Ace, Heart);
	//hand1 = hand + hand1;
	cout << hand1 << endl;

	hand1 -= Card(Ace, Heart);
	cout << hand1 << endl;

	cout << hand1 - 1 << endl;
	*/
	paintCards(hand);
	cout << hand;

	/*
	cout << Card(Ace, Spade).sameRank(Card(Ace, Heart)) << endl;
	cout << Card(Ace, Spade).sameRank(Card(King, Heart)) << endl;

	cout << Card(Ace, Heart).sameSuit(Card(King, Heart)) << endl;
	cout << Card(Ace, Spade).sameSuit(Card(Ace, Heart)) << endl;
	*/
	//drawTest();
	//testProg2();
}

