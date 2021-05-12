///////////////////////////////////////////////////////////////////////
// Loading - Generic library to describe bridge loadings
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

// LoadCombination.h : Declaration of the CLoadCombination

#ifndef __LOADCOMBINATION_H_
#define __LOADCOMBINATION_H_

#include "resource.h"       // main symbols
#include "LoadingCP.h"

#include <vector>

/////////////////////////////////////////////////////////////////////////////
// CLoadCombination
class ATL_NO_VTABLE CLoadCombination : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CLoadCase,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CLoadCombination, &CLSID_ldLoadCombination>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CLoadCombination>,
	public ldILoadCombination,
   public IPersistImpl<CLoadCombination>,
	public IStructuredStorage2,
   public IObjectSafetyImpl<CLoadCombination,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public CProxyDLoadCombinationEvents< CLoadCombination >
{
public:
   CLoadCombination():
   m_LiveLoadModelType(ldltNone),
   m_LiveLoadFactor(0.0),
   m_ItemData(0),
   m_LoadCombinationType(ldctUserDefined)
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_LOADCOMBINATION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLoadCombination)
	COM_INTERFACE_ENTRY(ldILoadCombination)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(IPersist)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CLoadCombination)
CONNECTION_POINT_ENTRY(IID_ldILoadCombinationEvents)
END_CONNECTION_POINT_MAP()

// IStructuredStorage2
	STDMETHOD(Load)(IStructuredLoad2 * Load) override;
	STDMETHOD(Save)(IStructuredSave2 * Save) override;

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ldILoadCombination
public:
	STDMETHOD(get_LoadCombinationType)(/*[out, retval]*/ ldLoadCombinationType *pVal) override;
	STDMETHOD(put_LoadCombinationType)(/*[in]*/ ldLoadCombinationType newVal) override;
	STDMETHOD(get_ItemData)(/*[out, retval]*/ VARIANT *pVal) override;
	STDMETHOD(put_ItemData)(/*[in]*/ VARIANT newVal) override;
	STDMETHOD(Clone)(/*[out,retval]*/ldILoadCombination* *lone) override;
	STDMETHOD(RemoveLoadCaseFactor)(/*[in]*/CollectionIndexType index) override;
	STDMETHOD(Clear)() override;
	STDMETHOD(GetLoadCaseFactor)(/*[in]*/CollectionIndexType index,  /*[out]*/BSTR* loadCaseName, /*[out]*/Float64* minFactor, /*[out]*/Float64* maxFactor) override;
	STDMETHOD(AddLoadCaseFactor)( /*[in]*/BSTR loadCaseName, /*[in]*/Float64 minFactor, /*[in]*/Float64 maxFactor) override;
	STDMETHOD(SetLoadCaseFactor)(/*[in]*/CollectionIndexType index, /*[in]*/BSTR loadCaseName, /*[in]*/Float64 minFactor, /*[in]*/Float64 maxFactor) override;
	STDMETHOD(get_LoadCaseFactorCount)(/*[out, retval]*/ CollectionIndexType *pVal) override;
	STDMETHOD(get_LiveLoadFactor)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_LiveLoadFactor)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_LiveLoadModel)(/*[out, retval]*/ ldLiveLoadModelType *pVal) override;
	STDMETHOD(put_LiveLoadModel)(/*[in]*/ ldLiveLoadModelType newVal) override;
	STDMETHOD(get_Description)(/*[out, retval]*/ BSTR *pVal) override;
	STDMETHOD(put_Description)(/*[in]*/ BSTR newVal) override;
	STDMETHOD(get_Name)(/*[out, retval]*/ BSTR *pVal) override;
	STDMETHOD(put_Name)(/*[in]*/ BSTR newVal) override;

protected:
   CComBSTR            m_Name;
   CComBSTR            m_Description;
   CComVariant         m_ItemData;
   ldLiveLoadModelType   m_LiveLoadModelType;
   Float64              m_LiveLoadFactor;
   ldLoadCombinationType m_LoadCombinationType;

   struct LoadCaseFactor
   {
      LoadCaseFactor()
      {;}

      LoadCaseFactor(BSTR loadCase, Float64 minFactor, Float64 maxFactor):
      m_LoadCase(loadCase),
      m_MinFactor(minFactor),
      m_MaxFactor(maxFactor)
      {;}

      CComBSTR  m_LoadCase;
      Float64    m_MinFactor;
      Float64    m_MaxFactor;
   };
   typedef std::vector<LoadCaseFactor>        LoadCaseFactorContainer;
   typedef LoadCaseFactorContainer::iterator  LoadCaseFactorIterator;

   LoadCaseFactorContainer m_LoadCaseFactors;

};

#endif //__LOADCOMBINATION_H_
