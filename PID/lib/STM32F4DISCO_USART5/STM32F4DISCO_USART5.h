#ifndef STM32F4DISCO_USART5_H
#define STM32F4DISCO_USART5_H

#include "../../include/ProjectDependencies.h"



void UART5_Enable(void);
void usart5Send(uint16_t integer);
void usart5SendString(const char * string, uint8_t stringLength);

#endif