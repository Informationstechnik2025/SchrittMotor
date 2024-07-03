/*
 * Hardware_Methoden.h
 *
 * Created: 21.01.2023 15:51:44
 *  Author: Thomas Heß
 */ 


#ifndef HARDWARE_H_
#define HARDWARE_H_

#include <stddef.h>  // für size_t
#include <stdint.h> // für uint8_t
#include <stdbool.h> // damit bool als (abgeleiteter) Datentyp existiert



namespace Motor {
	/** Init the hardware Pins */
	void init();
    
    

}


namespace Display{
    void init();
    void locate(int, int);
    void print(const char*, ...);
}

namespace Serial{
    void print(const char*, ...);
}

namespace ExtInterruptPins{
    void isr_rechts(void);
    

    void init_extint_rechts(void);
    
    


}


namespace Timers{
    
    void init_TIM7_interrupt(void);
    void isr_TIM7(void);

    void init_TIM6_interrupt(void);
    void isr_TIM6(void);

    

}

namespace Bluetooth
{

    void init_bt(void);
    bool bt_readable(void);
    void bt_read(void*,size_t);
    
    void bt_read_Dabble(uint16_t*);

}

#endif /* HARDWARE_H_ */