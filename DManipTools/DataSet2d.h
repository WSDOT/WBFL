///////////////////////////////////////////////////////////////////////
// DManipTools - Direct Manipulation Tools
// Copyright © 1999-2015  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the Alternate Route Library Open Source License as published by 
// the Washington State Department of Transportation, Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but is distributed 
// AS IS, WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See the Alternate Route Library Open Source 
// License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License 
// along with this program; if not, write to the Washington State Department of 
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// DataSet2d.h : Declaration of the CDataSet2d

#ifndef __DATASET2D_H_
#define __DATASET2D_H_

#include "resource.h"       // main symbols
#include "WBFLComCollections.h"

class CDataSet2d;

typedef CComVectorCollection<IDataSet2d, IPoint2d, IEnumDataSet2d, &IID_IEnumDataSet2d> DSVectorImpl;
typedef CPersistentCollection<CDataSet2d, DSVectorImpl, 1.0> PersistentDSCollImpl;

/////////////////////////////////////////////////////////////////////////////
// CDataSet2d
class ATL_NO_VTABLE CDataSet2d : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CDataSet2d, &CLSID_DataSet2d>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CDataSet2d>,
   public PersistentDSCollImpl
{
public:
   CDataSet2d():
   m_Color(RGB(100,0,0)),
   m_SymbolType(dpstNone)
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_DATASET2D)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CDataSet2d)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY_CHAIN(PersistentDSCollImpl)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
END_COM_MAP()
BEGIN_CONNECTION_POINT_MAP(CDataSet2d)
END_CONNECTION_POINT_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IDataSet2d
public:
	STDMETHOD(get_Color)(/*[out, retval]*/ COLORREF *pVal);
	STDMETHOD(put_Color)(/*[in]*/ COLORREF newVal);
	STDMETHOD(get_Name)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Name)(/*[in]*/ BSTR newVal);
	STDMETHOD(Clone)(/*[out, retval]*/ IDataSet2d** clone);
   STDMETHOD(put_DataPointSymbolType)(DataPointSymbolType type);
   STDMETHOD(get_DataPointSymbolType)(DataPointSymbolType* type);

   virtual HRESULT SaveAdditionalProperties(IStructuredSave2 *save);
   virtual HRESULT LoadAdditionalProperties(IStructuredLoad2 *load);


   virtual HRESULT OnBeforeAdd ( DSVectorImpl::StoredType* pVal)
   {
      CHECK_IN(pVal);
      return S_OK;
   }

   virtual HRESULT OnBeforeRemove ( DSVectorImpl::StoredType* pVal, long id)
   {
      return S_OK;
   }

   virtual HRESULT OnAfterRemove ( long id)
   {
      return S_OK;
   }

   virtual HRESULT OnAfterAdd ( DSVectorImpl::ItemType* pVal, long id)
   {
      return S_OK;
   }
protected:
   CComBSTR m_Name;
   COLORREF m_Color;
   DataPointSymbolType m_SymbolType;
};

#endif //__DataSet2d_H_
