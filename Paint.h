// Ascii art made by ejm98 https://www.asciiart.eu/miscellaneous/playing-cards
#include <string>
#include <iostream>
#include "Cards.h"

using namespace std;

// The number of elements in the string arrays
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


// Draws an array of cards in ASCII
// Cards are fully displayed and not on top of each other.
string paintCards(vector<Card> cardVect, int numDrawn=-1, int facedown=0){ 			
	// Bound checks
	if (numDrawn < 0 || numDrawn > cardVect.size()) numDrawn = cardVect.size(); 		
	if (facedown < 0) facedown = 0;
	if (facedown > cardVect.size()) facedown = cardVect.size();
	string outStr;
	// By default numDrawn will just be the vector size
	if (numDrawn == -1) numDrawn = cardVect.size(); 		
	for (int i = 0; i < CARD_HEIGHT; i++){
		for (int j = 0; j < numDrawn-facedown; j++){
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
						cardStr = "|10.  |";
					} 
					if (c.getSuit() == Diamond){
						cardStr = "|10^  |";
					}
					if (c.getSuit() == Club){
						cardStr = "|10_  |";
					}
					if (c.getSuit() == Heart){
						cardStr = "|10 _ |";
					}
				}
				if (i == 5){
					cardStr = "|___10|";
				}
			}
			outStr += cardStr;
		}
		for (int j = 0; j < facedown; j++){
			outStr += facedownCard[i];
		}
		outStr += "\n";
	}		
	//cout << outStr << endl;
	return outStr;
}
// Won't display any face down cards.
// Like drawCards, except the cards will be drawn as if they are on top of each other.
// topRHS=true will mean that the top card of the card vector will be on the right side.
string paintStacked(vector<Card> cardVect, int numDrawn=-1, int facedown=0, bool topRHS=true){ // Draws an array of cards in ASCII
	// Bound checks
	if (numDrawn < 0 || numDrawn > cardVect.size()) numDrawn = cardVect.size(); 		
	if (facedown < 0) facedown = 0;
	if (facedown > cardVect.size()) facedown = cardVect.size();
	if (facedown > numDrawn) facedown = numDrawn;
	string outStr, cardStr;
	Card c;
	char ch;
	// Right orientation
	if (topRHS){
		for (int i = 0; i < CARD_HEIGHT; i++){
			for (int j = 0; j < facedown; j++){
				outStr += facedownCard[i].substr(0,3);
			}
			for (int j = 0; j < numDrawn-facedown; j++){
				c = cardVect[j];
				cardStr = drawMap.find(c.getSuit())->second[i];
				cardStr = cardStr.substr(0,3);
				// 10 will require a special case because its length is 2.
				if (c.getRank() != Ten){
					ch = rankToChar.find(c.getRank())->second;
					replace(cardStr.begin(), cardStr.end(), 'Z', ch);
				} else {
					if (i == 1){
						cardStr = "|10";
					}
					if (i == 5){
						cardStr = "|__";
					}

				}
				outStr += cardStr;
			}
			// Draw the last card 
			c = cardVect[numDrawn-1-facedown];
			// Make sure we actually have any cards to draw
			if (numDrawn != 0){
				if (facedown == cardVect.size() || facedown == numDrawn)
					cardStr = facedownCard[i].substr(3,6);
				else {
					ch = rankToChar.find(c.getRank())->second;
					cardStr = drawMap.find(c.getSuit())->second[i].substr(3,6);
					if (c.getRank() != Ten)
						replace(cardStr.begin(), cardStr.end(), 'Z', ch);
					else {
						if (i == 1){
							if (c.getSuit() == Spade){
								cardStr = ".  |";
							} 
							if (c.getSuit() == Diamond){
								cardStr = "^  |";
							}
							if (c.getSuit() == Club){
								cardStr = "_  |";
							}
							if (c.getSuit() == Heart){
								cardStr = " _ |";
							}
						}
						if (i == 5){
							cardStr = "___|";
						}
					}
				}
				
				outStr += cardStr;
			}
			outStr += "\n";
		}		
	} else {  // Left orientation
		for (int i = 0; i < CARD_HEIGHT; i++){
			// Draw the first card
			c = cardVect[0];
			// Make sure we actually have any cards to draw
			if (numDrawn != 0){
				if (facedown == cardVect.size() || facedown == numDrawn)
					cardStr = facedownCard[i].substr(0,3);
				else {
					cardStr = drawMap.find(c.getSuit())->second[i].substr(0,3);
					if (c.getRank() != Ten){
						replace(cardStr.begin(), cardStr.end(), 'Z', ch);
					} else {
						if (i == 1){
							cardStr = "|10";
						}
						if (i == 5){
							cardStr = "|__";
						}
					}
				}

				outStr += cardStr;
			}
			for (int j = 0; j < numDrawn-facedown; j++){
				c = cardVect[j];
				cardStr = drawMap.find(c.getSuit())->second[i];
				cardStr = cardStr.substr(3,6);
				// 10 will require a special case because its length is 2.
				if (c.getRank() != Ten){
					ch = rankToChar.find(c.getRank())->second;
					replace(cardStr.begin(), cardStr.end(), 'Z', ch);
				} else {
					if (i == 1){
						if (c.getSuit() == Spade){
							cardStr = ".  |";
						} 
						if (c.getSuit() == Diamond){
							cardStr = "^  |";
						}
						if (c.getSuit() == Club){
							cardStr = "_  |";
						}
						if (c.getSuit() == Heart){
							cardStr = " _ |";
						}
					}
					if (i == 5){
						cardStr = "_10|";
					}
				}
				outStr += cardStr;
			}
			for (int j = 0; j < facedown; j++){
				outStr += facedownCard[i].substr(3,6);
			}
			outStr += "\n";
		}		
	}
	//cout << outStr << endl;
	return outStr;
}

// Draw a single Card object
string paintSingle(Card c){
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
	//cout << outStr << endl;
	return outStr;
}

