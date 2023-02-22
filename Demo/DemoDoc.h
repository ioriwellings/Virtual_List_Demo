// DemoDoc.h : interface of the CDemoDoc class
//
// Author: Ovidiu Cucu
// Homepage: http://www.codexpert.ro/
// Weblog: http://codexpert.ro/blog/

#pragma once

class CDemoDoc : public CDocument
{
    DECLARE_DYNCREATE(CDemoDoc)

protected: // create from serialization only
	CDemoDoc();

public:
	virtual ~CDemoDoc();

// Message handlers
protected:
	DECLARE_MESSAGE_MAP()
};
