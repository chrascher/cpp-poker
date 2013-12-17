

#pragma once

#include <string>

#include "player.h"

using namespace std; 

/*
 * real person playing 
*/
class RealPlayer : public Player {

private: 

public:
	RealPlayer(string playerName) : Player(playerName) {

	}

	~RealPlayer(void) {
		
	}

	string getName() {
		return getPlayerId();
	}


	// virtual see player 
	Actions RealPlayer::playActionStep( Table * table ); 


};

