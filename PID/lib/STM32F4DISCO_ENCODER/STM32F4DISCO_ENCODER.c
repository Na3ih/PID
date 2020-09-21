#include "STM32F4DISCO_ENCODER.h"

/* ----------------- ENCODER ------------------- */
/* GPIO configuration */
void timer3ExternalTriggerConfiguration(void)
{
    // 1.Enabling clock for GPIO port connected with Timer3 ETR
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;

    // 2.Set pin in alternate function mode   
    GPIOD->MODER |= GPIO_MODER_MODER2_1; ///< PD2 -> AF
    GPIOD->AFR[0] |= 0x00000200; ///< PD2 -> AF2 (TIM3..5)

    /* Counter configuration: (Time-base unit) */
    // 1.Counter Clock Enable 
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN; ///< APB1 speed = AHB speed = System Clock speed = 16MHz

    // 3.Counting edges number 
    TIM3->ARR = 0xFF; ///< reload value

    // 4.Direction 
    TIM3->CR1 &= ~TIM_CR1_DIR;  ///< Counter used as upcounter 

    // 5.Counter mode
    TIM3->SMCR |= TIM_SMCR_ECE; ///<  External CLK enable

    // 6.Re-initialize counter (after count to ARR or 0)
    TIM3->CR1 |= TIM_CR1_ARPE;

    // 7.Polarity (active edge selection)
    TIM3->SMCR &= ~(TIM_SMCR_ETP); ///< rising edge detection

    // **Enable timer
    TIM3->CR1 |= TIM_CR1_CEN;
}


uint32_t encoderGetImpulsesNumber(void)
{
    uint32_t impulsesNum = TIM3->CNT;
    //usart5Send(impulsesNum);
    TIM3->CNT = 0;
    return impulsesNum;
}

float convertToRPM(uint32_t ticks, uint8_t resolution, uint16_t timeMs)
{
    unsigned long ticksPerSecond = ticks * (1000 / timeMs);
    unsigned long rotatePerSecond = ticksPerSecond / resolution;
    return rotatePerSecond * 60;
}
/**
 * Converts number of ticks into speed in m/s
 * @param radius Wheel radius [mm]
 * @param ticks Number of ticks. 
 * @param resolution Encoder resolution [per rotate].
 * @param timeMs Time in miliseconds.
 */ 
float convertToSpeed(float radius, uint32_t ticks, uint8_t resolution, uint16_t timeMs)
{
    /// TODO: SPRAWDZIC
    static const float PI = 3.14;
    //usart5Send((int)PI);
    float circuit = 2 * PI * radius;
    //usart5Send((int)circuit);
    float distance = (circuit / resolution) * (float)ticks;
    //usart5Send((int)distance);
    return distance / timeMs;   //<[mm/ms]
}