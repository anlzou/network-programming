//Download by www.cctry.com
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "FtpClient.h"

#include "MainFrm.h"

//add new
#include "MsgShow.h"		//3�������ͷ�ļ�
#include "FileTree.h"
#include "FtpClientView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	ON_WM_CREATE()
	//}}AFX_MSG_MAP

	//add new
	ON_BN_CLICKED(IDC_CONNECT, OnConnect)
	ON_BN_CLICKED(IDC_CHOOSEDISC,OnChooseDisc)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	m_bConnect = false;
	m_pInetSession=new CInternetSession;
	m_curPath = "\\";
}

CMainFrame::~CMainFrame()
{
}

//add new
void CMainFrame::OnConnect() 
{
	//����CFileTree�ĺ�����ʾ�ļ��б�
	CFtpClientView	*pView = (CFtpClientView *)(m_splitter2.GetPane(0,1));
	CMsgShow		*pEdit = (CMsgShow *)(m_splitter1.GetPane(0,0));

	//�жϴ�ʱ�������������״̬
	if(!m_bConnect)
	{
		//��ȡ�����Ի�������д����Ϣ
		CString strHost,strName,strPass;

		m_myDlg.GetDlgItemText(IDC_IP,strHost);
		m_myDlg.GetDlgItemText(IDC_NAME,strName);
		m_myDlg.GetDlgItemText(IDC_PASSWORD,strPass);

		//����FTP������
		try 
		{ 
			m_pFtpConnection=m_pInetSession->GetFtpConnection(strHost,strName,strPass); 
		} 
		catch(CInternetException *pEx) 
		{ 
			TCHAR szError[256]; 
			if(pEx->GetErrorMessage(szError,256)) 
			{
				AfxMessageBox(szError); 
				return;
			}
			else 
			{
				AfxMessageBox("There was an exception."); 
				return;
			}
			
			pEx->Delete(); 
			m_pFtpConnection=NULL; 
		}	

		//�����������ϵ��ļ�
		pView->BrowseDir(m_curPath,m_pFtpConnection);

		//��Ϣ����ʾ��Ϣ
		pEdit->ShowMsg("����ftp������...");
		
		//�ı䰴ť������
		m_myDlg.GetDlgItem(IDC_CONNECT)->SetWindowText("�Ͽ�����");
		m_bConnect = true;

		//���ÿؼ�
		m_myDlg.GetDlgItem(IDC_IP)->EnableWindow(false);
		m_myDlg.GetDlgItem(IDC_NAME)->EnableWindow(false);
		m_myDlg.GetDlgItem(IDC_PASSWORD)->EnableWindow(false);
		m_myDlg.GetDlgItem(IDC_PORT)->EnableWindow(false);
	}
	else	//�Ͽ�����
	{
		//ɾ�������е�������
		pView->deleteItem();

		if(m_pFtpConnection!=NULL) 
		{ 
			m_pFtpConnection->Close(); 
			delete m_pFtpConnection; 
			m_pFtpConnection = NULL;
		}	
		m_bConnect = false;

		pEdit->ShowMsg("�Ͽ��������������");

		//�ı䰴ť������
		m_myDlg.GetDlgItem(IDC_CONNECT)->SetWindowText("���ӷ�����");

		//���ÿؼ�����
		m_myDlg.GetDlgItem(IDC_IP)->EnableWindow(true);
		m_myDlg.GetDlgItem(IDC_NAME)->EnableWindow(true);
		m_myDlg.GetDlgItem(IDC_PASSWORD)->EnableWindow(true);
		m_myDlg.GetDlgItem(IDC_PORT)->EnableWindow(true);
	}
}
void CMainFrame::OnChooseDisc()
{
	//��ȡ�ı����е���Ϣ
	m_myDlg.GetDlgItemText(IDC_DISC,strDisc);

	//����CFileTree�ĺ�����ʾ�ļ��б�
	CFileTree *pView = (CFileTree *)(m_splitter2.GetPane(0,0));

	//���������ͼ�ĵ�������
	pView->deleteItem();
	//�����ļ�
	pView->BrowseDir(strDisc,NULL);

	//��Ϣ����ʾ��Ϣ
	CMsgShow *pEdit = (CMsgShow *)(m_splitter1.GetPane(0,0));
	pEdit->ShowMsg("���ı����ļ���·��...");
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	//ע�͵����򵼴����Ĺ�������״̬��
/*	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}	*/

/*	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}	*/

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
//	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
//	EnableDocking(CBRS_ALIGN_ANY);
//	DockControlBar(&m_wndToolBar);

	//��������Լ���ƵĶԻ��򹤾���
	if( !m_myDlg.Create(this,IDD_FLOAT_DLG,CBRS_TOP | CBRS_HIDE_INPLACE,IDD_FLOAT_DLG) )
	{
		TRACE0("Failed to create dialog bar m_myDlg\n");
		return -1;
	}
	//����ͣ��
	m_myDlg.EnableDocking(CBRS_ALIGN_TOP);
	EnableDocking(CBRS_ALIGN_TOP);
	DockControlBar(&m_myDlg);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	if( !m_splitter1.CreateStatic(this,2,1) )
	{
		return false;
	}
	if( !m_splitter1.CreateView(0,0,RUNTIME_CLASS(CMsgShow),CSize(0,0),pContext) )
	{
		return false;
	}
	m_splitter1.SetRowInfo(0,100,50);		//�����и�

	if( !m_splitter2.CreateStatic(&m_splitter1,1,2,WS_CHILD |WS_VISIBLE,
		m_splitter1.IdFromRowCol(1,0)) )
	{
		return false;
	}
	if( !m_splitter2.CreateView(0,0,RUNTIME_CLASS(CFileTree),CSize(0,0),pContext) )
	{
		return false;
	}
	if( !m_splitter2.CreateView(0,1,RUNTIME_CLASS(CFtpClientView),CSize(0,0),pContext) )
	{
		return false;
	}
	m_splitter2.SetColumnInfo(0,300,50);	//�����п�

	return true;
}
