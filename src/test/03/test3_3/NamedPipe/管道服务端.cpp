#include<iostream>
#include<windows.h>

using namespace std;

int mainxx(){
	HANDLE hpip;
	OVERLAPPED ovi = {0};
	char buf[200];
	DWORD readbuf;
	hpip = CreateNamedPipe("\\\\.\\pip\\pipename",PIPE_ACCESS_DUPLEX,PIPE_TYPE_BYTE,PIPE_UNLIMITED_INSTANCES,1024,1024,0,NULL);
	cout<<"create sucess"<<endl;

	cout<<"���ڵȴ��ͻ��˵����ӡ�����"<<endl;
	if(ConnectNamedPipe(hpip,&ovi)){
		cout<<"�ͻ������ӳɹ�!!!!!"<<endl;
		cout<<"���ڶ�ȡ����"<<endl;
		if(ReadFile(hpip,buf,200,&readbuf,NULL)){
			cout<<"��ȡ���ݳɹ�����������<<endl";
			cout<<"����Ϊ��"<<buf<<endl;
		}else{
			cout<<"��ȡ����ʧ�ܣ���������������";
		}
	}
	return 0;
}