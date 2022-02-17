/**************************************************************************************************************************************
* LOG:                                                                   							   								  *
* VERSION					AUTHOR           					DATE 						DESCRIPTION 		   					  *
* 1.0.0 					Kareem Hassaan						03 JAN,2022					- Initial Creation						  *
**************************************************************************************************************************************/
/**************************************************************************************************************************************
* ! Title      	: SPI Driver                                                        							                      *                     
* ! File Name	: SPI_intrface.h                                                     							                      *
* ! Description : This file has the Definitions needed		         		        							                      *
* ! Compiler  	: GNU AVR cross Compiler                                            							                      *
* ! Target 	  	: Atmega32 Micro-Controller                                         							                      *
* ! Layer 	  	: MCAL                  						                                         							  *
**************************************************************************************************************************************/
#ifndef SPI_INTERFACE_H
#define SPI_INTERFACE_H
/*************************************************************************************************************************************/
/***************************************************** Functions Prototypes **********************************************************/
/*************************************************************************************************************************************/
/**************************************************************************************************************************************
* Function Name		: MSPI_VoidMasterInit															                      			  *
* Parameters (in)	: None																						                      *
* Parameters (out)	: None																						                      *
* Return value		: None																						                      *
* Description		: Function to Initiate the Node as a master				  									                      *
**************************************************************************************************************************************/
void MSPI_VoidMasterInit();
/**************************************************************************************************************************************
* Function Name		: MSPI_VoidSlaveInit															                      			  *
* Parameters (in)	: None																						                      *
* Parameters (out)	: None																						                      *
* Return value		: None																						                      *
* Description		: Function to Initiate the Node as a master				  									                      *
**************************************************************************************************************************************/
void MSPI_VoidSlaveInit();
/**************************************************************************************************************************************
* Function Name		: MSPI_voidTranseiverDataAsynch													                      			  *
* Parameters (in)	: None																						                      *
* Parameters (out)	: None																						                      *
* Return value		: None																						                      *
* Description		: Function to Send Data and Enable the Interrupt to Receive				  					                      *
**************************************************************************************************************************************/
void MSPI_voidTranseiverDataAsynch(uint8 Copy_uint8Data);
/**************************************************************************************************************************************
* Function Name		: MSPI_voidSetCallBack															                      			  *
* Parameters (in)	: void (*Copy_pvNotificationFunction)(void)													                      *
* Parameters (out)	: None																						                      *
* Return value		: None																						                      *
* Description		: Function to Set the CallBack Function					  									                      *
**************************************************************************************************************************************/
void MSPI_voidSetCallBack(void (*Copy_pvNotificationFunction)(void));

#endif /*SPI_INTERFACE_H*/