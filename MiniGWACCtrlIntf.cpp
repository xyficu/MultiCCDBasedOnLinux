// MiniGWACCtrlIntf.cpp : 实现文件
//

#include "StdAfx.h"
#include "MiniGWACCtrlIntf.h"



U9000CtrlIntf::U9000CtrlIntf()
{
	//1. 给U9000Params赋值
	//2. 启动CCD控制工作线程
	for (int i = 0; i<12; i++)
	{
		m_pThrd[i] = (CMyThread *)AfxBeginThread(RUNTIME_CLASS(CMyThread));
		m_pThrd[i]->m_pThreadParams = &m_u9000Params[i];
		m_pThrd[i]->m_conTakeSnapshot = FALSE;
		m_u9000Params[i].bCon = FALSE;
		m_pCWnd[i] = NULL;
		//m_pThrd[i]->m_pMainWnd = m_pCWnd[i];

		m_fitsHDUs[i].airmass = _T("");
		m_fitsHDUs[i].azimuth = _T("");
		m_fitsHDUs[i].bitpix = _T("");
		m_fitsHDUs[i].bscale = _T("");
		m_fitsHDUs[i].bzero = _T("");
		m_fitsHDUs[i].camid = _T("");
		m_fitsHDUs[i].ccdid = _T("");
		m_fitsHDUs[i].ccdsize = _T("");
		m_fitsHDUs[i].ccdtype = _T("");
		m_fitsHDUs[i].dateObs = _T("");
		m_fitsHDUs[i].dateObsUT = _T("");
		m_fitsHDUs[i].dec = _T("");
		m_fitsHDUs[i].elevation = _T("");
		m_fitsHDUs[i].epoch = _T("");
		m_fitsHDUs[i].expTimeHDU = _T("");
		m_fitsHDUs[i].fitsize = _T("");
		m_fitsHDUs[i].gain = _T("");
		m_fitsHDUs[i].imageID = _T("");
		m_fitsHDUs[i].JD = _T("");
		m_fitsHDUs[i].locst = _T("");
		m_fitsHDUs[i].moonAngle = _T("");
		m_fitsHDUs[i].moonPhase = _T("");
		m_fitsHDUs[i].mountID = _T("");
		m_fitsHDUs[i].naxis = _T("");
		m_fitsHDUs[i].naxis1 = _T("");
		m_fitsHDUs[i].naxis2 = _T("");
		m_fitsHDUs[i].pixelScale = _T("");
		m_fitsHDUs[i].ra = _T("");
		m_fitsHDUs[i].readOutNoise = _T("");
		m_fitsHDUs[i].readRate = _T("");
		m_fitsHDUs[i].simple = _T("");
		m_fitsHDUs[i].temperatureAct = _T("");
		m_fitsHDUs[i].temperatureSet = _T("");
		m_fitsHDUs[i].timeEnd = _T("");
		m_fitsHDUs[i].timeEndUT = _T("");
		m_fitsHDUs[i].timeObs = _T("");
		m_fitsHDUs[i].timeObsUT = _T("");
		m_fitsHDUs[i].wacID = _T("");
		m_fitsHDUs[i].weather = _T("");
		m_fitsHDUs[i].observer = _T("");
		//add observe mode
		m_fitsHDUs[i].obsMode = _T("");
	}
	
	m_camera = "A";
	m_prdtLvl ="0";
}

//常规曝光
int U9000CtrlIntf::RegExp( int ccdID, CString imgName, float expTime, BOOL shtStus/*=TRUE*/)
{
	BOOL rslt = FALSE;
	//准备曝光参数
	m_u9000Params[ccdID].stTakeSnapshot.fileName = imgName;
	m_u9000Params[ccdID].stTakeSnapshot.expTime = expTime;
	m_u9000Params[ccdID].stTakeSnapshot.shutter = shtStus;
	m_u9000Params[ccdID].stTakeSnapshot.status = -1;

	m_fitsHDUs[ccdID].ccdtype = "OBJECT";
	m_fitsHDUs[ccdID].obsMode = "O";
	SetHDUs(ccdID);
	//发送曝光消息
	rslt = m_pThrd[ccdID]->PostThreadMessageA(WM_TAKESNAPSHOT, 0, 0);
	if (FALSE == rslt)
	{
		return -1;
	}
	return 0;
}

