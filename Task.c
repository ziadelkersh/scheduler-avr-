/*
 * Task.c
 *
 *  Created on: Nov 17, 2018
 *      Author: ziad
 */
#include <avr/io.h>
#include <stdint.h>
#include "Task.h"
#include "Task_Cfg.h"

uint8_t key;

void Keypad_display (void)
{
	PORTB ^=0x01;
	Key=Keypad_GetKey();
}

void LCD_Display (void)
{
	PORTC ^=0x01;
	LCD_SetCursPos(0,0);
	LCD_DispString("The Key is :");
	LCD_DispChar(Key);
}

uint8_t Keypad_GetKey(void)
{
	uint8_t static KeyPressed =' ';
	PORTA &=~(0x1F);
	if(((PINA & 0xE0))== 0xE0)
	{
		KeyPressed=KeyPressed;
	}
	else if ((PINA & 0x80)==0)
	{
		PORTA=0x1E;
		if((PINA & 0x80)==0)
		{
			KeyPressed='1';
		}
		else
		{
			PORTA=0x1D;
			if((PINA & 0x80)==0)
			{
				KeyPressed='4';
			}
			else
			{
				PORTA=0x1B;
				if((PINA & 0x80)==0)
				{
					KeyPressed='7';
				}
				else
				{
					PORTA=0x17;
					if((PINA & 0x80)==0)
					{
						KeyPressed='*';
					}
					else
					{
						/* do nothing */
					}
				}
			}
		}
	}
	else if((PINA & 0x40)==0)
	{
		PORTA=0x1E;
		if((PINA &0x40)==0)
		{
			KeyPressed='2';
		}
		else
		{
			PORTA=0x1D;
			if((PINA & 0x40)==0)
			{
				KeyPressed ='5';
			}
			else
			{
				PORTA=0x1B;
				if((PINA &0x40)==0)
				{
					KeyPressed='8';
				}
				else
				{
					PORTA=0x17;
					if((PINA &0x40)==0)
					{
						KeyPressed='0';
					}
					else
					{
						/* Do nothing */
					}
				}
			}
		}
	}
	else if ((PINA & 0x20)==0)
	{
		PORTA=0x1E;
		if((PINA & 0x20)==0)
		{
			KeyPressed='3';
		}
		else
		{
			PORTA=0x1D;
			if((PINA &0x20)==0)
			{
				KeyPressed='6';
			}
			else
			{
				PORTA=0x1B;
				if((PINA & 0x20)==0)
				{
					KeyPressed='9';
				}
				else
				{
					PORTA=0x17;
					if((PINA &0x20)==0)
					{
						KeyPressed = '#'
					}
					else
					{
						/* do nothing */
					}
				}
			}
		}
	}
	return KeyPressed;
}

