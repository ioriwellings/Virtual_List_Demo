// VirtualListView.h : interface of the CVirtualListView class
//
// Author: Ovidiu Cucu
// Homepage: http://www.codexpert.ro/
// Weblog: http://codexpert.ro/blog/

#pragma once
#include "DBListView.h"

class CDBRecord;

class CVirtualListView : public CDBListView
{
    DECLARE_DYNCREATE(CVirtualListView)

// Attributes
private:
   CTypedPtrArray<CObArray, CDBRecord*> m_arrRows;

// COnstruction
protected: // create from serialization only
	CVirtualListView();
public:
    ~CVirtualListView();

// Overrides
protected:
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    virtual void ClearList();
    virtual UINT FillList(Recordset& rs);

// Implementation
private:
    void _FreeArray();

// Message handlers
protected:
	DECLARE_MESSAGE_MAP()
    afx_msg void OnLvnGetdispinfo(NMHDR *pNMHDR, LRESULT *pResult);
};


