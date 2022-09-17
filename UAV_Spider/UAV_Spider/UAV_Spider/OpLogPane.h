#pragma once
#include "DlgOpLog.h"

// COpLogPane

class COpLogPane : public CWnd
{
	DECLARE_DYNAMIC(COpLogPane)

public:
	COpLogPane();
	virtual ~COpLogPane();
	CDlgOpLog m_dlgEmbedded;
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
};


