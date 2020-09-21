#include "STM32F4DISCO_USART5.h"

void UART5_Enable()
{
    RCC->APB1ENR = RCC_APB1ENR_UART5EN;      // Enable UART5 clock
    UART5->BRR = 16000000 / 9600;            // Baud Rate = 9600
    UART5->CR1 |= USART_CR1_UE;              // Enable UART
    UART5->CR1 |= USART_CR1_TE;              // Enable Transmitter
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;     // Enable TX clock
    GPIOC->MODER |= (1U << 25);              // TX pin in alternate mode PC12
    GPIOC->AFR[1] |= (1U << 19);             // AF ...
    UART5->DR = 'T';                         ///< TEST
    while (!(UART5->SR & USART_SR_TXE));
}
/**
* Sending integer value as a string by UART5.
* @param integer Integer value (16bit).
*/
void usart5Send(uint16_t integer)
{
    char *buf = malloc(sizeof(integer));
    sprintf(buf, "%u", integer);
    while (*(buf))
    {
        UART5->DR = *buf++;
        while (!(UART5->SR & USART_SR_TXE));
    }
    UART5->DR = '\n';
    while (!(UART5->SR & USART_SR_TXE));
    UART5->DR = '\r';
    while (!(UART5->SR & USART_SR_TXE));
}

/**
* Sending integer value as a string by UART5.
* @param string Pointer to array with string to send.
* @param stringLength Number of chars to send.
*/
void usart5SendString(const char * string, uint8_t stringLength)
{
    char *buf = malloc(sizeof(char) * stringLength);
    sprintf(buf, "%s", string);
    while (*(buf))
    {
        UART5->DR = *buf++;
        while (!(UART5->SR & USART_SR_TXE));
    }
    UART5->DR = '\n';
    while (!(UART5->SR & USART_SR_TXE));
    UART5->DR = '\r';
    while (!(UART5->SR & USART_SR_TXE));
}
