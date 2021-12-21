// This file and main.cpp should be compiled separately. This file has its own main function.

#include "../Overloads.h"
#include <chrono>
#include <thread>

static const chrono::milliseconds TIME_CONST(500); 

// Draw cards not stacked
void paintTest1(){
	cout << "Paint test 1 (not stacked)" << endl;
	vector<Card> hand;
	for (auto its = suitToStr.begin(); its != suitToStr.end(); its++){
		hand.push_back(Card(Ace, its->first));
		hand.push_back(Card(Ten, its->first));
	}
	cout << paintCards(hand, 6, 4);
}

// Paint cards stacked, RHS on top with some cards face down
void paintTest2(){
	cout << "Paint test 2 (paintStacked RHS)" << endl;
	vector<Card> hand;
	for (auto its = suitToStr.begin(); its != suitToStr.end(); its++){
		hand.push_back(Card(Ace, its->first));
		hand.push_back(Card(Ten, its->first));
	}
	cout << paintStacked(hand, 6, 4);
}
// Paint cards stacked, LHS on top, with some cards face down
void paintTest3(){
	cout << "Paint test 3 (paintStacked LHS)" << endl;
	vector<Card> hand;
	for (auto its = suitToStr.begin(); its != suitToStr.end(); its++){
		hand.push_back(Card(Ace, its->first));
		hand.push_back(Card(Ten, its->first));
	}
	cout << paintStacked(hand, 6, 4, false);
}
void paintTest(){
	paintTest1();
	paintTest2();
	paintTest3();
}
void testProg1(){
	vector <Card> deck = createDeck(1);
	shuffleCards(deck);
	cout << paintCards(deck, 3); // (Card vector, numFacedown, start, end)
}

// Endlessly draw cards and reset deck when insufficient cards are left 
void testProg2(){
	int NUM_DECKS = 1;

	vector <Card> deck = createDeck(NUM_DECKS);
	vector <Card> hand;
	shuffleCards(deck);
	int NUM_CARDS = 5;
	bool dontPaint;
	while (true){ 
		dontPaint = false;
		cout << "Size: " << deck.size() << endl;
		if (deck.size() < NUM_CARDS && deck.size() != 0){
			hand = drawCards(deck, deck.size());
			cout << "Drew " << deck.size() << " cards." << endl;
		} else if (deck.size() == 0){
			deck = createDeck(NUM_DECKS);
			dontPaint = true;
		} else {
			hand = drawCards(deck, NUM_CARDS);
			cout << "Drew " << NUM_CARDS << " cards." << endl;
		}
		if (!dontPaint) cout << hand << endl;
		
		
		this_thread::sleep_for(TIME_CONST);
	}
}


void testProg3(){ 	
	int NUM_DECKS = 6;

	vector <Card> deck = createDeck(NUM_DECKS);
	vector <Card> hand;
	int NUM_CARDS = 10;
	// Do not forget to do +1 to omit cases when we have 0, otherwise we will get
	// Floating point errors.
	int numDrawn = rand() % NUM_CARDS+1;
	int numDown = rand() % numDrawn+1;
	bool dontPaint;
	while (true){ 
		dontPaint = false;
		cout << "Cards remaining: " << deck.size() << endl;
		if (deck.size() < NUM_CARDS && deck.size() != 0){
			hand = drawCards(deck, deck.size());
			cout << hand << endl;
		} else if (deck.size() == 0){
			deck = createDeck(NUM_DECKS);
			dontPaint = true;
		} else {
			hand = drawCards(deck, numDrawn);
		}
		cout << "numDown: " << numDown << endl;
		if (!dontPaint && numDrawn > 0) cout << paintStacked(hand, numDrawn, numDown, false);
		numDrawn = rand() % NUM_CARDS+1;
		numDown = rand() % numDrawn+1;
		
		this_thread::sleep_for(TIME_CONST);
	}
}

int main(){
	paintTest();
	//testProg1();
	//testProg2();	
	//testProg3();
	
}
