//Download by www.cctry.com
#include<winsock2.h>					//����ͷ�ļ�
#include<stdio.h>
#include<windows.h>
#pragma comment(lib,"WS2_32.lib")			//�����׽��ֿ�
using namespace std;

int main()
{
	WSADATA data;					//����ṹ�����
	WORD w=MAKEWORD(2,0);				//��ʼ���׽��ְ汾��
	WSAStartup(w,&data);				//��ʼ���׽��ֿ�
	
	SOCKET socketCli;					//�����׽���
	socketCli=socket(AF_INET,SOCK_DGRAM,0);		//����UDP�׽���
	sockaddr_in addrSer,addrCli;				//�����׽��ֵ�ַ
	int len=sizeof(addrCli);
	char buff[10]={0};
	addrSer.sin_family=AF_INET;
	addrSer.sin_port=htons(75);
	addrSer.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");		
	printf("UDP�ͻ����Ѿ�����\r\n");
	char sendBuf[]="���\r\n";

	if(sendto(socketCli,sendBuf,sizeof(sendBuf),0,(sockaddr*)&addrSer,len)!=0)	//������Ϣ
	{
		recvfrom(socketCli,buff,10,0,(sockaddr*)&addrCli,&len);		//������Ϣ
		printf("������˵��%s\r\n",buff);
		closesocket(socketCli);					//�ر��׽���
		WSACleanup();						//�ͷ��׽��ֿ�
	}

	if(getchar())							//��������룬��رճ���
	{
		return 0;						//������������
	}
	else
	{
		Sleep(100);						//Ӧ�ó���˯��
	}
}
