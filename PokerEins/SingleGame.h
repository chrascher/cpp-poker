#pragma once

#include "Table.h" 

class PokerApp;
/*
 this represents all activities required to play for one deck.
 so each player with one hand. 
 therefore we play for one pot.
*/
class SingleGame {

private: 
	PokerApp & app; // a game knows which app it is attached to, generall basic infos will be get from there
	Table table;

public:

	SingleGame(PokerApp & app);
	~SingleGame(void);


	void initialize(vector<Player * > players ) {
		
		table.initialize(players);


	}


	void run() {
		
		table.run(); 
	}


};

