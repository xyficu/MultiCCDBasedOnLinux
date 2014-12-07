#pragma once

#include "U9000Params.h"

#include "U9000DLLmfc.h"
#include "Markup.h"

// CMyThread

int SetImgNameSu( int ccdID, UINT imgNameSu);
int GetImgNameSu( int ccdID, UINT &imgNameSu);
//int CreateImgNameSu( int ccdID );

class CMyThread : public CWinThread
{
	DECLARE_DYNCREATE(CMyThread)

public://protected:
	CMyThread();
	CMyThread(CString _ip, UINT _port);           // 动态创建所使用的受保护的构造函数
	virtual ~CMyThread();

private:


public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual int Run();
	CString ip;
	UINT port;

public:
	U9000Ctrl* m_ccdCtrl;
	U9000Params *m_pU9000Params;
	BOOL m_conTakeSnapshot;

	void WriteHDUs(CString fileName);

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void Connect(WPARAM wParam, LPARAM lParam);
	afx_msg void DisConnect(WPARAM wParam, LPARAM lParam);
	afx_msg void SetIPAndPort(WPARAM wParam, LPARAM lParam);

	afx_msg void TakeSnapshot(WPARAM wParam, LPARAM lParam);
	afx_msg void SetImgSavPath(WPARAM wParam, LPARAM lParam);
	afx_msg void GetCcdStatus(WPARAM wParam, LPARAM lParam);
	afx_msg void AbortExp(WPARAM wParam, LPARAM lParam);
	afx_msg void SetCoolerTmp(WPARAM wParam, LPARAM lParam);
	afx_msg void GetCoolerTmp(WPARAM wParam, LPARAM lParam);
	afx_msg void StartCooler(WPARAM wParam, LPARAM lParam);
	afx_msg void StopCooler(WPARAM wParam, LPARAM lParam);
	afx_msg void SetFanSpd(WPARAM wParam, LPARAM lParam);
	afx_msg void ShutSvr(WPARAM wParam, LPARAM lParam);
	afx_msg void SetImgHeadInfo(WPARAM wParam, LPARAM lParam);
	afx_msg void TakeSnapshotSleep(WPARAM wParam, LPARAM lParam);
	afx_msg void WriteHDU(WPARAM wParam, LPARAM lParam);

	afx_msg void TakeSnapshotCon(WPARAM wParam, LPARAM lParam);
	afx_msg void StopTakeSnapshotCon(WPARAM wParam, LPARAM lParam);
	afx_msg void CreateDirOnSvrTh(WPARAM wParam, LPARAM lParam);
	afx_msg void RebootSvrTh(WPARAM wParam, LPARAM lParam);

};


