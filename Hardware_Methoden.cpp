/*
 * Hardware_Methoden.cpp
 *
 * Created: 21.01.2023 17:29:12
 *  Author: Thomas Heß
 */ 
#include <cstdint>
#undef __ARM_FP
#include "Hardware_Methoden.hpp"
#include "Hardware_Definitionen.hpp"
#include "mbed.h"
#include "TextLCD_I2C.hpp"
#include "Variable_Global.hpp" // für globalen Zugriff auf den Automaten derAutomat, speziell für isr

#include <cstdio>
#include <stdarg.h>


// Für Sturm-Board, um das LC-Display per I2C ansteuern zu können obwohl es an PA_11, PA_12
// angeschlossen ist. Es müssen auf dem Morpho-Header folgende Verbindungen gesteckt werden:
// SCL: PA_11 <-> PB_8
// SDA: PA_12 <-> PB_9

DigitalIn scl(PA_11,PullUp);  
DigitalIn sda(PA_12,PullUp);

PortOut stepper(MOTOR_PORT,0x000F);

InterruptIn S_rechts(S_RECHTS);
InterruptIn S_links(S_LINKS);
InterruptIn S_stopp(S_STOPP);




I2C i2c_lcd(I2C_SDA, I2C_SCL); // PB_9, PB_8 
// I2C i2c_lcd(PB_9, PB_8);
// I2C-Adresse 0x27 - 16 Spalten und 2 Zeilen 
// LCD20x4 → 20 Spalten und 4 Zeilen 
TextLCD_I2C LC_Display(&i2c_lcd, 0x27<<1, TextLCD_I2C::LCD16x2);


BufferedSerial blue(BT_TX, BT_RX); // TX,RX
DigitalOut enable(BT_EN, 0); // Enable auf 0, also kein Konfigurationsmodus


//=============================================================================
// MOTOR
//=============================================================================
void Motor::init()
{
	stepper.write(0x0F); // Alle Motoranschlüsse H-Pegel  
}

void Motor::schritt(uint8_t pVollschritt)
{
    stepper.write(pVollschritt);
}




//=============================================================================
// LCD
//=============================================================================

void Display::init()
{
    LC_Display.setBackLight(true);
    LC_Display.cls(); 
    LC_Display.locate(0,0); // (column,row) 
    
}

void Display::locate(int column, int row)
{
    LC_Display.locate(column, row);
}

// Wrapper for printf(), according to https://stackoverflow.com/questions/20639632/how-to-wrap-printf-into-a-function-or-macro

void Display::print(const char *format, ...)
{
    va_list args;
    va_start(args, format);

    LC_Display.vprintf(format, args);


    va_end(args);
}

//=============================================================================
// Serial ... Serieller Monitor
//=============================================================================

void Serial::print(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    vprintf(format, args);

}

//=============================================================================
// Externe InterruptPins
//=============================================================================

void ExtInterruptPins::init_extint_rechts()
{
    S_rechts.mode(PullDown);
    S_rechts.rise(&isr_rechts);
    S_rechts.enable_irq();
}

void ExtInterruptPins::init_extint_links()
{
    S_links.mode(PullDown);
    S_links.rise(&isr_links);
    S_links.enable_irq();
}

void ExtInterruptPins::init_extint_stopp()
{
    S_stopp.mode(PullDown);
    S_stopp.rise(&isr_stopp);
    S_stopp.enable_irq();
}

void ExtInterruptPins::isr_rechts(void)
{
    S_rechts.rise(NULL);
    derAutomat.sendEvent(TasterRechts);
    S_rechts.rise(&isr_rechts);
}

void ExtInterruptPins::isr_links()
{
    S_links.rise(NULL);
    derAutomat.sendEvent(TasterLinks);
    S_links.rise(&isr_links);
}

void ExtInterruptPins::isr_stopp()
{
    S_stopp.rise(NULL);
    derAutomat.sendEvent(TasterStopp);
    S_stopp.rise(&isr_stopp);   
}


//=============================================================================
// Timer
//=============================================================================

