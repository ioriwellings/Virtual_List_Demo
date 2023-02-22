// Demo.h : main header file for the Demo application
//
// Author: Ovidiu Cucu
// Homepage: http://www.codexpert.ro/
// Weblog: http://codexpert.ro/blog/

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols

// CDemoApp:
// See Demo.cpp for the implementation of this class
//

class CDemoApp : public CWinApp
{
// Attributes
public:
    enum e_AppMessages{WM_UPDATESTATUSBAR = WM_APP + 1,};
private:
    CDataConnection m_conn;

public:
	CDemoApp();

// Operations
public:
    CDataConnection& GetDataConnection() {return m_conn;}

// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
private:
    void _OpenConnection();
    CStringW _GetDatabasePath();

// Message handlers
protected:
	DECLARE_MESSAGE_MAP()
    afx_msg void OnAppAbout();
    afx_msg void OnFileNew();
};

extern CDemoApp theApp;
