// ChildFrm.cpp : implementation of the CChildFrame class
//
// Author: Ovidiu Cucu
// Homepage: http://www.codexpert.ro/
// Weblog: http://codexpert.ro/blog/

#include "stdafx.h"
#include "Demo.h"

#include "ChildFrm.h"
#include "VirtualListView.h"
#include "NonVirtualListView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
};

// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
    ON_WM_CREATE()
    ON_MESSAGE(CDemoApp::WM_UPDATESTATUSBAR, OnAppUpdateStatusBar)
END_MESSAGE_MAP()

// CChildFrame construction/destruction

CChildFrame::CChildFrame()
{
	// TODO: add member initialization code here
}

CChildFrame::~CChildFrame()
{
}

CString strClassName;

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	strClassName = AfxRegisterWndClass(CS_NOCLOSE | CS_HREDRAW | CS_VREDRAW);
    cs.lpszClass = strClassName;

	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

// CChildFrame message handlers

int CChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
        return -1;

   VERIFY(m_dlgBar.Create(this, IDD_DIALOGBAR, CBRS_TOP, IDD_DIALOGBAR)); 
   m_dlgBar.EnableDocking(CBRS_ALIGN_TOP|CBRS_ALIGN_BOTTOM);

	VERIFY(m_statusBar.Create(this));
	VERIFY(m_statusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT)));

   m_statusBar.SetPaneText(0, _T("Click on 'Query' button!"));

   EnableDocking(CBRS_ALIGN_ANY);
   DockControlBar(&m_dlgBar);

    return 0;
}

LRESULT CChildFrame::OnAppUpdateStatusBar(WPARAM wParam, LPARAM lParam)
{
    UINT nTime = (UINT)wParam;
    UINT nRecords = (UINT)lParam;
    CString strMessage;
    strMessage.Format(_T("%u records fetched in %u milliseconds"), nRecords, nTime);
    m_statusBar.SetPaneText(0, strMessage);

    return 0;
}


void CChildFrame::OnUpdateFrameTitle(BOOL bAddToTitle)
{
    CView* pView = GetActiveView();
    ASSERT_VALID(pView);

    if(pView->IsKindOf(RUNTIME_CLASS(CNonVirtualListView)))
    {
        SetWindowText(_T("Non-virtual list"));
    }
    else if(pView->IsKindOf(RUNTIME_CLASS(CVirtualListView)))
    {
        SetWindowText(_T("Virtual list"));
    }
    else
    {
        CMDIChildWnd::OnUpdateFrameTitle(bAddToTitle);
    }
}
