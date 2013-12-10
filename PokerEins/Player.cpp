
#include <iostream>
#include <vector>

#include "Player.h"
#include "Table.h" 
#include "Actions.h"

using namespace std; 

// SEE .h file
Actions Player::playActionStep( Table * table ) {

	vector<Player *> players = table->getPlayers(); 

	if(this->doRase) {
		return Actions::RAISE; 
	} 

	return Actions::CHECK; 
}

void  Player::receiveCard( Card * card ) {

	cout << "player: [" << this->playerID << "] got card" << *card << endl; 

	this->pocketCards.push_back(card); 

	if(pocketCards.size() > 2 ) {
		cerr << "ACHTUNG zuviele karten " << endl; 
		// throw exception ? 
	}

}