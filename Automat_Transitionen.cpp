/*
 * Automat_Transitionen.cpp
 *
 * Created: 12.02.2023 23:15:36
 *  Author: Thomas Heß
 */ 

#include <stdint.h>

#include "Automat_Transitionen.hpp"
#include "Hardware_Methoden.hpp" // Für die Transitionsaktionen
#include "Variable_Global.hpp" // Für Zugriff auf Methoden des Automaten



#pragma region Trans_Initialisierung_Stopp
// default constructor
Trans_Initialisierung_Stopp::Trans_Initialisierung_Stopp()
{
    ereignis = NoEvent; // unbedingter Übergang, also muss am Ende der entry() für Initialieierung
                        // sendEvent(NoEvent) kommen um diesen Übergang auszulösen.
}

bool Trans_Initialisierung_Stopp::guard()
{
    return true;
}
bool Trans_Initialisierung_Stopp::action()
{
    return true;
}
Events Trans_Initialisierung_Stopp::getEvent()
{
    return ereignis;
}
bool Trans_Initialisierung_Stopp::decision()
{
    return true;
}

// default destructor
Trans_Initialisierung_Stopp::~Trans_Initialisierung_Stopp()
{

}
#pragma endregion 

#pragma region Trans_Linkslauf_Stopp

// default constructor
Trans_Linkslauf_Stopp::Trans_Linkslauf_Stopp()
{
    ereignis = TasterStopp;
}

bool Trans_Linkslauf_Stopp::guard()
{
    return true;
}
bool Trans_Linkslauf_Stopp::action()
{
    Timers::TIM6_stopp(); //TIM6 stoppen
    return true;
}
Events Trans_Linkslauf_Stopp::getEvent()
{
    return ereignis;
}
bool Trans_Linkslauf_Stopp::decision()
{
    return true;
}

// default destructor
Trans_Linkslauf_Stopp::~Trans_Linkslauf_Stopp()
{

}
#pragma endregion

#pragma region Trans_Rechtslauf_Stopp

// default constructor
Trans_Rechtslauf_Stopp::Trans_Rechtslauf_Stopp()
{
    ereignis = TasterStopp;
}

bool Trans_Rechtslauf_Stopp::guard()
{
    return true;
}
bool Trans_Rechtslauf_Stopp::action()
{
    Timers::TIM6_stopp();
    return true;
}
Events Trans_Rechtslauf_Stopp::getEvent()
{
    return ereignis;
}
bool Trans_Rechtslauf_Stopp::decision()
{
    return true;
}

// default destructor
Trans_Rechtslauf_Stopp::~Trans_Rechtslauf_Stopp()
{

}
#pragma endregion


#pragma region Trans_Stopp_Linkslauf

// default constructor
Trans_Stopp_Linkslauf::Trans_Stopp_Linkslauf()
{
    ereignis = TasterLinks;
}

bool Trans_Stopp_Linkslauf::guard()
{
    return true;
}
bool Trans_Stopp_Linkslauf::action()
{
    Timers::TIM6_start();
    return true;
}
Events Trans_Stopp_Linkslauf::getEvent()
{
    return ereignis;
}
bool Trans_Stopp_Linkslauf::decision()
{
    return true;
}

// default destructor
Trans_Stopp_Linkslauf::~Trans_Stopp_Linkslauf()
{

}
#pragma endregion

#pragma region Trans_Stopp_Rechtslauf

// default constructor
Trans_Stopp_Rechtslauf::Trans_Stopp_Rechtslauf()
{
    ereignis = TasterRechts;
}

bool Trans_Stopp_Rechtslauf::guard()
{
    return true;
}
bool Trans_Stopp_Rechtslauf::action()
{
    Timers::TIM6_start();
    return true;
}
Events Trans_Stopp_Rechtslauf::getEvent()
{
    return ereignis;
}
bool Trans_Stopp_Rechtslauf::decision()
{
    return true;
}

// default destructor
Trans_Stopp_Rechtslauf::~Trans_Stopp_Rechtslauf()
{

}
#pragma endregion
