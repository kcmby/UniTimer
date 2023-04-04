#ifndef ENCODER_H
#define ENCODER_H

	#include "commons.h"

	//#define ENC_LIMITS		// ��.����
	#define ENC_TIKS	 	4		/*���������� ��������� �� ���� "������"*/

	#define ENCODER_PORT	PORTC	/*������� ����� ��������*/
	#define PIN_ENC_A			2		/*����� 0 ��������*/
	#define PIN_ENC_B			3		/*����� 1 ��������*/

	#ifdef ENC_LIMITS
	#define ENC_MIN		1
	#define ENC_MAX		99
	#endif

	extern volatile u08 EncData;      			// ���������� ���������� ��������� � ������ ��������

	// ��������� ��������� ������� ��������:
	#define state_0      0x00  								/*��������� 0 ������� ��������*/
	#define state_1      _BV(PIN_ENC_A)             		/*��������� 1 ������� ��������*/
	#define state_2      _BV(PIN_ENC_B)             		/*��������� 2 ������� ��������*/
	#define state_3      _BV(PIN_ENC_B) + _BV(PIN_ENC_A)	/*��������� 3 ������� ��������*/

	/****��������� ������� ****/
	
	void Encoder_init(void);               		// ������� ������������� ��������
	u08 Encoder_Scan(void);						// ������� ��������� ��������
	#ifndef ENC_LIMITS
	void SetEncoder_Lim(u08 l_min, u08 l_max);	// ������� ��������� ������� ��������
	#endif

#endif


