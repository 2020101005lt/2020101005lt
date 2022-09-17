// DlgTrapReport.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UAV_Spider.h"
#include "DlgTrapReport.h"
#include "afxdialogex.h"


// CDlgTrapReport �Ի���

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


// CDlgTrapReport ��Ϣ�������


BOOL CDlgTrapReport::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect rc;
	m_lstTrap.GetWindowRect(&rc);
	int nW = rc.right - rc.left;
	int nWidth = (int)(nW/7 + 0.5);
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_lstTrap.InsertColumn(0,_T("������"),LVCFMT_LEFT,nWidth);
	m_lstTrap.InsertColumn(1,_T("ʱ��"),LVCFMT_LEFT,nWidth);
	m_lstTrap.InsertColumn(2,_T("�����"),LVCFMT_LEFT,nWidth);
	m_lstTrap.InsertColumn(3,_T("����"),LVCFMT_LEFT,nWidth-4);
	m_lstTrap.InsertColumn(4,_T("�ٶ�"),LVCFMT_LEFT,nWidth);
	m_lstTrap.InsertColumn(5,_T("��λ"),LVCFMT_LEFT,nWidth);
	m_lstTrap.InsertColumn(6,_T("����"),LVCFMT_LEFT,nWidth);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
