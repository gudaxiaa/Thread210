#include <stdio.h>
#include <Windows.h>
#include <Process.h>
/*��һ�׶� �Ƚ����̺߳����߳̽���ʱ��
unsigned WINAPI threadFun(void* argi);

int main(void)
{
	printf("main begin\n");
	HANDLE tThread;
	int iParem = 10;
	unsigned int dwID;
	tThread = (HANDLE) _beginthreadex(NULL, 0, threadFun, (void*)&iParem, 0, &dwID);

	printf("main end\n");

	Sleep(20000);
	system("pause");
	return 0;
}

unsigned WINAPI threadFun(void* argi)
{
	int cnt = *((int*)argi);
	for (int i = 0; i < cnt; i++)
	{
		Sleep(1000);
		puts("thread runs now");
	}
	return 0;
}
*/

#if 0
DWORD dr;
unsigned WINAPI  threadFun(void* argi);

int main()
{
	printf("main begin:\n");

	int iParam = 10;
	unsigned int dwID;
	HANDLE tThread = (HANDLE)_beginthreadex(NULL,0,threadFun,(void*)&iParam,0,&dwID);
	if (!tThread )
	{
		puts("tThread erro\n!");
		return -1;
	}
	if ((dr = WaitForSingleObject(tThread, INFINITE)) == WAIT_FAILED)
	{
		puts("threadFun erro!\n");
		return -1;
	}
	printf("main end\n");

	system("pause");
	return 0;
}

unsigned WINAPI  threadFun(void* argi) 
{
	int cnt = *((int*)argi);
	for(int i=0;i<cnt;i++)
	{
		Sleep(1000);
		puts("thread runs now");
	}
	return 0;
}
#endif

#define  thread_num   50

DWORD dr;
long long num=0;
HANDLE hMutex;

unsigned WINAPI  threadInc(void* argi);
unsigned WINAPI  threadDes(void* argi);


int main(void)
{
	printf("main start:\n");
	HANDLE tThread[thread_num];
	//����������
	hMutex = CreateMutex(NULL,FALSE,NULL);

	for (int i = 0; i < thread_num; i++)
	{
		if (i % 2)
		{
			tThread[i] = (HANDLE)_beginthreadex(NULL, 0, threadInc, NULL, 0, NULL);
		}
		else
		{
			tThread[i] = (HANDLE)_beginthreadex(NULL, 0, threadDes, NULL, 0, NULL);
		}
	}
	if ((dr = WaitForMultipleObjects(thread_num, tThread, TRUE, INFINITE)) == WAIT_FAILED)
	{
		puts("wait for erro\n");
		return -1;
	}

	//�ͷŻ�����(���)
	CloseHandle(hMutex);

	printf("num��ֵ��:%lld\n", num);

	printf("main end\n");

	system("pause");
	return 0;
	
}
	unsigned WINAPI  threadInc(void* argi)
	{
		WaitForSingleObject(hMutex, INFINITE);
		for (int i = 0; i < 500000; i++)
		{
			num += 1;
		}
		ReleaseMutex(hMutex);
		return 0;
	}
	
	unsigned WINAPI  threadDes(void* argi)
	{
		//�ȴ��ں˶���(������)������Ϣ
		WaitForSingleObject(hMutex, INFINITE);
		// �ٽ��� ��һ�δ��� ����һ������
		for (int i = 0; i < 500000; i++)
		{
			num -= 1;
		}
		ReleaseMutex(hMutex);
		return 0;
	}