//连接服务器
int U9000CtrlIntf::ConnectSvr( int ccdID, CString ip, UINT port )
{
	BOOL rslt = FALSE;
	//准备连接参数
	m_u9000Params[ccdID].ip = ip;
	m_u9000Params[ccdID].port = port;
	m_u9000Params[ccdID].conStus = -1;
	//发送连接消息
	rslt = m_pThrd[ccdID]->PostThreadMessageA(WM_SETIPANDPORT, 0, 0);
	if (FALSE == rslt)
	{
		return -1;
	}
	m_pThrd[ccdID]->PostThreadMessageA(WM_CONNECT, 0, 0);
	if (FALSE == rslt)
	{
		return -1;
	}
	m_u9000Params[ccdID].bCon = TRUE;
	return 0;
}

//断开连接
int U9000CtrlIntf::DisConnectSvr( int ccdID )
{
	BOOL rslt = FALSE;
	m_u9000Params[ccdID].disConStus = -1;
	rslt = m_pThrd[ccdID]->PostThreadMessageA(WM_DISCONNECT, 0, 0);
	if (FALSE == rslt)
	{
		return -1;
	}
	m_u9000Params[ccdID].bCon = FALSE;
	return 0;
}

//设置图像保存路径
int U9000CtrlIntf::SetImgPath( int ccdID, CString imgSavPath )
{
	BOOL rslt = FALSE;
	m_u9000Params[ccdID].stSetImgSavPath.path = imgSavPath;
	m_u9000Params[ccdID].stSetImgSavPath.status = -1;
	rslt = m_pThrd[ccdID]->PostThreadMessageA(WM_SETIMGSAVPATH, 0, 0);
	if (FALSE == rslt)
	{
		return -1;
	}
	return 0;
}

//暗场曝光
int U9000CtrlIntf::DarkExp( int ccdID, CString imgName, float expTime, BOOL shtStus/*=FALSE*/ )
{
	BOOL rslt = FALSE;
	//准备曝光参数
	m_u9000Params[ccdID].stTakeSnapshot.fileName = imgName;
	m_u9000Params[ccdID].stTakeSnapshot.expTime = expTime;
	m_u9000Params[ccdID].stTakeSnapshot.shutter = shtStus;
	m_u9000Params[ccdID].stTakeSnapshot.status = -1;
	
	m_fitsHDUs[ccdID].ccdtype = "DARK";
	m_fitsHDUs[ccdID].obsMode = "C";
	//准备FitsHDUs信息
	SetHDUs(ccdID);

	rslt = m_pThrd[ccdID]->PostThreadMessageA(WM_TAKESNAPSHOT, 0, 0);
	if (FALSE == rslt)
	{
		return -1;
	}
	return 0;
}

//设置制冷器温度
int U9000CtrlIntf::SetCoolerTem( int ccdID, int tem )
{
	BOOL rslt = FALSE;
	m_u9000Params[ccdID].stSetCoolerTmp.tmp = tem;
	m_u9000Params[ccdID].stSetCoolerTmp.status = -1;
	rslt = m_pThrd[ccdID]->PostThreadMessageA(WM_SETCOOLERTMP, 0, 0);
	if (FALSE == rslt)
	{
		return -1;
	}
	return 0;
}

//开启制冷器
int U9000CtrlIntf::StartCooler( int ccdID )
{
	BOOL rslt = FALSE;
	m_u9000Params[ccdID].stStartCooler.status = -1;
	rslt = m_pThrd[ccdID]->PostThreadMessageA(WM_STARTCOOLER, 0, 0);
	if (FALSE == rslt)
	{
		return -1;
	}
	return 0;
}

//停止制冷器
int U9000CtrlIntf::StopCooler( int ccdID )
{
	BOOL rslt = FALSE;
	m_u9000Params[ccdID].stStopCooler.status = -1;
	rslt = m_pThrd[ccdID]->PostThreadMessageA(WM_STOPCOOLER, 0, 0);
	if (FALSE == rslt)
	{
		return -1;
	}
	return 0;
}

