
#include"header.h"

#define GREEN_LED     (1<<17)
#define YELLOW_LED    (1<<18)
#define RED_LED       (1<<19)
#define PIR_PIN       (1<<30)
#define FLAME_PIN     (1<<5)
#define SAFE          0
#define WARNING       1
#define DANGER        2

float temperature;
int pir_status, flame_status, system_status;
unsigned int adc_value;

void lcd_display(void)
{
    lcd_cmd(0x80);
    lcd_string("TEMP:");
    lcd_integer((int)temperature);
    lcd_string(" C   ");

    lcd_cmd(0xC0);

    if(system_status == SAFE)
        lcd_string("STATUS: SAFE    ");

    else if(system_status == WARNING)
        lcd_string("STATUS: WARNING ");

    else
        lcd_string("STATUS: DANGER  ");
}

void uart_display(void)
{
    uart0_tx_string("\r\nTemperature: ");
    uart0_int((int)temperature);

    uart0_tx_string(" C\r\nWorker: ");
    uart0_tx_string(pir_status ? "YES" : "NO");

    uart0_tx_string("\r\nFire: ");
    uart0_tx_string(flame_status ? "YES" : "NO");

    uart0_tx_string("\r\nStatus: ");

    if(system_status == SAFE)
        uart0_tx_string("SAFE");

    else if(system_status == WARNING)
        uart0_tx_string("WARNING");

    else
        uart0_tx_string("DANGER");

    uart0_tx_string("\r\n-------------------\r\n");
}

int main(void)
{
	
  VPBDIV = 0;
	IODIR0|=GREEN_LED|YELLOW_LED|RED_LED;
	IOSET0|=GREEN_LED|YELLOW_LED|RED_LED;

    adc_init();
    uart0_init(9600);
    lcd_init();
    lcd_cmd(0x0C);

    while(1)
    {
		adc_value = adc_read(0);
		temperature=((adc_value*3.3f) / 1023.0f)*100.0f;
		pir_status = (IOPIN0 & PIR_PIN) ? 1 : 0;
		flame_status = (IOPIN0 & FLAME_PIN) ? 0 : 1;
		
		if(temperature >= 50 || flame_status)
        system_status = DANGER;

		else if(temperature >= 40 || pir_status)
			system_status = WARNING;

		else
			system_status = SAFE;
        
        IOSET0=GREEN_LED|YELLOW_LED|RED_LED;
		
		if(system_status==SAFE)
			IOCLR0=GREEN_LED;
		else if(system_status == WARNING)
			IOSET0 = YELLOW_LED;
		else
			IOSET0 = RED_LED;
			
        lcd_display();
        uart_display();

        delay_ms(1000);
    }
}
