#include "tinyOS.h"

int task1Flag;									//Task1 flag
int task2Flag;									//Task2 flag
int task3Flag;									//Task3 flag
int task4Flag;									//Task4 flag

tTask tTask1;									//Task1 structure
tTask tTask2;									//Task2 structure
tTask tTask3;									//Task3 structure
tTask tTask4;									//Task4 structure

tTaskStack task1Env[1024];						//Task1 stack
tTaskStack task2Env[1024];						//Task2 stack
tTaskStack task3Env[1024];						//Task3 stack
tTaskStack task4Env[1024];						//Task4 stack

tEventControlBlock eventWaitNormal;				//Normal ECB

tSem sem1, sem2;

void task1DestroyFunc(void *param)				//Task1 clean function
{
	task1Flag=0;
}

void task1Entry(void *param)					//Task1 function
{
	tSetSysTickPeriod(10);						//Timing cycle is 10ms
	tSemInit(&sem1, 0, 10);
	tSemWait(&sem1, 0);
	for(;;)
	{			
		task1Flag=1;
		tTaskDelay(10);
		task1Flag=0;
		tTaskDelay(10);
	}
}

void task2Entry(void *param)					//Task2 function
{
	int destroyed=0;
	tSemInfo info;
	for(;;)
	{	
		task2Flag=1;
		tTaskDelay(10);
		task2Flag=0;
		tTaskDelay(10);
		if(destroyed==0)
		{
			tSemGetInfo(&sem1, &info);
			tSemDestroy(&sem1);
			destroyed=1;
		}
	}
}

void task3Entry(void *param)					//Task3 function
{
	tSemInit(&sem2, 0, 0);
	for(;;)
	{		
		tSemWait(&sem2, 100);
		task3Flag=1;
		tTaskDelay(10);
		task3Flag=0;
		tTaskDelay(10);
	}
}

void task4Entry(void *param)					//Task4 function
{
	for(;;)
	{	
		task4Flag=1;
		tTaskDelay(10);
		task4Flag=0;
		tTaskDelay(10);
	}
}

void tAppInit(void)							//Application initial function
{
	tTaskInit(&tTask1, task1Entry, (void *)0x11111111, 0, &task1Env[1024]);  //Task1 initiate
	tTaskInit(&tTask2, task2Entry, (void *)0x22222222, 1, &task2Env[1024]);  //Task2 initiate
	tTaskInit(&tTask3, task3Entry, (void *)0x33333333, 1, &task3Env[1024]);  //Task3 initiate
	tTaskInit(&tTask4, task4Entry, (void *)0x44444444, 1, &task4Env[1024]);  //Task4 initiate
}
