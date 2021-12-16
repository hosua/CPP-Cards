class Card{
	private:
		string rank;
		string suit;
	public:
		/* Getters */
		string getRank();
		string getSuit();
		/* Setter */
		void setCard(string r, string s);
		/* Print format: rank + " of " + suit */
		void print();
}

class CardHandler{
	public:
		/* Create a deck, with multiple n of a standard 52-card deck. */
		vector<Card> createDeck(int n=1); 
		/* Shuffle some vector of cards */
		void shuffleCards(vector<Card> &cards);
		/* Draw n number of cards from a Card vector and return the drawn cards in a vector */
		vector<Card> drawCards(vector<Card> &cards, int n);
}

	
