#ifndef PID_TUNE_H
#define PID_TUNE_H

#include <stdio.h>

const double Kp = 0.0003;           ///< Proportional Gain.
const double Ki = 0.0026;           ///< Integral Gain.
const double Kd = 1.2963e-005;      ///< Derrivate Gain.
const uint32_t dt = 5;              ///< Cycle time in miliseconds.
const double epsilon = 1;        ///< Minimal error to update integral part.
const double saturationUp = 5400;
const double saturationDn = 0;
#endif