//Download by www.cctry.com
#include <stdio.h>
#include <afxmt.h>

DWORD WINAPI myfun1(LPVOID lpParameter);	//�����̺߳���
DWORD WINAPI myfun2(LPVOID lpParameter);
CCriticalSection m_Sec;									//����ȫ�ֱ���m_Sec
int a=0;
												//����ȫ�ֱ���a
int main()
{	
	HANDLE h1,h2;											//�����߳̾��
	h1=::CreateThread(NULL,0,myfun1,NULL,0,NULL);			//�����߳�1
	printf("�߳�1��ʼ���У�\r\n");
	h2=::CreateThread(NULL,0,myfun2,NULL,0,NULL);			//�����߳�2
	printf("�߳�2��ʼ���У�\r\n");
	::CloseHandle(h1);										//�ر��߳̾������
	::CloseHandle(h2);
	::Sleep(10000);											//����˯��10��
	return 0;
}
DWORD WINAPI myfun1(LPVOID lpParameter) 				//�̺߳���1
{
	m_Sec.Lock();										//�����ٽ���
	a+=1;													//������1
	printf("%d\n",a);										//�������
	m_Sec.Unlock();								//���ٽ������н���
	return 0;
}
DWORD WINAPI myfun2(LPVOID lpParameter) 		//�̺߳���2
{
	m_Sec.Lock();								//�����ٽ���
	a+=1;											//������1
	printf("%d\n",a);								//�������
	m_Sec.Unlock();								//���ٽ������н���
	return 0;
}
