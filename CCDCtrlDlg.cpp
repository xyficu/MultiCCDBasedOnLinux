// CCDCtrlDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MultiCCDBasedOnLinux.h"
#include "CCDCtrlDlg.h"
#include "afxdialogex.h"


// CCCDCtrlDlg 对话框

IMPLEMENT_DYNAMIC(CCCDCtrlDlg, CDialog)

CCCDCtrlDlg::CCCDCtrlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCCDCtrlDlg::IDD, pParent)
{



	//  m_portCcd = _T("");
	m_portCcd = 0;
	m_imgSavPath = _T("");
	//  m_expTime = _T("");
	m_imgName = _T("");
	//  m_expTime = 0;

	m_feedback = _T("");
	m_expTime = 0.0f;
	m_setCoolerTem = 0.0f;
	m_getCoolerTem = 0.0f;
	m_airmass = _T("");
	m_azimuth = _T("");
	m_bitpix = _T("");
	m_bscale = _T("");
	m_bzero = _T("");
	m_camid = _T("");
	m_ccdid = _T("");
	m_ccdsize = _T("");
	m_ccdtype = _T("");
	m_dateObs = _T("");
	m_dateObsUT = _T("");
	m_dec = _T("");
	m_elevation = _T("");
	m_epoch = _T("");
	m_expTimeHDU = _T("");
	m_fitsize = _T("");
	m_gain = _T("");
	m_imageID = _T("");
	m_JD = _T("");
	m_locst = _T("");
	m_moonAngle = _T("");
	m_moonPhase = _T("");
	m_mountID = _T("");
	m_naxis = _T("");
	m_naxis1 = _T("");
	m_naxis2 = _T("");
	m_pixelScale = _T("");
	m_ra = _T("");
	m_readOutNoise = _T("");
	m_readRate = _T("");
	m_simple = _T("");
	m_temperatureAct = _T("");
	m_temperatureSet = _T("");
	m_timeEnd = _T("");
	m_timeEndUT = _T("");
	m_timeObs = _T("");
	m_timeObsUT = _T("");
	m_wacID = _T("");
	m_weather = _T("");
	m_observer = _T("");
	m_conExp = FALSE;
	//m_titleWacID = 1;
	m_titleCcdID = 1;

	m_camera = "A";
	m_ccd = "B";
	m_prdtLvl ="0";
	
}

CCCDCtrlDlg::~CCCDCtrlDlg()
{
}

void CCCDCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS_CCD, m_ipAddressCcd);
	//  DDX_Text(pDX, IDC_EDIT_PortOfCCD, m_portCcd);
	DDX_Text(pDX, IDC_EDIT_PortOfCCD, m_portCcd);
	DDV_MinMaxUInt(pDX, m_portCcd, 0, 65535);
	DDX_Text(pDX, IDC_EDIT_ImgPath, m_imgSavPath);
	//  DDX_Text(pDX, IDC_EDIT_EXPTime, m_expTime);
	DDX_Text(pDX, IDC_EDIT_ImgName, m_imgName);
	//  DDX_Text(pDX, IDC_EDIT_EXPTime, m_expTime);
	//  DDX_Control(pDX, IDC_EDIT_FeedBack, m_feedback);
	DDX_Text(pDX, IDC_EDIT_FeedBack, m_feedback);
	DDX_Text(pDX, IDC_EDIT_EXPTime, m_expTime);
	DDX_Text(pDX, IDC_EDIT_SetCoolerTem, m_setCoolerTem);
	DDX_Text(pDX, IDC_EDIT_GetCoolerTem, m_getCoolerTem);
	DDX_Text(pDX, IDC_EDIT_AIRMASS, m_airmass);
	DDX_Text(pDX, IDC_EDIT_AZIMUTH, m_azimuth);
	DDX_Text(pDX, IDC_EDIT_BITPIX, m_bitpix);
	DDX_Text(pDX, IDC_EDIT_BSCALE, m_bscale);
	DDX_Text(pDX, IDC_EDIT_BZERO, m_bzero);
	DDX_Text(pDX, IDC_EDIT_CAMID, m_camid);
	DDX_Text(pDX, IDC_EDIT_CCDID, m_ccdid);
	DDX_Text(pDX, IDC_EDIT_CCDSIZE, m_ccdsize);
	DDX_Text(pDX, IDC_EDIT_CCDTYPE, m_ccdtype);
	DDX_Text(pDX, IDC_EDIT_DATE_OBS, m_dateObs);
	DDX_Text(pDX, IDC_EDIT_DATE_OBS_UT, m_dateObsUT);
	DDX_Text(pDX, IDC_EDIT_DEC, m_dec);
	DDX_Text(pDX, IDC_EDIT_ELEVATION, m_elevation);
	DDX_Text(pDX, IDC_EDIT_EPOCH, m_epoch);
	DDX_Text(pDX, IDC_EDIT_EXPTIME_HDU, m_expTimeHDU);
	DDX_Text(pDX, IDC_EDIT_FITSIZE, m_fitsize);
	DDX_Text(pDX, IDC_EDIT_GAIN, m_gain);
	DDX_Text(pDX, IDC_EDIT_IMAGEID, m_imageID);
	DDX_Text(pDX, IDC_EDIT_JD, m_JD);
	DDX_Text(pDX, IDC_EDIT_LOCST, m_locst);
	DDX_Text(pDX, IDC_EDIT_MOONANGLE, m_moonAngle);
	DDX_Text(pDX, IDC_EDIT_MOONPHASE, m_moonPhase);
	DDX_Text(pDX, IDC_EDIT_MOUNTID, m_mountID);
	DDX_Text(pDX, IDC_EDIT_NAXIS, m_naxis);
	DDX_Text(pDX, IDC_EDIT_NAXIS1, m_naxis1);
	DDX_Text(pDX, IDC_EDIT_NAXIS2, m_naxis2);
	DDX_Text(pDX, IDC_EDIT_PIXELSCALE, m_pixelScale);
	DDX_Text(pDX, IDC_EDIT_RA, m_ra);
	DDX_Text(pDX, IDC_EDIT_READOUTNOISE, m_readOutNoise);
	DDX_Text(pDX, IDC_EDIT_READRATE, m_readRate);
	DDX_Text(pDX, IDC_EDIT_SIMPLE, m_simple);
	DDX_Text(pDX, IDC_EDIT_TEMPERATUREACT, m_temperatureAct);
	DDX_Text(pDX, IDC_EDIT_TEMPERATURESET, m_temperatureSet);
	DDX_Text(pDX, IDC_EDIT_TIME_END, m_timeEnd);
	DDX_Text(pDX, IDC_EDIT_TIME_END_UT, m_timeEndUT);
	DDX_Text(pDX, IDC_EDIT_TIME_OBS, m_timeObs);
	DDX_Text(pDX, IDC_EDIT_TIME_OBS_UT, m_timeObsUT);
	DDX_Text(pDX, IDC_EDIT_WACID, m_wacID);
	DDX_Text(pDX, IDC_EDIT_WEATHER, m_weather);
	DDX_Text(pDX, IDC_EDIT_OBSERVER, m_observer);
	DDX_Text(pDX, IDC_EDIT_ImgNameSu, m_imgNameSu);
	DDX_Control(pDX, IDC_CHECK_ShutterStatus, m_shutterStatus);
}


