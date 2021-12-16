#include "Cards.cpp"

int main(){
	srand(time(0)); // Set RNG seed
	vector <Card> cards;

	// Create deck of cards
	Card c1; 
	for (auto itr = rankMap.begin(); itr != rankMap.end(); itr++){ for (auto its = suitMap.begin(); its != suitMap.end(); its++){
			Card c;
			c.setCard(itr->second,its->second);
			cards.push_back(c);
		}
	} 
	random_shuffle(begin(cards), end(cards));

	// cout << "Deck size: " << cards.size() << endl;
	for (int i = 0; i < cards.size(); i++){
		cards[i].print();
	}
}

