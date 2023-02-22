//
// Author: Ovidiu Cucu
// Homepage: http://www.codexpert.ro/
// Weblog: http://codexpert.ro/blog/

#pragma once

class CDBValue : public CObject
{
    DECLARE_DYNAMIC(CDBValue)

// Attributes
private:
    variant_t m_vtValue;
    DBTYPE m_type;
    DBTIMESTAMP m_tsValue;


// Construction
public:
    CDBValue(Recordset& rs, DBORDINAL nColumn);
    ~CDBValue();

// Operations
public:
    const CString GetString() const;
};

