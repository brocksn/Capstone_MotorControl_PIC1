
/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/



/* TODO Application specific user parameters used in user.c may go here */

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

/* TODO User level functions prototypes (i.e. InitApp) go here */

void InitApp(void);         /* I/O and Peripheral Initialization */

void enableMotor(void);     // Enables motor by activating PWM output

void disableMotor(void);    // Disables motor by deactivating PWM output

void setSpeed(unsigned char speed);   // Changes motor speed by adjusting PWM duty cycle

void wait_ms(uint16_t time);
