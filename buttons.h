/*
 * buttons.h
 *
 *  Created on: 13 ���. 2019 �.
 *      Author: KCM
 *      ����� ������ ������������ ������ KEY_PERIOD
 */

#ifndef BUTTONS_H_
#define BUTTONS_H_

	//#define BUTWITHSOUND		// ��������������� ���� ��� ���������� ��. � �����

	#include "commons.h"
//	#include "buttonsdef.h"

	#define KEY_PERIOD		10	// ������������� ������ ������ (10mS)
	#define MAX_BUTTONS		3	// ���������� ������
	enum buttons {BUT_START,BUT_ENC,BUT_MODE};

		//PORT Defines
	//#define ENC_PORT		PORTC	// ���� ��������
	#define KEY_PORT		PORTD	// ���� ������ ����������

	//#define PIN_ENC_A		1	// +������ A �������� 				(PC1)
	//#define PIN_ENC_B		0	// +������ B �������� 				(PC0)
	#define PIN_START		0	// ������ ����						(PD0)
	#define PIN_ENC_D		1	// ������ ��������			 		(PD1)
	#define PIN_MODE		2	// ������� �������-������			(PD2)


	typedef struct {u08 enable		:  1;	// ��������� �� ��������� ��. (1-��, 0-���)
					u08 change		:  1;	// ������� ��������� ��������� ������
					u08 isswich		:  1;	// ������� ������������� (�� ������)
					u08 en_long		:  1;	// ��� ��. ��������� ������� �������
					u08 en_hold		:  1;	// ��� ��. ��������� ���������
					u08 def_val		:  1;	// ��������� ������ �� ���������
					u08 pre_val		:  1;	// ���������� ��������� ������
	} str_but;

	#define BUT_Disable			NO
	#define BUT_Enable			YES

	// ��������� ���������
	#define TIME_STD			40		// ��� �������� ����������(��������) ������� (40 * 10mS = 400 mS)
	#define TIME_LNG			150		// ��� �������� �������� ������� (150 * 10mS = 1,5 S)
	//#define TIME_ERR			255		// ���������� ��������� �������� (255 * 10mS = 2,5 S)

	// ������� ������ (�� ��������)
	#define BUT_NoEvent			0b000	// ��� �������
	#define BUT_ShortPress		0b001	// �������� �������
	#define BUT_LongPress		0b010	// ������� �������
	#define BUT_DblPress		0b011	// ������� �������
	#define SW_Off				0b100	// ������������� � ��������� 0
	#define SW_On				0b101	// ������������� � ��������� 1
	#define BUT_Released		0b100	// ��. ���� ��������
	#define BUT_Pressed			0b101	// ��. ���� ������
	#define BUT_Holded			0b110	// ��. ������������
	#define BUT_Error			0xFF	// ���������� �������

	/*������ ������ �������.
	��� �������� ������ ����
	������ ������� ������ (2, 4, 8, 16...).*/
	#define BUT_SIZE_BUF	2

	/**************** ���������������� ������� *****************/

	/*�������������.
	���������� � ������ ���������*/
	void BUT_Init(void);

	/*����� ������/������.
	���������� ������������ (������ 10mS)*/
	void Tsk_ButPoll(void);

	/*����� ������� � ID ������ �� ������.
	4 ��.���� - �������; 4 ��.���� ID ������.*/
	u08 BUT_GetBut(void);

	/* ������ ������ ������ */
	u08 BUT_GetState(u08);


	/* �� ������������� ��������� ������
	*/
	void BUT_Ignor(u08);

	/* ������������� ��������� ������
	*/
	void BUT_Activ(u08);

	/* �������� ��������� ��������� ������
	 * 		���� ��� ������ � �������� ��������� - ���������� 0
	 * 		���� ��� - ��� ������, ������� ��������� � ������ ��������� */
	u08 BUT_IsOk(void);

#endif /* BUTTONS_H_ */
