// NonVirtualListView.cpp : implementation file
//
// Author: Ovidiu Cucu
// Homepage: http://www.codexpert.ro/
// Weblog: http://codexpert.ro/blog/

#include "stdafx.h"
#include "Demo.h"
#include "NonVirtualListView.h"
#include "DBValue.h"
#include "Query.h"

// CNonVirtualListView

IMPLEMENT_DYNCREATE(CNonVirtualListView, CDBListView)

CNonVirtualListView::CNonVirtualListView()
{

}

CNonVirtualListView::~CNonVirtualListView()
{
}

void CNonVirtualListView::ClearList()
{
}

UINT CNonVirtualListView::FillList(Recordset& rs)
{
    UINT nRecords = 0;
    CListCtrl& listCtrl = GetListCtrl(); 

    const size_t nColCount = rs.GetColumnCount();
    HRESULT hr = rs.MoveFirst();
    while(SUCCEEDED(hr) && (hr != DB_S_ENDOFROWSET))
    {
        const int nItem = listCtrl.InsertItem(nRecords, NULL);
        for(size_t nCol = 1; nCol <= nColCount; nCol++)
        {
            CDBValue dbValue(rs, nCol);
            listCtrl.SetItemText(nItem, nCol - 1, dbValue.GetString());

        }
        nRecords++;
        hr = rs.MoveNext();
    }
    return nRecords;
}

BEGIN_MESSAGE_MAP(CNonVirtualListView, CDBListView)
END_MESSAGE_MAP()

