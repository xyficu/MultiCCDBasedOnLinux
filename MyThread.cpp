// MyThread.cpp : 实现文件
//

#include "StdAfx.h"
//#include "MultiCCDBasedOnLinux.h"
#include "MyThread.h"


// CMyThread

IMPLEMENT_DYNCREATE(CMyThread, CWinThread)

CMyThread::CMyThread(CString _ip, UINT _port)
{
	this->ip = _ip;
	this->port = _port;
}

CMyThread::CMyThread()
{
	m_conTakeSnapshot = TRUE;
}

CMyThread::~CMyThread()
{
}

BOOL CMyThread::InitInstance()
{
	m_ccdCtrl = new U9000Ctrl();
	m_pU9000Params = (U9000Params *)m_pThreadParams;
	return TRUE;
}



int CMyThread::ExitInstance()
{
	//delete m_ccdCtrl;
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CMyThread, CWinThread)
	ON_THREAD_MESSAGE(WM_TAKESNAPSHOT, &CMyThread::TakeSnapshot)
	ON_THREAD_MESSAGE(WM_CONNECT, &CMyThread::Connect)
	ON_THREAD_MESSAGE(WM_DISCONNECT, &CMyThread::DisConnect)
	ON_THREAD_MESSAGE(WM_SETIPANDPORT, &CMyThread::SetIPAndPort)
	ON_THREAD_MESSAGE(WM_SETIMGSAVPATH, &CMyThread::SetImgSavPath)
	ON_THREAD_MESSAGE(WM_GETCCDSTATUS, &CMyThread::GetCcdStatus)
	ON_THREAD_MESSAGE(WM_ABORTEXP, &CMyThread::AbortExp)
	ON_THREAD_MESSAGE(WM_SETCOOLERTMP, &CMyThread::SetCoolerTmp)
	ON_THREAD_MESSAGE(WM_GETCOOLERTMP, &CMyThread::GetCoolerTmp)
	ON_THREAD_MESSAGE(WM_STARTCOOLER, &CMyThread::StartCooler)
	ON_THREAD_MESSAGE(WM_STOPCOOLER, &CMyThread::StopCooler)
	ON_THREAD_MESSAGE(WM_SETFANSPEED, &CMyThread::SetFanSpd)
	ON_THREAD_MESSAGE(WM_SHUTSVR, &CMyThread::ShutSvr)
	ON_THREAD_MESSAGE(WM_SETIMGHEADINFO, &CMyThread::SetImgHeadInfo)
	ON_THREAD_MESSAGE(WM_TAKESNAPSHOTSLEEP, &CMyThread::TakeSnapshotSleep)
	ON_THREAD_MESSAGE(WM_WRITEHDU, &CMyThread::WriteHDU)
	ON_THREAD_MESSAGE(WM_STOPTAKESNAPSHOTCON, &CMyThread::StopTakeSnapshotCon)
	ON_THREAD_MESSAGE(WM_TAKESNAPSHOTCON, &CMyThread::TakeSnapshotCon)
	ON_THREAD_MESSAGE(WM_CREATEDIRONSVR, &CMyThread::CreateDirOnSvrTh)
	ON_THREAD_MESSAGE(WM_REBOOTSVR, &CMyThread::RebootSvrTh)


END_MESSAGE_MAP()

