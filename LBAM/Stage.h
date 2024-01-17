///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright © 1999-2024  Washington State Department of Transportation
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

// Stage.h : Declaration of the CStage

#ifndef __STAGE_H_
#define __STAGE_H_

#include "resource.h"       // main symbols
#include "StageCP.h"

/////////////////////////////////////////////////////////////////////////////
// CStage
class ATL_NO_VTABLE CStage : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CStage,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CStage, &CLSID_Stage>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CStage>,
	public IStage,
   public IPersistImpl<CStage>,
	public IStructuredStorage2,
   public IObjectSafetyImpl<CStage,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public CProxyDStageEvents< CStage >
{
public:
	CStage()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_STAGE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CStage)
	COM_INTERFACE_ENTRY(IStage)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(IPersist)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CStage)
CONNECTION_POINT_ENTRY(IID_IStageEvents)
END_CONNECTION_POINT_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

   // IStructuredStorage2
	STDMETHOD(Load)(IStructuredLoad2 * Load) override;
	STDMETHOD(Save)(IStructuredSave2 * Save) override;

// IStage
public:
	STDMETHOD(Clone)(/*[out,retval]*/IStage* *clone) override;
	STDMETHOD(get_Description)(/*[out, retval]*/ BSTR *pVal) override;
	STDMETHOD(put_Description)(/*[in]*/ BSTR newVal) override;
	STDMETHOD(get_Name)(/*[out, retval]*/ BSTR *pVal) override;
	STDMETHOD(put_Name)(/*[in]*/ BSTR newVal) override;

protected:
   CComBSTR m_Name;
   CComBSTR m_Description;
};

#endif //__STAGE_H_
