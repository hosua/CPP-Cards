// Ascii art made by ejm98, source: https://www.asciiart.eu/miscellaneous/playing-cards
#include <string>
#include <iostream>
#include "Cards.h"

using namespace std;
/* The functions in this file handle converting the cards into ASCII form. 
These functions can be used directly, along with the overloaded operations in overloads.h
*/

// The number of elements in the string arrays
// DO NOT change this value.
static const int CARD_HEIGHT = 6; 
inline string spadeCard[] = {
" _____ ",
"|Z .  |",
"| /.\\ |",
"|(_._)|",
"|  |  |",
"|____Z|"
}; 
inline string diamondCard[] = {
" _____ ",
"|Z ^  |",
"| / \\ |",
"| \\ / |",
"|  .  |",
"|____Z|"
};
inline string clubCard[] = {
" _____ ",
"|Z _  |",
"| ( ) |",
"|(_'_)|",
"|  |  |",
"|____Z|"
};
inline string heartCard[] = {
" _____ ",
"|Z_ _ |",
"|( v )|",
"| \\ / |",
"|  .  |",
"|____Z|"
};
inline string facedownCard[] = {
" _____ ",
"|\\\\~//|",
"|}}:{{|",
"|}}:{{|",
"|}}:{{|",
"|//~\\\\|"
};

inline map<Suit,string*> drawMap = {
	{Spade, spadeCard}, 
	{Diamond, diamondCard},
	{Club, clubCard}, 
	{Heart, heartCard}
};


/* Draws an array of cards in ASCII
Cards are fully displayed and not on top of each other.
*/
inline string paintCards(vector<Card> cardVect, int numDrawn=-1, int facedown=0){ 			
	// Bound checks
	if (numDrawn < 0 || numDrawn > cardVect.size()) numDrawn = cardVect.size(); 		
	if (facedown < 0) facedown = 0;
	if (facedown > cardVect.size()) facedown = cardVect.size();
	if (facedown > numDrawn) facedown = numDrawn;
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
/* Won't display any face down cards.
Like paintCards, except the cards will be painted as if they are stacked on top of each other.
topRHS=true will mean that the top card of the stack will be on the right side.
*/
inline string paintStacked(vector<Card> cardVect, int numDrawn=-1, int facedown=0, bool topRHS=true){ // Draws an array of cards in ASCII
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
			// Paint the first card 
			c = cardVect[0];
			// Make sure we actually have any cards to paint
			if (numDrawn != 0){
				if (facedown == cardVect.size() || facedown == numDrawn){
					cardStr = facedownCard[i].substr(0,3);
				} else {
					cardStr = drawMap.find(c.getSuit())->second[i].substr(0,3);
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
inline string paintSingle(Card c){
	string outStr, cardStr;
	for (int i = 0; i < CARD_HEIGHT; i++){
		cardStr = drawMap.find(c.getSuit())->second[i];
		if (c.getRank() == Ten){
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
		} else {
			char ch = rankToChar.find(c.getRank())->second;
			replace(cardStr.begin(), cardStr.end(), 'Z', ch);
		}
	
	outStr += cardStr + "\n";
	}
	return outStr;
}

// "Animates" a deck being shuffled. Does not actually shuffle a card Vector.
inline void shuffleAnimation(bool verbose=true){
	const chrono::milliseconds FRAME_LENGTH(50); 
	const int FRAMES = 52;
	vector <Card> animDeck = createDeck(2, false, false);
	cout << "STARTING" << endl;
	random_shuffle(begin(animDeck), end(animDeck));
	for (int n = 0; n < FRAMES; n++){
		if (verbose)
			cout << "Shuffling cards..." << endl;
		if (animDeck.empty())
			animDeck = createDeck(2, true, false);
		else {
			cout << animDeck.back() << endl;
			animDeck.pop_back();	
		}
		this_thread::sleep_for(FRAME_LENGTH);
		clear();
	}
	if (verbose)
		cout << "The cards were shuffled." << endl;
}
