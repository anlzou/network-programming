//Download by www.cctry.com
// SendDlg.cpp : implementation file
//

#include "stdafx.h"
#include "emailmanager.h"
#include "SendDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSendDlg dialog


CSendDlg::CSendDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSendDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSendDlg)
	m_filePath = _T("");
	m_context = _T("");
	m_recv = _T("");
	m_subject = _T("");
	m_smtp_ip = _T("");
	//}}AFX_DATA_INIT
}


void CSendDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSendDlg)
	DDX_Control(pDX, IDC_CLEAR, m_bnClear);
	DDX_Control(pDX, IDC_BTNSEND, m_bnSend);
	DDX_Text(pDX, IDC_FILE, m_filePath);
	DDX_Text(pDX, IDC_CONTEXT, m_context);
	DDX_Text(pDX, IDC_RECV, m_recv);
	DDX_Text(pDX, IDC_SUBJECT, m_subject);
	DDX_Text(pDX, IDC_SMTP_IP, m_smtp_ip);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSendDlg, CDialog)
	//{{AFX_MSG_MAP(CSendDlg)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_APPEND, OnAppend)
	ON_BN_CLICKED(IDC_CLEAR, OnClear)
	ON_BN_CLICKED(IDC_BTNSEND, OnBtnsend)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSendDlg message handlers

BOOL CSendDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_bmBack.DeleteObject();
	m_brBack.DeleteObject();
	m_bmBack.LoadBitmap(IDB_SENDBACK);					//���뱳��ͼƬ
	m_brBack.CreatePatternBrush(&m_bmBack);		//���洰�屳��ͼƬ����OnCtlColor()����

	CString strFontName = _T("����");

	//�������ʼ�����ť
	//set bitmap
	m_bnSend.SetBitmaps(IDB_BTN_NORMAL,IDB_BTN_DOWN,IDB_BTN_HLIGHT);
	m_bnSend.SetForceColor(RGB(255, 255, 0), RGB(255, 255, 255), RGB(255, 255, 255));
	m_bnSend.SetSound(MAKEINTRESOURCE(IDR_WAVEMOVE), ::GetModuleHandle(NULL));
	m_bnSend.SetSound(MAKEINTRESOURCE(IDR_WAVECLICK), ::GetModuleHandle(NULL), TRUE);
	m_bnSend.SizeToContent();
	m_bnSend.SetWindowText(TEXT("�����ʼ�"));
	m_bnSend.SetBtnCursor(IDC_CURSOR_HAND, FALSE);
	
	//set font
	m_bnSend
		.SetDrawText(TRUE, FALSE)							//�Ƿ���ʾ��ť����
		.SetFont3D(TRUE, 3, 2, FALSE)						//��ʾ����3dЧ��
		.SetText3DBKColor(RGB(95, 95, 95))					//3d��Ӱ��ɫ
		.SetFontBold(TRUE, FALSE)							//����
		.SetFontSize(18, FALSE)								//�����С
		.SetFontName(strFontName)							//��������
		;

	//����д�ʼ�����ť
	//set bitmap
	m_bnClear.SetBitmaps(IDB_BTN_NORMAL,IDB_BTN_DOWN,IDB_BTN_HLIGHT);
	m_bnClear.SetForceColor(RGB(255, 255, 0), RGB(255, 255, 255), RGB(255, 255, 255));
	m_bnClear.SetSound(MAKEINTRESOURCE(IDR_WAVEMOVE), ::GetModuleHandle(NULL));
	m_bnClear.SetSound(MAKEINTRESOURCE(IDR_WAVECLICK), ::GetModuleHandle(NULL), TRUE);
	m_bnClear.SizeToContent();
	m_bnClear.SetWindowText(TEXT("��д�ʼ�"));
	m_bnClear.SetBtnCursor(IDC_CURSOR_HAND, FALSE);
	
	//set font
	m_bnClear
		.SetDrawText(TRUE, FALSE)							//�Ƿ���ʾ��ť����
		.SetFont3D(TRUE, 3, 2, FALSE)						//��ʾ����3dЧ��
		.SetText3DBKColor(RGB(95, 95, 95))					//3d��Ӱ��ɫ
		.SetFontBold(TRUE, FALSE)							//����
		.SetFontSize(18, FALSE)								//�����С
		.SetFontName(strFontName)							//��������
		;

	SetWindowText("������");
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CSendDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if(nCtlColor == CTLCOLOR_DLG )
	{
		pDC->SetBkMode(TRANSPARENT);
		return m_brBack;
	}
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CSendDlg::OnAppend() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);

	CFileDialog dlg(TRUE);///TRUEΪOPEN�Ի���FALSEΪSAVE AS�Ի���
	if(dlg.DoModal()==IDOK)
		m_filePath = dlg.GetPathName();
	UpdateData(false);
}

void CSendDlg::OnClear() 
{
	// TODO: Add your control notification handler code here
	m_context = "";
	UpdateData(false);
}

void CSendDlg::OnBtnsend() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	
	m_smtp_ip.TrimLeft();
	m_smtp_ip.TrimRight();
	m_recv.TrimLeft();
	m_recv.TrimRight();
	m_subject.TrimLeft();
	m_subject.TrimRight();
	
	if(m_recv.GetLength() < 3)
	{
		AfxMessageBox("����д��ȷ���ռ�������");
		return;
	}
	
	try
	{
		jmail::IMessagePtr pMessage("JMail.Message");
		
		// ����������
		pMessage->From = (LPCTSTR)m_sender;
		// ����ռ���
		pMessage->AddRecipient((LPCTSTR)m_recv, "", "");		
		// ���ȼ�����,1-5��ν���, 3Ϊ�м�
		pMessage->Priority = 3;		
		// ���뷽ʽ����, Ĭ����iso-8859-1
		pMessage->Charset = "GB2312";		
		// ����
		pMessage->Subject = (LPCTSTR)m_subject;		
		// ����
		pMessage->Body = (LPCTSTR)m_context;		
		// ��ʼ����
		if(m_filePath != "")
		{
			pMessage->AddAttachment((LPCTSTR)m_filePath, VARIANT_TRUE, "image/gif");
		}
		
		pMessage->MailServerUserName = (LPCTSTR)m_sender;
		pMessage->MailServerPassWord = (LPCTSTR)m_sendPsd;
		
		pMessage->Send((LPCTSTR)m_smtp_ip, VARIANT_FALSE);
		pMessage.Release();	
		AfxMessageBox("���ͳɹ�!");
	}
	catch (_com_error e)
	{
		CString strErr;
		strErr.Format("������Ϣ��%s\r\n����������%s", (LPCTSTR)e.ErrorMessage(),
			(LPCTSTR)e.Description());
		AfxMessageBox(strErr);
	}
}
