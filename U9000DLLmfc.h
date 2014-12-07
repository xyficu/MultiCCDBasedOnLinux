// U9000DLLmfc.h : U9000DLLmfc DLL 的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
#include <afxsock.h>
#include "MySocket.h"


// CU9000DLLmfcApp
// 有关此类实现的信息，请参阅 U9000DLLmfc.cpp
//



//#include <tcl.h>
#include <direct.h>
#include <tchar.h>
#include <stdlib.h>

//#define OK 1
//#define ERROR -1

//int Tcl_AppInit(Tcl_Interp* interp);

//extern "C" _declspec(dllexport) int printHello(int argc, _TCHAR* argv[]);
//extern "C" _declspec(dllexport) int Housekeeping(char*);


//extern "C" _declspec(dllexport) int ExeCmd(CString ip, UINT port, CString cmd, CString res);
//extern "C" _declspec(dllexport) int Connect(CString ip, UINT port);
//extern "C" _declspec(dllexport) int DisConnect();


//////////////////////////////////////////////////////////////////////////
//U9000控制类
//
//////////////////////////////////////////////////////////////////////////
class U9000Ctrl
{
public:
	U9000Ctrl();
	U9000Ctrl(CString _ip, UINT _port);
	~U9000Ctrl();

public:
	int ExeCmd(CString cmd, CString &res);
	int Connect();
	int DisConnect();
	void SetIPAndPort(CString _ip, UINT _port);


public:
	BOOL sStatus;
	CMySocket *sSocket;
	CString ip;
	UINT port;

public:
	//1.拍照
	int TakeSnapshot(CString fileName, float expTime, BOOL shutter, CString &res);
	//2.设置图像存储目录
	int SetImgSavPath(CString path, CString &res);
	//3.获取U9000当前状态
	int GetCcdStatus(CString &res);
	
	//4.终止曝光
	int AbortExp(CString &res);
	//5.设置制冷温度
	int SetCoolerTmp(int tmp, CString &res);
	//6.获取制冷温度
	int GetCoolerTmp(float &tmp, CString &res);
	//7.开启制冷器
	int StartCooler(CString &res);
	//8.停止制冷器
	int StopCooler(CString &res);
	//9.设置风扇速度
	int SetFanSpd(CString fanLvl, CString &res);
	//10.关闭服务器
	int ShutSvr(CString &res);

	//11.设置图像头信息
	int SetImgHeadInfo(CString ra, CString dec, CString &res);

	//12.延迟拍照（等待到读出再拍）
	int TakeSnapshotSleep(CString fileName, float expTime, BOOL shutter, CString &res);

	//13.设置HDU
	int WriteHDU(CString fileName, CString keyName, CString keyValue, CString &res);

	//14.重启服务器
	int RebootSvr(CString &res);

	//15.创建目录
	int CreateDir(CString dirName, CString &res);

	//friend int ConnectByOutside(U9000Ctrl);
};