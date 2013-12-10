
#include <algorithm>
#include <time.h>

#include "Card.h"
#include "Deck.h"
#include "PokerApp.h"



Deck::Deck(PokerApp & app) : app(app)  {

	// we will use this card stack on the fly 
	// cards = app.getCards();

}



Deck::~Deck(void)
{
}

	// creates a new random stack for a new game to play
void Deck::shuffleNewStack() {

	srand(time(0));
	std::array<Card *, 52> cards = app.getCards();

	random_shuffle( cards.begin(), cards.end()); 

	if(app.isDebug() )
		debugRandomStack(cards); 

	cearStack();

	array <Card *, 52>::iterator iter;
	for ( iter = cards.begin( ) ; iter != cards.end( ) ; iter++ ) {
		Card * card = *iter;
		cardStack.push(card);
	}
}

void inline Deck::cearStack() {
	while ( ! cardStack.empty() ) {
		cardStack.pop();
	}
}

void Deck::debugRandomStack( std::array<Card *, 52> & cards ) {
	array <Card *, 52>::iterator iter;
    for ( iter = cards.begin( ) ; iter != cards.end( ) ; iter++ ) {
	  Card * card = *iter;
      cout << *card << " ";
	  // or may use this:  twice dereferencing 
	  // cout << "or: " << **iter << " "; 
   }
   cout << endl; 
}
