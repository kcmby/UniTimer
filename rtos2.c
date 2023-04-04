#include <avr/interrupt.h>
#include "rtos2.h"
#include "commons.h"

/******************************************************************************************
 * ���������� ������
 */
volatile static task TaskArray[MAX_TASKS];      // ������� �����
extern u08 arrayTail;                  			// "�����" �������
//volatile u08 tcount;							// ��������� ������� �������


/******************************************************************************************
 * ���������� ������ � ������
 */
#ifdef INTFUNC
void RTOS_SetTask (void (*taskFunc)(void), u32 taskDelay, u32 taskPeriod, void (*IFunc)(void))
{
   u08 i;
   
   //if(!taskFunc) return;
   for(i = 0; i < arrayTail; i++) {                   // ����� ������ � ������� ������
      if(TaskArray[i].pFunc == taskFunc) {            // ���� �����, �� ��������� ����������
         DISABLE_INTERRUPT;

         TaskArray[i].delay  = taskDelay;
         TaskArray[i].period = taskPeriod;
         TaskArray[i].run    = 0;
         TaskArray[i].pIFunc = IFunc;

         RESTORE_INTERRUPT;
         return;                                      // �������, �������
      }
   }

   if (arrayTail < MAX_TASKS) {                       // ���� ����� ������ � ������ ���
      DISABLE_INTERRUPT;							  // � ���� �����,�� ���������
      
      TaskArray[arrayTail].pFunc  = taskFunc;
      TaskArray[arrayTail].delay  = taskDelay;
      TaskArray[arrayTail].period = taskPeriod;
      TaskArray[arrayTail].run    = 0;
      TaskArray[i].pIFunc = IFunc;

      arrayTail++;                                    // ����������� "�����"
      RESTORE_INTERRUPT;
   }
}
#else
void RTOS_SetTask (void (*taskFunc)(void), u32 taskDelay, u32 taskPeriod)
{
   u08 i;

   //if(!taskFunc) return;
   for(i = 0; i < arrayTail; i++) {                   // ����� ������ � ������� ������
      if(TaskArray[i].pFunc == taskFunc) {            // ���� �����, �� ��������� ����������
         DISABLE_INTERRUPT;

         TaskArray[i].delay  = taskDelay;
         TaskArray[i].period = taskPeriod;
         TaskArray[i].run    = 0;

         RESTORE_INTERRUPT;
         return;                                      // �������, �������
      }
   }

   if (arrayTail < MAX_TASKS) {                       // ���� ����� ������ � ������ ���
      DISABLE_INTERRUPT;							  // � ���� �����,�� ���������

      TaskArray[arrayTail].pFunc  = taskFunc;
      TaskArray[arrayTail].delay  = taskDelay;
      TaskArray[arrayTail].period = taskPeriod;
      TaskArray[arrayTail].run    = 0;

      arrayTail++;                                    // ����������� "�����"
      RESTORE_INTERRUPT;
   }
}
#endif

/******************************************************************************************
 * �������� ������ �� ������
 */
void RTOS_DeleteTask (void (*taskFunc)(void))
{
	u08 i;
   
	for (i=0; i<arrayTail; i++) {							// �������� �� ������ �����
		if(TaskArray[i].pFunc == taskFunc) {				// ���� ������ � ������ �������
			DISABLE_INTERRUPT;
			if(i != (arrayTail - 1)) {						// ��������� ��������� ������
				TaskArray[i] = TaskArray[arrayTail - 1];	// �� ����� ���������
			}
			arrayTail--;									// ��������� ��������� "������"
			RESTORE_INTERRUPT;
			return;
		}
	}
}

/******************************************************************************************
 * ��������� ����, ���������� � main
 */

void RTOS_DispatchTask()
{
	u08 i;
	void (*function) (void);

	for (i=0; i<arrayTail; i++) {							// �������� �� ������ �����
		if (TaskArray[i].run == 1) {						// ���� ���� �� ���������� �������,
															// ���������� ������, �.�. ��
			function = TaskArray[i].pFunc;					// ����� ���������� �����
															// ���������� ������
			if(TaskArray[i].period == 0) {
															// ���� ������ ����� 0
				RTOS_DeleteTask(TaskArray[i].pFunc);		// ������� ������ �� ������,
			}
			else {
				TaskArray[i].run = 0;						// ����� ������� ���� �������
				if(!TaskArray[i].delay) {					// ���� ������ �� �������� ��������
															// ������ ��
					TaskArray[i].delay = TaskArray[i].period-1; 
				}											// ������ ��� ���� ����� ������� �����
			}
			(*function)();	// ��������� ������
		}
	}
}

/******************************************************************************************
 * ������ ����� ������� ��������� �������
 */
/*
u32 RTOS_ReadDelay (void (*function)(void))
{
	u08 i, nf;
	u32 delay;

	nf = 0;
	delay = 0;
	for (i=0; i<arrayTail; i++) {							// �������� �� ������ �����
		if(TaskArray[i].pFunc == function) {				// ���� ������ � ������ �������
			nf = 1;
			DISABLE_INTERRUPT;
			delay = TaskArray[i].delay;						// ���������� � ���������� ���������
			RESTORE_INTERRUPT;
//TLed_on();
			break;
		}
	}
	if (nf)
		function = NULL;								// ���� ������ �� �������

	return delay;
}
*/

/******************************************************************************************
 * ��������� ������ ���� (���������� ����������� �������)
 */
ISR(RTOS_ISR) 
{
	u08 i;
   
	for (i=0; i<arrayTail; i++) {		// �������� �� ������ �����
		if  (TaskArray[i].delay) {		// ���� ����� �� ���������� �� �������
			TaskArray[i].delay--;		// ��������� �����
		}
		else {
			TaskArray[i].run = 1;		// ����� ������� ���� �������,
#ifdef INTFUNC
			if(TaskArray[i].pIFunc) {
				(*TaskArray[i].pIFunc)();
//				Pow_Off();
			}
#endif
		}
	}
}




