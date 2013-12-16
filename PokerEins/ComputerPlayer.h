#pragma once
#include "player.h"


class ComputerPlayer : public Player
{

public:
	ComputerPlayer(string playerName) : Player(playerName) {

	}

	~ComputerPlayer(void);
	
	void npcRaise(){}
	void test(){}
};

