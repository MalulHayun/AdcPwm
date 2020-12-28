#include "compiler_defs.h"
#include "C8051F380_defs.h"
#include "lcd_4bit.h"
#include "delay.h"

void Init_Device(void);

/*
P0.3 num=17   P0.4 num=18
P1.0 num=21 P1.1 num=19 P1.2 num=20 P1.3 num=22 P1.6 num=23 P1.7 num=24
P2.0 num=0 P2.1 num=1 P2.2 num=2 P2.3 num=3 P2.4 num=25 P2.5 num=4 P2.6 num=5 P2.7 num=26 
P3.0 num=6 P3.1 num=7 P3.2 num=27 P3.3 num=28 P3.4 num=8 P3.5 num=9 P3.6 num=29 P3.7 num=10
P4.0 num=11 P4.1 num=32 P4.2 num=33 P4.3 num=12 P4.4 num=13P 4.5 num=14 P4.6 num=15 P4.7 num=34
Temp Sensor num=30  VDD   num=31
*/
int ADC_IN(int num) {
	AMX0N     = 0x1F;// negtive input= GND
	AMX0P=num;
	delay_us(1);
	AD0BUSY=1; // start conversion 
	while(!AD0INT); // wait end convesion 
	AD0INT = 0;   // clear ADC0 conversion complete flag 
	return (ADC0);
}

void main(void) {
	int adc;

	Init_Device();
	lcd_begin();
	lcd_println("ADC 10bit P0.3");

	while(1){
		adc=ADC_IN(17); //ADC  P0.3

		PCA0CPH0= adc/4;
		PCA0CPH1= adc/4;
		PCA0CPH2= adc/4;	
	}
}