//
// Author: Ovidiu Cucu
// Homepage: http://www.codexpert.ro/
// Weblog: http://codexpert.ro/blog/

#include "StdAfx.h"
#include "DBRecord.h"
#include "DBValue.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC(CDBRecord, CObject)

CDBRecord::CDBRecord()
{
}

CDBRecord::~CDBRecord()
{
   Free();
}

INT_PTR CDBRecord::AddValue(CDBValue* pValue)
{
   ASSERT_KINDOF(CDBValue, pValue);
   return m_arrValues.Add(pValue);
}

void CDBRecord::SetAt(INT_PTR nIndex, CDBValue* pValue)
{
   ASSERT_KINDOF(CDBValue, pValue);
   ASSERT(nIndex >= 0);
   ASSERT(nIndex < m_arrValues.GetSize());
   m_arrValues.SetAt(nIndex, pValue);
}

INT_PTR CDBRecord::GetSize() const
{
   return m_arrValues.GetSize();
}

void CDBRecord::SetSize(INT_PTR nNewSize, INT_PTR nGrowBy /*= -1*/)
{
   m_arrValues.SetSize(nNewSize, nGrowBy);
}

CDBValue* CDBRecord::GetAt(INT_PTR nIndex) const
{
   ASSERT(nIndex >= 0);
   ASSERT(nIndex < m_arrValues.GetSize());

   return m_arrValues.GetAt(nIndex);
}

void CDBRecord::Free()
{
   const INT_PTR nSize = GetSize();
   for(INT_PTR nIndex = 0; nIndex < nSize; nIndex++)
   {
      CDBValue* pValue = m_arrValues.GetAt(nIndex);
      delete pValue;
   }
   m_arrValues.RemoveAll();
}
