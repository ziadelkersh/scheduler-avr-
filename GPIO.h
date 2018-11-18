/*
 * GPIO.h
 *
 *  Created on: Nov 18, 2018
 *      Author: ziad
 */

#ifndef GPIO_H_
#define GPIO_H_

#include <stdint.h>
#include "GPIO_Cfg.h"
typedef void (*GPIO_FnPtrType)(void);
typedef struct
{
	uint8_t PortId;
	uint8_t PortMask;
	/* Data Control */
	/* input->0
	 * output ->1
	 */
	uint8_t PortDirection ;
}GPIO_CfgType;
typedef enum {GPIO_OK =0, GPIO_NOK} GPIO_CheckType;
typedef enum {EVENT_FALL_EDGE = 0, EVENT_RISE_EDGE = 0x01, EVENT_BOTH_EDGE = 0x04,
	          EVENT_LOW = 0x02, EVENT_HIGH = 0x03} GPIO_IntEventType;
typedef enum {MASK_ENABLED = 0xff,MASK_DISABLED = 0x00} GPIO_IntMaskStatus;
typedef enum {INT_PENDING = 0xff,INT_INACTIVE = 0x00}GPIO_IntStatus;
extern const GPIO_CfgType GPIO_ConfigParam [GPIO_GROUPS_NUMBER];

/*A function to initialize all the GPIO Groups in the configurations*/
GPIO_CheckType GPIO_Init(void);
/*A function to Digital Write data to a specific group*/
GPIO_CheckType GPIO_Write(uint8_t GroupId,uint8_t GroupData);
/*A function to Digital read data from a specific group*/
GPIO_CheckType GPIO_Read(uint8_t GroupId,uint8_t* GroupDataPtr);
/*A function to select which peripheral will be connected to a GPIO pin*/
GPIO_CheckType GPIO_SetAlternFuntion(uint8_t GroupId,uint8_t AlternFuncId);
/*A function to Select the interrupt event for a specific GPIO Group*/
GPIO_CheckType GPIO_SetInterruptEvent(uint8_t GroupId,GPIO_IntEventType IntEvent,GPIO_IntMaskStatus IntMaskStatus);
/*A function to clear a specific pin interrupt flag*/
GPIO_CheckType GPIO_ClrInterruptFlag(uint8_t GroupId);
/*A function to Get a specific pin interrupt status*/
GPIO_CheckType GPIO_GetInterruptStatus(uint8_t GroupId,GPIO_IntStatus *IntStatusPtr);



#endif /* GPIO_H_ */
