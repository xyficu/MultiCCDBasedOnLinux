// Request1.cpp : implementation file
//

#include "stdafx.h"
#include "MultiCCDBasedOnLinux.h"
#include "Request1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRequest1

CRequest1::CRequest1(CMultiCCDBasedOnLinuxDlg *pointerMultiCCD)
{
	m_pMultiCCDDlg = pointerMultiCCD;
}

CRequest1::~CRequest1()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CRequest1, CSocket)
	//{{AFX_MSG_MAP(CRequest1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CRequest1 member functions

void CRequest1::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	m_pMultiCCDDlg->FetchMsg(this);
	CSocket::OnReceive(nErrorCode);
}
