///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
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

// TendonCollection.h : Declaration of the CTendonCollection

#ifndef __TendonCollection_H_
#define __TendonCollection_H_

#include "resource.h"       // main symbols
#include <WBFLComCollections.h>
//#include "GenericBridgeCP.h"

class CTendonCollection;
using TendonColl = CComVectorCollection<ITendonCollection, ITendon, IEnumTendons, &IID_IEnumTendons, StrandIndexType>;
using PersistentTendonCollection = CPersistentCollection<CTendonCollection,TendonColl, StrandIndexType>;

/////////////////////////////////////////////////////////////////////////////
// CTendonCollection
class ATL_NO_VTABLE CTendonCollection : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CTendonCollection,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CTendonCollection, &CLSID_TendonCollection>,
	public ISupportErrorInfo,
	//public ITendonCollection,
   public PersistentTendonCollection,
//   public CProxyDTendonCollectionEvents< CTendonCollection >,
//   public ITendonCollectionPointContainerImpl<CTendonCollection>,
   public IObjectSafetyImpl<CTendonCollection,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>
{
public:
   CTendonCollection()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_TENDONCOLLECTION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CTendonCollection)
	COM_INTERFACE_ENTRY(ITendonCollection)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
//   COM_INTERFACE_ENTRY_IMPL(ITendonCollectionPointContainer)
   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY_CHAIN(PersistentTendonCollection)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CTendonCollection)
//	CONNECTION_POINT_ENTRY(IID_ITendonCollectionEvents)
END_CONNECTION_POINT_MAP()

   // ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ITendonCollection
public:
//   STDMETHOD(Add)(/*[in]*/ITendon* tendon) override;
//	STDMETHOD(get_Item)(/*[in]*/long index,/*[out,retval]*/ITendon** tendon) override;
//	STDMETHOD(Remove)(/*[in]*/long index) override;
//	STDMETHOD(Clear)() override;
	STDMETHOD(get_CG)(/*[in]*/ Float64 z,/*[in]*/ TendonMeasure measure,/*[out,retval]*/IPoint3d** cg) override;
	STDMETHOD(get_Slope)(/*[in]*/ Float64 z,/*[in]*/ TendonMeasure measure,/*[out,retval]*/IVector3d** slope) override;
	STDMETHOD(Cut)(/*[in]*/ Float64 z,/*[in]*/TendonMeasure measure,/*[out,retval]*/ IPoint3dCollection** points) override;
   STDMETHOD(get__EnumTendons)(/*[out,retval]*/IEnumTendons* *enumTendons) override;

//// IStructuredStorage2
//public:
//	STDMETHOD(Load)(/*[in]*/ IStructuredLoad2* load) override;
//	STDMETHOD(Save)(/*[in]*/ IStructuredSave2* save) override;
};

#endif //__TendonCollection_H_
