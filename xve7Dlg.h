// xve7Dlg.h : header file
//
#include <stdio.h>
#include <string.h>
#include <time.h>
#if !defined(AFX_XVE7DLG_H__7792C87C_4010_4430_8D98_85A6B0103350__INCLUDED_)
#define AFX_XVE7DLG_H__7792C87C_4010_4430_8D98_85A6B0103350__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CXve7Dlg dialog

class CXve7Dlg : public CDialog
{
// Construction
public:
	CXve7Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CXve7Dlg)
	enum { IDD = IDD_XVE7_DIALOG };
	CEdit	m_edit;
	CListBox	m_list;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXve7Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CXve7Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	//}}AFX_MSG
	void disp(char*);
	int conv(const char*,BOOL);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XVE7DLG_H__7792C87C_4010_4430_8D98_85A6B0103350__INCLUDED_)
