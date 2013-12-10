
#pragma once

#include <iostream>
#include <ostream>
#include <time.h>
#include <set>
#include <algorithm>

// #include "CardFactory.h"

using namespace std; 

/*
	This class encacpsulates the available cards for the game
	the cards will be created on system startup and are then
	fixed for the overall app/gam. 
	thre are 52 cards 
	there are 4 colors
	each color will have 2 to 10 and jack, queen, king ace as dedicated cards
	for each color. so there are 13 cards per color
    jetzt auch im GIT	
*/ 
class Card {

public:
   enum ColorE {  CLUBS = 1, // kreuz
				  DIAMOND,   // karo 
				  HEARTS,     // herz
                  SPADE     // pick
			   };

   enum ValueE {TWO = 2, THREE, FOUR, FIVE,
                SIX, SEVEN, EIGHT, NINE, TEN, 
				JACK, QUEEN,KING, ACE };


private: 
   const unsigned cardUID; // unique cardID overall the cards; 
   ColorE color;           // farbe der karte
   ValueE value;           // wert der karte

private: 
	Card( ColorE col, ValueE val, unsigned cid) : color(col), value(val), cardUID(cid) {
	}
	

public: 

	~Card(void) {
	}


	ColorE getColor () {
		return color; 
	}

	ValueE getValue() {
		return value; 
	}

	// if 2 cards are compared with the operator < we ONLY compare the VALUE 
	// but NOT the color 
    bool operator<(const Card& node) const {
		return ( this->value < node.value );
    }

    bool operator > (const Card& node) const {
		return ( this->value > node.value );
    }

    bool operator >= (const Card& node) const {
		return ( this->value >= node.value );
    }

    bool operator <= (const Card& node) const {
		return ( this->value <= node.value );
    }

    bool operator==(const Card& node) const {

		if( this == &node) { // Same object?
			std::cout << "its the same !! " << std::endl; 
			return true; 
		}

		return (this->value == node.value && this->color == node.color );
    }

	bool operator!=(const Card& node) const {
		return ! (*this == node ); 
	}

   Card& operator=(const Card & rhs) {
							   // Check for self-assignment!
		if (this == &rhs)      // Same object?
		  return *this;        // skip self assignment, and just return *this.

		throw "error you can not assign a card to another card " ; 
   }


   friend class CardFactory; 
   friend std::ostream& operator<<(std::ostream& ostr,const Card& c);


   // if we have vectors of pointers we need an operator which compares the objects 
   // instead of the pointers 
   struct PointerCompare {
		  bool operator()(const Card* l, const Card* r) {
			return *l < *r;
		  }
		};

};


/*
 * 
 */ 
class ForEachCard {

	ostream &o;

public:
	ForEachCard(ostream &ostr): o(ostr) { }

	void operator() (const Card * element) {

		o << *element << endl;

	}
};


