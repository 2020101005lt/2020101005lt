// DlgTrapReport.cpp : 实现文件
//

#include "stdafx.h"
#include "UAV_Spider.h"
#include "DlgTrapReport.h"
#include "afxdialogex.h"


// CDlgTrapReport 对话框

IMPLEMENT_DYNAMIC(CDlgTrapReport, CDialogEx)

CDlgTrapReport::CDlgTrapReport(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgTrapReport::IDD, pParent)
{

}

CDlgTrapReport::~CDlgTrapReport()
{
}

void CDlgTrapReport::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_TRAP, m_lstTrap);
}


BEGIN_MESSAGE_MAP(CDlgTrapReport, CDialogEx)
END_MESSAGE_MAP()


// CDlgTrapReport 消息处理程序


BOOL CDlgTrapReport::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CRect rc;
	m_lstTrap.GetWindowRect(&rc);
	int nW = rc.right - rc.left;
	int nWidth = (int)(nW/7 + 0.5);
	// TODO:  在此添加额外的初始化
	m_lstTrap.InsertColumn(0,_T("航迹号"),LVCFMT_LEFT,nWidth);
	m_lstTrap.InsertColumn(1,_T("时间"),LVCFMT_LEFT,nWidth);
	m_lstTrap.InsertColumn(2,_T("信噪比"),LVCFMT_LEFT,nWidth);
	m_lstTrap.InsertColumn(3,_T("距离"),LVCFMT_LEFT,nWidth-4);
	m_lstTrap.InsertColumn(4,_T("速度"),LVCFMT_LEFT,nWidth);
	m_lstTrap.InsertColumn(5,_T("方位"),LVCFMT_LEFT,nWidth);
	m_lstTrap.InsertColumn(6,_T("俯仰"),LVCFMT_LEFT,nWidth);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
