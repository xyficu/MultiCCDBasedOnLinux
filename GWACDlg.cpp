// GWACDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MultiCCDBasedOnLinux.h"
#include "GWACDlg.h"
#include "afxdialogex.h"


// CGWACDlg 对话框

IMPLEMENT_DYNAMIC(CGWACDlg, CDialogEx)

CGWACDlg::CGWACDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGWACDlg::IDD, pParent)
{
	for(int i=0; i<50; i++)
		m_pDlg[i] = NULL;


}

CGWACDlg::~CGWACDlg()
{
}

void CGWACDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGWACDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_WAC1CCD1, &CGWACDlg::OnBnClickedButtonWac1ccd1)
	ON_BN_CLICKED(IDC_BUTTON_WAC1CCD2, &CGWACDlg::OnBnClickedButtonWac1ccd2)
	ON_BN_CLICKED(IDC_BUTTON_WAC2CCD1, &CGWACDlg::OnBnClickedButtonWac2ccd1)
	ON_BN_CLICKED(IDC_BUTTON_WAC2CCD2, &CGWACDlg::OnBnClickedButtonWac2ccd2)
	ON_BN_CLICKED(IDC_BUTTON_WAC3CCD1, &CGWACDlg::OnBnClickedButtonWac3ccd1)
	ON_BN_CLICKED(IDC_BUTTON_WAC3CCD2, &CGWACDlg::OnBnClickedButtonWac3ccd2)
	ON_BN_CLICKED(IDC_BUTTON_WAC4CCD1, &CGWACDlg::OnBnClickedButtonWac4ccd1)
	ON_BN_CLICKED(IDC_BUTTON_WAC4CCD2, &CGWACDlg::OnBnClickedButtonWac4ccd2)
	ON_BN_CLICKED(IDC_BUTTON_WAC5CCD1, &CGWACDlg::OnBnClickedButtonWac5ccd1)
	ON_BN_CLICKED(IDC_BUTTON_WAC5CCD2, &CGWACDlg::OnBnClickedButtonWac5ccd2)
	ON_BN_CLICKED(IDC_BUTTON_WAC6CCD1, &CGWACDlg::OnBnClickedButtonWac6ccd1)
	ON_BN_CLICKED(IDC_BUTTON_WAC6CCD2, &CGWACDlg::OnBnClickedButtonWac6ccd2)
	//ON_BN_CLICKED(IDC_BUTTON1, &CGWACDlg::OnBnClickedButton1)
	ON_WM_CLOSE()

	ON_BN_CLICKED(IDC_BUTTON_BCCD1, &CGWACDlg::OnBnClickedButtonBccd1)
	ON_BN_CLICKED(IDC_BUTTON_BCCD2, &CGWACDlg::OnBnClickedButtonBccd2)
	ON_BN_CLICKED(IDC_BUTTON3_BCCD3, &CGWACDlg::OnBnClickedButton3Bccd3)
	ON_BN_CLICKED(IDC_BUTTON_BCCD4, &CGWACDlg::OnBnClickedButtonBccd4)
END_MESSAGE_MAP()


// CGWACDlg 消息处理程序



void CGWACDlg::InitAndShowWACWindow(CCCDCtrlDlg* &pDlg, int ccdID)
{
	if(NULL == pDlg)
	{
		pDlg = new CCCDCtrlDlg();
		
		//pDlg->m_titleWacID = wacId;
		pDlg->m_titleCcdID = ccdID;
		
		pDlg->Create(IDD_CCDCTRL, NULL);
		//pDlg->ShowWindow(SW_SHOW);
	}
	else
	{

		LoadCCDParams(pDlg, ccdID);
		pDlg->ShowWindow(SW_SHOW);
		pDlg->SetForegroundWindow();

	}
}




void CGWACDlg::OnBnClickedButtonWac1ccd1()
{
	//AfxBeginThread(StartCcdCtrlWindowThread, m_pDlg[0][0]);


	//DWORD   dwThread; 
	//HANDLE hHandle = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)StartCcdCtrlWindowThread, &m_pDlg[0][0], 0, NULL);   
	//WaitForSingleObject(hHandle,INFINITE);
	//CWinThread *pThread = AfxBeginThread(RUNTIME_CLASS(CMyThread));
	//m_wacID = 0;
	m_ccdID = 0;
	InitAndShowWACWindow(m_pDlg[m_ccdID], m_ccdID);
	
	

}


