/* 
 * File:   lab2Part2.c
 * Author: Robert Gaines
 * Main file for part two of lab2. Ping sensor will be used and calibrated using data sheet and least squares calibration
 * After calibration the ping sensor will be used to proportional control the frequency of the tone generator.
 *
 * Created on April 18, 2023, 11:21 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "timers.h" 
#include "PING.h"
#include "pwm.h"
#include "AD.h"
#include "serial.h"
#include "IO.h"

#define DELAY(x)    {int wait; for (wait = 0; wait <= x; wait++) {asm("nop");}}
#define A_BIT       18300
#define A_LOT       183000
/*
 * 
 */
int main(int argc, char** argv) {
    
    BOARD_Init();
    printf("Lab2 part 2!\r\n");
    TIMERS_Init();
    //PWM_Init();
    
    PING_Init();
    ToneGeneration_Init();
    int THRESH = 3;
    ToneGeneration_ToneOn(); 
    int d = 0;
    int lastReading = 0;
    while (1){
        
        d = PING_GetDistance();
        
        if(abs(d - lastReading) > THRESH){
            lastReading = d;
        }
        printf("Distance: %i \r\n", d);
        if(lastReading <= 5)ToneGeneration_SetFrequency(196); 
        else if(lastReading <= 20 && lastReading > 5)ToneGeneration_SetFrequency(293);
        else if(lastReading > 20 && lastReading <= 40)ToneGeneration_SetFrequency(440); 
        else if(lastReading > 40 && lastReading <= 60)ToneGeneration_SetFrequency(500); 
        else if(lastReading > 60 && lastReading <= 80)ToneGeneration_SetFrequency(659); 
        else if(lastReading > 80 && lastReading <= 100)ToneGeneration_SetFrequency(770); 
        else ToneGeneration_SetFrequency(880); 
    }
}