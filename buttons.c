/*
 * buttons.c
 *
 *  Created on: 24 ���. 2017 �.
 *      Author: KCM
 */

#include "buttons.h"

/******************************************************************************************
 * ���������� ������
 */
volatile static u08 CurBut;						// ����� ������� ��.
volatile static str_but ButState[MAX_BUTTONS];	// ������ ������ ������
volatile static u08 BCnt;						// ������� ��������� ���������� ��� ������� ������� ������

/*************** ��������� ����� ******************/
static uint8_t buf[BUT_SIZE_BUF];
static uint8_t head, tail, count;
/*************************************************/


/******************************************************************************************
 * ��������� � ����� ������� � ID ������
 * 	4 ��.���� - �������; 4 ��.���� ID ������
 */
static void PutBuf(u08 ev, u08 id)
{
	u08 but;
	but = ev << 4;		// ��������� �������
	but |= id;			// ... � ��� ������

	if (count < BUT_SIZE_BUF){
	 buf[head] = but;
	 count++;
	 head++;
	 head &= (BUT_SIZE_BUF - 1);
	}
}

/******************************************************************************************
 * ������������� ������
 */
void BUT_Init()
{
	u08 i;

	for(i=0; i<MAX_BUTTONS; i++) {
		ButState[i].enable = YES;  //
		ButState[i].def_val = 1;
		//ButState[i].pre_val = 1;
		ButState[i].pre_val = ButState[i].def_val;
		switch(i) {
		   case BUT_START:
			   DirReg(&KEY_PORT) &= ~_BV(PIN_START);	// �������������� �����
			   PortReg(&KEY_PORT) |= _BV(PIN_START);	// ���������� ���������� ��������
		      break;
		   case BUT_ENC:
			   DirReg(&KEY_PORT) &= ~_BV(PIN_ENC_D);
			   PortReg(&KEY_PORT) |= _BV(PIN_ENC_D);
		      break;
		   case BUT_MODE:
			   DirReg(&KEY_PORT) &= ~_BV(PIN_MODE);
			   PortReg(&KEY_PORT) |= ~_BV(PIN_MODE);
		      break;
		}
	}
	head = 0;
	tail = 0;
	count = 0;
}

/******************************************************************************************
 * �������� ��������� ��������� ������
 * 		���� ��� ������ � �������� ��������� - ���������� 0
 * 		���� ��� - ��� ������+1, ������� ��������� � ������ ���������
 */
u08 BUT_IsOk()
{
	u08 i, x;

	for(i=0; i<MAX_BUTTONS; i++) {
		switch(i) {
		   case BUT_START:
			   x = PinReg(&KEY_PORT) & _BV(PIN_START);
		      break;
		   case BUT_ENC:
			   x = PinReg(&KEY_PORT) & _BV(PIN_ENC_D);
		      break;
		   case BUT_MODE:
			   x = PinReg(&KEY_PORT) & _BV(PIN_MODE);
		      break;
		}
		if (x)	x = 1;
		x ^= ButState[i].def_val;
		if (x)
			return i+1;
	}
	return 0;
}

u08 ReadBut(u08 but)
{
	u08 p=0;

	switch(but) {
	   case BUT_START:
		   p = PinReg(&KEY_PORT) & _BV(PIN_START);
	      break;
	   case BUT_ENC:
		   p = PinReg(&KEY_PORT) & _BV(PIN_ENC_D);
	      break;
	   case BUT_MODE:
		   p = PinReg(&KEY_PORT) & _BV(PIN_MODE);
	      break;
	}
	if (p) 	p = 1;
	//else p = 0;

	return p;
}

/******************************************************************************************
 * ������ ��������� ������ �� ������ ������� ���������� (keyhist)
 * 		���������� �� Tsk_ButPoll()
 * 		����������:
 * 		-���� � keyhist ���������� ���������� - ��� ������� (BUT_ShortPress, BUT_LongPress � �.�.)
 * 		-����� - BUT_Error (���������� � keyhist �� ����� ������)
 */
