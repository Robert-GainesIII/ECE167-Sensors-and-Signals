/* 
 * File:   helloworld.c
 * Author: robertgaines
 *
 * Created on April 3, 2023, 11:45 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "BOARD.h"
#include "serial.h"
#include "AD.h"
#include "ToneGeneration.h"
#include "pwm.h"

#define DELAY(x)    {int wait; for (wait = 0; wait <= x; wait++) {asm("nop");}}
#define A_BIT       18300
#define A_LOT       183000


int main(void)
{
    BOARD_Init();
    AD_Init();
    ToneGeneration_Init();
    
    printf("Hello World!\n");
    int THRESH  = 10;
    ToneGeneration_SetFrequency(TONE_196);
    ToneGeneration_ToneOn();
    
    
    uint16_t data = 0;
    uint8_t movingAvgCount = 0;
    uint16_t avg = 0;
    uint16_t newData = 0;
    uint8_t buttonFlag = 0;
    uint8_t adcFlag = 0;
    uint16_t offset = 0;
    uint8_t SCALE = 5;
    AD_AddPins(AD_A1);
    AD_AddPins(AD_A2);
    
    
    while (1){
        
      
        
        if(AD_IsNewDataReady()){
            newData = AD_ReadADPin(AD_A1);
            
            if(abs(newData - data) > THRESH){
                data = newData;
                offset = data/SCALE;
                printf("%u \r\n", data);
                if(!adcFlag)
                ToneGeneration_SetFrequency(data);
            }
            
           
        }
        
        
        
        if(!adcFlag){ToneGeneration_ToneOn();}
       
//        if(abs(newData- data) > THRESH){
//            data = newData;
//            printf("%u \r\n", data);
//            
//        }
        
        DELAY(A_BIT);
    };
    
    BOARD_End();
}
