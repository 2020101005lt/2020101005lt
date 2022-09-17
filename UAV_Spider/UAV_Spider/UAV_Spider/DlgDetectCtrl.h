#pragma once

#include "resource.h"
// CDlgDetectCtrl �Ի���

class CDlgDetectCtrl : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgDetectCtrl)

public:
	CDlgDetectCtrl(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgDetectCtrl();

// �Ի�������
	enum { IDD = IDD_DLG_DETECT_CTRL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
