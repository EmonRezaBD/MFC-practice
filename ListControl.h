
// ListControl.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CListControlApp:
// See ListControl.cpp for the implementation of this class
//

class CListControlApp : public CWinApp
{
public:
	CListControlApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CListControlApp theApp;