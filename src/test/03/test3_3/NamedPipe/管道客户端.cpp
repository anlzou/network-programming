/***
 * @Date        : 2020-05-23 18:55:57
 * @LastEditors : anlzou
 * @Github      : https://github.com/anlzou
 * @LastEditTime: 2020-05-25 08:11:16
 * @FilePath    : \socket\src\test\03\test3_3\NamedPipe\�ܵ��ͻ���.cpp
 * @Describe    :
 */
#include <iostream>
#include <windows.h>

using namespace std;

int main() {
    HANDLE hpip;
    OVERLAPPED ovi = {0};
    char buf[] = "�����ܵ����Գ���";
    DWORD readbuf;
    cout << "�������������ܵ�" << endl;

    if (WaitNamedPipe("\\\\.\\pipe\\pipename", NMPWAIT_WAIT_FOREVER)) {
        hpip = CreateFile("\\\\.\\pipe\\pipename", GENERIC_READ | GENERIC_WRITE,
                          0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hpip == INVALID_HANDLE_VALUE) {
            cout << "�������ܵ�ʧ��" << endl;
        } else {
            if (WriteFile(hpip, buf, sizeof(buf), &readbuf, NULL)) {
                cout << "����д��ɹ�" << endl;
            } else {
                cout << "����д��ʧ��" << endl;
            }
        }
    } else {
        cout << "��������ܵ�ʧ��" << endl;
    }
    return 0;
}