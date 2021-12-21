#include "Overloads.h"

static const chrono::milliseconds TIME_CONST(500); 

int main(){
	// Not a very good way to generate random numbers but whatever
	srand(time(0)); 

	auto deck = createDeck();
	shuffleCards(deck);

}

