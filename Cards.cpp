#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;
/*
map <string, string> rankMap = { 
	{"1", "Ace"}, {"2", "Two"}, {"3", "Three"}, {"4", "Four"}, 
	{"5", "Five"}, {"6", "Six"}, {"7", "Seven"}, {"8", "Eight"}, 
	{"9", "Nine"}, {"10", "Ten"}, {"J", "Jack"}, {"Q", "Queen"}, 
	{"K", "King"} 
};
*/
map <string, string> rankMap = { 
	{"Ace", "A"}, {"Two", "2"}, {"Three", "3"}, {"Four", "4"}, 
	{"Five", "5"}, {"Six", "6"}, {"Seven", "7"}, {"Eight", "8"}, 
	{"Nine", "9"}, {"Ten", "10"}, {"Jack", "J"}, {"Queen", "Q"}, 
	{"King", "K"}
};

map <char, string> suitMap = { 
	{'D', "Diamond"}, {'C', "Club"}, 
	{'H', "Heart"}, {'S', "Spade"}
};


class Card{
private:
	string rank;
	string suit;

public:
	void setCard(string r, string s){
		this->rank = r;	
		this->suit = s;
	}

	string getRank(){
		return this->rank;	
	}

	string getSuit(){
		return this->suit;
	}

	void print(){
		cout << this->rank << " of " << this->suit << "s" << endl;	
	}
};

class CardHandler{
public:
	vector <Card> createDeck(int numDecks=1){ // Each deck is 52 cards
		vector <Card> deck;
		// Create deck of cards
		for (int i = 0; i < numDecks; i++){
			for (auto itr = rankMap.begin(); itr != rankMap.end(); itr++){ for (auto its = suitMap.begin(); its != suitMap.end(); its++){
					Card c;
					c.setCard(itr->first,its->second);
					deck.push_back(c);
				}
			} 
		}
		cout << "Created deck of " << deck.size() << " cards." << endl;
		return deck;
		}

	void shuffleCards(vector<Card> &cards){
		random_shuffle(begin(cards), end(cards));
	}

};

