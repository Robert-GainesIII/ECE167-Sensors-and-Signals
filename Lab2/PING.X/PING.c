
#include "PING.h"
#include "timers.h"
#include "AD.h"
#include "serial.h"
#include <stdio.h>
#include <stdlib.h>

//TIMERS_GetMicroSeconds()
//TIMERS_GetMilliSeconds()

/**
 * @function    PING_Init(void)
 * @brief       Sets up both the timer and Change notify peripherals along with their
 *              respective interrupts.  Also handles any other tasks needed such as pin 
 *              I/O directions, and any other things you need to initialize the sensor.
 *              TIMERS library must be inited before this library.
 * @return      SUCCESS or ERROR (as defined in BOARD.h)
 */



//VARIABLES
uint8_t state = 0;
uint8_t waiting = 0;
uint16_t count = 0;

volatile int time = 0;

char PING_Init(void) {
    // following block inits the timer
    T4CON = 0;
    T4CONbits.TCKPS = 0b110;
    PR4 = 0x8; //THIS IS NOT THE TIME YO
    T4CONbits.ON = 1;
    IFS0bits.T4IF = 0;
    IPC4bits.T4IP = 3;
    IEC0bits.T4IE = 1;

    // following block inits change notify
    CNCONbits.ON = 1; // Change Notify On
    CNENbits.CNEN14 = 1;
    int temp = PORTD; // this is intentional to ensure a interrupt occur immediately upon enabling
    IFS1bits.CNIF = 0; // clear interrupt flag
    IPC6bits.CNIP = 1; //set priority
    IPC6bits.CNIS = 3; // and sub priority
    IEC1bits.CNIE = 1; // enable change notify
    //Anything else that needs to occur goes here 


    TRISDbits.TRISD8 = 0; //set output on pin 2 (reg D8)
    LATDbits.LATD8 = 0; //set pin 2 high 
    
    time = 0;
    state = 0;
    waiting = 0;
    return SUCCESS;
}

/**
 * @function    PING_GetDistance(void)
 * @brief       Returns the calculated distance in mm using the sensor model determined
 *              experimentally. 
 *              No I/O should extern volatile uint32_t   CNEN __attribute__((section("sfrs"), address(0xBF8861D0))); be done in this function
 * @return      distance in mm
 */
unsigned int PING_GetDistance(void) {
    if(waiting)return 0;
    else return time/58;
}

/**
 * @function    PING_GetTimeofFlight(void)
 * @brief       Returns the raw microsecond duration of the echo from the sensor.
 *              NO I/O should be done in this function.
 * @return      time of flight in uSec
 */
unsigned int PING_GetTimeofFlight(void) {

    return time;
}



void __ISR(_CHANGE_NOTICE_VECTOR) ChangeNotice_Handler(void) {
    static char readPort = 0;
    readPort = PORTD; // this read is required to make the interrupt work
    IFS1bits.CNIF = 0;
    //Anything else that needs to occur goes here
    //ECHO JUST WENT OFF
    //printf("echo went off \r\n");
    
    if (waiting == 0) {
        //printf("Echo just went off. starting timer \r\n");
        time = TIMERS_GetMicroSeconds();
        waiting = 1;
    } else {
        //printf("Echo just went off again. ending timer \r\n");
        time = TIMERS_GetMicroSeconds() - time;
        waiting = 0;
        //printf("time: %i micro seconds\r\n", time);
    }

}

void __ISR(_TIMER_4_VECTOR) Timer4IntHandler(void) {
    IFS0bits.T4IF = 0;
    //Anything else that needs to occur goes here
    //TIMER 4 JUST WENT OFF
    if (state == 0) {
        LATDbits.LATD8 = 1; //set pin 2 high 
        //time = TIMERS_GetMilliSeconds();
        PR4 = 0x6;
        T4CONbits.ON = 1;
        count = 0;
        //printf("state 0 current MS: %i \r\n", TIMERS_GetMicroSeconds());
        state = 1;
    } else {
        if (count == 0)
            LATDbits.LATD8 = 0; //set pin 2 low 
        //time = TIMERS_GetMilliSeconds();
        PR4 = 0x6;
        T4CONbits.ON = 1;
        count++;
        if (count >= 6000) {
            //printf("10000 counts met resetting. \r\n");
            count = 0;
            state = 0;
        } else {
            state = 1;
        }
        //printf("state 1 current MS: %i \r\n", TIMERS_GetMicroSeconds());
        //printf("time: %i \r\n", time);
    }



}