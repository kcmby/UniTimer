/*
 * main.h
 *
 *  Created on: 26 ����. 2019 �.
 *      Author: SKudich
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "commons.h"
#include "modes.h"


//#define ENC_FLAG_UP		1			// ������� ������������� ������ ��������
//#define ENC_FLAG_DOWN	0			// ...��� ����������
#define WELD_YES		1			// ���� ������� ������
#define WELD_NO			0			// ������� ������ ��������
#define MAX_WELDING		10000		// max ������������ ������ � ������ ������ (� ����.)

#define ONESECOND		1000

/******************************************************************************************
 * ��������� �������
 */
//void ButInWeld(u08 keyid, u08 event);
//void ButInLamp(u08 keyid, u08 event);
//void ButInSetup(u08 keyid, u08 event);

void ButHandler_Start(u08 event);
void ButHandler_Enc(u08 event);
void ButHandler_Mode(u08 event);

void Sound(u16 signal, u08 times);
void Opt2Ind(u08 m, u08 s);
void Time2Second(void);

void Tsk_Sound_On (void);
void Tsk_Sound_Off (void);
void Tsk_Countdown (void);
void Tsk_Countup(void);
void Tsk_IndBlink_On (void);
void Tsk_Symistor1_On(void);
void Tsk_Symistor_Off(void);
void Tsk_Symistor2_On(void);
void Tsk_Symistor_pause(void);
void Tsk_Encoder(void);

void BlinkDigit_On(u08 digit);
void BlinkDigit_Off(void);

void Power(void);					// ���. ��������
void GhangeMode(void);
void GhangeSubMode(u08 flag);

void CurOptions(void);
void ReadCurOptions(void);
void ShowCurSettings(void);


void I_PowerOff(void);


#endif /* MAIN_H_ */
