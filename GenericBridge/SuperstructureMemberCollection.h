///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2016  Washington State Department of Transportation
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

// SuperstructureMemberCollection.h : Declaration of the CSuperstructureMemberCollection

#ifndef __SUPERSTRUCTUREMEMBERCOLLECTION_H_
#define __SUPERSTRUCTUREMEMBERCOLLECTION_H_

#include "WBFLComCollections.h"
#include "resource.h"       // main symbols

typedef CComVectorCollection<ISuperstructureMemberCollection, ISuperstructureMember, IEnumSuperstructureMembers, &IID_IEnumSuperstructureMembers, CollectionIndexType> SSMBRVectorImpl;

/////////////////////////////////////////////////////////////////////////////
// CSuperstructureMemberCollection
class ATL_NO_VTABLE CSuperstructureMemberCollection : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CSuperstructureMemberCollection,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CSuperstructureMemberCollection, &CLSID_SuperstructureMemberCollection>,
	public ISupportErrorInfo,
	//public IConnectionPointContainerImpl<CSuperstructureMemberCollection>,
	public SSMBRVectorImpl
{
public:
	CSuperstructureMemberCollection()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_SUPERSTRUCTUREMEMBERCOLLECTION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSuperstructureMemberCollection)
	COM_INTERFACE_ENTRY(ISuperstructureMemberCollection)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	//COM_INTERFACE_ENTRY(IConnectionPointContainer)
END_COM_MAP()
//
//BEGIN_CONNECTION_POINT_MAP(CSuperstructureMemberCollection)
//END_CONNECTION_POINT_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ISuperstructureMemberCollection
public:
   // commented methods are implemented by the base class
   //STDMETHOD(Add)(/*[in]*/ISuperstructureMember* pSSMbr);
   //STDMETHOD(get_Count)(/*[out, retval]*/ CollectionIndexType *pVal);
   //STDMETHOD(get_Item)(/*[in]*/CollectionIndexType index, /*[out, retval]*/ ISuperstructureMember* *pVal);
   //STDMETHOD(get__EnumElements)(/*[out, retval]*/ IEnumSuperstructureMembers* *pVal);
   //STDMETHOD(get__NewEnum)(/*[out, retval]*/ IUnknown** retval);  
   //STDMETHOD(Remove)(/*[in]*/ CollectionIndexType Index);
   //STDMETHOD(Clear)();
   //STDMETHOD(Reverse)();
   //STDMETHOD(Insert)(/*[in]*/CollectionIndexType index,/*[in]*/ISuperstructureMember* pVal);
};

#endif //__SUPERSTRUCTUREMEMBERCOLLECTION_H_