BEGIN_MESSAGE_MAP(CCCDCtrlDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ConnCCD, &CCCDCtrlDlg::OnBnClickedButtonConnccd)
	ON_BN_CLICKED(IDC_BUTTON_DisConnCCD, &CCCDCtrlDlg::OnBnClickedButtonDisconnccd)
	ON_BN_CLICKED(IDC_BUTTON_SavPath, &CCCDCtrlDlg::OnBnClickedButtonSavpath)
	ON_BN_CLICKED(IDC_BUTTON_EXP, &CCCDCtrlDlg::OnBnClickedButtonExp)
	ON_BN_CLICKED(IDC_BUTTON_StopEXP, &CCCDCtrlDlg::OnBnClickedButtonStopexp)
	ON_BN_CLICKED(IDC_BUTTON_FanFast, &CCCDCtrlDlg::OnBnClickedButtonFanfast)
	ON_BN_CLICKED(IDC_BUTTON_FanMed, &CCCDCtrlDlg::OnBnClickedButtonFanmed)
	ON_BN_CLICKED(IDC_BUTTON_FanSlow, &CCCDCtrlDlg::OnBnClickedButtonFanslow)
	ON_BN_CLICKED(IDC_BUTTON_FanOff, &CCCDCtrlDlg::OnBnClickedButtonFanoff)
	ON_BN_CLICKED(IDC_BUTTON_SetCoolerTem, &CCCDCtrlDlg::OnBnClickedButtonSetcoolertem)
	ON_BN_CLICKED(IDC_BUTTON_GetCoolerTem, &CCCDCtrlDlg::OnBnClickedButtonGetcoolertem)
	ON_BN_CLICKED(IDC_BUTTON_StartCooler, &CCCDCtrlDlg::OnBnClickedButtonStartcooler)
	ON_BN_CLICKED(IDC_BUTTON_StopCooler, &CCCDCtrlDlg::OnBnClickedButtonStopcooler)
	ON_BN_CLICKED(IDC_BUTTON_GetU9000Status, &CCCDCtrlDlg::OnBnClickedButtonGetu9000status)
	//ON_BN_CLICKED(IDC_BUTTON_writeHDUs, &CCCDCtrlDlg::OnBnClickedButtonwritehdus)
	ON_BN_CLICKED(IDC_BUTTON_ConEXP, &CCCDCtrlDlg::OnBnClickedButtonConexp)
	ON_BN_CLICKED(IDC_BUTTON_StopConEXP, &CCCDCtrlDlg::OnBnClickedButtonStopconexp)

	ON_MESSAGE(WM_TAKESNAPSHOTCPLT, &CCCDCtrlDlg::OnTakeSnapshotCplt)
	ON_MESSAGE(WM_SETIMGSAVPATHCPLT, &CCCDCtrlDlg::OnSetImgSavPathCplt)
	ON_MESSAGE(WM_GETCCDSTATUSCPLT, &CCCDCtrlDlg::OnGetCcdStatusCplt)
	ON_MESSAGE(WM_ABORTEXPCPLT, &CCCDCtrlDlg::OnAbortExpCplt)
	ON_MESSAGE(WM_SETCOOLERTMPCPLT, &CCCDCtrlDlg::OnSetCoolerTmpCplt)
	ON_MESSAGE(WM_GETCOOLERTMPCPLT, &CCCDCtrlDlg::OnGetCoolerTmpCplt)
	ON_MESSAGE(WM_STARTCOOLERCPLT, &CCCDCtrlDlg::OnStartCoolerCplt)
	ON_MESSAGE(WM_STOPCOOLERCPLT, &CCCDCtrlDlg::OnStopCoolerCplt)
	ON_MESSAGE(WM_SETFANSPEEDCPLT, &CCCDCtrlDlg::OnSetFanSpdCplt)
	ON_MESSAGE(WM_SHUTSVRCPLT, &CCCDCtrlDlg::OnShutSvrCplt)
	ON_MESSAGE(WM_SETIMGHEADINFOCPLT, &CCCDCtrlDlg::OnSetImgHeadInfoCplt)
	ON_MESSAGE(WM_TAKESNAPSHOTSLEEPCPLT, &CCCDCtrlDlg::OnTakeSnapshotSleepCplt)
	ON_MESSAGE(WM_WRITEHDUCPLT, &CCCDCtrlDlg::OnWriteHDUCplt)
	ON_MESSAGE(WM_STOPTAKESNAPSHOTCONCPLT, &CCCDCtrlDlg::OnTakeSnapshotConCplt)

	ON_EN_CHANGE(IDC_EDIT_FeedBack, &CCCDCtrlDlg::OnChangeEditFeedback)
	ON_BN_CLICKED(IDC_BUTTON_DARK, &CCCDCtrlDlg::OnBnClickedButtonDark)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CCCDCtrlDlg 消息处理程序

