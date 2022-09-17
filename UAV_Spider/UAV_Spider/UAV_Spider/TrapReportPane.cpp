// DetectReportPane.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UAV_Spider.h"
#include "TrapReportPane.h"

namespace TrapReport
{
	CTrapData::CTrapData()
	{
		m_dbLon = 0.0;
		m_dbLat = 0.0;
		m_dbAlt = 0.0;
		m_strLon = "";
		m_strLat = "";
		//m_strAlt = "";
		m_strNo = "1";	// ������
		m_strDate = "0.0";		// ʱ��
		m_strSwitchOnTime = "0.0";		// �����
		m_strSwitchOffTime = "0.0";		// ����
	}
	CTrapData::~CTrapData()
	{	
	}
	void CTrapData::GetTrapData()
	{
		m_dbLon = 85;
		m_dbLat = 43;
		m_dbAlt = 0;
		m_strLon.Format("%.7f",m_dbLon);
		m_strLat.Format("%.7f",m_dbLat);
		m_strAlt.Format("%.1f",m_dbAlt);
		SYSTEMTIME st;
		GetLocalTime(&st);
		m_strDate.Format("%4d-%2d-%2d",st.wYear,st.wMonth,st.wDay);
		m_strSwitchOnTime.Format("%2d:%2d:%2d",st.wHour,st.wMinute,st.wSecond);
		m_strSwitchOffTime.Format("%2d:%2d:%2d",st.wHour,st.wMinute,st.wSecond);

	}
	// CDetectReportPane

	IMPLEMENT_DYNAMIC(CTrapReportPane,CWnd)
		CTrapReportPane::CTrapReportPane()
	{
	}

	CTrapReportPane::~CTrapReportPane()
	{
	}

	BEGIN_MESSAGE_MAP(CTrapReportPane, CWnd)
		ON_WM_CREATE()
		ON_WM_CLOSE()
		ON_WM_SIZE()
	END_MESSAGE_MAP()

	// CDetectReportPane ��Ϣ�������
	int CTrapReportPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
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

		CXTPReportColumn* pCol0 = new CXTPReportColumn(0, _T("���"), 80);
		pCol0->SetHeaderAlignment(DT_CENTER);
		pCol0->SetAlignment(DT_CENTER);
		m_ReportCtrl.AddColumn(pCol0);

		CXTPReportColumn* pCol1 = new CXTPReportColumn(1, _T("����"), 80);
		pCol1->SetHeaderAlignment(DT_CENTER);
		pCol1->SetAlignment(DT_CENTER);
		m_ReportCtrl.AddColumn(pCol1);

		CXTPReportColumn* pCol2 = new CXTPReportColumn(2, _T("���俪ʼʱ��"), 80);
		pCol2->SetHeaderAlignment(DT_CENTER);
		pCol2->SetAlignment(DT_CENTER);
		m_ReportCtrl.AddColumn(pCol2);

		CXTPReportColumn* pCol3 = new CXTPReportColumn(3, _T("�������ʱ��"), 80);
		pCol3->SetHeaderAlignment(DT_CENTER);
		pCol3->SetAlignment(DT_CENTER);
		m_ReportCtrl.AddColumn(pCol3);

		m_ReportCtrl.AllowEdit(TRUE); 

		m_dataTrap.GetTrapData();
		m_ReportCtrl.Populate();

		return 0;
	}

	void CTrapReportPane::OnClose()
	{
		// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

		CWnd::OnClose();
	}

	void CTrapReportPane::OnSize(UINT nType, int cx, int cy)
	{
		CWnd::OnSize(nType, cx, cy);
		if ( m_ReportCtrl.GetSafeHwnd() )
		{
			m_ReportCtrl.MoveWindow(0,0,cx,cy);
			m_ReportCtrl.Invalidate(FALSE);
		}
		// TODO: �ڴ˴������Ϣ����������
	}

	void CTrapReportPane::UpdateTrapData()
	{
		CXTPReportRecord *pRecord;
		CXTPReportRecordItem *pItem;
		for(int i = 0;i < 5; i++ )
		{
			pRecord = new CXTPReportRecord();
			m_dataTrap.m_strNo.Format("%d",i+1);
			pRecord->AddItem(new CXTPReportRecordItemText(m_dataTrap.m_strNo));
			pRecord->AddItem(new CXTPReportRecordItemText(m_dataTrap.m_strDate));
			pRecord->AddItem(new CXTPReportRecordItemText(m_dataTrap.m_strSwitchOnTime));
			pRecord->AddItem(new CXTPReportRecordItemText(m_dataTrap.m_strSwitchOffTime));
			m_ReportCtrl.AddRecord(pRecord);
		}
		m_ReportCtrl.Populate();
	}

}