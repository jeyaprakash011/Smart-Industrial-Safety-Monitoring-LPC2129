
#include"header.h"
void delay_ms(u32 ms)
 {
 T0PR=15000-1;
 T0PC=0;
 T0TC=0;
 TOTCR=0XO2;
 T0TCR=0X01;
 while(T0TC<ms);
 T0TCR=0;
 }
