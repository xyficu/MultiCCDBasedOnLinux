#pragma once

// CMySocket ����Ŀ��

class CMySocket : public CSocket
{
public:
	CMySocket();
	virtual ~CMySocket();

private:
	int m_nTimerID;

public:
	BOOL KillTimeOut();
	BOOL SetTimeOut(UINT uTimeOut);

public:
	virtual BOOL OnMessagePending();

	
};