void CGWACDlg::OnBnClickedButtonWac1ccd2()
{
	
	
	m_ccdID = 1;
	InitAndShowWACWindow(m_pDlg[m_ccdID], m_ccdID);
}


void CGWACDlg::OnBnClickedButtonWac2ccd1()
{
	//m_wacID = 1;
	m_ccdID = 2;
	InitAndShowWACWindow(m_pDlg[m_ccdID], m_ccdID);
}


void CGWACDlg::OnBnClickedButtonWac2ccd2()
{
	//m_wacID = 1;
	m_ccdID = 3;
	InitAndShowWACWindow(m_pDlg[m_ccdID], m_ccdID);
}


void CGWACDlg::OnBnClickedButtonWac3ccd1()
{
	//m_wacID = 2;
	m_ccdID = 4;
	InitAndShowWACWindow(m_pDlg[m_ccdID], m_ccdID);
}


void CGWACDlg::OnBnClickedButtonWac3ccd2()
{
	//m_wacID = 2;
	m_ccdID = 5;
	InitAndShowWACWindow(m_pDlg[m_ccdID], m_ccdID);
}


void CGWACDlg::OnBnClickedButtonWac4ccd1()
{
	//m_wacID = 3;
	m_ccdID = 6;
	InitAndShowWACWindow(m_pDlg[m_ccdID], m_ccdID);
}


void CGWACDlg::OnBnClickedButtonWac4ccd2()
{
	//m_wacID = 3;
	m_ccdID = 7;
	InitAndShowWACWindow(m_pDlg[m_ccdID], m_ccdID);
}


void CGWACDlg::OnBnClickedButtonWac5ccd1()
{
	//m_wacID = 4;
	m_ccdID = 8;
	InitAndShowWACWindow(m_pDlg[m_ccdID], m_ccdID);
}


void CGWACDlg::OnBnClickedButtonWac5ccd2()
{
	//m_wacID = 4;
	m_ccdID = 9;
	InitAndShowWACWindow(m_pDlg[m_ccdID], m_ccdID);
}


void CGWACDlg::OnBnClickedButtonWac6ccd1()
{
	//m_wacID = 5;
	m_ccdID = 10;
	InitAndShowWACWindow(m_pDlg[m_ccdID], m_ccdID);
}


void CGWACDlg::OnBnClickedButtonWac6ccd2()
{
	//m_wacID = 5;
	m_ccdID = 11;
	InitAndShowWACWindow(m_pDlg[m_ccdID], m_ccdID);
}





BOOL CGWACDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	for(int i=0; i<50; i++)
		InitAndShowWACWindow(m_pDlg[i], i);


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CGWACDlg::OnClose()
{
	if (::MessageBox(this->m_hWnd, "是否退出该程序？\n", "提示", MB_OKCANCEL+MB_ICONQUESTION+MB_DEFBUTTON2) == IDOK)
	{
		CDialog::OnClose();
	}
}

