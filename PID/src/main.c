/**
 * @brief Program implements control algorithm for rotation angle adjustment of a DC motor with an encoder. 
 *        Rotation angle control use simple PID regulator algorithm.
 * @warning In project used incremental encoder so number of encoder ticks are added or subtracted depends on direction.
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
void motorSpeedLog(void);
volatile unsigned int timer_ms = 0;
volatile unsigned int i =0;
void controlGpioConfig( void );
void motorDirectionRight(void);
void motorDirectionLeft(void);
void motorStop(void);

volatile uint8_t leftDirFlag = 0;
float stering[2];
uint8_t actualDirection = LEFT;

int main(void)
{
    identyficationSystemConfig();
    usart5SendString("START\n\r", 7);
    motorDirectionLeft();
    while(1);
    return 0;
}

void SysTick_Handler(void)
{
    static int position = 0;
    static uint32_t ms = 0;
    static float step = 1.0;
    if (timer_ms >= SAMPLING_TIME_MS) {
        timer_ms = 0;
        if (actualDirection == LEFT) {
            position += (TIM3->CNT);
        } else {
            position -= (TIM3->CNT);
        }
        TIM3->CNT = 0;
        
        calculatePID(20.0, position, stering);
        leftDirFlag = stering[1];

        if (leftDirFlag != actualDirection) {
            if (ms >= 500) {
                switch (actualDirection) {
                case LEFT:
                    motorDirectionRight();
                    break;
                case RIGHT:
                    motorDirectionLeft();
                    break;
                }
                ms = 0;
            } else {
                motorStop();
                ms += SAMPLING_TIME_MS;
            }
        }
        setPWM((uint32_t)stering[0]);

        if ((i++) >= 100) {
            i = 0;
            char tmpBuf[50];
            sprintf(tmpBuf, "position: %d,  PWM: %.5f,  direction: %d", position, stering[0], actualDirection);
            usart5SendString(tmpBuf, 50);
            step += 5.0;
            
        }   
    } else {
        timer_ms++;
    }
}

void controlGpioConfig( void )
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
    GPIOC->MODER |= GPIO_MODER_MODER0_0 | GPIO_MODER_MODER2_0;
    GPIOC->ODR &= ~(GPIO_ODR_ODR_0 | GPIO_ODR_ODR_2);
}

void motorStop(void) 
{
    GPIOC->ODR |= GPIO_ODR_ODR_0 | GPIO_ODR_ODR_2;
}

void motorDirectionLeft(void)
{
    GPIOC->ODR |= GPIO_ODR_ODR_0;
    GPIOC->ODR &= ~GPIO_ODR_ODR_2;
    actualDirection = LEFT;
}

void motorDirectionRight(void)
{
    GPIOC->ODR |= GPIO_ODR_ODR_2;
    GPIOC->ODR &= ~GPIO_ODR_ODR_0;
    actualDirection = RIGHT;
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
    controlGpioConfig();
}


