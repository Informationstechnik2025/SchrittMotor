/*
 * Automat_Zustaende.cpp
 *
 * Created: 22.01.2023 10:41:44
 *  Author: Thomas Heß
 * Implementierung der Methoden entry(), exit() und do() für die einzelnen Zustandsklassen (die Objekte werden erst in ClassAutomat.cpp erzeugt)
 */ 

#include "Automat_Zustaende.hpp"
#include "Hardware_Methoden.hpp"
#include "Variable_Global.hpp"

#include <cstdint>
#include <stdint.h>
//=============================================================================
// Zustandsklasse StateInitialisierung
//=============================================================================
void StateInitialisierung::entryAction(){

    Motor::init();
    Display::init();

    ExtInterruptPins::init_extint_rechts();
    ExtInterruptPins::init_extint_links();
    ExtInterruptPins::init_extint_stopp();
    

    Timers::init_TIM7_interrupt();
    Timers::init_TIM6_interrupt();

    Bluetooth::init_bt();

    derAutomat.sendEvent(NoEvent); // Hiermit wird die Transition nach Bereit ausgelöst

}

void StateInitialisierung::exitAction(){

}

void StateInitialisierung::doAction(){

}

// default constructor
StateInitialisierung::StateInitialisierung()
{

}
// default destructor
StateInitialisierung::~StateInitialisierung()
{

}

//=============================================================================
// Zustandsklasse StateStopp
//=============================================================================
void StateStopp::entryAction() {

	Display::locate(0, 0);
    Display::print("Schrittmotor");

    Display::locate(0, 1);
    Display::print("Stopp           ");

    
}

//-----------------------------------------------------------------------------
void StateStopp::exitAction() {
	
}

//-----------------------------------------------------------------------------
void StateStopp::doAction() {
 
    
}	

// default constructor
StateStopp::StateStopp()
{

}
// default destructor
StateStopp::~StateStopp()
{

}

#pragma region Linkslauf
void StateLinkslauf::entryAction() {

	Display::locate(0, 0);
    Display::print("Schrittmotor");

    Display::locate(0, 1);
    Display::print("Linkslauf       ");

    derAutomat.setRichtung(false);
}

//-----------------------------------------------------------------------------
void StateLinkslauf::exitAction() {
	
}

//-----------------------------------------------------------------------------
void StateLinkslauf::doAction() {
 
    
}	

// default constructor
StateLinkslauf::StateLinkslauf()
{

}
// default destructor
StateLinkslauf::~StateLinkslauf()
{

}
#pragma endregion

#pragma region Rechtslauf
void StateRechtslauf::entryAction() {

	Display::locate(0, 0);
    Display::print("Schrittmotor");

    Display::locate(0, 1);
    Display::print("Rechtslauf      ");

    derAutomat.setRichtung(true);
}

//-----------------------------------------------------------------------------
void StateRechtslauf::exitAction() {
	
}

//-----------------------------------------------------------------------------
void StateRechtslauf::doAction() {
 
    
}	

// default constructor
StateRechtslauf::StateRechtslauf()
{

}
// default destructor
StateRechtslauf::~StateRechtslauf()
{

}
#pragma endregion
