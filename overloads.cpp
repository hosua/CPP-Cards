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
// Combine two Card vectors (without modifying either of the original vectors)
vector<Card> operator+(vector<Card> a, vector<Card> b){
    a.insert(a.end(), b.begin(), b.end());
    return a;
}

void drawTest(){
	drawTest1();
	drawTest2();
	drawTest3();
}
