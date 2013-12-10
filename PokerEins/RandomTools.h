#pragma once

#include <iostream>
#include <random>
#include <memory>


using namespace std; 

class RandomTools
{
public:


	static int getRandPercent(int percentMin, int percentMax) {

    random_device rd; // obtain a random number from hardware
    mt19937 eng(rd()); // seed the generator
    
	// uniform_int_distribution<> distr(1, 100); // define the range
	
	uniform_int_distribution<> distr(percentMin, percentMax ); // define the range

	return distr(eng); 

    //for(int n=0; n<52; ++n)
    //    std::cout << distr(eng) << ' '; // generate numbers


	}


};

