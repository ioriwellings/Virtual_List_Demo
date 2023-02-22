// MainFrm.h : interface of the CMainFrame class
//
// Author: Ovidiu Cucu
// Homepage: http://www.codexpert.ro/
// Weblog: http://codexpert.ro/blog/

#pragma once

class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
// Attributes
private:
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;

// Construction
public:
	CMainFrame();
    ~CMainFrame();

// Overrides
public:
//	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    virtual void OnUpdateFrameTitle(BOOL bAddToTitle);

// Message handlers
protected:
	DECLARE_MESSAGE_MAP()
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


