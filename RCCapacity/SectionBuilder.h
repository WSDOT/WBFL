///////////////////////////////////////////////////////////////////////
// RCCapacity - Reinforced Concrete Capacity Analysis Library
// Copyright © 2003  Washington State Department of Transportation
//                   Bridge and Structures Office
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

// SectionBuilder.h : Declaration of the CSectionBuilder

#ifndef __SectionBuilder_H_
#define __SectionBuilder_H_

#include "resource.h"       // main symbols
#include <vector>

/////////////////////////////////////////////////////////////////////////////
// CSectionBuilder
class ATL_NO_VTABLE CSectionBuilder : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSectionBuilder, &CLSID_SectionBuilder>,
	public ISupportErrorInfo,
	public ISectionBuilder
{
public:
	CSectionBuilder()
	{
   }

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_SECTIONBUILDER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSectionBuilder)
	COM_INTERFACE_ENTRY(ISectionBuilder)
END_COM_MAP()

private:

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ISectionBuilder
public:
   STDMETHOD(RectangularColumn)(/*[in]*/Float64 H,/*[in]*/Float64 W,/*[in]*/Float64 cover,/*[in]*/long Nh,/*[in]*/long Nw,/*[in]*/Float64 As,/*[in]*/IStressStrain* concrete,/*[in]*/IStressStrain* rebar,/*[out,retval]*/IGeneralSection** section);
   STDMETHOD(CircularColumn)(/*[in]*/Float64 D,/*[in]*/Float64 cover,/*[in]*/long Nb,/*[in]*/Float64 As,/*[in]*/IStressStrain* concrete,/*[in]*/IStressStrain* rebar,/*[out,retval]*/IGeneralSection** section);
};

#endif //__SectionBuilder_H_
