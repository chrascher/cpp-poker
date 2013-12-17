
#include "Table.h"
#include "SingleGame.h" 
#include "Player.h" 
#include "HandRankingBase.h"
#include "HandRankingPeda.h"

Table::Table(PokerApp & app) : app(app) , deck(app) , seats(9), minimumBet(2) {

	buttonPosition = -1; // ???
}


Table::~Table(void)
{
}

/*
 * see .h file 
*/
void Table::initialize(vector<Player * > players ) 
{
	this->players = players;

	buttonPosition = ++buttonPosition % seats ;		// = 0; warum nicht

	currentRound = PRE_START; 

	communityCards.clear();

	burnedCards.clear();

	deck.shuffleNewStack(); 

}

void Table::dealForTexasHoldem() 
{
	if (currentRound == Table::PRE_FLOP)
	{
		dealPocketCards(); 
	}
	else
	{
		dealCommunityCards();
	}
}

void Table::dealPocketCards() 
{
	for(int i = 0 ; i < (players.size()*2) ; i++ ) 
	{
		Player * nextPlayer = players.at(i % players.size());  // or use players[i]; 
		nextPlayer->receiveCard( deck.getNextCard() ) ; 
	}
}
void Table::dealCommunityCards() 
{
	this->burnedCards.push_back(deck.getNextCard());

	for (int i = 0; i < 3; i++)
	{
		this->communityCards.push_back(deck.getNextCard());
		if (currentRound != ON_FLOP) break;
	}
}

void Table::tellThemNextRound() 
{
	for(int i = 0 ; i < seats ; i++ ) 
	{
		Player * nextPlayer = players.at(i);  // or use players[i]; 
		
		SingleBet * oldBet = nextPlayer->resetSingleBet(); 
		if( oldBet != NULL ) 
		{
			this->pot.addCoins( oldBet->getCoins() ) ; 
			delete oldBet; 
		}
	}
}

void Table::tablePrepareForPreStart()
{
	// small blind will be forced to be set by player after button
	unsigned int smallBlind = buttonPosition + 1 ;
	players[smallBlind]->makeBlind( minimumBet/2 );

	// big blind will be enforce to player after small blind player
	unsigned int bigBlindPos = buttonPosition + 2 ;
	players[bigBlindPos]->makeBlind(  minimumBet  );

//	currentRound = PRE_FLOP;
}


void Table::tablePrepareForPreFlop() 
{
	dealForTexasHoldem();	// each player gets 2 cards:
}

void Table::tablePrepareForOnFlop() 
{
	dealForTexasHoldem();	// deal 3 community cards 
}

void Table::tablePrepareForOnTurn() 
{
	dealForTexasHoldem();	// open next 4. card
}

void Table::tablePrepareForOnRiver() 
{
	dealForTexasHoldem();	// open next 5. card 
}

void Table::tablePrepareForShowdown()  {

	vector<HandRankingBase *> rankings; 

	for( Player * next : players ) {

		if( next->getPlayerStatus() != PS_FOLDED ) {

			vector<Card *> handToRank ; 
			for(Card * card : communityCards ) {
				handToRank.push_back(card); 
			}

			vector<Card *> pocketCards = next->getPocketCards(); 
			for(Card * card : pocketCards ) {
				handToRank.push_back(card); 
			}

			HandRankingBase * ranking  = new HandRankingPeda(handToRank); 

			rankings.push_back(ranking); 

			sort(rankings.begin(), rankings.end(), HandRankingBase::PointerCompare() );


		}

	}


}

void Table::run()  
{
	// TODO :: button must be set to next button player for next singleGame

		for( int i = PRE_START; i <= SHOWDOWN; i++ ) 
		{
			this->currentRound = static_cast<BetRound>(i);

			if (currentRound != 1)		// darf PRE_FLOP die blins nicht abkassieren
				tellThemNextRound();	// and collect money // Peda: sollte das nicht am Ende der Schleife stehen???

			// todo:
			// 1. depending on bet round give 0 cardspre, then 3 cards, 1 card, or 1 card, or showdown
			if( PRE_START == currentRound)
			{
				tablePrepareForPreStart(); 
				continue;
			}
			if( PRE_FLOP == currentRound) 
				tablePrepareForPreFlop();
			if( ON_FLOP == currentRound) 
				tablePrepareForOnFlop();
			if( ON_TURN == currentRound) 
				tablePrepareForOnTurn();
			if( ON_RIVER == currentRound) 
				tablePrepareForOnRiver();
			if( SHOWDOWN == currentRound) 
			{
				tablePrepareForShowdown();
				break;
			}

			// 1.1. display action status on SCREEN (community cards + players active with tehre status and player-bet-size) 

			cout << endl << endl; 
			for( Card *j : communityCards ) 
				cout << *j << " - ";
			cout << endl; 

/*			for ( iter = communityCards.begin( ) ; iter != communityCards.end( ) ; iter++ ) {
			  Card * communityCards = *iter;
			  cout << *communityCards << " - ";
			}
*/
			// 2. now each player can perform its/his action 
			doActionsForPlayers( currentRound ); 

			// 3. after each player has done its things we must: 
			//    check if there are more than 1 player still active, if only one he is the winner !

		} // end for betrounds

			// if there are more than one player left then check showdown
			// this means compare best hand for each player 5 out of 7
			// determine best overall hand == winner ! 

} // end run 



void Table::doActionsForPlayers( BetRound currentRound ) {

	int currentPos; 

	if ( currentRound == PRE_FLOP ) {
		stepOutBetRoundPos = this->buttonPosition + 3 ; 
	} else {
		stepOutBetRoundPos = this->buttonPosition + 1 ; 
	}

	currentPos = stepOutBetRoundPos ; 

	bool firstRound = true; 

	// we start with minimum BET which was enforced by framework
	unsigned int lastRaiseAmount = minimumBet;  


	// for( int playerX = 0; i <= 8 ; playerX++ ) {
	while( currentPos != stepOutBetRoundPos || firstRound ) {
				
		firstRound = false; 

		Player * currentPlayer = this->players.at(currentPos); 
		// returns the action taken  == fold, call, raise, bet, all-in

		if (currentPos == 6)		// for debugging
			currentPlayer->setRaise();

		Actions action = currentPlayer-> playActionStep( this ); 

		cout << endl << "Player Action [0-Fold / 1-Check / 2-Call / 3-Raise / 4-All-IN]: >>>  " << action;	// Ausgabe der Action

		if(action == RAISE ) {
			// current player has raised, mark him,
			// restart loop over players, so they can check, fold, raise also 
			stepOutBetRoundPos = currentPos; 

			// CHECK if the player HAS really raised, and how much !! 
		}
		if(action == CALL ) {
			// CHECK if the player has called correclty, which means added the amount necessary to equals the current BET/RAISE
		}
		if(action == CHECK) {
			// check if the user is allowed to check. otherwise ... mhmmmm remove him from game ?? 
		}
		if(action == FOLD ) {
			// can fold every time. 
			// money will be collected after bet actions automatically with all other player pots 
			cout << "User has Folded: " << currentPlayer->getPlayerId() << endl; 
		}
		currentPos = ++currentPos % 9 ;	// % seats for overflow 
	} // end while 

}




