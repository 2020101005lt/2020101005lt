#pragma once

#include "DlgDetectCtrl.h"
// CDetectCtrlPane

class CDetectCtrlPane : public CWnd
{
	DECLARE_DYNAMIC(CDetectCtrlPane)

public:
	CDetectCtrlPane();
	virtual ~CDetectCtrlPane();

	CDlgDetectCtrl m_dlgEmbedded;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
};


