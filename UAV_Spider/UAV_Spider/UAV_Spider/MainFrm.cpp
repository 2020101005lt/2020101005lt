// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "UAV_Spider.h"

#include "MainFrm.h"
#include "resource.h"
#include "DlgDetectCtrl.h"
#include "DlgTrapCtrl.h"
#include "DetectReportPane.h"
#include "DetectCtrlPane.h"
using namespace DetectReport;	
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_COMMAND(XTP_ID_CUSTOMIZE, OnCustomize)
	ON_MESSAGE(XTPWM_DOCKINGPANE_NOTIFY, OnDockingPaneNotify)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 设置状态指示灯
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

static UINT uHideCmds[] =
{
	ID_FILE_PRINT,
	ID_FILE_PRINT_PREVIEW,
};

// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	m_pView = NULL;
	CntInTimer = 0;
	myOnTimer_Busy = 0;
}

CMainFrame::~CMainFrame()
{
}
int CMainFrame::ReadConfig()
{
	char buf[256];
	GetCurrentDirectoryA(sizeof(buf),buf);
	CString strFilePath;
	strFilePath.Format("%s\\Config.ini",buf);
	//读取到向量	std::vector <MAPWINGIS_LAYERSHOWINFO>	myShpLayerShowInfoVec; --->>>按照类型排序了！
	//GetLayerShowConfigInfo(relativeDir + "\\Config\\图层显示配置表.csv");
	CFileFind finder;   //查找是否存在ini文件，若不存在，则生成一个新的默认设置的ini文件，这样就保证了我们更改后的设置每次都可用  
	BOOL ifFind = finder.FindFile(strFilePath);
	if (!ifFind)
	{
		WritePrivateProfileString("TCP_Config", "LocalIP1", "192.168.31.82", strFilePath);
		WritePrivateProfileString("TCP_Config", "LocalIP2", "192.168.31.82", strFilePath);
		WritePrivateProfileString("TCP_Config", "DetectPort","6000",strFilePath);
		WritePrivateProfileString("TCP_Config", "TrapPort","6001",strFilePath);
		WritePrivateProfileString("Device_Config", "DeviceID", "001",strFilePath);
	}
	GetPrivateProfileString("TCP_Config", "LocalIP1","", m_strLoaclIP1.GetBuffer(MAX_PATH), MAX_PATH,strFilePath);
	GetPrivateProfileString("TCP_Config", "LocalIP2","", m_strLoaclIP2.GetBuffer(MAX_PATH), MAX_PATH,strFilePath);
	m_uDetectPort = (UINT)GetPrivateProfileInt("TCP_Config", "DetectPort",6000,strFilePath);
	m_uTrapPort = (UINT)GetPrivateProfileInt("TCP_Config", "TrapPort",6001,strFilePath);
	//SetDlgItemText(IDC_EDIT2, str);
	return 1;
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;


	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// Initialize the command bars
	if (!InitCommandBars())
		return -1;

	// Get a pointer to the command bars object.
	CXTPCommandBars* pCommandBars = GetCommandBars();
	if(pCommandBars == NULL)
	{
		TRACE0("Failed to create command bars object.\n");
		return -1;      // fail to create
	}

	// Set Office 2003 Theme
	CXTPPaintManager::SetTheme(xtpThemeOffice2003);

	// Hide array of commands
	pCommandBars->HideCommands(uHideCmds, _countof(uHideCmds));

	// Set "Always Show Full Menus" option to the FALSE
	pCommandBars->GetCommandBarsOptions()->bAlwaysShowFullMenus = FALSE;

	pCommandBars->GetShortcutManager()->SetAccelerators(IDR_MAINFRAME);
	pCommandBars->GetCommandBarsOptions()->bLargeIcons = TRUE;

	// Initialize the docking pane manager and set the
	// initial them for the docking panes.  Do this only after all
	// control bars objects have been created and docked.
	m_paneManager.InstallDockingPanes(this);
	// Set Office 2003 Theme
	m_paneManager.SetTheme(xtpPaneThemeOffice2003);
	m_paneManager.SetAlphaDockingContext(TRUE);
	m_paneManager.SetShowDockingContextStickers(TRUE);
	m_paneManager.SetShowContentsWhileDragging(TRUE);

	// Create docking panes.
	CXTPDockingPane* paneToolBar = m_paneManager.CreatePane(
		IDR_PANE_TOOLBAR, CRect(0, 0,100, 100), xtpPaneDockTop);
	paneToolBar->SetOptions(xtpPaneNoCloseable);
	paneToolBar->SetOptions(xtpPaneNoCaption);
	//paneToolBar->SetOptions(xtpPaneNoCloseable);
	//paneToolBar->SetOptions()
	CXTPDockingPane* paneDetectReport = m_paneManager.CreatePane(
		IDR_PANE_DETECT_REPORT, CRect(0, 0,500, 120), xtpPaneDockLeft);
	//paneDetectReport->SetTitle(_T("探测发现记录"));
	paneDetectReport->SetTitle(_T("编队参数列表"));
	CXTPDockingPane* paneTrapReport = m_paneManager.CreatePane(
		IDR_PANE_TRAP_REPORT, CRect(0, 0,500, 120), xtpPaneDockBottom, paneDetectReport);
	paneTrapReport->SetTitle(_T("诱骗动作记录"));
	CXTPDockingPane* paneDetectCtrl = m_paneManager.CreatePane(
		IDR_PANE_DETECT_CONTROL, CRect(0, 0,400, 120), xtpPaneDockRight);
	paneDetectCtrl->SetTitle(_T("探测控制面板"));
	CXTPDockingPane* paneTrapCtrl = m_paneManager.CreatePane(
		IDR_PANE_TRAP_CONTROL, CRect(0, 0,400, 120), xtpPaneDockBottom, paneDetectCtrl);
	paneTrapCtrl->SetTitle(_T("诱骗控制面板"));
	CXTPDockingPane* paneOpLog = m_paneManager.CreatePane(
		IDR_PANE_OPERATION_LOG, CRect(0, 0,200, 200), xtpPaneDockBottom);
	paneOpLog->SetTitle(_T("操作记录"));

	// Set the icons for the docking pane tabs.
	int nIDIcons[] = {IDR_PANE_TOOLBAR, IDR_PANE_DETECT_REPORT, IDR_PANE_TRAP_REPORT,IDR_PANE_DETECT_CONTROL,IDR_PANE_TRAP_CONTROL,IDR_PANE_OPERATION_LOG};
	m_paneManager.SetIcons(IDB_BITMAP_ICONS, nIDIcons,
		_countof(nIDIcons), RGB(0, 255, 0));
	
	ReadConfig();
	SetTimer(ID_TIMER_REFRESH_MAP,500,NULL);
	SetTimer(ID_TIMER_REFRESH_DETECT,200,NULL);  
	SetTimer(ID_TIMER_REFRESH_TRAP,500,NULL);  
	SetTimer(ID_TIMER_REFRESH_RUNTIME,1000,NULL);
	//if(!m_UDPclientTrap.UDPInit())
	//{
	//	TRACE("---------------------------------------------test1 ok-------------------------------------");
	//}
	//if(!m_TCPclientDetect.Create())//创建TCP的socket
	//{
	//	AfxMessageBox("DETECT网络创建失败！");
	//}
	//if(!m_TCPclientDetect.Connect(m_strLoaclIP1, m_uDetectPort))
	//{
	//	int nErr = GetLastError();//10061连接不到服务器
	//	AfxMessageBox("连接DETECT网络失败，请检查网络是否连接！");
	//}
	//if(!m_TCPclientTrap.Create())//创建TCP的socket
	//{
	//	AfxMessageBox("TRAP网络创建失败！");
	//}
	//if(!m_TCPclientTrap.Connect(m_strLoaclIP2, m_uTrapPort))
	//{
	//	int nErr = GetLastError();//10061连接不到服务器
	//	AfxMessageBox("连接TRAP网络失败，请检查网络是否连接！");
	//}
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style |= WS_CLIPCHILDREN|WS_CLIPSIBLINGS;
	cs.hMenu = NULL;			// 20191126-去掉菜单栏
	return TRUE;
}


// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame message handlers

void CMainFrame::RecvTCPData(CString szText)
{
	TRACE("Ln200-MainFrame:\t,进入主窗口接收TCP数据程序！%s\n",szText);
}


void CMainFrame::OnClose()
{
	// Save the current state for toolbars and menus.
	//SaveCommandBars(_T("CommandBars"));
	KillTimer(ID_TIMER_REFRESH_MAP);
	KillTimer(ID_TIMER_REFRESH_DETECT);
	KillTimer(ID_TIMER_REFRESH_RUNTIME);
	CFrameWnd::OnClose();
}


void CMainFrame::OnCustomize()
{
	// Get a pointer to the command bars object.
	CXTPCommandBars* pCommandBars = GetCommandBars();
	if(pCommandBars != NULL)
	{
		// Instanciate the customize dialog object.
		CXTPCustomizeSheet dlg(pCommandBars);

		// Add the keyboard page to the customize dialog.
		CXTPCustomizeKeyboardPage pageKeyboard(&dlg);
		dlg.AddPage(&pageKeyboard);
		pageKeyboard.AddCategories(IDR_MAINFRAME);

		// Add the options page to the customize dialog.
		CXTPCustomizeOptionsPage pageOptions(&dlg);
		dlg.AddPage(&pageOptions);

		// Add the commands page to the customize dialog.
		CXTPCustomizeCommandsPage* pCommands = dlg.GetCommandsPage();
		pCommands->AddCategories(IDR_MAINFRAME);

		// Use the command bar manager to initialize the
		// customize dialog.
		pCommands->InsertAllCommandsCategory();
		pCommands->InsertBuiltInMenus(IDR_MAINFRAME);
		pCommands->InsertNewMenuCategory();

		// Dispaly the dialog.
		dlg.DoModal();
	}
}

