///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2014  Washington State Department of Transportation
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

// Stage.h : Declaration of the CStage

#ifndef __STAGE_H_
#define __STAGE_H_

#include "resource.h"       // main symbols
#include "GenericBridgeCP.h"

/////////////////////////////////////////////////////////////////////////////
// CStage
class ATL_NO_VTABLE CStage : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CStage,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CStage, &CLSID_Stage>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CStage>,
	public IStage,
	public IStructuredStorage2,
   public IObjectSafetyImpl<CStage,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
   public CProxyDStageEvents< CStage >
{
public:
   CStage() :
      m_bstrName("Stage 1"),
      m_bstrDescription("Default Stage")
	{
	}

   void Init(CComBSTR bstrName,CComBSTR bstrDesc);
   void SetBridge(IGenericBridge* pBridge) { m_pBridge = pBridge; }

   STDMETHOD(Clone)(IStage* *clone);

DECLARE_REGISTRY_RESOURCEID(IDR_STAGE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CStage)
	COM_INTERFACE_ENTRY(IStage)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CStage)
CONNECTION_POINT_ENTRY(IID_IStageEvents)
END_CONNECTION_POINT_MAP()

private:
   static HRESULT PutName(CStage* pThis,CComBSTR bstrName);
   static HRESULT PutDescription(CStage* pThis,CComBSTR bstrDesc);


// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IStage
public:
	STDMETHOD(get_Name)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Name)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_Description)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Description)(/*[in]*/ BSTR newVal);

// IStructuredStorage2
public:
	STDMETHOD(Load)(/*[in]*/ IStructuredLoad2* load);
	STDMETHOD(Save)(/*[in]*/ IStructuredSave2* save);

private:
   CComBSTR m_bstrName;
   CComBSTR m_bstrDescription;

   IGenericBridge* m_pBridge; // Weak reference to bridge
};

#endif //__STAGE_H_
