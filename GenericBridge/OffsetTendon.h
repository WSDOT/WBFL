///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2018  Washington State Department of Transportation
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

#pragma once
// OffsetTendon.h : Declaration of the COffsetTendon

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// COffsetTendon
class ATL_NO_VTABLE COffsetTendon : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<COffsetTendon,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<COffsetTendon, &CLSID_OffsetTendon>,
	public ISupportErrorInfo,
	public IOffsetTendon,
   public IStructuredStorage2,
   public IObjectSafetyImpl<COffsetTendon,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>
{
public:
   COffsetTendon()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_OFFSETTENDON)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(COffsetTendon)
	COM_INTERFACE_ENTRY(IOffsetTendon)
	COM_INTERFACE_ENTRY(ITendon)
   COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(COffsetTendon)
//	CONNECTION_POINT_ENTRY(IID_IOffsetTendonEvents)
END_CONNECTION_POINT_MAP()

private:
   Float64 m_OD, m_ID;
   StrandIndexType m_StrandCount;
   CComPtr<IPrestressingStrand> m_Material;
   JackingEndType m_JackingEnd;

   CComPtr<ITendon> m_RefTendon; // reference tendon

   ISuperstructureMember* m_pSSMbr; // weak references

   struct Point
   {
      Float64 offsetX;
      Float64 offsetY;
      Float64 z; // location along tendon

      bool operator<(const Point& p) const
      {
         return z < p.z;
      }
   };

   std::vector<Point> m_Points;

   Float64 GetOffsetX(Float64 z);
   Float64 GetOffsetY(Float64 z);
   Float64 GetOffsetSlopeX(Float64 z);
   Float64 GetOffsetSlopeY(Float64 z);

   // ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IOffsetTendon
public:
   STDMETHOD(putref_RefTendon)(ITendon* tendon) override;
   STDMETHOD(AddOffset)(Float64 z,Float64 offsetX,Float64 offsetY) override;

// ITendon
public:
   STDMETHOD(AddSegment)(/*[in]*/ ITendonSegment* segment) override;
	STDMETHOD(get_Segment)(/*[in]*/ CollectionIndexType index,/*[out,retval]*/ITendonSegment** segment) override;
	STDMETHOD(get_Count)(/*[out,retval]*/CollectionIndexType* count) override;
	STDMETHOD(RemoveSegment)(/*[in]*/ CollectionIndexType index) override;
	STDMETHOD(ClearSegments)() override;
	STDMETHOD(get_OutsideDiameter)(/*[out,retval]*/Float64* size) override;
	STDMETHOD(put_OutsideDiameter)(/*[in]*/Float64 size) override;
	STDMETHOD(get_InsideDiameter)(/*[out,retval]*/Float64* size) override;
	STDMETHOD(put_InsideDiameter)(/*[in]*/Float64 size) override;
	STDMETHOD(get_InsideDuctArea)(/*[out,retval]*/Float64* Apt) override;
	STDMETHOD(get_TendonArea)(/*[out,retval]*/Float64* Apt) override;
	STDMETHOD(get_StrandCount)(/*[out,retval]*/StrandIndexType* count) override;
	STDMETHOD(put_StrandCount)(/*[in]*/StrandIndexType count) override;
	STDMETHOD(get_Material)(/*[out,retval]*/IPrestressingStrand** material) override;
	STDMETHOD(putref_Material)(/*[in]*/IPrestressingStrand* material) override;
   STDMETHOD(get_MinimumRadiusOfCurvature)(/*[out,retval]*/Float64* pMinRadiusOfCurvature) override;
   STDMETHOD(get_CG)(/*[in]*/ Float64 z,/*[in]*/ TendonMeasure measure,/*[out,retval]*/IPoint3d** cg) override;
	STDMETHOD(get_Slope)(/*[in]*/ Float64 z,/*[in]*/ TendonMeasure measure,/*[out,retval]*/IVector3d** slope) override;
	STDMETHOD(get_Length)(/*[out,retval]*/Float64* length) override;
   STDMETHOD(get_Start)(IPoint3d** start) override;
	STDMETHOD(get_End)(IPoint3d** end) override;
   STDMETHOD(get_Centerline)(/*[in]*/ TendonMeasure measure,/*[out,retval]*/IPoint3dCollection** ppPoints) override;
   STDMETHOD(get_JackingEnd)(/*[out,retval]*/JackingEndType* type) override;
   STDMETHOD(put_JackingEnd)(/*[in]*/JackingEndType type) override;
   STDMETHOD(putref_SuperstructureMember)(/*[in]*/ISuperstructureMember* pMbr) override;
   STDMETHOD(get_SuperstructureMember)(/*[out,retval]*/ISuperstructureMember** ppMbr) override;

// IStructuredStorage2
public:
	STDMETHOD(Load)(/*[in]*/ IStructuredLoad2* load) override;
	STDMETHOD(Save)(/*[in]*/ IStructuredSave2* save) override;
};
