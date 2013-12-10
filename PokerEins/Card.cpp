

#include <iostream>

#include "Card.h"

using namespace std;



ostream& operator<<(ostream& ostr,const Card& c)
{
   // const char *pCTxt[] = {"?", "\5", "\6", "\4", "\3"};
	const char *pCTxt[] = {"?", "\5", "\4", "\3", "\6" };

   const char *pVTxt[] = {"?", "?", "2", "3", "4", "5", "6",
                          "7", "8", "9", "10", "J",
                          "Q", "K", "A"};

   ostr <<  pVTxt[c.value] << pCTxt[c.color];

   return ostr;
}

