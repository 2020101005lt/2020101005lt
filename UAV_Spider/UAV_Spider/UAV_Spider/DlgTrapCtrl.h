#pragma once


// CDlgTrapCtrl 对话框

class CDlgTrapCtrl : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgTrapCtrl)

public:
	CDlgTrapCtrl(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgTrapCtrl();

// 对话框数据
	enum { IDD = IDD_DLG_TRAP_CTRL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnSendTime();
	afx_msg void OnBnClickedRadioTrapOn();
	afx_msg void OnBnClickedRadioTrapOff();
	afx_msg void OnBnClickedRadioLdOn();
	afx_msg void OnBnClickedRadioLdOff();
	afx_msg void OnBnClickedButtonSendcom();
};
