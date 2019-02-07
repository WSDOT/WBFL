///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2019  Washington State Department of Transportation
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

// FShapeBarrier.h : Declaration of the CFShapeBarrier

#ifndef __FSHAPEBARRIER_H_
#define __FSHAPEBARRIER_H_

#include "resource.h"       // main symbols


/////////////////////////////////////////////////////////////////////////////
// CFShapeBarrier
class ATL_NO_VTABLE CFShapeBarrier : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CFShapeBarrier,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CFShapeBarrier, &CLSID_FShapeBarrier>,
	public ISupportErrorInfo,
	public IFShapeBarrier,
   public IStructuredStorage2,
   public IObjectSafetyImpl<CFShapeBarrier,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>
{
public:
   CFShapeBarrier()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_FSHAPEBARRIER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CFShapeBarrier)
	COM_INTERFACE_ENTRY(IFShapeBarrier)
	COM_INTERFACE_ENTRY(IBarrier)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

private:
   CComPtr<ITrafficBarrier> m_BarrierShape;
   CComPtr<IMaterial> m_Material;

   // ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IFShapeBarrier
   STDMETHOD(put_Shape)(/*[in]*/ ITrafficBarrier* shape) override;

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

#endif //__FSHAPEBARRIER_H_
