/*
 * sound.h
 *
 *  Created on: 18 ���. 2019 �.
 *      Author: SKudich
 */

#ifndef SOUND_H_
#define SOUND_H_

#include "commons.h"

#define SOUND_PORT		PORTD	// ���� �����
#define PIN_SND			6		// ��� �����

#define Tone			0x31	// ������� �����
#define ShortSignal		50					// ������������ ��������� �������
#define LongSignal		500					// ������������ �������� �������
#define PauseSignal		200					// ����� ����� ���������

// 8-bit Timer/Counter0
#define Sound_On()	do{TCCR0B = ((1<<CS01)|(1<<CS00));} while(0)	// ���. ������� (�������� 64)
#define Sound_Off()	do{TCCR0B = 0; TCNT0 = 0;} while(0)				// ����. �������

/******************************************************************************************
 * ��������� �������
 */
void Sound_Init(void);
void SetSnd(u16 signal, u08 times);
u08 NextSnd(void);
u16 DurationSnd(void);

#endif /* SOUND_H_ */
