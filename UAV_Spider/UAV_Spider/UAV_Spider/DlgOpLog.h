#pragma once
#include "afxcmn.h"


// CDlgOpLog 对话框

class CDlgOpLog : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgOpLog)

public:
	CDlgOpLog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgOpLog();

// 对话框数据
	enum { IDD = IDD_DLG_OPERATION_LOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	// 操作记录信息列表
	CListCtrl m_listLogMsg;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLvnItemchangedListOpLog(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
};
