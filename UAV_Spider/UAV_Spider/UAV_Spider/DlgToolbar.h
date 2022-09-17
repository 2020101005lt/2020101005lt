#pragma once
#include "MyBtn.h"
#include "resource.h"
#include "U_StaticTime.h"
#include "iledroundx_detect.h"
// CDlgToolbar �Ի���

class CDlgToolbar : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgToolbar)

public:
	CDlgToolbar(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgToolbar();

// �Ի�������
	enum { IDD = IDD_DLG_TOOLBAR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	U_CStaticTime m_RunTime;
	DECLARE_MESSAGE_MAP()
public:
	// ����������豸��ع�������
	CMyBtn m_btnSetting;
	afx_msg void OnBnClickedBtnSetting();
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void UpdateRunTime();
	CIledroundx_detect m_iLedStatusD;
	CIledroundx_detect m_iLedStatusT;
};
