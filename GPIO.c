/*
 * GPIO.c
 *
 *  Created on: Nov 18, 2018
 *      Author: ziad
 */

include "GPIO.h"
#include "GPIO_Cfg.h"
#include <stdint.h>
typedef volatile uint8_t *const GPIO_RegAddType;
#define PORTS_NUMBER 4u

/* Register memory map */
#define PORTA_BASE_ADDRESS 0x3B
#define PORTB_BASE_ADDRESS 0x38
#define PORTC_BASE_ADDRESS 0x35
#define PORTD_BASE_ADDRESS 0x32

#define DDRA_BASE_ADDRESS 0x3A
#define DDRB_BASE_ADDRESS 0x37
#define DDRC_BASE_ADDRESS 0x34
#define DDRD_BASE_ADDRESS 0x31

#define PINA_BASE_ADDRESS 0x39
#define PINB_BASE_ADDRESS 0x36
#define PINC_BASE_ADDRESS 0x33
#define PIND_BASE_ADDRESS 0x30

static const uint8_t PortBaseAddressLut[PORTS_NUMBER] =
{
	PORTA_BASE_ADDRESS,
	PORTB_BASE_ADDRESS,
	PORTC_BASE_ADDRESS,
	PORTD_BASE_ADDRESS
};

static const uint8_t DDRBaseAddressLut[PORTS_NUMBER] =
{
	DDRA_BASE_ADDRESS,
	DDRB_BASE_ADDRESS,
	DDRC_BASE_ADDRESS,
	DDRD_BASE_ADDRESS
};
static const uint8_t PinBaseAddressLut[PORTS_NUMBER] =
{
	PINA_BASE_ADDRESS,
	PINB_BASE_ADDRESS,
	PINC_BASE_ADDRESS,
	PIND_BASE_ADDRESS
};

/* Port Control */
#define PORT(DATA,MASK,PORT_ID)		*((GPIO_RegAddType)(PortBaseAddressLut[PORT_ID])) = (*((GPIO_RegAddType)(PortBaseAddressLut[PORT_ID])) & ~(MASK)) | (DATA & MASK)
#define DDR(PORT_ID)				*((GPIO_RegAddType)(DDRBaseAddressLut[PORT_ID]))
#define PIN(MASK,PORT_ID)			*((GPIO_RegAddType)(PinBaseAddressLut[PORT_ID])) & MASK

static uint8_t GPIO_GroupState[GPIO_GROUPS_NUMBER]={0};

/* Afunction to initialize all the GPIO Groups in the configurations */
GPIO_CheckType GPIO_Init(void)
{
	uint8_t LoopIndex;
	uint8_t ErrorFlag=0;
	GPIO_CheckType RetVar;
	const GPIO_CfgType *CfgPtr;
	for(LoopIndex=0;((LoopIndex < GPIO_GROUPS_NUMBER)&& (ErrorFlag==0)); LoopIndex++)
	{
		if(GPIO_ConfigParam[LoopIndex].PortID< PORTS_NUMBER)
		{
			CfgPtr=&GPIO_ConfigParam[LoopIndex];
			DDR(CfgPtr->PortId)|=(CfgPtr->PortMask & CfgPtr->PortDirection);
			GPIO_GroupState[LoopIndex]=1;
			RetVar = GPIO_OK;
		}
		else
		{
			RetVar =GPIO_NOK;
			ErrorFlag=1;
		}
	}
	return RetVar;
}
/* Afunction to digital Write data to a specific group */
GPIO_CheckType GPIO_Write (uint8_t GroupId,uint8_t GroupData)
{
	GPIO_CheckType RetVar;
	const GPIO_CfgType *CfgPtr ;
	CfgPtr =&GPIO_ConfigParam[GroupId];
	if((GroupId<GPIO_GROUPS_NUMBER) &&(CfgPtr->PortDirection == 0xFF))
	{
		PORT(GroupData,CfgPtr->PortMask,CfgPtr->PortId);
		RetVar=GPIO_OK;
	}
	else
	{
		RetVar = GPIO_NOK;
	}
	return RetVar;
}
/* A function to digital real data from a specific group */
GPIO_CheckType GPIO_Read (uint8_t GroupId,uint8_t *GroupDataPtr)
{
	GPIO_CheckType Retvar;
	const GPIO_CfgType *CfgPtr;
	CfgPtr =&GPIO_ConfigParam[GroupId];
	if((GroupId<GPIO_GROUPS_NUMBER) && (CfgPtr->PortDirection==0x00))
	{
		*GroupDataPtr = PIN(CfgPtr->PortMask,CfgPtr->PortId);
		RetVar=GPIO_OK;
	}
	else
	{
		RetVar=GPIO_NOK;
	}
	return RetVar;
}
