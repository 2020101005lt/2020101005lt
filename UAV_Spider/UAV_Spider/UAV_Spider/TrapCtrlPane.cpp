// TrapCtrlPane.cpp : 实现文件
//

#include "stdafx.h"
#include "UAV_Spider.h"
#include "TrapCtrlPane.h"


// CTrapCtrlPane

IMPLEMENT_DYNAMIC(CTrapCtrlPane, CWnd)

CTrapCtrlPane::CTrapCtrlPane()
{

}

CTrapCtrlPane::~CTrapCtrlPane()
{
}


BEGIN_MESSAGE_MAP(CTrapCtrlPane, CWnd)
	ON_WM_DESTROY()
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// CTrapCtrlPane 消息处理程序




void CTrapCtrlPane::OnDestroy()
{
	CWnd::OnDestroy();
	m_dlgEmbedded.DestroyWindow();
	// TODO: 在此处添加消息处理程序代码
}


int CTrapCtrlPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	m_dlgEmbedded.Create(IDD_DLG_TRAP_CTRL,this);
	m_dlgEmbedded.ShowWindow(SW_SHOW);
	return 0;
}


void CTrapCtrlPane::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);
	if(m_dlgEmbedded.GetSafeHwnd())
	{
		CRect rect;
		GetClientRect(&rect);
		m_dlgEmbedded.MoveWindow(rect);
	}
	// TODO: 在此处添加消息处理程序代码
}
