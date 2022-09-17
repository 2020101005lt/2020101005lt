#pragma once

#include "DlgTrapCtrl.h"
// CTrapCtrlPane

class CTrapCtrlPane : public CWnd
{
	DECLARE_DYNAMIC(CTrapCtrlPane)

public:
	CTrapCtrlPane();
	virtual ~CTrapCtrlPane();
	CDlgTrapCtrl m_dlgEmbedded;
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


