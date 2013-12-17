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
/*
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

}; */

/*
 * Example Class Count IF for STL count to count if value euqals value
*/
/*
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

}; */

/*
 *  Provides a lot of example code and usage for STL count, countif 
 *  sorting and other stl utility methods
 */
class HandRankingPeda  : public HandRankingBase {

private:

//	array<Card *, 7> checkHand; 

	unsigned int straighthelp;	// diese werte könnten in ein array/feldliste zusammengefasst werden, macht das Sinn
	unsigned int straighthigh;
	unsigned int fourhigh;
	unsigned int threehigh; 
	unsigned int threelow;
	unsigned int pairhigh;
	unsigned int pairlow;
	unsigned int highcard;
	unsigned int sec_highcard;
	unsigned int trd_highcard;
	unsigned int fou_highcard;
	unsigned int fiv_highcard;

	int flusharraypos;
	bool flush;


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

public:

	unsigned int overallHandValue;

	// ich fände es wäre übersichtlicher mit 0. 0 = nix(Highcard) / 1 = 1 Pair / 2 = 2 Pair / 3 = 3ling ich hab aber bei der ausgabe ein Problem weil die führenden Nullen nicht angezeigt werden
	typedef enum	{ ILLEGALHANDVALUE = 0,
//					FIV_HIGHCARD = 0x1,			// Multiplikator
					FOU_HIGHCARD = 0x10,		// Multiplikator
					TRD_HIGHCARD = 0x100,		// Multiplikator
					SND_HIGHCARD = 0x1000,		// Multiplikator
					FST_HIGHCARD = 0x10000,		// Multiplikator
					SND_INDEXCARD = 0x100000,	// Multiplikator
					FST_INDEXCARD = 0x1000000,	// Multiplikator
					HIGHCARD = 0x10000000,		// Handwert
					PAIR = 0x20000000,			// Handwert
					TWOPAIR = 0x30000000,		// Handwert
					THREEoaK = 0x40000000,		// Handwert
					STRAIGHT = 0x50000000,		// Handwert
					FLUSH = 0x60000000,			// Handwert
					FULL = 0x70000000,			// Handwert
					FOURoaK = 0x80000000,		// Handwert
					STRAIGHTFLU = 0x90000000,	// Handwert
					ROYALFLU = 0xA0000000		// Handwert
					} eHandValue;	


	HandRankingPeda( vector<Card *> handToRank ) : HandRankingBase(handToRank) 
	{
		initialize();
	}

	~HandRankingPeda(void) {}

	unsigned int handvalue (int SpielerNr)			// möglicherweise mit int Parameter um auch einzelne Cards (Highcards abrufen zu können?
	{
		cout << endl << "using Peda`s handvalue()! [Debug Info]" << endl;

		displaypossibleCards();						// zeigt die bis zu 7 für die Hand verfügbaren Karten an

		createvalueslots();							// füllt colorslot und valueslot für die jeweilige Hand

		createvalueablecount();						// erzeugt einen eindeutigen Zahlenwert(hex) für die jeweilige Hand

		displayHandFigure(overallHandValue >> 28);	// erste Stelle der hex-Zahl wird als Parameter verwendet

		return overallHandValue;					// gibt den eindeutigen Zahlenwert für die jeweilige Hand zurück
	}

	// sub class MUST implement a value to compare all hands 
	unsigned int getHandValue() const {
		return overallHandValue; 
	}


	// ONLY doing examples here !! !!! 
	// overwrite implement ranking
	FigureE rankThisHand() 
	{
		handvalue(0);

		return FigureE::onepair; 
	}

private:

	void initialize()
	{
		straighthelp = 0;		// diese werte könnten in ein array zusammengefasst werden
		straighthigh = 0;
		fourhigh = 0;
		threehigh = 0;
		threelow = 0;
		pairhigh = 0;
		pairlow = 0;
		highcard = 0;
		sec_highcard = 0;
		trd_highcard = 0;
		fou_highcard = 0;
		fiv_highcard = 0;
		overallHandValue = 0;
		flusharraypos = 0;

		flush = false;

		for( int & valueI : colorslot ) // Schleife für STL array mittels Referenz
			valueI = 0; 

		int count = 0; 
		for( int j : valueslot )  // Schleife für STL array
			valueslot[count++] = 0; 

// Löschen der Slots mittels for Schleife
/*
for (int iclear = 0; iclear < 15; iclear++)
		{
			valueslot[iclear] = NULL;
			if (iclear<5) colorslot[iclear] = NULL;
		}*/
	}

	void displaypossibleCards()	// die bis zu 7 wertbaren Karten anzeigen
	{
		for (Card *i : checkHand)
			cout << *i << " ";

/*		for (int icheck = 0; icheck < 7; icheck++)
		{
			if (checkHand[icheck]==NULL) break;		// soll aus der for schleife springen wenn keine Karte mehr verfügbar ist
			cout << *checkHand[icheck] << " ";
		}*/
		cout << ">>>   ";
	}

