#include <string>
#include <iostream>
#include "Cards.h"

using namespace std;

// Ascii art made by ejm98 https://www.asciiart.eu/miscellaneous/playing-cards
static const int CARD_HEIGHT = 6;
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
string facedownCard[] = {
" _____ ",
"|\\\\~//|",
"|}}:{{|",
"|}}:{{|",
"|}}:{{|",
"|//~\\\\|"
};

map<Suit,string*> drawMap = {
	{Spade, spadeCard}, 
	{Diamond, diamondCard},
	{Club, clubCard}, 
	{Heart, heartCard}
};

class DrawHandler{

	public:
		void drawCards(vector<Card> cardVect, int numCards=-1, int faceDown=0){ // Draws an array of cards in ASCII
			string outStr;
			// By default numCards will just be the vector size
			if (numCards == -1) numCards = cardVect.size(); 		
			for (int i = 0; i < CARD_HEIGHT; i++){
				for (int j = 0; j < numCards-faceDown; j++){
					Card c = cardVect[j];
					string cardStr = drawMap.find(c.getSuit())->second[i];
					char ch;
					if (c.getRank() != Ten){
						ch = rankToChar.find(c.getRank())->second;
						replace(cardStr.begin(), cardStr.end(), 'Z', ch);
					} else {
						// 10 will require a special case because its length is 2.
						if (i == 1){
							if (c.getSuit() == Spade){
								cardStr = "10 .  |";
							} 
							if (c.getSuit() == Diamond){
								cardStr = "10 ^  |";
							}
							if (c.getSuit() == Club){
								cardStr = "10 _  |";
							}
							if (c.getSuit() == Heart){
								cardStr = "10_ _ |";
							}
						}
						if (i == 5){
							cardStr = "|___10|";
						}
					}
					outStr += cardStr;
				}
				for (int j = 0; j < faceDown; j++){
					outStr += facedownCard[i];
				}
				outStr += "\n";
			}		
			cout << outStr;
	}

	// Incase only drawing a single, non vector Card
	void drawSingle(Card c){
		string outStr, cardStr;
		for (int i = 0; i < CARD_HEIGHT; i++){
			cardStr = drawMap.find(c.getSuit())->second[i];
			if (i == 1){
				if (c.getSuit() == Spade){
					cardStr = "10 .  |";
				} 
				if (c.getSuit() == Diamond){
					cardStr = "10 ^  |";
				}
				if (c.getSuit() == Club){
					cardStr = "10 _  |";
				}
				if (c.getSuit() == Heart){
					cardStr = "10_ _ |";
				}
			}
			if (i == 5){
				cardStr = "|___10|";
			}
			outStr += cardStr + "\n";
		}
		cout << outStr << endl;
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
		Card c1, c2, c3, c4, c5, c6, c7, c8;
		c1.setCard(Ace, Spade); 
		c2.setCard(Ace, Heart);	
		c3.setCard(Ace, Diamond);
		c4.setCard(Ace, Club);
		c5.setCard(Ten, Spade);
		c6.setCard(Ten, Heart);	
		c7.setCard(Ten, Diamond);
		c8.setCard(Ten, Club); 
		hand.push_back(c1);
		hand.push_back(c2);
		hand.push_back(c3);
		hand.push_back(c4);
		hand.push_back(c5);
		hand.push_back(c6);
		hand.push_back(c7);
		hand.push_back(c8);
		DrawHandler Drawer;
		Drawer.drawCards(hand);
	}
	

};

