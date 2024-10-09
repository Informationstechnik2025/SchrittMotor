/*
 * Automat_Transitionen.h
 *
 * Created: 04.11.2023 22:54:01
 *  Author: Thomas Heß
 */ 


#ifndef APPLICATIONTRANSITIONS_H_
#define APPLICATIONTRANSITIONS_H_

#include "Ereignisse_Transition_Oberklasse.hpp"

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

class Trans_Linkslauf_Stopp : public Transition
{
		// properties
		private:
	
		public:
			bool guard();
			bool action();
			Events getEvent();
			bool decision();

            Trans_Linkslauf_Stopp();
            ~Trans_Linkslauf_Stopp();

};

class Trans_Rechtslauf_Stopp : public Transition
{
		// properties
		private:
	
		public:
			bool guard();
			bool action();
			Events getEvent();
			bool decision();

            Trans_Rechtslauf_Stopp();
            ~Trans_Rechtslauf_Stopp();

};

class Trans_Stopp_Linkslauf : public Transition
{
		// properties
		private:
	
		public:
			bool guard();
			bool action();
			Events getEvent();
			bool decision();

            Trans_Stopp_Linkslauf();
            ~Trans_Stopp_Linkslauf();

};

class Trans_Stopp_Rechtslauf : public Transition
{
		// properties
		private:
	
		public:
			bool guard();
			bool action();
			Events getEvent();
			bool decision();

            Trans_Stopp_Rechtslauf();
            ~Trans_Stopp_Rechtslauf();

};

#endif /* APPLICATIONTRANSITIONS_H_ */