//给工作线程发送消息，连接CCD控制机
void CCCDCtrlDlg::OnBnClickedButtonConnccd()
{
	//执行命令
	CString ip;
	UINT port;
	UpdateData(TRUE);
	m_ipAddressCcd.GetWindowTextA(ip);
	port = m_portCcd;
	//m_ccdCtrl.SetIPAndPort(ip, port);
	//m_ccdCtrl.Connect();

	
	m_u9000Params.ip = ip;
	m_u9000Params.port = port;
	m_pThrd->PostThreadMessageA(WM_SETIPANDPORT, 0, 0);
	m_pThrd->PostThreadMessageA(WM_CONNECT, 0, 0);


}

//给工作线程发送消息，断开与CCD控制机的连接
void CCCDCtrlDlg::OnBnClickedButtonDisconnccd()
{
	//m_ccdCtrl.DisConnect();
	m_pThrd->PostThreadMessageA(WM_DISCONNECT, 0, 0);
}


//给工作线程发送消息，设置图像存储路径
void CCCDCtrlDlg::OnBnClickedButtonSavpath()
{
	//执行命令
	UpdateData(TRUE);
	
	m_u9000Params.stSetImgSavPath.path = m_imgSavPath;
	m_pThrd->PostThreadMessageA(WM_SETIMGSAVPATH, 0, 0);
	
	
}

//给工作线程发送消息，单帧拍照
void CCCDCtrlDlg::OnBnClickedButtonExp()
{
	//按下按钮失效
	/*CButton* pBtn = (CButton*)GetDlgItem(IDC_BUTTON_EXP);
	if (NULL != pBtn)
	{
	pBtn->EnableWindow(FALSE);
	}*/

	UpdateData(TRUE);
	//准备曝光参数
	m_u9000Params.stTakeSnapshot.fileName = m_imgName;
	m_u9000Params.stTakeSnapshot.expTime = m_expTime;
	if (m_shutterStatus.GetCheck() == BST_CHECKED)
	{
		m_u9000Params.stTakeSnapshot.shutter = TRUE;
	}
	else
	{
		m_u9000Params.stTakeSnapshot.shutter = FALSE;
	}
	m_u9000Params.stTakeSnapshot.fileNameSu = m_imgNameSu;

	//准备FitsHDUs信息
	m_ccdtype = "OBJECT";
	GetRealHDUs();
	SetHDUs();

	m_pThrd->PostThreadMessageA(WM_TAKESNAPSHOT, 0, 0);
}

//给工作线程发送消息，终止曝光
void CCCDCtrlDlg::OnBnClickedButtonStopexp()
{
	UpdateData(TRUE);
	m_pThrd->PostThreadMessageA(WM_ABORTEXP, 0, 0);

}

//给工作线程发送消息，设置风扇速度
void CCCDCtrlDlg::OnBnClickedButtonFanfast()
{
	
	UpdateData(TRUE);
	m_u9000Params.stSetFanSpd.fanLvl = "fast";
	m_pThrd->PostThreadMessageA(WM_SETFANSPEED, 0, 0);
	
}

//给工作线程发送消息，设置风扇速度
void CCCDCtrlDlg::OnBnClickedButtonFanmed()
{
	UpdateData(TRUE);
	m_u9000Params.stSetFanSpd.fanLvl = "medium";
	m_pThrd->PostThreadMessageA(WM_SETFANSPEED, 0, 0);

}

//给工作线程发送消息，设置风扇速度
void CCCDCtrlDlg::OnBnClickedButtonFanslow()
{

	UpdateData(TRUE);
	m_u9000Params.stSetFanSpd.fanLvl = "slow";
	m_pThrd->PostThreadMessageA(WM_SETFANSPEED, 0, 0);

}

//给工作线程发送消息，设置风扇速度
void CCCDCtrlDlg::OnBnClickedButtonFanoff()
{
	UpdateData(TRUE);
	m_u9000Params.stSetFanSpd.fanLvl = "off";
	m_pThrd->PostThreadMessageA(WM_SETFANSPEED, 0, 0);
}


BOOL CCCDCtrlDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ipAddressCcd.SetAddress(190, 168, 1, 11);
	m_portCcd = 2001;
	m_imgName = "m01";
	m_expTime = 10;
	m_imgSavPath = "/data/";
	
	m_simple = "T";
	m_bitpix = "-32";
	m_naxis = "2";
	m_naxis1 = "3056";
	m_naxis2 = "3056";
	m_bscale = "1.0";
	m_bzero = "32768.0";

	m_imageID = "130725165823XM1ABO0";
	m_ccdtype = "OBJECT";               
	m_dateObs = "2013-07-25";          //自动获取
	m_timeObs = "16:58:23.00";         //自动获取
	m_timeEnd = "00:00:01.00";         //自动获取
	m_dateObsUT = "2013-07-25";        //自动获取
	m_timeObsUT = "08:58:23.00";       //自动获取
	m_timeEndUT = "00:00:01.00";       //自动获取
	m_expTimeHDU = "01.00";            //自动获取
	//m_ra = "15:23:45.21";              //从上位机获得
	//m_dec = "46:00:00.0";              //从上位机获得
	//m_azimuth = "74:00:00";            //从上位机获得
	//m_elevation = "35:00:00";          //从上位机获得
	m_epoch = "J2000";

	m_wacID = "XM";                   //自动生成
	m_mountID = "1";                  //自动生成
	m_camid = "2";                    //手动输入
	m_ccdid = "2";                    //手动输入

	m_ccdsize = "3056x3056";
	m_gain = "";
	m_readRate = "00.00";			   //手动输入
	m_readOutNoise = "10";            //手动输入
	m_temperatureSet = "-30";         //自动获得
	m_temperatureAct = "00.0";         //自动获得

	m_moonPhase = "";                  //手动输入
	m_moonAngle = "";                  //手动输入
	m_weather = "";               //手动输入

	m_pixelScale = "26.0";
	m_locst = "5";

	m_airmass = "";                 //手动输入
	m_fitsize = "";             
	m_JD = "";
	m_observer = "MiniGWAC";                //手动输入

	

	GetRealHDUs();

	m_feedback = "请连接后先设置图像保存路径后再拍照！\r\n";

	m_imgNameSu = 1;

	CString title;
	//title.Format("WAC%d-CCD%d CCD Control ", m_titleWacID+1, m_titleCcdID+1);
	title.Format("CCD%d Control", m_titleCcdID+1);
	this->SetWindowTextA(title);

	UpdateData(FALSE);

	//启动CCD控制工作线程	
	m_pThrd = (CMyThread *)AfxBeginThread(RUNTIME_CLASS(CMyThread));
	m_pThrd->m_pThreadParams = &m_u9000Params;
	m_pThrd->m_pMainWnd = this;

	m_shutterStatus.SetCheck(BST_CHECKED);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

