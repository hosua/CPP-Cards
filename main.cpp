#include "Overloads.h"
#include "Games/War.h"

void gamemenu(){
	cout << "Please select a card game to play:" << endl;
	vector<string> games = {
		"War",
	};
	for (int i = 0; i < games.size(); i++){
		cout << i + 1 << ") " << games[i] << endl;
	}
	cout << endl;
	cout << "Enter a number to select a game:";
	int opt;
	cin >> opt;
	switch (opt){
	case 1:
		cout << "Starting a game of War" << endl;
		war();
		break;
	case 0:
		exit(0);
		break;
	default:
		cout << "Invalid selection, exiting." << endl;
		break;
	};


}

int main(){
	// Be sure to start your program with this for rng to work properly
	// The seed will be based on the second the program is executed on.
	srand(time(0)); 

	gamemenu();
}