void Timers::init_TIM7_interrupt()
{
        // TIM7 mit Takt versorgen, Bit 5 in RCC_APB1ENR
    RCC->APB1ENR |= (1 << TIM7EN); // RCC_APB1ENR |= 0b 100000: RCC_APB1ENR.TIM7EN=1
    
    // TIM7 stoppen
    TIM7->CR1 &= ~(1 << CEN); // TIM7_CR1.CEN = 0; Bit 0
    
    // Prescaler auf 31999 setzen -A Taktsignal wird durch 32000 geteilt
    // Bei fCLK = 32MHz ergibt dies 1ms fCNT
    TIM7->PSC = 31999; // (1ms * 32MHz)-1 = 31999
    
    // TIM7 UIF löschen, ist Bit 0 im Register TIM6_SR
    TIM7->SR &= ~(1 << UIF); // FS TIM7->SR = 0, geht, da restl. 15 Bit reserved sind, trotzdem ungute Lösung
   
    // TIM7 neu laden
    TIM7->CNT = 0;
    
    // TIM7 Maximalwert auf 1000 setzen, also Interrupt nach 1s
    TIM7->ARR = 1000;
    
    // TIM7 ISR in die Vektortabelle des NVIC eintragen
    NVIC_SetVector(TIM7_IRQn,(uint32_t) &isr_TIM7);

    // TIM7-Interrupt im NVIC freigeben
    HAL_NVIC_EnableIRQ(TIM7_IRQn);

    // TIM7 Interrupt freigeben TIM7_DIER.UIE=1: Bit 0 setzen
    TIM7->DIER |= (1 << UIE);

    // TIM7 starten
    // TIM7->CR1 |= (1 << CEN); // TIM7_CR1.CEN = 1; Bit 0

}

void Timers::isr_TIM7(void)
{
     // TIM7 Interrupt stoppen TIM7_DIER.UIE=1: Bit 0 löschen
    TIM7->DIER &= ~(1 << UIE);

    // TIM7 stoppen
    TIM7->CR1 &= ~(1 << CEN); // TIM7_CR1.CEN = 0; Bit 0

    // Tick-Ereignis senden
    derAutomat.sendEvent(Tick);


    derAutomat.fsm_set_timeInState(1); // timeInState der fsm um 1 erhöhen

    // TIM7 UIF löschen, ist Bit 0 im Register TIM7_SR
    TIM7->SR &= ~(1 << UIF); // FS TIM7->SR = 0, geht, da restl. 15 Bit reserved sind, trotzdem ungute Lösung
   
    // TIM7 neu laden
    TIM7->CNT = 0;

    // TIM7 Interrupt freigeben TIM7_DIER.UIE=1: Bit 0 setzen
    TIM7->DIER |= (1 << UIE);

    //TIM7 starten
    TIM7->CR1 |= (1 << CEN); // TIM7_CR1.CEN = 1; Bit 0

    
}


void Timers::init_TIM6_interrupt()
{
        // TIM6 mit Takt versorgen, Bit 5 in RCC_APB1ENR
    RCC->APB1ENR |= (1 << TIM6EN); // RCC_APB1ENR |= 0b 10000: RCC_APB1ENR.TIM6EN=1
    
    // TIM6 stoppen
    TIM6->CR1 &= ~(1 << CEN); // TIM6_CR1.CEN = 0; Bit 0
    
    // Prescaler auf 31999 setzen -A Taktsignal wird durch 32000 geteilt
    // Bei fCLK = 32MHz ergibt dies 1ms fCNT
    TIM6->PSC = 31999; // (1ms * 32MHz)-1 = 31999
    
    // TIM6 UIF löschen, ist Bit 0 im Register TIM6_SR
    TIM6->SR &= ~(1 << UIF); // FS TIM6->SR = 0, geht, da restl. 15 Bit reserved sind, trotzdem ungute Lösung
   
    // TIM6 neu laden
    TIM6->CNT = 0;
    
    // TIM6 Maximalwert auf 500 setzen, also Interrupt nach 500ms
    TIM6->ARR = 500;
    
    
    // TIM6 ISR in die Vektortabelle des NVIC eintragen
    NVIC_SetVector(TIM6_IRQn,(uint32_t) &isr_TIM6);

    // TIM6-Interrupt im NVIC freigeben
    HAL_NVIC_EnableIRQ(TIM6_IRQn);

    // TIM6 Interrupt freigeben TIM6_DIER.UIE=1: Bit 0 setzen
    TIM6->DIER |= (1 << UIE);

    
    
}

void Timers::isr_TIM6(void)
{
     // TIM6 Interrupt stoppen TIM6_DIER.UIE=1: Bit 0 löschen
    TIM6->DIER &= ~(1 << UIE);

    // TIM6 stoppen
    TIM6->CR1 &= ~(1 << CEN); // TIM7_CR1.CEN = 0; Bit 0

 

    // TIM6 UIF löschen, ist Bit 0 im Register TIM6_SR
    TIM6->SR &= ~(1 << UIF); // FS TIM6->SR = 0, geht, da restl. 15 Bit reserved sind, trotzdem ungute Lösung
   
    // TIM6 neu laden
    TIM6->CNT = 0;

    if (derAutomat.getRichtung() == true)
    {
        derAutomat.schritt_rechts();
    }
    else
    {
        derAutomat.schritt_links();
    }
    

    // TIM6 Interrupt freigeben TIM6_DIER.UIE=1: Bit 0 setzen
    TIM6->DIER |= (1 << UIE);

    // TIM6 starten
    TIM6->CR1 |= (1 << CEN); // TIM6_CR1.CEN = 1; Bit 0

    
}

