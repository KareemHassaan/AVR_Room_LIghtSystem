/**************************************************************************************************************************************
* LOG:                                                                   							   								  *
* VERSION					AUTHOR           					DATE 						DESCRIPTION 		   					  *
* 1.0.0 					Kareem Hassaan						25 JAN,2022					- Initial Creation						  *
**************************************************************************************************************************************/
/**************************************************************************************************************************************
* ! Title      	: Time Triggered Tempreture Controlled Fan                                                        					  *
* ! File Name	: main.c                                                       							                      		  *
* ! Description : A Time Triggered system measure the tempreture of an atmosphere of a machine and Controlled the speed of a Fan      *
* ! Compiler  	: GNU AVR cross Compiler                                            							                      *
* ! Target 	  	: Atmega32 Micro-Controller                                         							                      *
* ! Layer 	  	: APP	                  						                                         							  *
**************************************************************************************************************************************/

/**************************************************** Library Inclusions *************************************************************/
#define F_CPU 8000000UL
#include<util/delay.h>
#include"../LIB/STD_TYPES.h"
#include"../LIB/BIT_MATH.h"
/************************************************** Lower Layer Inclusions ***********************************************************/
#include"../MCAL/01-DIO/DIO_intrface.h"
#include"../MCAL/02-EXT_INTERRUPT/EXTI_intrface.h"
#include"../MCAL/03-GIE/GIE_intrface.h"
#include"../MCAL/06-USART/USART_intrface.h"
#include"../MCAL/05-Timers/TIMERS_intrface.h"
/********************************************************* Macros ********************************************************************/
#define ROOM_MAIN_LIGHT						'a'
#define ROOM_FAN							'b'
#define ROOM_BED_LAMP						'c'
#define ROOM_OFFICE_LAMP					'd'
#define	ROOM_CUPBOARD_LIGHTING				'e'
#define	ROOM_MIRROR_LIGHTING				'f'
#define	ROOM_TELEVISION						'g'
#define	ROOM_TV_BACKLIGHT					'h'
#define	ROOM_TV_BABYLIGHT					'i'
#define	ROOM_WALL_BABYLIGHT					'j'
#define ROOM_DISCO_LIGHT_1					'k'
#define ROOM_DISCO_LIGHT_2					'l'
#define	ROOM_TV_BABYLIGHT_CTL				'm'
#define	ROOM_WALL_BABYLIGHT_CTL				'n'
#define ROOM_SYSTEM_OFF						'o'

#define ROOM_MAIN_LIGHT_PIN							PIN0
#define ROOM_FAN_PIN								PIN1
#define ROOM_BED_LAMP_PIN							PIN2
#define ROOM_OFFICE_LAMP_PIN						PIN3
#define	ROOM_CUPBOARD_LIGHTING_PIN					PIN4
#define	ROOM_MIRROR_LIGHTING_PIN					PIN5
#define	ROOM_TELEVISION_PIN							PIN6
#define	ROOM_TV_BACKLIGHT_PIN						PIN7

#define	ROOM_TV_BABYLIGHT_PIN						PIN0
#define	ROOM_WALL_BABYLIGHT_PIN						PIN1
#define ROOM_DISCO_LIGHT_1_PIN						PIN2
#define ROOM_DISCO_LIGHT_2_PIN						PIN3
#define	ROOM_TV_BABYLIGHT_CTL_PIN					PIN4
#define	ROOM_WALL_BABYLIGHT_CTL_PIN					PIN5

#define	ON											0
#define	SLOW_ANIMATION								1
#define	MEDIUM_ANIMATION							2
#define	FAST_ANIMATION								3
#define	OFF											4

#define ON_OFF_TIMEOUT								40000
#define SLOW_TIMEOUT								2000
#define MEDIUM_TIMEOUT								800
#define FAST_TIMEOUT								200

#define GO_IN										0
#define GO_OUT										1
/**************************************************** Global Variables ***************************************************************/
uint8 Local_uint8SystemOption;
uint8 ROOM_DISCO_LIGHT_1_Counter = 0;
uint8 ROOM_DISCO_LIGHT_2_Counter = 0;
uint8 Local_uint8SystemStatus = 0;

