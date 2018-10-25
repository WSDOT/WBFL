///////////////////////////////////////////////////////////////////////
// BridgeGeometry
// Copyright © 1999-2017  Washington State Department of Transportation
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

// PierCollection.h : Declaration of the CPierCollection

#pragma once
#include "resource.h"       // main symbols

#include "WBFLBridgeGeometry.h"
#include "WBFLComCollections.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif


class CPierLineCollection;
typedef CComVectorCollection<IPierLineCollection,IPierLine,IEnumPierLines,&IID_IEnumPierLines,PierIndexType> PierColl;
typedef CPersistentCollection<CPierLineCollection,PierColl,PierIndexType> PersistentPierLineCollection;

// CPierCollection

class ATL_NO_VTABLE CPierLineCollection :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPierLineCollection, &CLSID_PierLineCollection>,
	public PersistentPierLineCollection
{
public:
	CPierLineCollection()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_PIERLINECOLLECTION)

DECLARE_NOT_AGGREGATABLE(CPierLineCollection)

BEGIN_COM_MAP(CPierLineCollection)
   COM_INTERFACE_ENTRY_CHAIN(PersistentPierLineCollection)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

   PierIndexType GetPierLineIndex(IPierLine* pier);
   virtual HRESULT OnAfterAdd( StoredType* pVal, PierIndexType idx);
   void Sort();

   static bool PierSort(StoredType a,StoredType b);

// IPierLineCollection
public:
   //STDMETHOD(get__NewEnum)(/*[out, retval]*/ IUnknown** retval);  
   //STDMETHOD(get_Item)(/*[in]*/ PierIndexType index, /*[out, retval]*/ IPierLine* *pVal);
   //STDMETHOD(get_Count)(/*[out,retval]*/ PierIndexType* count);
   STDMETHOD(get_PierLine)(/*[in]*/ PierIndexType index, /*[out, retval]*/ IPierLine* *pVal);
   STDMETHOD(get_PierLineIndex)(/*[in]*/ IPierLine* pier,/*[out,retval]*/PierIndexType* index);
   STDMETHOD(get__EnumPiers)(/*[out,retval]*/IEnumPierLines* *enumPiers);
   STDMETHOD(FindPierLine)(PierIDType pierID, IPierLine* *pVal);
};

OBJECT_ENTRY_NON_CREATEABLE_EX_AUTO(__uuidof(PierLineCollection), CPierLineCollection)
