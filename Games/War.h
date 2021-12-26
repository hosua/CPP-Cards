#include "../Overloads.h"

#ifndef _WAR
#define _WAR

inline static const chrono::milliseconds TIME_CONST(1000); 

map <Rank, int> rankToPts;
// Returns the winning card. Returns a Null card if it's a tie.
Card getWinner(Card a, Card b){
    int apts = rankToPts.find(a.getRank())->second, bpts = rankToPts.find(b.getRank())->second;
    if (rankToPts.find(a.getRank())->second > rankToPts.find(b.getRank())->second)
        return a;
    else if (rankToPts.find(a.getRank())->second < rankToPts.find(b.getRank())->second)
        return b;
    else 
        return Card(NULLR, NULLS);
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
    rankToPts.insert(pair<Rank, int>(ACE, pts++));
    /*
    // Output point chart
    for (auto it = rankToPts.begin(); it != rankToPts.end(); it++){
        cout << "Rank: " << rankToStr.find(it->first)->second << "\tpts: " << it->second << endl;
    }
    */
    vector<Card> deck = createDeck();
    vector<Card> player, computer;
    verboseOverloads = false; // Disable this while we draw cards
    // I don't really have to deal the cards like this but this iteration stays true to the game rules
    for (int i = 0; i < 26; i++){ // Deal each player 1 card per iteration
        player += drawCards(deck, 1, false); 
        computer += drawCards(deck, 1, false);
    }
    verboseOverloads = true; // Re-enable verbose output for overloads

    cout << "Dealing the cards to both players..." << endl;
    this_thread::sleep_for(TIME_CONST*2);
    // A basic state machine implementation
    enum State { INITIAL_PHASE, Revealing, Calculating };
    State state = INITIAL_PHASE;
    while (true){
        clear();
        switch(state){
        case INITIAL_PHASE: // Drawing phase
            cout << "Press enter to play your card.";
            cin.get();
            clear();
            cout << "Player card count: " << player.size() << "\tComputer card count: " << computer.size() << endl;
            cout << player - (player.size()-1);
            cout << computer - (computer.size()-1);
            cin.get();
            clear();
            state = Revealing;
            break;

        case Revealing: // Players reveal their cards
            cout << "Cards remaining: " << deck.size() << endl;

            cout << "Press enter to reveal the cards!" << endl;
            cin.get();

            clear();
            cout << player << endl; // Show player & computer's card, face up
            cout << computer << endl; 
            this_thread::sleep_for(TIME_CONST*2);
            state = Calculating;
            break;

        case Calculating: // Calculate winner
            Card c = getWinner(player[0], computer[0]);
            if (c.getPair() == player[0].getPair()){
                cout << "Player wins!" << endl;
            } else if (c.getPair() == computer[0].getPair()){
                cout << "Computer wins!" << endl;
            } else {
                cout << "Tie." << endl;
            }
            cout << "Press enter to continue..." << endl;
            cin.get();
            state = INITIAL_PHASE;
            break;
        }
    }
}

#endif