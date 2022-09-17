// DetectCtrlPane.cpp : 实现文件
//

#include "stdafx.h"
#include "UAV_Spider.h"
#include "DetectCtrlPane.h"


// CDetectCtrlPane

IMPLEMENT_DYNAMIC(CDetectCtrlPane, CWnd)

CDetectCtrlPane::CDetectCtrlPane()
{

}

CDetectCtrlPane::~CDetectCtrlPane()
{
}


BEGIN_MESSAGE_MAP(CDetectCtrlPane, CWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()



// CDetectCtrlPane 消息处理程序


int CDetectCtrlPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	m_dlgEmbedded.Create(IDD_DLG_DETECT_CTRL,this);
	m_dlgEmbedded.ShowWindow(SW_SHOW);

	return 0;
}


void CDetectCtrlPane::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if(m_dlgEmbedded.GetSafeHwnd())
	{
		CRect rect;
		GetClientRect(&rect);
		m_dlgEmbedded.MoveWindow(rect);
	}
}


void CDetectCtrlPane::OnDestroy()
{
	CWnd::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	m_dlgEmbedded.DestroyWindow();
}
