/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/
#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>
#include <pic18f4685.h>        /* For true/false definition */

#include "uart.h"

// Adjust to system clock
#define _XTAL_FREQ 2000000

/* Initialize UART to provided baud rate */
void uart_init(const long int baudrate)
{
    unsigned int x;
    x = (_XTAL_FREQ - baudrate * 64)/(baudrate * 64);   //SPBRG for Low Baud Rate
    
    SPBRG = x;                                    //Writing SPBRG Register
    TXSTAbits.SYNC = 0;                           //Setting Asynchronous Mode, ie UART
    RCSTAbits.SPEN = 1;                           //Enables Serial Port
    TRISCbits.RC7 = 1;                            //As Prescribed in Datasheet
    TRISCbits.RC6 = 0;                            //As Prescribed in Datasheet
    RCSTAbits.CREN = 1;                           //Enables Continuous Reception
    TXSTAbits.TXEN = 1;     
}

/* Returns true if data is ready in UART */
char uart_data_ready()
{
    return (RCIF || PIR1bits.RCIF);
}

/* Returns a byte from the UART receive buffer */
char uart_read()
{
    while(!(RCIF || PIR1bits.RCIF));
    return RCREG;
}

/* Writes byte provided to UART */
void uart_write(char data)
{
    while(!TRMT);   // Wait until empty
    TXREG = data;
}

/* Writes a string to UART */
void uart_write_text(char *text)
{
  int i;
  for(i = 0; text[i] != '\0'; i++)
    uart_write(text[i]);
}

/* Writes a char array to UART */
void uart_write_array(char *text, unsigned int len)
{
    int i;
    for(i = 0; i < len; i++)
        uart_write(text[i]);
}

/* Reads a string from the UART buffer */
void uart_read_text(char *Output, unsigned int length)
{
    for(int i = 0; i < length; i++)
        Output[i] = uart_read();
}
