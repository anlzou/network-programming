//Download by www.cctry.com
// MFC�ؼ����ڱ��.h : main header file for the MFC�ؼ����ڱ�� application
//

#if !defined(AFX_MFC_H__E9FA4A02_F330_487F_90D8_3A26542720B6__INCLUDED_)
#define AFX_MFC_H__E9FA4A02_F330_487F_90D8_3A26542720B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMFCApp:
// See MFC�ؼ����ڱ��.cpp for the implementation of this class
//

class CMFCApp : public CWinApp
{
public:
	CMFCApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMFCApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFC_H__E9FA4A02_F330_487F_90D8_3A26542720B6__INCLUDED_)
