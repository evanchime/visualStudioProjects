
// MFCClientDemo.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include "ClientSocket.h"




// CMFCClientDemoApp:
// See MFCClientDemo.cpp for the implementation of this class
//

class CMFCClientDemoApp : public CWinApp
{
public:
	CMFCClientDemoApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCClientDemoApp theApp;