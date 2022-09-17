// DlgOpLog.cpp : 实现文件
//

#include "stdafx.h"
#include "UAV_Spider.h"
#include "DlgOpLog.h"
#include "afxdialogex.h"


// CDlgOpLog 对话框

IMPLEMENT_DYNAMIC(CDlgOpLog, CDialogEx)

CDlgOpLog::CDlgOpLog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgOpLog::IDD, pParent)
{

}

CDlgOpLog::~CDlgOpLog()
{
}

void CDlgOpLog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_OP_LOG, m_listLogMsg);
}


BEGIN_MESSAGE_MAP(CDlgOpLog, CDialogEx)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_OP_LOG, &CDlgOpLog::OnLvnItemchangedListOpLog)
END_MESSAGE_MAP()


// CDlgOpLog 消息处理程序


void CDlgOpLog::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	CWnd *pWnd;
	pWnd=GetDlgItem(IDC_LIST_OP_LOG);
	if(pWnd&&nType!=1)//当对话框工程刚打开时不执行此代码
	{
		CRect rc;
		GetClientRect(&rc);
		pWnd->MoveWindow(rc);
	}
	// TODO: 在此处添加消息处理程序代码
}


int CDlgOpLog::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;
	return 0;
}


void CDlgOpLog::OnLvnItemchangedListOpLog(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


BOOL CDlgOpLog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CString strDate,strTime,strLog;
	SYSTEMTIME st;
	GetLocalTime(&st);	
	strDate.Format("%4d/%2d/%2d",st.wYear,st.wMonth,st.wDay);
	strTime.Format("%2d:%2d:%2d",st.wHour,st.wMinute,st.wSecond);
	strLog.Format(strDate+" "+ strTime+" "+"打开探测开关");
	GetLocalTime(&st);
	m_listLogMsg.InsertItem(0,"2019/12/19 10:01 用户Admin，设置诱骗位置为经度103.962198，纬度30.767306");//插入行
	m_listLogMsg.InsertItem(1,"2019/12/19 12:08 用户Admin，设置频谱探测模式为城市模式，探测对象为图传");
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
