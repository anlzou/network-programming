#include<iostream>
#include<windows.h>

using namespace std;

int main(){
	HANDLE hpip;
	OVERLAPPED ovi = {0};
	char buf[] = "�����ܵ����Գ���";
	DWORD readbuf;
	cout<<"�������������ܵ�"<<endl;

	if(WaitNamedPipe("\\\\.\\pipe\\pipename",NMPWAIT_WAIT_FOREVER)){
		hpip = CreateFile("\\\\.\\pipe\\pipename",GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
		if(hpip == INVALID_HANDLE_VALUE){
			cout<<"�������ܵ�ʧ��"<<endl;
		}else{
			if(WriteFile(hpip,buf,sizeof(buf),&readbuf,NULL)){
				cout<<"����д��ɹ�"<<endl;
			}else{
				cout<<"����д��ʧ��"<<endl;
			}
		}
	}else{
		cout<<"��������ܵ�ʧ��"<<endl;
	}
	return 0;
}