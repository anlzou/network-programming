//Download by www.cctry.com
#include<winsock2.h>					//����ͷ�ļ�
#include<stdio.h>
#include<windows.h>
#pragma comment(lib,"WS2_32.lib")			//�����׽��ֿ�

int main()
{
	WSADATA data;					//����ṹ�����
	WORD w=MAKEWORD(2,0);				//��ʼ���׽��ְ汾��
	::WSAStartup(w,&data);				//��ʼ���׽��ֿ�
	SOCKET s;					//�����׽���
	s=::socket(AF_INET,SOCK_DGRAM,0);		//����UDP�׽���
	sockaddr_in addr,addr2;				//�����׽��ֵ�ַ
	int n=sizeof(addr2);
	char buff[10]={0};
	addr.sin_family=AF_INET;
	addr.sin_port=htons(75);
	addr.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");		
	printf("UDP�ͻ����Ѿ�����\r\n");
	char sztext[]="���\r\n";
	if(::sendto(s,sztext,sizeof(sztext),0,(sockaddr*)&addr,n)!=0)	//������Ϣ
	{
		::recvfrom(s,buff,10,0,(sockaddr*)&addr2,&n);		//������Ϣ
		printf("������˵��%s\r\n",buff);
		::closesocket(s);					//�ر��׽���
		::WSACleanup();						//�ͷ��׽��ֿ�
	} 
	if(getchar())							//��������룬��رճ���
	{
		return 0;						//������������
	}
	else
	{
		::Sleep(100);						//Ӧ�ó���˯��
	}
}
