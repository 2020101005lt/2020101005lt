#pragma once
#include "afxcmn.h"


// CDlgDetectReport 对话框

class CDlgDetectReport : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgDetectReport)

public:
	CDlgDetectReport(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgDetectReport();

// 对话框数据
	enum { IDD = IDD_DLG_DETECT_REPORT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_lstDetect;
};
