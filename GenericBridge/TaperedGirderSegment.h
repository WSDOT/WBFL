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

// TaperedGirderSegment.h : Declaration of the CSegment

#pragma once

#include "resource.h"       // main symbols
#include "ItemDataManager.h"
#include "SuperstructureMemberSegmentImpl.h"
#include <array>

/////////////////////////////////////////////////////////////////////////////
// CTaperedGirderSegment
class ATL_NO_VTABLE CTaperedGirderSegment : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CSegment,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CTaperedGirderSegment, &CLSID_TaperedGirderSegment>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CTaperedGirderSegment,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
   public ITaperedGirderSegment,
   public IItemData,
   public IStructuredStorage2
{
   friend CTaperedGirderSegment; // for easy cloning
public:
   CTaperedGirderSegment()
	{
      m_bUpdateVolumeAndSurfaceArea = true;
      m_Volume = -1;
      m_SurfaceArea = -1;
   }

   HRESULT FinalConstruct();
   void FinalRelease();


DECLARE_REGISTRY_RESOURCEID(IDR_TAPEREDGIRDERSEGMENT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CTaperedGirderSegment)
	COM_INTERFACE_ENTRY(ITaperedGirderSegment)
	COM_INTERFACE_ENTRY(ISegment)
   COM_INTERFACE_ENTRY(ISuperstructureMemberSegment)
	COM_INTERFACE_ENTRY(IItemData)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

private:
   CSuperstructureMemberSegmentImpl m_Impl;

   bool m_bUpdateVolumeAndSurfaceArea;
   Float64 m_Volume;
   Float64 m_SurfaceArea;

   struct ShapeData
   {
      CComPtr<IShape> Shape;
      CComPtr<IMaterial> FGMaterial;
      CComPtr<IMaterial> BGMaterial;
   };
   std::array<std::vector<ShapeData>,2> m_Shapes; // index is EndType

   struct compare
   {
      bool operator()(const Float64& a, const Float64&b)const { return ::IsLT(a, b); }
   };
   std::map<Float64, CComPtr<IShape>, compare> m_ShapeCache;

   CItemDataManager m_ItemDataMgr;

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// ISuperstructureMemberSegment
public:
   STDMETHOD(putref_SuperstructureMember)(ISuperstructureMember* ssMbr) override {return m_Impl.putref_SuperstructureMember(ssMbr);}
   STDMETHOD(get_SuperstructureMember)(ISuperstructureMember** ssMbr) override {return m_Impl.get_SuperstructureMember(ssMbr);}
   STDMETHOD(putref_GirderLine)(IGirderLine* girderLine) override {return m_Impl.putref_GirderLine(girderLine);}
   STDMETHOD(get_GirderLine)(IGirderLine** girderLine) override {return m_Impl.get_GirderLine(girderLine);}
   STDMETHOD(putref_PrevSegment)(ISegment* segment) override {return m_Impl.putref_PrevSegment(segment); }
   STDMETHOD(get_PrevSegment)(ISegment** segment) override { return m_Impl.get_PrevSegment(segment);}
   STDMETHOD(putref_NextSegment)(ISegment* segment) override {return m_Impl.putref_NextSegment(segment);}
   STDMETHOD(get_NextSegment)(ISegment** segment) override {return m_Impl.get_NextSegment(segment);}
   STDMETHOD(get_Section)(StageIndexType stageIdx,Float64 Xs, SectionBias sectionBias, SectionCoordinateSystemType coordinateSystem,ISection** ppSection) override;
   STDMETHOD(get_PrimaryShape)(Float64 Xs, SectionBias sectionBias, SectionCoordinateSystemType coordinateSystem, IShape** ppShape) override;
   STDMETHOD(GetVolumeAndSurfaceArea)(Float64* pVolume, Float64* pSurfaceArea) override;
   STDMETHOD(get_InternalSurfaceAreaOfVoids)(Float64* pSurfaceArea) override;
   STDMETHOD(get_Profile)(VARIANT_BOOL bIncludeClosure,IShape** ppShape) override;
   STDMETHOD(get_Length)(/*[out, retval]*/ Float64 *pVal) override {return m_Impl.get_Length(pVal);}
   STDMETHOD(get_LayoutLength)(/*[out, retval]*/ Float64 *pVal) override {return m_Impl.get_LayoutLength(pVal);}
   STDMETHOD(put_Orientation)(/*[in]*/Float64 orientation) override {return m_Impl.put_Orientation(orientation); }
   STDMETHOD(get_Orientation)(/*[out,retval]*/Float64* orientation) override {return m_Impl.get_Orientation(orientation);}
   STDMETHOD(GetHaunchDepth)(Float64* pStartVal,Float64* pMidVal,Float64* pEndVal) override {return m_Impl.GetHaunchDepth(pStartVal,pMidVal,pEndVal);}
   STDMETHOD(SetHaunchDepth)(Float64 startVal,Float64 midVal,Float64 endVal) override {return m_Impl.SetHaunchDepth(startVal,midVal,endVal);}
   STDMETHOD(ComputeHaunchDepth)(Float64 distAlongSegment,Float64* pVal) override {return m_Impl.ComputeHaunchDepth(distAlongSegment,pVal);}
   STDMETHOD(put_Fillet)(/*[in]*/Float64 Fillet) override {return m_Impl.put_Fillet(Fillet);}
   STDMETHOD(get_Fillet)(/*[out,retval]*/Float64* Fillet) override {return m_Impl.get_Fillet(Fillet);}
   STDMETHOD(put_FilletShape)(/*[in]*/FilletShape FilletShape) override { return m_Impl.put_FilletShape(FilletShape); }
   STDMETHOD(get_FilletShape)(/*[out,retval]*/FilletShape* FilletShape) override { return m_Impl.get_FilletShape(FilletShape); }
   STDMETHOD(put_Precamber)(/*[in]*/Float64 precamber) override {return m_Impl.put_Precamber(precamber);}
   STDMETHOD(get_Precamber)(/*[out,retval]*/Float64* pPrecamber) override {return m_Impl.get_Precamber(pPrecamber);}
   STDMETHOD(ComputePrecamber)(/*[in]*/Float64 distAlongSegment, /*[out,retval]*/Float64* pPrecamber) override {return m_Impl.ComputePrecamber(distAlongSegment,pPrecamber);}

// ITaperedGirderSegment
public:
	STDMETHOD(AddShape)(IShape* pStartShape,IShape* pEndShape,IMaterial* pFGMaterial,IMaterial* pBGMaterial) override;
   STDMETHOD(get_ShapeCount)(IndexType* nShapes) override;
   STDMETHOD(get_ForegroundMaterial)(IndexType index,IMaterial* *material) override;
   STDMETHOD(get_BackgroundMaterial)(IndexType index,IMaterial* *material) override;

// IItemData
public:
   STDMETHOD(AddItemData)(/*[in]*/BSTR name,/*[in]*/IUnknown* data) override;
   STDMETHOD(GetItemData)(/*[in]*/BSTR name,/*[out,retval]*/IUnknown** data) override;
   STDMETHOD(RemoveItemData)(/*[in]*/BSTR name) override;
   STDMETHOD(GetItemDataCount)(/*[out,retval]*/CollectionIndexType* count) override;

// IStructuredStorage2
public:
	STDMETHOD(Load)(/*[in]*/ IStructuredLoad2* load) override;
	STDMETHOD(Save)(/*[in]*/ IStructuredSave2* save) override;
};

