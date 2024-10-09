/*
 * Hardware_Definitionen.h
 *
 * Created: 21.01.2023 15:44:07
 *  Author: Thomas Heß
 */ 


#ifndef HARDWARE_HWDEFS_H_
#define HARDWARE_HWDEFS_H_




namespace Motor {
	
	#define MOTOR_A_OUT1        PC_3	
    #define MOTOR_A_OUT2        PC_2
	#define MOTOR_B_OUT1        PC_1
    #define MOTOR_B_OUT2        PC_0
    #define MOTOR_PORT          PortC
}

namespace ExtInterruptPins{
    #define S_RECHTS              PB_4
    #define S_STOPP               PB_3
    #define S_LINKS               PB_0
}


namespace Timers 
{
    // #define für einzelne Konfigurationsbits

    // RCC_APB1ENR
    #define TIM6EN 4
    #define TIM7EN 5

    // TIMx_CR1, CEN... counter enable
    #define CEN 0

    // TIMx_DIER, UIE ... Update Interrupt Enable
    #define UIE 0

    // TIMx_SR, UIF ... Update Interrupt Flag
    #define UIF 0
}

namespace Bluetooth
{
    // BT TX-Pin
    #define BT_TX PB_10

    // BT RX-Pin
    #define BT_RX PB_11

    // BT enable pin
    #define BT_EN PB_12
}
#endif /* HARDWARE_HWDEFS_H_ */