#pragma once
#include "StdAfx.h"
#include "U9000DLLmfc.h"
#include "U9000Params.h"
#include "MyThread.h"


class U9000CtrlIntf// : CWinThread
{
public:
	U9000CtrlIntf();
	~U9000CtrlIntf();

	//CCD操作方法
	int ConnectSvr(int ccdID, CString ip, UINT port);
	int DisConnectSvr(int ccdID);
	int SetImgPath(int ccdID, CString imgSavPath);

	int DarkExp(int ccdID, CString imgName, float expTime=10, BOOL shtStus=FALSE);
	int DarkExpCon(int ccdID, CString imgName, float expTime=10, BOOL shtStus=FALSE);
	int DarkExpAsn(int ccdID, CString imgName, float expTime, UINT imgCntAsn, BOOL shtStus=FALSE);
	int DarkExpConStop(int ccdID);

	int RegExpAsn(int ccdID, CString imgName, float expTime, UINT imgCntAsn, BOOL shtStus=TRUE);
	int RegExp(int ccdID, CString imgName, float expTime=10, BOOL shtStus=TRUE);
	int RegExpCon(int ccdID, CString imgName, float expTime=10, BOOL shtStus=TRUE);
	int RegExpConStop(int ccdID);

	//增加模板观测API
	int TmpltExp(int ccdID, CString imgName, float expTime=10, BOOL shtStus=FALSE);
	int TmpltExpCon(int ccdID, CString imgName, float expTime=10, BOOL shtStus=FALSE);
	int TmpltExpConStop(int ccdID);

	//增加导星观测API
	int GuideExp(int ccdID, CString imgName, float expTime=10, BOOL shtStus=FALSE);
	int GuideExpCon(int ccdID, CString imgName, float expTime=10, BOOL shtStus=FALSE);
	int GuideExpConStop(int ccdID);

	int SetCoolerTem(int ccdID, int tem);
	int GetCoolerTem(int ccdID, float &tem);
	int StartCooler(int ccdID);
	int StopCooler(int ccdID);
	int GetStatus(int ccdID, CString &stus);
	int CreateDirOnSvr(int ccdID, CString dirName);
	int RebootServer(int ccdID);
	void SetRaDec(int ccdID, CString ra, CString dec);

	void SetHDUs(int ccdID);
	void SaveOpsToLog(int ccdID, CString logInfo);


	//CCD控制参数
	U9000Params m_u9000Params[12];
	CMyThread *m_pThrd[12];
	FitsHDUs m_fitsHDUs[12];
	CWnd* m_pCWnd[12];

	CString m_camera;
	CString m_prdtLvl;

protected:

private:
	
};

