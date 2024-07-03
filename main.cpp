
#include "DigitalIn.h"
#include "DigitalOut.h"
#include "LinkedList.h"
#include "PinNames.h"
#include "PortNames.h"
#include "PortOut.h"
#include "ThisThread.h"
#include "cmsis_armclang.h"
#include "stm32l152xe.h"
#include <cstdint>
#undef __ARM_FP

#include "mbed.h"

PortOut stepper(PortC, 0x000F);

uint32_t vollschritt[] = {0b0110,0b0101,0b1001,0b1010};

int aktZustand = 0;

void SchrittRechts()
{
    if (aktZustand == 4)
    {
        aktZustand = 0;
    }

    stepper.write(vollschritt[aktZustand]);
    aktZustand = aktZustand + 1;
}

void SchrittLinks()
{
    if (aktZustand < 0)
    {
        aktZustand--;
    }
    else if (aktZustand == 0) {
        aktZustand = 3;
    }
    else
    {
        aktZustand --;
    }
    stepper.write(vollschritt[aktZustand]);
}

void isrTim6()
{
    TIM6->CR1 = 0;
    TIM6->CNT = 0;
    TIM6->SR  = 0;
    SchrittLinks();
    TIM6->CR1 = 1;
}

void init_Tim6()
{
    TIM6->SR  = 0;
    RCC->APB1ENR  |= 0b10000;
    TIM6->CR1 = 0;
    TIM6->ARR = 250;
    TIM6->PSC = 31999;
    TIM6->CNT = 0;
    NVIC_SetVector(TIM6_IRQn,(uint32_t) & isrTim6);
    HAL_NVIC_EnableIRQ(TIM6_IRQn);
    TIM6->DIER = 1; 
    __enable_irq();
    TIM6->CR1 = 1;
}

int main()
{
    // bool 
    init_Tim6();
    while (true) 
    {}
}
