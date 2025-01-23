///////////////////////////////////////////////////////////////////////
// LBAM Analysis - Longitindal Bridge Analysis Model
// Copyright © 1999-2025  Washington State Department of Transportation
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

// SectionResult3D.h : Declaration of the CSectionResult3D

#ifndef __SECTIONRESULT3D_H_
#define __SECTIONRESULT3D_H_

#include "resource.h"       // main symbols
#include "WBFLLBAMAnalysis.h"

/////////////////////////////////////////////////////////////////////////////
// CSectionResult3D
class ATL_NO_VTABLE CSectionResult3D : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSectionResult3D, &CLSID_SectionResult3D>,
	public ISupportErrorInfo,
	public ISectionResult3D, 
   public IPersistImpl<CSectionResult3D>,
   public IObjectSafetyImpl<CSectionResult3D,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IStructuredStorage2
{
public:
   CSectionResult3D():
   m_XLeft(0.0),
   m_YLeft(0.0),
   m_ZLeft(0.0),
   m_XRight(0.0),
   m_YRight(0.0),
   m_ZRight(0.0)
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_SECTIONRESULT3D)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSectionResult3D)
	COM_INTERFACE_ENTRY(ISectionResult3D)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(IPersist)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

   // IStructuredStorage2
	STDMETHOD(Load)(IStructuredLoad2 * Load) override;
	STDMETHOD(Save)(IStructuredSave2 * Save) override;

// ISectionResult3D
public:
	STDMETHOD(GetSingleResult)(/*[in]*/ForceEffectType effect, /*[out]*/ Float64 *leftVal, /*[out]*/ Float64 *rightVal) override;
	STDMETHOD(SetSingleResult)(/*[in]*/ForceEffectType effect, /*[in]*/ Float64 leftVal, /*[in]*/ Float64 rightVal) override;
	STDMETHOD(Zero)() override;
	STDMETHOD(Sum)(/*[in]*/Float64 XLeft, /*[in]*/Float64 YLeft, /*[in]*/Float64 ZLeft, /*[in]*/Float64 XRight, /*[in]*/Float64 YRight, /*[in]*/Float64 ZRight) override;
	STDMETHOD(FactorAndSum)(/*[in]*/ISectionResult3D* res,/*[in]*/Float64 leftFactor,/*[in]*/Float64 rightFactor) override;
	STDMETHOD(Clone)(/*[out,retval]*/ISectionResult3D** clone) override;
	STDMETHOD(GetResult)(/*[out]*/Float64* XLeft, /*[out]*/Float64* YLeft, /*[out]*/Float64* ZLeft, /*[out]*/Float64* XRight, /*[out]*/Float64* YRight, /*[out]*/Float64* ZRight) override;
	STDMETHOD(SetResult)(/*[in]*/Float64 XLeft, /*[in]*/Float64 YLeft, /*[in]*/Float64 ZLeft, /*[in]*/Float64 XRight, /*[in]*/Float64 YRight, /*[in]*/Float64 ZRight) override;
	STDMETHOD(get_ZRight)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_ZRight)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_ZLeft)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_ZLeft)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_YRight)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_YRight)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_YLeft)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_YLeft)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_XRight)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_XRight)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_XLeft)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_XLeft)(/*[in]*/ Float64 newVal) override;

protected:
   // pack data members so we can get at them by name or index
   union
   {
      struct {
         Float64 m_XLeft;
         Float64 m_YLeft;
         Float64 m_ZLeft;
         Float64 m_XRight;
         Float64 m_YRight;
         Float64 m_ZRight;
      };

      Float64 ForceVec[6];
   };
};

#endif //__SECTIONRESULT3D_H_
