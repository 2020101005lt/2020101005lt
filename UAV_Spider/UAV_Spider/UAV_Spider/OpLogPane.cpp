// OpLogPane.cpp : ʵ���ļ�
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



// COpLogPane ��Ϣ�������




int COpLogPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
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
	// TODO: �ڴ˴������Ϣ����������
}

void COpLogPane::OnDestroy()
{
	CWnd::OnDestroy();
	m_dlgEmbedded.DestroyWindow();
	// TODO: �ڴ˴������Ϣ����������
}
