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

	//hand.push_back(Card(King, Heart));

	vector<Card> hand1 = drawCards(deck, 3);
	cout << hand1+hand << endl;
	
	
	//drawTest();
	//testProg2();
}

