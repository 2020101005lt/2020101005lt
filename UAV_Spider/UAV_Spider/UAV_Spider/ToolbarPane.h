#pragma once
#include "DlgToolbar.h"

// CToolbarPane

class CToolbarPane : public CWnd
{
	DECLARE_DYNAMIC(CToolbarPane)

public:
	CToolbarPane();
	virtual ~CToolbarPane();
	CDlgToolbar m_dlgEmbedded;
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


