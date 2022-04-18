///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2022  Washington State Department of Transportation
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

// Column.h : Declaration of the CColumn

#ifndef __COLUMN_H_
#define __COLUMN_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CColumn
class ATL_NO_VTABLE CColumn : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CColumn, &CLSID_Column>,
	public ISupportErrorInfo,
	public IColumn,
   public IStructuredStorage2,
   public IObjectSafetyImpl<CColumn,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>
{
public:
	CColumn()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_COLUMN)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CColumn)
	COM_INTERFACE_ENTRY(IColumn)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

private:
   Float64 m_Height;
   Float64 m_BaseElevation;
   Float64 m_BaseOffset;

   bool m_bComputeBaseElevation;
   bool m_bComputeHeight;

   IColumnLayout* m_pColumnLayout; // weak reference

   IndexType m_Index;

   void ComputeHeight();
   void ComputeBaseElevation();

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IColumn
public:
   STDMETHOD(putref_ColumnLayout)(/*[in]*/IColumnLayout* pColumnLayout) override;
   STDMETHOD(get_ColumnLayout)(/*[out,retval]*/IColumnLayout** ppColumnLayout) override;
   STDMETHOD(put_Index)(/*[in]*/IndexType index) override;
   STDMETHOD(get_Index)(/*[out,retval]*/IndexType* pIndex) override;
   STDMETHOD(get_Height)(/*[out,retval]*/ Float64* height) override;
   STDMETHOD(put_Height)(/*[in]*/ Float64 height) override;
   STDMETHOD(get_BaseElevation)(/*[out,retval]*/ Float64* baseElevation) override;
   STDMETHOD(put_BaseElevation)(/*[in]*/ Float64 baseElevation) override;
   STDMETHOD(get_BaseOffset)(/*[out,retval]*/ Float64* offset) override;
   STDMETHOD(put_BaseOffset)(/*[in]*/ Float64 offset) override;
   STDMETHOD(get_Length)(/*[out,retval]*/ Float64* length) override;
   STDMETHOD(get_TopElevation)(/*[out,retval]*/Float64* topElev) override;
   STDMETHOD(Clone)(/*[out,retval]*/IColumn** ppClone) override;

// IStructuredStorage2
public:
	STDMETHOD(Load)(/*[in]*/ IStructuredLoad2* load) override;
	STDMETHOD(Save)(/*[in]*/ IStructuredSave2* save) override;
};

#endif //__COLUMN_H_
