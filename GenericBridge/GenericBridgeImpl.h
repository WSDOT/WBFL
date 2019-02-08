///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2019  Washington State Department of Transportation
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
   //public CComRefCountTracer<CGenericBridge,CComObjectRootEx<CComSingleThreadModel> >,
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
      m_WearingSurfaceDepth = 0;
      m_WearingSurfaceDensity = 0;
      m_WearingSurfaceStage = INVALID_INDEX;

      m_SacrificialDepth = 0;
      m_SacrificialDepthStage = INVALID_INDEX;
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

   Float64 m_WearingSurfaceDepth;
   Float64 m_WearingSurfaceDensity;
   StageIndexType m_WearingSurfaceStage; // stage when wearing surface is applied (not applied if INVALID_INDEX)

   Float64 m_SacrificialDepth;
   StageIndexType m_SacrificialDepthStage; // stage when deck surface is assumed to be reduced by the sacrifical depth (INVALID_INDEX if not used)

   CComPtr<IBridgeDeck> m_Deck;

   CComPtr<ISidewalkBarrier> m_LeftBarrier;
   CComPtr<ISidewalkBarrier> m_RightBarrier;

   std::map<GirderIDType,CAdapt<CComPtr<ISuperstructureMember>>> m_SuperstructureMembers;

   // Backdoor access to collections
   CPierCollection* GetPierCollection();

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IGenericBridge
public:
   STDMETHOD(get_BridgeGeometry)(IBridgeGeometry** bridgeGeometry) override;
   STDMETHOD(get_Alignment)(IAlignment** ppAlignment) override;
   STDMETHOD(get_Piers)(/*[out,retval]*/ IPierCollection* *piers) override;
   STDMETHOD(get_Length)(/*[out,retval]*/Float64* length) override;
   STDMETHOD(get_SpanLength)(SpanIndexType spanIdx,Float64* length) override;
	STDMETHOD(putref_Deck)(/*[in]*/ IBridgeDeck* deck) override;
	STDMETHOD(get_Deck)(/*[out,retval]*/ IBridgeDeck** deck) override;
	STDMETHOD(get_LeftBarrier)(/*[out,retval]*/ ISidewalkBarrier** barrier) override;
	STDMETHOD(putref_LeftBarrier)(/*[in]*/ ISidewalkBarrier* barrier) override;
	STDMETHOD(get_RightBarrier)(/*[out,retval]*/ ISidewalkBarrier** barrier) override;
	STDMETHOD(putref_RightBarrier)(/*[in]*/ ISidewalkBarrier* barrier) override;
   STDMETHOD(get_WearingSurfaceStage)(/*[out,retval]*/StageIndexType* stage) override;
	STDMETHOD(put_WearingSurfaceStage)(/*[in]*/StageIndexType stage) override;
	STDMETHOD(get_WearingSurfaceDepth)(/*[out,retval]*/Float64* d) override;
	STDMETHOD(put_WearingSurfaceDepth)(/*[in]*/Float64 d) override;
	STDMETHOD(get_WearingSurfaceDensity)(/*[out,retval]*/Float64* d) override;
	STDMETHOD(put_WearingSurfaceDensity)(/*[in]*/Float64 d) override;
	STDMETHOD(get_SacrificialDepth)(/*[out,retval]*/Float64* depth) override;
	STDMETHOD(put_SacrificialDepth)(/*[in]*/Float64 depth) override;
   STDMETHOD(get_SacrificialDepthStage)(/*[out,retval]*/StageIndexType* stage) override;
	STDMETHOD(put_SacrificialDepthStage)(/*[in]*/StageIndexType stage) override;
   STDMETHOD(CreateSuperstructureMember)(GirderIDType id,GirderIDType leftSSMbrID,GirderIDType rightSSMbrID,ISuperstructureMember** ppMbr) override;
   STDMETHOD(get_SuperstructureMember)(GirderIDType id,ISuperstructureMember** ppMbr) override;
   STDMETHOD(get__EnumSuperstructureMembers)(IEnumSuperstructureMembers* *enumSSMbrs) override;

   STDMETHOD(UpdateBridgeModel)() override;

// IStructuredStorage2
public:
	STDMETHOD(Load)(/*[in]*/ IStructuredLoad2* load) override;
	STDMETHOD(Save)(/*[in]*/ IStructuredSave2* save) override;
};

#endif //__GENERICBRIDGEIMPL_H_
