
#include <iostream>
#include <vector>

#include "Player.h"
#include "Table.h" 
#include "Actions.h"

using namespace std; 

void  Player::receiveCard( Card * card ) {

	cout << "player: [" << this->playerID << "] got card " << *card << endl; 

	this->pocketCards.push_back(card); 

	if(pocketCards.size() > 2 ) {
		cerr << "ACHTUNG zuviele karten " << endl; 
		// throw exception ? 
	}

}