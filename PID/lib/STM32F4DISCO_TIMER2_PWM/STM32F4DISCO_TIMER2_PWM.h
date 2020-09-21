#ifndef STM32F4DISCO_TIMER2_PWM_H
#define STM32F4DISCO_TIMER2_PWM_H

#include "../../include/ProjectDependencies.h"

void timer2PWM1Config(void);
void setPWM(uint16_t pulse);
void timer3ExternalTriggerConfiguration(void);

#endif