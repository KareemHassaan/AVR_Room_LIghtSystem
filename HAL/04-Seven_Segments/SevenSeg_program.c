/**************************************************************************************************************************************
* LOG:                                                                   							   								  *
* VERSION					AUTHOR           					DATE 						DESCRIPTION 		   					  *
* 1.0.0 					Kareem Hassaan						20 JAN,2022					- Initial Creation						  *
**************************************************************************************************************************************/
/**************************************************************************************************************************************
* ! Title      	: Seven Segment Driver                                                 							                      *
* ! File Name	: SevenSeg_program.c                                                      						                      *
* ! Description : This file has the implementation of Basic of Seven Segment functions        							              *
* ! Compiler  	: GNU AVR cross Compiler                                            							                      *
* ! Target 	  	: Atmega32 Micro-Controller                                         							                      *
* ! Layer 	  	: HAL	                  						                                         							  *
**************************************************************************************************************************************/

/**************************************************** Library Inclusions *************************************************************/
#include"../../LIB/STD_TYPES.h"
#include"../../LIB/BIT_MATH.h"
/************************************************** Lower Layer Inclusions ***********************************************************/
#include"../../MCAL/01-DIO/DIO_intrface.h" 
/************************************************** Self Layer Inclusions ************************************************************/

/************************************************** Self Files Inclusions ************************************************************/
#include"SevenSeg_intrface.h"  
#include"SevenSeg_private.h"
#include"SevenSeg_config.h"

/***************************************************** Global Variables **************************************************************/
static uint8 SevenSegmentArray[10] = SEVEN_SEG_ARRAY_VALUES;

/*************************************************************************************************************************************/
/***************************************************** Functions Definition **********************************************************/
/*************************************************************************************************************************************/
/**************************************************************************************************************************************
* Function Name		: HSevenSegment_VoidInit																	                      *
* Parameters (in)	: None																						                      *
* Parameters (out)	: None																						                      *
* Return value		: None																						                      *
* Description		: Function To Initialize the Port Of The Seven Segment										                      *
**************************************************************************************************************************************/
void HSevenSegment_VoidInit()
{
	MDIO_voidSetPortDirection(SEVEN_SEGMENT_PORT, ALL_OUTPUT);
}

/**************************************************************************************************************************************
* Function Name		: HSevenSegment_VoidInit																	                      *
* Parameters (in)	: None																						                      *
* Parameters (out)	: None																						                      *
* Return value		: None																						                      *
* Description		: Function To Initialize the Port Of The Seven Segment										                      *
**************************************************************************************************************************************/
void HSevenSegment_VoidDisplayNumber(uint8 Copy_uint8Number)
{
	#if(SEVEN_SEGMENT_TYPE == COMMON_ANODE)
			
			MDIO_voidSetPortValue(SEVEN_SEGMENT_PORT, SevenSegmentArray[Copy_uint8Number]);
			
	#elif(SEVEN_SEGMENT_TYPE == COMMON_CATHODE)
		
			MDIO_voidSetPortValue(SEVEN_SEGMENT_PORT, ~SevenSegmentArray[Copy_uint8Number]);
			
	#else
	
		#error"SEVEN_SEGMENT_TYPE Confogration Error"
	
	#endif	
}