//给工作线程发送消息，设置制冷器温度
void CCCDCtrlDlg::OnBnClickedButtonSetcoolertem()
{
	
	UpdateData(TRUE);
	m_u9000Params.stSetCoolerTmp.tmp = m_setCoolerTem;
	m_pThrd->PostThreadMessageA(WM_SETCOOLERTMP, 0, 0);

	
}

//给工作线程发送消息，获取制冷器温度
void CCCDCtrlDlg::OnBnClickedButtonGetcoolertem()
{
	m_u9000Params.stGetCoolerTmp.tmp = 0;
	m_pThrd->PostThreadMessageA(WM_GETCOOLERTMP, 0, 0);

}

//给工作线程发送消息，开启制冷器
void CCCDCtrlDlg::OnBnClickedButtonStartcooler()
{
	m_pThrd->PostThreadMessageA(WM_STARTCOOLER, 0, 0);

	
}

//给工作线程发送消息，停止制冷器
void CCCDCtrlDlg::OnBnClickedButtonStopcooler()
{
	
	m_pThrd->PostThreadMessageA(WM_STOPCOOLER, 0, 0);
	
}

//给工作线程发送消息，获取CCD状态
void CCCDCtrlDlg::OnBnClickedButtonGetu9000status()
{
	m_pThrd->PostThreadMessageA(WM_GETCCDSTATUS, 0, 0);
}

//
//void CCCDCtrlDlg::OnBnClickedButtonwritehdus()
//{
//	//如果已经连接成功
//
//	WriteHDUs();
//}

//
//void CCCDCtrlDlg::WriteHDUs()
//{
//	CString res;
//	CString fileName;
//	fileName.Format("%s/%s.fits", m_imgSavPath, m_imgName);
//	UpdateData(TRUE);
///*
//	m_ccdCtrl.WriteHDU(fileName, "SIMPLE", m_simple, res);
//	m_ccdCtrl.WriteHDU(fileName, "BITPIX", m_bitpix, res);
//	m_ccdCtrl.WriteHDU(fileName, "NAXIS", m_naxis, res);
//	m_ccdCtrl.WriteHDU(fileName, "NAXIS1", m_naxis1, res);
//	m_ccdCtrl.WriteHDU(fileName, "NAXIS2", m_naxis2, res);
//	m_ccdCtrl.WriteHDU(fileName, "BSCALE", m_bscale, res);
//	m_ccdCtrl.WriteHDU(fileName, "BZERO", m_bzero, res);
//*/
//	m_ccdCtrl.WriteHDU(fileName, "IMAGEID", m_imageID, res);
//	m_ccdCtrl.WriteHDU(fileName, "CCDTYPE", m_ccdtype, res);
//	m_ccdCtrl.WriteHDU(fileName, "DATE-OBS", m_dateObs, res);
//	m_ccdCtrl.WriteHDU(fileName, "TIME-OBS", m_timeObs, res);
//	m_ccdCtrl.WriteHDU(fileName, "TIME-END", m_timeEnd, res);
//	m_ccdCtrl.WriteHDU(fileName, "DATE-OBS-UT", m_dateObsUT, res);
//	m_ccdCtrl.WriteHDU(fileName, "TIME-OBS-UT", m_timeObsUT, res);
//	m_ccdCtrl.WriteHDU(fileName, "TIME-END-UT", m_timeEndUT, res);
//	
//	//m_expTimeHDU.Format("%s", m_expTime);
//	m_ccdCtrl.WriteHDU(fileName, "EXPTIME", m_expTimeHDU, res);
//	m_ccdCtrl.WriteHDU(fileName, "RA", m_ra, res);
//	m_ccdCtrl.WriteHDU(fileName, "DEC", m_dec, res);
//	m_ccdCtrl.WriteHDU(fileName, "EPOCH", m_epoch, res);
//
//	m_ccdCtrl.WriteHDU(fileName, "WACID", m_wacID, res);
//	m_ccdCtrl.WriteHDU(fileName, "MOUNTID", m_mountID, res);
//	m_ccdCtrl.WriteHDU(fileName, "CAMID", m_camid, res);
//	m_ccdCtrl.WriteHDU(fileName, "CCDID", m_ccdid, res);
//
//	m_ccdCtrl.WriteHDU(fileName, "CCDSIZE", m_ccdsize, res);
//	m_ccdCtrl.WriteHDU(fileName, "GAIN", m_gain, res);
//	m_ccdCtrl.WriteHDU(fileName, "READRATE", m_readRate, res);
//	m_ccdCtrl.WriteHDU(fileName, "READOUTNOISE", m_readOutNoise, res);
//	m_ccdCtrl.WriteHDU(fileName, "TEMPRATURESET", m_temperatureSet, res);
//	m_ccdCtrl.WriteHDU(fileName, "TEMPRATUREACT", m_temperatureAct, res);
//
//	m_ccdCtrl.WriteHDU(fileName, "MOONPHASE", m_moonPhase, res);
//	m_ccdCtrl.WriteHDU(fileName, "MOONANGLE", m_moonAngle, res);
//	m_ccdCtrl.WriteHDU(fileName, "WEATHER", m_weather, res);
//
//	m_ccdCtrl.WriteHDU(fileName, "PIXELSCALE", m_pixelScale, res);
//	m_ccdCtrl.WriteHDU(fileName, "LOCST", m_locst, res);
//	m_ccdCtrl.WriteHDU(fileName, "AZIMUTH", m_azimuth, res);
//	m_ccdCtrl.WriteHDU(fileName, "ELEVATION", m_elevation, res);
//	m_ccdCtrl.WriteHDU(fileName, "AIRMASS", m_airmass, res);
//
//	m_ccdCtrl.WriteHDU(fileName, "FITSIZE", m_fitsize, res);
//	m_ccdCtrl.WriteHDU(fileName, "JD", m_JD, res);
//
//	m_ccdCtrl.WriteHDU(fileName, "OBSERVER", m_observer, res);
//
//}

