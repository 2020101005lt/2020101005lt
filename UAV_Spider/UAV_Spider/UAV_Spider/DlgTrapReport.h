#pragma once


// CDlgTrapReport �Ի���

class CDlgTrapReport : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgTrapReport)

public:
	CDlgTrapReport(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgTrapReport();

// �Ի�������
	enum { IDD = IDD_DLG_DETECT_REPORT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_lstTrap;
};
