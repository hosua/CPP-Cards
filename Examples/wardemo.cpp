// Include Overloads.h in your .cpp file to use the Cards library
#include "../Overloads.h" 
#include <ostream>

static const chrono::milliseconds TIME_CONST(1000); 

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
int main(){
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