//单帧拍照完成后处理
LRESULT CCCDCtrlDlg::OnTakeSnapshotCplt(WPARAM wParam,LPARAM lParam)
{

	CString res;
	res = m_u9000Params.stTakeSnapshot.res;
	m_imgNameSu = m_u9000Params.stTakeSnapshot.fileNameSu;
	//DWORD ip;
	//m_ipAddressCcd.GetAddress(ip);
	//res.AppendFormat("%u:%s/%s.fits",ip, m_imgSavPath, m_u9000Params.stTakeSnapshot.fileName);
	m_dateObs = m_u9000Params.stFitsHDUs.dateObs;
	m_timeObs = m_u9000Params.stFitsHDUs.timeObs;
	m_timeEnd = m_u9000Params.stFitsHDUs.timeEnd;

	m_dateObsUT = m_u9000Params.stFitsHDUs.dateObsUT;
	m_timeObsUT = m_u9000Params.stFitsHDUs.timeObsUT;
	m_timeEndUT = m_u9000Params.stFitsHDUs.timeEndUT;

	m_temperatureAct = m_u9000Params.stFitsHDUs.temperatureAct;
	m_temperatureSet = m_u9000Params.stFitsHDUs.temperatureSet;

	m_imageID = m_u9000Params.stFitsHDUs.imageID;
	//显示反馈

	res.Format("%s %s_%04d", res, m_imgName, m_imgNameSu);
	
	UpdateFeedBack(res);

	/*CButton* pBtn = (CButton*)GetDlgItem(IDC_BUTTON_EXP);
	if (NULL != pBtn)
	{
		pBtn->EnableWindow(TRUE);
	}*/
	SaveCCDParams( m_titleCcdID);
	return 0;
}

//设置图像存储路径完成后处理
LRESULT CCCDCtrlDlg::OnSetImgSavPathCplt( WPARAM wParam,LPARAM lParam )
{
	CString res;
	res = m_u9000Params.stSetImgSavPath.res;
	if(-1 != m_u9000Params.stSetImgSavPath.status)
	{
		//显示反馈
		SYSTEMTIME sysTime;
		GetLocalTime(&sysTime);
		CString tm;
		tm.Format("%4d-%02d-%02d %02d:%02d:%02d.%03d", sysTime.wYear, sysTime.wMonth, sysTime.wDay,
			sysTime.wHour, sysTime.wMinute, sysTime.wSecond, sysTime.wMilliseconds);
		m_feedback.AppendFormat("%s: %s", tm, res);
		UpdateData(FALSE);
		CEdit *pEdit = (CEdit*)GetDlgItem(IDC_EDIT_FeedBack);
		pEdit->SetSel(0, -1);
	}
	else
	{
		//显示反馈
		res = "设置图像存储路径失败！";
		UpdateFeedBack(res);
	}
	return 0;
}

//终止曝光完成后处理
LRESULT CCCDCtrlDlg::OnAbortExpCplt( WPARAM wParam,LPARAM lParam )
{
	CString res;
	res = m_u9000Params.stAbortExp.res;
	//显示反馈
	UpdateFeedBack(res);
	return 0;
}

//设置风扇速度后处理
LRESULT CCCDCtrlDlg::OnSetFanSpdCplt( WPARAM wParam,LPARAM lParam )
{
	CString res;
	res = m_u9000Params.stSetFanSpd.res;
	//显示反馈
	UpdateFeedBack(res);
	return 0;
}

//设置制冷器温度完成后处理
LRESULT CCCDCtrlDlg::OnSetCoolerTmpCplt( WPARAM wParam,LPARAM lParam )
{
	CString res;
	res = m_u9000Params.stSetCoolerTmp.res;
	m_temperatureSet.Format("%.6f", m_setCoolerTem);
	//显示反馈
	UpdateFeedBack(res);
	return 0;
}

//开始制冷器完成后处理
LRESULT CCCDCtrlDlg::OnStartCoolerCplt( WPARAM wParam,LPARAM lParam )
{
	CString res;
	res = m_u9000Params.stStartCooler.res;
	//显示反馈
	UpdateFeedBack(res);
	return 0;
}

//停止制冷器完成后处理
LRESULT CCCDCtrlDlg::OnStopCoolerCplt( WPARAM wParam,LPARAM lParam )
{
	CString res;
	res = m_u9000Params.stStopCooler.res;
	//显示反馈
	UpdateFeedBack(res);
	return 0;
}

//获取制冷器温度完成后处理
LRESULT CCCDCtrlDlg::OnGetCoolerTmpCplt( WPARAM wParam,LPARAM lParam )
{
	CString res;
	res = m_u9000Params.stGetCoolerTmp.res;
	m_getCoolerTem = m_u9000Params.stGetCoolerTmp.tmp;
	m_temperatureSet.Format("%.6f", m_getCoolerTem);
	//显示反馈
	UpdateFeedBack(res);
	return 0;
}

//获取CCD状态完成后处理
LRESULT CCCDCtrlDlg::OnGetCcdStatusCplt( WPARAM wParam,LPARAM lParam )
{
	CString res;
	res = m_u9000Params.stGetCcdStatus.res;
	if(-1 != m_u9000Params.stGetCcdStatus.status)
	{
		//获得制冷器实际温度
		int pos = -1;
		pos = res.Find(' ');
		m_temperatureAct.Format("%.6s", res.Left(pos));

		//显示反馈
		SYSTEMTIME sysTime;
		GetLocalTime(&sysTime);
		CString tm;
		tm.Format("%4d-%02d-%02d %02d:%02d:%02d.%03d", sysTime.wYear, sysTime.wMonth, sysTime.wDay,
			sysTime.wHour, sysTime.wMinute, sysTime.wSecond, sysTime.wMilliseconds);
		m_feedback.AppendFormat("%s: %s", tm, res);
		
		UpdateData(FALSE);
		CEdit *pEdit = (CEdit*)GetDlgItem(IDC_EDIT_FeedBack);
		pEdit->SetSel(0, -1);
	}
	else
	{
		//显示反馈
		CString res = "获取U9000当前状态失败！";
		UpdateFeedBack(res);
	}
	return 0;
}

