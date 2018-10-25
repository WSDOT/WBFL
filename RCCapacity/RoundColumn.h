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

// RoundColumn.h : Declaration of the CRoundColumn

#ifndef __RoundColumn_H_
#define __RoundColumn_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CRoundColumn
class ATL_NO_VTABLE CRoundColumn : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CRoundColumn, &CLSID_RoundColumn>,
	public ISupportErrorInfo,
	public IRoundColumn
{
public:
	CRoundColumn()
	{
      m_Diameter = 72;
      m_Cover    = 2.0;
      m_As       = 10;
      m_Fc = 4;
      m_Fy = 60;
      m_Es = 29000;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ROUNDCOLUMN)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CRoundColumn)
	COM_INTERFACE_ENTRY(IRoundColumn)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

   Float64 m_Diameter;
   Float64 m_As;
   Float64 m_Cover;
   Float64 m_Fc;
   Float64 m_Fy;
   Float64 m_Es;

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IRoundColumn
public:
   STDMETHOD(put_Diameter)(/*[in]*/Float64 dia);
   STDMETHOD(get_Diameter)(/*[out,retval]*/Float64* dia);
   STDMETHOD(put_Cover)(/*[in]*/Float64 cover);
   STDMETHOD(get_Cover)(/*[out,retval]*/Float64* cover);
   STDMETHOD(put_As)(/*[in]*/Float64 as);
   STDMETHOD(get_As)(/*[out,retval]*/Float64* as);
   STDMETHOD(put_fc)(/*[in]*/Float64 fc);
   STDMETHOD(get_fc)(/*[out,retval]*/Float64* fc);
   STDMETHOD(put_fy)(/*[in]*/Float64 fy);
   STDMETHOD(get_fy)(/*[out,retval]*/Float64* fy);
   STDMETHOD(put_Es)(/*[in]*/Float64 es);
   STDMETHOD(get_Es)(/*[out,retval]*/Float64* es);
   STDMETHOD(ComputeInteraction)(/*[in]*/ long nSteps,/*[out,retval]*/IPoint2dCollection* *points);
};

#endif //__RoundColumn_H_