void CMyThread::TakeSnapshot( WPARAM wParam, LPARAM lParam )
{
	//更新HDUs时间
	SYSTEMTIME utcTime, localTime;
	GetLocalTime(&localTime);
	GetSystemTime(&utcTime);
	m_pU9000Params->stFitsHDUs.dateObsUT.Format("%4d-%02d-%02d", utcTime.wYear, utcTime.wMonth, utcTime.wDay);
	m_pU9000Params->stFitsHDUs.timeObsUT.Format("%02d:%02d:%02d.%02.2d", utcTime.wHour, utcTime.wMinute, utcTime.wSecond, utcTime.wMilliseconds);
	m_pU9000Params->stFitsHDUs.dateObs.Format("%4d-%02d-%02d", localTime.wYear, localTime.wMonth, localTime.wDay);
	m_pU9000Params->stFitsHDUs.timeObs.Format("%02d:%02d:%02d.%02.2d", localTime.wHour, localTime.wMinute, localTime.wSecond, localTime.wMilliseconds);
	//曝光
	m_pU9000Params->stTakeSnapshot.status = m_ccdCtrl->TakeSnapshotSleep(
		m_pU9000Params->stTakeSnapshot.fileName, m_pU9000Params->stTakeSnapshot.expTime, m_pU9000Params->stTakeSnapshot.shutter, m_pU9000Params->stTakeSnapshot.res);
	//写入Fits头
	if (0 == m_pU9000Params->stTakeSnapshot.status)
	{
		//this->PostThreadMessageA(WM_WRITEHDU, 0, 0);
		//Sleep(m_pU9000Params->stTakeSnapshot.expTime * 1000 +5000);
		CString fileName;
		fileName.Format("%s/%s.fits", m_pU9000Params->stSetImgSavPath.path, m_pU9000Params->stTakeSnapshot.fileName);

		//更新HDUs时间
		SYSTEMTIME utcTime, localTime;
		GetLocalTime(&localTime);
		GetSystemTime(&utcTime);
		m_pU9000Params->stFitsHDUs.timeEndUT.Format("%02d:%02d:%02d.%02.2d", utcTime.wHour, utcTime.wMinute, utcTime.wSecond, utcTime.wMilliseconds);
		m_pU9000Params->stFitsHDUs.timeEnd.Format("%02d:%02d:%02d.%02.2d", localTime.wHour, localTime.wMinute, localTime.wSecond, localTime.wMilliseconds);
		//更新HDUs温度
		CString res;
		m_ccdCtrl->GetCcdStatus(res);
		int pos = -1;
		pos = res.Find(' ');
		m_pU9000Params->stFitsHDUs.temperatureAct.Format("%.6s", res.Left(pos));
		float tmp;
		m_ccdCtrl->GetCoolerTmp(tmp, res);
		m_pU9000Params->stFitsHDUs.temperatureSet.Format("%.6f", tmp);
		//imageID
		m_pU9000Params->stFitsHDUs.imageID.Format("%02d%02d%02d%02d%02d%02d%s", localTime.wYear%100, localTime.wMonth, localTime.wDay, 
			localTime.wHour, localTime.wMinute, localTime.wSecond, m_pU9000Params->stFitsHDUs.imageID.Right(7));

		WriteHDUs(fileName);
		m_pMainWnd->PostMessageA(WM_WRITEHDUCPLT);

	}
	m_pMainWnd->PostMessageA(WM_TAKESNAPSHOTCPLT);
}

void CMyThread::Connect( WPARAM wParam, LPARAM lParam )
{
	m_pU9000Params->conStus = m_ccdCtrl->Connect();
	if (0 == m_pU9000Params->conStus)
	{
		m_pU9000Params->bCon = TRUE;
	}
	
}

void CMyThread::DisConnect( WPARAM wParam, LPARAM lParam )
{
	m_pU9000Params->disConStus = m_ccdCtrl->DisConnect();
	if (m_pU9000Params->disConStus == 0)
	{
		m_pU9000Params->bCon = FALSE;
	}
}

void CMyThread::SetIPAndPort( WPARAM wParam, LPARAM lParam )
{
	m_ccdCtrl->SetIPAndPort(m_pU9000Params->ip, m_pU9000Params->port);

}

void CMyThread::SetImgSavPath( WPARAM wParam, LPARAM lParam )
{
	
	m_pU9000Params->stSetImgSavPath.status = m_ccdCtrl->SetImgSavPath(
		m_pU9000Params->stSetImgSavPath.path, m_pU9000Params->stSetImgSavPath.res);
	m_pMainWnd->PostMessageA(WM_SETIMGSAVPATHCPLT);
}

void CMyThread::GetCcdStatus( WPARAM wParam, LPARAM lParam )
{
	m_pU9000Params->stGetCcdStatus.status = m_ccdCtrl->GetCcdStatus(m_pU9000Params->stGetCcdStatus.res);
	m_pMainWnd->PostMessageA(WM_GETCCDSTATUSCPLT);
}

void CMyThread::AbortExp( WPARAM wParam, LPARAM lParam )
{
	m_pU9000Params->stAbortExp.status = m_ccdCtrl->AbortExp(m_pU9000Params->stAbortExp.res);
	m_pMainWnd->PostMessageA(WM_ABORTEXPCPLT);
}

