//Download by www.cctry.com
// testDlg.cpp : implementation file
//

#include "stdafx.h"
#include "test.h"
#include "testDlg.h"

#include "comm.h"

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
// CTestDlg dialog

CTestDlg::CTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestDlg)
	m_phonenum = _T("");
	m_context = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestDlg)
	DDX_Control(pDX, IDC_STOPBIT, m_stopbit);
	DDX_Control(pDX, IDC_PORITY, m_pority);
	DDX_Control(pDX, IDC_DATA, m_data);
	DDX_Control(pDX, IDC_BO, m_bo);
	DDX_Text(pDX, IDC_PHONENUM, m_phonenum);
	DDX_Text(pDX, IDC_CONTEXT, m_context);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestDlg, CDialog)
	//{{AFX_MSG_MAP(CTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONCOMM, OnConcomm)
	ON_BN_CLICKED(IDC_SENDPDUMSG, OnSendpdumsg)
	ON_BN_CLICKED(IDC_SENDENGLISH, OnSendenglish)
	ON_BN_CLICKED(IDC_SENDCHINESE, OnSendchinese)
	ON_BN_CLICKED(IDC_SENDPDUMSG2, OnSendpdumsg2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestDlg message handlers

BOOL CTestDlg::OnInitDialog()
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
	m_phonenum = "15110679212";
	m_context = "���������˽�";
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTestDlg::OnPaint() 
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
HCURSOR CTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTestDlg::OnConcomm() 
{
	// TODO: Add your control notification handler code here

	//���ں�
	char numCom[6] = "";
	GetDlgItemText(IDC_COM,numCom,6);
	
	//������
	int index_sel = m_bo.GetCurSel();
	char temp_str[10] = "";
	m_bo.GetLBText(index_sel,temp_str);
	int bo = atoi(temp_str);
	
	//��żУ��λ
	int pority = m_pority.GetCurSel();
	
	//����λ
	index_sel = m_data.GetCurSel();
	memset(temp_str,0,10);
	m_data.GetLBText(index_sel,temp_str);
	int bytebit = atoi(temp_str);
	
	//ֹͣλ
	index_sel = m_stopbit.GetCurSel();
	memset(temp_str,0,10);
	m_stopbit.GetLBText(index_sel,temp_str);
	int stopbit = 0;
	
	if(temp_str == "1")
		stopbit = ONESTOPBIT;
	else if(temp_str == "1.5")
		stopbit = ONE5STOPBITS;
	else if(temp_str == "2")
		stopbit = TWOSTOPBITS;
	
	//�򿪴���
	if(!OpenComm(numCom,bo,pority,bytebit,stopbit))
	{
		AfxMessageBox("�򿪴���ʧ�ܣ�");
		return;
	}
	AfxMessageBox("���ڴ򿪳ɹ�");

	//д������"at\r"
	CString command = "at\r";
	WriteComm(command.GetBuffer(0),command.GetLength());
	
	//���շ��ص�����
	char recv_comm[40] = "";
	ReadComm(recv_comm,40);
	
	//��ʾ��ȡ����Ϣ
	AfxMessageBox(recv_comm);
}




void CTestDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	CloseComm();
	
	CDialog::OnCancel();
}

