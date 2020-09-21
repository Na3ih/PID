/**
 * @brief Program implements the identification test algorithm for a DC motor with an encoder. 
 *        It consists in measuring the rotational speed and logging the results by UART.
 *        
 *        The algorithm was adapted to the STM32F4 DISCO evaluation board connected to the L298N DC motor controller.
 */ 
#include "ProjectDependencies.h" 
#include "SystemParameters.h"
#include <STM32F4DISCO_USART5.h>
#include <STM32F4DISCO_ENCODER.h>
#include <STM32F4DISCO_TIMER2_PWM.h>
#include <PID_Algorithm.h>

void identyficationSystemConfig(void);
volatile unsigned int timer_ms = 0;

int main(void)
{
    identyficationSystemConfig();
    setPWM(1000);
    usart5SendString("START\n\r", 7);
    while(1);
    return 0;
}

void SysTick_Handler(void)
{
    
    if (timer_ms >= SAMPLING_TIME_MS) {
        timer_ms = 0;
        float speed = 0.0;         
        speed = convertToRPM(encoderGetImpulsesNumber(), ENCODER_RESOLUTION, SAMPLING_TIME_MS);
        usart5Send(speed);
    } else {
        timer_ms++;
    }
}

void identyficationSystemConfig(void)
{
    UART5_Enable();
    timer3ExternalTriggerConfiguration();
    usart5SendString("timer3ExternalTriggerConfiguration\n\r", 36);
    timer2PWM1Config();
    usart5SendString("timer2PWM1Config\n\r", 18);
    SysTick_Config(SystemCoreClock / 1000); ///< Interrupt in every 1 ms
    usart5SendString("SysTick_Config\n\r", 16);
}


