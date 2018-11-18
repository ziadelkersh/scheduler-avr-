/*
 * Scheduler.c
 *
 *  Created on: Nov 17, 2018
 *      Author: ziad
 */
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Task.h"
#include "Task_Cfg.h"
#include "Scheduler.h"

static void ArrangeTasksPriority(void);
static void Count_Init(void);


static uint8_t TaskState[NumberofTasks];
static uint8_t TaskArrange[NumberofTasks];
static uint8_t ArrayIndex[NumberofTasks];
static uint8_t Counter[NumberofTasks];

void StartScheduler (void)
{
	ArrangeTasksPriority();
	//Count_Init();
	TCNT0 |=0xf8;
	TCCR0 |=0x01;
	TIMSK |=0x01;
}

ISR(TIMER0_OVF_Vect)
{
	uint8_t LoopIndex ;
	static count=1;
	TCNT0 |=0xf8;
	for(LoopIndex=0;LoopIndex<NumberofTasks;LoopIndex++)
	{
		if((/*Counter[LoopIndex)*/ count % TasksConfigParam[LoopIndex].TaskPeriodicity)==0)
		{
			/* Making the task ready */
			TaskState[LoopIndex]=1;
			//Counter[LoopIndex]=1;
		}
		else
		{
			/* the task is not ready yet */
			TaskState[LoopIndex]=0;
			//Counter[LoopIndex]++
		}
	}
	for (LoopIndex=0;LoopIndex<NumberofTasks;LoopIndex++)
	{
		if(TaskState[ArrayIndex[LoopIndex]]==1)
		{
			//TasksConfigParam[ArrayIndex[LoopIndex]].TaskPtr();
			LCD_DispChar(ArrayIndex[LoopIndex]+48);
		}
		else
		{

		}
	}
	if(count < MaxCount)
	{
		count++;
	}
	else if (count == MaxCount)
	{
		count=1;
	}
	else
	{
		/* do nothing */
	}
}



static void ArrangeTasksPriority(void)
{
	uint8_t LoopIndex;
	uint8_t LoopIndex1;
	uint8_t Temp;
	for(LoopIndex=0;LoopIndex<NumberofTasks;LoopIndex++)
	{
		TaskArrange[LoopIndex]=TasksConfigParam[LoopIndex].TaskPriority;
	}
	for(LoopIndex=0;LoopIndex<NumberofTasks;LoopIndex++)
	{
		for(LoopIndex1=LoopIndex+1;LoopIndex1<NumberofTasks;LoopIndex1++)
		{
			if(TaskArrange[LoopIndex]>TaskArrange[LoopIndex1])
			{
				Temp=TaskArrange[LoopIndex];
				TaskArrange[LoopIndex]=TaskArrange[LoopIndex1];
				TaskArrange[loopIndex1]=Temp;
			}
			else
			{
				/* do nothing */
			}
		}
	}
	for(LoopIndex=0;LoopIndex<NumberofTasks;LoopIndex++)
	{
		for(LoopIndex1=0;LoopIndex1<NumberofTasks;LoopIndex1++)
		{
			if(TaskArrange[LoopIndex]==TasksConfigParam[LoopIndex1].TaskPriority)
			{
				ArrayIndex[LoopIndex]=LoopIndex1;
			}
			else
			{
				/* do nothing */
			}
		}
	}
}

static void Count_Init(void)
{
	uint8_t LoopIndex;
	for (LoopIndex =0;LoopIndex< NumberofTasks;LoopIndex++)
	{
		Counter[LoopIndex]=1;
	}
}