void CTestDlg::OnSendpdumsg() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	CString strTemp;
	char recv_comm[128] = "";

	//���÷���ģʽ
	strTemp = "at+cmgf=0\r";
	WriteComm(strTemp.GetBuffer(0),strTemp.GetLength());
	ReadComm(recv_comm,128);	
	
	//��ȡ�������ĺ��룬���at+csca?
	strTemp = "at+csca?\r";
	WriteComm(strTemp.GetBuffer(0),strTemp.GetLength());
	memset(recv_comm,0,128);
	ReadComm(recv_comm,128);

	//��ȡ�������ĺ���,������Ϊ׼
	CString strParse = recv_comm;
	char serNum[16] = "";
	int i = 0,j = 0;
	int index_start,index_end;
	index_start = strParse.Find('"');					//����˫���ŵ�λ��
	if(index_start != -1)
	{
		index_end = strParse.Find('"',index_start+1);	//������һ��˫���ŵ�λ��
		if(index_end != -1)
		{
			for(j=index_start+1+1;j<index_end;j++)
			{
				serNum[i++] = strParse.GetAt(j);
			}
		}
	}

	//-------��ʽ���������ĺ���
	//1.ĩβ׷��F
	serNum[i] = 'F';
	CString storeSerNum = serNum;			//��������--�������ĺ���
	//2.��ż����λ��
	for(i=0;i<=12;i+=2)
	{
		char ch;
		ch = serNum[i];
		serNum[i] = serNum[i+1];
		serNum[i+1] = ch;
	}
	//3.��ǰ���"0891"
	CString afterSerNum = "0891";
	afterSerNum += serNum;								//---afterSerNum

	//------��ʽ�����ź���
	//1.�ӡ�86���͡�F��
	CString phoneNum = "86";
	phoneNum += m_phonenum;
	phoneNum += "F";
	//2.��ż����λ��
	for(i=0;i<=12;i+=2)
	{
		char ch1,ch2;
		ch1 = phoneNum.GetAt(i);
		ch2 = phoneNum.GetAt(i+1);
		phoneNum.SetAt(i,ch2);
		phoneNum.SetAt(i+1,ch1);
	}

	//------��ʽ����������
	//1.�ַ�ת��ΪUnicode��ʽ
	WCHAR	SendContext[64];
	
	int countChar = MultiByteToWideChar(CP_ACP,0,m_context,-1,SendContext,64);
	CString strContext;
	for(i=0;i<countChar-1;i++)
	{
		CString strTemp;
		strTemp.Format("%x",SendContext[i]);
		strContext += strTemp;
	}
	//2.���㴮�ĳ��ȣ���2�������ǰ��,��ʮ��������ʽ
	int len = strContext.GetLength();
	len = len/2;	
	strTemp.Format("%X",len);
	CString strFinCon = "";
	if(len < 16)
	{
		strFinCon = "0";
	}	
	strFinCon += strTemp;
	strFinCon += strContext;							//---strFinCon

	//---��ϴ���
	strTemp = "11000d91";
	strTemp += phoneNum;
	strTemp += "000800";
	strTemp += strFinCon;

	//ͨ��AT�����
	len = strTemp.GetLength();
	len = len/2;
	CString strLen;
	strLen.Format("%d",len);
 	CString sendAt = "at+cmgs=";
	sendAt += strLen;
 	sendAt += "\r";

	WriteComm(sendAt.GetBuffer(0),sendAt.GetLength());
	memset(recv_comm,0,128);
	ReadComm(recv_comm,128);

	CString sendMsg = afterSerNum + strTemp;
	sendMsg += "\x1a";

	WriteComm(sendMsg.GetBuffer(0),sendMsg.GetLength());
	memset(recv_comm,0,128);
	ReadComm(recv_comm,128);
	AfxMessageBox("���ŷ��ͳɹ�~~~");
}

void CTestDlg::OnSendenglish() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	
	//���÷���ģʽ
	CString strTemp = "at+cmgf=1\r";
	WriteComm(strTemp.GetBuffer(0),strTemp.GetLength());
	char recv_comm[128] = "";
	ReadComm(recv_comm,128);

	//���÷���Ӣ��
	strTemp = "at+csmp=1,255,0,0\r";
	WriteComm(strTemp.GetBuffer(0),strTemp.GetLength());
	memset(recv_comm,0,128);
	ReadComm(recv_comm,128);
	
	//�ֻ�����
	//��������at+cmgs=�ֻ���
	CString sendNum = "at+cmgs=";
	sendNum += m_phonenum;
	sendNum += "\r";
	WriteComm(sendNum.GetBuffer(0),sendNum.GetLength());
	ReadComm(recv_comm,128);
	
	//д���������
	sendNum = m_context;
	sendNum += (char)26;	//Ctrl+Z
	WriteComm(sendNum.GetBuffer(0),sendNum.GetLength());
	memset(recv_comm,0,128);
	ReadComm(recv_comm,128);
	AfxMessageBox("���ŷ��ͳɹ�~~~");
}