//获取CCD状态
int U9000CtrlIntf::GetStatus( int ccdID, CString &stus )
{
	BOOL rslt;
	m_u9000Params[ccdID].stGetCcdStatus.status = -1;
	rslt = m_pThrd[ccdID]->PostThreadMessageA(WM_GETCCDSTATUS, 0, 0);
	if (FALSE == rslt)
	{
		return -1;
	}
	Sleep(300);
	stus = m_u9000Params[ccdID].stGetCcdStatus.res;
	return 0;
}

//连续常规曝光
int U9000CtrlIntf::RegExpCon( int ccdID, CString imgName, float expTime, BOOL shtStus/*=TRUE*/ )
{
	BOOL rslt = FALSE;
	//准备曝光参数
	m_u9000Params[ccdID].stTakeSnapshot.fileName = imgName;
	m_u9000Params[ccdID].stTakeSnapshot.expTime = expTime;
	m_u9000Params[ccdID].stTakeSnapshot.shutter = shtStus;
	m_u9000Params[ccdID].stTakeSnapshot.status = -1;
	
	if (-1 == GetImgNameSu(ccdID, m_u9000Params[ccdID].stTakeSnapshot.fileNameSu))
	{
		SetImgNameSu(ccdID, 1);
		m_u9000Params[ccdID].stTakeSnapshot.fileNameSu = 1;
	}
	m_u9000Params[ccdID].stTakeSnapshot.snapStatus = 0;

	m_fitsHDUs[ccdID].ccdtype = "OBJECT";
	m_fitsHDUs[ccdID].obsMode = "O";
	//准备FitsHDUs信息
	SetHDUs(ccdID);

	m_pThrd[ccdID]->m_conTakeSnapshot = TRUE;
	rslt = m_pThrd[ccdID]->PostThreadMessageA(WM_TAKESNAPSHOTCON, 0, 0);
	if (FALSE == rslt)
	{
		return -1;
	}

	return 0;
}

//停止连续常规曝光
int U9000CtrlIntf::RegExpConStop( int ccdID )
{
	m_pThrd[ccdID]->m_conTakeSnapshot = FALSE;
	return 0;
}

