//Download by www.cctry.com
// TCP�ͻ��˳���.h : main header file for the TCP�ͻ��˳��� application
//

#if !defined(AFX_TCP_H__79645CB7_D87A_41F8_A61C_D2CBCC383100__INCLUDED_)
#define AFX_TCP_H__79645CB7_D87A_41F8_A61C_D2CBCC383100__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTCPApp:
// See TCP�ͻ��˳���.cpp for the implementation of this class
//

class CTCPApp : public CWinApp
{
public:
	CTCPApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCPApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTCPApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TCP_H__79645CB7_D87A_41F8_A61C_D2CBCC383100__INCLUDED_)
