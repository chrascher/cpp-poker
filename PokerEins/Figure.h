#pragma once


	enum FigureE {
			onepair=10000,
			twopair=20000,
			threeofakind=30000,
			straight=40000,
			flush=50000,
			fullhouse=60000,
			fourofakind=70000,
			straightflush=80000,
			royalflush=90000
		};



class Figure {
public:


public:
	Figure(void);
	~Figure(void);

	bool checkroyalflush(){}
	bool checkstraightflush(){}
	bool checkfourofakind(){}
	bool checkfullhouse(){}
	bool checkflush(){}
	bool checkstraight(){}
	bool checkthreeofakind(){}
	bool checktwopair(){}
	bool checkonepair(){}

	unsigned int calculate(int a){}


	void checkfigures(/*vector 7 karten*/){
			if(checkroyalflush()){
				calculate(royalflush);

			}else if(checkstraightflush()){
				calculate(straightflush);

			}else if (checkfourofakind()){
				calculate(fourofakind);

			}else if(checkfullhouse()){
				calculate(fullhouse);

			}else if(checkflush()){
				
				// calculate( flush );

			}else if(checkstraight()){
				calculate(straight);

			}else if(checkthreeofakind()){
					calculate(threeofakind);

			}else if(checktwopair()){
				calculate(twopair);

			}else if(checkonepair()){
				calculate(onepair);

			}
	}
};

