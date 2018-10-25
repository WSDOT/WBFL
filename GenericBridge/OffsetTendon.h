///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2013  Washington State Department of Transportation
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
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(COffsetTendon)
//	CONNECTION_POINT_ENTRY(IID_IOffsetTendonEvents)
END_CONNECTION_POINT_MAP()

private:
   Float64 m_DuctDiameter;
   StrandIndexType m_StrandCount;
   CComPtr<IPrestressingStrand> m_Material;
   JackingEndType m_JackingEnd;

   CComPtr<ITendon> m_RefTendon; // reference tendon

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
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IOffsetTendon
public:
   STDMETHOD(putref_RefTendon)(ITendon* tendon);
   STDMETHOD(AddOffset)(Float64 z,Float64 offsetX,Float64 offsetY);

// ITendon
public:
   STDMETHOD(AddSegment)(/*[in]*/ ITendonSegment* segment);
	STDMETHOD(get_Segment)(/*[in]*/ CollectionIndexType index,/*[out,retval]*/ITendonSegment** segment);
	STDMETHOD(get_Count)(/*[out,retval]*/CollectionIndexType* count);
	STDMETHOD(RemoveSegment)(/*[in]*/ CollectionIndexType index);
	STDMETHOD(ClearSegments)();
	STDMETHOD(get_DuctDiameter)(/*[out,retval]*/Float64* size);
	STDMETHOD(put_DuctDiameter)(/*[in]*/Float64 size);
	STDMETHOD(get_TendonArea)(/*[out,retval]*/Float64* Apt);
	STDMETHOD(get_StrandCount)(/*[out,retval]*/StrandIndexType* count);
	STDMETHOD(put_StrandCount)(/*[in]*/StrandIndexType count);
	STDMETHOD(get_Material)(/*[out,retval]*/IPrestressingStrand** material);
	STDMETHOD(putref_Material)(/*[in]*/IPrestressingStrand* material);
   STDMETHOD(get_CG)(/*[in]*/ Float64 z,/*[in]*/ TendonMeasure measure,/*[out,retval]*/IPoint3d** cg);
	STDMETHOD(get_Slope)(/*[in]*/ Float64 z,/*[in]*/ TendonMeasure measure,/*[out,retval]*/IVector3d** slope);
	STDMETHOD(get_Length)(/*[out,retval]*/Float64* length);
   STDMETHOD(get_Start)(IPoint3d** start);
	STDMETHOD(get_End)(IPoint3d** end);
   STDMETHOD(get_JackingEnd)(/*[out,retval]*/JackingEndType* type);
   STDMETHOD(put_JackingEnd)(/*[in]*/JackingEndType type);

// IStructuredStorage2
public:
	STDMETHOD(Load)(/*[in]*/ IStructuredLoad2* load);
	STDMETHOD(Save)(/*[in]*/ IStructuredSave2* save);
};
