#pragma once
#include "afxcmn.h"


// CDlgDetectReport �Ի���

class CDlgDetectReport : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgDetectReport)

public:
	CDlgDetectReport(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgDetectReport();

// �Ի�������
	enum { IDD = IDD_DLG_DETECT_REPORT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_lstDetect;
};