	void createvalueslots()	// füllen der Slots
	{
		// füllen der Slots mittels STL array Funktion
		for ( Card * p : checkHand ) 
		{
			if( p != nullptr ) {
				colorslot[ p->getColor()]++;
				valueslot[ p->getValue()]++; 
			}
		}

		// füllen der Slots mittels Schleife
/*		for (int islot = 0; islot < 7; islot++)				
		{
			if (checkHand[islot]==NULL) break;		// soll aus der for schleife springen wenn keine Karte mehr verfügbar ist
			colorslot[checkHand[islot]->getColor()-1]++;
			valueslot[checkHand[islot]->getValue()]++;
		}*/
	}

	void createvalueablecount()		// erzeugt einen eindeutigen Zahlenwert(hex) für die jeweilige Hand
	{
		bool test = false;
		checkforflush();			// prüft ob ein Flush vorliegt und eliminiert die andersfarbigen Karten

		createhighcards();			// erzeugt die Highcards für die jeweilige Hand

		// erkennt einen RayolFlush und berechnet den eindeutigen Handwert
		if (straighthigh == (14 * FST_INDEXCARD) && flush)
			overallHandValue = ROYALFLU;

		// erkennt ein Straight Flush und berechnet den eindeutigen Handwert
		else if (straighthigh != 0 && flush)
			overallHandValue = STRAIGHTFLU
							 + straighthigh;

		// erkennt eine Straße und berechnet den eindeutigen Handwert
		else if (straighthigh != 0)
			overallHandValue = STRAIGHT 
 							 + straighthigh;

		// erkennt einen Vierling und berechnet den eindeutigen Handwert
		if (fourhigh != 0)
			overallHandValue = FOURoaK
							 + fourhigh
							 + highcard;

		// erkennt ein Full und berechnet den eindeutigen Handwert
		if (threehigh != 0 && ( pairhigh != 0 || threelow != 0))
			overallHandValue = FULL 
							 + threehigh 
							 + threelow;

		// erkennt einen Drilling und berechnet den eindeutigen Handwert
		else if (threehigh != 0 && straighthigh == 0 && fourhigh == 0)
			overallHandValue = THREEoaK
 							 + threehigh
 							 + highcard
							 + sec_highcard;

		// erkennt einen Flush und berechnet den eindeutigen Handwert
		else if (flush && straighthigh == 0 && fourhigh == 0)
			overallHandValue = FLUSH
							 + highcard
							 + sec_highcard
							 + trd_highcard
							 + fou_highcard
							 + fiv_highcard;

		// erkennt 2 Paar und berechnet den eindeutigen Handwert
		if (pairhigh != 0 && pairlow != 0 && threehigh == 0 && straighthigh == 0)
			overallHandValue = TWOPAIR
							 + pairhigh
							 + pairlow
							 + highcard;

		// erkennt ein Paar und berechnet den eindeutigen Handwert
		if (pairhigh != 0 && pairlow == 0 && threehigh == 0 && straighthigh == 0 && fourhigh == 0)
			overallHandValue = PAIR
							 + pairhigh
							 + highcard
							 + sec_highcard
							 + trd_highcard;

		// erkennt Highcards und berechnet den eindeutigen Handwert
		if (highcard != 0 && straighthigh == 0 && fourhigh == 0 && threehigh == 0 && pairhigh == 0 && !flush)
			overallHandValue = HIGHCARD
							 + highcard
							 + sec_highcard
							 + trd_highcard
							 + fou_highcard
							 + fiv_highcard;
	}

	void checkforflush ()		// löschen alle Karten die nicht zum Flush gehören und sortieren der restlichen Karten
	{
		flusharraypos = 0;

		for (int icol = 0; icol < 4; icol++)	// sucht die Farbe des Flushes
		{
			if ( colorslot[icol] >= 5)  		// erkennt die Farbe des Flushes
			{
				flush = true;

				for (int j = 0; j < 7; j++)
				{
					if ( checkHand[j]!=NULL )					// soll aus der for schleife springen wenn keine Karte mehr verfügbar ist
					{
						if ( checkHand[j]->getColor() == icol+1 )	// verschiebt flushzugehörige Karten
						{
							checkHand[flusharraypos++] = checkHand[j];
							if (flusharraypos-1 != j)
								checkHand[j] = NULL;
						}
						else
						{
							valueslot[checkHand[j]->getValue()]--;
							checkHand[j]=NULL;
						}
					}
				}
				break;	// dadurch soll icol erhalten bleiben als Information welche Farbe der Flush hat
			}
		}	
	}

