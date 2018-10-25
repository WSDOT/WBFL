///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2015  Washington State Department of Transportation
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

// ColumnSpacing.h : Declaration of the CColumnSpacing

#ifndef __COLUMNSPACING_H_
#define __COLUMNSPACING_H_

#include "resource.h"       // main symbols
#include "GenericBridgeCP.h"
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
// CColumnSpacing
class ATL_NO_VTABLE CColumnSpacing : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CColumnSpacing, &CLSID_ColumnSpacing>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CColumnSpacing>,
	public IColumnSpacing,
   public IStructuredStorage2,
   public IObjectSafetyImpl<CColumnSpacing,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public CProxyDColumnSpacingEvents< CColumnSpacing >
{
public:
	CColumnSpacing()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

   void SetBridge(IGenericBridge* pBridge);
   Float64 GetCrossBeamWidth();

   STDMETHOD(Clone)(IColumnSpacing* *clone);
   void ClearColumns();
   void AddColumn(IColumn* column);

DECLARE_REGISTRY_RESOURCEID(IDR_COLUMNSPACING)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CColumnSpacing)
	COM_INTERFACE_ENTRY(IColumnSpacing)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(IObjectSafety)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
   COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CColumnSpacing)
CONNECTION_POINT_ENTRY(IID_IColumnSpacingEvents)
END_CONNECTION_POINT_MAP()

private:
   IGenericBridge* m_pBridge; // weak reference to parent
   ColumnSpacingData m_SpacingData;
   VARIANT_BOOL m_bUniform;
   Float64 m_UniformSpacing;

   std::vector<CComPtr<IColumn> > m_Columns;

   // Returns the number of columns as defined by the spacing object
   ColumnIndexType GetNumColumns() const;
   void PutColumn(ColumnIndexType columnIdx,IColumn* column);

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IColumnSpacing
public:
   STDMETHOD(get_Uniform)(/*[out,retval]*/ VARIANT_BOOL* bUniform);
   STDMETHOD(put_Uniform)(/*[in]*/ VARIANT_BOOL bUniform);
   STDMETHOD(get_Spacing)(/*[in]*/ SpacingIndexType spaceIdx,/*[out,retval]*/ Float64* space);
   STDMETHOD(put_Spacing)(/*[in]*/ SpacingIndexType spaceIdx,/*[in]*/ Float64 space);
   STDMETHOD(get_Overhang)(/*[in]*/ DirectionType side,/*[out,retval]*/ Float64* overhang);
   STDMETHOD(put_Overhang)(/*[in]*/ DirectionType side ,/*[in]*/ Float64 overhang);
   STDMETHOD(get_ColumnCount)(/*[out,retval]*/ ColumnIndexType* nColumns);
   STDMETHOD(Add)(/*[in]*/ ColumnIndexType nColumns);
   STDMETHOD(Insert)(/*[in]*/ SpacingIndexType spaceIdx,/*[in]*/ SpacingIndexType nInsert);
   STDMETHOD(Remove)(/*[in]*/ ColumnIndexType columnIdx,/*[in]*/ ColumnIndexType nRemove);
   STDMETHOD(get_Column)(/*[in]*/ ColumnIndexType colIdx,/*[out,retval]*/ IColumn* *column);

// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave);
   STDMETHOD(Load)(IStructuredLoad2* pLoad);
};

#endif //__COLUMNSPACING_H_
