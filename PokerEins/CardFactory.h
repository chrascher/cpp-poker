#pragma once

#include <iostream>
#include <random>
#include <array>

#include "Card.h" 

using namespace std; 

class CardFactory {


public:

	CardFactory(void)
	{
	}

	~CardFactory(void)
	{
	}

	void initializeCards(array<Card *, 52> & cards ) {

		
		unsigned int cardNumber = 0; 

		for( int colorI=Card::CLUBS; colorI <= Card::SPADE ; colorI++ ) {   //  int colorI = Card::CLUBS; colorI != Card::HEARTS; colorI++ ) {
			Card::ColorE colorEnum = static_cast<Card::ColorE>(colorI);
			for( int valueJ = 2; valueJ <=  Card::ACE ;  valueJ++) {
				Card::ValueE valueEnum = static_cast<Card::ValueE>(valueJ);
				
				// cout << "color: " << colorEnum << " value " << valueEnum << endl; 
				cards[cardNumber] = new Card(colorEnum, valueEnum, cardNumber); 

				cout << "next card: " << *cards[cardNumber] << endl; 


				cardNumber++; 
			}
		}
	}


};

