#include "PID_Algorithm.h"
#include "PID_Tune.h"
#include <stdlib.h> 

#include <STM32F4DISCO_USART5.h>

void calculatePID(float setpoint,float actual_value, float * retTab)
{
     static float pre_error = 0.0; 
     static float integral = 0.0; 
     float error; 
     float derivative; 
     float output; 
     uint8_t direction;

     //Caculate P,I,D 
     error = setpoint - actual_value; 
     if (error > 0.0) {
         direction = LEFT;
     } else {
         direction = RIGHT;
     }
     //In case of error too small then stop integration 
     if (abs(error) > epsilon) { 
     
             integral = integral + error * dt; 
     } 

     derivative = (error - pre_error)/dt; 
     output = Kp*error + Ki*integral + Kd*derivative; 
     
    //Saturation Filter 
     if (error == 0) {
         output = 0.0;
     } else if(output > saturationUp) {
        output = saturationUp; 
     } else if (output < saturationDn) { 
        output = saturationDn; 
     } 
     
     *retTab = output;
     *(++retTab) = direction;
     //Update error 
     pre_error = error; 
}