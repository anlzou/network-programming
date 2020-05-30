//Download by www.cctry.com
// FtpClientView.h : interface of the CFtpClientView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FTPCLIENTVIEW_H__184971C8_45A7_4DB8_96F5_580651E7B7BA__INCLUDED_)
#define AFX_FTPCLIENTVIEW_H__184971C8_45A7_4DB8_96F5_580651E7B7BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//add new
class CFtpClientDoc;
class CFtpConnection;

class CFtpClientView : public CListView
{
protected: // create from serialization only
	CFtpClientView();
	DECLARE_DYNCREATE(CFtpClientView)

// Attributes
public:
	CFtpClientDoc* GetDocument();

	HIMAGELIST	sys_large_icon;
	CImageList	m_IconList;		//��¼�������б�ؼ�������ͼ���б�
	CListCtrl	*filelist;		//�������ָ��
	CImageList	*m_pImageList;	//ͼ���б�
	bool		m_isDragging;	//�ж��϶�״̬
	CString		m_fileCopy;		//FTP�������ϵ��ļ�·��
	CString		m_filename;		//ѡ������ļ���
	CString		m_curPath;		//�������ĸ�Ŀ¼

// Operations
public:
	//������������Ŀ¼�����е��ļ����������ļ��У�
	VOID BrowseDir(CString strDir,CFtpConnection *ftpCon);
	//��ȡ�б���ͼ���εĴ�С
	void GetCtrlRect(CRect *rt);
	//ɾ���б���ͼ��������
	VOID deleteItem();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFtpClientView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFtpClientView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFtpClientView)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in FtpClientView.cpp
inline CFtpClientDoc* CFtpClientView::GetDocument()
   { return (CFtpClientDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FTPCLIENTVIEW_H__184971C8_45A7_4DB8_96F5_580651E7B7BA__INCLUDED_)
