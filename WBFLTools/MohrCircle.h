///////////////////////////////////////////////////////////////////////
// WBFLTools - Utility Tools for the WBFL
// Copyright © 1999-2020  Washington State Department of Transportation
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

// MohrCircle.h : Declaration of the CMohrCircle

#ifndef __MOHRCIRCLE_H_
#define __MOHRCIRCLE_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMohrCircle
class ATL_NO_VTABLE CMohrCircle : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMohrCircle, &CLSID_MohrCircle>,
   public IObjectSafetyImpl<CMohrCircle,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IMohrCircle
{
public:
	CMohrCircle()
	{
      m_Sii = 0;
      m_Sjj = 0;
      m_Sij = 0;
   }

DECLARE_REGISTRY_RESOURCEID(IDR_MOHRCIRCLE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMohrCircle)
	COM_INTERFACE_ENTRY(IMohrCircle)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

private:
   Float64 m_Sii;
   Float64 m_Sjj;
   Float64 m_Sij;

// IMohrCircle
public:
	STDMETHOD(ComputeSxx)(/*[in]*/ Float64 angle,/*[out,retval]*/Float64* sxx) override;
	STDMETHOD(ComputeSxy)(/*[in]*/ Float64 angle,/*[out,retval]*/Float64* sxy) override;
	STDMETHOD(ComputeSyy)(/*[in]*/ Float64 angle,/*[out,retval]*/Float64* syy) override;
	STDMETHOD(ComputeState)(/*[in]*/ Float64 angle,/*[out]*/ Float64* S11,/*[out]*/ Float64* S22, /*[out]*/ Float64* S12) override;
	STDMETHOD(get_Tmax)(/*[out, retval]*/ Float64 *Tmax) override;
	STDMETHOD(get_Smin)(/*[out, retval]*/ Float64 *Smin) override;
	STDMETHOD(get_Smax)(/*[out, retval]*/ Float64 *Smax) override;
	STDMETHOD(get_PrincipleDirection)(/*[out, retval]*/ Float64 *dir) override;
	STDMETHOD(get_Radius)(/*[out, retval]*/ Float64 *radius) override;
	STDMETHOD(get_Center)(/*[out, retval]*/ Float64 *center) override;
	STDMETHOD(get_Sij)(/*[out, retval]*/ Float64 *sij) override;
	STDMETHOD(put_Sij)(/*[in]*/ Float64 sij) override;
	STDMETHOD(get_Sjj)(/*[out, retval]*/ Float64 *sjj) override;
	STDMETHOD(put_Sjj)(/*[in]*/ Float64 sjj) override;
	STDMETHOD(get_Sii)(/*[out, retval]*/ Float64 *sii) override;
	STDMETHOD(put_Sii)(/*[in]*/ Float64 sii) override;
};

#endif //__MOHRCIRCLE_H_
