/*
 * Task.h
 *
 *  Created on: Nov 17, 2018
 *      Author: ziad
 */

#ifndef TASK_H_
#define TASK_H_

#include <stdint.h>
#include "Task_Cfg.h"

typedef struct
{
	uint8_t TaskPriority;
	uint8_t TaskPeriodicity;
	void (*TaskPtr) (void);
}TaskParameters;

extern const TaskParameters TaskConfigParam [NumberofTasks];

void LCD_Display(void);
void Keypad_Display(void);
uint8_t Keypad_GetKey(void);

#endif /* TASK_H_ */