void U9000CtrlIntf::SetHDUs( int ccdID )
{
	SYSTEMTIME utcTime, localTime;
	GetLocalTime(&localTime);
	GetSystemTime(&utcTime);

	GetLocalTime(&localTime);
	m_fitsHDUs[ccdID].dateObs.Format("%4d-%02d-%02d", localTime.wYear, localTime.wMonth, localTime.wDay);
	m_fitsHDUs[ccdID].timeObs.Format("%02d:%02d:%02d.%02.2d", localTime.wHour, localTime.wMinute, localTime.wSecond, localTime.wMilliseconds);
	//GetLocalTime(&localTime);
	//m_timeEnd.Format("%02d:%02d:%02d.%02.2d", localTime.wHour, localTime.wMinute, localTime.wSecond, localTime.wMilliseconds);

	GetSystemTime(&utcTime);
	m_fitsHDUs[ccdID].dateObsUT.Format("%4d-%02d-%02d", utcTime.wYear, utcTime.wMonth, utcTime.wDay);
	m_fitsHDUs[ccdID].timeObsUT.Format("%02d:%02d:%02d.%02.2d", utcTime.wHour, utcTime.wMinute, utcTime.wSecond, utcTime.wMilliseconds);
	//GetSystemTime(&utcTime);
	//m_timeEndUT.Format("%02d:%02d:%02d.%02.2d", utcTime.wHour, utcTime.wMinute, utcTime.wSecond, utcTime.wMilliseconds);


	m_fitsHDUs[ccdID].expTimeHDU.Format("%.2f", m_u9000Params[ccdID].stTakeSnapshot.expTime);
	//m_azimuth = "74:00:00";            //从上位机获得
	//m_elevation = "35:00:00";          //从上位机获得
	//m_ra = "15:23:45.21";              //从上位机获得
	//m_dec = "46:00:00.0";              //从上位机获得
	m_fitsHDUs[ccdID].epoch = "2000";

	m_fitsHDUs[ccdID].wacID.Format("XM");
	m_fitsHDUs[ccdID].ccdid.Format("%c", ccdID +'A');

	m_fitsHDUs[ccdID].ccdsize = "3056x3056";
	//m_fitsHDUs[ccdID].gain = "";
	

	m_fitsHDUs[ccdID].mountID.Format("%d", ccdID/2 + 1);//手动输入
	m_fitsHDUs[ccdID].camid = m_camera;                //手动输入
	//m_fitsHDUs[ccdID].readRate = "00.00";			   //手动输入
	//m_fitsHDUs[ccdID].readOutNoise = "10";            //手动输入
	//m_fitsHDUs[ccdID].moonPhase = "";                  //手动输入
	//m_fitsHDUs[ccdID].moonAngle = "";                  //手动输入
	//m_fitsHDUs[ccdID].weather = "";               //手动输入
	//m_fitsHDUs[ccdID].airmass = "";                 //手动输入
	m_fitsHDUs[ccdID].observer = "MiniGWAC";                //手动输入
	//m_fitsHDUs[ccdID].fitsize = "";             
	//m_fitsHDUs[ccdID].JD = "";

	m_fitsHDUs[ccdID].latitude = "40:45:17.88";
	m_fitsHDUs[ccdID].longitude = "117:71:97.22";
	m_fitsHDUs[ccdID].site = "bao";
	m_fitsHDUs[ccdID].target = "release";


	//m_imageID = "130725165823XM1ABO0";
	//date(6)-time(6)-wac(2)-mount(1)-camera(1)-ccd(1)-ccdtype(1)-product level(1)
	m_fitsHDUs[ccdID].imageID.Format("%02d%02d%02d%02d%02d%02dXM%s%s%s%s%s", localTime.wYear%100, localTime.wMonth, localTime.wDay, 
		localTime.wHour, localTime.wMinute, localTime.wSecond,
		m_fitsHDUs[ccdID].mountID.Right(1), m_fitsHDUs[ccdID].camid.Right(1), 
		m_fitsHDUs[ccdID].ccdid.Right(1), m_fitsHDUs[ccdID].ccdtype.Left(1), m_prdtLvl);
	

	//m_u9000Params.stFitsHDUs.simple = m_simple;
	//m_u9000Params.stFitsHDUs.bitpix = m_bitpix;
	//m_u9000Params.stFitsHDUs.naxis = m_naxis;
	//m_u9000Params.stFitsHDUs.naxis1 = m_naxis1;
	//m_u9000Params.stFitsHDUs.naxis2 = m_naxis2;
	//m_u9000Params.stFitsHDUs.bscale = m_bscale;
	//m_u9000Params.stFitsHDUs.bzero = m_bzero;

	//pass local HDUs to thread HDUs 
	m_u9000Params[ccdID].stFitsHDUs.imageID = m_fitsHDUs[ccdID].imageID;
	m_u9000Params[ccdID].stFitsHDUs.ccdtype = m_fitsHDUs[ccdID].ccdtype;
	m_u9000Params[ccdID].stFitsHDUs.dateObs = m_fitsHDUs[ccdID].dateObs;
	m_u9000Params[ccdID].stFitsHDUs.timeObs = m_fitsHDUs[ccdID].timeObs;
	m_u9000Params[ccdID].stFitsHDUs.timeEnd = m_fitsHDUs[ccdID].timeEnd;
	m_u9000Params[ccdID].stFitsHDUs.dateObsUT = m_fitsHDUs[ccdID].dateObsUT;
	m_u9000Params[ccdID].stFitsHDUs.timeObsUT = m_fitsHDUs[ccdID].timeObsUT;
	m_u9000Params[ccdID].stFitsHDUs.timeEndUT = m_fitsHDUs[ccdID].timeEndUT;
	m_u9000Params[ccdID].stFitsHDUs.expTimeHDU = m_fitsHDUs[ccdID].expTimeHDU;
	m_u9000Params[ccdID].stFitsHDUs.ra = m_fitsHDUs[ccdID].ra;
	m_u9000Params[ccdID].stFitsHDUs.dec = m_fitsHDUs[ccdID].dec;
	m_u9000Params[ccdID].stFitsHDUs.epoch = m_fitsHDUs[ccdID].epoch;

	m_u9000Params[ccdID].stFitsHDUs.wacID = m_fitsHDUs[ccdID].wacID;
	m_u9000Params[ccdID].stFitsHDUs.mountID = m_fitsHDUs[ccdID].mountID;
	m_u9000Params[ccdID].stFitsHDUs.camid = m_fitsHDUs[ccdID].camid;
	m_u9000Params[ccdID].stFitsHDUs.ccdid = m_fitsHDUs[ccdID].ccdid;

	m_u9000Params[ccdID].stFitsHDUs.ccdsize = m_fitsHDUs[ccdID].ccdsize;
	m_u9000Params[ccdID].stFitsHDUs.gain = m_fitsHDUs[ccdID].gain;
	m_u9000Params[ccdID].stFitsHDUs.readRate = m_fitsHDUs[ccdID].readRate;
	m_u9000Params[ccdID].stFitsHDUs.readOutNoise = m_fitsHDUs[ccdID].readOutNoise;
	m_u9000Params[ccdID].stFitsHDUs.temperatureSet = m_fitsHDUs[ccdID].temperatureSet;
	m_u9000Params[ccdID].stFitsHDUs.temperatureAct = m_fitsHDUs[ccdID].temperatureAct;

	m_u9000Params[ccdID].stFitsHDUs.moonPhase = m_fitsHDUs[ccdID].moonPhase;
	m_u9000Params[ccdID].stFitsHDUs.moonAngle = m_fitsHDUs[ccdID].moonAngle;
	m_u9000Params[ccdID].stFitsHDUs.weather = m_fitsHDUs[ccdID].weather;

	m_u9000Params[ccdID].stFitsHDUs.pixelScale = m_fitsHDUs[ccdID].pixelScale;
	m_u9000Params[ccdID].stFitsHDUs.locst = m_fitsHDUs[ccdID].locst;
	m_u9000Params[ccdID].stFitsHDUs.azimuth = m_fitsHDUs[ccdID].azimuth;
	m_u9000Params[ccdID].stFitsHDUs.elevation = m_fitsHDUs[ccdID].elevation;
	m_u9000Params[ccdID].stFitsHDUs.airmass = m_fitsHDUs[ccdID].airmass;
	m_u9000Params[ccdID].stFitsHDUs.fitsize = m_fitsHDUs[ccdID].fitsize;
	m_u9000Params[ccdID].stFitsHDUs.JD = m_fitsHDUs[ccdID].JD;
	m_u9000Params[ccdID].stFitsHDUs.observer = m_fitsHDUs[ccdID].observer;
	//add observe mode
	m_u9000Params[ccdID].stFitsHDUs.obsMode = m_fitsHDUs[ccdID].obsMode;


	m_u9000Params[ccdID].stFitsHDUs.latitude = m_fitsHDUs[ccdID].latitude;
	m_u9000Params[ccdID].stFitsHDUs.longitude = m_fitsHDUs[ccdID].longitude;
	m_u9000Params[ccdID].stFitsHDUs.site = m_fitsHDUs[ccdID].site;
	m_u9000Params[ccdID].stFitsHDUs.target = m_fitsHDUs[ccdID].target;

}

