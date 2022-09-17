// UAV_Spider.h : main header file for the UAV_Spider application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CUAV_SpiderApp:
// See UAV_Spider.cpp for the implementation of this class
//

class CUAV_SpiderApp : public CWinApp
{
public:
	CUAV_SpiderApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CUAV_SpiderApp theApp;