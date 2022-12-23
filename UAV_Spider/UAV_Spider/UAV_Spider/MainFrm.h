// MainFrm.h : interface of the CMainFrame class
//


#pragma once
#include "ToolbarPane.h"
#include "DetectReportPane.h"
#include "TrapReportPane.h"
#include "DetectCtrlPane.h"
#include "TrapCtrlPane.h"
#include "OpLogPane.h"
#include "CTCPSock.h"
#include "UAV_SpiderView.h"
//#include "UDPSock.h"
#define ID_TIMER_REFRESH_DETECT 200
#define ID_TIMER_REFRESH_TRAP	201
#define ID_TIMER_REFRESH_RUNTIME 202
#define ID_TIMER_REFRESH_MAP	203//定义字符串
using namespace DetectReport;
using namespace TrapReport;

class CMainFrame : public CXTPFrameWnd//构造函数
{

protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)
	int ReadConfig();
// Attributes
public://添加函数
	CString m_strLoaclIP1;//构造函数，定义对象
	CString m_strLoaclIP2;
	UINT m_uDetectPort;//声明变量
	UINT m_uTrapPort;

	CUAV_SpiderView* m_pView;
	int CntInTimer;	//第一个定时器事件--用于屏幕初始化
	int	myOnTimer_Busy;//程序重定时器程序中退出的标志：0表达退出
// Operations
public:
	CToolbarPane m_panToolbar;
	CDetectReportPane m_paneDetectReport;
	CTrapReportPane m_paneTrapReport;
	CDetectCtrlPane m_paneDetectCtrl;
	CTrapCtrlPane m_paneTrapCtrl;
	COpLogPane m_paneOpLog;
	CTCPSock m_TCPclientDetect;
	//CTCPSock m_TCPclientTrap;
	//UDPSock m_UDPclientTrap;
// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	void RecvTCPData(CString szText);
// Implementation
public:
	virtual ~CMainFrame();//添加函数
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif//对提供运行对象内部状态进行检查

protected:  // control bar embedded members
	CXTPStatusBar  m_wndStatusBar;//在对话框中添加变量成员
	CXTPDockingPaneManager m_paneManager;//停靠窗口

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);//定义子窗口
	afx_msg void OnClose();//定义子窗口
	afx_msg void OnCustomize();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg LRESULT OnDockingPaneNotify(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};
