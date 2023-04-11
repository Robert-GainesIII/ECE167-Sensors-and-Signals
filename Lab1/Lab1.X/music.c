/* 
 * File:   music.c
 * Author: robertgaines
 *
 * Created on April 11, 2023, 9:21 AM
 */

#include <stdio.h>
#include <stdlib.h>

#include "../../Common/BOARD.h"
#include "../../Common/serial.h"
#include "../../Common/AD.h"
#include "../../Common/ToneGeneration.h"
#include "../../Common/pwm.h"

#define DELAY(x)    {int wait; for (wait = 0; wait <= x; wait++) {asm("nop");}}
#define A_BIT       18300
#define A_LOT       183000

#define TONEFLAG1 196 
#define TONEFLAG2 293
#define TONEFLAG3 440
#define TONEFLAG4 659

#define DURATION 20


int main(void)
{
    BOARD_Init();
    AD_Init();
    ToneGeneration_Init();
    
    printf("Hello World!\r\n");
    int THRESH  = 10;
    
    
    
    uint16_t data = 0;
    uint8_t movingAvgCount = 0;
    uint16_t avg = 0;
    uint16_t newData = 0;
    uint8_t buttonFlag = 0;
    uint8_t adcFlag = 0;
    uint16_t offset = 0;
    uint16_t scaryData = 0;
    uint16_t oldScaryData = 0;
    uint8_t SCALE = 5;
    uint8_t play = 0;
    uint16_t tone = 0;
    uint16_t count = 0;
    AD_AddPins(AD_A1);
    AD_AddPins(AD_A2);
    
    ToneGeneration_ToneOn();
    
    while (1){
        
            
        
        //if(AD_IsNewDataReady()){
            newData = AD_ReadADPin(AD_A1);
            
            if(abs(newData - data) > THRESH){
                data = newData;
                offset = data/SCALE;
                printf("%u \r\n", data);
                
                if(data < 400){
                    tone = TONEFLAG1;
                }
                else if (data > 300 && data < 500){
                    tone = TONEFLAG2;
                }
                else if(data > 400 && data < 600){
                    tone = TONEFLAG3;
                }
                else{
                    tone = TONEFLAG4;
                }
                 
                ToneGeneration_SetFrequency(data);
            }
            
            scaryData = AD_ReadADPin(AD_A2);
          
            if(abs(scaryData - oldScaryData) > THRESH){
                oldScaryData = scaryData;
                offset = data/SCALE;
                printf(" scary data: %u\r\n", scaryData);
                if(scaryData > 300){
                    play = 1;
                    count = DURATION;
                    printf("playing music new for 100 cycles \r\n");
                    ToneGeneration_ToneOn();
                }
        
            }
            
            
            if(play == 1){
                count--;
                if(count <= 0){
                    ToneGeneration_ToneOff();
                    play = 0;
                }
                
            }
            else {
                ToneGeneration_ToneOff();
            }
              
           
          
           
      
        
        
       
//        if(abs(newData- data) > THRESH){
//            data = newData;
//            printf("%u \r\n", data);
//            
//        }
        
        DELAY(A_BIT);
    };
    
    BOARD_End();
}

