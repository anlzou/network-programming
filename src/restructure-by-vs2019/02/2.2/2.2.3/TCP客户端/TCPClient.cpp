//Download by www.cctry.com
#include<winsock2.h>				//����ͷ�ļ�
#include<stdio.h>
#include<windows.h>
#pragma comment(lib,"WS2_32.lib")		//��ʽ�����׽��ֿ�

int main()							//��������ʼ
{
	WSADATA data;						//����WSADATA�ṹ�����
	WORD w=MAKEWORD(2,0);					//����汾����
	::WSAStartup(w,&data);					//��ʼ���׽��ֿ�
	SOCKET s;						//���������׽��־��
	char sztext[10]={0};
	s=::socket(AF_INET,SOCK_STREAM,0);			//����TCP�׽���
	sockaddr_in addr;					//�����׽��ֵ�ַ�ṹ
	addr.sin_family=AF_INET;				//��ʼ����ַ�ṹ
	addr.sin_port=htons(75);
	addr.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");
	printf("�ͻ����Ѿ�����\r\n");				//�����ʾ��Ϣ
	::connect(s,(sockaddr*)&addr,sizeof(addr));
	::recv(s,sztext,sizeof(sztext),0);
	printf("%s\r\n",sztext);
	::closesocket(s);					//�ر��׽��־��
	::WSACleanup();						//�ͷ��׽��ֿ�
	if(getchar())						//��������룬��رճ���
	{
		return 0;					//������������
	}
	else
	{
		::Sleep(100);					//����˯��
	}
}
