// Header guards so that headers can be included more than once
#ifndef _CARDS
#define _CARDS

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <random>
#include <chrono>
#include <thread>
#include <algorithm>

using namespace std;


enum Rank { ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, NULLR};
enum Suit { DIAMOND, HEART, CLUB, SPADE, NULLS};

// Clear console output completely
// https://stackoverflow.com/questions/6486289/how-can-i-clear-console
inline void clear() { 
#if defined _WIN32
    system("cls");
    //clrscr(); // including header file : conio.h
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    //std::cout<< u8"\033[2J\033[1;1H"; // This method of clearing lets the user scroll back up to previous output.
    system("clear"); // This method of clearing does not, it actually clears the console output.
#elif defined (__APPLE__)
    system("clear");
#endif
}

inline map <Suit, string> suitToStr = {
	{ DIAMOND, "Diamond" }, { HEART, "Heart" },
	{ CLUB, "Club" }, { SPADE, "Spade" }
};

inline map <Rank, string> rankToStr = {
	{ ACE, "Ace" }, { TWO, "Two" }, { THREE, "Three" }, { FOUR, "Four" }, 
	{ FIVE, "Five" }, { SIX, "Six" }, { SEVEN, "Seven" }, { EIGHT, "Eight" },
	{ NINE, "Nine" }, { TEN, "Ten" }, { JACK, "Jack" }, { QUEEN, "Queen" },
	{ KING, "King" } 
};

inline map <Rank, char> rankToChar = { 
	// 10 will awkwardly be displayed as 'T' with ->second, but whatever.
	// Just manually deal with it later. idk wtf to do with it right now
	{ ACE, 'A'}, { TWO, '2'}, { THREE, '3'}, { FOUR, '4'}, 
	{ FIVE, '5'}, { SIX, '6'}, { SEVEN, '7'}, { EIGHT, '8'}, 
	{ NINE, '9'}, { TEN, 'T'}, { JACK, 'J'}, { QUEEN, 'Q'}, 
	{ KING, 'K'} 
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
			this->rank = NULLR;
			this->suit = NULLS;
			this->rsPair = make_pair(rank, suit);
		}
		// Constructor with Rank and Suit as parameters
		Card(Rank r, Suit s){
			this->rank = r;
			this->suit = s;
			this->rsPair = make_pair(rank, suit);
		}

		/* Setter */
		// Set Rank and Suit
		void setCard(Rank r, Suit s){
			this->rank = r;	
			this->suit = s;
		}

		/* Getters */
		// Get Card object's Rank
		Rank getRank(){
			return this->rank;	
		}

		// Get Card object's suit
		Suit getSuit(){
			return this->suit;
		}

		// Get both the Card object's rank and suit in a pair<Rank, Suit>
		pair<Rank, Suit> getPair(){
			return make_pair(this->rank, this->suit);
		}

		// Get the Card object's Suit and Rank as text and return it as a string.
		string getInfo(){
			return rankToStr.find(this->rank)->second + " of " + suitToStr.find(this->suit)->second + "s";	
		}

		// Print the Card object's Rank and Suit as text.
		void printInfo(){
			cout << getInfo();
		}

		// Returns true if two Card Objects have the same Suit and Rank
		bool samePair(Card c){
			if (this->rsPair == c.getPair())
				return true;
			return false;
		}
		// Returns true if two Card Objects have the same Suit 
		bool sameSuit(Card c){
			if (this->suit == c.getSuit())
				return true;
			return false;
		}
		// Returns true if two Card Objects have the same Rank
		bool sameRank(Card c){
			if (this->rank == c.getRank())
				return true;
			return false;
		}

		/* Overload declarations */
		// Directly print Card objects through output stream with '<<'
		friend ostream& operator<<(ostream& out, Card c);

		// Directly print Card vectors through output stream with '<<'
		friend ostream& operator<<(ostream& out, vector<Card> cardVect);

		// Return a Card object added to a Card vector
		// ** Does not modify original vector
		friend vector<Card> operator+(vector<Card> cardVect, Card c);
		// Reversed
		friend vector<Card> operator+(Card c, vector<Card> cardVect);
		// Return a vector made from 2 card objects
		friend vector<Card> operator+(Card a, Card b);
		// Append a Card object to a deck with '+='
		friend void operator+=(vector<Card> &cardVect, Card c);

		/* Return two Card vectors combined into one.
		 * ***Does not modify original vector
		 */
		friend vector<Card> operator+(vector<Card> a, vector<Card> b);

		/* Combine two Card vectors 
		 * ** Directly modifies the vector
		 */
		friend void operator+=(vector<Card> &a, vector<Card> b);

		/* Remove the first instance of Card object found in the vector if it exists.
		 * ** Directly modifies the vector 
		 */
		friend void operator-=(vector<Card> &cardVect, Card c);

		/* Remove the first instance of all cards in vector b from vector a. 
		 * ** Directly modifies the Card vector
		 */
		friend void operator-=(vector<Card> &a, vector<Card> b);

		/* Return the card Vector, "minus" the card specified. 
		 * Only removes the first instance of the card if multiple exist.
		 * ** Does not directly modify the Card vector
		 */
		friend vector<Card> operator-(vector<Card> cardVect, Card c);
		/* Return the Card vector a, minus all the cards in Card vector b that are found in a.
		 * ** Does not directly modify the Card vector 
		 */
		friend vector<Card> operator-(vector<Card> a, vector<Card> b);
		/* Subtracting an integer from a Card vector will return the painted cards
		 * but with n-cards facedown. 
		 * Example use: 
		 * cout << cardVect-2 << endl;
		 * This will print all cards in cardVect but with 2 facing down.
		 */
		friend string operator-(vector<Card> cardVect, int n);
		/* A single card can be subtracted by a number to display it faced down.
		 * Since a single card is 1 card, this number should be subtracted by 1.
		 * If it's not, it will be automatically assumed as such, and it will be mentioned
		 * if verboseOverloads is true.
		 */
		friend string operator-(Card c, int n);


	
};
/* Note to self: do not declare any parameters (the default ones) in extern functions */
// Draw a single card using ASCII art.
extern string paintSingle(Card c);
// Draws a vector of cards using ASCII art.
extern string paintCards(vector<Card> cardVect, int numDrawn, int facedown);
// Draws a vector of cards using ASCII art, but with the cards stacked on top of each other.
extern string paintStacked(vector<Card> cardVect, int numDrawn, int facedown, bool topRHS);
// Animate deck shuffling
extern void shuffleAnimation(bool verbose);

