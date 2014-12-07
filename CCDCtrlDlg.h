#pragma once
#include "U9000DLLmfc.h"
#include <afxwin.h>
#include "MyThread.h"
#include "U9000Params.h"
#include "Markup.h"


// CCCDCtrlDlg 对话框



class CCCDCtrlDlg : public CDialog
{
	DECLARE_DYNAMIC(CCCDCtrlDlg)

public:
	CCCDCtrlDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCCDCtrlDlg();

	//void WriteHDUs();
	//friend UINT WriteHDUsThread(LPVOID pParam);
	void UpdateFeedBack(CString res);
	void SetHDUs();
	void GetTem();
	void GetRealHDUs();
	void SaveCCDParams( int ccdID);
	void SaveFeedbkToLog( int ccdID, CString logInfo);

	

public:
	U9000Ctrl m_ccdCtrl;
	//CMyThread *m_U9000Thd;
	CMyThread *m_pThrd;
	U9000Params m_u9000Params;
	BOOL m_conExp;
	float m_coolerTemAct;
	float m_coolerTemSet;

	//int m_titleWacID;
	int m_titleCcdID;
	//date(6)-time(6)-wac(2)-mount(1)-camera(1)-ccd(1)-ccdtype(1)-product level(1)
	CString m_camera;
	CString m_ccd;
	CString m_prdtLvl;

public:
	void AssertValid() const;
	

// 对话框数据
	enum { IDD = IDD_CCDCTRL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonConnccd();
	CIPAddressCtrl m_ipAddressCcd;
//	CString m_portCcd;
	UINT m_portCcd;
	afx_msg void OnBnClickedButtonDisconnccd();
	afx_msg void OnBnClickedButtonSavpath();
	CString m_imgSavPath;
//	CString m_expTime;
	CString m_imgName;
	afx_msg void OnBnClickedButtonExp();
//	int m_expTime;
	afx_msg void OnBnClickedButtonStopexp();
	afx_msg void OnBnClickedButtonFanfast();
	afx_msg void OnBnClickedButtonFanmed();
	afx_msg void OnBnClickedButtonFanslow();
	afx_msg void OnBnClickedButtonFanoff();
	virtual BOOL OnInitDialog();
//	CEdit m_feedback;
	CString m_feedback;
	float m_expTime;
	float m_setCoolerTem;
	float m_getCoolerTem;
	afx_msg void OnBnClickedButtonSetcoolertem();
	afx_msg void OnBnClickedButtonGetcoolertem();
	afx_msg void OnBnClickedButtonStartcooler();
	afx_msg void OnBnClickedButtonStopcooler();
	afx_msg void OnBnClickedButtonGetu9000status();
	CString m_airmass;
	CString m_azimuth;
	CString m_bitpix;
	CString m_bscale;
	CString m_bzero;
	CString m_camid;
	CString m_ccdid;
	CString m_ccdsize;
	CString m_ccdtype;
	CString m_dateObs;
	CString m_dateObsUT;
	CString m_dec;
	CString m_elevation;
	CString m_epoch;
	CString m_expTimeHDU;
	CString m_fitsize;
	CString m_gain;
	CString m_imageID;
	CString m_JD;
	CString m_locst;
	CString m_moonAngle;
	CString m_moonPhase;
	CString m_mountID;
	CString m_naxis;
	CString m_naxis1;
	CString m_naxis2;
	CString m_pixelScale;
	CString m_ra;
	CString m_readOutNoise;
	CString m_readRate;
	CString m_simple;
	CString m_temperatureAct;
	CString m_temperatureSet;
	CString m_timeEnd;
	CString m_timeEndUT;
	CString m_timeObs;
	CString m_timeObsUT;
	CString m_wacID;
	CString m_weather;
	//afx_msg void OnBnClickedButtonwritehdus();
	CString m_observer;
	CString m_latitude;
	CString m_longitude;
	CString m_site;
	CString m_target;
	afx_msg LRESULT OnTakeSnapshotCplt(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnSetImgSavPathCplt(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnGetCcdStatusCplt(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnAbortExpCplt(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnSetCoolerTmpCplt(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnGetCoolerTmpCplt(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnStartCoolerCplt(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnStopCoolerCplt(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnSetFanSpdCplt(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnShutSvrCplt(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnSetImgHeadInfoCplt(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnTakeSnapshotSleepCplt(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnWriteHDUCplt(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnTakeSnapshotConCplt(WPARAM wParam,LPARAM lParam);
	afx_msg void OnBnClickedButtonConexp();
	afx_msg void OnBnClickedButtonStopconexp();

	
//	virtual void OnCancel();
//	virtual void PostNcDestroy();
	
	UINT m_imgNameSu;
	afx_msg void OnChangeEditFeedback();
	CButton m_shutterStatus;
	afx_msg void OnBnClickedButtonDark();
	afx_msg void OnClose();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
