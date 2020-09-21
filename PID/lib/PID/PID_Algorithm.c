#include "PID_Algorithm.h"
#include "PID_Tune.h"
#include <stdlib.h> 

float calculatePID(float setpoint,float actual_value)
{
     static float pre_error = 0.0; 
     static float integral = 0.0; 
     float error; 
     float derivative; 
     float output; 
     //Caculate P,I,D 
     error = setpoint - actual_value; 
     //In case of error too small then stop integration 
     if (abs(error) > epsilon) { 
         integral = integral + error * dt; 
     } 
     derivative = (error - pre_error)/dt; 
     output = Kp*error + Ki*integral + Kd*derivative; 
     
    //Saturation Filter 
     if(output > saturationUp) {
        output = saturationUp; 
     } else if (output < saturationDn) { 
        output = saturationDn; 
     } 
     
     //Update error 
     pre_error = error; 
     return output;
     }