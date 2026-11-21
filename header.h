/* header.h */

#include <lpc21xx.h>
#include<stdio.h>

typedef unsigned int u32;
typedef signed int s32;
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short int u16;
typedef short int s16;

void delay_ms(u32 );

void uart0_init(u32 );
void uart0_tx(u8 );
unsigned char uart0_rx();
void uart0_tx_string(char * );
void uart0_int(int );

void adc_init();
u32 adc_read(u32 );

void lcd_data(unsigned char data);
void lcd_cmd(unsigned char cmd);
void lcd_init();
void lcd_string(char *ptr);
void lcd_integer(int num);

