/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>        /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>       /* HiTech General Include File */
#elif defined(__18CXX)
    #include <p18cxxx.h>   /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */


#endif

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */
#include "uart.h"       
/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/


/* i.e. uint8_t <variable_name>; */
unsigned int state = 1;
/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

void main(void) {
    char speed = 0x00;
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp();
    
    uart_init(2400);
    
    while (1) {
        
        if (uart_data_ready()) {
            speed = uart_read(); 
            setSpeed(speed);
        }
    }

}

// Main Interrupt Service Routine (ISR)
/*
void interrupt ISR(void) {
    wait_ms(5);
    if(INTCONbits.INT0IF) {
        if (state == 0) {
            int i;
            for (i = 0; i < 11; i++) {
                setSpeed(i);
            }
            for ( ; i > -1; i--) {
                setSpeed(i);
            }
            state = 1;
        } else if (state == 1) {
            setSpeed(10);
            wait_ms(5);
            state = 2;
        } else {
            setSpeed(0);
            wait_ms(5);
            state = 0;
        }
        
        INTCONbits.INT0IF = 0;
    }
}
*/

