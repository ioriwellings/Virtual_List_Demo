//
// Author: Ovidiu Cucu
// Homepage: http://www.codexpert.ro/
// Weblog: http://codexpert.ro/blog/

#pragma once

class CDBValue;
class CDBRecord : public CObject
{
   DECLARE_DYNAMIC(CDBRecord)

// Attributes
private:
   CTypedPtrArray<CObArray, CDBValue*> m_arrValues;

// Contruction
public:
   CDBRecord();
   ~CDBRecord();

// Operations
public:
   INT_PTR AddValue(CDBValue* pValue);
   void SetAt(INT_PTR nIndex, CDBValue* pValue);
   INT_PTR GetSize() const;
   void SetSize(INT_PTR nNewSize, INT_PTR nGrowBy = -1);
   CDBValue* GetAt(INT_PTR nIndex) const;
   void Free();
};

