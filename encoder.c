//����� ������� ��� ������������ ���������������� ��������
//����� s_black - www.embed.com.ua
//���� 2010 �. 	

#include "encoder.h"

#ifndef ENC_LIMITS
u08 ENC_MIN;
u08 ENC_MAX;
#endif

inline void Encoder_init (void)//������� ������������� ��������
{
	/****�������������� ����� ��� ����������� �������� ****/
	DirReg(&ENCODER_PORT)  &= ~(_BV(PIN_ENC_A));
	DirReg(&ENCODER_PORT)  &= ~(_BV(PIN_ENC_B));
	/****���������� ���������� �������� ****/
	PortReg(&ENCODER_PORT) |= _BV(PIN_ENC_A) | _BV(PIN_ENC_B);
}

//#ifdef ENC_LIMITS
u08 Encoder_Scan(void)//������� ��������� ��������
{
    static u08 New, EncPlus, EncMinus;//���������� ������ �������� ��������, ������������� ���������� + � -
    static u08 EncState;
	uint8_t ret = 0;

    New = PinReg(&ENCODER_PORT) & (_BV(PIN_ENC_B) | _BV(PIN_ENC_A));// ��������� ��������� ��������� ��������

    if(New != EncState)//���� �������� ���������� �� ��������� � ��������
    {
        switch(EncState) //������� �������� �������� ��������
	    {
	    case state_2:if(New == state_3) EncPlus++;//� ����������� �� �������� �����������
		             if(New == state_0) EncMinus++;//��� ���������
		       break;
	    case state_0:if(New == state_2) EncPlus++;
		             if(New == state_1) EncMinus++;
		       break;
	    case state_1:if(New == state_0) EncPlus++;
		             if(New == state_3) EncMinus++;
		       break;
	    case state_3:if(New == state_1) EncPlus++;
		             if(New == state_2) EncMinus++;
		       break;
        default:break;
	    }

		if(EncPlus == ENC_TIKS) //���� ������ ���� "������"
		{
		    if(EncData++ >= ENC_MAX) EncData = ENC_MAX;	//����������� ��������, ������, ����� �� ����� �� ������� ��������
			EncPlus = 0;
			ret = 1;
		}

		if(EncMinus == ENC_TIKS) //���� ������ ���� "������"
		{
		    if(EncData-- <= ENC_MIN) EncData = ENC_MIN;	//��������� ��������, ������ ����� �� ����� �� ������� ������� ��������
			EncMinus = 0;
			ret = 1;
		}
        EncState = New;	// ���������� ����� �������� ����������� ���������
	}
	return ret;
}
//#else
#ifndef ENC_LIMITS
inline void SetEncoder_Lim(u08 l_min, u08 l_max)
{
	ENC_MIN = l_min;
	ENC_MAX = l_max;
}
#endif
/*
u08 Encoder_Scan(u08 l_min, u08 l_max)		//������� ��������� ��������
{
    static u08 New, EncPlus, EncMinus;//���������� ������ �������� ��������, ������������� ���������� + � -
    static u08 EncState;
	uint8_t ret = 0;
 
    New = PinReg(&ENCODER_PORT) & (_BV(PIN_ENC_B) | _BV(PIN_ENC_A));// ��������� ��������� ��������� ��������
 
    if(New != EncState)//���� �������� ���������� �� ��������� � ��������
    {
        switch(EncState) //������� �������� �������� ��������
	    {
	    case state_2:if(New == state_3) EncPlus++;//� ����������� �� �������� �����������
		             if(New == state_0) EncMinus++;//��� ���������  
		       break;
	    case state_0:if(New == state_2) EncPlus++;
		             if(New == state_1) EncMinus++; 
		       break;
	    case state_1:if(New == state_0) EncPlus++;
		             if(New == state_3) EncMinus++; 
		       break;
	    case state_3:if(New == state_1) EncPlus++;
		             if(New == state_2) EncMinus++; 
		       break;
        default:break;
	    }
		
		if(EncPlus == ENC_TIKS) //���� ������ ���� "������"
		{
		    if(EncData++ >= l_max) EncData = l_max;//����������� ��������, ������, ����� �� ����� �� ������� ��������
			EncPlus = 0;
			ret = 1;
		}
		
		if(EncMinus == ENC_TIKS) //���� ������ ���� "������"
		{
		    if(EncData-- <= l_min) EncData = l_min;//��������� ��������, ������ ����� �� ����� �� ������� ������� ��������
			EncMinus = 0;
			ret = 1;
		}
        EncState = New;	// ���������� ����� �������� ����������� ���������
	}
	return ret;
}
*/
//#endif
