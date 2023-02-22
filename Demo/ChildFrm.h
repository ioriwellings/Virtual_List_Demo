// ChildFrm.h : interface of the CChildFrame class
//
// Author: Ovidiu Cucu
// Homepage: http://www.codexpert.ro/
// Weblog: http://codexpert.ro/blog/

#pragma once

class CChildFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CChildFrame)

// Attributes
private:
    CDialogBar m_dlgBar;
    CStatusBar m_statusBar;

// Construction
public:
	CChildFrame();
    virtual ~CChildFrame();

// Overrides
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    virtual void OnUpdateFrameTitle(BOOL bAddToTitle);
	
// Messages handlers
protected:
	DECLARE_MESSAGE_MAP()
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg LRESULT OnAppUpdateStatusBar(WPARAM wParam, LPARAM lParam);
    
};
