///////////////////////////////////////////////////////////////////////
// UnitServer - Unit Conversion and Display Unit Management Library
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

// DisplayUnitFormatter.h : Declaration of the CDisplayUnitFormatter

#ifndef __DISPLAYUNITFORMATTER_H_
#define __DISPLAYUNITFORMATTER_H_

#include "resource.h"       // main symbols
#include "WbflUnitServerCP.h"

/////////////////////////////////////////////////////////////////////////////
// CDisplayUnitFormatter
class ATL_NO_VTABLE CDisplayUnitFormatter : 
   public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CDisplayUnitFormatter,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CDisplayUnitFormatter, &CLSID_DisplayUnitFormatter>,
   public IConnectionPointContainerImpl<CDisplayUnitFormatter>,
   public ISupportErrorInfoImpl<&IID_IDisplayUnitFormatter>,
   public IObjectSafetyImpl<CDisplayUnitFormatter,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IDisplayUnitFormatter,
	public CProxyDDisplayUnitFormatterEvents< CDisplayUnitFormatter >
{
public:
	CDisplayUnitFormatter()
	{
      m_Width = 0;
      m_Precision = 6;
      m_Notation = nftAutomatic;
      m_Justify = tjRight;
      m_ZeroTolerance = 1e-06;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_DISPLAYUNITFORMATTER)
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CDisplayUnitFormatter)
	COM_INTERFACE_ENTRY(IDisplayUnitFormatter)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CDisplayUnitFormatter)
CONNECTION_POINT_ENTRY(IID_IDisplayUnitFormatterEvents)
END_CONNECTION_POINT_MAP()

protected:
   Uint32 m_Width;
   Uint32 m_Precision;
   NumericFormatType m_Notation;
   TextJustificationType m_Justify;
   Float64 m_ZeroTolerance;

// IDisplayUnitFormatter
public:
   STDMETHOD(get_UsesTag)(/*[out,retval]*/ VARIANT_BOOL *bUsesTag);
   STDMETHOD(Format)(/*[in]*/ Float64 cv,/*[in]*/ BSTR tag,/*[out,retval]*/ BSTR* fmtString);
	STDMETHOD(get_Justification)(/*[out,retval]*/ TextJustificationType* justify);
   STDMETHOD(get_Notation)(/*[out,retval]*/ NumericFormatType* notation);
	STDMETHOD(get_Width)(/*[out, retval]*/ Uint32 *width);
	STDMETHOD(get_Precision)(/*[out, retval]*/ Uint32 *precision);
	STDMETHOD(get_ZeroTolerance)(/*[out, retval]*/ Float64 *zeroTol);
	STDMETHOD(FormatSpecifiers)(/*[in]*/Uint32 width,/*[in]*/ Uint32 precision,/*[in]*/ TextJustificationType justify,/*[in]*/NumericFormatType notation,/*[in]*/ Float64 zeroTol);
};

#endif //__DISPLAYUNITFORMATTER_H_
