// VirtualListView.cpp : implementation of the CVirtualListView class
//
// Author: Ovidiu Cucu
// Homepage: http://www.codexpert.ro/
// Weblog: http://codexpert.ro/blog/

#include "stdafx.h"
#include "Demo.h"

#include "DemoDoc.h"
#include "VirtualListView.h"
#include "DBRecord.h"
#include "DBValue.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CVirtualListView

IMPLEMENT_DYNCREATE(CVirtualListView, CDBListView)

BEGIN_MESSAGE_MAP(CVirtualListView, CDBListView)
    ON_NOTIFY_REFLECT(LVN_GETDISPINFO, &CVirtualListView::OnLvnGetdispinfo)
END_MESSAGE_MAP()

// CVirtualListView construction/destruction

CVirtualListView::CVirtualListView()
{
	// TODO: add construction code here
}

CVirtualListView::~CVirtualListView()
{
	_FreeArray();

}

void CVirtualListView::ClearList()
{
    _FreeArray();
}

UINT CVirtualListView::FillList(Recordset& rs)
{
    UINT nRecords = 0;
    _FreeArray();

    const size_t nColCount = rs.GetColumnCount();
    HRESULT hr = rs.MoveFirst();
    while(SUCCEEDED(hr) && (hr != DB_S_ENDOFROWSET))
    {
        CDBRecord* pRecord = new CDBRecord;
        pRecord->SetSize(nColCount);
        for(size_t nCol = 1; nCol <= nColCount; nCol++)
        {
            CDBValue* pDBValue = new CDBValue(rs, nCol);
            pRecord->SetAt(nCol - 1, pDBValue);
        }
        m_arrRows.Add(pRecord);
        nRecords++;
        hr = rs.MoveNext();
    }

    CListCtrl& listCtrl = GetListCtrl(); 
    listCtrl.SetItemCount(nRecords);
    return nRecords;
}

BOOL CVirtualListView::PreCreateWindow(CREATESTRUCT& cs)
{
    cs.style |= LVS_OWNERDATA;

	return CDBListView::PreCreateWindow(cs);
}

void CVirtualListView::_FreeArray()
{
   const INT_PTR nSize = m_arrRows.GetSize();
   for(INT_PTR nIndex = 0; nIndex < nSize; nIndex++)
   {
      CDBRecord* pRow = m_arrRows.GetAt(nIndex);
      delete pRow;
   }
   m_arrRows.RemoveAll();
}

// CVirtualListView message handlers

void CVirtualListView::OnLvnGetdispinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
    NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
    LV_ITEM* pItem = &(pDispInfo)->item;

   if(pItem->mask & LVIF_TEXT)
   {
      // Set the text for the given item 
      // (use pItem->iItem, pItem->iSubItem, pItem->pszText, and pItem->cchTextMax)
      CDBRecord* pRow = m_arrRows.GetAt(pItem->iItem);
      CDBValue* pValue = pRow->GetAt(pItem->iSubItem);
      _tcscpy_s(pItem->pszText, pItem->cchTextMax, pValue->GetString());
   }
    *pResult = 0;
}
