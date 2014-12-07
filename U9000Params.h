#pragma once

struct TakeSnapshot
{
	CString fileName;
	float expTime;
	BOOL shutter;
	CString res;
	int status;
	UINT fileNameSu;
	int snapStatus;		//0:initial status; 1:exp status; 2:readout status;
	UINT countAsn;
	UINT countCrt;
};

struct SetImgSavPath
{
	CString path;
	CString res;
	int status;
};

struct GetCcdStatus
{
	CString res;
	int status;
};

struct AbortExp
{
	CString res;
	int status;
};

struct SetCoolerTmp
{
	int tmp;
	CString res;
	int status;
};

struct GetCoolerTmp
{
	float tmp;
	CString res;
	int status;
};

struct StartCooler
{
	CString res;
	int status;
};

struct StopCooler
{
	CString res;
	int status;
};

struct SetFanSpd
{
	CString fanLvl;
	CString res;
	int status;
};

struct ShutSvr
{
	CString res;
	int status;
};

struct SetImgHeadInfo
{
	CString ra;
	CString dec;
	CString res;
	int status;
};

struct TakeSnapshotSleep
{
	CString fileName;
	float expTime;
	BOOL shutter;
	CString res;
	int status;
};

struct WriteHDU
{
	CString fileName;
	CString keyName;
	CString keyValue;
	CString res;
	int status;
};

struct FitsHDUs
{
	CString simple;
	CString bitpix;
	CString naxis;
	CString naxis1;
	CString naxis2;
	CString bscale;
	CString bzero;

	CString imageID;
	CString ccdtype;
	CString dateObs;
	CString timeObs;
	CString timeEnd;
	CString dateObsUT;
	CString timeObsUT;
	CString timeEndUT;
	CString expTimeHDU;
	CString ra;
	CString dec;
	CString epoch;

	CString wacID;
	CString mountID;
	CString camid;
	CString ccdid;

	CString ccdsize;
	CString gain;
	CString readRate;
	CString readOutNoise;
	CString temperatureSet;
	CString temperatureAct;

	CString moonPhase;
	CString moonAngle;
	CString weather;

	CString pixelScale;
	CString locst;
	CString azimuth;
	CString elevation;
	CString airmass;
	CString fitsize;
	CString JD;
	CString observer;

	CString latitude;
	CString longitude;
	CString site;
	CString target;
	CString obsMode;  // if in template mode, set to 'T'

	CString res;
	int status;
};

struct CreateDirInfo
{
	CString dirName;
	CString res;
	int status;
};

struct RebootSvrInfo
{
	CString res;
	int status;
};

struct U9000Params
{
	CString ip;
	UINT port;
	int conStus;
	int disConStus;
	int status;
	BOOL bCon;
	TakeSnapshot stTakeSnapshot;
	SetImgSavPath stSetImgSavPath;
	GetCcdStatus stGetCcdStatus;
	AbortExp stAbortExp;
	SetCoolerTmp stSetCoolerTmp;
	GetCoolerTmp stGetCoolerTmp;
	StartCooler stStartCooler;
	StopCooler stStopCooler;
	SetFanSpd stSetFanSpd;
	ShutSvr stShutSvr;
	SetImgHeadInfo stSetImgHeadInfo;
	TakeSnapshotSleep stTakeSnapshotSleep;
	WriteHDU stWriteHDU;
	FitsHDUs stFitsHDUs;
	CreateDirInfo stCreateDirInfo;
	RebootSvrInfo stRebootSvrInfo;

};