u08 TestHist(u08 keyhist)
{
	u08 h, l, x;

	h = ButState[CurBut].en_hold;
	l = h = ButState[CurBut].en_long;

	x = BUT_Error;
	if (BCnt == TIME_STD) {
		switch(keyhist) {
		   case 0:
			   // ��. ��������
			   x = BUT_Released;
			  break;
		   case 1:
			   if(h | l)	x = BUT_NoEvent;	// ������� ������� ��� ��������� � ��������
			   else			x = BUT_Pressed;	// ��. ������
			  break;
		   case 0b10:
			   // �������� �������
			   x = BUT_ShortPress;
		      break;
		   case 0b1010:
			   // ������� �������
			   x = BUT_DblPress;
		      break;
		}
	}
	else {
		if(keyhist == 1) {
			// ������� ������� ��� ���������
			if(l)   x = BUT_LongPress;
			if(h)   x = BUT_Holded;
		}
	}
	return x;
}


/******************************************************************************************
 * ������������� ����� ������
 * 		���������� �� ����������
 * 		������������� ������ ��. KEY_PERIOD
 */
void Tsk_ButPoll()
{
	u08 i, p;
	static u08 ButGo = NO;		// NO-��� ��. � ���������� ���������, YES-���� ������(��������) ������
	static u08 BHist = 0;		// ������� ��������� ������� ��.

// �������� ������ �� ����� �� ������
	if(ButGo == NO) {
		for(i=0; i<MAX_BUTTONS; i++) {
			if (ButState[i].enable == NO)	continue;
			// ��������� ��������� ������
			p = ReadBut(i);
			// ���������� � ���������� ���������
			if (p != ButState[i].pre_val) {
				// ���� ��������� ��. ����������...
				ButGo = YES;
				CurBut = i;							// ��������� ����� ��.
				ButState[i].change = YES;			// ���������� ������� ���������
				BHist = 0;							// ������� ��. � ���.���������
				BCnt = 0;							// �������� ������� �������
				break;
			}
		}
		return;
	}

// ������� ��� ���� ������ ������
	p = ReadBut(CurBut);				// ��������� ������ ������
	++BCnt;

	if (ButState[CurBut].change == YES) {
		// ������� ��� ���������� ��������� ������
		if (p != ButState[CurBut].pre_val) {
			// ...� ��. � ��� �� ���������, ��� � ������� ��� (������� ��������)
			ButState[CurBut].pre_val = p;		// ��������� ��� ���������
			ButState[CurBut].change = NO;		// ������� ������� ���������
			p ^= ButState[CurBut].def_val;		// (p=1-��. ������, p=0-��. ��������)

			if (ButState[CurBut].isswich) {		// ���� ��� �������������
				p |= SW_Off;
				PutBuf(p, CurBut);				// ... �� ������� � �����
				ButGo = NO;
				return;
			}
			else {								// ���� ��� ������ ��.
				BHist = BHist >> 1;				// ...������� ���������� ������� �������
				BHist |= p;						// ...� ������� ���������
				BCnt = 0;
			}
		}
		else {
			// ...� ������ ���������� ��������� �� ����������� (������?)
			ButState[CurBut].change = NO;
			if (BHist == 0) {
				ButGo = NO;
				return;
			}
		}
	}
	else {
		// ������� ��� ��������� ������ �� ����������
		if (p != ButState[CurBut].pre_val) {
			// ... � �� ���� ���� ��������� ����������
			ButState[CurBut].change = YES;			// ���������� ������� ���������
		}
	}

// ���������� �� ���������� �������� �������� ������� ������� �������(��) ��.
	if((BCnt == TIME_STD) || (BCnt == TIME_LNG)) {
		// ����������� BHist
		p = TestHist(BHist);
		switch(p) {
		   case BUT_NoEvent:
			   // ���������� ������
		      break;
		   case BUT_Error:
			   // ������
			   ButGo = NO;
		      break;
		   default:
			   // �������
			   PutBuf(p, CurBut);
			   ButGo = NO;
		}
	}
	return;
}
/******************************************************************************************
 * ������ �� ������ ������� � ID ������
 *   	4 ��.���� - �������; 4 ��.���� ID ������
 *   	���� ����� ���� �������� 0
 */
u08 BUT_GetBut(void)
{
  u08 but = 0;

  if (count){
     but = buf[tail];
     count--;
     tail++;
     tail &= (BUT_SIZE_BUF - 1);
  }

  return but;
}

/******************************************************************************************
 * ������ ������ ������
 */
inline u08 BUT_GetState(u08 keyid)
{
	return ButState[keyid].enable;
}

/******************************************************************************************
 * �� ������������� ��������� ������
 */
inline void BUT_Ignor(u08 keyid)
{
	ButState[keyid].enable = NO;
}

/******************************************************************************************
 * ������������� ��������� ������
 */
inline void BUT_Activ(u08 keyid)
{
	ButState[keyid].enable = YES;
}
