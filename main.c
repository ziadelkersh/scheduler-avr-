/*
 * main.c
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include "GPIO.h"
#include "GPIO_Cfg.h"
#include "LCD.h"
#include "LCD_Cfg.h"
#include "Scheduler.h"
#include "Task.h"
#include "Task_Cfg.h"

int main(void) {
	DDRB=0xFF;
	DDRA=0x0F;
	DDRC|=0x01;
	StartScheduler();
	GPIO_Init();
	LCD_Init();
	sei();
	while(1)
	{
		/* Do nothing */
	}
	return 0;
}
/* void Timer_OneMs(void)
 * {
 * TCNT0|=0xf8;
 * TCCR0|=0X01;
 * TIMSK|=0X01;
 * }
 */

 /*ISR(TIMER0_OVF_vect) {
  *TIFR|=0X01;
  *TCNT0|=0Xf8;
  *if(x==0){
  *ptr();
  *x++; }
  *else if (x==1){
  *ptr1();
  *x--; }
  *  }
  * void Red_Led (void){
  * PORTA ^=0xFF; }
  *
  * void Green_Led (void) {
  * PORTC ^=0X01
  * LCD_DispString("LED State is ON");
  */
