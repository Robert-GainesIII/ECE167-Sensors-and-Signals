#include "QEI.h"
#include "serial.h"
#include <stdio.h>
#include <stdlib.h>
#include "pwm.h"

/*
This module uses the change notify peripheral to interface to a quadrature encoder. 
 *          If you are unfamiliar with change notify please read the lab appendix before beginning.
 *          The peripheral is configured to generate an interrupt on any change in input of pins RD6
 *          or RD7 (pins 36 and 37 on the Uno32). The interrupt will not tell you which pin changed
 *          states so you will need to implement a simple state machine to handle the transitions and
 *          keep track of the encoder count.
 *          NOTE: Encoder A and B must be input to pins 36 and 37

/**
 * @function QEI_Init(void)
 * @param none
 * @brief  Enables the Change Notify peripheral and sets up the interrupt, anything
 *         else that needs to be done to initialize the module. 
 * @return SUCCESS or ERROR (as defined in BOARD.h)
*/


int count = 0;
uint8_t ready = 0;
int state = 0;

char QEI_Init(void){
    // INIT Change notify
        CNCONbits.ON = 1; // Change Notify On
        CNENbits.CNEN15 = 1; //enable one phase
        CNENbits.CNEN16 = 1; //enable other phase
        int temp = PORTD; // this is intentional to ensure a interrupt occur immediately upon enabling
        IFS1bits.CNIF = 0; // clear interrupt flag
        IPC6bits.CNIP = 1; //set priority
        IPC6bits.CNIS = 3; // and sub priority
        IEC1bits.CNIE = 1; // enable change notify
       
        count = 0;
        state = 0;
        
}

/**
 * @function QEI_GetPosition(void) 
 * @param none
 * @brief This function returns the current count of the Quadrature Encoder in ticks.      
*/
int QEI_GetPosition(void){
    return count/4;
}

/**
 * @Function QEI_ResetPosition(void) 
 * @param  none
 * @return none
 * @brief  Resets the encoder such that it starts counting from 0.
*/
void QEI_ResetPosition(){
    count = 0;
}

volatile uint32_t output = 0;
 void __ISR(_CHANGE_NOTICE_VECTOR) ChangeNotice_Handler(void) {
    static char readPort = 0;
    readPort = PORTD; // this read is required to make the interrupt work
    output = PORTD;
    IFS1bits.CNIF = 0;
    int a = PORTDbits.RD7;
    int b = PORTDbits.RD6;
    //printf("==================================\r\n");
    
    printf("count: %d \r\n", count);
    
    
    if(state == 0){
        //ready
     
        if(a == 0)
        {
            state = 2;
            printf("going to state 1\r\n");
            count ++;
        }
        if(b == 0)
        {
            state = 1;
            printf("going to state 2\r\n");
            count --;
            
        }
        
               
    }
    else if(state == 1){
       
        
        if(b == 1){
            printf("going to state 0\r\n");
            state = 0;
            count ++;
        }
        
        if(a == 0){
            printf("going to state 3\r\n");
            state = 3;
            count --;
        }
       
            
       

    }
    else if(state == 2){
     
        if(b == 0){
            printf("going to state 3\r\n");
            state = 3;
            count ++;
        }
        if(a == 1){
            printf("going to state 0\r\n");
            state = 0;
            count --;
        }
        
        
    }
    else if(state = 3){
        //not ready yet
  
        if(a == 1){
            printf("going to state 2\r\n");
            state = 1;
            count ++;
        }
        if(b == 1){
            printf("going to state 1\r\n");
            state = 2;
            count --;
        }
        
        //printf("leaving state 3\r\n");
    }
               //anything else that needs to happen goes here
    if(count <= -96){
                count = 0;
    }
    if(count >= 96)count = 0;
     printf("==================================\r \n\n\n");
}
 
 