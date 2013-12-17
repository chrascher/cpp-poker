#pragma once

#include <array>
#include <vector>

#include "Player.h"
#include "Pot.h"
#include "Card.h"
#include "Actions.h"
#include "Deck.h"

class PokerApp;

/*
  This class represents the central table where one game is played.

*/
class Table {
public: 
		enum BetRound {
			      PRE_START = 0,     // status before game has even started
				  PRE_FLOP = 1,      // game starts with pre flop
                  ON_FLOP  = 2,      // 3 cards visible
				  ON_TURN  = 3,      // +1 card == 4 cards
				  ON_RIVER = 4,      // +1 card == 5 cards  
				  SHOWDOWN = 5       // show the Hands, display the Winner and earn the Pot  
			   } ;

private:    
	const unsigned int seats; 
	const unsigned int minimumBet;  

	PokerApp & app; // a game knows which app it is attached to, generall basic infos will be get from there

	Deck deck;

	BetRound currentRound; 

	vector<Player *> players;  // Player * seats[8]; // 0 to 8 

	// coins in the pot for this single game
	// current bet and call values will remain with the players pot/bet, 
	// and moved to this pot, when the bet round is over
	Pot pot; 

	vector<Card *> communityCards; // should be 0, 3, 4 or 5 ; encapsulate in class if required 

	vector<Card *> burnedCards; // collects the 3 burned Cards

	int buttonPosition; 

	// poistion of game player which has last raised and will not asked for action again 
	int stepOutBetRoundPos; // instead of finalBetPos to prevent overflow (0-1)


public:
	Table(PokerApp & app);

	~Table(void);

	vector<Player *> getPlayers() const {
		return players; 
	}

	/*
	 * initialize the table for a new game ! 
	 * gets the players from app. must be already full with players or computer players
	 */
	void initialize(vector<Player * > );

	void run(); 

	// Player * getLastRaisedPlayer() ; 

	//
	unsigned int getLastRaisedAmount() {
		Player * player =  players.at(this->stepOutBetRoundPos);
		SingleBet * pot = player->getSingleBetPot (); 
		return pot->getCoins(); 
	}


private: 
	void dealForTexasHoldem() ;

	void dealPocketCards(); 

	void dealCommunityCards(); 

	void Table::tellThemNextRound(); 

	void Table::doActionsForPlayers( BetRound round ) ; 

	void Table::tablePrepareForPreStart(); 

	void Table::tablePrepareForPreFlop(); 

	void Table::tablePrepareForOnFlop(); 

	void Table::tablePrepareForOnTurn(); 

	void Table::tablePrepareForOnRiver(); 

	void Table::tablePrepareForShowdown();


};

