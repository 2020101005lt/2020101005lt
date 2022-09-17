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
			double m_dbLon;			// 经度
			double m_dbLat;			// 纬度
			double m_dbAlt;			// 高度
			CString m_strLon;
			CString m_strLat;
			CString m_strAlt;
			CString m_strNo;			// 编号：每天从1开始编号，过了0点重新开始
			CString m_strDate;			// 日期：当天日期
			CString m_strAppearTime;	// 出现时间：24小时格式，精确到秒
			CString m_strDisappearTime;	// 消失时间：24小时格式，精确到秒
			CString m_strAzimuth;		// 探测方位角：目标出现的方位角
			CString m_strFreqRange;		// 频段信息：探测到的目标频段信息
			CString m_strUAVType;		// 机型信息：根据频段推算出的机型
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