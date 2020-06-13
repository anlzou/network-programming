//Download by www.cctry.com
// SetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "emailmanager.h"
#include "SetDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetDlg dialog


CSetDlg::CSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetDlg)
	m_ip = _T("");
	m_password = _T("");
	m_username = _T("");
	//}}AFX_DATA_INIT
}


void CSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetDlg)
	DDX_Control(pDX, IDCANCEL, m_bnCancel);
	DDX_Control(pDX, IDOK, m_bnOk);
	DDX_Text(pDX, IDC_IP, m_ip);
	DDX_Text(pDX, IDC_PASSWORD, m_password);
	DDX_Text(pDX, IDC_USERNAME, m_username);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetDlg, CDialog)
	//{{AFX_MSG_MAP(CSetDlg)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetDlg message handlers

BOOL CSetDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_bmBack.DeleteObject();
	m_brBack.DeleteObject();
	m_bmBack.LoadBitmap(IDB_SETBACK);					//���뱳��ͼƬ
	m_brBack.CreatePatternBrush(&m_bmBack);		//���洰�屳��ͼƬ����OnCtlColor()����

	CString strFontName = _T("����");
	
	//////////////////////////////////////////////////////////////////////////

	//��ȷ������ť

	//set bitmap
	m_bnOk.SetBitmaps(IDB_SET_NORMAL, IDB_SET_DOWN, IDB_SET_HLIGHT, 0);
	m_bnOk.SetForceColor(RGB(255, 255, 0), RGB(255, 255, 255), RGB(255, 255, 255), FALSE);
	m_bnOk.SetSound(MAKEINTRESOURCE(IDR_WAVEMOVE), ::GetModuleHandle(NULL));
	m_bnOk.SetSound(MAKEINTRESOURCE(IDR_WAVECLICK), ::GetModuleHandle(NULL), TRUE);
	m_bnOk.SizeToContent();
	m_bnOk.SetBtnCursor(IDC_CURSOR_HAND, FALSE);
	m_bnOk.SetWindowText(TEXT("ȷ��"));
	//set font
	m_bnOk
		.SetDrawText(TRUE, FALSE)							//�Ƿ���ʾ��ť����
		.SetFont3D(TRUE, 3, 2, FALSE)						//��ʾ����3dЧ��
		.SetText3DBKColor(RGB(95, 95, 95), FALSE)			//3d��Ӱ��ɫ
		.SetFontSize(14, FALSE)								//�����С
		.SetFontName(strFontName)							//��������
		;

	//��ȡ������ť

	//set bitmap
	m_bnCancel.SetBitmaps(IDB_SET_NORMAL, IDB_SET_DOWN, IDB_SET_HLIGHT, 0);
	m_bnCancel.SetForceColor(RGB(255, 255, 0), RGB(255, 255, 255), RGB(255, 255, 255), FALSE);
	m_bnCancel.SetSound(MAKEINTRESOURCE(IDR_WAVEMOVE), ::GetModuleHandle(NULL));
	m_bnCancel.SetSound(MAKEINTRESOURCE(IDR_WAVECLICK), ::GetModuleHandle(NULL), TRUE);
	m_bnCancel.SizeToContent();
	m_bnCancel.SetBtnCursor(IDC_CURSOR_HAND, FALSE);
	m_bnCancel.SetWindowText(TEXT("ȡ��"));
	
	//set font
	m_bnCancel
		.SetDrawText(TRUE, FALSE)							//�Ƿ���ʾ��ť����
		.SetFont3D(TRUE, 3, 2, FALSE)						//��ʾ����3dЧ��
		.SetText3DBKColor(RGB(95, 95, 95), FALSE)			//3d��Ӱ��ɫ
		.SetFontSize(14, FALSE)								//�����С
		.SetFontName(strFontName)							//��������
		;

	SetWindowText("��������");
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CSetDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if(nCtlColor == CTLCOLOR_DLG)
	{
		pDC->SetBkMode(TRANSPARENT);
		return m_brBack;
	}
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}
