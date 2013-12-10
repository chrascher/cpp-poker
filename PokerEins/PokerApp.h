#pragma once

#include <array>

#include "Card.h" 
#include "CardFactory.h" 
#include "SingleBet.h"
#include "SingleGame.h"
#include "Player.h" 
#include "RealPlayer.h" 
#include "ComputerPlayer.h"
#include "Pot.h" 
#include "HandRankingBase.h"
#include "HandRankingCGS.h"

using namespace std; 

const char* const pNames[] = {
	"Joe Doe", "Thomas Atkins", "Anna Belle", "Henry VIII",
	"Boney M.", "Peter Alexander", "Pointer Sister", "Elvis Presley",
};

/*
  Class for the overall poker Application 
*/
class PokerApp {

private: 

	array<Card *, 52> cards; 

	vector<SingleGame * > games; 

	SingleGame * currentGame; 

	Player * currentPlayer; // currently ony one player

public:

	PokerApp(void) {

	}
	PokerApp(int a ) { // just a test constructor for usage with shared_ptr examples 
	}

	virtual ~PokerApp(void) {
	}

	bool isDebug() {
		return true;
	}

	array<Card *, 52> getCards() const {
		return cards;
	}
	
	void initialize () {

		// create and initialize cards 
		CardFactory factory;
		factory.initializeCards( cards ) ; 

		examplesForSortETC(); 

	}

	//
	// example usage code only 
	// comment out if not needed anymore 
	//
	void examplesForSortETC() {

		//
		// example for sorting the cards of POINTERS to really sort the objects not the pointer adresses 
		//
		// sort(cards.begin(), cards.end(), Card::PointerCompare() );


		for_each( cards.begin(), cards.end(), ForEachCard(cout) ) ; 

		for ( Card * p : cards ) {
			cout << "for " << *p << endl; 
		}

		int ddd[2]; 
		for ( int valueVonPosI : ddd ) {
			cout << "for " << valueVonPosI << endl; 
		}


		Card * pCard = cards[1];
		Card * pCard2 = cards[2];

		cout << "pointer address 1: " << &pCard << endl; 
		cout << "pointer address 2: " << &pCard2 << endl; 
		cout << "echtes objekt: " << *pCard2 << endl; 


		if( *pCard == *pCard2) {
			cout << "yes its equal" << endl; 
		}

		// create and initialize Figures 

		vector<Card * > hand ; 
		hand.push_back( cards[11] );
		hand.push_back( cards[12] );
		hand.push_back( cards[13] );

		HandRankingBase * ranking = new HandRankingCGS(hand) ; 

		ranking->rankThisHand(); 
	}


	void run() {

		// cards.begin(); 
		// vector<Card *> gameCards() ; 

		// ask user about game and anzahl compter spieler
		// currently everything is default 
		// cout << "Wieviele Computer Spieler sollen mitspielen ? " << endl; 
	
		currentGame  = new SingleGame(*this); 
	
		currentGame->initialize(buildPlayerList());

		currentGame->run(); 

		// currentGame->startGame(currentPlayer) ; 


		// create game
		// initiailze game with user, and x random players
		//     game --> create random stack for deck
		//     game --> seat player randomly
		//     game --> seat other random computer players
		// 

	}

	// build players with push_back or array index access. 
	// push_back is safer, index does not need memory re-location
	vector<Player * > buildPlayerList() {

		vector<Player * > players(9); // pre allocate size

		players[0] = getNextRealPlayer(); // replace position 1 
		// players.push_back(getNextRealPlayer());
		for (int i = 1; i <= 8; i++) {
			// push back to add new slot (will increase memory dynamically in vector)
			// players.push_back( getNextComputerPlayer(i) ); 
			
			// or replace position i, when you know it is valid
			players[i] = getNextComputerPlayer(i); 
		}

		return players;
	}

	ComputerPlayer * getNextComputerPlayer(unsigned i) {
		unsigned nextPlayerNameIndex = i % 8; 
		string playerName = pNames[nextPlayerNameIndex];
		
		// TODO determine or choose algorithm...

		return new ComputerPlayer(playerName);
	}


	RealPlayer * getNextRealPlayer( ) {

		string hName;
		cout << "Please enter your name: ";
		cin >> hName;
		cin.ignore(100, '\n');
		cout << "Welcome " << hName << "!" << endl;

		RealPlayer  * nextPlayer = new RealPlayer(hName);

		return nextPlayer; 
	}


};




