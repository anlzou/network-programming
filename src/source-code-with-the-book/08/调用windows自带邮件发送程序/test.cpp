//Download by www.cctry.com
#include <stdio.h>								//�������ͷ�ļ�
#include <windows.h>

int main()											//������				
{
	int i=0;										//����ѭ������
	char ch;										//�����ַ������ڻ�ȡ�û�����
	printf("ȷ�ϴ��ʼ��շ�����!(Y/N)\n");			//��ʾ�û�
	scanf(&ch);										//����ָ��
	if(ch && 'Y')									//�ж�����ָ��
	{
		printf("�ʼ��շ��������ڴ򿪣����Ժ򡭡�\n");	//��ʾ�û�
		while(i<=10000000)							//ѭ����ģ����������
		{
			i+=1;													
		}
		ShellExecute(NULL,NULL,"mailto:lymlrl@163.com",
			NULL,NULL,SW_SHOW);								//���ú��������ʼ��շ�����
		printf("�ʼ��շ������Ѿ��򿪣���ʹ�ã�\n");
	}
	else
	{
		printf("ллʹ��!\n");  
	}
	return 0;
}
