/**************************************************************************************************************************************
* LOG:                                                                   							   								  *
* VERSION					AUTHOR           					DATE 						DESCRIPTION 		   					  *
* 1.0.0 					Kareem Hassaan						29 JAN,2022					- Initial Creation						  *
**************************************************************************************************************************************/
/**************************************************************************************************************************************
* ! Title      	: Shceduler 	                                                     							                      *                     
* ! File Name	: SCH_intrface.h                                                     							                      *
* ! Description : This file has the Definitions needed		         		        							                      *
* ! Compiler  	: GNU AVR cross Compiler                                            							                      *
* ! Target 	  	: Atmega32 Micro-Controller                                         							                      *
* ! Layer 	  	: SERVICE                  						                                         							  *
**************************************************************************************************************************************/
#ifndef SCH_INTERFACE_H
#define SCH_INTERFACE_H
/*************************************************************************************************************************************/
/***************************************************** Functions Prototypes **********************************************************/
/*************************************************************************************************************************************/
/**************************************************************************************************************************************
* Function Name		: SSCH_VoidInit																				                      *
* Parameters (in)	: None																						                      *
* Parameters (out)	: None																						                      *
* Return value		: None																						                      *
* Description		: Function To Initialize the shceduler by initialize the timer								                      *
**************************************************************************************************************************************/
void SSCH_VoidInit();
/**************************************************************************************************************************************
* Function Name		: SSCH_VoidCreateTask																		                      *
* Parameters (in)	: uint8 Copyuint8Priority, uint32 Copyuint8Periodicity, void (*PtrFunc_Instructions)()			   			      *
* Parameters (out)	: None																						                      *
* Return value		: None																						                      *
* Description		: Function To Create Task and assign its parameters to it									                      *
**************************************************************************************************************************************/
void SSCH_VoidCreateTask(uint8 Copyuint8Priority, uint32 Copyuint8Periodicity, void (*PtrFunc_Instructions)());
/**************************************************************************************************************************************
* Function Name		: SSCH_VoidInit																				                      *
* Parameters (in)	: None																						                      *
* Parameters (out)	: None																						                      *
* Return value		: None																						                      *
* Description		: Function To Initialize the shceduler by initialize the timer								                      *
**************************************************************************************************************************************/
void SSCH_VoidStart();







#endif /*SCH_INTERFACE_H*/