LRESULT CMainFrame::OnDockingPaneNotify(WPARAM wParam, LPARAM lParam)
{
	if (wParam == XTP_DPN_SHOWWINDOW)
	{
		CXTPDockingPane* pPane = (CXTPDockingPane*)lParam;

		if (!pPane->IsValid())
		{
			switch (pPane->GetID())
			{
			case IDR_PANE_TOOLBAR:
				{
					if (m_panToolbar.GetSafeHwnd() == 0)
					{
						m_panToolbar.Create(NULL,NULL,WS_CHILD|WS_BORDER|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS,CXTPEmptyRect(),this,IDR_PANE_TOOLBAR);
					}
					pPane->Attach(&m_panToolbar);
					break;
				}
			case IDR_PANE_DETECT_REPORT:
				{
					if (m_paneDetectReport.GetSafeHwnd() == 0)
					{
						m_paneDetectReport.Create(NULL,NULL,WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS,CXTPEmptyRect(),this,IDR_PANE_DETECT_REPORT);
						//m_paneDetectReport->OnInitDialog();
						m_paneDetectReport.UpdateDetectData();
					}
					pPane->Attach(&m_paneDetectReport);
					//m_paneManager.ClosePane(pPane);
					break;
				}
			case IDR_PANE_TRAP_REPORT:
				{
					if (m_paneTrapReport.GetSafeHwnd() == 0)
					{
						m_paneTrapReport.Create(NULL,NULL,WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS,CXTPEmptyRect(),this,IDR_PANE_DETECT_REPORT);
						//m_paneDetectReport->OnInitDialog();
						m_paneTrapReport.UpdateTrapData();
					}
					pPane->Attach(&m_paneTrapReport);
					break;
				}
			case IDR_PANE_DETECT_CONTROL:
				{
					if (m_paneDetectCtrl.GetSafeHwnd() == 0)
					{
						m_paneDetectCtrl.Create(NULL,NULL,WS_CHILD|WS_VISIBLE|WS_BORDER|WS_CLIPCHILDREN|WS_CLIPSIBLINGS,CXTPEmptyRect(),this,IDR_PANE_DETECT_CONTROL);
					}
					pPane->Attach(&m_paneDetectCtrl);
					break;
				}
			case IDR_PANE_TRAP_CONTROL:
				{
					if (m_paneTrapCtrl.GetSafeHwnd() == 0)
					{
						m_paneTrapCtrl.Create(NULL,NULL,WS_CHILD|WS_VISIBLE|WS_BORDER|WS_CLIPCHILDREN|WS_CLIPSIBLINGS,CXTPEmptyRect(),this,IDR_PANE_TRAP_CONTROL);
					}
					pPane->Attach(&m_paneTrapCtrl);
					break;
				}
			case IDR_PANE_OPERATION_LOG:
				{
					if (m_paneOpLog.GetSafeHwnd() == 0)
					{
						m_paneOpLog.Create(NULL,NULL,WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS,CXTPEmptyRect(),this,IDR_PANE_OPERATION_LOG);
					}
					pPane->Attach(&m_paneOpLog);
					break;
				}
			}
		}
		return TRUE;
	}
	return FALSE;
}

