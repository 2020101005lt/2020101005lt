#pragma once
#include "MyBtn.h"
#include "resource.h"
#include "U_StaticTime.h"
#include "iledroundx_detect.h"
// CDlgToolbar 对话框

class CDlgToolbar : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgToolbar)

public:
	CDlgToolbar(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgToolbar();

// 对话框数据
	enum { IDD = IDD_DLG_TOOLBAR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	U_CStaticTime m_RunTime;
	DECLARE_MESSAGE_MAP()
public:
	// 设置软件和设备相关工作参数
	CMyBtn m_btnSetting;
	afx_msg void OnBnClickedBtnSetting();
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void UpdateRunTime();
	CIledroundx_detect m_iLedStatusD;
	CIledroundx_detect m_iLedStatusT;
};
