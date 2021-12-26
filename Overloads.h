// Header guards so that headers can be included more than once
#ifndef _OVERLOADS
#define _OVERLOADS

#include "Paint.h"

// All overload definitions reside in this file.
// NOTE TO SELF: To define overload operators in header files, they need to be inline 


// Set how Card vectors will be displayed.
// STACK_MODE options: "NONE", "LHS", or "RHS"
enum Mode { NONE, LHS, RHS };
// "NONE" will mean that the whole card will be shown
// "LHS" displays the cards as stacked, with the top card on the left side.
// "RHS" displays the cards as stacked, with the top card on the right side.
// This can also manually be handled using paintCards() and/or paintStacked() with the proper flags.
static Mode STACK_MODE = LHS;
// Set verboseOverloads to false if you do not want the overload operators to print text.
static bool verboseOverloads = true;


// Directly print Card objects through output stream with '<<'
inline ostream& operator<<(ostream& out, Card c){
	out << paintSingle(c);
	return out;
}
// Directly print Card vectors through output stream with '<<'
inline ostream& operator<<(ostream& out, vector<Card> cardVect){
    if (STACK_MODE == NONE) // Unstacked
        out << paintCards(cardVect);
    else if (STACK_MODE == RHS) // Top of stack on right side
        out << paintStacked(cardVect);
    else if (STACK_MODE == LHS) // Top of stack on left side
        out << paintStacked(cardVect, -1, 0, false);
    return out;
}

// Return a Card object added to a Card vector
// ***Does not modify original vector
inline vector<Card> operator+(vector<Card> cardVect, Card c){
    vector<Card> r = cardVect;
    r.push_back(c);
    return r;
}
// Reversed. This way of inserting is much less efficient and should not be used often
inline vector<Card> operator+(Card c, vector<Card> cardVect){
    cardVect.insert(cardVect.begin(), c); // O(n) operation
    return cardVect;
};

// Append a Card object to a Card vector with '+='
inline void operator+=(vector<Card> &cardVect, Card c){
    cardVect.push_back(c);
    if (verboseOverloads) cout << "Added " << c.getInfo() << " to Card vector." << endl;
}

// Return two Card vectors combined into one.
// ** Does not modify original vectors
inline vector<Card> operator+(vector<Card> a, vector<Card> b){
    a.insert(a.end(), b.begin(), b.end());
    return a;
}

// Return a vector made from 2 Card objects
inline vector<Card> operator+(Card a, Card b){
    return vector<Card> {a, b};
}

// Combine two Card vectors 
// ** Directly modifies the left vector operand
inline void operator+=(vector<Card> &a, vector<Card> b){
    a.insert(a.end(), b.begin(), b.end());
    if (verboseOverloads) {
        cout << "Added ";
        for (int i = 0; i < b.size(); i++){
            if (i != b.size()-1)
                cout << b[i].getInfo() + ", ";
            else 
                cout << "and " << b[i].getInfo();
        }
        cout << " to Card vector." << endl;
    }
}

// Remove the first instance of Card object found in the vector if it exists.
// ** Directly modifies the vector of the left operand
inline void operator-=(vector<Card> &cardVect, Card c){
    bool found = false;
    for (int i = 0; i < cardVect.size(); i++){
        Card itc = cardVect[i];
        if (itc.getPair() == c.getPair()){
            cardVect.erase(cardVect.begin()+i);
            if (verboseOverloads)
                cout << "Removed " << cardVect[i].getInfo() << " from Card vector." << endl;
            found = true;
            break;
        }
    }
    if (!found && verboseOverloads)
        cout << "Did not find " << c.getInfo() << endl;
}

// Remove the first instance of all cards in vector b from vector a. 
// ** Directly modifies the Card vector
inline void operator-=(vector<Card> &a, vector<Card> b){
    for (int i = 0; i < b.size(); i++){
        for (int j = 0; j < a.size(); j++){
            if (a[j].getPair() == b[i].getPair()){
                Card c = a[j];
                a.erase(a.begin()+j);
                if (verboseOverloads)
                    cout << "Removed " << c.getInfo() << " from Card vector." << endl;
                break;
            }
        }
    }
}

// Return the  card Vector, "minus" the card specified. 
// Only removes the first instance of the card if multiple exist.
// ** Does not directly modify the Card vector
inline vector<Card> operator-(vector<Card> cardVect, Card c){
    bool found = false;
    for (int i = 0; i < cardVect.size(); i++){
        Card itc = cardVect[i];
        if (itc.getPair() == c.getPair()){
            cardVect.erase(cardVect.begin()+i);
            found = true;
            break;
        }
    }
    if (!found && verboseOverloads)
        cout << "Did not find " << c.getInfo() << endl;
    return cardVect;
}
// Return the Card vector a, minus all the cards in Card vector b that are found in a.
// ** Does not directly modify the Card vector
inline vector<Card> operator-(vector<Card> a, vector<Card> b){
    for (int i = 0; i < b.size(); i++){
        for (int j = 0; j < a.size(); j++){
            if (a[j].getPair() == b[i].getPair()){
                a.erase(a.begin()+j);
                break;
            }
        }
    }
    return a;
}

// Subtracting an int, n from a Card vector will return the painted cards with n-cards facedown. 
// Example use: 
// cout << cardVect-2 << endl;
// This will paint all cards in cardVect but with 2 facing down.
inline string operator-(vector<Card> cardVect, int n){
    string outStr;
    if (STACK_MODE == NONE)
        outStr = paintCards(cardVect, -1, n);
    else if (STACK_MODE == RHS)
        outStr = paintStacked(cardVect, -1, n);
    else if (STACK_MODE == LHS)
        outStr = paintStacked(cardVect, -1, n, false);
    return outStr;
}

#endif


