/*
 * Automat_Transitionen.h
 *
 * Created: 04.11.2023 22:54:01
 *  Author: Thomas Heß
 */ 


#ifndef APPLICATIONTRANSITIONS_H_
#define APPLICATIONTRANSITIONS_H_

#include "Ereignisse_Transition_Oberklasse.h"

#include <stdint.h>


class Trans_Initialisierung_Stopp : public Transition
{
		// properties
		private:
	
		public:
			bool guard();
			bool action();
			Events getEvent();
			bool decision();

            Trans_Initialisierung_Stopp();
            ~Trans_Initialisierung_Stopp();

};



#endif /* APPLICATIONTRANSITIONS_H_ */