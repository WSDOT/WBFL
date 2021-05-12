///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright © 1999-2021  Washington State Department of Transportation
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

// LiveLoad.h : Declaration of the CLiveLoad

#ifndef __LIVELOAD_H_
#define __LIVELOAD_H_

#include "resource.h"       // main symbols
#include "LiveLoadCP.h"

/////////////////////////////////////////////////////////////////////////////
// CLiveLoad
class ATL_NO_VTABLE CLiveLoad : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLiveLoad, &CLSID_LiveLoad>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CLiveLoad>,
	public ILiveLoad,
   public IPersistImpl<CLiveLoad>,
	public IStructuredStorage2,
	public CProxyDLiveLoadEvents< CLiveLoad >,
   public IObjectSafetyImpl<CLiveLoad,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public ILiveLoadModelEvents
{
public:
   CLiveLoad();

   HRESULT FinalConstruct();
   void FinalRelease();


DECLARE_REGISTRY_RESOURCEID(IDR_LIVELOAD)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLiveLoad)
	COM_INTERFACE_ENTRY(ILiveLoad)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(IPersist)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(ILiveLoadModelEvents)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CLiveLoad)
CONNECTION_POINT_ENTRY(IID_ILiveLoadEvents)
END_CONNECTION_POINT_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ILiveLoad
public:
	STDMETHOD(Clear)() override;
	STDMETHOD(Clone)(/*[out,retval]*/ILiveLoad** clone) override;
   STDMETHOD(get_LegalRoutineRating)(/*[out, retval]*/ ILiveLoadModel* *pVal) override;
   STDMETHOD(putref_LegalRoutineRating)(/*[in]*/ ILiveLoadModel* newVal) override;
   STDMETHOD(get_LegalSpecialRating)(/*[out, retval]*/ ILiveLoadModel* *pVal) override;
   STDMETHOD(putref_LegalSpecialRating)(/*[in]*/ ILiveLoadModel* newVal) override;
   STDMETHOD(get_LegalEmergencyRating)(/*[out, retval]*/ ILiveLoadModel* *pVal) override;
   STDMETHOD(putref_LegalEmergencyRating)(/*[in]*/ ILiveLoadModel* newVal) override;
   STDMETHOD(get_PermitRoutineRating)(/*[out, retval]*/ ILiveLoadModel* *pVal) override;
   STDMETHOD(putref_PermitRoutineRating)(/*[in]*/ ILiveLoadModel* newVal) override;
   STDMETHOD(get_PermitSpecialRating)(/*[out, retval]*/ ILiveLoadModel* *pVal) override;
   STDMETHOD(putref_PermitSpecialRating)(/*[in]*/ ILiveLoadModel* newVal) override;
	STDMETHOD(get_Pedestrian)(/*[out, retval]*/ ILiveLoadModel* *pVal) override;
	STDMETHOD(putref_Pedestrian)(/*[in]*/ ILiveLoadModel* newVal) override;
	STDMETHOD(get_Special)(/*[out, retval]*/ ILiveLoadModel* *pVal) override;
	STDMETHOD(putref_Special)(/*[in]*/ ILiveLoadModel* newVal) override;
	STDMETHOD(get_Permit)(/*[out, retval]*/ ILiveLoadModel* *pVal) override;
	STDMETHOD(putref_Permit)(/*[in]*/ ILiveLoadModel* newVal) override;
	STDMETHOD(get_Fatigue)(/*[out, retval]*/ ILiveLoadModel* *pVal) override;
	STDMETHOD(putref_Fatigue)(/*[in]*/ ILiveLoadModel* newVal) override;
	STDMETHOD(get_Deflection)(/*[out, retval]*/ ILiveLoadModel* *pVal) override;
	STDMETHOD(putref_Deflection)(/*[in]*/ ILiveLoadModel* newVal) override;
	STDMETHOD(get_Design)(/*[out, retval]*/ ILiveLoadModel* *pVal) override;
	STDMETHOD(putref_Design)(/*[in]*/ ILiveLoadModel* newVal) override;

   // ILiveLoadModelEvents
   STDMETHOD(OnLiveLoadModelChanged)(/*[in]*/ILiveLoadModel* model, ChangeType change) override;

   // IStructuredStorage2
	STDMETHOD(Load)(IStructuredLoad2 * Load) override;
	STDMETHOD(Save)(IStructuredSave2 * Save) override;

protected:
   CComPtr<ILiveLoadModel> m_Models[12];
   DWORD                   m_Cookies[12];

private:
   HRESULT PutLiveLoadModel(LiveLoadModelType modelType, ILiveLoadModel *newVal, bool doFire=true);
};

#endif //__LIVELOAD_H_
