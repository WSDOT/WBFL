///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2013  Washington State Department of Transportation
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

// GenericBridgeImpl.h : Declaration of the CGenericBridge

#ifndef __GENERICBRIDGEIMPL_H_
#define __GENERICBRIDGEIMPL_H_

#include "resource.h"       // main symbols
#include <map>

class CPierCollection;

/////////////////////////////////////////////////////////////////////////////
// CGenericBridge
class ATL_NO_VTABLE CGenericBridge :
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CGenericBridge,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CGenericBridge, &CLSID_GenericBridge>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CGenericBridge,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IGenericBridge,
   public IStructuredStorage2
{
public:
   friend CGenericBridge;

   CGenericBridge()
	{
   }

   HRESULT FinalConstruct();
   void FinalRelease();

   // Causes the internal span/pier linkages pointers to be re-initialized
   void LinkSpansAndPiers();

DECLARE_REGISTRY_RESOURCEID(IDR_GENERICBRIDGE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CGenericBridge)
	COM_INTERFACE_ENTRY(IGenericBridge)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

private:
   void DoUpdateBridgeModel();

   CComPtr<IPierCollection> m_Piers;

   CComPtr<IBridgeGeometry> m_BridgeGeometry;

   CComPtr<IBridgeDeck> m_Deck;

   CComPtr<ISidewalkBarrier> m_LeftBarrier;
   CComPtr<ISidewalkBarrier> m_RightBarrier;

   std::map<GirderIDType,CAdapt<CComPtr<ISuperstructureMember>>> m_SuperstructureMembers;

   // Backdoor access to collections
   CPierCollection* GetPierCollection();

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IGenericBridge
public:
   STDMETHOD(get_BridgeGeometry)(IBridgeGeometry** bridgeGeometry);
   STDMETHOD(get_Alignment)(IAlignment** ppAlignment);
   STDMETHOD(get_Piers)(/*[out,retval]*/ IPierCollection* *piers);
   STDMETHOD(get_Length)(/*[out,retval]*/Float64* length);
   STDMETHOD(get_SpanLength)(SpanIndexType spanIdx,Float64* length);
	STDMETHOD(putref_Deck)(/*[in]*/ IBridgeDeck* deck);
	STDMETHOD(get_Deck)(/*[out,retval]*/ IBridgeDeck** deck);
	STDMETHOD(get_LeftBarrier)(/*[out,retval]*/ ISidewalkBarrier** barrier);
	STDMETHOD(putref_LeftBarrier)(/*[in]*/ ISidewalkBarrier* barrier);
	STDMETHOD(get_RightBarrier)(/*[out,retval]*/ ISidewalkBarrier** barrier);
	STDMETHOD(putref_RightBarrier)(/*[in]*/ ISidewalkBarrier* barrier);
   STDMETHOD(CreateSuperstructureMember)(GirderIDType id,LocationType locationType,ISuperstructureMember** ppMbr);
   STDMETHOD(get_SuperstructureMember)(GirderIDType id,ISuperstructureMember** ppMbr);
   STDMETHOD(get__EnumSuperstructureMembers)(IEnumSuperstructureMembers* *enumSSMbrs);
   STDMETHOD(get_SuperstructureMembersAtStation)(Float64 station,IFilteredSuperstructureMemberCollection** ppMbrs);

   STDMETHOD(UpdateBridgeModel)();

// IStructuredStorage2
public:
	STDMETHOD(Load)(/*[in]*/ IStructuredLoad2* load);
	STDMETHOD(Save)(/*[in]*/ IStructuredSave2* save);
};

#endif //__GENERICBRIDGEIMPL_H_
