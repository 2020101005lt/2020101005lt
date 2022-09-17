#pragma once
#include "afxwin.h"
#include "MyBtn.h"

// CButtonDlg �Ի���

class CButtonDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CButtonDlg)

public:
	CButtonDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CButtonDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_BTN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_strKind;
	//CButton m_btn;
	//CBitmapButton m_btn;
	CMyBtn m_btn;
	CView * m_pParentView;
	afx_msg void OnBnClickedBtnMap();
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
