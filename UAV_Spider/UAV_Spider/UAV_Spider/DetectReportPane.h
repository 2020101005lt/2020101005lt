#pragma once


// CDetectReportPane
namespace DetectReport
{
	class AFX_EXT_CLASS CDetectData
	{
		public:
			CDetectData();
			~CDetectData();	
		public:
			double m_dbLon;			// ����
			double m_dbLat;			// γ��
			double m_dbAlt;			// �߶�
			CString m_strLon;
			CString m_strLat;
			CString m_strAlt;
			CString m_strNo;			// ��ţ�ÿ���1��ʼ��ţ�����0�����¿�ʼ
			CString m_strDate;			// ���ڣ���������
			CString m_strAppearTime;	// ����ʱ�䣺24Сʱ��ʽ����ȷ����
			CString m_strDisappearTime;	// ��ʧʱ�䣺24Сʱ��ʽ����ȷ����
			CString m_strAzimuth;		// ̽�ⷽλ�ǣ�Ŀ����ֵķ�λ��
			CString m_strFreqRange;		// Ƶ����Ϣ��̽�⵽��Ŀ��Ƶ����Ϣ
			CString m_strUAVType;		// ������Ϣ������Ƶ��������Ļ���
		public:
			void GetDetectData();
	};

	class CDetectReportPane : public CWnd
	{
		DECLARE_DYNAMIC(CDetectReportPane)

	public:
		CDetectReportPane();
		virtual ~CDetectReportPane();
	
	protected:
		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		afx_msg void OnClose();
		afx_msg void OnSize(UINT nType, int cx, int cy);
		DECLARE_MESSAGE_MAP()

	public:
		void UpdateDetectData();
		CDetectData m_dataDetect;

	protected:
		CXTPReportControl m_ReportCtrl;
	};
}