void CMyThread::SetCoolerTmp( WPARAM wParam, LPARAM lParam )
{
	m_pU9000Params->stSetCoolerTmp.status = m_ccdCtrl->SetCoolerTmp(
		m_pU9000Params->stSetCoolerTmp.tmp, m_pU9000Params->stSetCoolerTmp.res);
	m_pMainWnd->PostMessageA(WM_SETCOOLERTMPCPLT);
}

void CMyThread::GetCoolerTmp( WPARAM wParam, LPARAM lParam )
{

	m_pU9000Params->stGetCoolerTmp.status = m_ccdCtrl->GetCoolerTmp(
		m_pU9000Params->stGetCoolerTmp.tmp, m_pU9000Params->stGetCoolerTmp.res);
	m_pMainWnd->PostMessageA(WM_GETCOOLERTMPCPLT);
}

void CMyThread::StopCooler( WPARAM wParam, LPARAM lParam )
{
	m_pU9000Params->stStopCooler.status = m_ccdCtrl->StopCooler(m_pU9000Params->stStopCooler.res);
	m_pMainWnd->PostMessageA(WM_STOPCOOLERCPLT);
}

void CMyThread::StartCooler( WPARAM wParam, LPARAM lParam )
{
 	m_pU9000Params->stStartCooler.status = m_ccdCtrl->StartCooler(m_pU9000Params->stStartCooler.res);
	m_pMainWnd->PostMessageA(WM_STARTCOOLERCPLT);
}

void CMyThread::SetFanSpd( WPARAM wParam, LPARAM lParam )
{
	m_pU9000Params->stSetFanSpd.status = m_ccdCtrl->SetFanSpd(m_pU9000Params->stSetFanSpd.fanLvl, m_pU9000Params->stSetFanSpd.res);
	m_pMainWnd->PostMessageA(WM_SETFANSPEEDCPLT);
}

void CMyThread::ShutSvr( WPARAM wParam, LPARAM lParam )
{

	m_pU9000Params->stShutSvr.status = m_ccdCtrl->ShutSvr(m_pU9000Params->stShutSvr.res);
	m_pMainWnd->PostMessageA(WM_SHUTSVRCPLT);
}

void CMyThread::SetImgHeadInfo( WPARAM wParam, LPARAM lParam )
{
	
}

void CMyThread::TakeSnapshotSleep( WPARAM wParam, LPARAM lParam )
{
	m_pU9000Params->stTakeSnapshotSleep.status = m_ccdCtrl->TakeSnapshotSleep(
		m_pU9000Params->stTakeSnapshotSleep.fileName, m_pU9000Params->stTakeSnapshotSleep.expTime,
		m_pU9000Params->stTakeSnapshotSleep.shutter, m_pU9000Params->stTakeSnapshotSleep.res);
	m_pMainWnd->PostMessageA(WM_TAKESNAPSHOTSLEEPCPLT);
}

void CMyThread::WriteHDU( WPARAM wParam, LPARAM lParam )
{
	Sleep(m_pU9000Params->stTakeSnapshot.expTime * 1000 +5000);

	m_pMainWnd->PostMessageA(WM_WRITEHDUCPLT);
}

int CMyThread::Run()
{
	return CWinThread::Run();
}

