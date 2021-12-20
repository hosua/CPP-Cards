#include "Paint.h"
// Set how you wish Card vectors to be displayed.
// STACK_MODE options:
// "NONE" will mean that the whole card will be shown
// "LHS" display the cards as stacked, with the top card on the left side.
// "RHS" display the cards as stacked, with the top card on the right side.
const static string STACK_MODE = "NONE";

// Directly print of Card objects through output stream with '<<'
ostream& operator<<(ostream& out, Card c){
	out << paintSingle(c);
	return out;
}
// Directly print of Card vectors through output stream with '<<'
ostream& operator<<(ostream& out, vector<Card> cardVect){
    if (STACK_MODE == "NONE")
        out << paintCards(cardVect);
    else if (STACK_MODE == "RHS")
        out << paintStacked(cardVect);
    else if (STACK_MODE == "LHS")
        out << paintStacked(cardVect, -1, 0, false);
    return out;
}

// Append a Card object to a deck with '+='
void operator+=(vector<Card> &cardVect, Card c){
    cardVect.push_back(c);
}

// Return two Card vectors combined into one.
// ***Does not modify vector
vector<Card> operator+(vector<Card> a, vector<Card> b){
    a.insert(a.end(), b.begin(), b.end());
    return a;
}
// Combine two Card vectors 
// ** Directly modifies the vector
void operator+=(vector<Card> &a, vector<Card> b){
    a.insert(a.end(), b.begin(), b.end());
}

// Remove the first instance of Card object found in the vector if it exists.
// ** Directly modifies the vector 
void operator-=(vector<Card> &cardVect, Card c){
    for (int i = 0; i < cardVect.size(); i++){
        Card itc = cardVect[i];
        if (itc.getPair() == c.getPair()){
            cardVect.erase(cardVect.begin()+i);
            cout << "Removed " << cardVect[i].getInfo() << endl;
            break;
        }
    }
}

string operator-(vector<Card> cardVect, int n){
    string outStr;
    if (STACK_MODE == "NONE")
        outStr = paintCards(cardVect, -1, n);
    else if (STACK_MODE == "RHS")
        outStr = paintStacked(cardVect, -1, n);
    else if (STACK_MODE == "LHS")
        outStr = paintStacked(cardVect, -1, n, false);

    return outStr;
}

    



