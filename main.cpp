#include "Draw.cpp"
/* For sleeping, if I end up using it */
#include <chrono>
#include <thread> 

/* Some time to sleep for. We'll just set it to 1 second because why wouldn't I */
//static const chrono::milliseconds TIME_CONST(1000); 
static const chrono::milliseconds TIME_CONST(500); 
void testProg1(){
	CardHandler CH;
	DrawHandler DH;
	
	vector <Card> deck = CH.createDeck(1);
	CH.shuffleCards(deck);
	DH.drawCards(deck, 3); // (Card vector, numFacedown, start, end)
	// DH.drawSingle(deck[0]);
}

void testProg2(){
	CardHandler CH;
	DrawHandler DH;
	int NUM_DECKS = 1;

	vector <Card> deck = CH.createDeck(NUM_DECKS);
	vector <Card> hand;
	CH.shuffleCards(deck);
	int NUM_CARDS = 5;
	// Endlessly draw cards and reset deck when insufficient cards are left 
	while (true){ 
		cout << "Size: " << deck.size() << endl;
		if (deck.size() < NUM_CARDS && deck.size() != 0){
			cout << "Drawing " << deck.size() << " cards." << endl;
			hand = CH.drawCards(deck, deck.size());
		} else if (deck.size() == 0){
			deck = CH.createDeck(NUM_DECKS);
		
		} else {
			hand = CH.drawCards(deck, NUM_CARDS);
			cout << "Drew " << NUM_CARDS << " cards." << endl;
		}
		DH.drawCards(hand);
		
		this_thread::sleep_for(TIME_CONST);
	}

}


int main(){
	srand(time(0)); // Always start program with this to set RNG seed based on the time
	testProg2();

}