void CMyThread::TakeSnapshotCon( WPARAM wParam, LPARAM lParam )
{
	while (TRUE == m_conTakeSnapshot)
	{
		CString fileName;
		fileName.Format("%s_%04u", m_pU9000Params->stTakeSnapshot.fileName, m_pU9000Params->stTakeSnapshot.fileNameSu);

		//更新HDUs时间
		SYSTEMTIME utcTime, localTime;
		GetLocalTime(&localTime);
		GetSystemTime(&utcTime);
		m_pU9000Params->stFitsHDUs.dateObsUT.Format("%4d-%02d-%02d", utcTime.wYear, utcTime.wMonth, utcTime.wDay);
		m_pU9000Params->stFitsHDUs.timeObsUT.Format("%02d:%02d:%02d.%02.2d", utcTime.wHour, utcTime.wMinute, utcTime.wSecond, utcTime.wMilliseconds);
		m_pU9000Params->stFitsHDUs.dateObs.Format("%4d-%02d-%02d", localTime.wYear, localTime.wMonth, localTime.wDay);
		m_pU9000Params->stFitsHDUs.timeObs.Format("%02d:%02d:%02d.%02.2d", localTime.wHour, localTime.wMinute, localTime.wSecond, localTime.wMilliseconds);
		//更新曝光状态
		m_pU9000Params->stTakeSnapshot.snapStatus = 1;
		//曝光
		m_pU9000Params->stTakeSnapshot.status = m_ccdCtrl->TakeSnapshotSleep(
			fileName, m_pU9000Params->stTakeSnapshot.expTime, m_pU9000Params->stTakeSnapshot.shutter, m_pU9000Params->stTakeSnapshot.res);
		//更新曝光状态
		m_pU9000Params->stTakeSnapshot.snapStatus = 2;

		if (0 == m_pU9000Params->stTakeSnapshot.status)
		{
			//写入Fits头
			if (0 == m_pU9000Params->stTakeSnapshot.status)
			{
				CString fileName;
				fileName.Format("%s/%s_%04u.fits", m_pU9000Params->stSetImgSavPath.path, m_pU9000Params->stTakeSnapshot.fileName, 
					m_pU9000Params->stTakeSnapshot.fileNameSu);

				//更新HDUs时间
				SYSTEMTIME utcTime, localTime;
				GetLocalTime(&localTime);
				GetSystemTime(&utcTime);
				m_pU9000Params->stFitsHDUs.timeEndUT.Format("%02d:%02d:%02d.%02.2d", utcTime.wHour, utcTime.wMinute, utcTime.wSecond, utcTime.wMilliseconds);
				m_pU9000Params->stFitsHDUs.timeEnd.Format("%02d:%02d:%02d.%02.2d", localTime.wHour, localTime.wMinute, localTime.wSecond, localTime.wMilliseconds);
				//更新HDUs温度
				CString res;
				m_ccdCtrl->GetCcdStatus(res);
				int pos = -1;
				pos = res.Find(' ');
				m_pU9000Params->stFitsHDUs.temperatureAct.Format("%.6s", res.Left(pos));
				float tmp;
				m_ccdCtrl->GetCoolerTmp(tmp, res);
				m_pU9000Params->stFitsHDUs.temperatureSet.Format("%.6f", tmp);
				//imageID
				m_pU9000Params->stFitsHDUs.imageID.Format("%02d%02d%02d%02d%02d%02d%s", localTime.wYear%100, localTime.wMonth, localTime.wDay, 
					localTime.wHour, localTime.wMinute, localTime.wSecond, m_pU9000Params->stFitsHDUs.imageID.Right(7));

				WriteHDUs(fileName);
				m_pMainWnd->PostMessageA(WM_WRITEHDUCPLT);
			}
			//更新曝光状态
			m_pU9000Params->stTakeSnapshot.snapStatus = 0;
			//发送曝光结束消息
			m_pMainWnd->PostMessageA(WM_TAKESNAPSHOTCPLT);
			Sleep(1000);//test if err is caused by shot too quickly
			m_pU9000Params->stTakeSnapshot.fileNameSu ++;
			char ch = m_pU9000Params->stFitsHDUs.ccdid[0];
			SetImgNameSu(ch - 'A', m_pU9000Params->stTakeSnapshot.fileNameSu);
		}
		else
		{
			m_conTakeSnapshot = FALSE;
			m_pMainWnd->PostMessageA(WM_STOPTAKESNAPSHOTCONCPLT);
			return;
		}
	}
	m_pMainWnd->PostMessageA(WM_STOPTAKESNAPSHOTCONCPLT);
	
}

//响应停止连续拍照消息
void CMyThread::StopTakeSnapshotCon( WPARAM wParam, LPARAM lParam )
{
	m_conTakeSnapshot = FALSE;
}

