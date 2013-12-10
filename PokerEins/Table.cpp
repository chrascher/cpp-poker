
#include "Table.h"
#include "SingleGame.h" 
#include "Player.h" 


Table::Table(PokerApp & app) : app(app) , deck(app) , seats(9), minimumBet(2) {

	buttonPosition -1; 
}


Table::~Table(void)
{
}

/*
 * see .h file 
*/
void Table::initialize(vector<Player * > players ) {

	this->players = players;


	buttonPosition = ++buttonPosition % seats ; 

	currentRound = PRE_START; 

	communityCards.clear();

	deck.shuffleNewStack(); 

}

void Table::dealForTexasHoldem() {

	dealOneRoundOfCards(); 
	dealOneRoundOfCards(); 
}

void Table::dealOneRoundOfCards() {

	int startPos = this->buttonPosition + 1; 
	for(int i = 0 ; i < seats ; i++ ) {
		Player * nextPlayer = players.at(i);  // or use players[i]; 
	
		nextPlayer->receiveCard( deck.getNextCard() ) ; 
		startPos = ++startPos % players.size(); 
	}
}

void Table::tellThemNextRound() {

	for(int i = 0 ; i < seats ; i++ ) {
		Player * nextPlayer = players.at(i);  // or use players[i]; 
		
		SingleBet * oldBet = nextPlayer->resetSingleBet(); 
		if( oldBet != NULL ) {
			this->pot.addCoins( oldBet->getCoins() ) ; 
			delete oldBet; 
		}

	}
}



void Table::run()  {

		// TODO :: button must be set to next button player
		
		tellThemNextRound(); 

		// small blind will be forced to be set by player after button
		unsigned int smallBlind = buttonPosition + 1 ;
		players[smallBlind]->makeBlind( minimumBet/2 );

		// big blind will be enforce to player after small blind player
		unsigned int bigBlindPos = buttonPosition + 2 ;
		
		players[bigBlindPos]->makeBlind(  minimumBet  );

		// each player gets 2 cards:
		dealForTexasHoldem(); 

		for( int i = PRE_FLOP; i <= ON_RIVER; i++ ) {

			this->currentRound = static_cast<BetRound>(i);

			// todo:
			// 1. depending on bet round give 0 cardspre, then 3 cards, 1 card, or 1 card, or showdown

			// 1.1. display action status on SCREEN (community cards + players active with tehre status and player-bet-size) 

			// 2. now each player can perform its/his action 

			int finalBetPos; // player which started this round, after big blind
			                   // or he is the last raiser 
			int currentPos; 

			if ( i == PRE_FLOP ) {
				finalBetPos = this->buttonPosition + 2 ; 

			} else {
				finalBetPos = this->buttonPosition ; 
			}
			currentPos = finalBetPos + 1 ; 

			bool firstRound = true; 
			// for( int playerX = 0; i <= 8 ; playerX++ ) {
			while( currentPos != finalBetPos+1 || firstRound ) {
				
				firstRound = false; 

				Player * currentPlayer = this->players.at(currentPos); 
				// returns the action taken  == fold, call, raise, bet, all-in
				
				Actions action = currentPlayer-> playActionStep( this ); 

				if(action == RAISE ) {
					// current player has raised, mark him,
					//  restart loop over players, so they can check, fold, raise also 
					finalBetPos = currentPos != 0 ? currentPos-1 : 8 ; 
				} 

				currentPos ++; 
				if(currentPos == 9) {
					currentPos = 0; 
				}
			

			} // end while 

			// 3. after each player has done its things we must: 
			//    check if there are more than 1 player still active, if only one he is the winner !

		}

		// if there are more than one player left then check showdown

		// this means compare best hand for each player 5 out of 7
		// determine best overall hand == winner ! 



}
