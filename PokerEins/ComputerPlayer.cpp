#include "ComputerPlayer.h"




ComputerPlayer::~ComputerPlayer(void)
{
}


	// virtual see player 
Actions ComputerPlayer::playActionStep( Table * table ) {

	return Actions::CHECK; 
}
