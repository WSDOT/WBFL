///////////////////////////////////////////////////////////////////////
// GenericBridgeTools - Tools for manipluating the Generic Bridge Modeling
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

// RebarRowFacePattern.h : Declaration of the CRebarRowFacePattern

#ifndef __RebarRowFacePattern_H_
#define __RebarRowFacePattern_H_

#include "resource.h"       // main symbols


/////////////////////////////////////////////////////////////////////////////
// CRebarRowFacePattern
class ATL_NO_VTABLE CRebarRowFacePattern : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CRebarRowFacePattern,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CRebarRowFacePattern, &CLSID_RebarRowFacePattern>,
	public ISupportErrorInfo,
	public IRebarRowFacePattern,
   public IStructuredStorage2,
   public IObjectSafetyImpl<CRebarRowFacePattern,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>
{
public:
   CRebarRowFacePattern()
	{
      m_pRebarLayoutItem = nullptr;
      m_pSegment = nullptr;
      m_HookType[qcbLeft] = htNone;
      m_HookType[qcbRight] = htNone;
   }

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_REBARROWFACEPATTERN)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CRebarRowFacePattern)
	COM_INTERFACE_ENTRY(IRebarRowFacePattern)
	COM_INTERFACE_ENTRY(IRebarPattern)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

private:
   CComPtr<IRebar> m_Rebar;
   CollectionIndexType m_Count;
   Float64 m_Offset;
   FaceType m_Face;
   Float64 m_Spacing;
   RebarRowOrientation m_Orientation;

   HookType m_HookType[2];

   IRebarLayoutItem* m_pRebarLayoutItem; // weak reference
   ISegment* m_pSegment; // weak reference

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IRebarPattern
public:
	STDMETHOD(putref_Rebar)(/*[in]*/IRebar* rebar) override;
	STDMETHOD(get_Rebar)(/*[out,retval]*/IRebar** rebar) override;
   STDMETHOD(putref_RebarLayoutItem)(/*[in]*/IRebarLayoutItem* rebarLayoutItem) override;
   STDMETHOD(put_Hook)(/*[in]*/DirectionType side,/*[in]*/HookType hook) override;
   STDMETHOD(get_Hook)(/*[in]*/DirectionType side,/*[out,retval]*/HookType* hook) override;
	STDMETHOD(get_Count)(/*[out,retval]*/CollectionIndexType* count) override;
	STDMETHOD(get_Location)(/*[in]*/Float64 distFromStartOfPattern,/*[in]*/CollectionIndexType barIdx,/*[out,retval]*/IPoint2d** location) override;
   STDMETHOD(get_Profile)(/*[in]*/IndexType barIdx,/*[out,retval]*/IPoint2dCollection** ppProfile) override;

// IRebarRowFacePattern
public:
   STDMETHOD(putref_Segment)(/*[in]*/ISegment* pSegment) override;
   STDMETHOD(get_Segment)(/*[out,retval]*/ISegment** pSegment) override;
   STDMETHOD(put_Face)(/*[in]*/FaceType faceType) override;
   STDMETHOD(get_Face)(/*[out,retval]*/FaceType* faceType) override;
   STDMETHOD(put_Offset)(/*[in]*/Float64 offset) override;
   STDMETHOD(get_Offset)(/*[out,retval]*/Float64* offset) override;
	STDMETHOD(put_Count)(/*[in]*/RowIndexType count) override;
	STDMETHOD(put_Spacing)(/*[in]*/Float64 spacing) override;
	STDMETHOD(get_Spacing)(/*[out,retval]*/Float64* spacing) override;
	STDMETHOD(put_Orientation)(/*[in]*/RebarRowOrientation orientation) override;
	STDMETHOD(get_Orientation)(/*[out,retval]*/RebarRowOrientation* orientation) override;

// IStructuredStorage2
public:
	STDMETHOD(Load)(/*[in]*/ IStructuredLoad2* load) override;
	STDMETHOD(Save)(/*[in]*/ IStructuredSave2* save) override;
};

#endif //__RebarRowFacePattern_H_