LRESULT CCCDCtrlDlg::OnWriteHDUCplt( WPARAM wParam,LPARAM lParam )
{
	return 0;
}

LRESULT CCCDCtrlDlg::OnTakeSnapshotSleepCplt( WPARAM wParam,LPARAM lParam )
{
	return 0;
}

LRESULT CCCDCtrlDlg::OnShutSvrCplt( WPARAM wParam,LPARAM lParam )
{
	return 0;
}

LRESULT CCCDCtrlDlg::OnSetImgHeadInfoCplt( WPARAM wParam,LPARAM lParam )
{
	return 0;
}



//开始多帧拍摄
void CCCDCtrlDlg::OnBnClickedButtonConexp()
{
	UpdateData(TRUE);
	
	//准备曝光参数
	m_u9000Params.stTakeSnapshot.fileName = m_imgName;
	m_u9000Params.stTakeSnapshot.expTime = m_expTime;
	if (m_shutterStatus.GetCheck() == BST_CHECKED)
	{
		m_u9000Params.stTakeSnapshot.shutter = TRUE;
	}
	else
	{
		m_u9000Params.stTakeSnapshot.shutter = FALSE;
	}
	m_u9000Params.stTakeSnapshot.fileNameSu = m_imgNameSu;

	//准备FitsHDUs信息
	GetRealHDUs();
	SetHDUs();

	CString res = "连续拍照开始！";

	UpdateFeedBack(res);

	m_pThrd->m_conTakeSnapshot = TRUE;
	m_pThrd->PostThreadMessageA(WM_TAKESNAPSHOTCON, 0, 0);
	
}

//停止多帧
void CCCDCtrlDlg::OnBnClickedButtonStopconexp()
{
	m_pThrd->m_conTakeSnapshot = FALSE;
	//m_pThrd->PostThreadMessageA(WM_STOPTAKESNAPSHOTCON, 0, 0);
}



//拍照结束后处理
LRESULT CCCDCtrlDlg::OnTakeSnapshotConCplt( WPARAM wParam,LPARAM lParam )
{
	CString res = "连续拍照结束！";
	m_imgNameSu = m_u9000Params.stTakeSnapshot.fileNameSu;

	UpdateFeedBack(res);
	SaveCCDParams( m_titleCcdID);
	return 0;
}


void CCCDCtrlDlg::OnChangeEditFeedback()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	
}

//更新反馈信息
void CCCDCtrlDlg::UpdateFeedBack( CString res )
{
	SYSTEMTIME sysTime;
	GetLocalTime(&sysTime);
	CString tm;
	tm.Format("%4d-%02d-%02d %02d:%02d:%02d.%03d", sysTime.wYear, sysTime.wMonth, sysTime.wDay,
		sysTime.wHour, sysTime.wMinute, sysTime.wSecond, sysTime.wMilliseconds);
	m_feedback.AppendFormat("%s: %s\r\n", tm, res);

	UpdateData(FALSE);

	CEdit *pEdit = (CEdit*)GetDlgItem(IDC_EDIT_FeedBack);
	pEdit->SetSel(0, -1);

	//保存feedback到日志文件
	CString logRow;
	logRow.Format("%s: %s\r\n", tm, res);
	SaveFeedbkToLog( m_titleCcdID, logRow);
}

void CCCDCtrlDlg::SetHDUs()
{
	m_u9000Params.stFitsHDUs.simple = m_simple;
	m_u9000Params.stFitsHDUs.bitpix = m_bitpix;
	m_u9000Params.stFitsHDUs.naxis = m_naxis;
	m_u9000Params.stFitsHDUs.naxis1 = m_naxis1;
	m_u9000Params.stFitsHDUs.naxis2 = m_naxis2;
	m_u9000Params.stFitsHDUs.bscale = m_bscale;
	m_u9000Params.stFitsHDUs.bzero = m_bzero;

	m_u9000Params.stFitsHDUs.imageID = m_imageID;
	m_u9000Params.stFitsHDUs.ccdtype = m_ccdtype;
	m_u9000Params.stFitsHDUs.dateObs = m_dateObs;
	m_u9000Params.stFitsHDUs.timeObs = m_timeObs;
	m_u9000Params.stFitsHDUs.timeEnd = m_timeEnd;
	m_u9000Params.stFitsHDUs.dateObsUT = m_dateObsUT;
	m_u9000Params.stFitsHDUs.timeObsUT = m_timeObsUT;
	m_u9000Params.stFitsHDUs.timeEndUT = m_timeEndUT;
	m_u9000Params.stFitsHDUs.expTimeHDU = m_expTimeHDU;
	m_u9000Params.stFitsHDUs.ra = m_ra;
	m_u9000Params.stFitsHDUs.dec = m_dec;
	m_u9000Params.stFitsHDUs.epoch = m_epoch;

	m_u9000Params.stFitsHDUs.wacID = m_wacID;
	m_u9000Params.stFitsHDUs.mountID = m_mountID;
	m_u9000Params.stFitsHDUs.camid = m_camid;
	m_u9000Params.stFitsHDUs.ccdid = m_ccdid;

	m_u9000Params.stFitsHDUs.ccdsize = m_ccdsize;
	m_u9000Params.stFitsHDUs.gain = m_gain;
	m_u9000Params.stFitsHDUs.readRate = m_readRate;
	m_u9000Params.stFitsHDUs.readOutNoise = m_readOutNoise;
	m_u9000Params.stFitsHDUs.temperatureSet = m_temperatureSet;
	m_u9000Params.stFitsHDUs.temperatureAct = m_temperatureAct;

	m_u9000Params.stFitsHDUs.moonPhase = m_moonPhase;
	m_u9000Params.stFitsHDUs.moonAngle = m_moonAngle;
	m_u9000Params.stFitsHDUs.weather = m_weather;

	m_u9000Params.stFitsHDUs.pixelScale = m_pixelScale;
	m_u9000Params.stFitsHDUs.locst = m_locst;
	m_u9000Params.stFitsHDUs.azimuth = m_azimuth;
	m_u9000Params.stFitsHDUs.elevation = m_elevation;
	m_u9000Params.stFitsHDUs.airmass = m_airmass;
	m_u9000Params.stFitsHDUs.fitsize = m_fitsize;
	m_u9000Params.stFitsHDUs.JD = m_JD;
	m_u9000Params.stFitsHDUs.observer = m_observer;

	m_u9000Params.stFitsHDUs.latitude = m_latitude;
	m_u9000Params.stFitsHDUs.longitude = m_longitude;
	m_u9000Params.stFitsHDUs.site = m_site;
	m_u9000Params.stFitsHDUs.target = m_target;
}


