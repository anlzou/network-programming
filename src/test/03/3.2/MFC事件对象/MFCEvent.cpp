//Download by www.cctry.com
#include <afxmt.h>
#include <stdio.h>

DWORD WINAPI myfun1(LPVOID lpParameter);//�����̺߳���
DWORD WINAPI myfun2(LPVOID lpParameter);
CEvent event(false,false,NULL,NULL);			//���¼�������Ϊȫ�ֱ���
int a=0;										//����ȫ�ֱ���a

int main()
{	
	HANDLE h1,h2;									//�����߳̾��
	event.SetEvent();
	h1=::CreateThread(NULL,0,myfun1,NULL,0,NULL);	//�����߳�1
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
		::WaitForSingleObject(event.m_hObject,INFINITE);	//�����¼�����
		//event.ResetEvent();							//�����¼�����Ϊ���ź�״̬
		if(a<10000)
		{
			a+=1;											//�����Լ�
			::Sleep(1000);									//�߳�˯��1��
			printf("�߳�1��%d\r\n",a);					//�������
			event.SetEvent();							//�����¼�����Ϊ���ź�״̬
		}
		else
		{
			event.SetEvent();								//�����¼�����Ϊ���ź�״̬
			break;										//����ѭ��
		}
	}
    return 0;									//�߳�
}
DWORD WINAPI myfun2(LPVOID lpParameter) 		//�̺߳���2
{
	while(1)
	{
		::WaitForSingleObject(event.m_hObject,INFINITE);	//�����¼�����
		//event.ResetEvent();							//�����¼�����Ϊ���ź�״̬
		if(a<10000)
		{
			a+=1;
			::Sleep(1000);
			printf("�߳�2��%d\r\n",a);					//�������
			event.SetEvent();
		}
		else
		{
			event.SetEvent();							//�����¼�����Ϊ���ź�״̬
			break;										//����ѭ��
		}
	}
    return 0;									//�߳������˳�
}
