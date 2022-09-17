// OpLogPane.cpp : 实现文件
//

#include "stdafx.h"
#include "UAV_Spider.h"
#include "OpLogPane.h"


// COpLogPane

IMPLEMENT_DYNAMIC(COpLogPane, CWnd)

COpLogPane::COpLogPane()
{

}

COpLogPane::~COpLogPane()
{
}


BEGIN_MESSAGE_MAP(COpLogPane, CWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()



// COpLogPane 消息处理程序




int COpLogPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	m_dlgEmbedded.Create(IDD_DLG_OPERATION_LOG,this);
	m_dlgEmbedded.ShowWindow(SW_SHOW);
	return 0;
}


void COpLogPane::OnSize(UINT nType, int cx, int cy)
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

void COpLogPane::OnDestroy()
{
	CWnd::OnDestroy();
	m_dlgEmbedded.DestroyWindow();
	// TODO: 在此处添加消息处理程序代码
}
