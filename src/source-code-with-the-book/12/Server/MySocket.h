//Download by www.cctry.com
#if !defined(AFX_MYSOCKET_H__0F4585A5_54CB_4147_BA74_70C139396533__INCLUDED_)
#define AFX_MYSOCKET_H__0F4585A5_54CB_4147_BA74_70C139396533__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MySocket.h : header file
//

#define SOCKET_EVENT WM_USER + 1001

enum {ACCEPT = 0,SEND = 1,RETR = 2,CLOSE = 3};

/////////////////////////////////////////////////////////////////////////////
// CMySocket command target

class CMySocket : public CSocket
{
// Attributes
public:
	//�����������
	CWnd	*pWnd;
	//������Ϣ��������
	ULONG	m_Total;
	//�����û���
	CString m_Player;

// Operations
public:
	CMySocket();
	virtual ~CMySocket();
	
	//��Socket����������--socket�б����˴��ڵ�ָ��
	void AttachCWnd(CWnd *pWnd);

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMySocket)
	public:
	virtual void OnAccept(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CMySocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSOCKET_H__0F4585A5_54CB_4147_BA74_70C139396533__INCLUDED_)
