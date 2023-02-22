//
// Author: Ovidiu Cucu
// Homepage: http://www.codexpert.ro/
// Weblog: http://codexpert.ro/blog/

#include "StdAfx.h"
#include "DBValue.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC(CDBValue, CObject)

CDBValue::CDBValue(Recordset& rs, DBORDINAL nColumn)
{
    rs.GetColumnType(nColumn, &m_type);
    switch(m_type)
    {
    case DBTYPE_NULL:
        m_vtValue.ChangeType(VT_NULL);
        break;
    case DBTYPE_WSTR:
        m_vtValue = (WCHAR*)rs.GetValue(nColumn);
        break;
    case DBTYPE_STR:
        m_vtValue.SetString((CHAR*)rs.GetValue(nColumn));
        break;
    case DBTYPE_I2:
        m_vtValue.ChangeType(VT_I2);
        rs.GetValue(nColumn, &m_vtValue.iVal);
        break;
    case DBTYPE_I4:
        m_vtValue.ChangeType(VT_I4);
        rs.GetValue(nColumn, &m_vtValue.lVal);
        break;
    case DBTYPE_CY:
        m_vtValue.ChangeType(VT_CY);
        rs.GetValue(nColumn, &m_vtValue.cyVal);
        break;
    case DBTYPE_DBTIMESTAMP:
        rs.GetValue(nColumn, &m_tsValue);
        break;
    case DBTYPE_R4:
        m_vtValue.ChangeType(VT_R4);
        rs.GetValue(nColumn, &m_vtValue.fltVal);
        break;
    case DBTYPE_R8:
        m_vtValue.ChangeType(VT_R8);
        rs.GetValue(nColumn, &m_vtValue.dblVal);
        break;
    case DBTYPE_BOOL:
        m_vtValue.ChangeType(VT_BOOL);
        rs.GetValue(nColumn, &m_vtValue.boolVal);
        break;
    default:
        ATLTRACE("\nUNKNOWN TYPE = %u", m_type);
        break;
    }
}

CDBValue::~CDBValue()
{
}

const CString CDBValue::GetString() const
{
    CString strValue;
    VT_I2;
    switch(m_type)
    {
    case DBTYPE_NULL:
        strValue = _T("[NULL]");
        break;
    case DBTYPE_WSTR:
    case DBTYPE_STR:
        strValue = m_vtValue;
        break;
    case DBTYPE_I2:
        strValue.Format(_T("%d"), (short)m_vtValue);
        break;
    case DBTYPE_I4:
        strValue.Format(_T("%d"), (long)m_vtValue);
        break;
    case DBTYPE_CY:
        strValue = COleCurrency((CY)m_vtValue).Format();
        break;
    case DBTYPE_DBTIMESTAMP:
       strValue = COleDateTime(m_tsValue).Format();
        break;
    case DBTYPE_R4:
        strValue.Format(_T("%f"), (float)m_vtValue); 
        break;
    case DBTYPE_R8:
        strValue.Format(_T("%f"), (double)m_vtValue);
        break;
    case DBTYPE_BOOL:
        strValue = (bool)m_vtValue ? _T("[TRUE]") : _T("[FALSE]"); 
        break;
    default:
        ATLTRACE("\nUNKNOWN TYPE = %u", m_type);
        break;
    }
    return strValue;
}