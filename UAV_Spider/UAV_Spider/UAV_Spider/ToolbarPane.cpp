// ToolbarPane.cpp : ʵ���ļ�
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



// CToolbarPane ��Ϣ�������




int CToolbarPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	m_dlgEmbedded.Create(IDD_DLG_TOOLBAR,this);
	m_dlgEmbedded.ShowWindow(SW_SHOW);
	return 0;
}


void CToolbarPane::OnDestroy()
{
	CWnd::OnDestroy();
	m_dlgEmbedded.DestroyWindow();
	// TODO: �ڴ˴������Ϣ����������
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
	// TODO: �ڴ˴������Ϣ����������
}
