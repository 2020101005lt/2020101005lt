#pragma once
#include "afxcmn.h"


// CDlgOpLog �Ի���

class CDlgOpLog : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgOpLog)

public:
	CDlgOpLog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgOpLog();

// �Ի�������
	enum { IDD = IDD_DLG_OPERATION_LOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	// ������¼��Ϣ�б�
	CListCtrl m_listLogMsg;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLvnItemchangedListOpLog(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
};
