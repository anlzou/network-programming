//Download by www.cctry.com
#include <afxmt.h>
#include <stdio.h>

DWORD WINAPI myfun1(LPVOID lpParameter);//�����̺߳���
DWORD WINAPI myfun2(LPVOID lpParameter);
CMutex hmutex(NULL,FALSE,NULL);				//����ȫ�ֻ������
int a=0;										//����ȫ�ֱ���a

int main()
{	
	HANDLE h1,h2;									//�����߳̾��
	h1=::CreateThread(NULL,0,myfun1,NULL,0,NULL);	//�����߳�1
	printf("ʹ��CMutex ��ʵ���߳�ͬ��\r\n");
	printf("�߳�1��ʼ���У�\r\n");
	h2=::CreateThread(NULL,0,myfun2,NULL,0,NULL);	//�����߳�2
	printf("�߳�2��ʼ���У�\r\n");
	::CloseHandle(h1);								//�ر��߳̾������
	::CloseHandle(h2);
	::Sleep(10000);									//����˯��10��
	return 0;
}

DWORD WINAPI myfun1(LPVOID lpParameter) 		//�̺߳���1
{
	while(1)
	{
		hmutex.Lock(INFINITE);						//�����������
		if(a<10000)
		{
			a+=1;											//�����Լ�
			::Sleep(1000);									//�߳�˯��1��
			printf("�߳�1��%d\r\n",a);
			hmutex.Unlock();							//�ͷŻ������
		}
		else
		{
			hmutex.Unlock();								//�ͷŻ������
			break;										//����ѭ��
		}
	}
    return 0;	
}
DWORD WINAPI myfun2(LPVOID lpParameter) 		//�̺߳���2
{
	while(1)
	{
		hmutex.Lock(INFINITE);						//�����������
		if(a<10000)
		{
			a+=1;
			::Sleep(1000);
			printf("�߳�2��%d\r\n",a);					//�������
			hmutex.Unlock();							//�ͷŻ������
		}
		else
		{	
			hmutex.Unlock();							//�ͷŻ������
			break;										//����ѭ��
		}
	}
    return 0;									//�߳������˳�
}
