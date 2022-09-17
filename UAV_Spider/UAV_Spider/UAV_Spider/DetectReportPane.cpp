// DetectReportPane.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UAV_Spider.h"
#include "DetectReportPane.h"
#include <WinBase.h >

namespace DetectReport
{
	CDetectData::CDetectData()
	{
		m_dbLon = 0.0;
		m_dbLat = 0.0;
		m_dbAlt = 6500;
		m_strLon = "104.3";
		m_strLat = "45.6";
		m_strAlt = "6500";
		m_strNo = "1";	// ������
		m_strDate = "6500";		// ʱ��
		m_strAppearTime = "6500";		// ����
		m_strDisappearTime = "6500";		// �߶�
		m_strAzimuth = "32.8";			// �ٶ�
		m_strFreqRange = "5";	// ��λ��
		m_strUAVType = "1200";		// ������
	}
	CDetectData::~CDetectData()
	{	
	}
	void CDetectData::GetDetectData()
	{
		m_dbLon = 104.8;
		m_dbLat = 45.9;
		m_dbAlt = 6500;
		m_strLon.Format("%.7f",m_dbLon);
		m_strLat.Format("%.7f",m_dbLat);
		m_strAlt.Format("%.1f",m_dbAlt);
		//SYSTEMTIME st;
		//GetLocalTime(&st);
		//m_strDate.Format("%4d/%2d/%2d",st.wYear,st.wMonth,st.wDay);
		//m_strAppearTime.Format("%2d:%2d:%2d",st.wHour,st.wMinute,st.wSecond);
		//m_strDisappearTime.Format("%2d:%2d:%2d",st.wHour,st.wMinute,st.wSecond);
	}
// CDetectReportPane

IMPLEMENT_DYNAMIC(CDetectReportPane,CWnd)
CDetectReportPane::CDetectReportPane()
{
}

CDetectReportPane::~CDetectReportPane()
{
}

BEGIN_MESSAGE_MAP(CDetectReportPane, CWnd)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CDetectReportPane ��Ϣ�������
int CDetectReportPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	if ( m_ReportCtrl.GetSafeHwnd() == NULL )
	{
		// m_ReportCtrl.Create(CRect(0,0,0,0),this,0,m_ReportCtrl.SetOwner(this),m_ReportCtrl.SetTheme());
		m_ReportCtrl.Create(WS_CHILD|WS_VISIBLE|WS_BORDER, CRect(0,0,0,0), this, IDC_DETECT_LIST);
	}
	m_ReportCtrl.SetGridStyle(TRUE,XTPReportGridStyle(xtpReportGridSolid));//���ô�ֱ�����߷��
	m_ReportCtrl.SetGridStyle(FALSE,XTPReportGridStyle(xtpReportGridSolid));//���ô�ֱ�����߷��
	m_ReportCtrl.GetPaintManager()->SetColumnStyle(XTPReportColumnStyle(xtpReportColumnOffice2007));//�����еķ��
	m_ReportCtrl.GetReportHeader()->SetAutoColumnSizing(TRUE);//����������Զ����ڿ��

	CXTPReportColumn* pCol0 = new CXTPReportColumn(0, _T("��ӱ��"), 20);
	pCol0->SetHeaderAlignment(DT_CENTER);
	pCol0->SetAlignment(DT_CENTER);
	m_ReportCtrl.AddColumn(pCol0);

	CXTPReportColumn* pCol1 = new CXTPReportColumn(1, _T("��ӹ���"), 40);	// ����
	pCol1->SetHeaderAlignment(DT_CENTER);
	pCol1->SetAlignment(DT_CENTER);
	m_ReportCtrl.AddColumn(pCol1);

	CXTPReportColumn* pCol2 = new CXTPReportColumn(2, _T("�ɻ�����"), 40);	// ����ʱ��
	pCol2->SetHeaderAlignment(DT_CENTER);
	pCol2->SetAlignment(DT_CENTER);
	m_ReportCtrl.AddColumn(pCol2);