	void createhighcards()
	{
		for (int ivalslot = 14; ivalslot >= 0 ; ivalslot--)		// valueslot von 14-0 untersuchen (bis 1 würde reichen aber ich nutze die Null um die Straßenwerte zurückzusetzen wenn A uod 1 uod 3 uod 4 gezählt werde. Das könnte ich auch über ein zusätzliches if machen. Was ist da besser?)
		{
			if (valueslot[ivalslot]!=0 && straighthelp == 0)	// höchste Karte der Straße erkennen
				straighthigh = ivalslot * FST_INDEXCARD;
			
			if (valueslot[ivalslot]!=0 || (ivalslot == 1 && valueslot[14] != 0))// Straßenzähler erhöhen (oder ist um Asse auch als 1 zu werten)
				straighthelp++;
			else if (straighthelp < 5 && straighthelp != 0)		// Straßenwerte zurücksetzen
				straighthelp = 0, straighthigh = 0;

			if (valueslot[ivalslot]==4)							// Vierling erkennen (Vorsicht möglicherweise Paar mit Wert höher als Highcard)
				fourhigh = ivalslot * FST_INDEXCARD;
			if (fourhigh != 0 && ((pairhigh / 256) > highcard))	// Paar höher als Highcard gilt als Highcard
				highcard = pairhigh / 256;						
			if (fourhigh != 0 && (threehigh != 0))				// Drilling höher als Highcard gilt als Highcard
				highcard = threehigh / 256;						
			
			if (valueslot[ivalslot]==3 && threehigh == 0)		// höchsten Drilling erkennen
				threehigh = ivalslot * FST_INDEXCARD;
			else if (valueslot[ivalslot]==3)					// zweithöchsten Drilling erkennen 	
				threelow = ivalslot * SND_INDEXCARD;

			if (valueslot[ivalslot]==2 && pairhigh == 0)		// höchstes Paar erkennen
				pairhigh = ivalslot * FST_INDEXCARD;
			else if (valueslot[ivalslot]==2 && pairlow == 0)	// zweithöchstes Paar erkennen (Vorsicht möglicherweise 3. Paar mit Wert höher als Highcard)
				pairlow = ivalslot * SND_INDEXCARD;
			else if (valueslot[ivalslot]==2 && highcard == 0)	// drittes Paar höher als Highcard gilt als Highcard
				highcard = ivalslot * FST_HIGHCARD;

			if (valueslot[ivalslot]==1 && highcard == 0)		//	Highcards erkennen
				highcard = ivalslot * FST_HIGHCARD;
			else if (valueslot[ivalslot]==1 && sec_highcard == 0)
				sec_highcard = ivalslot * SND_HIGHCARD;
			else if (valueslot[ivalslot]==1 && trd_highcard == 0)
				trd_highcard = ivalslot * TRD_HIGHCARD;
			else if (valueslot[ivalslot]==1 && fou_highcard == 0)
				fou_highcard = ivalslot * FOU_HIGHCARD;
			else if (valueslot[ivalslot]==1 && fiv_highcard == 0)
				fiv_highcard = ivalslot;
		}
		if (threelow == 0 && threehigh != 0)		// Full Korrektur 
			threelow = pairhigh / 16;
	}

	void displayHandFigure(int figure)	// Ausgabe der Figur inkl. Angabe von vorerst bis zu 2 "Highcards"
	{
		const char *pVTxt[] = {"?", "1!", "2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K", "A"};

		switch (figure)	// den bitshift hier kann man evtl. in einen Operator überladen
		{
			case 10:
				cout << "ROYAL FLUSH   -> " << endl << hex << overallHandValue << dec << endl << endl;
				break;
			case 9:
				cout << "STRAIGHT FLUSH-> " << pVTxt[straighthigh>>24] << "-high" << endl << hex << overallHandValue << dec << endl << endl;
				break;
			case 8:
				cout << "FOUR oa KIND  -> " << pVTxt[fourhigh>>24] << "'s, " << "Highcard: " << pVTxt[highcard>>16] << endl << hex << overallHandValue << dec << endl << endl;
				break;
			case 7:
				cout << "FULL HOUSE    -> Drilling: " << pVTxt[threehigh>>24] << "'s, Pair: " << pVTxt[threelow>>20] << "'s" << endl << hex << overallHandValue << dec << endl << endl;
				break;
			case 6:
				cout << "FLUSH         -> " << pVTxt[highcard>>16] << endl << "-high" << endl << hex << overallHandValue << dec << endl << endl;
				break;
			case 5:
				cout << "STRAIGHT      -> " << pVTxt[straighthigh>>24] << "-high" << endl << hex << overallHandValue << dec << endl << endl;
				break;
			case 4:
				cout << "THREE oa KIND -> " << pVTxt[threehigh>>24] << "'s, " << "Highcard: " << pVTxt[highcard>>16] << ", 2nd Highcard: " << pVTxt[sec_highcard>>12] << endl << hex << overallHandValue << dec << endl << endl;
				break;
			case 3:
				cout << "TWO PAIR      -> " << pVTxt[pairhigh>>24] << "'s and " << pVTxt[pairlow>>20] << "'s" << ", Highcard: " << pVTxt[highcard>>16] << endl << hex << overallHandValue << dec << endl << endl;
				break;
			case 2:
				cout << "ONE PAIR      -> " << pVTxt[pairhigh>>24] << "'s, " << "Highcard: " << pVTxt[highcard>>16] << ", 2nd Highcard: " << pVTxt[sec_highcard>>12] << endl << hex << overallHandValue << dec << endl << endl;
				break;
			case 1:
				cout << "HIGHCARD      -> " << pVTxt[highcard>>16] << ", 2nd Highcard: " << pVTxt[sec_highcard>>12] << endl << hex << overallHandValue << dec << endl << endl;
				break;
			default:
				break;
		}
	}
};

