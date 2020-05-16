//Download by www.cctry.com
// ClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Client.h"
#include "ClientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//add new
#include "LogDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CClientDlg dialog

CClientDlg::CClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CClientDlg)
	m_check = FALSE;
	m_ectx = _T("");
	m_esay = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	curNum = 0;
	m_check = false;
}


void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClientDlg)
	DDX_Control(pDX, IDC_LIST, m_list);
	DDX_Check(pDX, IDC_CHECK, m_check);
	DDX_Text(pDX, IDC_ECTX, m_ectx);
	DDX_Text(pDX, IDC_ESAY, m_esay);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CClientDlg, CDialog)
	//{{AFX_MSG_MAP(CClientDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTNSEND, OnBtnsend)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, OnDblclkList)
	//}}AFX_MSG_MAP
	ON_MESSAGE(SOCKET_EVENT,OnSocket)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientDlg message handlers

BOOL CClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	//���öԻ��򱳾�
	m_bmBack.DeleteObject();
	m_brBack.DeleteObject();
	m_bmBack.LoadBitmap(IDB_CBACK);
	m_brBack.CreatePatternBrush(&m_bmBack);	

tryagain:
	//�ȵ�����¼�Ի���
	CLogDlg ld;
	if(ld.DoModal() != IDOK)		//û�а�ȷ�ϼ�
	{
		PostQuitMessage(0);			//�˳�����
		return TRUE;
	}
	
	//����������ϢУ��
	if(strlen(ld.m_ipAddr) == 0)
	{
		MessageBox("�������������ַ!");
		goto tryagain;
	}
	
	if(ld.m_name.IsEmpty())
	{
		MessageBox("��������ĳ�ν!");
		goto tryagain;
	}

	m_Name = ld.m_name;
	char im = ld.m_imgNum + 1;

	CString	msg;
	DWORD	err;

	//��SOCKET��Ի�����ϵ������SOCKET����Ϣ��֪ͨ���Ի���
	m_socket.AttachCWnd(this);
	
	if(m_socket.Create() == FALSE)			//�Զ����SOCKET�ĳ�ʼ��������
	{
		err = GetLastError();
		msg.Format("����Socketʧ��!\r\n�������:%d",err);//sprintf��ͬ
		goto msgbox;
	}
	
	//���öԻ���ı���     
	SetWindowText("�������ӵ�������...");
	
	//���ӵ���������������˿�Ϊ0x8123�ĳ���
	if(m_socket.Connect(ld.m_ipAddr,0x8123) == FALSE)
	{
		//������ӳɹ����Է������µ�SOCKET���µĶ˿ںţ������µ�SOCKET���µĶ˿ں�ͨ�š�
		err = GetLastError();
		msg.Format("���ӷ�����ʧ��! \r\n�������:%d",err);

msgbox:
		MessageBox(msg);
		PostQuitMessage(0);           //�˳�
		return TRUE;
	}	
	
	char	pkt[200];
	sprintf(pkt,"%s �����ӵ�������!",m_Name);

	//�ٴ����öԻ���ı���
	SetWindowText(pkt);
	
	Sleep(1000);

	//����Э����Ϣ

	//�����룬���������ң��Լ�����
	pkt[0] = 0x11;
	pkt[1] = im;
	strncpy(pkt+2,m_Name,98);        //����ν�������������

	//����
	int l = strlen(pkt)+1;
	if(m_socket.Send(pkt,l) == FALSE)
	{
		MessageBox("�������ݴ���!");
	}		

	//����ͼ��ͷ��
	HICON myIcon[6];
	int i;
	for( i=0;i<6;i++)
	{
		myIcon[i] = AfxGetApp()->LoadIcon(IDI_ICON1 + i);
	}
	
	//����ͼ���б�
	m_ImageList.Create(32, 32, ILC_COLOR32, 6, 6); 
	for( i=0; i < 6; i++) 
	{ 
		m_ImageList.Add(myIcon[i]); 
	} 

	m_list.SetImageList(&m_ImageList, LVSIL_SMALL); 
	
	m_bSend.AutoLoad(IDC_BTNSEND,this);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CClientDlg::OnPaint() 
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
HCURSOR CClientDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

HBRUSH CClientDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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

void CClientDlg::OnSocket(WPARAM wParam, LPARAM lParam)
{
	char	pkt[4096];
	memset(pkt,0,4096);

	LVFINDINFO   info;
	LVITEM lvitem; 

	switch(lParam)
	{
	case RETR:
		m_socket.Receive(pkt,4096);

		switch(pkt[0])
		{
		case 0x11:
			pName[curNum] = pkt +2;
			curNum++;
			m_ectx += pkt + 2;
			m_ectx += " �������ҡ�\r\n";
			
			lvitem.mask = LVIF_IMAGE|LVIF_TEXT; 
			lvitem.iItem = curNum; 
			lvitem.pszText = pkt + 2; 
			lvitem.iImage = pkt[1] - 1; 
			lvitem.iSubItem = 0; 

			m_list.InsertItem(&lvitem);
			
			break;
		//�Ѽ����û���Ϣ
		case 0x31:
			pName[curNum] = pkt +2;
			curNum++;

			lvitem.mask = LVIF_IMAGE|LVIF_TEXT; 
			lvitem.iItem = curNum; 
			lvitem.pszText = pkt + 2; 
			lvitem.iImage = pkt[1] - 0x31; 
			lvitem.iSubItem = 0; 

			m_list.InsertItem(&lvitem); 
			break;

		case 0x41:
			//pkt + 1��������û���
			m_ectx += pkt + 1;
			m_ectx += " �˳�����\r\n";

			info.flags = LVFI_PARTIAL|LVFI_STRING;  
			info.psz   = pkt + 1;
			int item;
			item = m_list.FindItem(&info);

			if(item != -1)
			{
				m_list.DeleteItem(item);
			}
			break;
		default:
			//����û���κ��������Ϣ��ֱ����ʾ����Ϣ����
			m_ectx += pkt + 1;
		}
		
		UpdateData(false);
		break;
		
		case CLOSE:
			MessageBox("�������ѹر�!");
			break;
	}
}

void CClientDlg::OnBtnsend() 
{
	// TODO: Add your control notification handler code here

	UpdateData();

	char pkt[4096];
	memset(pkt,0,sizeof(pkt));

	int			len;
	
	if(m_check)
	{
		//˽����Ϣ
		pkt[0] = 0x51;
		strcpy(pkt + 1,pName[m_curIndex]);
		len = sprintf(pkt + 100 ,"˽�ģ�%s��%s\r\n",m_Name,m_esay);
		m_socket.Send(pkt,len + 100);
		
		sprintf(pkt + 100 ,"˽�ģ���%s˵��%s\r\n",pName[m_curIndex],m_esay);
		m_ectx += pkt +100;
		m_esay.Empty();
	}
	else
	{	
		//Ⱥ����Ϣ
		pkt[0] = 0x21;										//���빦����0x21
		len = sprintf(pkt+1,"%s˵: %s\r\n",m_Name,m_esay);	//len�ǳ���
		m_socket.Send(pkt,len + 3);							//�ַ��������β���෢������
		
		m_esay.Empty();		
	}
	UpdateData(FALSE);
}

void CClientDlg::OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here

	m_curIndex   =m_list.GetNextItem(-1,   LVNI_SELECTED);
	if(m_curIndex == -1)
	{
		AfxMessageBox("��û��ѡ��˽�ĵ��û�...");
		return;
	}

	m_check =true;
	UpdateData(false);

	*pResult = 0;
}

CClientDlg::~CClientDlg()
{
	m_socket.Close();
}	
