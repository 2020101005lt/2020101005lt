// DlgDetectReport.cpp : 实现文件
//

#include "stdafx.h"
#include "UAV_Spider.h"
#include "DlgDetectReport.h"
#include "afxdialogex.h"


// CDlgDetectReport 对话框

IMPLEMENT_DYNAMIC(CDlgDetectReport, CDialogEx)

CDlgDetectReport::CDlgDetectReport(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgDetectReport::IDD, pParent)
{

}

CDlgDetectReport::~CDlgDetectReport()
{
}

void CDlgDetectReport::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_DETECT, m_lstDetect);
}


BEGIN_MESSAGE_MAP(CDlgDetectReport, CDialogEx)
END_MESSAGE_MAP()


// CDlgDetectReport 消息处理程序


BOOL CDlgDetectReport::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CRect rc;
	m_lstDetect.GetWindowRect(&rc);
	int nW = rc.right - rc.left;
	int nWidth = (int)(nW/7 + 0.5);
	// TODO:  在此添加额外的初始化
	m_lstDetect.InsertColumn(0,_T("航迹号"),LVCFMT_LEFT,nWidth);
	m_lstDetect.InsertColumn(1,_T("时间"),LVCFMT_LEFT,nWidth);
	m_lstDetect.InsertColumn(2,_T("距离"),LVCFMT_LEFT,nWidth);
	m_lstDetect.InsertColumn(3,_T("高度"),LVCFMT_LEFT,nWidth-4);
	m_lstDetect.InsertColumn(4,_T("速度"),LVCFMT_LEFT,nWidth);
	m_lstDetect.InsertColumn(5,_T("方位"),LVCFMT_LEFT,nWidth);
	m_lstDetect.InsertColumn(6,_T("俯仰"),LVCFMT_LEFT,nWidth);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
