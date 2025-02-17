///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright � 1999-2025  Washington State Department of Transportation
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

using SSMBRVectorImpl = CComVectorCollection<ISuperstructureMemberCollection, ISuperstructureMember, IEnumSuperstructureMembers, &IID_IEnumSuperstructureMembers, IndexType>;

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
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ISuperstructureMemberCollection
public:
   // commented methods are implemented by the base class
   //STDMETHOD(Add)(/*[in]*/ISuperstructureMember* pSSMbr) override;
   //STDMETHOD(get_Count)(/*[out, retval]*/ IndexType *pVal) override;
   //STDMETHOD(get_Item)(/*[in]*/IndexType index, /*[out, retval]*/ ISuperstructureMember* *pVal) override;
   //STDMETHOD(get__EnumElements)(/*[out, retval]*/ IEnumSuperstructureMembers* *pVal) override;
   //STDMETHOD(get__NewEnum)(/*[out, retval]*/ IUnknown** retval) override;  
   //STDMETHOD(Remove)(/*[in]*/ IndexType Index) override;
   //STDMETHOD(Clear)() override;
   //STDMETHOD(Reverse)() override;
   //STDMETHOD(Insert)(/*[in]*/IndexType index,/*[in]*/ISuperstructureMember* pVal) override;
};

#endif //__SUPERSTRUCTUREMEMBERCOLLECTION_H_