/*************************************************** Functions Prototypes ************************************************************/
void RoomPIR_TimerCBKFunc();
void RoomPIR_EXTI_CBKFunc();
void Disco1_CBKFunc();
void Disco2_CBKFunc();

/*************************************************************************************************************************************/
/****************************************************** Main Function ****************************************************************/
/*************************************************************************************************************************************/
void main()
{
	MUSART_VoidInit();
	/*Initiate TX and RX Of USART Output Pins*/
	MDIO_voidSetPinDirection(PORTD,PIN0,INPUT);
	MDIO_voidSetPinDirection(PORTD,PIN1,OUTPUT);
	MDIO_voidSetPinDirection(PORTD,PIN2,INPUT);

	MDIO_voidSetPortDirection(PORTA, ALL_OUTPUT);
	MDIO_voidSetPortDirection(PORTB, ALL_OUTPUT);

	MDIO_voidSetPortValue(PORTA, ALL_HIGH);
	MDIO_voidSetPortValue(PORTB, ALL_HIGH);

	MGIE_voidGlobalInterruptEnable();

	M_EXTI_VoidInit();
	M_EXTI_voidSetCallback(INT0, RoomPIR_EXTI_CBKFunc);

	MTIMERS_voidSetCallBack(TIMER0, OVERFLOW, RoomPIR_TimerCBKFunc);
	MTIMERS_voidSetCallBack(TIMER1, OVERFLOW, Disco1_CBKFunc);
	MTIMERS_voidSetCallBack(TIMER2, OVERFLOW, Disco2_CBKFunc);


	while (1)
	{
		MUSART_VoidSendString("|***********************************************************| \r\n");
		Local_uint8SystemOption = MUSART_VoidReceive();

		switch(Local_uint8SystemOption)
		{
			case ROOM_MAIN_LIGHT :

					if(MDIO_uint8GetPinValue(PORTA, ROOM_MAIN_LIGHT_PIN) == LOW)
					{
						MDIO_voidSetPinValue(PORTA, ROOM_MAIN_LIGHT_PIN,HIGH);
						MUSART_VoidSendString("Room Main Light OFF \r\n");
					}
					else
					{
						MDIO_voidSetPinValue(PORTA, ROOM_MAIN_LIGHT_PIN, LOW);
						MUSART_VoidSendString("Room Main Light ON \r\n");
					}
			break;

			case ROOM_FAN :

					if(MDIO_uint8GetPinValue(PORTA, ROOM_FAN_PIN) == LOW)
					{
						MDIO_voidSetPinValue(PORTA, ROOM_FAN_PIN,HIGH);
						MUSART_VoidSendString("Room Fan OFF \r\n");
					}
					else
					{
						MDIO_voidSetPinValue(PORTA, ROOM_FAN_PIN, LOW);
						MUSART_VoidSendString("Room Fan ON \r\n");
					}
			break;

			case ROOM_BED_LAMP :

					if(MDIO_uint8GetPinValue(PORTA, ROOM_BED_LAMP_PIN) == LOW)
					{
						M_EXTI_VoidInterruptEnable(INT0, DISABLE);
						MDIO_voidSetPinValue(PORTA, ROOM_BED_LAMP_PIN,HIGH);
						MUSART_VoidSendString("Room Bed Lamp OFF \r\n");
					}
					else
					{
						MDIO_voidSetPinValue(PORTA, ROOM_BED_LAMP_PIN, LOW);
						M_EXTI_VoidInterruptEnable(INT0, ENABLE);
						MUSART_VoidSendString("Room Bed Lamp ON \r\n");
					}
			break;

			case ROOM_OFFICE_LAMP :

					if(MDIO_uint8GetPinValue(PORTA, ROOM_OFFICE_LAMP_PIN) == LOW)
					{
						MDIO_voidSetPinValue(PORTA, ROOM_OFFICE_LAMP_PIN,HIGH);
						MUSART_VoidSendString("Room Office Lamp OFF \r\n");
					}
					else
					{
						MDIO_voidSetPinValue(PORTA, ROOM_OFFICE_LAMP_PIN, LOW);
						MUSART_VoidSendString("Room Office Lamp ON \r\n");
					}
			break;

			case ROOM_CUPBOARD_LIGHTING :

					if(MDIO_uint8GetPinValue(PORTA, ROOM_CUPBOARD_LIGHTING_PIN) == LOW)
					{
						MDIO_voidSetPinValue(PORTA, ROOM_CUPBOARD_LIGHTING_PIN,HIGH);
						MUSART_VoidSendString("Room Cupboard Light OFF \r\n");
					}
					else
					{
						MDIO_voidSetPinValue(PORTA, ROOM_CUPBOARD_LIGHTING_PIN, LOW);
						MUSART_VoidSendString("Room Cupboard Light ON \r\n");
					}
			break;

			case ROOM_MIRROR_LIGHTING :

					if(MDIO_uint8GetPinValue(PORTA, ROOM_MIRROR_LIGHTING_PIN) == LOW)
					{
						MDIO_voidSetPinValue(PORTA, ROOM_MIRROR_LIGHTING_PIN,HIGH);
						MUSART_VoidSendString("Room Mirror Light OFF \r\n");
					}
					else
					{
						MDIO_voidSetPinValue(PORTA, ROOM_MIRROR_LIGHTING_PIN, LOW);
						MUSART_VoidSendString("Room Mirror Light ON \r\n");
					}
			break;

			case ROOM_TELEVISION :

					if(MDIO_uint8GetPinValue(PORTA, ROOM_TELEVISION_PIN) == LOW)
					{
						MDIO_voidSetPinValue(PORTA, ROOM_TELEVISION_PIN,HIGH);
						MUSART_VoidSendString("Room Television OFF \r\n");
					}
					else
					{
						MDIO_voidSetPinValue(PORTA, ROOM_TELEVISION_PIN, LOW);
						MUSART_VoidSendString("Room Television ON \r\n");
					}
			break;

			case ROOM_TV_BACKLIGHT :

					if(MDIO_uint8GetPinValue(PORTA, ROOM_TV_BACKLIGHT_PIN) == LOW)
					{
						MDIO_voidSetPinValue(PORTA, ROOM_TV_BACKLIGHT_PIN,HIGH);
						MUSART_VoidSendString("Room Television Back Light OFF \r\n");
					}
					else
					{
						MDIO_voidSetPinValue(PORTA, ROOM_TV_BACKLIGHT_PIN, LOW);
						MUSART_VoidSendString("Room Television Back Light ON \r\n");
					}
			break;

			case ROOM_TV_BABYLIGHT :

					if(MDIO_uint8GetPinValue(PORTB, ROOM_TV_BABYLIGHT_PIN) == LOW)
					{
						MDIO_voidSetPinValue(PORTB, ROOM_TV_BABYLIGHT_PIN,HIGH);
						MUSART_VoidSendString("Room Television Baby Light OFF \r\n");
					}
					else
					{
						MDIO_voidSetPinValue(PORTB, ROOM_TV_BABYLIGHT_PIN, LOW);
						MUSART_VoidSendString("Room Television Baby Light ON \r\n");
					}
			break;

			case ROOM_WALL_BABYLIGHT :

					if(MDIO_uint8GetPinValue(PORTB, ROOM_WALL_BABYLIGHT_PIN) == LOW)
					{
						MDIO_voidSetPinValue(PORTB, ROOM_WALL_BABYLIGHT_PIN,HIGH);
						MUSART_VoidSendString("Room Wall Baby Light OFF \r\n");

					}
					else
					{
						MDIO_voidSetPinValue(PORTB, ROOM_WALL_BABYLIGHT_PIN, LOW);
						MUSART_VoidSendString("Room Wall Baby Light ON \r\n");
					}

			break;

			case ROOM_DISCO_LIGHT_1 :

					switch(ROOM_DISCO_LIGHT_1_Counter)
					{
						case ON :

								ROOM_DISCO_LIGHT_1_Counter = SLOW_ANIMATION;
								MDIO_voidSetPinValue(PORTB, ROOM_DISCO_LIGHT_1_PIN,LOW);
								MUSART_VoidSendString("Room Disco Light 1 ON \r\n");
						break;


						case SLOW_ANIMATION:

								ROOM_DISCO_LIGHT_1_Counter = MEDIUM_ANIMATION;
								MTIMERS_VoidTimer1Init();
								MUSART_VoidSendString("Room Disco Light 1 Slow Animation \r\n");
						break;

						case MEDIUM_ANIMATION :

								ROOM_DISCO_LIGHT_1_Counter = FAST_ANIMATION;
								MUSART_VoidSendString("Room Disco Light 1 Medium Animation \r\n");
						break;

						case FAST_ANIMATION :

								ROOM_DISCO_LIGHT_1_Counter = OFF;
								MUSART_VoidSendString("Room Disco Light 1 Fast Animation \r\n");
						break;

						case OFF :

								MTIMERS_VoidTimer1Disable();
								ROOM_DISCO_LIGHT_1_Counter = ON;
								MDIO_voidSetPinValue(PORTB, ROOM_DISCO_LIGHT_1_PIN, HIGH);
								MUSART_VoidSendString("Room Disco Light 1 OFF \r\n");
						break;
					}

			break;

			case ROOM_DISCO_LIGHT_2 :

					switch(ROOM_DISCO_LIGHT_2_Counter)
					{
						case ON :

								ROOM_DISCO_LIGHT_2_Counter = SLOW_ANIMATION;
								MDIO_voidSetPinValue(PORTB, ROOM_DISCO_LIGHT_2_PIN,LOW);
								MUSART_VoidSendString("Room Disco Light 2 ON \r\n");
						break;


						case SLOW_ANIMATION:

								ROOM_DISCO_LIGHT_2_Counter = MEDIUM_ANIMATION;
								MTIMERS_VoidTimer2Init();
								MUSART_VoidSendString("Room Disco Light 2 Slow Animation \r\n");
						break;

						case MEDIUM_ANIMATION :

								ROOM_DISCO_LIGHT_2_Counter = FAST_ANIMATION;
								MUSART_VoidSendString("Room Disco Light 2 Medium Animation \r\n");
						break;

						case FAST_ANIMATION :

								ROOM_DISCO_LIGHT_2_Counter = OFF;
								MUSART_VoidSendString("Room Disco Light 2 Fast Animation \r\n");
						break;

						case OFF :

								MTIMERS_VoidTimer2Disable();
								ROOM_DISCO_LIGHT_2_Counter = ON;
								MDIO_voidSetPinValue(PORTB, ROOM_DISCO_LIGHT_2_PIN, HIGH);
								MUSART_VoidSendString("Room Disco Light 2 OFF \r\n");
						break;
					}
			break;

			case ROOM_TV_BABYLIGHT_CTL :

					MDIO_voidSetPinValue(PORTB, ROOM_TV_BABYLIGHT_CTL_PIN,LOW);
					_delay_ms(1000);
					MDIO_voidSetPinValue(PORTB, ROOM_TV_BABYLIGHT_CTL_PIN,HIGH);
					MUSART_VoidSendString("Tv BabyLight Mode Changed \r\n");

			break;

			case ROOM_WALL_BABYLIGHT_CTL :

					MDIO_voidSetPinValue(PORTB, ROOM_WALL_BABYLIGHT_CTL_PIN,LOW);
					_delay_ms(1000);
					MDIO_voidSetPinValue(PORTB, ROOM_WALL_BABYLIGHT_CTL_PIN,HIGH);
					MUSART_VoidSendString("Wall BabyLight Mode Changed \r\n");
			break;

			case ROOM_SYSTEM_OFF:

					M_EXTI_VoidInterruptEnable(INT0, DISABLE);
					Local_uint8SystemStatus = GO_OUT;
					MUSART_VoidSendString("System OFF GoodBye \r\n");
					MTIMERS_VoidTimer0Init();
			break;
		}
	}
}

