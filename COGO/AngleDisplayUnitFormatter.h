///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
// Copyright © 1999-2023  Washington State Department of Transportation
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

// AngleDisplayUnitFormatter.h : Declaration of the CAngleDisplayUnitFormatter

#ifndef __ANGLEDISPLAYUNITFORMATTER_H_
#define __ANGLEDISPLAYUNITFORMATTER_H_
#pragma once

#include "resource.h"       // main symbols
#include "COGOCP.h"

/////////////////////////////////////////////////////////////////////////////
// CAngleDisplayUnitFormatter
class ATL_NO_VTABLE CAngleDisplayUnitFormatter : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CAngleDisplayUnitFormatter, &CLSID_AngleDisplayUnitFormatter>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CAngleDisplayUnitFormatter,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IConnectionPointContainerImpl<CAngleDisplayUnitFormatter>,
	public IAngleDisplayUnitFormatter,
	public CProxyDDisplayUnitFormatterEvents< CAngleDisplayUnitFormatter >
{
public:
	CAngleDisplayUnitFormatter()
	{
	}

   HRESULT FinalConstruct();

DECLARE_REGISTRY_RESOURCEID(IDR_ANGLEDISPLAYUNITFORMATTER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CAngleDisplayUnitFormatter)
	COM_INTERFACE_ENTRY(IAngleDisplayUnitFormatter)
   COM_INTERFACE_ENTRY(IDisplayUnitFormatter)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CAngleDisplayUnitFormatter)
CONNECTION_POINT_ENTRY(IID_IDisplayUnitFormatterEvents)
END_CONNECTION_POINT_MAP()


// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IDisplayUnitFormatter
public:
	STDMETHOD(FormatSpecifiers)(/*[in]*/ Uint32 width,/*[in]*/Uint32 precision,/*[in]*/ TextJustificationType justify,/*[in]*/NumericFormatType fmt,/*[in]*/ Float64 zeroVal) override;
	STDMETHOD(get_Width)(/*[out,retval]*/ Uint32* val) override;
	STDMETHOD(get_Precision)(/*[out,retval]*/ Uint32* val) override;
	STDMETHOD(get_Notation)(/*[out,retval]*/ NumericFormatType* notation) override;
	STDMETHOD(get_Justification)(/*[out,retval]*/ TextJustificationType* justify) override;
	STDMETHOD(get_ZeroTolerance)(/*[out,retval]*/ Float64* zeroTol) override;
   STDMETHOD(Format)(/*[in]*/ Float64 val, /*[in]*/ BSTR tag,/*[out,retval]*/ BSTR* fmtString) override;
   STDMETHOD(get_UsesTag)(/*[out,retval]*/ VARIANT_BOOL *bUsesTag) override;

// IAngleDisplayUnitFormatter
public:
	STDMETHOD(get_Signed)(/*[out, retval]*/ VARIANT_BOOL *pVal) override;
	STDMETHOD(put_Signed)(/*[in]*/ VARIANT_BOOL newVal) override;
	STDMETHOD(get_CondensedFormat)(/*[out, retval]*/ VARIANT_BOOL *pVal) override;
	STDMETHOD(put_CondensedFormat)(/*[in]*/ VARIANT_BOOL newVal) override;

private:
   VARIANT_BOOL m_bSigned;
   VARIANT_BOOL m_bCondensedFormat;
   Uint32 m_Width;
   Uint32 m_Precision;
   TextJustificationType m_Justification;
   NumericFormatType m_Notation;
   Float64 m_ZeroTolerance;
};

#endif //__ANGLEDISPLAYUNITFORMATTER_H_
