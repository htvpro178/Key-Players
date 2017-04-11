
// Keyplayers_GUI.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CKeyplayers_GUIApp:
// See Keyplayers_GUI.cpp for the implementation of this class
//

class CKeyplayers_GUIApp : public CWinApp
{
public:
	CKeyplayers_GUIApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CKeyplayers_GUIApp theApp;