void RoomPIR_EXTI_CBKFunc()
{
	if(MDIO_uint8GetPinValue(PORTA, ROOM_BED_LAMP_PIN) == HIGH)
	{
		Local_uint8SystemStatus = GO_IN;
		MDIO_voidSetPinValue(PORTA, ROOM_OFFICE_LAMP_PIN,LOW);
		MTIMERS_VoidTimer0Init();
	}
}

void RoomPIR_TimerCBKFunc()
{
	static uint32 Local_uint32TimeOut = 0;
	Local_uint32TimeOut++;

	if(Local_uint32TimeOut == ON_OFF_TIMEOUT)
	{
		if(Local_uint8SystemStatus == GO_OUT)
		{
			 MDIO_voidSetPortValue(PORTA, ALL_HIGH);
			 MDIO_voidSetPortValue(PORTB, ALL_HIGH);
			 M_EXTI_VoidInterruptEnable(INT0, ENABLE);
		}
		else
		{
			MDIO_voidSetPinValue(PORTA, ROOM_OFFICE_LAMP_PIN,HIGH);
		}

		Local_uint32TimeOut = 0;
		MTIMERS_VoidTimer0Disable();
	}
}

void Disco1_CBKFunc()
{
	static uint32 Local_uint32TimeOut = 0;
	Local_uint32TimeOut++;

	switch(ROOM_DISCO_LIGHT_1_Counter-1)
	{
		case SLOW_ANIMATION:

				if(Local_uint32TimeOut == SLOW_TIMEOUT)
				{
					if(MDIO_uint8GetPinValue(PORTB, ROOM_DISCO_LIGHT_1_PIN) == LOW)
					{
						MDIO_voidSetPinValue(PORTB, ROOM_DISCO_LIGHT_1_PIN,HIGH);
					}
					else
					{
						MDIO_voidSetPinValue(PORTB, ROOM_DISCO_LIGHT_1_PIN,LOW);
					}

					Local_uint32TimeOut = 0;
				}
		break;

		case MEDIUM_ANIMATION :

			if(Local_uint32TimeOut == MEDIUM_TIMEOUT)
			{
				if(MDIO_uint8GetPinValue(PORTB, ROOM_DISCO_LIGHT_1_PIN) == LOW)
				{
					MDIO_voidSetPinValue(PORTB, ROOM_DISCO_LIGHT_1_PIN,HIGH);
				}
				else
				{
					MDIO_voidSetPinValue(PORTB, ROOM_DISCO_LIGHT_1_PIN,LOW);
				}

				Local_uint32TimeOut = 0;
			}

		break;

		case FAST_ANIMATION :

			if(Local_uint32TimeOut == FAST_TIMEOUT)
			{
				if(MDIO_uint8GetPinValue(PORTB, ROOM_DISCO_LIGHT_1_PIN) == LOW)
				{
					MDIO_voidSetPinValue(PORTB, ROOM_DISCO_LIGHT_1_PIN,HIGH);
				}
				else
				{
					MDIO_voidSetPinValue(PORTB, ROOM_DISCO_LIGHT_1_PIN,LOW);
				}

				Local_uint32TimeOut = 0;
			}
		break;
	}
}

