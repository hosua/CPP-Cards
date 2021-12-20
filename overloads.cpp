#include "Paint.h"
// Set which stack mode for when drawing multiple cards
// stackMode can be "NONE", "LHS", or "RHS"
const static string STACK_MODE = "LHS";

// Directly print of Card objects through output stream with '<<'
ostream& operator<<(ostream& out, Card c){
	out << paintSingle(c);
	return out;
}
// Directly print of Card vectors through output stream with '<<'
ostream& operator<<(ostream& out, vector<Card> cardVect){
    if (STACK_MODE == "NONE")
        out << drawCards(cardVect);
    else if (STACK_MODE == "RHS")
        out << paintStacked(cardVect);
    else if (STACK_MODE == "LHS")
        out << paintStacked(cardVect, -1, 0, false);
    return out;
}

// Append a Card object to a deck with '+='
void operator+=(vector<Card> &cardVect, Card c);

// Return two Card vectors combined into one.
// ***Does not modify original vector values.
vector<Card> operator+(vector<Card> a, vector<Card> b){
    a.insert(a.end(), b.begin(), b.end());
    return a;
}
// Combine two Card vectors 
// ** Directly modifies the vector being appended to.
void operator+=(vector<Card> &a, vector<Card> b){
    a.insert(a.end(), b.begin(), b.end());
}


