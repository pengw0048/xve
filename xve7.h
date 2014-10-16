// xve7.h : main header file for the XVE7 application
//

#if !defined(AFX_XVE7_H__16E0F5DB_AABA_45A2_BA9C_5E24DB4B38AE__INCLUDED_)
#define AFX_XVE7_H__16E0F5DB_AABA_45A2_BA9C_5E24DB4B38AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CXve7App:
// See xve7.cpp for the implementation of this class
//

class CXve7App : public CWinApp
{
public:
	CXve7App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXve7App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CXve7App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XVE7_H__16E0F5DB_AABA_45A2_BA9C_5E24DB4B38AE__INCLUDED_)
