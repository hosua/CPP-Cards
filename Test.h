#include "Paint.h"

#include <chrono>
#include <thread>

static const chrono::milliseconds TIME_CONST(500); 

// Draw no stacked
void paintTest1(){
	cout << "Draw test 1" << endl;
	vector<Card> hand;
	for (auto its = suitToStr.begin(); its != suitToStr.end(); its++){
		hand.push_back(Card(Ace, its->first));
		hand.push_back(Card(Ten, its->first));
	}
	paintCards(hand, 6, 4);
}

// Draw stacked, RHS on top with some cards face down
void paintTest2(){
	cout << "Draw test 2 (drawStacked RHS)" << endl;
	vector<Card> hand;
	for (auto its = suitToStr.begin(); its != suitToStr.end(); its++){
		hand.push_back(Card(Ace, its->first));
		hand.push_back(Card(Ten, its->first));
	}
	paintStacked(hand, 6, 4);
}
// Draw stacked, LHS on top, with some cards face down
void paintTest3(){
	cout << "Draw test 3 (drawStacked LHS)" << endl;
	vector<Card> hand;
	Card c1, c2, c3, c4, c5, c6, c7, c8;
	c1.setCard(Ace, Spade); 
	c2.setCard(Ace, Heart);	
	c3.setCard(Ace, Diamond);
	c4.setCard(Ace, Club);
	c5.setCard(Ten, Spade);
	c6.setCard(Ten, Heart);	
	c7.setCard(Ten, Diamond);
	c8.setCard(Ten, Club); 
	hand.push_back(c5);
	hand.push_back(c6);
	hand.push_back(c7);
	hand.push_back(c8);
	hand.push_back(c1);
	hand.push_back(c2);
	hand.push_back(c3);
	hand.push_back(c4);
	paintStacked(hand, 6, 4, false);
}

void testProg1(){
	
	vector <Card> deck = createDeck(1);
	shuffleCards(deck);
	paintCards(deck, 3); // (Card vector, numFacedown, start, end)
	// DH.drawSingle(deck[0]);
}

// Endlessly draw cards and reset deck when insufficient cards are left 
void testProg2(){
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
		if (!dontDraw) paintCards(hand);
		
		
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
		if (!dontDraw && numDrawn > 0) paintStacked(hand, numDrawn, numDown, true);
		if (!dontDraw && numDrawn > 0) paintStacked(hand, numDrawn, numDown, false);
		numDrawn = rand() % NUM_CARDS+1;
		numDown = rand() % numDrawn+1;
		
		this_thread::sleep_for(TIME_CONST);
	}
}
