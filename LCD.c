/*
 * LCD.c
 *
 *  Created on: Nov 17, 2018
 *      Author: ziad
 */
#include "GPIO.h"
#include "LCD.h"
#include "LCD_CFG.h"

static void Delay (unsigned int DelayVal);
static void SendCmd(unsigned char CmdId);
static void SendData (unsigned char Data);

#if(DATA_MODE==DATA_MODE_8)
static const DataPinsIdx[8]=
{
		DB0_GROUP_IDX,DB1_GROUP_IDX,
		DB2_GROUP_IDX,DB3_GROUP_IDX,
		DB4_GROUP_IDX,DB5_GROUP_IDX,
		DB6_GROUP_IDX,DB7_GROUP_IDX};
};
#else
static const DataPinsIdx[4]=
{
		DB4_GROUP_IDX,DB5_GROUP_IDX,DB6_GROUP_IDX,DB7_GROUP_IDX]
};

#endif
static int InitState=0;
void LCD_Init(void)
{
	Delay(15000);
#if DATA_MODE == DATA_MODE_4
	SendCmd(0x33);
	SendCmd(0x32);
	SendCmd(0x28);
#else
	SendCmd(0x38);
#endif

#if CURSOR_MODE ==CURSOR_OFF
	SendCmd(0x0C);
#else
	SendCmd(0x0E);
#endif
	SendCmd(0x01);
	InitState=1;
}
LCD_ChkType LCD_DispChar (char Data)
{
	char string =Data;
	LCD_Chktype RetVar;
	if(InitState==1)
	{
		SendData(String);
		RetVar=LCD_OK;
	}
	else
	{
		RetVar=LCD_NOK;
	}
	return RetVar;
}

LCD_ChkType LCD_setCursPos(int x,int y)
{
  if(y==0)
  {
	  SendCmd(0x80 + x);
  }
  else
  {
	  SendCmd(0xC0 + x);
  }
}
LCD_ChkType LCD_Clear(void)
{
	SendCmd(0x01);
}
LCD_ChkType LCD_DispString (char *StrPtr)
{
	while ((*StrPtr) !='\0')
	{
		SendData(*StrPtr);
		StrPtr++;
	}
}
static void SendCmd (unsigned char CmdId)
{
	int i;
	unsigned char GpioData,Cmd1;
    GPIO_Write(RS_GROUP_IDX,0x00);
    GPIO_Write(RW_GROUP_IDX,0x00);
#if(DATA_MODE == DATA_MODE_8)
    for(i=0;i<8;i++)
    {
    	GpioData =CmdId & 0x01;
    	GpioData =(~GpioData)+1;
    	CmdId = CmdId >> 1;
    	GPIO_Write(DataPinsIdx[i],GpioData);
    }
    GPIO_Write(EN_GROUP_IDX,0xff);
    Delay(100);
    GPIO_Write(EN_GROUP_IDX,0x00);
#else
Cmd1=(CmdId & 0xF0)>>4;
for(i=0;i<4;i++)
{
	GpioData = Cmd1 & 0x01;
	GpioData = (~GpioData)+1;
	Cmd1=Cmd1 >> 1;
	GPIO_Write(DataPinsIdx[i],GpioData);
}
GPIO_Write(EN_GROUP_IDX,0xff);
Delay(100);
GPIO_Write(EN_GROUP_IDX,0x00);
Cmd1 =(CmdId & 0x0f);
for(i=0;i<4;i++)
{
	GpioData = Cmd1 & 0x01;
	GpioData = (~GpioData)+1;
	Cmd1 = Cmd1 >> 1;
	GPIO_Write(DataPinsIdx[i],GpioData);
}
GPIO_Write(EN_GROUP_IDX,0xff);
Delay(100);
GPIO_Write(EN_GROUP_IDX,0x00);
#endif
Delay(2000);
}
void Delay (unsigned int DelayVal)
{
	volatile long int i;
	for(i=0;i<(DelayVal*4);i++);
}

static void SendData (unsigned char DataId)
{
	int i;
	unsigned char GpioData,Cmd1;
    GPIO_Write(RS_GROUP_IDX,0xff);
    GPIO_Write(RW_GROUP_IDX,0x00);
#if(DATA_MODE == DATA_MODE_8)
    for(i=0;i<8;i++)
    {
    	GpioData = DataId & 0x01;
    	GpioData = (~GpioData)+1;
    	DataId = DataId >> 1;
    	GPIO_Write(DataPinsIdx[i],GpioData);
    }
    GPIO_Write(EN_GROUP_IDX,0xff);
    Delay(100);
    GPIO_Write(EN_Group_IDX,0x00);
#else
    Cmd1 =(DataId & 0xf0) >> 4;
    for(i=0;i<4;i++)
    {
    	GpioData=Cmd1 & 0x01;
    	GpioData =(~GpioData)+1;
    	Cmd1 = Cmd1 >> 1;
    	GPIO_Write(DataPinsIdx[i],GpioData);
    }
    GPIO_Write(EN_GROUP_IDX,0xff);
    Delay(100);
    GPIO_Write(EN_GROUP_IDX,0X00);
    Cmd1= (DataId & 0x0f);
    for(i=0;i<4;i++)
    {
    	GpioData =Cmd1 & 0x01;
    	GpioData =(~GpioData)+1;
    	Cmd1=Cmd1 >> 1;
    	GPIO_Write(DataPinsIdx[i],GpioData);
    }
    GPIO_Write(EN_GROUP_IDX,0xff);
    Delay(100);
    GPIO_Write(EN_GROUP_IDX,0x00);
#endif
    Delay(10);
}
