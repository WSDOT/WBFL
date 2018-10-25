///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
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

// CrossSection.h : Declaration of the CCrossSection

#ifndef __CROSSSECTION_H_
#define __CROSSSECTION_H_
#pragma once

#include "resource.h"       // main symbols
#include "COGOCP.h"

/////////////////////////////////////////////////////////////////////////////
// CCrossSection
class ATL_NO_VTABLE CCrossSection : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CCrossSection,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CCrossSection, &CLSID_CrossSection>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CCrossSection,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IConnectionPointContainerImpl<CCrossSection>,
	public CProxyDCrossSectionEvents< CCrossSection >,
   public ICrossSection,
   public IStructuredStorage2,
   public IPersistImpl<CCrossSection>
{
public:
	CCrossSection()
	{
      m_Station = 0.0;
      m_CrownPtOffset = 0.0;
      m_Left = 0.0;
      m_Right = 0.0;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_CROSSSECTION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCrossSection)
	COM_INTERFACE_ENTRY(ICrossSection)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY(IPersist)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CCrossSection)
CONNECTION_POINT_ENTRY(IID_ICrossSectionEvents)
END_CONNECTION_POINT_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ICrossSection
public:
   STDMETHOD(get_StructuredStorage)(/*[out,retval]*/IStructuredStorage2* *pStg);
   STDMETHOD(Clone)(/*[out,retval]*/ ICrossSection* *clone);
	STDMETHOD(get_RightCrownSlope)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_RightCrownSlope)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_LeftCrownSlope)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_LeftCrownSlope)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_CrownPointOffset)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_CrownPointOffset)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_Station)(/*[out, retval]*/ IStation* *station);
	STDMETHOD(put_Station)(/*[in]*/ VARIANT varStation);

// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave);
   STDMETHOD(Load)(IStructuredLoad2* pLoad);

private:
	Float64 m_Right;
	Float64 m_Left;
	Float64 m_CrownPtOffset;
	Float64 m_Station;
};

#endif //__CROSSSECTION_H_