//保存消息到日志文件
void U9000CtrlIntf::SaveOpsToLog( int ccdID, CString logInfo )
{
	CString ccdName, logFileName, logPath;
	CStdioFile logFile;
	CFileException fileException;
	//确定log文件名
	ccdName.Format("m%02d", ccdID + 1);

	//GetModuleFileName(NULL,logPath.GetBufferSetLength(MAX_PATH+1),MAX_PATH); 
	//logPath.ReleaseBuffer(); 
	//int pos = logPath.ReverseFind('\\'); 
	//logPath = logPath.Left(pos);

	char path[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, path);

	logPath.Format("%s\\Log", path);
	//创建日志路径
	CFileFind fileFind;
	if (fileFind.FindFile(logPath) == FALSE)
	{
		if (CreateDirectory(logPath, NULL) ==  FALSE)
		{
			AfxMessageBox("创建日志目录失败！");
			return;
		}
	}

	SYSTEMTIME utcTime;
	GetSystemTime(&utcTime);
	logFileName.Format("%s\\%s_UTC-%4d-%02d-%02d.log", logPath, ccdName, utcTime.wYear, utcTime.wMonth, utcTime.wDay);
	if(logFile.Open(logFileName,CFile::typeText|CFile::modeCreate|CFile::modeNoTruncate|CFile::modeReadWrite),&fileException)
	{
		logFile.SeekToEnd();
		logFile.WriteString(logInfo);

	}
	else
	{
		TRACE("Can't open file %s,error=%u\n",logFile,fileException.m_cause);
	}
	logFile.Close();

	return;
}

