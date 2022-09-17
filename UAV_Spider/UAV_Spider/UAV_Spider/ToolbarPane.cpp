// ToolbarPane.cpp : 实现文件
//

#include "stdafx.h"
#include "UAV_Spider.h"
#include "ToolbarPane.h"


// CToolbarPane

IMPLEMENT_DYNAMIC(CToolbarPane, CWnd)

CToolbarPane::CToolbarPane()
{

}

CToolbarPane::~CToolbarPane()
{
}


BEGIN_MESSAGE_MAP(CToolbarPane, CWnd)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// CToolbarPane 消息处理程序




int CToolbarPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	m_dlgEmbedded.Create(IDD_DLG_TOOLBAR,this);
	m_dlgEmbedded.ShowWindow(SW_SHOW);
	return 0;
}


void CToolbarPane::OnDestroy()
{
	CWnd::OnDestroy();
	m_dlgEmbedded.DestroyWindow();
	// TODO: 在此处添加消息处理程序代码
}


void CToolbarPane::OnSize(UINT nType, int cx, int cy)
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