void CGWACDlg::LoadCCDParams(CCCDCtrlDlg* &pDlg, int ccdID)
{
	BOOL bLoadXml = FALSE;
	BOOL bFind = FALSE;
	bLoadXml = m_xmlMiniGWAC.Load("MiniGWAC.xml");
	if (bLoadXml)
	{
		CString ccdName, ipAddr, port, imgSavPath, expTime, shutterStatus, imgName, imgNameSu, setCoolerTem;
		CString xmlNode = "CCDCtrlParams";
		m_xmlMiniGWAC.ResetPos();
		ccdName.Format("m%02d", ccdID + 1);
		if (m_xmlMiniGWAC.FindElem(xmlNode))
		{
			
			if (m_xmlMiniGWAC.FindChildElem(ccdName))
			{
				//从XML文件获取属性
				ipAddr = m_xmlMiniGWAC.GetChildAttrib("IPAddress");
				port = m_xmlMiniGWAC.GetChildAttrib("Port");
				imgSavPath = m_xmlMiniGWAC.GetChildAttrib("ImgSavPath");
				expTime = m_xmlMiniGWAC.GetChildAttrib("ExpTime");
				shutterStatus = m_xmlMiniGWAC.GetChildAttrib("ShutterStatus");
				imgName = m_xmlMiniGWAC.GetChildAttrib("ImgName");
				imgNameSu = m_xmlMiniGWAC.GetChildAttrib("ImgSuffix");
				setCoolerTem = m_xmlMiniGWAC.GetChildAttrib("CoolerTem");

				//将属性传递给窗体
				BYTE n1, n2, n3, n4;
				/*byte bt1[30], bt2[30], bt3[30], bt4[30];
				sscanf(ipAddr, "%d%[,:]%d%[,:]%d%[,:]%d", bt1, bt2, bt3, bt4);
				n1 = (BYTE)bt1;
				n2 = (BYTE)bt2;
				n3 = (BYTE)bt3;
				n4 = (BYTE)bt4;*/
				CString str1, str2, str3, str4;
				AfxExtractSubString(str1, ipAddr, 0, ':');
				AfxExtractSubString(str2, ipAddr, 1, ':');
				AfxExtractSubString(str3, ipAddr, 2, ':');
				AfxExtractSubString(str4, ipAddr, 3, ':');
				n1 = (BYTE)atoi(str1);
				n2 = (BYTE)atoi(str2);
				n3 = (BYTE)atoi(str3);
				n4 = (BYTE)atoi(str4);
				m_pDlg[ccdID]->m_ipAddressCcd.SetAddress(n1, n2, n3, n4);
				pDlg->m_portCcd = atoi(port);
				pDlg->m_imgSavPath = imgSavPath;
				pDlg->m_expTime = atof(expTime);
				if (shutterStatus == '1')
				{
					pDlg->m_shutterStatus.SetCheck(BST_CHECKED);
				}
				else if(shutterStatus == '0')
				{
					pDlg->m_shutterStatus.SetCheck(BST_UNCHECKED);
				}
				pDlg->m_imgName = imgName;
				pDlg->m_imgNameSu = atoi(imgNameSu);
				pDlg->m_setCoolerTem = atof(setCoolerTem);

				pDlg->UpdateData(FALSE);
			}
		}
	}
	//xml_miniGWAC.SetDoc("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n");
	//xml_miniGWAC.AddElem("m_01");
	//xml_miniGWAC.IntoElem();
	//xml_miniGWAC.AddElem("Name", "m01");
	//xml_miniGWAC.AddElem("IPAddr", "190.168.1.11");
	//xml_miniGWAC.OutOfElem();
	//xml_miniGWAC.Save("MiniGWAC.xml");
	
}


BOOL CGWACDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(pMsg->message == WM_KEYDOWN   &&   pMsg->wParam == VK_ESCAPE)     return   TRUE;   
	if(pMsg->message == WM_KEYDOWN   &&   pMsg->wParam == VK_RETURN)     return   TRUE;     
	else
		return CDialogEx::PreTranslateMessage(pMsg);
}


void CGWACDlg::OnBnClickedButtonBgccd1()
{

}


void CGWACDlg::OnBnClickedButtonBgccd2()
{

}


void CGWACDlg::OnBnClickedButtonBccd1()
{
	m_ccdID = 32;
	InitAndShowWACWindow(m_pDlg[m_ccdID], m_ccdID);
}


void CGWACDlg::OnBnClickedButtonBccd2()
{
	m_ccdID = 33;
	InitAndShowWACWindow(m_pDlg[m_ccdID], m_ccdID);
}


void CGWACDlg::OnBnClickedButton3Bccd3()
{
	m_ccdID = 34;
	InitAndShowWACWindow(m_pDlg[m_ccdID], m_ccdID);
}


void CGWACDlg::OnBnClickedButtonBccd4()
{
	m_ccdID = 35;
	InitAndShowWACWindow(m_pDlg[m_ccdID], m_ccdID);
}
