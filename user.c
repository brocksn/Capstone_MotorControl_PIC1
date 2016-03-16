/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#elif defined(__18CXX)
    #include <p18cxxx.h>    /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#endif

#include "user.h"
#include "system.h"

/* Lookup table for CCPR1L register values:
 * -0 means motor off, 1ms wide pulses
 * -10 means max motor speed, 2ms wide pulses */
static const char table1[] = {
    0b00011111,
    0b00100010,
    0b00100101,
    0b00101000,
    0b00101011,
    0b00101110,
    0b00110001,
    0b00110101,
    0b00111000,
    0b00111011,
    0b00111110
};

/* Lookup table for CCPR1CON register values:
 * -0 means motor off, 1ms wide pulses
 * -10 means max motor speed, 2ms wide pulses */
static const char table2[] = {
    0b00001100,
    0b00011100,
    0b00011100,
    0b00101100,
    0b00101100,
    0b00111100,
    0b00111100,
    0b00001100,
    0b00001100,
    0b00011100,
    0b00011100
};

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

void InitApp(void) {
    /* Setup analog functionality and port direction */
    TRISA = 0x00;
    PORTA = 0x00;
    TRISC = 0x00;
    PORTC = 0x00;
    TRISBbits.TRISB0 = 0b1;
    
    /* Enable Interrupts */
    /*
    INTCONbits.GIE  = 0b1;    // Enable interrupts
    INTCONbits.INT0IE = 0b1;    // Enable external interrupts.
    INTCON2bits.INTEDG0 = 0b0;  // Sets external interrupt on falling edge
    */
    // Initialize PWM
   
    PR2 = 0b10011011 ;
    T2CON = 0b00000111 ;
    setSpeed(0);
    enableMotor();
    
    
    
    /* Configure the IPEN bit (1=on) in RCON to turn on/off int priorities */

    /* Enable interrupts */
}

void enableMotor() {
    CCP1CONbits.CCP1M = 0xF;
}

void disableMotor() {
    CCP1CONbits.CCP1M = 0x0;
}

void setSpeed(unsigned char speed) {
    //disableMotor();
    if (!(speed > 10 || speed < 0)) {
        CCPR1L = table1[speed];
        CCP1CON = table2[speed];
    } else {
        CCPR1L = table1[0];
        CCP1CON = table2[0];
    }

    //enableMotor();
    wait_ms(50);
}

void wait_ms(uint16_t time) {
    for (int i = 0; i < time; i++) {
        __delay_ms(1);
    }
    
    //static long timel = 0;
    //timel = time * 1251;
    //for( ; timel; timel--);// no initial condition, while time is >0, decrement time each loop
}