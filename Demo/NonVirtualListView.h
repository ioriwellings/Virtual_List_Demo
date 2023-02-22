//
// Author: Ovidiu Cucu
// Homepage: http://www.codexpert.ro/
// Weblog: http://codexpert.ro/blog/

#pragma once
#include "DBListView.h"

// CNonVirtualListView view

class CNonVirtualListView : public CDBListView
{
	DECLARE_DYNCREATE(CNonVirtualListView)

// Construction
protected:
	CNonVirtualListView(); 
	virtual ~CNonVirtualListView();

// Overrides
protected:
    virtual void ClearList();
    virtual UINT FillList(Recordset& rs);   

// Message handlers
protected:
	DECLARE_MESSAGE_MAP()
};


