
#pragma once

#include <stack>
#include <array>
#include "Card.h"

// # include "PokerApp.h"

class PokerApp;

/*
 * We have the Deck of cards to be a stack itself, so basically we can add additional infos
 * and limitations here to be able to enforce correct deck behaviour
 */
class Deck {

private:
	PokerApp & app; // a game knows which app it is attached to, generall basic infos will be get from there

	std::stack<Card *> cardStack;

public:

	Deck(PokerApp & app); 
	
	~Deck(void);

	// creates a new random stack for a new game to play
	void shuffleNewStack() ; 


	Card * getNextCard() {
		Card * nextCard = cardStack.top();
		cardStack.pop(); 
		return nextCard;
	}

private:
	void cearStack() ; 
	void debugRandomStack( std::array<Card *, 52> & cards) ;


};

