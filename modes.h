/*
 * modes.h
 *
 *  Created on: 15 ����. 2019 �.
 *      Author: KCM
 */

#ifndef MODES_H_
#define MODES_H_

	#define MAX_SUBMODES		5  // ���������� ����������

	// ������
	#define MODE_TEST		0b000		// ����� ������������ (��� ���������)
	#define MODE_WELD		0b001		// ����� ������
	#define MODE_LAMP		0b010		// ����� ��������
	#define MODE_SETUP		0b011		// ����� ���������
	// ���������
	#define SM_WELD_1		0b001		// �������� ������ � ��������� ���������
	#define SM_WELD_2		0b010		// �������� ������ � ������� ���������
	#define SM_WELD_M		0b011		// �������� ������ ������
	#define SM_LAMP_S		0b001		// �������� �������� � �������� ���������������
	#define SM_LAMP_L		0b010		// �������� �������� � ���������� ���������������


#endif /* MODES_H_ */