// Will create and shuffle deck, and output text by default
inline vector <Card> createDeck(int numDecks=1, bool shuffle=true, bool verbose=true){ 
	const chrono::milliseconds FRAME_LENGTH(50); 
	const int FRAMES = 52;
	vector <Card> deck, animDeck;
	// Create deck of cards
	if (verbose)
		cout << "Creating a deck of " << numDecks*52 << " cards..." << endl;
	this_thread::sleep_for(FRAME_LENGTH*10);
	for (int i = 0; i < numDecks; i++){
		for (auto itr = rankToStr.begin(); itr != rankToStr.end(); itr++){
			for (auto its = suitToStr.begin(); its != suitToStr.end(); its++){
				deck.push_back(Card(itr->first,its->first));
				animDeck.push_back(Card(itr->first,its->first));
			}
		} 
	}
	if (verbose) 
		cout << "Deck was created." << endl;
	if (shuffle) {
		random_shuffle(begin(deck), end(deck));
		if (verbose)
			shuffleAnimation(true); 
		else
			shuffleAnimation(false);
	}
	this_thread::sleep_for(FRAME_LENGTH*15);
	
	return deck;
}
// Shuffles the deck of cards
inline void shuffleCards(vector<Card> &cards, bool animate=true, bool verbose=true){
	const chrono::milliseconds FRAME_LENGTH(50); 
	const int FRAMES = 52;
	random_shuffle(begin(cards), end(cards));
	// Shuffling animation
	if (animate){
		if (verbose)
			shuffleAnimation(true);
		else 
			shuffleAnimation(false);
	}
	if (verbose)
		cout << "The cards were shuffled." << endl;
}
inline vector<Card> drawCards(vector<Card> &cardVect, int numDrawn=1, bool verbose=true){
	vector <Card> c;
	int a = 0;
	// Never draw too many cards
	if (numDrawn > cardVect.size()){
		numDrawn = cardVect.size();
	}
	if (cardVect.size() != 0){
		while (a < numDrawn){
			c.push_back(cardVect.back());
			cardVect.pop_back();
			a++;
		}
		if (verbose) cout << "Drew " << numDrawn << " cards from deck." << endl;
	} else {
		if (verbose) cout << "Deck was empty!" << endl;
	}
	return c;
}

#endif