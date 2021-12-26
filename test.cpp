// This file and main.cpp should be compiled separately. This file has its own main function.

#include "Overloads.h"
#include <chrono>
#include <thread>

inline static const chrono::milliseconds TIME_CONST(500); 

// Draw cards not stacked
void paintTest1(){
	cout << "Paint test 1 (NONE)" << endl;
	vector<Card> hand;
	for (auto its = suitToStr.begin(); its != suitToStr.end(); its++){
		hand.push_back(Card(Ace, its->first));
		hand.push_back(Card(Ten, its->first));
	}
	cout << paintCards(hand, 6, 4);
}

// Paint cards stacked, RHS on top with some cards face down
void paintTest2(){
	cout << "Paint test 2 (RHS)" << endl;
	vector<Card> hand;
	for (auto its = suitToStr.begin(); its != suitToStr.end(); its++){
		hand.push_back(Card(Ace, its->first));
		hand.push_back(Card(Ten, its->first));
	}
	cout << paintStacked(hand, 6, 4);
}
// Paint cards stacked, LHS on top, with some cards face down
void paintTest3(){
	cout << "Paint test 3 (LHS)" << endl;
	vector<Card> hand;
	for (auto its = suitToStr.begin(); its != suitToStr.end(); its++){
		hand.push_back(Card(Ace, its->first));
		hand.push_back(Card(Ten, its->first));
	}
	cout << paintStacked(hand, 6, 4, false);
}
void paintTest(){
	paintTest1();
	paintTest2();
	paintTest3();
}
void testProg1(){
	vector <Card> deck = createDeck(1);
	cout << paintCards(deck, 3); // (cardVect, numPainted, numFacedown,)
}

// Endlessly draw cards and reset deck when insufficient cards are left 
void testProg2(){
	int NUM_DECKS = 1;

	vector <Card> deck = createDeck(NUM_DECKS);
	vector <Card> hand;
	int NUM_CARDS = 5;
	bool dontPaint;
	while (true){ 
		dontPaint = false;
		cout << "Size: " << deck.size() << endl;

		if (deck.size() < NUM_CARDS && deck.size() != 0){
			hand = drawCards(deck, deck.size());
		} else if (deck.size() == 0){
			deck = createDeck(NUM_DECKS);
			dontPaint = true;
		} else {
			hand = drawCards(deck, NUM_CARDS);
		}
		if (!dontPaint) cout << hand << endl;
		
		
		this_thread::sleep_for(TIME_CONST);
	}
}


void testProg3(){ 	
	int NUM_DECKS = 6;

	vector <Card> deck = createDeck(NUM_DECKS);
	vector <Card> hand;
	int NUM_CARDS = 10;
	// Do not forget to do +1 to omit cases when we have 0, otherwise we will get
	// Floating point errors.
	int numDrawn = rand() % NUM_CARDS+1;
	int numDown = rand() % numDrawn+1;
	bool dontPaint;
	while (true){ 
		dontPaint = false;
		cout << "Cards remaining: " << deck.size() << endl;
		if (deck.size() < NUM_CARDS && deck.size() != 0){
			hand = drawCards(deck, deck.size());
			cout << hand << endl;
		} else if (deck.size() == 0){
			deck = createDeck(NUM_DECKS);
			dontPaint = true;
		} else {
			hand = drawCards(deck, numDrawn);
		}
		if (!dontPaint && numDrawn > 0) cout << paintStacked(hand, numDrawn, numDown, false);
		numDrawn = rand() % NUM_CARDS+1;
		numDown = rand() % numDrawn+1;
		
		this_thread::sleep_for(TIME_CONST);
	}
}

