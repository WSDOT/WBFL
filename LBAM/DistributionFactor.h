///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright © 1999-2017  Washington State Department of Transportation
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

// DistributionFactor.h : Declaration of the CDistributionFactor

#ifndef __DISTRIBUTIONFACTOR_H_
#define __DISTRIBUTIONFACTOR_H_

#include "resource.h"       // main symbols
#include "LBAMCP.h"

/////////////////////////////////////////////////////////////////////////////
// CDistributionFactor
class ATL_NO_VTABLE CDistributionFactor : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CDistributionFactor,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CDistributionFactor, &CLSID_DistributionFactor>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CDistributionFactor>,
	public IDistributionFactor,
   public IPersistImpl<CDistributionFactor>,
	public IStructuredStorage2,
   public IObjectSafetyImpl<CDistributionFactor,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public CProxyDDistributionFactorEvents< CDistributionFactor >
{
public:
   CDistributionFactor():
   m_GPedestrian(1.0),
   m_GFatM(1.0),
   m_GFatV(1.0),
   m_GRMul(1.0),
   m_GRSgl(1.0),
   m_GTSgl(1.0),
   m_GTMul(1.0),
   m_GDMul(1.0),
   m_GDSgl(1.0),
   m_GVMul(1.0),
   m_GVSgl(1.0),
   m_GNMMul(1.0),
   m_GNMSgl(1.0),
   m_GPMMul(1.0),
   m_GPMSgl(1.0)
	{
	}

   ~CDistributionFactor()
   {
   }


DECLARE_REGISTRY_RESOURCEID(IDR_DISTRIBUTIONFACTOR)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CDistributionFactor)
	COM_INTERFACE_ENTRY(IDistributionFactor)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(IPersist)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CDistributionFactor)
CONNECTION_POINT_ENTRY(IID_IDistributionFactorEvents)
END_CONNECTION_POINT_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IDistributionFactor
public:
	STDMETHOD(get_GTMul)(/*[out, retval]*/ Float64  *pVal) override;
	STDMETHOD(put_GTMul)(/*[in]*/ Float64  newVal) override;
	STDMETHOD(Clone)(/*[out, retval]*/IDistributionFactor**) override;
	STDMETHOD(SetG)(/*[in]*/ Float64 PMSgl, /*[in]*/ Float64 PMMul, /*[in]*/ Float64 NMSgl,
                   /*[in]*/ Float64 NMMul, /*[in]*/ Float64 VSgl,  /*[in]*/ Float64 VMul, 
                   /*[in]*/ Float64 DSgl,  /*[in]*/ Float64 DMul,  /*[in]*/ Float64 RSgl, 
                   /*[in]*/ Float64 RMul,  /*[in]*/ Float64 TSgl,  /*[in]*/ Float64 TMul,
                   /*[in]*/ Float64 FatM,  /*[in]*/ Float64 FatV,  /*[in]*/ Float64 Pedestrian);
	STDMETHOD(GetG)(/*[out]*/ Float64* PMSgl, /*[out]*/ Float64* PMMul, /*[out]*/ Float64* NMSgl, 
                   /*[out]*/ Float64* NMMul, /*[out]*/ Float64* VSgl,  /*[out]*/ Float64* VMul, 
                   /*[out]*/ Float64* DSgl,  /*[out]*/ Float64* DMul,  /*[out]*/ Float64* RSgl, 
                   /*[out]*/ Float64* RMul,  /*[out]*/ Float64* TSgl,  /*[out]*/ Float64* TMul,
                   /*[out]*/ Float64* FatM,  /*[out]*/ Float64* FatV,  /*[out]*/ Float64* Pedestrian);
	STDMETHOD(get_GPedestrian)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_GPedestrian)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(GetGFat)(/*[out]*/ Float64 *pMom, /*[out]*/ Float64 *pShear) override;
	STDMETHOD(SetGFat)(/*[in]*/  Float64 gMom,  /*[in]*/  Float64 gShear) override;
	STDMETHOD(get_GRMul)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_GRMul)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_GRSgl)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_GRSgl)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_GTSgl)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_GTSgl)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_GDMul)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_GDMul)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_GDSgl)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_GDSgl)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_GVMul)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_GVMul)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_GVSgl)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_GVSgl)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_GNMMul)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_GNMMul)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_GNMSgl)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_GNMSgl)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_GPMMul)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_GPMMul)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_GPMSgl)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_GPMSgl)(/*[in]*/ Float64 newVal) override;

// IStructuredStorage2
	STDMETHOD(Load)(IStructuredLoad2 * Load) override;
	STDMETHOD(Save)(IStructuredSave2 * Save) override;

protected:
   Float64 m_GPedestrian;
   Float64 m_GFatM, m_GFatV;
   Float64 m_GRMul;
   Float64 m_GRSgl;
   Float64 m_GTSgl;
   Float64 m_GTMul;
   Float64 m_GDMul;
   Float64 m_GDSgl;
   Float64 m_GVMul;
   Float64 m_GVSgl;
   Float64 m_GNMMul;
   Float64 m_GNMSgl;
   Float64 m_GPMMul;
   Float64 m_GPMSgl;

private:
HRESULT PutVal(Float64 newVal, Float64& G);
HRESULT PutVal2(Float64 newVal, Float64& G, bool& dofire);
HRESULT GetProp(IStructuredLoad2 *pload, BSTR name, Float64& prop);
};

#endif //__DISTRIBUTIONFACTOR_H_

