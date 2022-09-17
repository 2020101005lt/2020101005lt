#pragma once


// CDlgTrapReport 对话框

class CDlgTrapReport : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgTrapReport)

public:
	CDlgTrapReport(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgTrapReport();

// 对话框数据
	enum { IDD = IDD_DLG_DETECT_REPORT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_lstTrap;
};
