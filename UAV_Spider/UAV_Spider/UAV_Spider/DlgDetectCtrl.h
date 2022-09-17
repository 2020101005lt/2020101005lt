#pragma once

#include "resource.h"
// CDlgDetectCtrl 对话框

class CDlgDetectCtrl : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgDetectCtrl)

public:
	CDlgDetectCtrl(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgDetectCtrl();

// 对话框数据
	enum { IDD = IDD_DLG_DETECT_CTRL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRadioDetectOn();
	afx_msg void OnBnClickedRadioDetectOff();
	afx_msg void OnBnClickedRadioFk();
	afx_msg void OnBnClickedRadioTc();
	afx_msg void OnBnClickedRadioTrackOn();
	afx_msg void OnBnClickedRadioTrackOff();
	afx_msg void OnBnClickedRadioUploadOn();
	afx_msg void OnBnClickedRadioUploadOff();
};
