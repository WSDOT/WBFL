///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry
// Copyright © 1999-2025  Washington State Department of Transportation
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

// Superelevation.h : Declaration of the CSuperelevation

#pragma once

#include "resource.h"       // main symbols


/////////////////////////////////////////////////////////////////////////////
// CSuperelevation
class ATL_NO_VTABLE CSuperelevation : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CSuperelevation,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CSuperelevation, &CLSID_Superelevation>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CSuperelevation,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
   public ISuperelevation
{
public:
	CSuperelevation()
	{
	}

	HRESULT FinalConstruct();
   void FinalRelease();

   void SetSuperelevation(std::shared_ptr<WBFL::COGO::Superelevation> super) { m_Superelevation = super; }
   std::shared_ptr<WBFL::COGO::Superelevation> GetSuperelevation() { return m_Superelevation; }

DECLARE_REGISTRY_RESOURCEID(IDR_SUPERELEVATION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSuperelevation)
	COM_INTERFACE_ENTRY(ISuperelevation)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ISuperelevation
public:
   STDMETHOD(Init)(VARIANT varBeginStation,VARIANT varBeginFullStation,VARIANT varEndFullStation,VARIANT varEndStation,Float64 rate,IndexType pivotPoint,SuperTransitionType beginType,Float64 beginL1,Float64 beginL2,SuperTransitionType endType,Float64 endL1,Float64 endL2) override;
   STDMETHOD(get_Surface)(ISurface* *pVal) override;
   STDMETHOD(putref_Surface)(ISurface* newVal) override;
   STDMETHOD(put_BeginTransition)(VARIANT varBeginTransition) override;
   STDMETHOD(get_BeginTransition)(IStation** ppBeginTransition) override;
   STDMETHOD(put_BeginFullSuper)(VARIANT varBeginFullSuper) override;
   STDMETHOD(get_BeginFullSuper)(IStation** ppBeginFullSuper) override;
   STDMETHOD(put_EndFullSuper)(VARIANT varEndFullSuper) override;
   STDMETHOD(get_EndFullSuper)(IStation** ppEndFullSuper) override;
   STDMETHOD(put_EndTransition)(VARIANT varEndTransition) override;
   STDMETHOD(get_EndTransition)(IStation** ppEndTransition) override;
   STDMETHOD(put_Rate)(Float64 rate) override;
   STDMETHOD(get_Rate)(Float64* rate) override;
   STDMETHOD(put_PivotPoint)(IndexType pivotPointIdx) override;
   STDMETHOD(get_PivotPoint)(IndexType* pivotPointIdx) override;
   STDMETHOD(put_BeginTransitionType)(SuperTransitionType type) override;
   STDMETHOD(get_BeginTransitionType)(SuperTransitionType* type) override;
   STDMETHOD(SetBeginTransitionParameters)(Float64 L1,Float64 L2) override;
   STDMETHOD(GetBeginTransitionParameters)(Float64* L1,Float64* L2) override;
   STDMETHOD(put_EndTransitionType)(SuperTransitionType type) override;
   STDMETHOD(get_EndTransitionType)(SuperTransitionType* type) override;
   STDMETHOD(SetEndTransitionParameters)(Float64 L1,Float64 L2) override;
   STDMETHOD(GetEndTransitionParameters)(Float64* L1,Float64* L2) override;
   STDMETHOD(GetSlope)(VARIANT varStation,Float64 templateSlope,Float64* pSlope) override;

private:
   std::shared_ptr<WBFL::COGO::Superelevation> m_Superelevation;
   ISurface* m_pSurface; // weak reference

   HRESULT ValidateStation(const WBFL::COGO::Station& station);
};
