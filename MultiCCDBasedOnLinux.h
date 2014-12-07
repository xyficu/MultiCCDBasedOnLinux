// MultiCCDBasedOnLinux.h : main header file for the MULTICCDBASEDONLINUX application
//

#if !defined(AFX_MULTICCDBASEDONLINUX_H__5E56B879_BAA4_40EE_8CB5_7CC6B74DF92F__INCLUDED_)
#define AFX_MULTICCDBASEDONLINUX_H__5E56B879_BAA4_40EE_8CB5_7CC6B74DF92F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMultiCCDBasedOnLinuxApp:
// See MultiCCDBasedOnLinux.cpp for the implementation of this class
//

class CMultiCCDBasedOnLinuxApp : public CWinApp
{
public:
	CMultiCCDBasedOnLinuxApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMultiCCDBasedOnLinuxApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMultiCCDBasedOnLinuxApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MULTICCDBASEDONLINUX_H__5E56B879_BAA4_40EE_8CB5_7CC6B74DF92F__INCLUDED_)
