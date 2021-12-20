#include "Draw.h"
// Set which stack mode for when drawing multiple cards
// stackMode can be "NONE", "LHS", or "RHS"
const static string STACK_MODE = "LHS";

DrawHandler DH;
// Allows direct printing of Card objects
ostream& operator<<(ostream& out, Card c){
	out << DH.drawSingle(c);
	return out;
}
// Allow direct printing of Card vectors
ostream& operator<<(ostream& out, vector<Card> cardVect){
    if (STACK_MODE == "NONE")
        out << DH.drawCards(cardVect);
    else if (STACK_MODE == "RHS")
        out << DH.drawStacked(cardVect);
    else if (STACK_MODE == "LHS")
        out << DH.drawStacked(cardVect, -1, 0, false);
    return out;
}
// Allow using + to add two cards together to create a card vector
vector<Card> operator+(Card a, Card b){
	vector<Card> cardVect;
	cardVect.push_back(b);
	cardVect.push_back(a);
	return cardVect;
}
// Allow using += to add a card to an existing card vector
void operator+(vector<Card> &cardVect, Card c){
	cardVect.push_back(c);
}
// Allow using + to add a pair of Rank and Suit to a card vector
void operator+(vector<Card> &cardVect, pair<Rank, Suit> cardPair){
    Card c;
    Rank r = get<0>(cardPair);
    Suit s = get<1>(cardPair);
    c.setCard(r, s);
    cardVect.push_back(c);
}
// Allow using - to remove n amount of cards from the top of the deck
void operator-(vector<Card> &cardVect, int n){
	int a = 0;
	while (a < n){
		cardVect.pop_back();
		a++;
	}
}
// Delete a card by a Rank and Suit pair.
void operator-(vector<Card> &cardVect, pair<Rank, Suit> cardPair){
    Rank r = get<0>(cardPair);
    Suit s = get<1>(cardPair);
    for (int i = 0; i < cardVect.size(); i++){
        if (cardVect[i].getRank() == r && cardVect[i].getSuit() == s){
            cardVect.erase(cardVect.begin()+i);
        }
}

}
void drawTest(){
	drawTest1();
	drawTest2();
	drawTest3();
}
