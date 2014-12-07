// U9000DLLmfc.h : U9000DLLmfc DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include <afxsock.h>
#include "MySocket.h"


// CU9000DLLmfcApp
// �йش���ʵ�ֵ���Ϣ������� U9000DLLmfc.cpp
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
//U9000������
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
	//1.����
	int TakeSnapshot(CString fileName, float expTime, BOOL shutter, CString &res);
	//2.����ͼ��洢Ŀ¼
	int SetImgSavPath(CString path, CString &res);
	//3.��ȡU9000��ǰ״̬
	int GetCcdStatus(CString &res);
	
	//4.��ֹ�ع�
	int AbortExp(CString &res);
	//5.���������¶�
	int SetCoolerTmp(int tmp, CString &res);
	//6.��ȡ�����¶�
	int GetCoolerTmp(float &tmp, CString &res);
	//7.����������
	int StartCooler(CString &res);
	//8.ֹͣ������
	int StopCooler(CString &res);
	//9.���÷����ٶ�
	int SetFanSpd(CString fanLvl, CString &res);
	//10.�رշ�����
	int ShutSvr(CString &res);

	//11.����ͼ��ͷ��Ϣ
	int SetImgHeadInfo(CString ra, CString dec, CString &res);

	//12.�ӳ����գ��ȴ����������ģ�
	int TakeSnapshotSleep(CString fileName, float expTime, BOOL shutter, CString &res);

	//13.����HDU
	int WriteHDU(CString fileName, CString keyName, CString keyValue, CString &res);

	//14.����������
	int RebootSvr(CString &res);

	//15.����Ŀ¼
	int CreateDir(CString dirName, CString &res);

	//friend int ConnectByOutside(U9000Ctrl);
};