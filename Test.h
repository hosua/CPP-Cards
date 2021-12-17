#include "Draw.h"

#include <chrono>
#include <thread>

static const chrono::milliseconds TIME_CONST(500); 

void testProg1(){
	CardHandler CH;
	DrawHandler DH;
	
	vector <Card> deck = CH.createDeck(1);
	CH.shuffleCards(deck);
	DH.drawCards(deck, 3); // (Card vector, numFacedown, start, end)
	// DH.drawSingle(deck[0]);
}

// Endlessly draw cards and reset deck when insufficient cards are left 
void testProg2(){
	CardHandler CH;
	DrawHandler DH;
	int NUM_DECKS = 1;

	vector <Card> deck = CH.createDeck(NUM_DECKS);
	vector <Card> hand;
	CH.shuffleCards(deck);
	int NUM_CARDS = 5;
	bool dontDraw;
	while (true){ 
		dontDraw = false;
		cout << "Size: " << deck.size() << endl;
		if (deck.size() < NUM_CARDS && deck.size() != 0){
			hand = CH.drawCards(deck, deck.size());
			cout << "Drew " << deck.size() << " cards." << endl;
		} else if (deck.size() == 0){
			deck = CH.createDeck(NUM_DECKS);
			dontDraw = true;
		} else {
			hand = CH.drawCards(deck, NUM_CARDS);
			cout << "Drew " << NUM_CARDS << " cards." << endl;
		}
		if (!dontDraw) DH.drawCards(hand);
		
		
		this_thread::sleep_for(TIME_CONST);
	}
}

