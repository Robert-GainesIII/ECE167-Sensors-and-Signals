/* 
 * File:   calibrate.c
 * Author: robertgaines
 *
 * Created on April 29, 2023, 12:01 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "BOARD.h"
#include "BNO055.h"
#include "I2C.h"
#include "serial.h"


#define ACCELDATA
//#define MAGDATA
//#define GYRODATA


#define DELAY(x)    {int wait; for (wait = 0; wait <= x; wait++) {asm("nop");}}
#define A_BIT       18300
#define A_LOT       183000
#define FREQ 50
#define GLOBALFREQ 1000

/*
 * 
 */
int main(void) {
    
    //FILE *fptr;
    
    //fopen("data.txt","w");

        
    
    BOARD_Init();
    //I2C_Init(I2C_DEFAULT_RATE);

    char c = BNO055_Init();
    if (c == 0) {
        printf("Error in BN0O55 init function. Exiting Program. \r\n");
        return (-1);
    }



    printf("Lab 3: IMU CALIBRATION! \r\n");





    int globalcount = 0;
    int count = 0;
    int freqCount = 0;
    int x,y,z;
    while (1) {
        count ++;
        globalcount ++;
        
        
        if(count > FREQ && !(freqCount >= GLOBALFREQ)){
            count = 0;
            freqCount ++;
            
            
            //printf("\e[1;1H\e[2J");
            //READ OUT IMU DATA EACH
            #ifdef ACCELDATA
            x = BNO055_ReadAccelX();
            y = BNO055_ReadAccelY();
            z = BNO055_ReadAccelZ();
    
            //fprintf(fptr,"%d \r\n",z);
            //printf("%d ", x);
            //printf("%d ", y);
            printf("%d ", z);
            printf("\r\n");
            #endif

            #ifdef GYRODATA
            printf("GyroX: %i \r\n", BNO055_ReadGyroX());
            printf("GyroY: %i \r\n", BNO055_ReadGyroY());
            printf("GyroZ: %i \r\n", BNO055_ReadGyroZ());
            #endif

            #ifdef MAGDATA
            printf("MagX: %i \r\n", BNO055_ReadMagX());
            printf("MagY: %i \r\n", BNO055_ReadMagY());
            printf("MagZ: %i \r\n", BNO055_ReadMagZ());
            #endif

     
            //DELAY(A_BIT);
        }
    }
    /*
    for(int i =0; i < 1000; i++ ){
        printf("%f ", xList[i]);
    }
    printf("\r\n================================\r\n");
    for(int i =0; i < 1000; i++ ){
        printf("%f ", yList[i]);
    }
    printf("\r\n================================\r\n");
    for(int i =0; i < 1000; i++ ){
        printf("%f ", zList[i]);
    }
    printf("\r\n================================\r\n");
    //printf("count is: %i \r\n", freqCount);
    //printf("Global count is: %i \r\n", globalcount);
    //fclose(fptr);
     *
     */
}
