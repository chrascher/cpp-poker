#pragma once

#include <array>
#include <vector>

#include <algorithm>    // for max_element
#include <functional>   // for less
#include <iostream>     // for cout, endl
#include <vector>       // for vector


#include "card.h"
#include "Figure.h" 

/*
 * Base Class for different implementations of hand rainkings
*/
class HandRankingBase {

protected: 
	vector<Card *> checkHand; 

	vector<Card *> resultHand; 

public:

	HandRankingBase(vector<Card *> handToRank ) {

		this->checkHand = handToRank;
	}

	virtual ~HandRankingBase(void)
	{
	}

    // if 2 cards are compared with the operator < we ONLY compare the VALUE 
	// but NOT the color 
    bool operator < (const HandRankingBase& node) const {
		return ( this->getHandValue() < node.getHandValue() );
    }

    bool operator > (const HandRankingBase& node) const {
		return ( this->getHandValue() > node.getHandValue() );
    }

    bool operator >= (const HandRankingBase& node) const {
		return ( this->getHandValue() >= node.getHandValue() );
    }

    bool operator <= (const HandRankingBase& node) const {
		return ( this->getHandValue() <= node.getHandValue() );
    }

    bool operator==(const HandRankingBase& node) const {

		if( this == &node) { // Same object?
			return true; 
		}

		return (this->getHandValue() == node.getHandValue() );
    }

	bool operator!=(const HandRankingBase& node) const {
		return ! (*this == node ); 
	}

   HandRankingBase& operator=(const HandRankingBase & rhs) {
							   // Check for self-assignment!
		if (this == &rhs)      // Same object?
		  return *this;        // skip self assignment, and just return *this.

		throw "error you can not assign a HandRanking to another card " ; 
   }


    // calculate figures rank this hand, and provide
    // the best hand as resultHand
	virtual FigureE rankThisHand() = 0 ; 


	// sub class MUST implement a value to compare all hands 
	virtual unsigned int getHandValue() const = 0;


	virtual vector<Card *>  getResultHand() {
		return resultHand; 
	}


   // if we have vectors of pointers we need an operator which compares the objects 
   // instead of the pointers 
   struct PointerCompare {
	   bool operator()(const HandRankingBase* l, const HandRankingBase* r) {
			return *l < *r;
		  }
		};

};

