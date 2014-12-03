// Tree30303.h : main header file for the TREE30303 application
//

#if !defined(AFX_TREE30303_H__316F13F5_30E1_46E5_A18D_EE87E54060FA__INCLUDED_)
#define AFX_TREE30303_H__316F13F5_30E1_46E5_A18D_EE87E54060FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTree30303App:
// See Tree30303.cpp for the implementation of this class
//

class CTree30303App : public CWinApp
{
public:
	CTree30303App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTree30303App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CTree30303App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TREE30303_H__316F13F5_30E1_46E5_A18D_EE87E54060FA__INCLUDED_)
