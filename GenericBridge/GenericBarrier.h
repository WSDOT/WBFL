///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2021  Washington State Department of Transportation
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

// GenericBarrier.h : Declaration of the CGenericBarrier

#ifndef __GENERICBARRIER_H_
#define __GENERICBARRIER_H_

#include "resource.h"       // main symbols


/////////////////////////////////////////////////////////////////////////////
// CGenericBarrier
class ATL_NO_VTABLE CGenericBarrier : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CGenericBarrier,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CGenericBarrier, &CLSID_GenericBarrier>,
	public ISupportErrorInfo,
	public IGenericBarrier,
   public IStructuredStorage2,
   public IObjectSafetyImpl<CGenericBarrier,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>
{
public:
   CGenericBarrier();

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_GENERICBARRIER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CGenericBarrier)
	COM_INTERFACE_ENTRY(IGenericBarrier)
	COM_INTERFACE_ENTRY(IBarrier)

	COM_INTERFACE_ENTRY(IStructuredStorage2)

	COM_INTERFACE_ENTRY(ISupportErrorInfo)

   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

private:
   CComPtr<IShape> m_BarrierShape;
   CComPtr<IMaterial> m_Material;
   Float64 m_CurbLoc;
   Float64 m_InteriorToe;
   Float64 m_ExteriorToe;

   // ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IGenericBarrier
   STDMETHOD(Init)(/*[in]*/IShape* shape, /*[in]*/Float64 curbLocation, /*[in]*/ Float64 interiorToe,/*[in]*/Float64 exteriorToe) override;

// IBarrier
public:
   STDMETHOD(get_Shape)(/*[out,retval]*/ IShape** shape) override;
	STDMETHOD(get_Material)(/*[out,retval]*/ IMaterial** material) override;
	STDMETHOD(putref_Material)(/*[in]*/ IMaterial* material) override;
   STDMETHOD(get_CurbLocation)(/*[out,retval]*/Float64* loc) override;
   STDMETHOD(get_BarrierToeLocations)(/*[out]*/ Float64* interiorToe,/*[out]*/Float64* exteriorToe) override;
   STDMETHOD(Clone)(/*[out,retval]*/IBarrier** barrier) override;

// IStructuredStorage2
public:
	STDMETHOD(Load)(/*[in]*/ IStructuredLoad2* load) override;
	STDMETHOD(Save)(/*[in]*/ IStructuredSave2* save) override;
};

#endif //__GenericBARRIER_H_
