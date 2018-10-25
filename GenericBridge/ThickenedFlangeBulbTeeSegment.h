///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2015  Washington State Department of Transportation
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

// ThickenedFlangeBulbTeeSegment.h : Declaration of the CSegment

#pragma once

#include "resource.h"       // main symbols
#include "GenericBridgeCP.h"
#include "Segments.h"

/////////////////////////////////////////////////////////////////////////////
// CThickenedFlangeBulbTeeSegment
class ATL_NO_VTABLE CThickenedFlangeBulbTeeSegment : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CSegment,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CThickenedFlangeBulbTeeSegment, &CLSID_ThickenedFlangeBulbTeeSegment>,
	public ISupportErrorInfo,
   public CProxyDSegmentEvents< CThickenedFlangeBulbTeeSegment >,
   public IConnectionPointContainerImpl<CThickenedFlangeBulbTeeSegment>,
   public IObjectSafetyImpl<CThickenedFlangeBulbTeeSegment,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
   public IThickenedFlangeBulbTeeSegment,
   public IMaterialEvents,
   public IStructuredStorage2
{
   friend CThickenedFlangeBulbTeeSegment; // for easy cloning
public:
   CThickenedFlangeBulbTeeSegment()
	{
      m_pSegmentMeasure = 0;
      m_Orientation = 0;
	}

   HRESULT FinalConstruct();
   void FinalRelease();


DECLARE_REGISTRY_RESOURCEID(IDR_THICKENEDFLANGEBULBTEESEGMENT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CThickenedFlangeBulbTeeSegment)
	COM_INTERFACE_ENTRY(IThickenedFlangeBulbTeeSegment)
	COM_INTERFACE_ENTRY(ISegment)
   COM_INTERFACE_ENTRY(IMaterialEvents)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CThickenedFlangeBulbTeeSegment)
	CONNECTION_POINT_ENTRY(IID_ISegmentEvents)
END_CONNECTION_POINT_MAP()

private:
   Float64 m_Length;
   CComPtr<IBulbTeeSection> m_Beam;
   Float64 m_FlangeThickening;
   ISegmentMeasure* m_pSegmentMeasure; // weak reference because it is SuperstructureMember
                                       // that implements this interface. Strong reference
                                       // creates a circular reference situation

   Float64 m_Orientation; // orientation of girder... plumb = 0... rotated CW is +... radians

   CComPtr<IMaterial> m_Material;
   DWORD m_dwMaterialCookie;

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ISegment
public:
   STDMETHOD(putref_SegmentMeasure)(/*[in]*/ISegmentMeasure* sm);
	STDMETHOD(Clone)(/*[out,retval]*/ISegment** ppClone);
	STDMETHOD(get_Shape)(/*[in]*/ Float64 distAlongSegment,/*[out,retval]*/IShape** ppShape);
	STDMETHOD(get_Length)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_Length)(/*[in]*/ Float64 newVal);
   STDMETHOD(get_SegmentLength)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(putref_Material)(/*[in]*/IMaterial* material);
   STDMETHOD(get_Material)(/*[out,retval]*/IMaterial* *material);
   STDMETHOD(put_Orientation)(/*[in]*/Float64 orientation);
	STDMETHOD(get_Orientation)(/*[out,retval]*/Float64* orientation);

// IThickenedFlangeBulbTeeSegment
public:
	STDMETHOD(putref_BulbTeeSection)(/*[in]*/ IBulbTeeSection* pPrecastBeam,/*[in]*/Float64 flangeThickening);

// IMaterialEvents
public:
	STDMETHOD(OnMaterialChanged)(IMaterial* material)
   {
      Fire_OnSegmentChanged(this);
      return S_OK;
   }

// IStructuredStorage2
public:
	STDMETHOD(Load)(/*[in]*/ IStructuredLoad2* load);
	STDMETHOD(Save)(/*[in]*/ IStructuredSave2* save);

private:
   Float64 GetSuperstructureMemberLength();
};

