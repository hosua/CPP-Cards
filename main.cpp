#include "Draw.cpp"
/* For sleeping, if I end up using it */
#include <chrono>
#include <thread> 

/* Some time to sleep for. We'll just set it to 1 second because why wouldn't I */
static const chrono::milliseconds TIME_CONST(1000); 

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
	CH.shuffleCards(deck);
	int NUM_CARDS = 5;
	// Endlessly draw cards and reset deck when insufficient cards are left 
	while (true){ 
		int remaining = deck.size() - NUM_CARDS;
		// cout << "d: " << deck.size() << " s: " << NUM_CARDS << endl;
		cout << "Cards remaining: " << remaining << endl;

		// If we don't have enough cards remaining, draw the remaining
		if (remaining <= 0){
			CH.drawCards(deck, remaining);
			// Create & shuffle
			deck = CH.createDeck(NUM_DECKS);
			CH.shuffleCards(deck);
		// Otherwise, draw NUM_CARDS.
		} else {
			vector<Card> hand = CH.drawCards(deck, NUM_CARDS);
			cout << "2" << endl; 
			DH.drawCards(hand, NUM_CARDS);
		}
		this_thread::sleep_for(TIME_CONST);
	}

}


int main(){
	srand(time(0)); // Always start program with this to set RNG seed based on the time
	testProg2();

}

