//Download by www.cctry.com
#include<winsock2.h>				//����ͷ�ļ�
#include<stdio.h>
#include<windows.h>
#pragma comment(lib,"WS2_32.lib")		//��ʽ�����׽��ֿ�
using namespace std;

int main()							//��������ʼ
{
	WSADATA data;						//����WSADATA�ṹ�����
	WORD w=MAKEWORD(2,0);					//����汾����
	WSAStartup(w,&data);					//��ʼ���׽��ֿ�

	SOCKET socketCli;						//���������׽��־��
	char recvBuf[10]={0};					//���յ���Ϣ����
	socketCli=socket(AF_INET,SOCK_STREAM,0);			//����TCP�׽���
	sockaddr_in addrCli;					//�����׽��ֵ�ַ�ṹ
	addrCli.sin_family=AF_INET;				//��ʼ����ַ�ṹ
	addrCli.sin_port=htons(75);
	addrCli.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");
	printf("�ͻ����Ѿ�����\r\n");				//�����ʾ��Ϣ

	connect(socketCli,(sockaddr*)&addrCli,sizeof(addrCli));
	recv(socketCli,recvBuf,sizeof(recvBuf),0);
	printf("%s\r\n",recvBuf);
	
	closesocket(socketCli);					//�ر��׽��־��
	WSACleanup();						//�ͷ��׽��ֿ�
	if(getchar())						//��������룬��رճ���
	{
		return 0;					//������������
	}
	else
	{
		Sleep(100);					//����˯��
	}
}
