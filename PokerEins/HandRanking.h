#pragma once

#include <array>
#include <vector>

#include <algorithm>    // for max_element
#include <functional>   // for less
#include <iostream>     // for cout, endl
#include <vector>       // for vector


#include "card.h"
#include "Figure.h" 

using namespace std;


/*
 *
*/
class HandRanking {

	// SLOTS: die anzahl der gefundenen farben speichern wir in einem array ab
	// die poistion ist so wie im ENUM also ColorE.
	// ColorE:CLUBS hat den wert 1 
	// hier werden also je gefundenen CLUBS karte der wert dieses Slots um 1 erhöt
	// danach haben wir je slot die anzahl der karten in dieser farbe.
	array <int, 4> colorslot;		// CLUBS, DIAMOND, HEARTS, SPADE

	// konzept wie bei farben.
	array <int, 15> valueslot;      // X, X, 2, 3, 4, ....

	vector<Card *> checkHand; 

public:

	HandRanking( vector<Card *> handToRank ) {

		// check cards are >= 2  <=7 
		
		checkHand = handToRank;

		for( int & valueI : colorslot ) 
			valueI = 0; 

		int count = 0; 
		for( int j : valueslot ) 
			valueslot[count++] = 0; 

	}

	virtual ~HandRanking(void) {

	}

	void testMitIterationUeberKarten() {

		for( int i = 0; i < checkHand.size() ; i++ ) {
			Card * pCard = checkHand.at(i); 
			cout << *pCard << endl; 			
		}



	}



	FigureE rankThisHand() {

		for ( Card * p : checkHand ) {
			if( p != nullptr ) {
				colorslot[ p->getColor()]++;
				valueslot[ p->getValue()]++; 
			}
		}



		auto iterAuto =  std::max_element(valueslot.begin(), valueslot.end() );

		_Array_iterator<int, 15> iter =  std::max_element(valueslot.begin(), valueslot.end() );

		int index = std::distance(valueslot.begin(), iter);

		cout << "max element is: " << *iter << " at index pos " << index << endl; 



		// example for native array field:: 
		int valueslotNative[15] = { 0 }; 

		for( int iVal : valueslot ) 
			valueslotNative[15] = iVal; 
		int * maxEl = std::max_element(valueslotNative, valueslotNative + 15 );

	    std::cout << "Max element Native is " << *maxEl << " at position " << std::distance( valueslotNative, maxEl) << std::endl;

		

		return FigureE::onepair; 
	}



	

};