void ovlExample1(){
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

void ovlExample2(){

    // Don't shuffle so we can skip animation 
    auto deck = createDeck(1, false); 
    /// Shuffle, and don't animate 
    shuffleCards(deck, false); 
    // Draw 5 cards from deck
    auto hand1 = drawCards(deck, 5); 
    auto hand2 = drawCards(deck, 5); 

    cout << "\ncout << Card(Ace, Spade) + Card(Ace, Diamond) + Card(Ace, Club) + Card(Ace, Heart) << endl;" << endl;
    // You can concatenate Card vectors together to print a combined one
    cout << Card(Ace, Spade) + Card(Ace, Diamond) + Card(Ace, Club) + Card(Ace, Heart) << endl;


    cout << "cout << hand1 + Card(Ace, Spade) + hand2 + Card(Ace, Diamond) + Card(Ace, Heart) << endl;" << endl;
    // You can concatenate Card vectors and Card objects together in any order.
    // This does not modify any of the card vectors.
    cout << hand1 + Card(Ace, Spade) + hand2 + Card(Ace, Diamond) + Card(Ace, Heart) << endl;

}


//static const chrono::milliseconds TIME_CONST(1000); 

map <Rank, int> rankToPts;
// Returns the winning card. Returns a Null card if it's a tie.
Card getWinner(Card a, Card b){
    int apts = rankToPts.find(a.getRank())->second, bpts = rankToPts.find(b.getRank())->second;
    if (rankToPts.find(a.getRank())->second > rankToPts.find(b.getRank())->second)
        return a;
    else if (rankToPts.find(a.getRank())->second < rankToPts.find(b.getRank())->second)
        return b;
    else 
        return Card(NullR, NullS);
}
void war(){
	// Be sure to start your program with this for rng to work properly
	// The seed will be based on the second the program is executed on.
	srand(time(0)); 
    int pts = 2;
    // Declare map to determine winner card
    for (auto itr = next(rankToStr.begin()); itr != rankToStr.end(); itr++){
        rankToPts.insert(pair<Rank, int>(itr->first, pts));
        pts++;
    }
    rankToPts.insert(pair<Rank, int>(Ace, pts++));

    // Output point chart
    for (auto it = rankToPts.begin(); it != rankToPts.end(); it++){
        cout << "Rank: " << rankToStr.find(it->first)->second << "\tpts: " << it->second << endl;
    }

    vector<Card> deck;
    vector<Card> player, computer;
    // A basic state machine implementation
    enum State {Drawing, Revealing, Calculating};
    State state = Drawing;
    int playerScore = 0, computerScore = 0;
    while (true){
        clear();
        switch(state){
            case Drawing: // Drawing phase
                if (deck.size() == 0){
                    cout << "Empty deck detected, creating a new one." << endl;
                    this_thread::sleep_for(TIME_CONST);
                    deck = createDeck(); 
                }
                cout << "Cards remaining: " << deck.size() << endl;
                player = drawCards(deck, 1, false); // Draw 1 card, without verbose output
                cout << "Player: " << playerScore << " points\n" << player-1 << endl; 
                computer = drawCards(deck, 1, false);
                cout << "Computer: " << computerScore << " points\n" << computer-1 << endl; 
                cout << "Player and Computer each draw a card." << endl;
                this_thread::sleep_for(TIME_CONST*2);
                clear();
                state = Revealing;
                break;

            case Revealing: // Players reveal their cards
                cout << "Revealing cards..." << endl;
                cout << player-1 << endl; // Show player & computer's card, face down
                cout << computer-1 << endl;
                this_thread::sleep_for(TIME_CONST);
                clear();
                cout << "Player: " << playerScore << " points" << endl;
                cout << player << endl; // Show player & computer's card, face up
                cout << "Computer: " << computerScore << " points" << endl;
                cout << computer << endl; 
                this_thread::sleep_for(TIME_CONST*2);
                state = Calculating;
                break;

            case Calculating: // Calculate winner
                Card c = getWinner(player[0], computer[0]);
                if (c.getPair() == player[0].getPair()){
                    cout << "Player wins!" << endl;
                    playerScore++;
                } else if (c.getPair() == computer[0].getPair()){
                    cout << "Computer wins!" << endl;
                    computerScore++;
                } else {
                    cout << "Tie." << endl;
                }

                this_thread::sleep_for(TIME_CONST*1.5);
                state = Drawing;
                break;
        }
    }
}

int main(){
	// Be sure to start your program with this for rng to work properly
	// The seed will be based on the second the program is executed on.
	srand(time(0)); 

	int option;
	vector<string> opts = {
		"paintTest()", // Shows all kinds of stack modes
		"testProg1()", // Show 3 cards unstacked
		"testProg2()", // Endlessly draw 5 cards from a deck
		"testProg3()", // Draw a random amount of cards and display a random amount facedown
		"ovlExample1()", // See the syntax of how overloads can be used
		"ovlExample2()", // More overload examples
		"war()" // An endless demo of the game, War. No gameplay involved. This demo runs automatically 
	};
	cout << endl;
	for (int i = 0; i < opts.size(); i++){
		cout << i + 1 << ") " << opts[i] << endl;
	}
	cout << endl;
	cout << "Enter a number to select an option: ";
	cin >> option;
	switch(option){
		case 1:
			paintTest(); // Shows all kinds of stack modes
			break;
		case 2:
			testProg1();
			break;
		case 3:
			testProg2();	
			break;
		case 4:
			testProg3();
			break;
		case 5:
			ovlExample1();
			break;
		case 6:
			ovlExample2();
			break;
		case 7:
			war();
			break;
		case 0:
			exit(0);
			break;
	};

	
}
