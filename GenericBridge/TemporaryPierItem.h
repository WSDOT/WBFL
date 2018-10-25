///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2010  Washington State Department of Transportation
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

// TemporaryPierItem.h : Declaration of the CTemporaryPierItem

#ifndef __TEMPORARYPIERITEM_H_
#define __TEMPORARYPIERITEM_H_

#include "resource.h"       // main symbols
#include "GenericBridgeCP.h"
#include "Pier.h"

/////////////////////////////////////////////////////////////////////////////
// CTemporaryPierItem
class ATL_NO_VTABLE CTemporaryPierItem : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CTemporaryPierItem,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CTemporaryPierItem, &CLSID_TemporaryPierItem>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CTemporaryPierItem,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IConnectionPointContainerImpl<CTemporaryPierItem>,
	public CProxyDTemporaryPierItemEvents< CTemporaryPierItem >,
   public ITemporaryPierItem,
   public IStructuredStorage2,
   public IPierEvents
{
public:
	CTemporaryPierItem()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

   void Init(long id,Float64 location,BSTR bstrRemovalStage);
   void Init(long id,Float64 location,BSTR bstrRemovalStage,IPier* pier);

   STDMETHOD(Clone)(ITemporaryPierItem* *clone);

   void SetBridge(IGenericBridge* pBridge)
   {
      m_pBridge = pBridge;
      CPier* pPier = dynamic_cast<CPier*>(m_Pier.p);
      pPier->SetBridge(m_pBridge);
   }

DECLARE_REGISTRY_RESOURCEID(IDR_TEMPORARYPIERITEM)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CTemporaryPierItem)
	COM_INTERFACE_ENTRY(ITemporaryPierItem)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(IPierEvents)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CTemporaryPierItem)
CONNECTION_POINT_ENTRY(IID_ITemporaryPierItemEvents)
END_CONNECTION_POINT_MAP()


// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ITemporaryPierItem
public:
	STDMETHOD(get_ID)(/*[out, retval]*/ long* id);
	STDMETHOD(get_Location)(/*[out, retval]*/ Float64* location);
	STDMETHOD(put_Location)(/*[in]*/ Float64 location);
	STDMETHOD(get_RemovalStage)(/*[out, retval]*/ BSTR* bstrRemovalStage);
	STDMETHOD(put_RemovalStage)(/*[in]*/ BSTR bstrRemovalStage);
	STDMETHOD(get_Pier)(/*[out, retval]*/ IPier* *pVal);

// IPierEvents
public:
	STDMETHOD(OnPierChanged)(IPier * Pier)
	{
      Fire_OnTemporaryPierChanged(m_ID);
		return S_OK;
	}

// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave);
   STDMETHOD(Load)(IStructuredLoad2* pLoad);

protected:
   long m_ID;
   CComBSTR m_bstrRemovalStage;
   Float64 m_Location;
   CComPtr<IPier> m_Pier;
   DWORD m_dwCookie;

   IGenericBridge* m_pBridge;

   HRESULT AdvisePier();
   HRESULT UnadvisePier();
};

#endif //__TEMPORARYPIERITEM_H_
