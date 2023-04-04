/******************************************************************************************
 * rtoshal.h
 *
 *  Created on: 11.09.2017 23:55:01
 *      Author: kcm
 */


#ifndef RTOSHAL_H_
#define RTOSHAL_H_

//#include "HAL.h"


#define TIMER_DefVal		0	             	// ��������� �������� �������

#ifdef __AVR_AT90S8515__
	#define RTOS_ISR		TIMER1_COMPA_vect 	// ������ ����������
	#define COMPARE_REG		OCR1A				// ������� ��������� (��� CTC ������)
	#define OCRA_TOP		0x007C				// Max-�������� ��� �������� ���������
	#define TIMER_COUNTER	TCNT1           	// �������-�������

	#define FLAG_OCFA_Reset	{TIFR   |= (1<<OCF1A);}					// �������� ����
	#define CTC_Mode_On		{TCCR1B	|= (1<<CTC1);}					// �������� ����� CTC
	#define COMPARE_A_IE	{TIMSK	|= (1<<OCIE1A);}				// ��������� ����������
	#define Timer_RTS_Start	{TCCR1B	|= ((1<<CS11)|(1<<CS10));}		// ������ ������� (�������� 64)
#endif
#ifdef __AVR_ATmega328P__
// 8-bit Timer/Counter2
	#define RTOS_ISR		TIMER2_COMPA_vect	// ������ ����������
	#define COMPARE_REG		OCR2A				// ������� ��������� (��� CTC ������)
	#define OCRA_TOP		0xF9				// Max-�������� ��� �������� ���������
	#define TIMER_COUNTER	TCNT2           	// �������-�������

	#define FLAG_OCFA_Reset	{TIFR2  |= (1<<OCF2A);}		// �������� ����
	#define CTC_Mode_On		{TCCR2A	|= (1<<WGM21);}		// �������� ����� CTC
	#define COMPARE_A_IE	{TIMSK2	|= (1<<OCIE2A);}	// ��������� ����������
	#define Timer_RTS_Start	{TCCR2B	|= (1<<CS22);}	// ������ ������� (�������� 64)
#endif

#define MAX_TASKS			9               // ���������� �����

#define STATUS_REG 			SREG
#define Interrupt_Flag		SREG_I

void RTOS_Init (void);

#endif /* RTOSHAL_H_ */
