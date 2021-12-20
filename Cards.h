#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

enum Rank { Ace, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King, NullR};
enum Suit { Diamond, Heart, Club, Spade, NullS};

map <string, char> suitMap = { 
	{ "Diamond", 'D' }, { "Club", 'C' }, 
	{ "Heart", 'H' }, { "Spade", 'S' }
};

map <Suit, string> suitToStr = {
	{ Diamond, "Diamond" }, { Heart, "Heart" },
	{ Club, "Club" }, { Spade, "Spade" }
};

map <Rank, string> rankToStr = {
	{ Ace, "Ace" }, { Two, "Two" }, { Three, "Three" }, { Four, "Four" }, 
	{ Five, "Five" }, { Six, "Six" }, { Seven, "Seven" }, { Eight, "Eight" },
	{ Nine, "Nine" }, { Ten, "Ten" }, { Jack, "Jack" }, { Queen, "Queen" },
	{ King, "King" } 
};

map <Rank, char> rankToChar = { 
	// 10 will awkwardly be displayed as 'T' with ->second, but whatever.
	// Just manually deal with it later. idk wtf to do with it right now
	{ Ace, 'A'}, { Two, '2'}, { Three, '3'}, { Four, '4'}, 
	{ Five, '5'}, { Six, '6'}, { Seven, '7'}, { Eight, '8'}, 
	{ Nine, '9'}, { Ten, 'T'}, { Jack, 'J'}, { Queen, 'Q'}, 
	{ King, 'K'} 
};

// For war
map <Rank, int> rankVal = {
	{ Two, 2 }, { Three, 3 }, { Four, 4 }, { Five, 5 }, 
	{ Six, 6 }, { Seven, 7 }, { Eight, 8 }, { Nine, 9 }, 
	{ Ten, 10 }, { Jack, 11 }, { Queen, 12 }, { King, 13 },
	{ Ace, 14 }
};

class Card{
	private:
		Rank rank;
		Suit suit;
		pair<Rank, Suit> rsPair;

	public:
		/* Constructors */
		// Constructor with no parameters
		Card(){
			this->rank = NullR;
			this->suit = NullS;
			this->rsPair = make_pair(rank, suit);
		}
		// Constructor with parameters
		Card(Rank r, Suit s){
			this->rank = r;
			this->suit = s;
			this->rsPair = make_pair(rank, suit);
		}

		/* Setter */
		void setCard(Rank r, Suit s){
			this->rank = r;	
			this->suit = s;
		}

		/* Getters */
		// Get card's rank
		Rank getRank(){
			return this->rank;	
		}

		// Get card's suit
		Suit getSuit(){
			return this->suit;
		}

		// Get both the Card object's rank and suit in a pair<Rank, Suit>
		pair<Rank, Suit> getPair(){
			return make_pair(this->rank, this->suit);
		}

		// Get the Card object's information as text and return it as a string.
		string getInfo(){
			return rankToStr.find(this->rank)->second + " of " + suitToStr.find(this->suit)->second + "s";	
		}

		// Print the Card object's information as text.
		void printInfo(){
			cout << getInfo();
		}

		// Check if two Card Objects have the same Suit and Rank
		bool samePair(Card c){
			if (this->rsPair == c.getPair())
				return true;
			return false;
		}
		// Check if two Card Objects have the same Suit 
		bool sameSuit(Card c){
			if (this->suit == c.getSuit())
				return true;
			return false;
		}
		// Check if two Card Objects have the same Rank
		bool sameRank(Card c){
			if (this->rank == c.getRank())
				return true;
			return false;
		}

		// Directly print of Card objects through output stream with '<<'
		friend ostream& operator<<(ostream& out, Card c);
		// Directly print of Card vectors through output stream with '<<'
		friend ostream& operator<<(ostream& out, vector<Card> cardVect);

		// Append a Card object to a deck with '+='
		friend void operator+=(vector<Card> &cardVect, Card c);

		// Return two Card vectors combined into one.
		// ***Does not modify original vector values.
		friend vector<Card> operator+(vector<Card> a, vector<Card> b);
		// Combine two Card vectors 
		// ***Directly modifies the vector being appended to.
		friend void operator+=(vector<Card> &a, vector<Card> b);

		// Remove the first instance of Card object found in the vector if it exists.
		// ** Directly modifies the vector 
		friend void operator-=(vector<Card> &cardVect, Card c);

		friend string operator-(vector<Card> cardVect, int n);


	
};

void shuffleCards(vector<Card> &cards){
	random_shuffle(begin(cards), end(cards));
}
vector <Card> createDeck(int n=1, bool shuffle=true){ 
	vector <Card> deck;
	// Create deck of cards
	for (int i = 0; i < n; i++){
		for (auto itr = rankToStr.begin(); itr != rankToStr.end(); itr++){
			for (auto its = suitToStr.begin(); its != suitToStr.end(); its++){
				deck.push_back(Card(itr->first,its->first));
			}
		} 
	}
	cout << "Created deck of " << deck.size() << " cards." << endl;
	if (shuffle) shuffleCards(deck);
	return deck;
}

vector<Card> drawCards(vector<Card> &cards, int n=1){
	vector <Card> c;
	int a = 0;
	while (a < n){
		c.push_back(cards.back());
		cards.pop_back();
		a++;
	}
	return c;
}


