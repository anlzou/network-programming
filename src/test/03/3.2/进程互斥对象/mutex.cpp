//Download by www.cctry.com
#include<windows.h>								//����ͷ�ļ�
#include<stdio.h>

int main()												//������
{
	HANDLE hmutex;									//���廥�������
	hmutex=::CreateMutex(NULL,true,"VC������");	//����������󲢷�������
	if(hmutex)										//�жϴ�����������Ƿ�ɹ�
	{
		if(ERROR_ALREADY_EXISTS==GetLastError())		//��ȡ����
		{
			printf("ֻ����һ��ʵ���������У�\r\n");		//��ӡ�����Ϣ
		}
		else
		{
			printf("ʵ���������гɹ���\r\n");
		}
	}
	::ReleaseMutex(hmutex);						//�ͷŻ��������
	::Sleep(100000);								//ʹ����˯��100��
	return 0;										//������������
}
