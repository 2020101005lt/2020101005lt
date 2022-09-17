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
#define ID_TIMER_REFRESH_MAP	203
using namespace DetectReport;
using namespace TrapReport;

class CMainFrame : public CXTPFrameWnd
{

protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)
	int ReadConfig();
// Attributes
public:
	CString m_strLoaclIP1;
	CString m_strLoaclIP2;
	UINT m_uDetectPort;
	UINT m_uTrapPort;

	CUAV_SpiderView* m_pView;
	int CntInTimer;	//��һ����ʱ���¼�--������Ļ��ʼ��
	int	myOnTimer_Busy;//�����ض�ʱ���������˳��ı�־��0����˳�
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
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CXTPStatusBar  m_wndStatusBar;
	CXTPDockingPaneManager m_paneManager;

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnCustomize();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg LRESULT OnDockingPaneNotify(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};
