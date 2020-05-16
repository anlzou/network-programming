//Download by www.cctry.com
// ServerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Server.h"
#include "ServerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CServerDlg dialog

CServerDlg::CServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CServerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CServerDlg)
	m_Ctx = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CServerDlg)
	DDX_Control(pDX, IDC_LISTUSER, m_List);
	DDX_Text(pDX, IDC_CTX, m_Ctx);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CServerDlg, CDialog)
	//{{AFX_MSG_MAP(CServerDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTNRUN, OnBtnrun)
	//}}AFX_MSG_MAP
	ON_MESSAGE(SOCKET_EVENT,OnSocket)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CServerDlg message handlers

BOOL CServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	//�޸����Ի���ı���
	m_brBack.DeleteObject();
	m_bmBack.DeleteObject();
	m_bmBack.LoadBitmap(IDB_SBACK);
	m_brBack.CreatePatternBrush(&m_bmBack);

	//��ʼ���б�ؼ����б�ͷ
	m_List.InsertColumn(0,"�û���",LVCFMT_LEFT,120);		//��һ�б�ͷ
	m_List.InsertColumn(1,"IP",LVCFMT_LEFT,100);		//�ڶ��б�ͷ
	m_List.InsertColumn(2,"��Ϣ��",LVCFMT_LEFT,130);		//�����б�ͷ
	m_List.InsertColumn(3,"ͷ��",LVCFMT_LEFT,60);		//�����б�ͷ

	m_bnRun.AutoLoad(IDC_BTNRUN,this);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CServerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CServerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

HBRUSH CServerDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if(nCtlColor == CTLCOLOR_DLG)
	{
		return m_brBack;
	}
	// TODO: Return a different brush if the default is not desired
	return hbr;
}
//wParam��Ӧ����Ӧ�ͻ���ͨ�ŵ�SOCKETָ�룬Ҳ�п�������SOCKET��lParam��Ӧ�¼�����
void CServerDlg::OnSocket(WPARAM wParam, LPARAM lParam)
{
	CMySocket	*sock = (CMySocket*)wParam;
	CMySocket	*c;
	//SOCKADDR_IN��һ���ṹ����ʾIP��ַ���˿ںŵ�
	SOCKADDR_IN sockAddr;
	int			nSize = sizeof(sockAddr);
	BOOL		res;
	
	switch(lParam)
	{
	//�µ�������Ϣ
	case ACCEPT:
		//����һ���µ�SOCKET
		c = new CMySocket;
		//�����Ӱ󶨵�������
		c->AttachCWnd(this);
		
		//��SOCKETָ���´�����SOCKET��ͻ���ͨ��
		res = sock->Accept(*c,(SOCKADDR *)&sockAddr,&nSize);
		if(res == FALSE)
		{
			MessageBox("Accept Error!");
		}
		break;

	//���ӹر���Ϣ
	case CLOSE:
		//�ر�����
		ClosePlayer(sock);
		break;
		
	//�յ�������Ϣ
	case RETR:
		ParserPkt(sock);									//������Ϣ
		break;
	}
}

//�����û��˳��¼�
void CServerDlg::ClosePlayer(CMySocket *from)
{
	int		i , msg_len;
	char	out_msg[200];

	//returns the number of bytes stored in buffer, 
	//not counting the terminating null character.
	msg_len = sprintf(out_msg," %s �˳�������\r\n",from->m_Player) + 1;

	//�����˳�������û���
	char	nbuf[100];

	m_csList.Lock();

	//ɾ���˳��û�����Ϣ
	for(i = 0; i < m_List.GetItemCount(); i++)
	{
		//GetItemData() - This value is the lParam member of the LVITEM structure
		//Retrieves the 32-bit application-specific value
		//associated with the item specified by nItem. 
		if(m_List.GetItemData(i) == (DWORD)from)
		{
			//ɾ���׽���
			delete from;

			//�û��˳�������
			nbuf[0] = 0x41;
			m_List.GetItemText(i,0,nbuf + 1, 100);	 
			m_List.DeleteItem(i);					//ɾ���˳��û����б��е���Ϣ
			break;
		}
	}

	//���û��˳���Ϣ���͸������û�
	for(i = 0; i < m_List.GetItemCount(); i++)
	{
		CMySocket *s;
		
		s = (CMySocket*)m_List.GetItemData(i);

		s->Send(nbuf,100);							//������Ϣ
	}

	m_csList.Unlock();
	
	Append(out_msg);
}

//׷����Ϣ��
void CServerDlg::Append(char *msg)
{
	//��ȡ��Ϣ�������е���Ϣ
	m_Ctx += msg;
	UpdateData(FALSE);
}

