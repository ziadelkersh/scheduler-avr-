/*
 * Task_Cfg.c
 *
 *  Created on: Nov 17, 2018
 *      Author: ziad
 */

#include <stdint.h>
#include "Task.h"
#include "Task_Cfg.h"

const taskParameters TaskConfigParam [NumberofTasks]=
{
		{
				1,
				5,
				LCD_Display
		},
		{
			2,
			5,
			Keypad_Display
		},
};
