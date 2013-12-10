#pragma once

#include <iostream>

using namespace std; 

/*
 * pot amount of coins already bet for this singleGame
 * 
*/ 
class Pot {

private: 

	unsigned int coins; 

public:
	Pot(void);
	~Pot(void);

	// returns the current amout for this pot 
	unsigned getCoins () {
		return coins; 
	}

	void addCoins(unsigned addValue) {
		coins += addValue; 
	}

	void removeCoins( unsigned removeValue ) {

		if(removeValue> coins) {
			coins = 0;
			cerr << "you can not remove more than the available amout from a pot" << endl; 
		} else 
			coins = coins - removeValue;
	}

	unsigned clearPot () {
		unsigned tmp = coins; 
		coins = 0;
		return tmp; 
	}


};

