// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__864FB875_E427_44EC_BF05_10DFC22F2BC3__INCLUDED_)
#define AFX_STDAFX_H__864FB875_E427_44EC_BF05_10DFC22F2BC3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxsock.h>		// MFC socket extensions
#include <afxcontrolbars.h>

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__864FB875_E427_44EC_BF05_10DFC22F2BC3__INCLUDED_)


#define WM_TAKESNAPSHOT (WM_USER + 200)
#define WM_SETIMGSAVPATH (WM_USER + 201)
#define WM_GETCCDSTATUS (WM_USER + 202)
#define WM_ABORTEXP (WM_USER + 203)
#define WM_SETCOOLERTMP (WM_USER + 204)
#define WM_GETCOOLERTMP (WM_USER + 205)
#define WM_STARTCOOLER (WM_USER + 206)
#define WM_STOPCOOLER (WM_USER + 207)
#define WM_SETFANSPEED (WM_USER + 208)
#define WM_SHUTSVR (WM_USER + 209)
#define WM_SETIMGHEADINFO (WM_USER + 210)
#define WM_TAKESNAPSHOTSLEEP (WM_USER + 211)
#define WM_WRITEHDU (WM_USER + 212)

#define WM_TAKESNAPSHOTCPLT (WM_USER + 300)
#define WM_SETIMGSAVPATHCPLT (WM_USER + 301)
#define WM_GETCCDSTATUSCPLT (WM_USER + 302)
#define WM_ABORTEXPCPLT (WM_USER + 303)
#define WM_SETCOOLERTMPCPLT (WM_USER + 304)
#define WM_GETCOOLERTMPCPLT (WM_USER + 305)
#define WM_STARTCOOLERCPLT (WM_USER + 306)
#define WM_STOPCOOLERCPLT (WM_USER + 307)
#define WM_SETFANSPEEDCPLT (WM_USER + 308)
#define WM_SHUTSVRCPLT (WM_USER + 309)
#define WM_SETIMGHEADINFOCPLT (WM_USER + 310)
#define WM_TAKESNAPSHOTSLEEPCPLT (WM_USER + 311)
#define WM_WRITEHDUCPLT (WM_USER + 312)


#define WM_CONNECT (WM_USER + 400)
#define WM_DISCONNECT (WM_USER + 401)
#define WM_SETIPANDPORT (WM_USER + 402)

#define WM_TAKESNAPSHOTCON (WM_USER + 500)
#define WM_STOPTAKESNAPSHOTCON (WM_USER + 501)
#define WM_STOPTAKESNAPSHOTCONCPLT (WM_USER + 502)
//#define WM_STOPCONCPLT (WM_USER + 503)
#define WM_CREATEDIRONSVR (WM_USER + 503)
#define WM_REBOOTSVR (WM_USER + 504)
#define WM_TAKESNAPSHOTASN (WM_USER +505)



