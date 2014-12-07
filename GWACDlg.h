#pragma once
#include "CCDCtrlDlg.h"
#include "MyThread.h"
#include "Markup.h"
//#include "Test2CCDs.h"

// CGWACDlg �Ի���

class CGWACDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGWACDlg)

public:
	CGWACDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGWACDlg();

	CCCDCtrlDlg *m_pDlg[50];
	//CCCDCtrlDlg *m_pDlgBG[36];
	//int m_ccdIDBG;
	CMarkup m_xmlMiniGWAC;
	//int m_wacID;
	int m_ccdID;

	void InitAndShowWACWindow(CCCDCtrlDlg* &pDlg, int ccdID);
	//void InitAndShowWACWindow(CCCDCtrlDlg* &pDlg, int ccdIDBG);
	void LoadCCDParams(CCCDCtrlDlg* &pDlg, int ccdID);
// �Ի�������
	enum { IDD = IDD_DIALOG_MainDlg };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonWac1ccd1();
	afx_msg void OnBnClickedButtonWac1ccd2();
	afx_msg void OnBnClickedButtonWac2ccd1();
	afx_msg void OnBnClickedButtonWac2ccd2();
	afx_msg void OnBnClickedButtonWac3ccd1();
	afx_msg void OnBnClickedButtonWac3ccd2();
	afx_msg void OnBnClickedButtonWac4ccd1();
	afx_msg void OnBnClickedButtonWac4ccd2();
	afx_msg void OnBnClickedButtonWac5ccd1();
	afx_msg void OnBnClickedButtonWac5ccd2();
	afx_msg void OnBnClickedButtonWac6ccd1();
	afx_msg void OnBnClickedButtonWac6ccd2();
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButtonBgccd1();
	afx_msg void OnBnClickedButtonBgccd2();
	afx_msg void OnBnClickedButtonBccd1();
	afx_msg void OnBnClickedButtonBccd2();
	afx_msg void OnBnClickedButton3Bccd3();
	afx_msg void OnBnClickedButtonBccd4();
};
