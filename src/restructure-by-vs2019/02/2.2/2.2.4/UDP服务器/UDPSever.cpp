//Download by www.cctry.com
#include<winsock2.h>							//����ͷ�ļ�
#include<stdio.h>
#include<windows.h>
#pragma comment(lib,"WS2_32.lib")				//�����׽��ֿ�

int main()
{
	WSADATA data;									//����ṹ�����
	WORD w=MAKEWORD(2,0);							//�����׽��ְ汾
	char sztext[]="��ӭ��\r\n";						//���延ӭ��Ϣ
	::WSAStartup(w,&data);							//��ʼ���׽��ֿ�
	
	SOCKET socketSer;										//�����׽��־��
	socketSer=::socket(AF_INET, SOCK_DGRAM,0);				//����UDP�׽���
	sockaddr_in addrSer,addrCli;							//�׽��ֵ�ַ�ṹ����
	int len=sizeof(addrCli);							//��ַ�ṹ������С
	char buff[10]={0};								//�������ݻ�����
	addrSer.sin_family=AF_INET;
	addrSer.sin_port=htons(75);
	addrSer.sin_addr.S_un.S_addr=INADDR_ANY;
    ::bind(socketSer,(sockaddr*)&addrSer,sizeof(addrSer));		//���׽���
	printf("UDP�������Ѿ�����\r\n");				//��ʾ��ʾ��Ϣ

	while(1)
	{
		if(::recvfrom(socketSer,buff,10,0,(sockaddr*)&addrCli,&len)!=0)		//���տͻ�����Ϣ
		{
			printf("%s�Ѿ�������\r\n",inet_ntoa(addrCli.sin_addr));
			printf("%s\r\n",buff);
			::sendto(socketSer,sztext,sizeof(sztext),0,(sockaddr*)&addrCli,len);//�������ݵ��ͻ���
			break;
		} 
	}
	::closesocket(socketSer);							//�ر��׽��ֶ���
	::WSACleanup();								//�ͷ��׽��ֿ�

	if(getchar())							//��������룬��رճ���
	{
	   return 0;									//������������
	}
	else
	{
	   ::Sleep(100);									//Ӧ�ó���˯��
	}
}
