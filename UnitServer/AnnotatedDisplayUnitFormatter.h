///////////////////////////////////////////////////////////////////////
// UnitServer - Unit Conversion and Display Unit Management Library
// Copyright © 2000  Washington State Department of Transportation
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

// AnnotatedDisplayUnitFormatter.h : Declaration of the CAnnotatedDisplayUnitFormatter

#ifndef __ANNOTATEDDISPLAYUNITFORMATTER_H_
#define __ANNOTATEDDISPLAYUNITFORMATTER_H_

#include "resource.h"       // main symbols
#include "WbflUnitServerCP.h"

/////////////////////////////////////////////////////////////////////////////
// CAnnotatedDisplayUnitFormatter
class ATL_NO_VTABLE CAnnotatedDisplayUnitFormatter : 
   public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CAnnotatedDisplayUnitFormatter,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CAnnotatedDisplayUnitFormatter, &CLSID_AnnotatedDisplayUnitFormatter>,
   public IConnectionPointContainerImpl<CAnnotatedDisplayUnitFormatter>,
   public ISupportErrorInfoImpl<&IID_IDisplayUnitFormatter>,
   public IObjectSafetyImpl<CAnnotatedDisplayUnitFormatter,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
   public IAnnotatedDisplayUnitFormatter,
   public CProxyDDisplayUnitFormatterEvents< CAnnotatedDisplayUnitFormatter >
{
public:
   CAnnotatedDisplayUnitFormatter() :
   m_bstrAnnotation("")
	{
      m_nDigits = 0;
      m_Multiplier = 12.0;
      m_bstrAnnotation = "ft-,in";
      m_bstrSeperator = "ft-";
      m_bstrSuffix = "in";
      m_Width = 0;
      m_Precision = 6;
      m_Notation = nftAutomatic;
      m_Justify = tjRight;
      m_ZeroTolerance = 1e-06;
   }

DECLARE_REGISTRY_RESOURCEID(IDR_ANNOTATEDDISPLAYUNITFORMATTER)
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CAnnotatedDisplayUnitFormatter)
	COM_INTERFACE_ENTRY(IAnnotatedDisplayUnitFormatter)
   COM_INTERFACE_ENTRY(IDisplayUnitFormatter)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IConnectionPointContainer)
   COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CAnnotatedDisplayUnitFormatter)
CONNECTION_POINT_ENTRY(IID_IDisplayUnitFormatterEvents)
END_CONNECTION_POINT_MAP()

private:
   UINT32 m_nDigits;
   Float64 m_Multiplier;
   CComBSTR m_bstrAnnotation;
   CComBSTR m_bstrSeperator;
   CComBSTR m_bstrSuffix;
   UINT32 m_Width;
   UINT32 m_Precision;
   NumericFormatType m_Notation;
   TextJustificationType m_Justify;
   Float64 m_ZeroTolerance;

// ISupportErrorInfo
public:
   STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IAnnotatedDisplayUnitFormatter
public:
	STDMETHOD(FormatSpecifiers)(/*[in]*/Uint32 width,/*[in]*/ Uint32 precision,/*[in]*/ TextJustificationType justify,/*[in]*/NumericFormatType notation,/*[in]*/ Float64 zeroVal);
	STDMETHOD(get_Width)(/*[out, retval]*/ Uint32 *width);
	STDMETHOD(get_Precision)(/*[out, retval]*/ Uint32 *precision);
   STDMETHOD(get_Notation)(/*[out,retval]*/ NumericFormatType* notation);
	STDMETHOD(get_Justification)(/*[out,retval]*/ TextJustificationType* justify);
	STDMETHOD(get_ZeroTolerance)(/*[out,retval]*/ Float64* zeroTol);
   STDMETHOD(Format)(/*[in]*/ Float64 cv,/*[in]*/ BSTR tag,/*[out,retval]*/ BSTR* fmtString);
   STDMETHOD(get_UsesTag)(/*[out,retval]*/ VARIANT_BOOL* bUsesTag);
	STDMETHOD(put_OffsetDigits)(/*[in]*/ Uint32 nDigits);
	STDMETHOD(get_OffsetDigits)(/*[out,retval]*/ Uint32* nDigits);
	STDMETHOD(put_Multiplier)(/*[in]*/ Float64 multiplier);
	STDMETHOD(get_Multiplier)(/*[out,retval]*/ Float64 *multiplier);
	STDMETHOD(put_Annotation)(/*[in]*/ BSTR bstrAnnotation);
	STDMETHOD(get_Annotation)(/*[out,retval]*/ BSTR* bstrAnnotation);
};

#endif //__ANNOTATEDDISPLAYUNITFORMATTER_H_
