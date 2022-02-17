/**************************************************************************************************************************************
* LOG:                                                                   							   								  *
* VERSION					AUTHOR           					DATE 						DESCRIPTION 		   					  *
* 1.0.0 					Kareem Hassaan						20 JAN,2022					- Initial Creation						  *
**************************************************************************************************************************************/
/**************************************************************************************************************************************
* ! Title      	: Seven Segment Driver                                                        							              *
* ! File Name	: SevenSeg_private.h                                                     							                  *
* ! Description : This file has the Private definitions needed				       							                          *
* ! Compiler  	: GNU AVR cross Compiler                                            							                      *
* ! Target 	  	: Atmega32 Micro-Controller                                         							                      *
* ! Layer 	  	: HAL                  						                                         							      *
**************************************************************************************************************************************/
#ifndef SevenSeg_PRIVATE_H
#define SevenSeg_PRIVATE_H

#define COMMON_CATHODE					0
#define COMMON_ANODE					1

#define	SEVEN_SEG_ZERO					0b0000001
#define	SEVEN_SEG_ONE					0b1001111
#define	SEVEN_SEG_TWO					0b0010010
#define	SEVEN_SEG_THREE					0b0000110
#define	SEVEN_SEG_FOUR					0b1001100
#define	SEVEN_SEG_FIVE					0b0100100
#define	SEVEN_SEG_SIX					0b0100000
#define	SEVEN_SEG_SEVEN					0b0001111
#define	SEVEN_SEG_EIGHT					0b0000000
#define	SEVEN_SEG_NINE					0b0000100

#define SEVEN_SEG_ARRAY_VALUES		   {SEVEN_SEG_ZERO,\
										SEVEN_SEG_ONE,\
										SEVEN_SEG_TWO,\
										SEVEN_SEG_THREE,\
										SEVEN_SEG_FOUR,\
										SEVEN_SEG_FIVE,\
										SEVEN_SEG_SIX,\
										SEVEN_SEG_SEVEN,\
										SEVEN_SEG_EIGHT,\
										SEVEN_SEG_NINE}	

#endif /*SevenSeg_PRIVATE_H*/