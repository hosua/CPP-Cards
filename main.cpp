#include "overloads.cpp"
#include <chrono>
#include <thread>

static const chrono::milliseconds TIME_CONST(500); 

int main(){
	CardHandler CH;
	// If we ever decide to take this project seriously, we should use a better means
	// of number generation. srand() is not a good way to generate random numbers, but it's good enough
	// for testing.
	srand(time(0)); 
	vector<Card> deck = CH.createDeck();
	vector<Card> hand = CH.drawCards(deck, 5);
	Card c1;
	c1.setCard(Ace, Spade);
	hand.push_back(c1);
	cout << hand << endl;
	
	
	//drawTest();
	//testProg2();
}

