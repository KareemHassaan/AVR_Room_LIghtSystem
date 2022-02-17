/**************************************************************************************************************************************
* LOG:                                                                   							   								  *
* VERSION					AUTHOR           					DATE 						DESCRIPTION 		   					  *
* 1.0.0 					Kareem Hassaan						03 JAN,2022					- Initial Creation						  *
**************************************************************************************************************************************/
/**************************************************************************************************************************************
* ! Title      	: SPI Driver                                                        							                      *
* ! File Name	: SPI_private.h                                                     							                      *
* ! Description : This file has the Private definitions needed				       							                          *
* ! Compiler  	: GNU AVR cross Compiler                                            							                      *
* ! Target 	  	: Atmega32 Micro-Controller                                         							                      *
* ! Layer 	  	: MCAL                  						                                         							  *
**************************************************************************************************************************************/
#ifndef SPI_PRIVATE_H
#define SPI_PRIVATE_H

//************************************************************************************************************************************/
/***************************************************** Registers Memory Map **********************************************************/
/*************************************************************************************************************************************/

/**************************************************** SPI Control Register ***********************************************************/

#define SPCR  									*((volatile uint8 *)0x2D)				//SPI Control Register

#define SPCR_SPR0								0										//SPI Clock Rate Select Bit 0			
#define SPCR_SPR1								1										//SPI Clock Rate Select Bit 1 		
#define SPCR_CPHA								2										//Clock Phase			
#define SPCR_CPOL								3										//Clock Polarity			
#define SPCR_MSTR								4										//Master/Slave Select			
#define SPCR_DORD								5										//Data Order			
#define SPCR_SPE								6										//SPI Enable		
#define SPCR_SPIE								7										//SPI Interrupt Enable			    

/***************************************************** SPI Status Register ***********************************************************/

#define SPSR  									*((volatile uint8 *)0x2E)				//SPI Status Register

#define SPSR_SPI2X								0										//Double SPI Speed Bit
#define SPSR_WCOL								6										//Write COLlision Flag
#define SPSR_SPIF 								7										//SPI Interrupt Flag

/***************************************************** SPI Data Registe ***********************************************************/

#define SPDR 									*((volatile uint8 *)0x2F)				//SPI Data Registe

#define	ENABLE 									1
#define DISABLE									0

#define LSB_FIRST			 					0b00100000
#define MSB_FIRST			 					0b00000000
#define DORD_MASK			 					0b11011111

#define LEADING_RISING_TRAILING_FALLING			0b00000000
#define LEADING_FALLING_TRAILING_RISING			0b00001000
#define CPOL_MASK			 					0b11110111

#define LEADING_SAMPLE_TRAILING_SETUP			0b00000000
#define LEADING_SETUP_TRAILING_SAMPLE			0b00000100
#define CPHA_MASK			 					0b11111011

#define FOSC_DIVIDE_BY_4						0b00000000
#define FOSC_DIVIDE_BY_16         				0b00000001
#define FOSC_DIVIDE_BY_64         				0b00000010
#define FOSC_DIVIDE_BY_128        				0b00000011
#define DS_FOSC_DIVIDE_BY_2          			0b00000000
#define DS_FOSC_DIVIDE_BY_8          			0b00000001
#define DS_FOSC_DIVIDE_BY_32         			0b00000010
#define DS_FOSC_DIVIDE_BY_64         			0b00000011

#define PRESCALLER_MASK         				0b11111100

#endif /*SPI_PRIVATE_H*/