/**************************************************************************************************************************************
* LOG:                                                                   							   								  *
* VERSION					AUTHOR           					DATE 						DESCRIPTION 		   					  *
* 1.0.0 					Kareem Hassaan						29 JAN,2022					- Initial Creation						  *
**************************************************************************************************************************************/
/**************************************************************************************************************************************
* ! Title      	: Shceduler 	                                                        							                  *
* ! File Name	: SCH_program.c                                                       							                      *
* ! Description : This file has the implementation of Basic of Simple Shceduler functions (Non-preemptive – fixed priority)           *
* ! Compiler  	: GNU AVR cross Compiler                                            							                      *
* ! Target 	  	: Atmega32 Micro-Controller                                         							                      *
* ! Layer 	  	: SERVICE                  						                                         							  *
**************************************************************************************************************************************/

/**************************************************** Library Inclusions *************************************************************/
#include"../../LIB/STD_TYPES.h"
#include"../../LIB/BIT_MATH.h"
/************************************************** Lower Layer Inclusions ***********************************************************/
#include"../../MCAL/05-Timers/TIMERS_intrface.h"
/************************************************** Self Layer Inclusions ************************************************************/

/************************************************** Self Files Inclusions ************************************************************/
/*Must be with that order maybe change Private with config only*/
#include"SCH_intrface.h"  
#include"SCH_private.h"
#include"SCH_config.h"

/***************************************************** Global Variables **************************************************************/
static Task ArrStruct_TaskShcedule[TASK_NUM] = {{0}}; //Array of struct To Store Tasks as Index of the array is the priority of the Task

/*************************************************************************************************************************************/
/***************************************************** Functions Definition **********************************************************/
/*************************************************************************************************************************************/
/**************************************************************************************************************************************
* Function Name		: SSCH_VoidInit																				                      *
* Parameters (in)	: None																						                      *
* Parameters (out)	: None																						                      *
* Return value		: None																						                      *
* Description		: Function To Initialize the shceduler by initialize the timer								                      *
**************************************************************************************************************************************/
void SSCH_VoidInit()
{
	/*Initialize Timer 0*/
	MTIMERS_VoidTimer0Init();	
}

/**************************************************************************************************************************************
* Function Name		: SSCH_VoidCreateTask																		                      *
* Parameters (in)	: uint8 Copyuint8Priority, uint32 Copyuint8Periodicity, void (*PtrFunc_Instructions)()			   			      *
* Parameters (out)	: None																						                      *
* Return value		: None																						                      *
* Description		: Function To Create Task and assign its parameters to it									                      *
**************************************************************************************************************************************/
void SSCH_VoidCreateTask(uint8 Copyuint8Priority, uint32 Copyuint8Periodicity, void (*PtrFunc_Instructions)())
{
	/*Storing the Task Periodicity in its structure in Array*/
	ArrStruct_TaskShcedule[Copyuint8Priority].TaskPeriodicity = Copyuint8Periodicity;
	/*Storing the Task Instructions in its structure in Array*/
	ArrStruct_TaskShcedule[Copyuint8Priority].PtrFunc_TaskInstructios = PtrFunc_Instructions;
}

/**************************************************************************************************************************************
* Function Name		: SSCH_VoidInit																				                      *
* Parameters (in)	: None																						                      *
* Parameters (out)	: None																						                      *
* Return value		: None																						                      *
* Description		: Function To Initialize the shceduler by initialize the timer								                      *
**************************************************************************************************************************************/
void SSCH_VoidStart()
{
	/*Set CallBack Function to the Timer to Excute it Each OVF*/
	MTIMERS_voidSetCallBack(TIMER0, OVERFLOW, &SSCH_VoidShceduler);	
}

/**************************************************************************************************************************************
* Function Name		: SSCH_VoidShceduler																				              *
* Parameters (in)	: None																						                      *
* Parameters (out)	: None																						                      *
* Return value		: None																						                      *
* Description		: Function To Excute Tasks in its Time Period								                      				  *
**************************************************************************************************************************************/
static void SSCH_VoidShceduler()
{
	static uint32 Local_uint32TickCounter = 0;
	uint8  Local_uint32TaskLoopCounter    = 0;
	Local_uint32TickCounter++;
	
	/*Looping on Task By Task Scaning Its Periodicity*/
	for(Local_uint32TaskLoopCounter = 0; Local_uint32TaskLoopCounter < TASK_NUM; Local_uint32TaskLoopCounter++)
	{
		if(0 == Local_uint32TickCounter % ArrStruct_TaskShcedule[Local_uint32TaskLoopCounter].TaskPeriodicity)
		{
			if(ArrStruct_TaskShcedule[Local_uint32TaskLoopCounter].PtrFunc_TaskInstructios != NULL)
			{
				ArrStruct_TaskShcedule[Local_uint32TaskLoopCounter].PtrFunc_TaskInstructios();
			}
		}
	}
	
}