//获取CCD温度
int U9000CtrlIntf::GetCoolerTem( int ccdID, float &tem )
{
	BOOL rslt = FALSE;
	m_u9000Params[ccdID].stGetCoolerTmp.tmp = 0;
	m_u9000Params[ccdID].stGetCoolerTmp.status = -1;
	rslt = m_pThrd[ccdID]->PostThreadMessageA(WM_GETCOOLERTMP, 0, 0);
	if (FALSE == rslt)
	{
		return -1;
	}
	Sleep(300);
	tem = m_u9000Params[ccdID].stGetCoolerTmp.tmp;
	return 0;
}

U9000CtrlIntf::~U9000CtrlIntf()
{

}

//在对应的CCD服务器上创建目录
int U9000CtrlIntf::CreateDirOnSvr( int ccdID, CString dirName )
{
	BOOL rslt = FALSE;
	m_u9000Params[ccdID].stCreateDirInfo.dirName = dirName;
	rslt = m_pThrd[ccdID]->PostThreadMessageA(WM_CREATEDIRONSVR, 0, 0);
	if (FALSE == rslt)
	{
		return -1;
	}
	return 0;
}

//重启CCD对应的服务器
int U9000CtrlIntf::RebootServer( int ccdID )
{
	BOOL rslt = FALSE;
	rslt = m_pThrd[ccdID]->PostThreadMessageA(WM_REBOOTSVR, 0, 0);
	if (FALSE == rslt)
	{
		return -1;
	}
	return 0;
}

//设置FITS头的RA和DEC
void U9000CtrlIntf::SetRaDec( int ccdID, CString ra, CString dec )
{
	m_fitsHDUs[ccdID].ra = ra;
	m_fitsHDUs[ccdID].dec = dec;
	
}

int U9000CtrlIntf::DarkExpCon( int ccdID, CString imgName, float expTime/*=10*/, BOOL shtStus/*=FALSE*/ )
{
	BOOL rslt = FALSE;
	//准备曝光参数
	m_u9000Params[ccdID].stTakeSnapshot.fileName = imgName;
	m_u9000Params[ccdID].stTakeSnapshot.expTime = expTime;
	m_u9000Params[ccdID].stTakeSnapshot.shutter = shtStus;
	m_u9000Params[ccdID].stTakeSnapshot.status = -1;

	if (-1 == GetImgNameSu(ccdID, m_u9000Params[ccdID].stTakeSnapshot.fileNameSu))
	{
		SetImgNameSu(ccdID, 1);
		m_u9000Params[ccdID].stTakeSnapshot.fileNameSu = 1;
	}
	m_u9000Params[ccdID].stTakeSnapshot.snapStatus = 0;

	m_fitsHDUs[ccdID].ccdtype = "DARK";
	m_fitsHDUs[ccdID].obsMode = "C";
	//准备FitsHDUs信息
	SetHDUs(ccdID);

	m_pThrd[ccdID]->m_conTakeSnapshot = TRUE;
	rslt = m_pThrd[ccdID]->PostThreadMessageA(WM_TAKESNAPSHOTCON, 0, 0);
	if (FALSE == rslt)
	{
		return -1;
	}

	return 0;
}

