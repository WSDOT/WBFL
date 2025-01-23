///////////////////////////////////////////////////////////////////////
// GenericBridgeTools - Tools for manipluating the Generic Bridge Modeling
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

// EffectiveFlangeWidthDetails.h : Declaration of the CEffectiveFlangeWidthDetails

#ifndef __EFFECTIVEFLANGEWIDTHDETAILS_H_
#define __EFFECTIVEFLANGEWIDTHDETAILS_H_

#include "resource.h"       // main symbols
#include <vector>

/////////////////////////////////////////////////////////////////////////////
// CEffectiveFlangeWidthDetails
class ATL_NO_VTABLE CEffectiveFlangeWidthDetails : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEffectiveFlangeWidthDetails, &CLSID_EffectiveFlangeWidthDetails>,
	public ISupportErrorInfo,
	public IEffectiveFlangeWidthDetails,
   public IObjectSafetyImpl<CEffectiveFlangeWidthDetails,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>
{
public:
	CEffectiveFlangeWidthDetails()
	{
	}

   HRESULT FinalConstruct();

DECLARE_REGISTRY_RESOURCEID(IDR_EFFECTIVEFLANGEWIDTHDETAILS)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CEffectiveFlangeWidthDetails)
	COM_INTERFACE_ENTRY(IEffectiveFlangeWidthDetails)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

private:
   Float64 m_EffSpanLength;
   Float64 m_SlabThickness;

   struct PARAMS
   {
      Float64 WebThickness;
      Float64 TopFlangeThickness;
      Float64 LeftSpacing;
      Float64 RightSpacing;
   };
   std::vector<PARAMS> m_FlangeParameters;

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IEffectiveFlangeWidthDetails
public:
	STDMETHOD(put_EffectiveSpanLength)(/*[in]*/ Float64 length) override;
	STDMETHOD(get_EffectiveSpanLength)(/*[out,retval]*/ Float64* length) override;
	STDMETHOD(put_SlabThickness)(/*[in]*/ Float64 tSlab) override;
	STDMETHOD(get_SlabThickness)(/*[out,retval]*/ Float64* tSlab) override;
	STDMETHOD(AddFlangeParameters)(/*[in]*/Float64 tFlange,/*[in]*/Float64 wFlange,/*[in]*/Float64 lSpacing,/*[in]*/Float64 rSpacing) override;
	STDMETHOD(get_FlangeCount)(/*[out,retval]*/FlangeIndexType* nFlanges) override;
	STDMETHOD(GetFlangeParameters)(/*[in]*/ FlangeIndexType flangeIdx,/*[out]*/Float64* tFlange,/*[out]*/Float64* wFlange,/*[out]*/Float64* lSpacing,/*[out]*/Float64* rSpacing) override;
   STDMETHOD(EffectiveFlangeWidth)(/*[out,retval]*/ Float64* effFlangeWidth) override;
};

#endif //__EFFECTIVEFLANGEWIDTHDETAILS_H_
