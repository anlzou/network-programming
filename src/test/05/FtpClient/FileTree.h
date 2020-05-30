//Download by www.cctry.com
#if !defined(AFX_FILETREE_H__4CD45F39_CBD1_4ACC_ABC9_4544D405B1C3__INCLUDED_)
#define AFX_FILETREE_H__4CD45F39_CBD1_4ACC_ABC9_4544D405B1C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileTree.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFileTree view

class CFileTree : public CTreeView
{
protected:
	CFileTree();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CFileTree)

// Attributes
public:
	CTreeCtrl		*tree;				//ָ��treeview����
	CImageList		m_lpImagelist;		//����Զ�����ļ����ļ���ͼ��
	CImageList*		m_pDragImage;       //�϶�ʱ��ʾ��ͼ���б�
	HTREEITEM		m_hItemDragS;		//���϶��ı�ǩ��
	BOOL			m_bDragging;		//����Ƿ����϶�״̬
	CString			m_filename;			//���϶����ļ���
	CString			m_fileLname;		//���游�ڵ�+�ӽڵ��ļ�������������·��

// Operations
public:
	VOID BrowseDir(CString strDir,HTREEITEM hParent);	//�����ļ���--���û�����·��
	VOID deleteItem();									//ɾ������ͼ�е�������
	void GetCtrlRect(CRect *rt);						//��ȡ����ͼ���ھ��δ�С

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileTree)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CFileTree();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CFileTree)
	afx_msg void OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILETREE_H__4CD45F39_CBD1_4ACC_ABC9_4544D405B1C3__INCLUDED_)