//写入Fits图像的HDUs
void CMyThread::WriteHDUs(CString fileName)
{

	/*m_ccdCtrl->WriteHDU(fileName, "SIMPLE", m_pU9000Params->stFitsHDUs.simple, m_pU9000Params->stFitsHDUs.res);
	m_ccdCtrl->WriteHDU(fileName, "BITPIX", m_pU9000Params->stFitsHDUs.bitpix, m_pU9000Params->stFitsHDUs.res);
	m_ccdCtrl->WriteHDU(fileName, "NAXIS", m_pU9000Params->stFitsHDUs.naxis, m_pU9000Params->stFitsHDUs.res);
	m_ccdCtrl->WriteHDU(fileName, "NAXIS1", m_pU9000Params->stFitsHDUs.naxis1, m_pU9000Params->stFitsHDUs.res);
	m_ccdCtrl->WriteHDU(fileName, "NAXIS2", m_pU9000Params->stFitsHDUs.naxis2, m_pU9000Params->stFitsHDUs.res);
	m_ccdCtrl->WriteHDU(fileName, "BSCALE", m_pU9000Params->stFitsHDUs.bscale, m_pU9000Params->stFitsHDUs.res);
	m_ccdCtrl->WriteHDU(fileName, "BZERO", m_pU9000Params->stFitsHDUs.bzero, m_pU9000Params->stFitsHDUs.res);*/
	
	m_ccdCtrl->WriteHDU(fileName, "IMAGEID", m_pU9000Params->stFitsHDUs.imageID, m_pU9000Params->stFitsHDUs.res);
	m_ccdCtrl->WriteHDU(fileName, "COMMENT1", " /date(6)-time(6)-wac(2)-mount(1)-", m_pU9000Params->stFitsHDUs.res);
	m_ccdCtrl->WriteHDU(fileName, "COMMENT2", " /camera(1)-ccd(1)-ccdtype(1)-product level(1)", m_pU9000Params->stFitsHDUs.res);
	m_ccdCtrl->WriteHDU(fileName, "CCDTYPE", m_pU9000Params->stFitsHDUs.ccdtype, m_pU9000Params->stFitsHDUs.res);
	//add observe mode
	m_ccdCtrl->WriteHDU(fileName, "OBSMODE", m_pU9000Params->stFitsHDUs.obsMode + " /object(O), template(T), BIAS DARK FLAT(C)", m_pU9000Params->stFitsHDUs.res);
	
	m_ccdCtrl->WriteHDU(fileName, "DATE-OBS", m_pU9000Params->stFitsHDUs.dateObs + " /local date", m_pU9000Params->stFitsHDUs.res);
	m_ccdCtrl->WriteHDU(fileName, "TIME-OBS", m_pU9000Params->stFitsHDUs.timeObs + " /local time of starting exposure", m_pU9000Params->stFitsHDUs.res);
	m_ccdCtrl->WriteHDU(fileName, "TIME-END", m_pU9000Params->stFitsHDUs.timeEnd + " /local time of ending exposure", m_pU9000Params->stFitsHDUs.res);
	m_ccdCtrl->WriteHDU(fileName, "D-OBS-UT", m_pU9000Params->stFitsHDUs.dateObsUT + " /universal date", m_pU9000Params->stFitsHDUs.res);
	m_ccdCtrl->WriteHDU(fileName, "T-OBS-UT", m_pU9000Params->stFitsHDUs.timeObsUT + " /universal time of starting exposure", m_pU9000Params->stFitsHDUs.res);
	m_ccdCtrl->WriteHDU(fileName, "T-END-UT", m_pU9000Params->stFitsHDUs.timeEndUT + " /universal time of ending exposure", m_pU9000Params->stFitsHDUs.res);

	
	m_ccdCtrl->WriteHDU(fileName, "EXPTIME", m_pU9000Params->stFitsHDUs.expTimeHDU + " /exposure time", m_pU9000Params->stFitsHDUs.res);
	m_ccdCtrl->WriteHDU(fileName, "RA", m_pU9000Params->stFitsHDUs.ra + " /initialized RA OF THE CENTER OF FOV", m_pU9000Params->stFitsHDUs.res);
	m_ccdCtrl->WriteHDU(fileName, "DEC", m_pU9000Params->stFitsHDUs.dec + " /initialized DEC OF THE CENTER OF FOV", m_pU9000Params->stFitsHDUs.res);
	m_ccdCtrl->WriteHDU(fileName, "EPOCH", m_pU9000Params->stFitsHDUs.epoch + " /2000", m_pU9000Params->stFitsHDUs.res);

	m_ccdCtrl->WriteHDU(fileName, "WACID", m_pU9000Params->stFitsHDUs.wacID + " /ID of WAC", m_pU9000Params->stFitsHDUs.res);
	m_ccdCtrl->WriteHDU(fileName, "MOUNTID", m_pU9000Params->stFitsHDUs.mountID + " /ID of MOUNT", m_pU9000Params->stFitsHDUs.res);
	m_ccdCtrl->WriteHDU(fileName, "CAMID", m_pU9000Params->stFitsHDUs.camid + " /ID of CAMERA (letter)", m_pU9000Params->stFitsHDUs.res);
	m_ccdCtrl->WriteHDU(fileName, "CCDID", m_pU9000Params->stFitsHDUs.ccdid + " /ID of CCD (letter)", m_pU9000Params->stFitsHDUs.res);

	m_ccdCtrl->WriteHDU(fileName, "CCDSIZE", m_pU9000Params->stFitsHDUs.ccdsize + " /PIXEL number", m_pU9000Params->stFitsHDUs.res);
	m_ccdCtrl->WriteHDU(fileName, "GAIN", m_pU9000Params->stFitsHDUs.gain + " /e-/ADU", m_pU9000Params->stFitsHDUs.res);
	m_ccdCtrl->WriteHDU(fileName, "READRATE", m_pU9000Params->stFitsHDUs.readRate + " /MHz", m_pU9000Params->stFitsHDUs.res);
	m_ccdCtrl->WriteHDU(fileName, "RDNOISE", m_pU9000Params->stFitsHDUs.readOutNoise + " /read out noise", m_pU9000Params->stFitsHDUs.res);
	m_ccdCtrl->WriteHDU(fileName, "TEMPSET", m_pU9000Params->stFitsHDUs.temperatureSet + " /set CCD temperature", m_pU9000Params->stFitsHDUs.res);
	m_ccdCtrl->WriteHDU(fileName, "TEMPACT", m_pU9000Params->stFitsHDUs.temperatureAct + " /actual CCD temperature", m_pU9000Params->stFitsHDUs.res);

	m_ccdCtrl->WriteHDU(fileName, "MOONPH", m_pU9000Params->stFitsHDUs.moonPhase + " /moon phase", m_pU9000Params->stFitsHDUs.res);
	m_ccdCtrl->WriteHDU(fileName, "MOONANG", m_pU9000Params->stFitsHDUs.moonAngle + " /moon angle", m_pU9000Params->stFitsHDUs.res);
	m_ccdCtrl->WriteHDU(fileName, "WEATHER", m_pU9000Params->stFitsHDUs.weather, m_pU9000Params->stFitsHDUs.res);

	m_ccdCtrl->WriteHDU(fileName, "PXLSCLE", m_pU9000Params->stFitsHDUs.pixelScale + " /pixel scale", m_pU9000Params->stFitsHDUs.res);
	m_ccdCtrl->WriteHDU(fileName, "LCST", m_pU9000Params->stFitsHDUs.locst + " /local sidereal time", m_pU9000Params->stFitsHDUs.res);
	m_ccdCtrl->WriteHDU(fileName, "AZIMUTH", m_pU9000Params->stFitsHDUs.azimuth, m_pU9000Params->stFitsHDUs.res);
	m_ccdCtrl->WriteHDU(fileName, "ELEVA", m_pU9000Params->stFitsHDUs.elevation, m_pU9000Params->stFitsHDUs.res);
	m_ccdCtrl->WriteHDU(fileName, "AIRMASS", m_pU9000Params->stFitsHDUs.airmass, m_pU9000Params->stFitsHDUs.res);

	m_ccdCtrl->WriteHDU(fileName, "FITSIZE", m_pU9000Params->stFitsHDUs.fitsize + " /PIXEL number of image", m_pU9000Params->stFitsHDUs.res);
	m_ccdCtrl->WriteHDU(fileName, "JD", m_pU9000Params->stFitsHDUs.JD + " /julian day (starting with )", m_pU9000Params->stFitsHDUs.res);

	m_ccdCtrl->WriteHDU(fileName, "OBSERVER", m_pU9000Params->stFitsHDUs.observer, m_pU9000Params->stFitsHDUs.res);

	m_ccdCtrl->WriteHDU(fileName, "LATITUDE", m_pU9000Params->stFitsHDUs.latitude, m_pU9000Params->stFitsHDUs.res);
	m_ccdCtrl->WriteHDU(fileName, "LONGITUD", m_pU9000Params->stFitsHDUs.longitude, m_pU9000Params->stFitsHDUs.res);
	m_ccdCtrl->WriteHDU(fileName, "OBSERVAT", m_pU9000Params->stFitsHDUs.site, m_pU9000Params->stFitsHDUs.res);
	//m_ccdCtrl->WriteHDU(fileName, "TARGET", m_pU9000Params->stFitsHDUs.target, m_pU9000Params->stFitsHDUs.res);

	m_ccdCtrl->WriteHDU(fileName, "TELESCOP", "", m_pU9000Params->stFitsHDUs.res);
	m_ccdCtrl->WriteHDU(fileName, "INSTRUME", "", m_pU9000Params->stFitsHDUs.res);

}

