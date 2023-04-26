/* 
 * File:   CAPTOUCH.c
 * Author: robertgaines
 *
 * Created on April 25, 2023, 12:42 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "BOARD.h"
#include "Buttons.h"
#include "serial.h"
#include "AD.h"

/*
 * 
 */
int main(int argc, char** argv) {

    BOARD_Init();
    AD_Init();
    
    AD_AddPins(AD_A0);
    
    while(1){
        if(AD_IsNewDataReady()){
                newData = AD_ReadADPin(AD_A0);

                if(abs(newData - data) > THRESH){
                    data = newData;
                    offset = data/SCALE;
                    printf("%u \r\n", data);
                    if(!adcFlag)
                    ToneGeneration_SetFrequency(data);
                }


        }  
    }
}

