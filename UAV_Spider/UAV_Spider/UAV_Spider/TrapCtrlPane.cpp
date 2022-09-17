// TrapCtrlPane.cpp : ʵ���ļ�
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



// CTrapCtrlPane ��Ϣ�������




void CTrapCtrlPane::OnDestroy()
{
	CWnd::OnDestroy();
	m_dlgEmbedded.DestroyWindow();
	// TODO: �ڴ˴������Ϣ����������
}


int CTrapCtrlPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
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
	// TODO: �ڴ˴������Ϣ����������
}
