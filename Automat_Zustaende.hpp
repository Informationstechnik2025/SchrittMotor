/*
 * Automat_Zustaende.h
 *
 * Created: 22.01.2023 10:32:23
 *  Author: Thomas Heß
 *  Implements all the states of the finite state machine
 *  ApplicationState States of FSM
 */ 


#ifndef CLASSAPPLICATIONSTATES_H_
#define CLASSAPPLICATIONSTATES_H_

#include "Zustand_Oberklasse.hpp"

#include <stdint.h> 

/*
 *  Initialisierungszustand
*/
class StateInitialisierung : public State {
  private:
  public:
    void entryAction();
    void exitAction();
    void doAction();

    StateInitialisierung();
    ~StateInitialisierung();
    
};

/*
 *  Stoppzustand
*/
class StateStopp : public State {
  private:
  public:
    void entryAction();
    void exitAction();
    void doAction();

    StateStopp();
    ~StateStopp();
    
};

class StateLinkslauf : public State {
  private:
  public:
    void entryAction();
    void exitAction();
    void doAction();

    StateLinkslauf();
    ~StateLinkslauf();
    
};

class StateRechtslauf : public State {
  private:
  public:
    void entryAction();
    void exitAction();
    void doAction();

    StateRechtslauf();
    ~StateRechtslauf();
    
};



#endif /* CLASSAPPLICATIONSTATES_H_ */