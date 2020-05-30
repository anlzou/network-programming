//Download by www.cctry.com
// FTP_clientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FTP_client.h"
#include "FTP_clientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFTP_clientDlg dialog

CFTP_clientDlg::CFTP_clientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFTP_clientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFTP_clientDlg)
	m_host = _T("");
	m_password = _T("");
	m_username = _T("");
	m_port = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFTP_clientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFTP_clientDlg)
	DDX_Control(pDX, IDC_LISTFILE, m_listfile);
	DDX_Control(pDX, IDC_LISTINFO, m_listinfo);
	DDX_Text(pDX, IDC_HOST, m_host);
	DDX_Text(pDX, IDC_PASSWORD, m_password);
	DDX_Text(pDX, IDC_USERNAME, m_username);
	DDX_Text(pDX, IDC_PORT, m_port);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFTP_clientDlg, CDialog)
	//{{AFX_MSG_MAP(CFTP_clientDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONNECT, OnConnect)
	ON_LBN_DBLCLK(IDC_LISTFILE, OnDblclkListfile)
	ON_BN_CLICKED(IDC_UPDATE, OnUpdate)
	ON_BN_CLICKED(IDC_STOREFILE, OnStorefile)
	ON_BN_CLICKED(IDC_LOADFILE, OnLoadfile)
	ON_BN_CLICKED(IDC_QUIT, OnQuit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFTP_clientDlg message handlers

BOOL CFTP_clientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFTP_clientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFTP_clientDlg::OnPaint() 
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
HCURSOR CFTP_clientDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CFTP_clientDlg::OnConnect() 
{
	// TODO: Add your control notification handler code here

	//����socket
	if( !sock_client.Create() )		//important
	{
		AfxMessageBox("socket����ʧ��");
		return;
	}

	UpdateData(true);

	//���ӷ�����
	if( !sock_client.Connect(m_host,m_port) )
	{
		AfxMessageBox("socket���ӷ�����ʧ��");
		return;
	}	
	MySockRecv();

	CString	send_msg;	//ר������������

	//�����û���
	send_msg = "USER ";
	send_msg += m_username;
	send_msg += "\r\n";	
	MySockSend(send_msg);
	MySockRecv();

	//��������
	send_msg = "PASS ";
	send_msg += m_password;
	send_msg += "\r\n";	
	MySockSend(send_msg);
	MySockRecv();

	//����4���ı��༭��1����ť
	GetDlgItem(IDC_HOST)->EnableWindow(false);
	GetDlgItem(IDC_PORT)->EnableWindow(false);
	GetDlgItem(IDC_USERNAME)->EnableWindow(false);
	GetDlgItem(IDC_PASSWORD)->EnableWindow(false);
	GetDlgItem(IDC_CONNECT)->EnableWindow(false);
}

//���ղ������ļ��б���Ϣ
void CFTP_clientDlg::Parse_list()
{
	//���µ�socket�Ͷ˿ڽ����ļ���Ϣ
	char  filelist[1024] = "";
	if( SOCKET_ERROR == sock_temp.Receive(filelist,1024) )
	{
		AfxMessageBox("���ݽ���ʧ��");
		return;
	}
	CString parselist = filelist;

	//�ַ����ĳ���
	long len = parselist.GetLength();

	//���������е��ļ���
	char filename[32] = "";
	int index_rn = parselist.Find("\r\n");
	int i,j = 0;

	while(len-1 != index_rn+1)
	{
		for(i = index_rn-1;parselist.GetAt(i) != ' ';i--);	//��ȡ�ļ�����ʼλ��
		for(i = i+1;i<index_rn;i++)
		{
			filename[j++] = parselist.GetAt(i);
		}
		j = 0;
		index_rn = parselist.Find("\r\n",index_rn+2);
		if(filename[0] == '.')
		{
			memset(filename,0,32);
			continue;
		}
		m_listfile.AddString(filename);
		memset(filename,0,32);
	}

	//��ȡ���һ���ļ���
	for(i = index_rn-1;parselist.GetAt(i) != ' ';i--);	//��ȡ�ļ�����ʼλ��
	for(i = i+1;i<index_rn;i++)
	{
		filename[j++] = parselist.GetAt(i);
	}
	if(filename[0] == '.')
	{
		return;
	}
	m_listfile.AddString(filename);	
}

//ʹ�÷��������뱻��ģʽ���½��׽��������¿��Ķ˿�
BOOL CFTP_clientDlg::Pasv_mode()
{
	//�����µ�socket
	if( !sock_temp.Create() )
	{
		AfxMessageBox("sock_temp����ʧ��");
		return false;
	}

	CString send_msg;	//ר���ڷ�����Ϣ

	//�÷��������뱻��ģʽ�����PASV
	send_msg = "PASV\r\n";
	MySockSend(send_msg);

	//������Ϣ
	char buf_recv[64] = "";
	if( SOCKET_ERROR == sock_client.Receive(buf_recv,63) )
	{
		AfxMessageBox("���ݽ���ʧ��");
		sock_temp.Close();
		return false;
	}
	CString show_msg = "��Ӧ��";
	show_msg += buf_recv;
	m_listinfo.AddString(show_msg);
	//��ȡ�¿��Ķ˿ںţ���������·���ֵ���ƣ�227 Entering Passive Mode (192,168,0,101,194,73)
	//���㹫ʽ �¿��˿ں� = 194*256 + 73

	//�������ص���Ϣ
	CString parse_str = buf_recv;
	int index_first = 0,index_mid = 0,index_end = 0;

	//��λ
	index_end   = parse_str.Find(')');
	index_mid   = parse_str.ReverseFind(',');
	for(int ind = 0;ind < 4;ind++)
	{
		index_first = parse_str.Find(',',index_first+1);
	}
	
	//����˿ں�
	char port_str[4] = "";
	int i,j = 0;
	for(i = index_first+1;i < index_mid;i++)
	{
		port_str[j++] = parse_str.GetAt(i);
	}

	int port_int = atoi(port_str);
	j = 0;
	memset(port_str,0,4);
	for(i = index_mid+1;i < index_end;i++)
	{
		port_str[j++] = parse_str.GetAt(i);
	}

	//����ó��¿��Ķ˿ں�
	port_int = port_int*256 + atoi(port_str);

	//���µ�sock���ӷ�����
	if( !sock_temp.Connect(m_host,port_int) )	//����ʹ����ַ
	{
		int ErrorNum = GetLastError();
		AfxMessageBox("sock_temp���ӷ�����ʧ��");
		sock_temp.Close();
		return false;
	}
	return true;
}

void CFTP_clientDlg::MySockRecv()
{
	char buf_recv[128] = "";
	if( SOCKET_ERROR == sock_client.Receive(buf_recv,127) )
	{
		AfxMessageBox("���ݽ���ʧ��");
		return;
	}
	//����Ϣ��ʾ��ListBox��
	CString show_msg = "��Ӧ��";
	show_msg += buf_recv;
	m_listinfo.AddString(show_msg);	
}

void CFTP_clientDlg::MySockSend(CString send_msg)
{
	if( SOCKET_ERROR == sock_client.Send( send_msg,send_msg.GetLength() ) )
	{
		AfxMessageBox("���ݷ���ʧ��");
		return;
	}
	//����Ϣ��ʾ��ListBox��
	CString show_msg = "���";
	show_msg += send_msg;
	m_listinfo.AddString(show_msg);
}

void CFTP_clientDlg::OnDblclkListfile() 
{
	// TODO: Add your control notification handler code here
	//���������뱻��ģʽ
	if( !Pasv_mode() )
		return;

	//��ȡѡ����ļ���
	int index = m_listfile.GetCurSel();
	CString filename = "";
	m_listfile.GetText(index,filename);

	//�����ļ������RETR �ļ���
	CString send_msg = "RETR ";
	send_msg += filename;
	send_msg += "\r\n";
	MySockSend(send_msg);
	MySockRecv();

	//д������ļ�����
	fileStore(filename);

	//��ʾ��Ϣ
	AfxMessageBox("�ļ��ѱ���");
}

//�����ļ�����д������
void CFTP_clientDlg::fileStore(CString filename)
{

	//�ļ�����Ի���
	CFileDialog save_dlg(false,NULL,filename);

	if( save_dlg.DoModal() == IDOK)
	{
		CString full_name = save_dlg.GetPathName();
		//�½��ļ�
		CFile	file(full_name,CFile::modeCreate | CFile::modeWrite);
		
		//���µ�socket�Ͷ˿ڽ����ļ���Ϣ
		char  fileContext[128] = "";
		while( 0 != sock_temp.Receive(fileContext,127) )
		{
			file.Write(fileContext,strlen(fileContext));
			memset(fileContext,0,128);
		}
		//�ر��ļ�
		file.Close();
		//�ر��½���������
		sock_temp.Close();
	}
}

void CFTP_clientDlg::OnUpdate()
{
	// TODO: Add your control notification handler code here

	//ʹ���������뱻��ģʽ
	if( !Pasv_mode() )
		return;
	
	//��ȡ��ǰ��������Ŀ¼�µ��ļ��������LIST
	CString send_msg = "LIST\r\n";
	MySockSend(send_msg);
	MySockRecv();	//150 Opening ASCII mode data connection for /bin/ls.
	
	//�����б���Ϣ
	Parse_list();

	//�ر��½���������
	sock_temp.Close();
}

void CFTP_clientDlg::OnStorefile() 
{
	// TODO: Add your control notification handler code here
	//��ʾ���ļ��Ի���
	CFileDialog open_dlg(true);

	CString full_name;	//�ļ���ȫ·��
	CString file_name;

	if(open_dlg.DoModal() == IDOK)
	{
		full_name = open_dlg.GetPathName();
		file_name = open_dlg.GetFileName();
		
		//���뱻��ģʽ
		if( !Pasv_mode() )
			return;

		//�������STOR �ļ���
		CString send_msg = "STOR ";
		send_msg += file_name;
		send_msg += "\r\n";
		MySockSend(send_msg);
		MySockRecv();

		//���ļ�
		CFile file_read(full_name,CFile::modeRead);
		
		//�����ļ�����
		char buf_read[128] = "";
		while( 0 != file_read.Read(buf_read,127) )
		{
			//�ϴ��ļ�
			sock_temp.Send(buf_read,128);
			memset(buf_read,0,128);
		}

		//�ر�����
		sock_temp.Close();
		file_read.Close();
		AfxMessageBox("�ϴ����");
	}
}

void CFTP_clientDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CFTP_clientDlg::OnLoadfile() 
{
	// TODO: Add your control notification handler code here
	//���������뱻��ģʽ
	if( !Pasv_mode() )
		return;
	
	//��ȡѡ����ļ���
	int index = m_listfile.GetCurSel();
	CString filename = "";
	m_listfile.GetText(index,filename);
	
	//�����ļ������RETR �ļ���
	CString send_msg = "RETR ";
	send_msg += filename;
	send_msg += "\r\n";
	MySockSend(send_msg);
	MySockRecv();
	
	//д������ļ�����
	fileStore(filename);
	
	//��ʾ��Ϣ
	AfxMessageBox("�ļ��ѱ���");
}

void CFTP_clientDlg::OnQuit() 
{
	// TODO: Add your control notification handler code here
	//�������QUIT
	CString send_msg = "QUIT\r\n";
	MySockSend(send_msg);
	MySockRecv();

	sock_client.Close();
}
