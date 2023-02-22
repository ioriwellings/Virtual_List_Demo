// DBListView.cpp : implementation file
//
// Author: Ovidiu Cucu
// Homepage: http://www.codexpert.ro/
// Weblog: http://codexpert.ro/blog/

#include "stdafx.h"
#include "Demo.h"
#include "DBListView.h"
#include "Query.h"


// CDBListView

IMPLEMENT_DYNAMIC(CDBListView, CListView)

CDBListView::CDBListView()
    : m_bIsFilling(FALSE)
{

}

CDBListView::~CDBListView()
{
}

void CDBListView::_ClearListHeader()
{
    CListCtrl& listCtrl = GetListCtrl(); 

    CHeaderCtrl* pHeader = listCtrl.GetHeaderCtrl();
    if(NULL != pHeader)
    {
        const int nColCount = pHeader->GetItemCount();
        for(int nCol = 0; nCol < nColCount; nCol++)
        {
            pHeader->DeleteItem(0);
        }
    }
}

void CDBListView::_ClearListItems()
{
    CListCtrl& listCtrl = GetListCtrl(); 
    listCtrl.DeleteAllItems();

    // performs additional cleaning in derived classes
    ClearList();
}

void CDBListView::_InsertColumns(LPCWSTR pszQuery)
{
    _ClearListHeader();

    CDemoApp* pApp = (CDemoApp*)AfxGetApp();
    CDataConnection& conn = pApp->GetDataConnection(); 
    ASSERT((bool)conn); // Database connection not open!

    Recordset rs;
    HRESULT hr = rs.Open(conn, pszQuery);
    ATLENSURE_SUCCEEDED(hr);

    CListCtrl& listCtrl = GetListCtrl(); 
    const size_t nColCount = rs.GetColumnCount();

    for(size_t nCol = 1; nCol <= nColCount; nCol++)
    {
        CString strColumnName = rs.GetColumnName(nCol);
        listCtrl.InsertColumn(nCol - 1, strColumnName, LVCFMT_LEFT, 100, nCol - 1);
    }
}

void CDBListView::_DoQuery(LPCWSTR pszQuery)
{
    m_bIsFilling = TRUE;
    try
    {
        CDemoApp* pApp = (CDemoApp*)AfxGetApp();
        CDataConnection& conn = pApp->GetDataConnection(); 
        ASSERT((bool)conn); // Database connection not open!

        _ClearListItems();

        Recordset rs;
        HRESULT hr = rs.Open(conn, pszQuery);
        ATLENSURE_SUCCEEDED(hr);

        DWORD dwStart = ::GetTickCount();
        UINT nRecords = FillList(rs);
        DWORD dwTime = GetTickCount() - dwStart;
        GetParentFrame()->SendMessage(CDemoApp::WM_UPDATESTATUSBAR, (WPARAM)dwTime, (LPARAM)nRecords);
    }
    catch(CException* e)
    {
        CString strMessage;
        CString strErrorDescription;
        e->GetErrorMessage(CStrBuf(strErrorDescription, 128), 128); 
        strMessage.Format(_T("Query failed.\nError: %s"), strErrorDescription);
        AfxMessageBox(strMessage);
        e->Delete();
    }

    m_bIsFilling = FALSE;
}

BEGIN_MESSAGE_MAP(CDBListView, CListView)
    ON_COMMAND(ID_DATABASE_QUERY, &CDBListView::OnDatabaseQuery)
    ON_UPDATE_COMMAND_UI(ID_DATABASE_QUERY, &CDBListView::OnUpdateDatabaseQuery)
END_MESSAGE_MAP()

// CDBListView message handlers


BOOL CDBListView::PreCreateWindow(CREATESTRUCT& cs)
{
    cs.style &= ~LVS_TYPEMASK;
    cs.style |= LVS_REPORT;

    return CListView::PreCreateWindow(cs);
}


void CDBListView::OnInitialUpdate()
{
    CListView::OnInitialUpdate();

    CListCtrl& listCtrl = GetListCtrl(); 
    listCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

    _InsertColumns(Query::pszOrdersQuery);
}

void CDBListView::OnDatabaseQuery()
{
    _DoQuery(Query::pszOrdersQuery);
}


void CDBListView::OnUpdateDatabaseQuery(CCmdUI *pCmdUI)
{
    pCmdUI->Enable(!m_bIsFilling);
}