void CCCDCtrlDlg::OnBnClickedButtonDark()
{
	UpdateData(TRUE);
	//准备曝光参数
	m_u9000Params.stTakeSnapshot.fileName = m_imgName;
	m_u9000Params.stTakeSnapshot.expTime = 0.0;
	m_u9000Params.stTakeSnapshot.shutter = FALSE;
	m_u9000Params.stTakeSnapshot.fileNameSu = m_imgNameSu;

	m_expTimeHDU.Format("%f", m_u9000Params.stTakeSnapshot.expTime);
	//准备FitsHDUs信息
	m_ccdtype = "DARK";
	GetRealHDUs();
	SetHDUs();

	m_pThrd->PostThreadMessageA(WM_TAKESNAPSHOT, 0, 0);
}

//重载以去掉多线程传递对象指针，这里没有问题
void CCCDCtrlDlg::AssertValid() const
{
	if (m_hWnd == NULL)
		return;     // null (unattached) windows are valid

	// check for special wnd??? values
	ASSERT(HWND_TOP == NULL);       // same as desktop
	if (m_hWnd == HWND_BOTTOM)
		ASSERT(this == &CWnd::wndBottom);
	else if (m_hWnd == HWND_TOPMOST)
		ASSERT(this == &CWnd::wndTopMost);
	else if (m_hWnd == HWND_NOTOPMOST)
		ASSERT(this == &CWnd::wndNoTopMost);
	else
	{
		// should be a normal window
		ASSERT(::IsWindow(m_hWnd));

		// should also be in the permanent or temporary handle map
/*		CHandleMap* pMap = afxMapHWND();
		ASSERT(pMap != NULL);

		CObject* p=NULL;
		if(pMap)
		{
			ASSERT( (p = pMap->LookupPermanent(m_hWnd)) != NULL ||
				(p = pMap->LookupTemporary(m_hWnd)) != NULL);
		}
		ASSERT((CWnd*)p == this);   // must be us
*/
		// Note: if either of the above asserts fire and you are
		// writing a multithreaded application, it is likely that
		// you have passed a C++ object from one thread to another
		// and have used that object in a way that was not intended.
		// (only simple inline wrapper functions should be used)
		//
		// In general, CWnd objects should be passed by HWND from
		// one thread to another.  The receiving thread can wrap
		// the HWND with a CWnd object by using CWnd::FromHandle.
		//
		// It is dangerous to pass C++ objects from one thread to
		// another, unless the objects are designed to be used in
		// such a manner.
	}
}

void CCCDCtrlDlg::GetRealHDUs()
{
	SYSTEMTIME utcTime, localTime;
	GetLocalTime(&localTime);
	GetSystemTime(&utcTime);

	GetLocalTime(&localTime);
	m_dateObs.Format("%4d-%02d-%02d", localTime.wYear, localTime.wMonth, localTime.wDay);
	m_timeObs.Format("%02d:%02d:%02d.%02.2d", localTime.wHour, localTime.wMinute, localTime.wSecond, localTime.wMilliseconds);
	//GetLocalTime(&localTime);
	//m_timeEnd.Format("%02d:%02d:%02d.%02.2d", localTime.wHour, localTime.wMinute, localTime.wSecond, localTime.wMilliseconds);
	
	GetSystemTime(&utcTime);
	m_dateObsUT.Format("%4d-%02d-%02d", utcTime.wYear, utcTime.wMonth, utcTime.wDay);
	m_timeObsUT.Format("%02d:%02d:%02d.%02.2d", utcTime.wHour, utcTime.wMinute, utcTime.wSecond, utcTime.wMilliseconds);
	//GetSystemTime(&utcTime);
	//m_timeEndUT.Format("%02d:%02d:%02d.%02.2d", utcTime.wHour, utcTime.wMinute, utcTime.wSecond, utcTime.wMilliseconds);

	
	m_expTimeHDU.Format("%.2f", m_expTime);
	//m_azimuth = "74:00:00";            //从上位机获得
	//m_elevation = "35:00:00";          //从上位机获得
	//m_ra = "15:23:45.21";              //从上位机获得
	//m_dec = "46:00:00.0";              //从上位机获得
	m_epoch = "2000";

	m_wacID.Format("XM");
	m_ccdid.Format("%c", m_titleCcdID +'A');

	m_ccdsize = "3056x3056";
	m_gain = "";

	m_mountID.Format("%d", m_titleCcdID/2 + 1);//手动输入
	m_camid = m_camera;                //手动输入
	m_readRate = "";			   //手动输入
	m_readOutNoise = "";            //手动输入
	m_moonPhase = "";                  //手动输入
	m_moonAngle = "";                  //手动输入
	m_weather = "";               //手动输入
	m_airmass = "";                 //手动输入
	m_observer = "MiniGWAC";                //手动输入

	m_latitude = "40:45:17.88";
	m_longitude = "117:71:97.22";
	m_site = "bao";
	m_target = "release";

	//m_imageID = "130725165823XM1ABO0";
	//date(6)-time(6)-wac(2)-mount(1)-camera(1)-ccd(1)-ccdtype(1)-product level(1)
	m_imageID.Format("%02d%02d%02d%02d%02d%02dXM%s%s%s%s%s", localTime.wYear%100, localTime.wMonth, localTime.wDay, 
		localTime.wHour, localTime.wMinute, localTime.wSecond,
		m_mountID.Right(1), m_camid.Right(1), m_ccdid.Right(1), m_ccdtype.Left(1), m_prdtLvl);

}

