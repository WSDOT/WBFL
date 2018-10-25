///////////////////////////////////////////////////////////////////////
// GenericBridgeTools - Tools for manipluating the Generic Bridge Modeling
// Copyright © 1999-2016, Washington State Department of Transportation, All Rights Reserved
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
//
// FixedLengthRebarLayoutItem.h : Declaration of the CFixedLengthRebarLayoutItem

#pragma once
#include "resource.h"       // main symbols

#include "WBFLComCollections.h"
#include "GenericBridgeToolsCP.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

class CFixedLengthRebarLayoutItem;
typedef CComVectorCollection<IFixedLengthRebarLayoutItem,IRebarPattern,IEnumRebarPatterns,&IID_IEnumRebarPatterns,CollectionIndexType> FixedPtrnColl;
typedef CPersistentCollection<CFixedLengthRebarLayoutItem,FixedPtrnColl,CollectionIndexType> PersistentFixedLengthRebarLayoutItem;


// CFixedLengthRebarLayoutItem
class ATL_NO_VTABLE CFixedLengthRebarLayoutItem :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CFixedLengthRebarLayoutItem, &CLSID_FixedLengthRebarLayoutItem>,
	public ISupportErrorInfo,
   public PersistentFixedLengthRebarLayoutItem,
   public IObjectSafetyImpl<CFixedLengthRebarLayoutItem,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>
{
public:
	CFixedLengthRebarLayoutItem()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_FIXEDLENGTHREBARLAYOUTITEM)


BEGIN_COM_MAP(CFixedLengthRebarLayoutItem)
	COM_INTERFACE_ENTRY(IFixedLengthRebarLayoutItem)
	COM_INTERFACE_ENTRY(IRebarLayoutItem)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

protected:
   CComBSTR GetCollectionName() { return CComBSTR("RebarPatterns"); }
   CComBSTR GetStoredName()     { return CComBSTR("RebarPattern");  }
   virtual HRESULT DoSaveItem(IStructuredSave2* save,IRebarPattern* item);
   virtual HRESULT DoLoadItem(IStructuredLoad2* load,IRebarPattern* *ppItem);

// IRebarLayoutItem
public:
   STDMETHOD(ContainsLocation)(/*[in]*/ Float64 distFromGdrStart,/*[out,retval]*/ VARIANT_BOOL* bResult);
	STDMETHOD(get_Start)(/*[out,retval]*/Float64* start);
	STDMETHOD(get_Length)(/*[out,retval]*/Float64* length);
//	STDMETHOD(get_Count)(/*[out,retval]*/long* count);
//	STDMETHOD(get_Item)(/*[in]*/ long idx,/*[out,retval]*/IRebarPattern** pattern);
	STDMETHOD(AddRebarPattern)(/*[in]*/IRebarPattern* pattern);
//   STDMETHOD(get__NewEnum)(/*[out, retval]*/ IUnknown** retval);  
   STDMETHOD(get__EnumRebarPatterns)(/*[out,retval]*/IEnumRebarPatterns** enumRebarPatterns);

// IFixedLengthRebarLayoutItem
	STDMETHOD(put_Start)(/*[in]*/ Float64 start);
	STDMETHOD(put_End)(/*[in]*/ Float64 end);
	STDMETHOD(get_End)(/*[out,retval]*/ Float64* end);
	STDMETHOD(putref_Girder)(/*[in]*/IPrecastGirder* girder);

private:
   Float64 m_Start, m_End;
   IPrecastGirder* m_pGirder; // weak reference

};