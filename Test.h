#include "Draw.h"

#include <chrono>
#include <thread>

static const chrono::milliseconds TIME_CONST(500); 

void testProg1(){
	DrawHandler DH;
	
	vector <Card> deck = createDeck(1);
	shuffleCards(deck);
	DH.drawCards(deck, 3); // (Card vector, numFacedown, start, end)
	// DH.drawSingle(deck[0]);
}

// Endlessly draw cards and reset deck when insufficient cards are left 
void testProg2(){
	DrawHandler DH;
	int NUM_DECKS = 1;

	vector <Card> deck = createDeck(NUM_DECKS);
	vector <Card> hand;
	shuffleCards(deck);
	int NUM_CARDS = 5;
	bool dontDraw;
	while (true){ 
		dontDraw = false;
		cout << "Size: " << deck.size() << endl;
		if (deck.size() < NUM_CARDS && deck.size() != 0){
			hand = drawCards(deck, deck.size());
			cout << "Drew " << deck.size() << " cards." << endl;
		} else if (deck.size() == 0){
			deck = createDeck(NUM_DECKS);
			dontDraw = true;
		} else {
			hand = drawCards(deck, NUM_CARDS);
			cout << "Drew " << NUM_CARDS << " cards." << endl;
		}
		if (!dontDraw) DH.drawCards(hand);
		
		
		this_thread::sleep_for(TIME_CONST);
	}
}


void testProg3(){ 	
	DrawHandler DH;
	int NUM_DECKS = 6;

	vector <Card> deck = createDeck(NUM_DECKS);
	vector <Card> hand;
	int NUM_CARDS = 10;
	// Do not forget to do +1 to omit cases when we have 0, otherwise we will get
	// Floating point errors.
	int numDrawn = rand() % NUM_CARDS+1;
	int numDown = rand() % numDrawn+1;
	bool dontDraw;
	while (true){ 
		dontDraw = false;
		cout << "Size: " << deck.size() << endl;
		if (deck.size() < NUM_CARDS && deck.size() != 0){
			hand = drawCards(deck, deck.size());
			cout << "Drew " << deck.size() << " cards." << endl;
		} else if (deck.size() == 0){
			deck = createDeck(NUM_DECKS);
			dontDraw = true;
		} else {
			hand = drawCards(deck, numDrawn);
			cout << "Drew " << numDrawn << " cards." << endl;
		}
		if (!dontDraw && numDrawn > 0) DH.drawStacked(hand, numDrawn, numDown, true);
		if (!dontDraw && numDrawn > 0) DH.drawStacked(hand, numDrawn, numDown, false);
		numDrawn = rand() % NUM_CARDS+1;
		numDown = rand() % numDrawn+1;
		
		this_thread::sleep_for(TIME_CONST);
	}
}
