#include "../Overloads.h"

#ifndef _WAR
#define _WAR

bool auto_run = true;

inline static const chrono::milliseconds TIME_CONST(1000); 

map <Rank, int> rankToPts;
int playerVictories = 0, computerVictories = 0;


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
    // Automatic will play the game without user input.
    // Manual will require user input to continue
    int opt;
    cout << "Do you want the gameplay to be automatic or manual?" << endl
         << "1) Automatic" << endl 
         << "2) Manual" << endl
         << "0) Exit game" << endl;
    cin >> opt;
    switch(opt){
    case 0:
        exit(0);
        break;
    case 1:
        cout << "Selected automatic mode." << endl;
        auto_run = true;
        break;
    case 2:
        cout << "Selected manual mode." << endl;
        auto_run = false;
        break;
    default:
        cout << "Invalid input, exiting the game." << endl;
        exit(1);
        break;
    }
    this_thread::sleep_for(TIME_CONST);
    
    

    /* Original deck */
    vector<Card> deck = createDeck();
    /* These are the cards being played */
    vector<Card> playerHand, computerHand;     
    /* These are the cards that are out-of-play. They are shuffled and reinserted into the deck when
        * They are shuffled and reinserted into the hand when the hand vectors are empty.
        */
    vector<Card> playerDiscard, computerDiscard; 
    /* These card vectors are using when there is a tie, (a war) */
    vector<Card> playerField, computerField;

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
    /* REMOVE AFTER TESTING */
    /*
    for (int i = 0; i < 26; i++){
        playerHand[i] = Card(KING, DIAMOND);
        computerHand[i] = Card(KING, DIAMOND);
    }
    */

    // A basic state machine implementation
    enum State { 
                START_PHASE,
                INIT_PHASE, REVEAL_PHASE, CALC_PHASE, 
                WAR_INIT_PHASE, WAR_REVEAL_PHASE, WAR_CALC_PHASE,
                END_PHASE
            };
    State phase = START_PHASE;
    bool playerWin;
    while (true){
        clear();
        // Clear consolue output at the beginning of every phase
        switch(phase){
        case START_PHASE:
        {
            cout << "Starting a game. Good luck!" << endl;
            verboseOverloads = false; 
            /* I don't really have to deal the cards like this but this way of 
             * iterating stays true to the game rules */
            for (int i = 0; i < 26; i++){ 
                playerHand += drawCards(deck, 1, false); 
                computerHand += drawCards(deck, 1, false);
            }
            cout << "Dealing the cards to both players..." << endl;
            this_thread::sleep_for(TIME_CONST*2);
            if (!auto_run){
                cout << "Done! Press enter to continue" << endl;
                cin.get();
            } 
            phase = INIT_PHASE;
        }
        case INIT_PHASE:  
        {
            // Verify that player & cpu have cards remaining
            if (playerHand.size() == 0){
                if (playerDiscard.size() == 0){
                    cout << "Game over! Player lost the war!" << endl;
                    playerWin = false;
                    phase = END_PHASE;
                }  
                playerHand += playerDiscard;
                playerDiscard.clear();
                cout << "Shuffling the player's discarded cards and placing them back in their hand." << endl;
                shuffleCards(playerHand, true, false);

            }
            if (computerHand.size() == 0){
                if (computerDiscard.size() == 0){
                    cout << "Player wins the war! Congratulations" << endl;
                    playerWin = true;
                    phase = END_PHASE;
                }
                computerHand += computerDiscard;
                computerDiscard.clear();
                shuffleCards(computerHand, true, false);
                cout << "Shuffling the player's discarded cards and placing them back in their hand." << endl;
            }
            cout << "Games won: " << playerVictories << "\tGames Lost: " << computerVictories << endl
            << "Player card count: " << playerHand.size() << endl 
            << "Player discarded cards count: " << playerDiscard.size() << endl
            << "Total player cards: " << playerHand.size() + playerDiscard.size() << endl
            << playerHand[0] - 1
            << "Computer card count: " << computerHand.size() << endl
            << "Computer discarded cards count: " << computerDiscard.size() << endl
            << "Total computer cards: " << computerHand.size() + computerDiscard.size() << endl
            << computerHand[0] - 1;
            
            if (!auto_run){
                cout << "Press enter to reveal the next card." << endl;
                cin.get();
            } else {
                this_thread::sleep_for(TIME_CONST*1.5);
            }
            phase = REVEAL_PHASE;
            break;
        }

        case REVEAL_PHASE: // Flip one card up
        {
            cout << "Cards were revealed!" << endl
            << "Games won: " << playerVictories << "\tGames Lost: " << computerVictories << endl
            << "Player card count: " << playerHand.size() << endl
            << "Player discarded cards count: " << playerDiscard.size() << endl
            << "Total player cards: " << playerHand.size() + playerDiscard.size() << endl
            << playerHand[0]
            << "Computer card count: " << computerHand.size() << endl
            << "Computer discarded cards count: " << computerDiscard.size() << endl
            << "Total computer cards: " << computerHand.size() + computerDiscard.size() << endl
            << computerHand[0];

            if (!auto_run){
            cout << "Press enter to continue." << endl;
            cin.get();
            } else {
                this_thread::sleep_for(TIME_CONST*1.5);
            }
            phase = CALC_PHASE;
            break;
        }
        case CALC_PHASE: // Calculate winner
        {
            Card winCard = getWinner(playerHand[0], computerHand[0]);
            if (winCard.samePair(playerHand[0])){
                cout << "Player wins!" << endl;
                rotate(playerHand.begin(), playerHand.begin()+1, playerHand.end()); // Rotate the first Card to the back of the hand
                playerDiscard += computerHand[0]; // Push winner card to discard pile
                playerDiscard += playerHand[0]; // Push loser card to discard pile
                computerHand -= computerHand[0]; // Remove from computer hand
                playerHand -= playerHand[0]; // Remove from player hand
            } else if (winCard.samePair(computerHand[0])){
                cout << "Computer wins!" << endl;
                computerDiscard += computerHand[0];
                computerDiscard += playerHand[0];
                computerHand -= computerHand[0];
                playerHand -= playerHand[0];
            } else { // A tie means war
                cout << "WAR!" << endl;
                // Discard top cards
                playerDiscard += playerHand[0];
                computerDiscard += computerHand[0];
                playerHand -= playerHand[0];
                computerHand -= computerHand[0];
                
                phase = WAR_INIT_PHASE;
                break;
            }
            if (!auto_run){
                cout << "Press enter to continue." << endl;
                cin.get();
            } else {
                this_thread::sleep_for(TIME_CONST*1.5);
            }
            phase = INIT_PHASE;
            break;
        }
        // Every tie will incur another war until there is no tie
        case WAR_INIT_PHASE:
        {
            /* Ensure we dont overdraw cards for computer */

            if (playerHand.size() == 0){
                if (playerDiscard.size() == 0){
                    cout << "Player loses the war!" << endl;
                    playerWin = false;
                    phase = END_PHASE;
                }
                playerHand += playerDiscard;
                playerDiscard.clear();
                cout << "Shuffling the player's discarded cards and placing them back in their hand." << endl;
                shuffleCards(playerHand, true, false);
            }
            if (computerHand.size() == 0){
                if (computerDiscard.size() == 0){
                    cout << "Player wins the war! Congratulations!" << endl;
                    playerWin = true;
                    phase = END_PHASE;
                }
                computerHand += computerDiscard;
                computerDiscard.clear();
                cout << "Shuffling the player's discarded cards and placing them back in their hand." << endl;
                shuffleCards(computerHand, true, false);
            }
            /* Ensure we dont overdraw cards for player 
             * This will draw new cards to the beginning of the hand to prevent an endless loop if another
             * war occurs
             */
            if (playerHand.size() >= 3)
                playerField = drawCards(playerHand, 3, false) + playerField;
            else
                playerField = drawCards(playerHand, playerHand.size(), false) + playerField;

            if (computerHand.size() >= 3)
                computerField = drawCards(computerHand, 3, false) + computerField;
            else
                computerField = drawCards(computerHand, computerHand.size(), false) + computerField;

            cout << "WAR!" << endl
            << "Cards are placed on the field by both players!" << endl
            << "Games won: " << playerVictories << "\tGames Lost: " << computerVictories << endl
            << "Player card count: " << playerHand.size() << endl
            << "Discarded cards count: " << playerDiscard.size() << endl
            << "Cards on field: " << playerField.size() << endl
            << playerField - playerField.size()
            << "Computer card count: " << computerHand.size() << endl
            << "Discarded cards count: " << computerDiscard.size() << endl
            << "Cards on field: " << computerField.size() << endl
            << computerField - computerField.size();
            if (!auto_run){
            cout << "Press enter to reveal the cards." << endl;
            cin.get();
            } else {
                this_thread::sleep_for(TIME_CONST*1.5);
            }
            phase = WAR_REVEAL_PHASE;
            break;
        }
        case WAR_REVEAL_PHASE:
        {
            cout << "WAR!" << endl
            << "The cards were revealed!" << endl
            << "Games won: " << playerVictories << "\tGames Lost: " << computerVictories << endl
            << "Player card count: " << playerHand.size() << endl
            << "Player discarded cards count: " << playerDiscard.size() << endl
            << playerField - (playerField.size()-1)
            << "Computer card count: " << computerHand.size() << endl
            << "Computer discarded cards count: " << computerDiscard.size() << endl
            << computerField - (computerField.size()-1);
            if (!auto_run){
            cout << "Press enter to reveal the cards." << endl;
            cin.get();
            } else {
                this_thread::sleep_for(TIME_CONST*1.5);
            }
            phase = WAR_CALC_PHASE;
            break;

        }
        case WAR_CALC_PHASE:
        {
            cout << "WAR!" << endl;
            Card winCard = getWinner(playerField[0], computerField[0]);

            if (winCard.samePair(playerField[0])){
                cout << "Player wins!" << endl;
                /* Card vector B is not directly modified, so cards must manually be erased once done
                 * Add all field cards to winner
                 */
                playerHand += playerField;
                playerHand += computerField;
                /* Clear field */
                playerField.clear();
                computerField.clear();
            } else if (winCard.samePair(computerField[0])){
                cout << "Computer wins!" << endl;
                computerHand += playerField;
                computerHand += computerField;
                playerField.clear();
                computerField.clear();
            } else { /* A tie means war again */
                cout << "WAR CONTINUES!" << endl;
                
                if (!auto_run){
                    cout << "Press enter to continue" << endl;
                    cin.get(); 
                } else {
                    this_thread::sleep_for(TIME_CONST*3);
                }
                phase = WAR_INIT_PHASE;
                break;
            }
            if (!auto_run){
                cout << "Press enter to continue." << endl;
                cin.get();
            } else {
                this_thread::sleep_for(TIME_CONST*1.5);
            }
            phase = INIT_PHASE;
        }
        case END_PHASE:
        {
            if (playerWin)
                playerVictories++;
            else
                computerVictories++;
            if (!auto_run){
                cout << "Press enter to start a new game." << endl;
                cin.get();
            } else {
                this_thread::sleep_for(TIME_CONST);
            }
            cout << "Starting a new game..." << endl;
            this_thread::sleep_for(TIME_CONST*2);
            phase = START_PHASE;
        }

        }
        
        
    }
}

#endif