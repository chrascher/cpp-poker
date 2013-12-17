#include "RealPlayer.h"
#include "Table.h" 


// SEE .h file
Actions RealPlayer::playActionStep( Table * table ) {

	vector<Player *> players = table->getPlayers(); 
	// TODO geht infos from table about raise status and amount 
	// decide what do do

	Actions returnvalue;
	char i;
	bool validInput = true;

	do {
		cout << "Druecken Sie f fuer fold, c fuer call und check, r fuer raise oder a fuer all in:" << endl;
		cin >> i;
		validInput = true;
		switch(i)
			{
				case 'f':
					returnvalue = Actions::FOLD;
					break;
				case 'c':
					returnvalue = Actions::CALL; // CHECK;
					break;
					case 'r':
					returnvalue = Actions::RAISE;
					break;
				case 'a':
					returnvalue = Actions::ALL_IN;
					break;
				default:
					cout << "ungueltige Eingabe" << endl;
					validInput = false;
			}

	}while(validInput == false);


	if(returnvalue == Actions::FOLD) {
			cout << this->getPlayerId() << " folds" << endl;
			gameStatus = playerStatus::PS_FOLDED;
			       
	}

	if(returnvalue == Actions::CALL || returnvalue == Actions::CHECK ) {
		
		/* if(table->getRaiseAmount > currentBet) {
			cout << this->getPlayerId() << " calls" << endl;
			}
			else {
			cout << this->getPlayerId() << " checks" << endl;
			}
		*/
			gameStatus = playerStatus::PS_ACTIVE;

	}


	if(returnvalue == Actions::RAISE) {

			int validInput = true;
			int r;
			do {
				cout << "Geben Sie den gewuenschten Setzbetrag ein: " << endl;
				cin >> r;

				// check if enough money is available in your ... this->coinStack

				// if( table->checkRaiseAmount( r ) == false )  {
				   // validRaiseAmount == false; 
				   // cout "so geht das nicht.... " << endl; 
				//}	 

			} while(validInput == false ) ; 

			// impliemntiere last raised amount + player in table. damit wir das hier abfragen können.
			// int oldBet = this->getSingleBetPot(); 
			cout << this->getPlayerId() << " raises: " << r << endl;

			this->betCoins(r);

			gameStatus = playerStatus::PS_ACTIVE;

		}

	if(returnvalue == Actions::ALL_IN) {
		cout << this->getPlayerId() << " is all-in" << endl;

		gameStatus = playerStatus::PS_ALL_IN;
		
	}

	

	// TODO : if raise or ALLIN... transfer money ! IF exists enough money ! 

	return returnvalue; 
}



