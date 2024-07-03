/*
 * Automat_Transitionen.cpp
 *
 * Created: 12.02.2023 23:15:36
 *  Author: Thomas Heß
 */ 

#include <stdint.h>

#include "Automat_Transitionen.h"
#include "Hardware_Methoden.h" // Für die Transitionsaktionen
#include "Variable_Global.h" // Für Zugriff auf Methoden des Automaten


//=============================================================================
// Zustandsübergangsklasse Trans_Initialisierung_Stopp
//=============================================================================

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