void CMainFrame::OnTimer(UINT nIDEvent)
{
	switch(nIDEvent) {
	case ID_TIMER_REFRESH_MAP:
		if(myOnTimer_Busy != 0)		
			return;
		myOnTimer_Busy = 1;
		if ( CntInTimer == 0 )
		{
			m_pView = (CUAV_SpiderView *)GetActiveView();
			if (!m_pView)
			{
				return;
			}
			m_pView->LoadMap();
		}
		myOnTimer_Busy = 0;
		CntInTimer++;
		break;

	//case ID_TIMER_REFRESH_TRAP:
	//	{
	//		fd_set rfd;                           // 描述符集 这个将用来测试有没有一个可用的连接
	//		struct timeval timeout;
	//		timeout.tv_sec=0;               //等下select用到这个
	//		timeout.tv_usec=0;              //timeout设置为0，可以理解为非阻塞
	//		int rev=0;
	//		int SelectRcv;
	//		int recvbuf = 1;
	//		setsockopt(m_UDPclientTrap.s_UDPSockSrv,SOL_SOCKET,SO_RCVBUF,(char*)&recvbuf,sizeof(int));
	//		//设置为非阻塞模式  
	//		int imode=1;  
	//		rev=ioctlsocket(m_UDPclientTrap.s_UDPSockSrv,FIONBIO,(u_long *)&imode);  
	//		// UDP数据接收
	//		FD_ZERO(&rfd);           //总是这样先清空一个描述符集
	//		FD_SET(m_UDPclientTrap.s_UDPSockSrv,&rfd); //把sock放入要测试的描述符集
	//		SelectRcv = select(m_UDPclientTrap.s_UDPSockSrv+1,&rfd,0,0, &timeout); //检查该套接字是否可读
	//		if(SelectRcv<0) 
	//		{
	//			TRACE("监听失败\n");
	//		}
	//		if(SelectRcv==0) 
	//		{
	//			/*TRACE("超时\n");*/
	//		}
	//		if (SelectRcv > 0)
	//		{
	//			rev=0;
	//			m_UDPclientTrap.UDPRecv();
	//			/*		m_TCPclientTrap.UDPSend();*/
	//		}
	//	}

	//	break;
	//	case ID_TIMER_REFRESH_DETECT:
	//	m_paneDetectReport.m_dataDetect.m_strDate = "2019/12/27";
	//	m_paneDetectReport.m_dataDetect.m_strAppearTime = "10:15:36";
	//	m_paneDetectReport.m_dataDetect.m_strDisappearTime = "10:18:42";
	//	m_paneDetectReport.m_dataDetect.m_strAzimuth = "49.2";
	//	m_paneDetectReport.m_dataDetect.m_strFreqRange = "频段2";
	//	m_paneDetectReport.m_dataDetect.m_strUAVType = "Dji2300";
	//	//m_paneDetectReport.UpdateDetectData();
	//	break;
	//case ID_TIMER_REFRESH_TRAP:
	//	//funcB();
	//	break;
	//default:
	//	break;
	//}
	case ID_TIMER_REFRESH_RUNTIME:
		m_panToolbar.m_dlgEmbedded.UpdateRunTime();
		break;
	}
}
