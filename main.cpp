#include "overloads.cpp"
#include <chrono>
#include <thread>

static const chrono::milliseconds TIME_CONST(500); 

int main(){
	// If we ever decide to take this project seriously, we should use a better means
	// of number generation. srand() is not a good way to generate random numbers, but it's good enough
	// for testing.
	srand(time(0)); 

	vector<Card> deck = createDeck();
	vector<Card> hand = drawCards(deck, 5);
	
	vector<Card> hand1 = drawCards(deck);

	hand1 += hand;
	hand1.push_back(Card(King, Diamond));

	hand1 += Card(Ace, Heart);
	//hand1 = hand + hand1;
	cout << hand1 << endl;

	hand1 -= Card(Ace, Heart);
	cout << hand1 << endl;

	cout << hand1 - 1 << endl;
	

	/*
	cout << Card(Ace, Spade).sameRank(Card(Ace, Heart)) << endl;
	cout << Card(Ace, Spade).sameRank(Card(King, Heart)) << endl;

	cout << Card(Ace, Heart).sameSuit(Card(King, Heart)) << endl;
	cout << Card(Ace, Spade).sameSuit(Card(Ace, Heart)) << endl;
	*/
	//drawTest();
	//testProg2();
}

