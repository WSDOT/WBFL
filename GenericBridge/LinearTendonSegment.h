///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright � 1999-2025  Washington State Department of Transportation
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

// LinearTendonSegment.h : Declaration of the CLinearTendonSegment

#ifndef __LINEARTENDONSEGMENT_H_
#define __LINEARTENDONSEGMENT_H_

#include "resource.h"       // main symbols
//#include "GenericBridgeCP.h"


/////////////////////////////////////////////////////////////////////////////
// CLinearTendonSegment
class ATL_NO_VTABLE CLinearTendonSegment : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CLinearTendonSegment,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CLinearTendonSegment, &CLSID_LinearTendonSegment>,
	public ISupportErrorInfo,
	public ILinearTendonSegment,
   public IStructuredStorage2,
//   public CProxyDLinearTendonSegmentEvents< CLinearTendonSegment >,
//   public ILinearTendonSegmentPointContainerImpl<CLinearTendonSegment>,
   public IObjectSafetyImpl<CLinearTendonSegment,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>
{
public:
   CLinearTendonSegment()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_LINEARTENDONSEGMENT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLinearTendonSegment)
	COM_INTERFACE_ENTRY(ILinearTendonSegment)
   COM_INTERFACE_ENTRY(ITendonSegment)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
//   COM_INTERFACE_ENTRY_IMPL(ILinearTendonSegmentPointContainer)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CLinearTendonSegment)
//	CONNECTION_POINT_ENTRY(IID_ILinearTendonSegmentEvents)
END_CONNECTION_POINT_MAP()

private:
   CComPtr<IPoint3d> m_Start;
   CComPtr<IPoint3d> m_End;
   ITendonSegment* m_pPrevSegment; // weak reference
   ITendonSegment* m_pNextSegment; // weak reference

   ITendon* m_pTendon; // weak reference

   // ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ILinearTendonSegment
public:
   STDMETHOD(put_Start)(/*[in]*/ IPoint3d* start) override;
	STDMETHOD(get_Start)(/*[out,retval]*/ IPoint3d** start) override;
	STDMETHOD(put_End)(/*[in]*/ IPoint3d* end) override;
   STDMETHOD(get_End)(/*[out,retval]*/ IPoint3d** end) override;
   STDMETHOD(putref_PrevTendonSegment)(/*[in]*/ITendonSegment* pTendonSegment) override;
   STDMETHOD(get_PrevTendonSegment)(/*[out,retval]*/ITendonSegment** ppTendonSegment) override;
   STDMETHOD(putref_NextTendonSegment)(/*[in]*/ITendonSegment* pTendonSegment) override;
   STDMETHOD(get_NextTendonSegment)(/*[out,retval]*/ITendonSegment** ppTendonSegment) override;

// ITendonSegment
public:
   STDMETHOD(get_Position)(/*[in]*/ TendonMeasure measure,/*[in]*/ Float64 z,/*[out,retval]*/ IPoint3d** cg) override;
	STDMETHOD(get_Slope)(/*[in]*/ Float64 z,/*[out,retval]*/ IVector3d** slope) override;
	STDMETHOD(get_Length)(/*[out,retval]*/ Float64* length) override;
   STDMETHOD(ProjectedLength)(/*[out]*/ Float64* dx,/*[out]*/ Float64* dy,/*[out]*/ Float64* dz) override;
   STDMETHOD(get_Centerline)(/*[in]*/ TendonMeasure measure,/*[out,retval]*/IPoint3dCollection** ppPoints) override;
   STDMETHOD(putref_Tendon)(/*[in]*/ITendon* pTendon) override;
   STDMETHOD(get_Tendon)(/*[out,retval]*/ITendon** ppTendon) override;
   STDMETHOD(get_MinimumRadiusOfCurvature)(/*[out,retval]*/Float64* pMinRadiusOfCurvature) override;

// IStructuredStorage2
public:
	STDMETHOD(Load)(/*[in]*/ IStructuredLoad2* load) override;
	STDMETHOD(Save)(/*[in]*/ IStructuredSave2* save) override;
};

#endif //__LINEARTENDONSEGMENT_H_
