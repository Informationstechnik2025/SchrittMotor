/* 
* main.cpp
*
* Created: 12.02.2023 22:37:38
* Author: Thomas Heß
*/

/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */
#undef __ARM_FP

#include "mbed.h"
#include "Automat.h"
#include "Hardware_Methoden.h"  // für Zugriff auf die Hardware (GPIO, UART, ADC, ...) z.B. für Polling
#include "Variable_Global.h"  // Definition der globalen Variablen, die von anderen Funktionen in anderen cpp-files benötigt werden
#include <cstdint>
#include <cstdio>



/************************************************************
 * Angeschlossene Hardware:
 *
 * Tasten:      Rechtslauf   PB_4     extInt, steigende Flanke
 *              Stopp:       PB_3     extInt, steigende Flanke
                Linkslauf:   PB_0     extInt, steigende Flanke
 *
 *
 *
 * 
 * Motor:       Anschluss A:    PC_3     
 *              Anschluss A/:   PC_2     
 *              Anschluss B:    PC_1
 *              Anschluss B/:   PC_0
 *
 * Tasten am Dabble-Gamepad (Digital) mit zugehörigem 2Byte-Hex-Code
 * Pfeil nach oben:     0x0001
 * Pfeil nach unten     0x0002
 * Pfeil nach links     0x0004
 * Pfeil nach rechts    0x0008
 * Start                0x0100
 * Select               0x0200
 * Dreieck              0x0400
 * Kreis                0x0800
 * Kreuz                0x1000
 * Quadrat              0x2000

 ************************************************************/

Automat derAutomat;  // Deklaration der globalen Variable derAutomat, die in Variable_Global.h extern definiert ist
                            // nur in einem cpp-file deklarieren, in den anderen cpp-files nur per 
                            // #include "Globals.h" verfügbar machen
                            // Im Konstruktor von Automat wird init() aufgerufen um die FSM zu initialisieren


int main()
{
       
	
    

	 // Globale Interruptfreigabe
	 __enable_irq();


    while (true) {

            
            

    


    derAutomat.process_StateChange();

    } // of while(true)

    return 1;
}