//停止连续暗场曝光
int U9000CtrlIntf::DarkExpConStop( int ccdID )
{
	m_pThrd[ccdID]->m_conTakeSnapshot = FALSE;
	return 0;
}

int U9000CtrlIntf::DarkExpAsn( int ccdID, CString imgName, float expTime, UINT imgCntAsn, BOOL shtStus/*=FALSE*/ )
{
	BOOL rslt = FALSE;
	//设置暗场连续曝光文件后缀
	m_u9000Params[ccdID].stTakeSnapshot.countCrt = 0;
	m_u9000Params[ccdID].stTakeSnapshot.countAsn = imgCntAsn;
	//准备曝光参数
	m_u9000Params[ccdID].stTakeSnapshot.fileName = imgName;
	m_u9000Params[ccdID].stTakeSnapshot.expTime = expTime;
	m_u9000Params[ccdID].stTakeSnapshot.shutter = shtStus;
	m_u9000Params[ccdID].stTakeSnapshot.status = -1;
	
	m_u9000Params[ccdID].stTakeSnapshot.snapStatus = 0;

	m_fitsHDUs[ccdID].ccdtype = "DARK";
	m_fitsHDUs[ccdID].obsMode = "C";
	//准备FitsHDUs信息
	SetHDUs(ccdID);

	rslt = m_pThrd[ccdID]->PostThreadMessageA(WM_TAKESNAPSHOTASN, 0, 0);
	if (FALSE == rslt)
	{
		return -1;
	}

	return 0;
}

int U9000CtrlIntf::RegExpAsn( int ccdID, CString imgName, float expTime, UINT imgCntAsn, BOOL shtStus/*=TRUE*/ )
{
	BOOL rslt = FALSE;
	//设置暗场连续曝光文件后缀
	m_u9000Params[ccdID].stTakeSnapshot.countCrt = 0;
	m_u9000Params[ccdID].stTakeSnapshot.countAsn = imgCntAsn;
	//准备曝光参数
	m_u9000Params[ccdID].stTakeSnapshot.fileName = imgName;
	m_u9000Params[ccdID].stTakeSnapshot.expTime = expTime;
	m_u9000Params[ccdID].stTakeSnapshot.shutter = shtStus;
	m_u9000Params[ccdID].stTakeSnapshot.status = -1;

	m_u9000Params[ccdID].stTakeSnapshot.snapStatus = 0;

	m_fitsHDUs[ccdID].ccdtype = "OBJECT";
	m_fitsHDUs[ccdID].obsMode = "O";
	//准备FitsHDUs信息
	SetHDUs(ccdID);

	rslt = m_pThrd[ccdID]->PostThreadMessageA(WM_TAKESNAPSHOTASN, 0, 0);
	if (FALSE == rslt)
	{
		return -1;
	}

	return 0;
}

//停止连续模板曝光
int U9000CtrlIntf::TmpltExpConStop( int ccdID )
{
	m_pThrd[ccdID]->m_conTakeSnapshot = FALSE;
	return 0;
}

//模板观测单帧曝光
int U9000CtrlIntf::TmpltExp( int ccdID, CString imgName, float expTime/*=10*/, BOOL shtStus/*=FALSE*/ )
{
	BOOL rslt = FALSE;
	//准备曝光参数
	m_u9000Params[ccdID].stTakeSnapshot.fileName = imgName;
	m_u9000Params[ccdID].stTakeSnapshot.expTime = expTime;
	m_u9000Params[ccdID].stTakeSnapshot.shutter = shtStus;
	m_u9000Params[ccdID].stTakeSnapshot.status = -1;

	m_fitsHDUs[ccdID].ccdtype = "OBJECT";
	m_fitsHDUs[ccdID].obsMode = "T";
	SetHDUs(ccdID);
	//发送曝光消息
	rslt = m_pThrd[ccdID]->PostThreadMessageA(WM_TAKESNAPSHOT, 0, 0);
	if (FALSE == rslt)
	{
		return -1;
	}
	return 0;
}

