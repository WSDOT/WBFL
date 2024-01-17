///////////////////////////////////////////////////////////////////////
// GenericBridgeTools - Tools for manipluating the Generic Bridge Modeling
// Copyright © 1999-2024  Washington State Department of Transportation
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

// RebarSection.h : Declaration of the CRebarSection

#ifndef __RebarSection_H_
#define __RebarSection_H_

#include "resource.h"       // main symbols
#include "WBFLComCollections.h"

class CRebarSection;
using RSIColl = CComVectorCollection<IRebarSection, IRebarSectionItem, IEnumRebarSectionItem, &IID_IEnumRebarSectionItem, IndexType>;
using PersistentRebarSection = CPersistentCollection<CRebarSection,RSIColl,IndexType>;

/////////////////////////////////////////////////////////////////////////////
// CRebarSection
class ATL_NO_VTABLE CRebarSection : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CRebarSection,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CRebarSection, &CLSID_RebarSection>,
	public ISupportErrorInfo,
   public PersistentRebarSection,
   public IObjectSafetyImpl<CRebarSection,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>
{
public:
   CRebarSection()
	{
	}

   void FinalRelease();
   void SetBridge(IGenericBridge* bridge);

DECLARE_REGISTRY_RESOURCEID(IDR_REBARSECTION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CRebarSection)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY_CHAIN(PersistentRebarSection)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

protected:
   CComBSTR GetCollectionName() { return CComBSTR("RebarSection"); }
   CComBSTR GetStoredName()     { return CComBSTR("RebarSectionItem");  }
   HRESULT DoSaveItem(IStructuredSave2* save,IRebarSectionItem* item);
   HRESULT DoLoadItem(IStructuredLoad2* load,IRebarSectionItem* *ppItem);

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IRebarSection
public:
   //STDMETHOD(get__NewEnum)(/*[out, retval]*/ IUnknown** retval) override;  
   //STDMETHOD(get_Item)(/*[in]*/ long index, /*[out, retval]*/ IRebarSectionItem* *pVal) override;
   //STDMETHOD(get_Count)(/*[out,retval]*/ long* count) override;
   STDMETHOD(get__EnumRebarSectionItem)(/*[out,retval]*/IEnumRebarSectionItem* *enumRSI) override;
};

#endif //__RebarSection_H_
