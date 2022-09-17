#pragma once


// CDetectReportPane
namespace TrapReport
{
	class AFX_EXT_CLASS CTrapData
	{
	public:
		CTrapData();
		~CTrapData();	
	public:
		double m_dbLon;			// ����
		double m_dbLat;			// γ��
		double m_dbAlt;			// �߶�
		CString m_strLon;
		CString m_strLat;
		CString m_strAlt;
		CString m_strNo;		// ��ţ�ÿ���1��ʼ��ţ�����0�����¿�ʼ
		CString m_strDate;			// ���ڣ���������
		CString m_strSwitchOnTime;	// ���俪ʼʱ�䣺24Сʱ��ʽ����ȷ����
		CString m_strSwitchOffTime;	// �������ʱ�䣺24Сʱ��ʽ����ȷ����
	public:
		void GetTrapData();
	};

	class CTrapReportPane : public CWnd
	{
		DECLARE_DYNAMIC(CTrapReportPane)

	public:
		CTrapReportPane();
		virtual ~CTrapReportPane();

	protected:
		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		afx_msg void OnClose();
		afx_msg void OnSize(UINT nType, int cx, int cy);
		DECLARE_MESSAGE_MAP()

	public:
		void UpdateTrapData();
		CTrapData m_dataTrap;

	protected:
		CXTPReportControl m_ReportCtrl;
	};
}