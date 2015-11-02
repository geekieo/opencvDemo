// Graph Cut.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols

//////////////////////////////////////////////////////////////////////////
#include "cv.h"
#include "cvaux.h"
#include "highgui.h"
#include "cxcore.h"
#define  IMAGE_WIDTH  256
#define  IMAGE_HEIGHT  256
#define  IMAGE_CHANNELS 3
//////////////////////////////////////////////////////////////////////////

// CGraphCutApp:
// See Graph Cut.cpp for the implementation of this class
//

class CGraphCutApp : public CWinApp
{
public:
	CGraphCutApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CGraphCutApp theApp;