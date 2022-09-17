// ButtonDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "UAV_Spider.h"
#include "ButtonDlg.h"
#include "afxdialogex.h"
#include "UAV_SpiderView.h"

// CButtonDlg 对话框

IMPLEMENT_DYNAMIC(CButtonDlg, CDialogEx)

CButtonDlg::CButtonDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CButtonDlg::IDD, pParent)
{
	m_pParentView = NULL;
}

CButtonDlg::~CButtonDlg()
{
}

void CButtonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_MAP, m_btn);
}


BEGIN_MESSAGE_MAP(CButtonDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_MAP, &CButtonDlg::OnBnClickedBtnMap)
	ON_WM_SIZE()
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CButtonDlg 消息处理程序


void CButtonDlg::OnBnClickedBtnMap()
{
	// TODO: 在此添加控件通知处理程序代码
	CUAV_SpiderView* pView = NULL;
	pView = (CUAV_SpiderView*)m_pParentView;
	if ( m_strKind == "IN" )
	{
		pView->OnBnClickedBtnZoomin();
	}
	if (m_strKind == "OUT")
	{
		pView->OnBnClickedBtnZoomout();
	}
	if (m_strKind == "PAN")
	{
		pView->OnBnClickedBtnPan();
	}
}


BOOL CButtonDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
		// TODO:  在此添加额外的初始化
	CRect temprect(0,0,32,32);
	CWnd::SetWindowPos(NULL,0,0,temprect.Width(),temprect.Height(),SWP_NOZORDER|SWP_NOMOVE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CButtonDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	CWnd *pWnd;
	pWnd=GetDlgItem(IDC_BTN_MAP);
	if(pWnd&&nType!=1)//当对话框工程刚打开时不执行此代码
	{
		CRect rc;
		GetClientRect(&rc);
		pWnd->MoveWindow(rc);
	}
	// TODO: 在此处添加消息处理程序代码
}


int CButtonDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;
	//ModifyStyleEx(0, WS_EX_LAYERED);
	//SetLayeredWindowAttributes(0,133,LWA_ALPHA);
	// TODO:  在此添加您专用的创建代码
	//CRect   temprect(0,0,32,32);
	//CWnd::SetWindowPos(NULL,0,0,temprect.Width(),temprect.Height(),SWP_NOZORDER|SWP_NOMOVE);
	if ( m_strKind == "IN" )
	{
		m_btn.LoadBitmaps(IDB_BITMAP_ZOOMIN,IDB_BITMAP_ZOOMOUT,IDB_BITMAP_ZOOMIN,IDB_BITMAP_ZOOMIN);
	}
	else if ( m_strKind == "OUT" )
	{
		m_btn.LoadBitmaps(IDB_BITMAP_ZOOMOUT,IDB_BITMAP_ZOOMIN,IDB_BITMAP_ZOOMOUT,IDB_BITMAP_ZOOMOUT);
	}
	else if ( m_strKind == "PAN" )
	{
		m_btn.LoadBitmaps(IDB_BITMAP_PAN,IDB_BITMAP_PAN,IDB_BITMAP_PAN,IDB_BITMAP_PAN);
	}
	return 0;
}
