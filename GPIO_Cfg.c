/*
 * GPIO_Cfg.c
 *
 *  Created on: Nov 18, 2018
 *      Author: ziad
 */

#include "GPIO.h"
#include "GPIO_Cfg.h"
const GPIO_CfgType GPIO_ConfigParam [GPIO_GROUPS_NUMBER] =
		{


			 {
					0x02,1<<6,
                    0xff
			 }
            ,{
	               	0x02,1<<5,
	               	0xff
             }
            ,{
	               	0x02,1<<7,
	               	0xff
             }
            ,{
	               	0x03,1<<4,
	               	0xff
			 }
            ,{
					0x03,1<<5,
	               	0xff
             }
            ,{
	               	0x03,1<<6,
	               	0xff
             }
            ,{
	               	0x03,1<<7,
	               	0xff
             }

		};




