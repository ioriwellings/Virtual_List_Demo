// Demo.cpp : Defines the class behaviors for the application.
//
// Author: Ovidiu Cucu
// Homepage: http://www.codexpert.ro/
// Weblog: http://codexpert.ro/blog/

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "Demo.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "DemoDoc.h"
#include "VirtualListView.h"
#include "NonVirtualListView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDemoApp

BEGIN_MESSAGE_MAP(CDemoApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CDemoApp::OnAppAbout)
    ON_COMMAND(ID_FILE_NEW, &CDemoApp::OnFileNew)
END_MESSAGE_MAP()


// CDemoApp construction

CDemoApp::CDemoApp()
{
	// TODO: replace application ID string below with unique ID string; recommended
	// format for string is CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("Demo.AppID.NoVersion"));

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CDemoApp object

CDemoApp theApp;

// CDemoApp initialization

BOOL CDemoApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

    // Try to open database connection
    try
    {
        _OpenConnection();
    }
    catch(CException* e)
    {
        CString strMessage;
        CString strErrorDescription;
        e->GetErrorMessage(CStrBuf(strErrorDescription, 128), 128); 
        strMessage.Format(_T("Open connection failed.\nError: %s"), strErrorDescription);
        AfxMessageBox(strMessage);
        e->Delete();
        return FALSE;
    }

	AfxEnableControlContainer();
	EnableTaskbarInteraction(FALSE);


	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings(0);  // Load standard INI file options (including MRU)


	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CMultiDocTemplate* pDocTemplate = NULL;
	pDocTemplate = new CMultiDocTemplate(IDR_DemoTYPE,
		RUNTIME_CLASS(CDemoDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CVirtualListView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	pDocTemplate = new CMultiDocTemplate(IDR_DemoTYPE,
		RUNTIME_CLASS(CDemoDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CNonVirtualListView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

    // CNonVirtualListView

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;
	// call DragAcceptFiles only if there's a suffix
	//  In an MDI app, this should occur immediately after setting m_pMainWnd

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// The main window has been initialized, so show and update it
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

int CDemoApp::ExitInstance()
{
	//TODO: handle additional resources you may have added
	AfxOleTerm(FALSE);
	return CWinApp::ExitInstance();
}

/*****************************************************************************************************
   IMPORTANT NOTES:
******************************************************************************************************
   1. This implementation is just for demo purpose and contains hard-coded stuff.
      It assumes having 'nortwhind.sdf' SQL Server Compact version 4.0 database in the solution folder. 
   2. Here you can download and install Microsoft SQL Server Compact 4.0 run-time
      http://www.microsoft.com/en-us/download/details.aspx?id=17876
******************************************************************************************************/

void CDemoApp::_OpenConnection()
{
    CStringW strInitializationString;
    CStringW strDatabasePath = _GetDatabasePath();
    strInitializationString.Format(L"Provider=Microsoft.SQLSERVER.CE.OLEDB.4.0;"
        L"Data Source=%s;",
        strDatabasePath);

    HRESULT hr = m_conn.Open(strInitializationString);
    ATLENSURE_SUCCEEDED(hr);

}

CStringW CDemoApp::_GetDatabasePath()
{
    CStringW strDatabasePath;
    ::GetModuleFileNameW(NULL, CStrBufW(strDatabasePath, MAX_PATH), MAX_PATH);
    ::PathRemoveFileSpecW(CStrBufW(strDatabasePath, MAX_PATH));
    ::PathRemoveFileSpecW(CStrBufW(strDatabasePath, MAX_PATH));
    ::PathAppendW(CStrBufW(strDatabasePath, MAX_PATH), L"northwind.sdf");
    if(! ::PathFileExistsW(strDatabasePath))
    {
        CString strMessage;
        strMessage.Format(_T("Could not find database\n'%ls'"), strDatabasePath);
        AfxMessageBox(strMessage);
        AtlThrow(HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND));
    }
    return strDatabasePath;
}

// CDemoApp message handlers

void CDemoApp::OnFileNew()
{
   POSITION pos = GetFirstDocTemplatePosition();
   while(NULL != pos)
   {
      CDocTemplate* pDocTemplate = GetNextDocTemplate(pos);
      ASSERT_VALID(pDocTemplate);
      pDocTemplate->OpenDocumentFile(NULL);
   }
}


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// App command to run the dialog
void CDemoApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

