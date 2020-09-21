#ifndef PID_TUNE_H
#define PID_TUNE_H

#include <stdio.h>

const long double Kp = 1.3333;     ///< Proportional Gain.
const long double Ki = 0.0044;         ///< Integral Gain.
const long double Kd = 55.96;      ///< Derrivate Gain.
const uint32_t dt = 5;               ///< Cycle time in miliseconds.
const double epsilon = 1.00;         ///< Minimal error to update integral part.
const double saturationUp = 1000.00;
const double saturationDn = 900.00;
#endif