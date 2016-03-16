/******************************************************************************/
/* Function prototypes and definitions                                        */
/******************************************************************************/
void uart_init(const long int baudrate);
char uart_data_ready();
char uart_read();
void uart_write(char data);
void uart_write_text(char *text);
void uart_write_array(char *text, unsigned int len);
void uart_read_text(char *Output, unsigned int length);