void CCCDCtrlDlg::GetTem()
{
	m_temperatureSet = "-30";         //自动获得


	//m_temperatureAct = "00.0";         //自动获得
	//if(m_pThrd->m_ccdCtrl.sStatus == TRUE)
	//	m_pThrd->PostThreadMessageA(WM_GETCOOLERTMP, 0, 0);
}


void CCCDCtrlDlg::OnClose()
{
	//AfxMessageBox("onClose called.");
	SaveCCDParams(m_titleCcdID);
	CDialog::OnClose();
}

//将CCD界面的参数保存到XML文件
void CCCDCtrlDlg::SaveCCDParams( int ccdID )
{
	CMarkup xmlMiniGWAC;
	BOOL bLoadXML;
	BOOL bFindXML;
	bLoadXML = xmlMiniGWAC.Load("MiniGWAC.xml");
	CString ccdName, ipAddr, port, imgSavPath, expTime, shutterStatus, imgName, imgNameSu, setCoolerTem;
	BYTE bt1, bt2, bt3, bt4;
	CString xmlNode = "CCDCtrlParams";

	//准备要写入的数据
	UpdateData(TRUE);
	ccdName.Format("m%02d", ccdID + 1);
	m_ipAddressCcd.GetAddress(bt1, bt2, bt3, bt4);
	ipAddr.Format("%d:%d:%d:%d", bt1, bt2, bt3, bt4);
	port.Format("%d", m_portCcd);
	imgSavPath = m_imgSavPath;
	expTime.Format("%.3f", m_expTime);
	if (m_shutterStatus.GetCheck() == BST_CHECKED)
	{
		shutterStatus = '1';
	}
	else if(m_shutterStatus.GetCheck() == BST_UNCHECKED)
	{
		shutterStatus = '0';
	}
	imgName = m_imgName;
	imgNameSu.Format("%d", m_imgNameSu);
	setCoolerTem.Format("%.3f", m_setCoolerTem);
	

	//写入数据
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
				
				xmlMiniGWAC.SetAttrib("CoolerTem", setCoolerTem);
				xmlMiniGWAC.SetAttrib("ImgSuffix", imgNameSu);
				xmlMiniGWAC.SetAttrib("ImgName", imgName);
				xmlMiniGWAC.SetAttrib("ShutterStatus", shutterStatus);
				xmlMiniGWAC.SetAttrib("ExpTime", expTime);
				xmlMiniGWAC.SetAttrib("ImgSavPath", imgSavPath);
				xmlMiniGWAC.SetAttrib("Port", port);
				xmlMiniGWAC.SetAttrib("IPAddress", ipAddr);
			}
			else
			{
				xmlMiniGWAC.AddElem(ccdName);

				xmlMiniGWAC.AddAttrib("CoolerTem", setCoolerTem);
				xmlMiniGWAC.AddAttrib("ImgSuffix", imgNameSu);
				xmlMiniGWAC.AddAttrib("ImgName", imgName);
				xmlMiniGWAC.AddAttrib("ShutterStatus", shutterStatus);
				xmlMiniGWAC.AddAttrib("ExpTime", expTime);
				xmlMiniGWAC.AddAttrib("ImgSavPath", imgSavPath);
				xmlMiniGWAC.AddAttrib("Port", port);
				xmlMiniGWAC.AddAttrib("IPAddress", ipAddr);
			}
		}
		else
		{
			xmlMiniGWAC.AddElem(xmlNode);
			xmlMiniGWAC.IntoElem();
			xmlMiniGWAC.AddElem(ccdName);

			xmlMiniGWAC.AddAttrib("CoolerTem", setCoolerTem);
			xmlMiniGWAC.AddAttrib("ImgSuffix", imgNameSu);
			xmlMiniGWAC.AddAttrib("ImgName", imgName);
			xmlMiniGWAC.AddAttrib("ShutterStatus", shutterStatus);
			xmlMiniGWAC.AddAttrib("ExpTime", expTime);
			xmlMiniGWAC.AddAttrib("ImgSavPath", imgSavPath);
			xmlMiniGWAC.AddAttrib("Port", port);
			xmlMiniGWAC.AddAttrib("IPAddress", ipAddr);
		}
		
	}
	else
	{
		xmlMiniGWAC.SetDoc("<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
		xmlMiniGWAC.AddElem(xmlNode);
		xmlMiniGWAC.IntoElem();
		xmlMiniGWAC.AddElem(ccdName);
		

		xmlMiniGWAC.AddAttrib("CoolerTem", setCoolerTem);
		xmlMiniGWAC.AddAttrib("ImgSuffix", imgNameSu);
		xmlMiniGWAC.AddAttrib("ImgName", imgName);
		xmlMiniGWAC.AddAttrib("ShutterStatus", shutterStatus);
		xmlMiniGWAC.AddAttrib("ExpTime", expTime);
		xmlMiniGWAC.AddAttrib("ImgSavPath", imgSavPath);
		xmlMiniGWAC.AddAttrib("Port", port);
		xmlMiniGWAC.AddAttrib("IPAddress", ipAddr);
	}
	
	xmlMiniGWAC.OutOfElem();
	xmlMiniGWAC.Save("MiniGWAC.xml");


}


BOOL CCCDCtrlDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(pMsg->message == WM_KEYDOWN   &&   pMsg->wParam == VK_ESCAPE)     return   TRUE;   
	if(pMsg->message == WM_KEYDOWN   &&   pMsg->wParam == VK_RETURN)     return   TRUE;     
	else
		return CDialog::PreTranslateMessage(pMsg);
}

void CCCDCtrlDlg::SaveFeedbkToLog(  int ccdID, CString logInfo )
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




HBRUSH CCCDCtrlDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	switch(nCtlColor)
	{
	case CTLCOLOR_STATIC:  //radio为static类型控件
		if (pWnd->GetDlgCtrlID()==IDC_CHECK_ShutterStatus)//其中IDC_RADIO_MY
			//为radio控件ID
			pDC->SetTextColor(RGB(255, 0, 0));//设置字体颜色

	}

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
