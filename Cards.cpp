#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;
/* // Keeping this just incase I ever decide I wanna flip these around 
map <string, string> rankMap = { 
	{"1", "Ace"}, {"2", "Two"}, {"3", "Three"}, {"4", "Four"}, 
	{"5", "Five"}, {"6", "Six"}, {"7", "Seven"}, {"8", "Eight"}, 
	{"9", "Nine"}, {"10", "Ten"}, {"J", "Jack"}, {"Q", "Queen"}, 
	{"K", "King"} 
};
*/
map <string, char> rankMap = { 
	// 10 will awkwardly be displayed as 'T' with ->second, but whatever.
	// Just manually deal with it later idk wtf to do with it right now
	{"Ace", 'A'}, {"Two", '2'}, {"Three", '3'}, {"Four", '4'}, 
	{"Five", '5'}, {"Six", '6'}, {"Seven", '7'}, {"Eight", '8'}, 
	{"Nine", '9'}, {"Ten", 'T'}, {"Jack", 'J'}, {"Queen", 'Q'}, 
	{"King", 'K'} 
};

map <string, char> suitMap = { 
	{"Diamond", 'D'}, {"Club", 'C'}, 
	{"Heart", 'H'}, {"Spade", 'S'}
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
		vector <Card> createDeck(int n=1){ 
			vector <Card> deck;
			// Create deck of cards
			for (int i = 0; i < n; i++){
				for (auto itr = rankMap.begin(); itr != rankMap.end(); itr++){ for (auto its = suitMap.begin(); its != suitMap.end(); its++){
						Card c;
						c.setCard(itr->first,its->first);
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