//模板观测连续曝光
int U9000CtrlIntf::TmpltExpCon( int ccdID, CString imgName, float expTime/*=10*/, BOOL shtStus/*=FALSE*/ )
{
	BOOL rslt = FALSE;
	//准备曝光参数
	m_u9000Params[ccdID].stTakeSnapshot.fileName = imgName;
	m_u9000Params[ccdID].stTakeSnapshot.expTime = expTime;
	m_u9000Params[ccdID].stTakeSnapshot.shutter = shtStus;
	m_u9000Params[ccdID].stTakeSnapshot.status = -1;

	if (-1 == GetImgNameSu(ccdID, m_u9000Params[ccdID].stTakeSnapshot.fileNameSu))
	{
		SetImgNameSu(ccdID, 1);
		m_u9000Params[ccdID].stTakeSnapshot.fileNameSu = 1;
	}
	m_u9000Params[ccdID].stTakeSnapshot.snapStatus = 0;

	m_fitsHDUs[ccdID].ccdtype = "OBJECT";
	m_fitsHDUs[ccdID].obsMode = "T";
	//准备FitsHDUs信息
	SetHDUs(ccdID);

	m_pThrd[ccdID]->m_conTakeSnapshot = TRUE;
	rslt = m_pThrd[ccdID]->PostThreadMessageA(WM_TAKESNAPSHOTCON, 0, 0);
	if (FALSE == rslt)
	{
		return -1;
	}

	return 0;
}

int U9000CtrlIntf::GuideExp( int ccdID, CString imgName, float expTime/*=10*/, BOOL shtStus/*=FALSE*/ )
{
	BOOL rslt = FALSE;
	//准备曝光参数
	m_u9000Params[ccdID].stTakeSnapshot.fileName = imgName;
	m_u9000Params[ccdID].stTakeSnapshot.expTime = expTime;
	m_u9000Params[ccdID].stTakeSnapshot.shutter = shtStus;
	m_u9000Params[ccdID].stTakeSnapshot.status = -1;

	m_fitsHDUs[ccdID].ccdtype = "OBJECT";
	m_fitsHDUs[ccdID].obsMode = "G";
	SetHDUs(ccdID);
	//发送曝光消息
	rslt = m_pThrd[ccdID]->PostThreadMessageA(WM_TAKESNAPSHOT, 0, 0);
	if (FALSE == rslt)
	{
		return -1;
	}
	return 0;
}

int U9000CtrlIntf::GuideExpCon( int ccdID, CString imgName, float expTime/*=10*/, BOOL shtStus/*=FALSE*/ )
{
	BOOL rslt = FALSE;
	//准备曝光参数
	m_u9000Params[ccdID].stTakeSnapshot.fileName = imgName;
	m_u9000Params[ccdID].stTakeSnapshot.expTime = expTime;
	m_u9000Params[ccdID].stTakeSnapshot.shutter = shtStus;
	m_u9000Params[ccdID].stTakeSnapshot.status = -1;

	if (-1 == GetImgNameSu(ccdID, m_u9000Params[ccdID].stTakeSnapshot.fileNameSu))
	{
		SetImgNameSu(ccdID, 1);
		m_u9000Params[ccdID].stTakeSnapshot.fileNameSu = 1;
	}
	m_u9000Params[ccdID].stTakeSnapshot.snapStatus = 0;

	m_fitsHDUs[ccdID].ccdtype = "OBJECT";
	m_fitsHDUs[ccdID].obsMode = "G";
	//准备FitsHDUs信息
	SetHDUs(ccdID);

	m_pThrd[ccdID]->m_conTakeSnapshot = TRUE;
	rslt = m_pThrd[ccdID]->PostThreadMessageA(WM_TAKESNAPSHOTCON, 0, 0);
	if (FALSE == rslt)
	{
		return -1;
	}

	return 0;
}

int U9000CtrlIntf::GuideExpConStop( int ccdID )
{
	m_pThrd[ccdID]->m_conTakeSnapshot = FALSE;
	return 0;
}





