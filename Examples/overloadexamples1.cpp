#include "../Overloads.h"

using namespace std;

int main(){

    // Don't shuffle so we can skip animation 
    auto deck = createDeck(1, false); 
    /// Shuffle, and don't animate 
    shuffleCards(deck, false); 
    // Draw 5 cards from deck
    auto hand = drawCards(deck, 5); 
    cout << "cout << hand << endl;" << endl;
    // We can easily show the contents of a Card vector by printing it with "cout <<"
    cout << hand << endl; 
    // We can display a card vector, with some number of cards down with cardVector - n;
    // Where n is the number of cards.
    // This will print hand with 2 cards face down.
    cout << "cout << hand - 2 << endl;" << endl;

    cout << hand - 2 << endl;

    cout << "hand += Card(King, Diamond);" << endl;
    // We can add a card directly to a Card vector with '+=' operator
    hand += Card(King, Diamond);
    
    cout << hand << endl;

    cout << "hand -= Card(King, Diamond);" << endl;
    // We can delete a card from a cardVect with '-='
    hand -= Card(King, Diamond);

    cout << hand << endl;


}