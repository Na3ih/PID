#ifndef STM32F4DISCO_ENCODER_H
#define STM32F4DISCO_ENCODER

#include "../../include/ProjectDependencies.h"

uint32_t encoderGetImpulsesNumber(void);
float convertToSpeed(float radius, uint32_t ticks, uint8_t resolution, uint16_t timeMs);
float convertToRPM(uint32_t ticks, uint8_t resolution, uint16_t timeMs);

#endif