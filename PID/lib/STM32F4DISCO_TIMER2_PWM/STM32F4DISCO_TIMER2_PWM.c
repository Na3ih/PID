#include "STM32F4DISCO_TIMER2_PWM.h"

/* --------------------- Motor Control ----------------------- */
//PA1 - TIM2_CH2 
void timer2PWM1Config(void)
{
    /* GPIO configuration */
    // 1.Enabling clock for GPIO port connected with Timer3 channel 1
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    // 2.Set pin in alternate function mode
        GPIOA->MODER |= GPIO_MODER_MODER3_1; ///< PA3 -> AF
        GPIOA->AFR[0] |= 0x00001000; ///< AF1 (TIM1/2) -> TIM2_CH2 

    /* Counter configuration: (Time-base unit) */
    // 1.Counter Clock Enable 
        RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; ///< APB1 speed = AHB speed = System Clock speed = 16MHz

    // 2.Prescaler --> 16MHz / 4 = 4MHz
        TIM2->PSC = 16;

    // 3.PWM Period --> 16MHz / 1000 = 1kHz 
        TIM2->ARR = 1000 - 1;

    // 4.Direction */
        TIM2->CR1 &= ~TIM_CR1_DIR;  ///< Counter used as upcounter 

    /* Channel configuration */
    // 1.Channel mode (Output compare 1 mode)
        TIM2->CCMR2 |= TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2;  ///< PWM1 mode 

    // 2.Re-initialize counter (after count to ARR or 0)
        TIM2->CR1 |= TIM_CR1_ARPE;
	// //PA3 -> TIM2_CH4 - AF1
	// RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	// RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	// GPIOA->MODER &= ~(GPIO_MODER_MODER3_0);
	// GPIOA->MODER |= GPIO_MODER_MODER3_1;
	// GPIOA->AFR[0] |= 0x00001000;// 0x01 << (3 * 4);	///< AF1 == (1U << 12)
	// TIM2->PSC = 0;						///< Prescaler
	// TIM2->ARR = 1000;					///< Aato Reload Register
	// TIM2->CCR4 = 100;					///< Capture/ Compare register
	
	// TIM2->EGR |= TIM_EGR_UG;	///< Re-initialize counter (after count to ARR or 0)
	// TIM2->CCMR2 |= TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1;	///< PWM1 Mode
	//  TIM2->CCMR2 |= TIM_CCMR2_OC4PE;	///<  Preload register enable(Read/Write operations access)
	 TIM2->CCER |= TIM_CCER_CC4E;	///< Compare Output Enable(signal is output on the corresponding output pin) 
	//  TIM2->BDTR |= TIM_BDTR_MOE; ///< Main output enable ???
	 TIM2->CR1 |= TIM_CR1_CEN;	///< Enable TIMER2
}

void setPWM(uint16_t pulse)
{
    TIM2->CCR4 = pulse;
}