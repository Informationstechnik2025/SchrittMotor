/* 
* Automat.cpp
*
* Created: 14.05.2023 19:51:05
* Author: Thomas Heß
*/

 
#include <cstdint>
#include <stddef.h>  // für NULL

#include "Automat.h"



// default constructor
Automat::Automat()
{
    init();
} // Automat

// default destructor
Automat::~Automat()
{
} // ~Automat


void Automat::init()
{

	eineFSM.init(fsmApp,initState,evQueue,EventQueueSize,sizeof(fsmApp)/sizeof(State2State)); // sizeof(fsmApp)/sizeof(State2State) ... uint8_t num_of_entries

    
    
}

void Automat::sendEvent(Events e)
{
	eineFSM.sendEvent(e);
}

bool Automat::process_StateChange()
{
	eineFSM.StateChange();
    return true;
}



uint16_t Automat::fsm_get_timeInState()
{
    return eineFSM.get_timeInState();
}

void Automat::fsm_set_timeInState(uint16_t time_incr)
{
    eineFSM.set_timeInState(time_incr);
}




