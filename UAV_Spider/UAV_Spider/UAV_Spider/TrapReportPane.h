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
		double m_dbLon;			// 经度
		double m_dbLat;			// 纬度
		double m_dbAlt;			// 高度
		CString m_strLon;
		CString m_strLat;
		CString m_strAlt;
		CString m_strNo;		// 编号：每天从1开始编号，过了0点重新开始
		CString m_strDate;			// 日期：当天日期
		CString m_strSwitchOnTime;	// 发射开始时间：24小时格式，精确到秒
		CString m_strSwitchOffTime;	// 发射结束时间：24小时格式，精确到秒
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