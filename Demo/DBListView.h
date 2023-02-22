//
// Author: Ovidiu Cucu
// Homepage: http://www.codexpert.ro/
// Weblog: http://codexpert.ro/blog/

#pragma once

// CDBListView view

class CDBListView : public CListView
{
	DECLARE_DYNAMIC(CDBListView)
// Attributes
private:
    BOOL m_bIsFilling;

protected:
	CDBListView();           // protected constructor used by dynamic creation
	virtual ~CDBListView();

// Overrides
protected:
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    virtual void ClearList() = 0;
    virtual UINT FillList(Recordset& rs) = 0;

// Implementation
private:
    void _InsertColumns(LPCWSTR pszQuery);
    void _DoQuery(LPCWSTR pszQuery);
    void _ClearListHeader();
    void _ClearListItems();

// Message handlers
protected:
	DECLARE_MESSAGE_MAP()
    virtual void OnInitialUpdate();
    afx_msg void OnDatabaseQuery();
    afx_msg void OnUpdateDatabaseQuery(CCmdUI *pCmdUI);
};