void Disco2_CBKFunc()
{
	static uint32 Local_uint32TimeOut = 0;
		Local_uint32TimeOut++;

		switch(ROOM_DISCO_LIGHT_2_Counter-1)
		{
			case SLOW_ANIMATION:

					if(Local_uint32TimeOut == SLOW_TIMEOUT)
					{
						if(MDIO_uint8GetPinValue(PORTB, ROOM_DISCO_LIGHT_2_PIN) == LOW)
						{
							MDIO_voidSetPinValue(PORTB, ROOM_DISCO_LIGHT_2_PIN,HIGH);
						}
						else
						{
							MDIO_voidSetPinValue(PORTB, ROOM_DISCO_LIGHT_2_PIN,LOW);
						}

						Local_uint32TimeOut = 0;
					}
			break;

			case MEDIUM_ANIMATION :

				if(Local_uint32TimeOut == MEDIUM_TIMEOUT)
				{
					if(MDIO_uint8GetPinValue(PORTB, ROOM_DISCO_LIGHT_2_PIN) == LOW)
					{
						MDIO_voidSetPinValue(PORTB, ROOM_DISCO_LIGHT_2_PIN,HIGH);
					}
					else
					{
						MDIO_voidSetPinValue(PORTB, ROOM_DISCO_LIGHT_2_PIN,LOW);
					}

					Local_uint32TimeOut = 0;
				}

			break;

			case FAST_ANIMATION :

				if(Local_uint32TimeOut == FAST_TIMEOUT)
				{
					if(MDIO_uint8GetPinValue(PORTB, ROOM_DISCO_LIGHT_2_PIN) == LOW)
					{
						MDIO_voidSetPinValue(PORTB, ROOM_DISCO_LIGHT_2_PIN,HIGH);
					}
					else
					{
						MDIO_voidSetPinValue(PORTB, ROOM_DISCO_LIGHT_2_PIN,LOW);
					}

					Local_uint32TimeOut = 0;
				}
			break;
		}

}
