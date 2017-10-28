
// MFCComboBox.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCComboBoxApp:
// See MFCComboBox.cpp for the implementation of this class
//

class CMFCComboBoxApp : public CWinApp
{
public:
	CMFCComboBoxApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCComboBoxApp theApp;