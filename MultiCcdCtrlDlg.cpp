// MultiCcdCtrlDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MultiCCDBasedOnLinux.h"
#include "CCDCtrlDlg.h"
#include "afxdialogex.h"


// CMultiCcdCtrlDlg 对话框

IMPLEMENT_DYNAMIC(CMultiCcdCtrlDlg, CDialogEx)

CMultiCcdCtrlDlg::CMultiCcdCtrlDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMultiCcdCtrlDlg::IDD, pParent)
{

}

CMultiCcdCtrlDlg::~CMultiCcdCtrlDlg()
{
}

void CMultiCcdCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMultiCcdCtrlDlg, CDialogEx)
END_MESSAGE_MAP()


// CMultiCcdCtrlDlg 消息处理程序
