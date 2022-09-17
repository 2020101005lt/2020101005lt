// DlgDetectReport.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UAV_Spider.h"
#include "DlgDetectReport.h"
#include "afxdialogex.h"


// CDlgDetectReport �Ի���

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


// CDlgDetectReport ��Ϣ�������


BOOL CDlgDetectReport::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect rc;
	m_lstDetect.GetWindowRect(&rc);
	int nW = rc.right - rc.left;
	int nWidth = (int)(nW/7 + 0.5);
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_lstDetect.InsertColumn(0,_T("������"),LVCFMT_LEFT,nWidth);
	m_lstDetect.InsertColumn(1,_T("ʱ��"),LVCFMT_LEFT,nWidth);
	m_lstDetect.InsertColumn(2,_T("����"),LVCFMT_LEFT,nWidth);
	m_lstDetect.InsertColumn(3,_T("�߶�"),LVCFMT_LEFT,nWidth-4);
	m_lstDetect.InsertColumn(4,_T("�ٶ�"),LVCFMT_LEFT,nWidth);
	m_lstDetect.InsertColumn(5,_T("��λ"),LVCFMT_LEFT,nWidth);
	m_lstDetect.InsertColumn(6,_T("����"),LVCFMT_LEFT,nWidth);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