void CTestDlg::OnSendchinese() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	
	//���÷���ģʽ
	CString strTemp = "at+cmgf=1\r";
	WriteComm(strTemp.GetBuffer(0),strTemp.GetLength());
	char recv_comm[128] = "";
	ReadComm(recv_comm,128);
	
	//���÷�������
	strTemp = "at+csmp=1,255,0,8\r";
	WriteComm(strTemp.GetBuffer(0),strTemp.GetLength());
	memset(recv_comm,0,128);
	ReadComm(recv_comm,128);

	//����ָ��
	strTemp = "at+cmgs=";
	strTemp += m_phonenum;
	strTemp += "\r";
	WriteComm(strTemp.GetBuffer(0),strTemp.GetLength());
	memset(recv_comm,0,128);
	ReadComm(recv_comm,128);

	//�ַ�ת��ΪUnicode��ʽ
	WCHAR	SendContext[64];
	int countChar = MultiByteToWideChar(CP_ACP,0,m_context,-1,SendContext,64);
	CString strContext;
	for(int i=0;i<countChar-1;i++)
	{
		CString temp;
		temp.Format("%x",SendContext[i]);
		strContext += temp;
	}
	strContext += "\x1a";
	//���ͺ���
	WriteComm(strContext.GetBuffer(0),strContext.GetLength());
	memset(recv_comm,0,128);
	ReadComm(recv_comm,128);
	AfxMessageBox("���ŷ��ͳɹ�~~~");
}

void CTestDlg::OnSendpdumsg2() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	CString strTemp;
	char recv_comm[128] = "";

	//���÷���ģʽ
	strTemp = "at+cmgf=0\r";
	WriteComm(strTemp.GetBuffer(0),strTemp.GetLength());
	ReadComm(recv_comm,128);	
	
	//------��ʽ�����ź���
	//1.�ӡ�86���͡�F��
	CString phoneNum = "86";
	phoneNum += m_phonenum;
	phoneNum += "F";
	//2.��ż����λ��
	for(int i=0;i<=12;i+=2)
	{
		char ch1,ch2;
		ch1 = phoneNum.GetAt(i);
		ch2 = phoneNum.GetAt(i+1);
		phoneNum.SetAt(i,ch2);
		phoneNum.SetAt(i+1,ch1);
	}

	//------��ʽ����������
	//1.�ַ�ת��ΪUnicode��ʽ
	WCHAR	SendContext[64];
	int countChar = MultiByteToWideChar(CP_ACP,0,m_context,-1,SendContext,64);
	CString strContext;
	for(i=0;i<countChar-1;i++)
	{
		CString strTemp;
		strTemp.Format("%x",SendContext[i]);
		strContext += strTemp;
	}
	//2.���㴮�ĳ��ȣ���2�������ǰ��,��ʮ��������ʽ
	int len = strContext.GetLength();
	len = len/2;	
	strTemp.Format("%X",len);
	CString strFinCon = "";
	if(len < 16)
	{
		strFinCon = "0";
	}	
	strFinCon += strTemp;
	strFinCon += strContext;							//---strFinCon

	//---��ϴ���
	strTemp = "0011000d91";
	strTemp += phoneNum;
	strTemp += "000800";
	strTemp += strFinCon;

	//ͨ��AT�����
	len = strTemp.GetLength()-2;
	len = len/2;
	CString strLen;
	strLen.Format("%d",len);
 	CString sendAt = "at+cmgs=";
	sendAt += strLen;
 	sendAt += "\r";

	WriteComm(sendAt.GetBuffer(0),sendAt.GetLength());
	memset(recv_comm,0,128);
	ReadComm(recv_comm,128);

	CString sendMsg = strTemp;
	sendMsg += "\x1a";

	WriteComm(sendMsg.GetBuffer(0),sendMsg.GetLength());
	memset(recv_comm,0,128);
	ReadComm(recv_comm,128);
	AfxMessageBox("���ŷ��ͳɹ�~~~");
}
