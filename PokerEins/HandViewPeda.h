#pragma once
#include "handRankingPeda.h"

class HandViewPeda :
	public HandRankingPeda
{
private:

public:

	HandViewPeda( vector<Card *> handToView) : HandRankingPeda(handToView) 
	{
		unsigned int HandValue = HandRankingPeda::overallHandValue;
	}

	~HandViewPeda(void)
	{
	}

	void displaypossibleCards()	// die bis zu 7 wertbaren Karten anzeigen
	{
		for (Card *i : checkHand)
			cout << *i << " ";
		cout << ">>>   ";
	}

	void displayHandFigure(unsigned int figure)	// Ausgabe der Figur inkl. Angabe von vorerst bis zu 2 "Highcards"
	{
		const char *pVTxt[] = {"?", "1!", "2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K", "A"};

		switch (figure)	// den bitshift hier kann man evtl. in einen Operator überladen
		{
			case 10:
				cout << "ROYAL FLUSH   -> " << endl << hex << HandRankingPeda::overallHandValue << dec << endl << endl;
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

