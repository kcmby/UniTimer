/*
 * ee_special.h
 *
 *  Created on: 14 ����. 2019 �.
 *      Author: KCM
 */

#ifndef EE_SPECIAL_H_
#define EE_SPECIAL_H_

	#include <avr/eeprom.h> 	// ������ � eeprom
	#include "commons.h"
	#include "modes.h"

	typedef struct tmode
	{
		//u08 id;				// id ������
		u08 mode;			// ����� �������
		u08 submode;		// �������� �������
		u08 name[4];		// �������� ������ �� ����������
		u08 d_min;			// ������������ (�����)
		u08 d_sec;			// ������������ (������)
		u08 pulse1;			// ������������ 1-�� �������� (� ��������)
		u08 pauza;			// ����� ����� ���������� (� ��������)
		u08 pulse2;			// ������������ 2-�� �������� (� ��������)
		//u08 enc_min;		// ����������� �������� ��� ���������
		//u08 enc_max;		// ������������ �������� ��� ���������
		u08 dots;			// ������� ����� �� ����������
	}tmode;


	u08 GetLastID(void);
	void SetLastID(u08 id);
	u08 GetLastLampID(void);
	u08 GetLastWeldID(void);
	u08 ForSafety(void);
	void ReadOptions (tmode *buffer, u08 id);
	void WriteOptions (tmode *buffer, u08 id);


#endif /* EE_SPECIAL_H_ */
