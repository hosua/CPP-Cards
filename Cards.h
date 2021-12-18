#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

enum Rank { Ace, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King};
enum Suit { Diamond, Heart, Club, Spade };

map <string, char> suitMap = { 
	{"Diamond", 'D'}, {"Club", 'C'}, 
	{"Heart", 'H'}, {"Spade", 'S'}
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
	{ Ace, 'A'}, { Two, '2'}, { Three, '3'}, {Four, '4'}, 
	{ Five, '5'}, { Six, '6'}, { Seven, '7'}, {Eight, '8'}, 
	{ Nine, '9'}, { Ten, 'T'}, {Jack, 'J'}, {Queen, 'Q'}, 
	{ King, 'K'} 
};

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

	public:
		void setCard(Rank r, Suit s){
			this->rank = r;	
			this->suit = s;
		}

		Rank getRank(){
			return this->rank;	
		}

		Suit getSuit(){
			return this->suit;
		}

		void print(){
			cout << rankToStr.find(this->rank)->second << " of " << this->suit << "s" << endl;	
		}
};

class CardHandler{
	public:
		void shuffleCards(vector<Card> &cards){
			random_shuffle(begin(cards), end(cards));
		}

		vector <Card> createDeck(int n=1, bool shuffle=true){ 
			vector <Card> deck;
			Card c;
			// Create deck of cards
			for (int i = 0; i < n; i++){
				for (auto itr = rankToStr.begin(); itr != rankToStr.end(); itr++){
					for (auto its = suitToStr.begin(); its != suitToStr.end(); its++){
						c.setCard(itr->first, its->first);
						deck.push_back(c);
					}
				} 
			}
			cout << "Created deck of " << deck.size() << " cards." << endl;
			if (shuffle) shuffleCards(deck);
			return deck;
			}

		vector<Card> drawCards(vector<Card> &cards, int n){
			vector <Card> c;
			int a = 0;
			while (a < n){
				c.push_back(cards.back());
				cards.pop_back();
				a++;
			}
			return c;
		}

};