//重启服务器端
void CMyThread::RebootSvrTh( WPARAM wParam, LPARAM lParam )
{
	m_pU9000Params->stRebootSvrInfo.status = m_ccdCtrl->RebootSvr(m_pU9000Params->stRebootSvrInfo.res);
}

//在服务器端创建目录
void CMyThread::CreateDirOnSvrTh( WPARAM wParam, LPARAM lParam )
{
	m_pU9000Params->stCreateDirInfo.status = m_ccdCtrl->CreateDir(m_pU9000Params->stCreateDirInfo.dirName, m_pU9000Params->stCreateDirInfo.res);
}



// CMyThread 消息处理程序

int SetImgNameSu( int ccdID, UINT imgNameSu )
{
	CMarkup xmlMiniGWAC;
	BOOL bLoadXML;
	BOOL bFindXML;
	
	CString ccdName, ccdCfgName;
	CString xmlNode = "CCDCtrlParams";

	//准备要写入的数据
	ccdName.Format("m%02d", ccdID + 1);
	ccdCfgName.Format("MiniGWAC_%s.xml", ccdName);

	//写入数据
	bLoadXML = xmlMiniGWAC.Load(ccdCfgName);
	if (bLoadXML)
	{
		xmlMiniGWAC.ResetMainPos();
		bFindXML = xmlMiniGWAC.FindElem(xmlNode);
		if (bFindXML == TRUE)
		{
			xmlMiniGWAC.IntoElem();
			bFindXML = xmlMiniGWAC.FindElem(ccdName);
			if (bFindXML)
			{

				xmlMiniGWAC.SetAttrib("ImgSuffix", imgNameSu);

			}
			else
			{
				xmlMiniGWAC.AddElem(ccdName);
				xmlMiniGWAC.AddAttrib("ImgSuffix", imgNameSu);

			}
		}
		else
		{
			xmlMiniGWAC.AddElem(xmlNode);
			xmlMiniGWAC.IntoElem();
			xmlMiniGWAC.AddElem(ccdName);

			xmlMiniGWAC.AddAttrib("ImgSuffix", imgNameSu);

		}

	}
	else
	{
		if (TRUE == xmlMiniGWAC.SetDoc("<?xml version=\"1.0\" encoding=\"UTF-8\"?>"))
		{
			return -1;
		}
		//xmlMiniGWAC.SetDoc("<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
		xmlMiniGWAC.AddElem(xmlNode);
		xmlMiniGWAC.IntoElem();
		xmlMiniGWAC.AddElem(ccdName);

		xmlMiniGWAC.AddAttrib("ImgSuffix", imgNameSu);

	}

	xmlMiniGWAC.OutOfElem();
	xmlMiniGWAC.Save(ccdCfgName);
	return 0;

}

int GetImgNameSu( int ccdID, UINT &imgNameSu )
{
	CMarkup xmlMiniGWAC;
	BOOL bLoadXml = FALSE;
	BOOL bFind = FALSE;
	CString ccdName;
	CString xmlNode = "CCDCtrlParams";
	CString ccdCfgName;

	ccdName.Format("m%02d", ccdID + 1);
	ccdCfgName.Format("MiniGWAC_%s.xml", ccdName);
	bLoadXml = xmlMiniGWAC.Load(ccdCfgName);
	if (bLoadXml)
	{
		
		xmlMiniGWAC.ResetPos();
		
		if (xmlMiniGWAC.FindElem(xmlNode))
		{

			if (xmlMiniGWAC.FindChildElem(ccdName))
			{
				//从XML文件获取属性
				CString str = xmlMiniGWAC.GetChildAttrib("ImgSuffix");
				imgNameSu = atoi(str);
				return 0;

			}
			else
				return -1;
		}
		else
			return -1;
	}
	else
		return -1;

}

//int CreateImgNameSu( int ccdID )
//{
//	return 0;
//}
