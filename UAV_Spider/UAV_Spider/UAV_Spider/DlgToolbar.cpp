// DlgToolbar.cpp : 实现文件
//

#include "stdafx.h"
#include "UAV_Spider.h"
#include "DlgToolbar.h"
#include "afxdialogex.h"
#include "resource.h"

// CDlgToolbar 对话框

IMPLEMENT_DYNAMIC(CDlgToolbar, CDialogEx)

CDlgToolbar::CDlgToolbar(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgToolbar::IDD, pParent)
{

}

CDlgToolbar::~CDlgToolbar()
{
}

void CDlgToolbar::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_SETTING, m_btnSetting);
	DDX_Control(pDX, IDC_STATIC_RUNTIME, m_RunTime);
	DDX_Control(pDX, IDC_ILEDROUNDX_DETECT, m_iLedStatusD);
	DDX_Control(pDX, IDC_ILEDROUNDX_TRAP, m_iLedStatusT);
}


BEGIN_MESSAGE_MAP(CDlgToolbar, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_SETTING, &CDlgToolbar::OnBnClickedBtnSetting)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CDlgToolbar 消息处理程序


void CDlgToolbar::OnBnClickedBtnSetting()
{
	// TODO: 在此添加控件通知处理程序代码
	int a = 1;
	int b = 2;
}


BOOL CDlgToolbar::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_btnSetting.LoadBitmaps(IDB_BITMAP_SETTING,IDB_BITMAP_SETTING,IDB_BITMAP_SETTING,IDB_BITMAP_SETTING);
	m_RunTime.SetColourFaded(RGB(0,40,0));
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlgToolbar::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
}

void CDlgToolbar::UpdateRunTime()
{
	m_RunTime.DisplayCurrentTime();
}