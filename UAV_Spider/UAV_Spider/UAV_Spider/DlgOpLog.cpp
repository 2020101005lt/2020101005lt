// DlgOpLog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UAV_Spider.h"
#include "DlgOpLog.h"
#include "afxdialogex.h"


// CDlgOpLog �Ի���

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


// CDlgOpLog ��Ϣ�������


void CDlgOpLog::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	CWnd *pWnd;
	pWnd=GetDlgItem(IDC_LIST_OP_LOG);
	if(pWnd&&nType!=1)//���Ի��򹤳̸մ�ʱ��ִ�д˴���
	{
		CRect rc;
		GetClientRect(&rc);
		pWnd->MoveWindow(rc);
	}
	// TODO: �ڴ˴������Ϣ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


BOOL CDlgOpLog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CString strDate,strTime,strLog;
	SYSTEMTIME st;
	GetLocalTime(&st);	
	strDate.Format("%4d/%2d/%2d",st.wYear,st.wMonth,st.wDay);
	strTime.Format("%2d:%2d:%2d",st.wHour,st.wMinute,st.wSecond);
	strLog.Format(strDate+" "+ strTime+" "+"��̽�⿪��");
	GetLocalTime(&st);
	m_listLogMsg.InsertItem(0,"2019/12/19 10:01 �û�Admin��������ƭλ��Ϊ����103.962198��γ��30.767306");//������
	m_listLogMsg.InsertItem(1,"2019/12/19 12:08 �û�Admin������Ƶ��̽��ģʽΪ����ģʽ��̽�����Ϊͼ��");
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