//�����յ�������
void CServerDlg::ParserPkt(CMySocket *from)
{
	char SendBuff[4096];		//���ͻ���
	char ShowBuff[4096];		//��ʾ����
	char nbuf[100];				//��ʱ������

	//��ʼ����������
	memset(SendBuff,0,4096);
	memset(ShowBuff,0,4096);
	memset(nbuf,0,100);

	int len;					//��¼���ͳ���
	int item;					//�б����
	char pic[2];				//ͼ�����		
	CMySocket *s1;				//����һ����Ϣ��Socket		
	CMySocket *s;				//�����û�������Ϣ��Socket


	//��ȡ����
	len = from->Receive(SendBuff,4096);

	//0---���ӹرգ�-1---���ʹ���
	if(len < 1)	
	{
		AfxMessageBox("��Ϣ����--������ϢError");
		return;
	}

	//0x11---�����������û�����������
	if(SendBuff[0] == 0x11)	
	{
		CString ipaddr;				//IP�ַ���	
		UINT port;					//�˿ں�

		//ȡ������׽������ӵĶԷ���IP��ַ���˿ں�
		from->GetPeerName(ipaddr,port);
		//��SOCKETͨ�ŵ��û��ĳ�ν
		from->m_Player = SendBuff + 2;//���Ƶļ�¼����Ϊ��ʱֹͣ--great!

		//ͷ����Ŵ���
		pic[0] = SendBuff[1] + 0x30;	//�ҵ��ַ���1����λ��--great! '1'��asciiΪ0x31
		pic[1] = '\0';

		//���б��в���һ��
		m_csList.Lock();

		//�б��в���һ�У����ز�����к�
		item = m_List.InsertItem(0,SendBuff+2);
		//�����SOCKETָ�뵽���еĸ���������
		m_List.SetItemData(item,(DWORD)from);
		//���õ�2�У�IP��ַ��
		m_List.SetItemText(item,1,ipaddr);
		//���õ�3�У��û�ͷ��
		m_List.SetItemText(item,3,pic);

		m_csList.Unlock();

		//s1�б����¼����û���socket
		s1 = (CMySocket*)m_List.GetItemData(item);

		//֪ͨ�����û������û�����
		m_csList.Lock();

		for(item = 0; item < m_List.GetItemCount(); item++)
		{
			s = (CMySocket*)m_List.GetItemData(item);
			len = sprintf(ShowBuff ," %s ��������\r\n",from->m_Player);
			
			Sleep(200);

			//����ͼ��ź��û���
			if( s != from )	
			{
				//����ָ��Ϊ0x11������
				s->Send(SendBuff,len+1);

				//�����û������ѵ�¼�û���Ϣ
			
				//��ȡͼ���
				m_List.GetItemText(item,3,&pic[0],2);
				//0x31---�ѵ�¼�û���Ϣ��
				nbuf[0] = 0x31;
				nbuf[1] = pic[0];
				//��ȡ�û���
				m_List.GetItemText(item,0,nbuf+2,100);
				len = strlen(nbuf);
				s1->Send(nbuf,len+1);		//�����û���+ͷ���
			}
			else
			{
				//���û���Ϣ��1
				char tot[10];

				sprintf(tot,"%u",from->m_Total);
				//���õ�2�У���Ϣ����
				m_List.SetItemText(item,2,tot);
			}
		}

		m_csList.Unlock();
	}
	//˽����Ϣ---��ͬ����Ϣ��ʽ
	else if(SendBuff[0] == 0x51)	//�����û���ת����
	{
		char pName[100],bName[100];
		memset(pName,0,100);
		memset(bName,0,100);

		//����˽�ĵ��û�������
		strcpy(pName,SendBuff +1);
		for(item = 0; item < m_List.GetItemCount(); item++)
		{
			m_List.GetItemText(item,0,bName,100);

			if(0 == strcmp(pName,bName))
			{
				s = (CMySocket*)m_List.GetItemData(item);
				//ͬ��ֱ�ӷ������ı�
			    s->Send(SendBuff + 99 ,len);
			}
		}
	}
	//������Ϣ
	else	//�������û�ת����Ϣ	
	{
		m_csList.Lock();

		for(item = 0; item < m_List.GetItemCount(); item++)
		{
			s = (CMySocket*)m_List.GetItemData(item);
			s->Send(SendBuff,len);

			if(s == from)
			{
				char tot[10];
				sprintf(tot,"%u",from->m_Total);
				m_List.SetItemText(item,2,tot);				//���õ�2�У���Ϣ����
			}
		}
		memcpy(ShowBuff,SendBuff+1,4096);

		m_csList.Unlock();
	}

	//����������������Ϣ��д������2�ࣺ�û����롢˽����Ϣ������¼��������Ϣ��
	Append(ShowBuff);
}

void CServerDlg::OnBtnrun() 
{
	// TODO: Add your control notification handler code here

	//socket
	m_socket.AttachCWnd(this);
	BOOL isTrue = m_socket.Create(0x8123,SOCK_STREAM);
	if(isTrue)
	{
		m_socket.Listen();
		AfxMessageBox("�����ɹ���");
		GetDlgItem(IDC_BTNRUN)->EnableWindow(FALSE);
		return;
	}
	AfxMessageBox("������˼�����˵�����...");
}
