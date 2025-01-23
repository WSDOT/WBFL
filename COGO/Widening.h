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

// Widening.h : Declaration of the CWidening

#pragma once

#include "resource.h"       // main symbols


/////////////////////////////////////////////////////////////////////////////
// CWidening
class ATL_NO_VTABLE CWidening : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CWidening,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CWidening, &CLSID_Widening>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CWidening,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
   public IWidening
{
public:
	CWidening()
	{
	}

	HRESULT FinalConstruct();
   void FinalRelease();

   void SetWidening(std::shared_ptr<WBFL::COGO::Widening> widening) { m_Widening = widening; }
   std::shared_ptr<WBFL::COGO::Widening> GetWidening() { return m_Widening; }

DECLARE_REGISTRY_RESOURCEID(IDR_WIDENING)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CWidening)
	COM_INTERFACE_ENTRY(IWidening)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()


// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IWidening
public:
   STDMETHOD(Init)(VARIANT varBeginStation,VARIANT varBeginFullStation,VARIANT varEndFullStation,VARIANT varEndStation,Float64 widening,IndexType seg1,IndexType seg2) override;
   STDMETHOD(get_Surface)(ISurface* *pVal) override;
   STDMETHOD(putref_Surface)(ISurface* newVal) override;
   STDMETHOD(put_BeginTransition)(VARIANT varStation) override;
   STDMETHOD(get_BeginTransition)(IStation** station) override;
   STDMETHOD(put_BeginFullWidening)(VARIANT varStation) override;
   STDMETHOD(get_BeginFullWidening)(IStation** station) override;
   STDMETHOD(put_EndFullWidening)(VARIANT varStation) override;
   STDMETHOD(get_EndFullWidening)(IStation** station) override;
   STDMETHOD(put_EndTransition)(VARIANT varStation) override;
   STDMETHOD(get_EndTransition)(IStation** station) override;
   STDMETHOD(put_Widening)(Float64 value) override;
   STDMETHOD(get_Widening)(Float64* value) override;
   STDMETHOD(put_Segment)(IndexType pntIdx,IndexType segmentIdx) override;
   STDMETHOD(get_Segment)(IndexType pntIdx,IndexType* segmentIdx) override;
   STDMETHOD(GetWidening)(VARIANT varStation,IndexType templateSegmentIdx,Float64* pWidening) override;

private:
   std::shared_ptr<WBFL::COGO::Widening> m_Widening;
   ISurface* m_pSurface; // weak reference

   HRESULT ValidateStation(const WBFL::COGO::Station& station);
};