///<summary>
///Startet den Timer TIM6
///</summary>
void Timers::TIM6_start()
{
    // TIM6 UIF löschen, ist Bit 0 im Register TIM6_SR
    TIM6->SR &= ~(1 << UIF); // FS TIM6->SR = 0, geht, da restl. 15 Bit reserved sind, trotzdem ungute Lösung
    // TIM6 neu laden
    TIM6->CNT = 0;
    // TIM6 Interrupt freigeben TIM6_DIER.UIE=1: Bit 0 setzen
    TIM6->DIER |= (1 << UIE);

    // TIM6 starten
    TIM6->CR1 |= (1 << CEN); // TIM6_CR1.CEN = 1; Bit 0
}

void Timers::TIM6_stopp()
{
    // TIM6 Interrupt stoppen TIM6_DIER.UIE=1: Bit 0 löschen
    TIM6->DIER &= ~(1 << UIE);
    // TIM6 stoppen
    TIM6->CR1 &= ~(1 << CEN); // TIM7_CR1.CEN = 0; Bit 0
    // TIM6 neu laden
    TIM6->CNT = 0;

    //neues feature
    auto a = 0;
}

//=============================================================================
// Bluetooth
//=============================================================================

void Bluetooth::init_bt()
{
    // Set desired properties (9600-8-N-1). HM-10 kann nur 9600Baud 
    ;
    blue.set_blocking(false); // Kein blocking, bt_read() blockiert also nicht wenn keine lesbaren Daten vorhanden sind
}

bool Bluetooth::bt_readable()
{
    return(true);
}

void Bluetooth::bt_read(void *buf, size_t laenge)
{
    ;
}



void Bluetooth::bt_read_Dabble(uint16_t *taste)
{   
    
    uint8_t i=0;
    char zeichen;
    char payload[20]={0}; // eingelesene Nutzdaten
    uint16_t pressed_key; // betätigte Taste
    

    
    
        
        
        while( i<16)    // 2 Frames einlesen, es werden also immer 16Byte eingelesen.
                        // Daher ist blocking auf false gesetzt, dann wird i auch erhöht
                        // wenn die Anzahl an Bytes kleiner als 16 ist, insbes. beim
                        // Verbinden des BT-Moduls. Sonst hängt das Programm in dieser
                        // Schleife fest bis zum Reset des Controllers
        {
            
            {
                blue.read(&zeichen,1);
                payload[i] = zeichen;
                i=i+1;

                
            }
            
        }


        pressed_key = (payload[4] << 8) + payload[5]; // Byte 4 und 5, eigentlich Byte 5 und 6, liegt vermutlich an blue.readable(), so dass schon 1 Byte verloren geht, da nicht direkt der Lesebefehl auf reabalbe() folgt.
        // pressed_key = (payload[5] << 8) + payload[6];

        

        switch(pressed_key) // hier dann den abspeichern
                            // der jeweils nachfolgende Durchlauf erzeugt den Tastencode 0,
                            // daher muss er in den case-Teilen gesichert werden bevor der 
                            // anschließende 0-Durchlauf kommt
        {
            case 0x0001: *taste = pressed_key; // Up 
                         break;
            case 0x0002: *taste = pressed_key; // Dwn
                         break;
            case 0x0004: *taste = pressed_key; // Left
                         break;
            case 0x0008: *taste = pressed_key; // Right
                         break;
            case 0x0100: *taste = pressed_key; // Start
                         break;
            case 0x0200: *taste = pressed_key; // Select
                         break;
            case 0x0400: *taste = pressed_key; // Triangle
                         break;
            case 0x0800: *taste = pressed_key; // Circle
                         break;
            case 0x1000: *taste = pressed_key; // Cross
                         break;             
            case 0x2000: *taste = pressed_key; // Square
                         break;
            
        }

         

        ThisThread::sleep_for(250ms);  //unbedingt notwendig, damit der Buffer durch den momentanen Tastendruck abschließend gefüllt werden kann.
    
        blue.sync(); // Buffer löschen
        
}