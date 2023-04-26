/* 
 * File:   lab2.c
 * Author: robertgaines
 *
 * Created on April 17, 2023, 11:29 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "BOARD.h"
#include "Buttons.h"
#include "serial.h"
#include "AD.h"
#include "ToneGeneration.h"
#include "pwm.h"
#include "QEI.h"




#define DELAY(x)    {int wait; for (wait = 0; wait <= x; wait++) {asm("nop");}}
#define A_BIT       18300
#define A_LOT       183000

/*
 * 
 */
int main(int argc, char** argv) {

    BOARD_Init();
    TIMERS_Init();
    unsigned int tick = 0;

    ToneGeneration_Init();
    QEI_Init();
    PWM_Init();


    PWM_AddPins(PWM_PORTZ06);//
    PWM_AddPins(PWM_PORTY12);
    PWM_AddPins(PWM_PORTY04);
    printf("Lab2 part 1!\n");
    int THRESH = 10;
    ToneGeneration_SetFrequency(TONE_196);
    ToneGeneration_ToneOn();


    int count = 0;
    while (1) {
        if (TIMERS_GetMilliSeconds() - tick >= 10) {
            tick = TIMERS_GetMilliSeconds();
            count = QEI_GetPosition() * 15;
            count = abs(count);
            printf("Count is: %i \r\n", count);
            //DELAY(A_BIT);
            if (count == 0) {
                PWM_SetDutyCycle(PWM_PORTZ06, 0);
                PWM_SetDutyCycle(PWM_PORTY12, 1000);
                PWM_SetDutyCycle(PWM_PORTY04, 1000);

            } else if (count == 15) {
                PWM_SetDutyCycle(PWM_PORTZ06, 0);
                PWM_SetDutyCycle(PWM_PORTY12, 750);
                PWM_SetDutyCycle(PWM_PORTY04, 1000);

            } else if (count == 30) {
                PWM_SetDutyCycle(PWM_PORTZ06, 0);
                PWM_SetDutyCycle(PWM_PORTY12, 500);
                PWM_SetDutyCycle(PWM_PORTY04, 1000);

            } else if (count == 45) {
                PWM_SetDutyCycle(PWM_PORTZ06, 0);
                PWM_SetDutyCycle(PWM_PORTY12, 250);
                PWM_SetDutyCycle(PWM_PORTY04, 1000);

            } else if (count == 60) {
                PWM_SetDutyCycle(PWM_PORTZ06, 0);
                PWM_SetDutyCycle(PWM_PORTY12, 0);
                PWM_SetDutyCycle(PWM_PORTY04, 1000);

            } else if (count == 75) {
                PWM_SetDutyCycle(PWM_PORTZ06, 250);
                PWM_SetDutyCycle(PWM_PORTY12, 0);
                PWM_SetDutyCycle(PWM_PORTY04, 1000);

            } else if (count == 90) {
                PWM_SetDutyCycle(PWM_PORTZ06, 500);
                PWM_SetDutyCycle(PWM_PORTY12, 0);
                PWM_SetDutyCycle(PWM_PORTY04, 1000);

            } else if (count == 105) {
                PWM_SetDutyCycle(PWM_PORTZ06, 750);
                PWM_SetDutyCycle(PWM_PORTY12, 0);
                PWM_SetDutyCycle(PWM_PORTY04, 1000);

            } else if (count == 120) {
                PWM_SetDutyCycle(PWM_PORTZ06, 1000);
                PWM_SetDutyCycle(PWM_PORTY12, 0);
                PWM_SetDutyCycle(PWM_PORTY04, 1000);

            } else if (count == 135) {
               PWM_SetDutyCycle(PWM_PORTZ06, 1000);
               PWM_SetDutyCycle(PWM_PORTY12, 0);
               PWM_SetDutyCycle(PWM_PORTY04, 750); 

            } else if (count == 150) {
                PWM_SetDutyCycle(PWM_PORTZ06, 1000);
                PWM_SetDutyCycle(PWM_PORTY12, 0);
                PWM_SetDutyCycle(PWM_PORTY04, 500);

            } else if (count == 165) {
                PWM_SetDutyCycle(PWM_PORTZ06, 1000);
                PWM_SetDutyCycle(PWM_PORTY12, 0);
                PWM_SetDutyCycle(PWM_PORTY04, 250);

            } else if (count == 180) {

               PWM_SetDutyCycle(PWM_PORTZ06, 1000);
               PWM_SetDutyCycle(PWM_PORTY12, 0);
               PWM_SetDutyCycle(PWM_PORTY04, 0);
            } else if (count == 195) {
                PWM_SetDutyCycle(PWM_PORTZ06, 1000);
                PWM_SetDutyCycle(PWM_PORTY12, 250);
                PWM_SetDutyCycle(PWM_PORTY04, 0);

            } else if (count == 210) {
                
                PWM_SetDutyCycle(PWM_PORTZ06, 1000);
                PWM_SetDutyCycle(PWM_PORTY12, 500);
                PWM_SetDutyCycle(PWM_PORTY04, 0);
            }
             else if (count == 225) {
                
                PWM_SetDutyCycle(PWM_PORTZ06, 1000);
                PWM_SetDutyCycle(PWM_PORTY12, 750);
                PWM_SetDutyCycle(PWM_PORTY04, 0);
            }
             else if (count == 240) {
                
                PWM_SetDutyCycle(PWM_PORTZ06, 1000);
                PWM_SetDutyCycle(PWM_PORTY12, 1000);
                PWM_SetDutyCycle(PWM_PORTY04, 0);
            }
             else if (count == 255) {
                
                PWM_SetDutyCycle(PWM_PORTZ06, 750);
                PWM_SetDutyCycle(PWM_PORTY12, 1000);
                PWM_SetDutyCycle(PWM_PORTY04, 0);
            }
             else if (count == 270) {
                
                PWM_SetDutyCycle(PWM_PORTZ06, 500);
                PWM_SetDutyCycle(PWM_PORTY12, 1000);
                PWM_SetDutyCycle(PWM_PORTY04, 0);
            }
             else if (count == 285) {
                
                PWM_SetDutyCycle(PWM_PORTZ06, 250);
                PWM_SetDutyCycle(PWM_PORTY12, 1000);
                PWM_SetDutyCycle(PWM_PORTY04, 0);
            }
             else if (count == 300) {
                
                PWM_SetDutyCycle(PWM_PORTZ06, 0);
                PWM_SetDutyCycle(PWM_PORTY12, 1000);
                PWM_SetDutyCycle(PWM_PORTY04, 0);
            }
             else if (count == 315) {
                
                PWM_SetDutyCycle(PWM_PORTZ06, 0);
                PWM_SetDutyCycle(PWM_PORTY12, 1000);
                PWM_SetDutyCycle(PWM_PORTY04, 250);
            }
             else if (count == 330) {
                
                PWM_SetDutyCycle(PWM_PORTZ06, 0);
                PWM_SetDutyCycle(PWM_PORTY12, 1000);
                PWM_SetDutyCycle(PWM_PORTY04, 500);
            }
             else if (count ==345) {
                
                PWM_SetDutyCycle(PWM_PORTZ06, 0);
                PWM_SetDutyCycle(PWM_PORTY12, 1000);
                PWM_SetDutyCycle(PWM_PORTY04, 750);
            }
             else if (count == 360) {
                
                PWM_SetDutyCycle(PWM_PORTZ06, 0);
                PWM_SetDutyCycle(PWM_PORTY12, 1000);
                PWM_SetDutyCycle(PWM_PORTY04, 1000);
            }
        }
    }
}

