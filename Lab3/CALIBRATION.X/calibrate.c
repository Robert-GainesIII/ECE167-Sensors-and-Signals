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


//#define ACCELDATA
//#define MAGDATA
#define GYRODATA


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
    int freqCount = 0;
    int xangle = 0;
    int yangle = 0;
    int zangle = 0;
    int x,y,z;
    int count = 0;
    DelayMicros(100000);
    while (1) {
     
        globalcount ++;
        
        
       
         
            freqCount ++;
            
            
            //printf("\e[1;1H\e[2J");
            //READ OUT IMU DATA EACH
            #ifdef ACCELDATA
            x = BNO055_ReadAccelX();
            y = BNO055_ReadAccelY();
            z = BNO055_ReadAccelZ();
    
           
            printf("%f \r\n", z/1000.0f);
           
            #endif

            #ifdef GYRODATA
            xangle += BNO055_ReadGyroX()/1000;
            yangle += BNO055_ReadGyroY()/1000;
            zangle += BNO055_ReadGyroZ()/1000;
            //printf("x angle: %d \r\n", xangle);
            //printf("y angle: %d \r\n", yangle);
            count ++;
            if(count >= 5){
                count = 0;
                printf("z angle: %d \r\n", zangle);
            }
           
            #endif

            #ifdef MAGDATA
            printf("%d ", BNO055_ReadMagX());
            printf("%d ", BNO055_ReadMagY());
            printf("%d ", BNO055_ReadMagZ());
            printf("\r\n");
            #endif

            DelayMicros(100000);
            //DELAY(A_BIT);
        
    }
   
}
