#include <string>
#include <iostream>
#include "Cards.cpp"

using namespace std;

// Ascii art made by ejm98 https://www.asciiart.eu/miscellaneous/playing-cards
int CARD_HEIGHT = 6;
string spadeCard[] = {
" _____ ",
"|Z .  |",
"| /.\\ |",
"|(_._)|",
"|  |  |",
"|____Z|"
}; 
string diamondCard[] = {
" _____ ",
"|Z ^  |",
"| / \\ |",
"| \\ / |",
"|  .  |",
"|____Z|"
};
string clubCard[] = {
" _____ ",
"|Z _  |",
"| ( ) |",
"|(_'_)|",
"|  |  |",
"|____Z|"
};
string heartCard[] = {
" _____ ",
"|Z_ _ |",
"|( v )|",
"| \\ / |",
"|  .  |",
"|____Z|"
};

map<string,string*> drawMap = {
	{"Spade", spadeCard}, 
	{"Diamond", diamondCard},
	{"Club", clubCard}, 
	{"Heart", heartCard}
};

class DrawCard{
public:
	string drawCards(vector<Card> cardVect){ // Draws an array of cards in ASCII
		string outStr;
		for (int i = 0; i < CARD_HEIGHT; i++){
			for (int j = 0; j < cardVect.size(); j++){
				Card c = cardVect[j];
				string cardStr = drawMap.find(c.getSuit())->second[i];
				// 10 will require a special case because it is 2 digits long
				if (c.getRank() != "Ten"){
					char ch = rankMap.find(c.getRank())->second[0]; 				
					replace(cardStr.begin(), cardStr.end(), 'Z', ch);
				}
				outStr += cardStr;
			}	
			outStr += "\n";
		}
		cout << outStr;
		return outStr;
	}

	void drawTest1(){
		for (int i = 0; i < CARD_HEIGHT; i++){
			cout << spadeCard[i] << endl;
		}
		for (int i = 0; i < CARD_HEIGHT; i++){
			cout << heartCard[i] << endl;
		}
		for (int i = 0; i < CARD_HEIGHT; i++){
			cout << diamondCard[i] << endl;
		}
		for ( int i = 0; i < CARD_HEIGHT; i++){
			cout << clubCard[i] << endl;
		}
	}
	void drawTest2(){
		vector<Card> hand;
		Card c1, c2, c3, c4;
		c1.setCard("Ace", "Spade");
		c2.setCard("Ace", "Heart");	
		c3.setCard("Ace", "Diamond");
		c4.setCard("Ace", "Club");
		hand.push_back(c1);
		hand.push_back(c2);
		hand.push_back(c3);
		hand.push_back(c4);
		DrawCard Drawer;
		Drawer.drawCards(hand);
	}

};

int main(){
	DrawCard D;
	D.drawTest2();
}
