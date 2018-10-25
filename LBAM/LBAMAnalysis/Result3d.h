///////////////////////////////////////////////////////////////////////
// LBAM Analysis - Longitindal Bridge Analysis Model
// Copyright © 1999-2013  Washington State Department of Transportation
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

// Result3D.h : Declaration of the CResult3D

#ifndef __RESULT3D_H_
#define __RESULT3D_H_

#include "resource.h"       // main symbols
#include "WBFLLBAMAnalysis.h"

/////////////////////////////////////////////////////////////////////////////
// CResult3D
class ATL_NO_VTABLE CResult3D : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CResult3D, &CLSID_Result3D>,
	public ISupportErrorInfo,
	public IResult3D,
   public IPersistImpl<CResult3D>,
   public IObjectSafetyImpl<CResult3D,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IStructuredStorage2
{
public:
   CResult3D():
   m_X(0.0),
   m_Y(0.0),
   m_Z(0.0)
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_RESULT3D)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CResult3D)
	COM_INTERFACE_ENTRY(IResult3D)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(IPersist)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IStructuredStorage2
	STDMETHOD(Load)(IStructuredLoad2 * Load);
	STDMETHOD(Save)(IStructuredSave2 * Save);

// IResult3D
public:
	STDMETHOD(SetSingleResult)(/*[in]*/ForceEffectType fet, /*[in]*/Float64 val);
	STDMETHOD(GetSingleResult)(/*[in]*/ForceEffectType fet, /*[out,retval]*/Float64* val);
	STDMETHOD(GetResult)(/*[out]*/Float64* X, /*[out]*/Float64* Y, /*[out]*/Float64* Z);
	STDMETHOD(SetResult)(/*[in]*/Float64 X, /*[in]*/Float64 Y, /*[in]*/Float64 Z);
	STDMETHOD(Zero)();
	STDMETHOD(Sum)(/*[in]*/Float64 X, /*[in]*/Float64 Y, /*[in]*/Float64 Z);
	STDMETHOD(FactorAndSum)(/*[in]*/IResult3D* res, /*[in]*/Float64 factor);
	STDMETHOD(Clone)(/*[out,retval]*/IResult3D** clone);
	STDMETHOD(get_Z)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_Z)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_Y)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_Y)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_X)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_X)(/*[in]*/ Float64 newVal);

protected:
   union
   {
      struct {
         Float64 m_X;
         Float64 m_Y;
         Float64 m_Z;
      };

      Float64 ForceVec[3];
   };

};

#endif //__RESULT3D_H_
