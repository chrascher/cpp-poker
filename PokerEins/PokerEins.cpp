// PokerEins.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include <iostream>
#include <random>
#include <memory>

#include "stdafx.h"
#include "PokerApp.h"

using namespace std; 
using namespace std::tr1; 

int _tmain(int argc, _TCHAR* argv[]) {

		PokerApp app; 

	try {

		app.initialize(); 

		app.run() ; 

	// TODO custom error object and catch more detailed  !! 

	} catch(...) {
		cout << "ein fehler ist aufgetreten" << endl; 
	}


	return 0;
}





/*
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 eng(rd()); // seed the generator
    std::uniform_int_distribution<> distr(1, 52); // define the range

    for(int n=0; n<52; ++n)
        std::cout << distr(eng) << ' '; // generate numbers

*/
