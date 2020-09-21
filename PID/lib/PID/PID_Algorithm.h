#ifndef PID_ALGORITHM_H
#define PID_ALGORITHM_H

// #include "PID_Tune.h"

void calculatePID(float setpoint,float actual_value, float * retTab);

enum direction {
    LEFT = 1,
    RIGHT = 0
};
#endif