/**************************************************************************************************************************************
* LOG:                                                                   							   								  *
* VERSION					AUTHOR           					DATE 						DESCRIPTION 		   					  *
* 1.0.0 					Kareem Hassaan						03 JAN,2022					- Initial Creation						  *
**************************************************************************************************************************************/
/**************************************************************************************************************************************
* ! Title      	: SPI Driver                                                        							                      *
* ! File Name	: SPI_program.c                                                       							                      *
* ! Description : This file has the implementation of Basic of SPI functions        							                      *
* ! Compiler  	: GNU AVR cross Compiler                                            							                      *
* ! Target 	  	: Atmega32 Micro-Controller                                         							                      *
* ! Layer 	  	: MCAL                  						                                         							  *
**************************************************************************************************************************************/

/**************************************************** Library Inclusions *************************************************************/
#include"../../LIB/STD_TYPES.h"
#include"../../LIB/BIT_MATH.h"
/************************************************** Lower Layer Inclusions ***********************************************************/

/************************************************** Self Layer Inclusions ************************************************************/

/************************************************** Self Files Inclusions ************************************************************/
/*Must be with that order maybe change Private with config only*/
#include"SPI_intrface.h"  
#include"SPI_private.h"
#include"SPI_config.h"

/***************************************************** Global Variables **************************************************************/
static void (*Global_pvCallBackFunction)(void) = NULL;					   //Global Pointer to Function to set the call back Function 	
uint8 MSPI_uint8ReceiveData = 0;										   //Global Variable to Store the Recived Data

/*************************************************************************************************************************************/
/***************************************************** Functions Definition **********************************************************/
/*************************************************************************************************************************************/
/**************************************************************************************************************************************
* Function Name		: MSPI_VoidMasterInit															                      			  *
* Parameters (in)	: None																						                      *
* Parameters (out)	: None																						                      *
* Return value		: None																						                      *
* Description		: Function to Initiate the Node as a master				  									                      *
**************************************************************************************************************************************/
void MSPI_VoidMasterInit()
{
	/*Set the node to be master*/
	 SET_BIT(SPCR,SPCR_MSTR);
	
	/*Configre the Data MSB or LSB Transfer first according to the configration*/
	 SET_SPECIFIC_REG_BITS_VALUE(SPCR,DORD_MASK,DATA_ORDER_VALUE);
	
	
	/*Configer the CPOL according to the configration*/
	 SET_SPECIFIC_REG_BITS_VALUE(SPCR,CPOL_MASK,CLOCK_POLARITY_VALUE);
	/*Configer the CPHA according to the configration*/
	 SET_SPECIFIC_REG_BITS_VALUE(SPCR,CPHA_MASK,CPHA_FUNCTIONALITY_VALUE);
	
	
	/*Configer the Prescaller according to the configration*/
	 #if(DOUBLE_SPEED_ENABLE == ENABLE)
		
		/*Enable the Double Speed Mode*/
		 SET_BIT(SPSR,SPSR_SPI2X);
		 SET_SPECIFIC_REG_BITS_VALUE(SPCR,PRESCALLER_MASK,PRESCALLER_VALUE);
		
	 #elif(DOUBLE_SPEED_ENABLE == DISABLE)
		
		/*Disable the Double Speed Mode*/
		 CLR_BIT(SPSR,SPSR_SPI2X);
		 SET_SPECIFIC_REG_BITS_VALUE(SPCR,PRESCALLER_MASK,PRESCALLER_VALUE);
		
	 #else
		
		/*Printing that DOUBLE_SPEED_ENABLE has Configration error*/
		 #error"DOUBLE_SPEED_ENABLE Configration error"
		
	 #endif
	
	/*Enable SPI*/
	 SET_BIT(SPCR,SPCR_SPE);
}

/**************************************************************************************************************************************
* Function Name		: MSPI_VoidSlaveInit															                      			  *
* Parameters (in)	: None																						                      *
* Parameters (out)	: None																						                      *
* Return value		: None																						                      *
* Description		: Function to Initiate the Node as a master				  									                      *
**************************************************************************************************************************************/
void MSPI_VoidSlaveInit()
{
	/*Set the node to be master*/
	CLR_BIT(SPCR,SPCR_MSTR);
	
	/*Configre the Data MSB or LSB Transfer first according to the configration*/
	 SET_SPECIFIC_REG_BITS_VALUE(SPCR,DORD_MASK,DATA_ORDER_VALUE);
	
	
	/*Configer the CPOL according to the configration*/
	 SET_SPECIFIC_REG_BITS_VALUE(SPCR,CPOL_MASK,CLOCK_POLARITY_VALUE);
	/*Configer the CPHA according to the configration*/
	 SET_SPECIFIC_REG_BITS_VALUE(SPCR,CPHA_MASK,CPHA_FUNCTIONALITY_VALUE);
	
	
	/*Configer the Prescaller according to the configration*/
	 #if(DOUBLE_SPEED_ENABLE == ENABLE)
		
		/*Enable the Double Speed Mode*/
		 SET_BIT(SPSR,SPSR_SPI2X);
		 SET_SPECIFIC_REG_BITS_VALUE(SPCR,PRESCALLER_MASK,PRESCALLER_VALUE);
		
	 #elif(DOUBLE_SPEED_ENABLE == DISABLE)
		
		/*Disable the Double Speed Mode*/
		 CLR_BIT(SPSR,SPSR_SPI2X);
		 SET_SPECIFIC_REG_BITS_VALUE(SPCR,PRESCALLER_MASK,PRESCALLER_VALUE);
		
	 #else
		
		/*Printing that DOUBLE_SPEED_ENABLE has Configration error*/
		 #error"DOUBLE_SPEED_ENABLE Configration error"
		
	 #endif
	
	/*Enable SPI*/
	 SET_BIT(SPCR,SPCR_SPE);
}

/**************************************************************************************************************************************
* Function Name		: MSPI_voidTranseiverDataAsynch													                      			  *
* Parameters (in)	: None																						                      *
* Parameters (out)	: None																						                      *
* Return value		: None																						                      *
* Description		: Function to Send Data and Enable the Interrupt to Receive				  					                      *
**************************************************************************************************************************************/
void MSPI_voidTranseiverDataAsynch(uint8 Copy_uint8Data)
{
	/*Storing the Wanted Data to send*/
	SPDR = Copy_uint8Data;
	
	/*Enable Spi Interrupt*/
	SET_BIT(SPCR,SPCR_SPIE);
}

/**************************************************************************************************************************************
* Function Name		: MSPI_voidSetCallBack															                      			  *
* Parameters (in)	: void (*Copy_pvNotificationFunction)(void)													                      *
* Parameters (out)	: None																						                      *
* Return value		: None																						                      *
* Description		: Function to Set the CallBack Function					  									                      *
**************************************************************************************************************************************/
void MSPI_voidSetCallBack(void (*Copy_pvNotificationFunction)(void))
{
    Global_pvCallBackFunction = Copy_pvNotificationFunction;
}


/*************************************************************************************************************************************/
/************************************************************ SPI ISR ****************************************************************/
/*************************************************************************************************************************************/
void __vector_12 (void) __attribute__((signal));
void __vector_12 (void)
{
	/* Get the Received Data */
    MSPI_uint8ReceiveData = SPDR;
	
    if(Global_pvCallBackFunction != NULL)
    {
        Global_pvCallBackFunction();
    }
	
    CLR_BIT(SPCR, SPCR_SPIE);
}