	CXTPReportColumn* pCol3 = new CXTPReportColumn(3, _T("�ɻ��ܴμ�"), 40);	// ��ʧʱ��
	pCol3->SetHeaderAlignment(DT_CENTER);
	pCol3->SetAlignment(DT_CENTER);
	m_ReportCtrl.AddColumn(pCol3);

	CXTPReportColumn* pCol4 = new CXTPReportColumn(4, _T("��Ӷ���"), 30);	// ��λ��
	pCol4->SetHeaderAlignment(DT_CENTER);
	pCol4->SetAlignment(DT_CENTER);
	m_ReportCtrl.AddColumn(pCol4);

	CXTPReportColumn* pCol5 = new CXTPReportColumn(5, _T("���β���"), 20);		// Ƶ��
	pCol5->SetHeaderAlignment(DT_CENTER);
	pCol5->SetAlignment(DT_CENTER);
	m_ReportCtrl.AddColumn(pCol5);

	//CXTPReportColumn* pCol6 = new CXTPReportColumn(6, _T("����ʱ��"), 20);
	//pCol6->SetHeaderAlignment(DT_CENTER);
	//pCol6->SetAlignment(DT_CENTER);
	//m_ReportCtrl.AddColumn(pCol6);

	m_ReportCtrl.AllowEdit(TRUE); 

	m_dataDetect.GetDetectData();
	m_ReportCtrl.Populate();

	return 0;
}

void CDetectReportPane::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CWnd::OnClose();
}

void CDetectReportPane::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);
	if ( m_ReportCtrl.GetSafeHwnd() )
	{
		m_ReportCtrl.MoveWindow(0,0,cx,cy);
		m_ReportCtrl.Invalidate(FALSE);
	}
	// TODO: �ڴ˴������Ϣ����������
}

void CDetectReportPane::UpdateDetectData()
{
	CXTPReportRecord *pRecord;
	CXTPReportRecordItem *pItem;
	for(int i = 0;i < 5; i++ )
	{
		pRecord = new CXTPReportRecord();
		m_dataDetect.m_strNo.Format("%d",i+1);
		//pRecord->AddItem(new CXTPReportRecordItemText(m_dataDetect.m_strNo));
		//pRecord->AddItem(new CXTPReportRecordItemText(m_dataDetect.m_strDate));
		//pRecord->AddItem(new CXTPReportRecordItemText(m_dataDetect.m_strAppearTime));
		//pRecord->AddItem(new CXTPReportRecordItemText(m_dataDetect.m_strDisappearTime));
		//pRecord->AddItem(new CXTPReportRecordItemText(m_dataDetect.m_strAzimuth));	
		//pRecord->AddItem(new CXTPReportRecordItemText(m_dataDetect.m_strFreqRange));
		//pRecord->AddItem(new CXTPReportRecordItemText(m_dataDetect.m_strUAVType));
		pRecord->AddItem(new CXTPReportRecordItemText(m_dataDetect.m_strNo));
		pRecord->AddItem(new CXTPReportRecordItemText(m_dataDetect.m_strLon));
		pRecord->AddItem(new CXTPReportRecordItemText(m_dataDetect.m_strLat));
		pRecord->AddItem(new CXTPReportRecordItemText(m_dataDetect.m_strAlt));
		pRecord->AddItem(new CXTPReportRecordItemText(m_dataDetect.m_strAzimuth));	
		pRecord->AddItem(new CXTPReportRecordItemText(m_dataDetect.m_strFreqRange));
		pRecord->AddItem(new CXTPReportRecordItemText(m_dataDetect.m_strUAVType));
		m_ReportCtrl.AddRecord(pRecord);
		//for (int i = 0; i < 7; i++)
		//{
		//	pRecord = new CXTPReportRecord();
		//	m_ReportCtrl.AddRecord(pRecord);
		//	pItem = new CXTPReportRecordItemText("0.0");
		//	pRecord->AddItem(pItem);
		//	pItem->SetItemData(i);
		//}
		
	}	
	m_ReportCtrl.Populate();
}

}