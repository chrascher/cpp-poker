#pragma once

#include <array>
#include <vector>

#include <algorithm>    // for max_element
#include <functional>   // for less
#include <iostream>     // for cout, endl
#include <vector>       // for vector


#include "card.h"
#include "Figure.h" 
#include "HandRankingBase.h" 

using namespace std;


/*
 * Example for a possible value count object. 
 * so they can be sorted seperately accourding to their count and value
 * 
 * class to collect the number of cards for each card value 
 * e.g. 4 cards for queens
*/
class ValueCount {

	Card::ValueE cardValue; 
	
	unsigned int count; 

public: 
	ValueCount(Card::ValueE forCard) {
		this->cardValue = forCard; 
		this->count = 0;
	}

	// Order by count and sub order by cardValue
    bool operator > (const ValueCount& node) const {
		
		if( this->count == node.count ) {
			return this->cardValue > node.cardValue; 
		}
		return this->count > node.count; 
    }

	ValueCount & operator++() {
		this->count++; 
		return *this;
	}

}; 

/*
 * Example Class Count IF for STL count to count if value euqals value
*/
class CountIf {

	// value to search
	Card::ValueE value;

public:
	CountIf( Card::ValueE value ) {
		this->value = value; 
	}

	// operator () instead of function:
	//     bool CountIf (const Card * element) 
	bool operator() (const Card * element) {
		return (value == element->getValue() ) ; 
	}

}; 

/*
 *  Provides a lot of example code and usage for STL count, countif 
 *  sorting and other stl utility methods
 */
class HandRankingCGS  : public HandRankingBase {

	// SLOTS: die anzahl der gefundenen farben speichern wir in einem array ab
	// die poistion ist so wie im ENUM also ColorE.
	// ColorE:CLUBS hat den wert 1 
	// hier werden also je gefundenen CLUBS karte der wert dieses Slots um 1 erhöt
	// danach haben wir je slot die anzahl der karten in dieser farbe.
	array <int, 5> colorslot;		// 0, CLUBS, DIAMOND, HEARTS, SPADE

	// konzept wie bei farben.
	array <int, 15> valueslot;      // X, X, 2, 3, 4, ....

	// an overall integer number generated to be able to overall compare all hand and figurues
	// it guarantees that figures are ordered correctly, and wtihin figures they are 
	// ordered accourding to their card and highcard values
	// SEE integer alogrithm below ! 
	unsigned int overallHandValue;

public:

	HandRankingCGS( vector<Card *> handToRank ) : HandRankingBase(handToRank) {

		for( int & valueI : colorslot ) 
			valueI = 0; 

		int count = 0; 
		for( int j : valueslot ) 
			valueslot[count++] = 0; 

		overallHandValue = 0; 
	}

	~HandRankingCGS(void) {

	}

	// sub class MUST implement a value to compare all hands 
	unsigned int getHandValue() const {
		return overallHandValue; 
	}


	// ONLY doing examples here !! !!! 
	// overwrite implement ranking
	FigureE rankThisHand() {

		for ( Card * p : checkHand ) {
			if( p != nullptr ) {
				colorslot[ p->getColor()]++;
				valueslot[ p->getValue()]++; 
			}
		}

		//
		// example for max_elements
		// with keyword auto and iter 
		//
		auto iterAuto =  std::max_element(valueslot.begin(), valueslot.end() );

		_Array_iterator<int, 15> iter =  std::max_element(valueslot.begin(), valueslot.end() );


		//
		// example for distance 
		//
		int index = std::distance(valueslot.begin(), iter);

		cout << "max element is: " << *iter << " at index pos " << index << endl; 

		//
		// example for native array field and its usage with max_element template algorithm 
		// 
		int valueslotNative[15] = { 0 }; 

		int i = 0;
		for( int iVal : valueslot ) // initialize native array with values from std:array valueslot
			valueslotNative[i] = iVal; 

		int * maxEl = std::max_element(valueslotNative, valueslotNative + 15 );

	    std::cout << "Max element Native is " << *maxEl << " at position " << std::distance( valueslotNative, maxEl) << std::endl;


		//
		// Example using count_if STL algorithm
		//
		int result = count_if(checkHand.begin(), checkHand.end(), CountIf( Card::ACE ) ); 
		cout << "count_if aces in vector " << result << endl ; 

		//
		// Example for count if a specific object is found with ==
		//         using first element (card) of vector to search for 
		//
		int resultElement = count(checkHand.begin(), checkHand.end(), *checkHand.begin() ); 
		cout << "count aces in vector " << resultElement << endl ; 


		return FigureE::onepair; 
	}

	//
	// Beispiele zum Iterieren über einen vector
	//
	void testBeispielMitIterationUeberKarten() {

		for( int i = 0; i < checkHand.size() ; i++ ) {
			Card * pCard = checkHand.at(i); 
			cout << *pCard << endl; 			
		}
	}

};

