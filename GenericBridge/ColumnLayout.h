///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2021  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Library Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// ColumnLayout : Declaration of the CColumnLayout

#ifndef __ColumnLayout_H_
#define __ColumnLayout_H_

#include "resource.h"       // main symbols
#include <MathEx.h>
#include <vector>

typedef struct ColumnSpacingData
{
   ColumnSpacingData() { m_Overhang[0] = 0.0; m_Overhang[1] = 0.0; }

   bool operator==(const struct ColumnSpacingData& other) const
   {
      return (IsEqual(m_Overhang[0],other.m_Overhang[0]) && IsEqual(m_Overhang[1],other.m_Overhang[1]) && m_Spacing == other.m_Spacing);
   }

   std::vector<Float64> m_Spacing; // one item for each space between columns
   Float64 m_Overhang[2]; // Left and right cap beam overhang from CL exterior column (0=Left,1=Right)
} ColumnSpacingData;

/////////////////////////////////////////////////////////////////////////////
// CColumnLayout
class ATL_NO_VTABLE CColumnLayout : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CColumnLayout, &CLSID_ColumnLayout>,
	public ISupportErrorInfo,
	public IColumnLayout,
   public IStructuredStorage2,
   public IObjectSafetyImpl<CColumnLayout,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>
{
public:
	CColumnLayout()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

   void ClearColumns();
   void AddColumn(IColumn* column);
   void RenumberColumns();

DECLARE_REGISTRY_RESOURCEID(IDR_COLUMNLAYOUT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CColumnLayout)
	COM_INTERFACE_ENTRY(IColumnLayout)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(IObjectSafety)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

private:
   IPier* m_pPier; // weak reference
   ColumnSpacingData m_SpacingData;
   VARIANT_BOOL m_bUniform;
   Float64 m_UniformSpacing;

   ColumnIndexType m_RefColIdx; // index of the reference column
   Float64 m_RefColOffset; // offset of the reference column from the alignment

   std::vector<CComPtr<IColumn> > m_Columns;

   // Returns the number of columns as defined by the spacing object
   ColumnIndexType GetNumColumns() const;
   void PutColumn(ColumnIndexType columnIdx,IColumn* column);

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IColumnLayout
public:
   STDMETHOD(putref_Pier)(/*[in]*/IPier* pPier) override;
   STDMETHOD(get_Pier)(/*[out,retval]*/IPier** ppPier) override;
   STDMETHOD(get_Uniform)(/*[out,retval]*/ VARIANT_BOOL* bUniform) override;
   STDMETHOD(put_Uniform)(/*[in]*/ VARIANT_BOOL bUniform) override;
   STDMETHOD(get_Spacing)(/*[in]*/ SpacingIndexType spaceIdx,/*[out,retval]*/ Float64* space) override;
   STDMETHOD(put_Spacing)(/*[in]*/ SpacingIndexType spaceIdx,/*[in]*/ Float64 space) override;
   STDMETHOD(get_Overhang)(/*[in]*/ DirectionType side,/*[out,retval]*/ Float64* overhang) override;
   STDMETHOD(put_Overhang)(/*[in]*/ DirectionType side ,/*[in]*/ Float64 overhang) override;
   STDMETHOD(get_ColumnCount)(/*[out,retval]*/ ColumnIndexType* nColumns) override;
   STDMETHOD(put_ColumnCount)(/*[in]*/ColumnIndexType nColumns) override;
   STDMETHOD(Add)(/*[in]*/ ColumnIndexType nColumns) override;
   STDMETHOD(Insert)(/*[in]*/ SpacingIndexType spaceIdx,/*[in]*/ SpacingIndexType nInsert) override;
   STDMETHOD(Remove)(/*[in]*/ ColumnIndexType columnIdx,/*[in]*/ ColumnIndexType nRemove) override;
   STDMETHOD(SetReferenceColumn)(/*[in]*/ColumnIndexType colIdx,/*[in]*/Float64 alignmentOffset) override;
   STDMETHOD(GetReferenceColumn)(/*[out]*/ColumnIndexType* pColIdx,/*[out]*/Float64* pAlignmentOffset) override;
   STDMETHOD(get_Column)(/*[in]*/ ColumnIndexType colIdx,/*[out,retval]*/ IColumn* *column) override;
   STDMETHOD(get_ColumnLayoutWidth)(/*[out,retval]*/Float64* pCLW) override;
   STDMETHOD(get_ColumnLocation)(/*[in]*/ColumnIndexType colIdx,/*[out,retval]*/Float64* pXxb) override;
   STDMETHOD(get_ColumnOffset)(/*[in]*/ColumnIndexType colIdx,/*[out,retval]*/Float64* pOffset) override;
   STDMETHOD(get_TopColumnElevation)(/*[in]*/ColumnIndexType colIdx,/*[out,retval]*/Float64* pElev) override;
   STDMETHOD(get_BottomColumnElevation)(/*[in]*/ColumnIndexType colIdx,/*[out,retval]*/Float64* pElev) override;

// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave) override;
   STDMETHOD(Load)(IStructuredLoad2* pLoad) override;
};

#endif //__ColumnLayout_H_
