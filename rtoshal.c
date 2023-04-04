/******************************************************************************************
 * rtoshal.c
 *
 *  Created on: 12.09.2017 0:06:38
 *      Author: kcm
 */

#include "rtoshal.h"
#include "commons.h"

volatile u08 arrayTail;                  // "�����" �������

/******************************************************************************************
 * ������������� ����, ����� ���� - 1 ��
 */
inline void RTOS_Init()
{
	arrayTail = 0;							// "�����" � 0

	FLAG_OCFA_Reset							// �������� ����
	TIMER_COUNTER 	= TIMER_DefVal;			// ��������� ��������� ��. � ������� �������
	COMPARE_REG	  	= OCRA_TOP;				// ��������� ������� ���������
	CTC_Mode_On								// �������� ����� CTC
	COMPARE_A_IE							// Compare Match A Interrupt Enable
	Timer_RTS_Start							// ����� (��������� - 64)
}
