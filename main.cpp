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
	cout << "Enter a number to select a game:" << endl;
	int opt;
	cin >> opt;
	switch (opt){
	case 1:
		cout << "Starting game of War" << endl;
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
	gamemenu();
}

