///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2012  Washington State Department of Transportation
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

// TransversePierDescription.h : Declaration of the CTransversePierDescription

#ifndef __TRANSVERSEPIERDESCRIPTION_H_
#define __TRANSVERSEPIERDESCRIPTION_H_

#include "resource.h"       // main symbols
#include "GenericBridgeCP.h"
#include <vector>

/////////////////////////////////////////////////////////////////////////////
// CTransversePierDescription
class ATL_NO_VTABLE CTransversePierDescription : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTransversePierDescription, &CLSID_TransversePierDescription>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CTransversePierDescription>,
	public CProxyDTransversePierDescriptionEvents< CTransversePierDescription >,
	public ITransversePierDescription,
   public IStructuredStorage2,
   public IColumnSpacingEvents,
	public ICrossBeamEvents,
   public IColumnEvents,
   public IObjectSafetyImpl<CTransversePierDescription,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>
{
public:
	CTransversePierDescription()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

   void SetBridge(IGenericBridge* pBridge);

   void SetPier(IPier* pier)
   {
      m_pPier = pier;
   }

   void SetItems(IColumnSpacing* pSpacing,ICrossBeam* pCrossBeam);

   STDMETHOD(Clone)(ITransversePierDescription* *clone);

DECLARE_REGISTRY_RESOURCEID(IDR_TRANSVERSEPIERDESCRIPTION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CTransversePierDescription)
	COM_INTERFACE_ENTRY(ITransversePierDescription)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY(IColumnSpacingEvents)
   COM_INTERFACE_ENTRY(ICrossBeamEvents)
   COM_INTERFACE_ENTRY(IColumnEvents)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CTransversePierDescription)
   CONNECTION_POINT_ENTRY(IID_ITransversePierDescriptionEvents)
END_CONNECTION_POINT_MAP()

private:
   CComPtr<ICrossBeam> m_CrossBeam;
   DWORD m_dwCrossBeamCookie;

   CComPtr<IColumnSpacing> m_ColumnSpacing;
   DWORD m_dwColumnSpacingCookie;

   IGenericBridge* m_pBridge; // weak reference
   IPier* m_pPier; // weak reference

   HRESULT AdviseChild(IUnknown* punk,REFIID riid,DWORD* pdwCookie);
   HRESULT UnadviseChild(IUnknown* punk,REFIID riid,DWORD dwCookie);

   std::vector< std::pair<DWORD,CComPtr<IColumn> > > m_ColumnCookies;
   void AdviseColumns();
   void UnadviseColumns();

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ITransversePierDescription
public:
   STDMETHOD(get_CrossBeam)(/*[out,retval]*/ICrossBeam* *crossBeam);
   STDMETHOD(get_ColumnSpacing)(/*[out,retval]*/IColumnSpacing* *columnSpacing);
   STDMETHOD(get_Column)(/*[in]*/ ColumnIndexType columnIdx,/*[out,retval]*/IColumn* *column);
   STDMETHOD(get_Pier)(/*[out,retval]*/IPier* *pier);

// IStructuredStorage2
public:
	STDMETHOD(Load)(/*[in]*/ IStructuredLoad2* load);
	STDMETHOD(Save)(/*[in]*/ IStructuredSave2* save);

// IColumnSpacingEvents
public:
	STDMETHOD(OnColumnCountChanged)(ColumnIndexType newVal)
	{
      UnadviseColumns();
      AdviseColumns();
      Fire_OnChanged();
      return S_OK;
	}
	STDMETHOD(OnColumnSpacingChanged)()
	{
      Fire_OnChanged();
      return S_OK;
	}

// ICrossBeamEvents
public:
	STDMETHOD(OnCrossBeamChanged)(ICrossBeam * CrossBeam)
	{
      Fire_OnChanged();
      return S_OK;
	}
// IColumnEvents
	STDMETHOD(OnColumnChanged)(IColumn * Column)
	{
      Fire_OnChanged();
      return S_OK;
	}
};

#endif //__TRANSVERSEPIERDESCRIPTION_H_
