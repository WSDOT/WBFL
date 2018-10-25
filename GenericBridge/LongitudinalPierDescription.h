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

// LongitudinalPierDescription.h : Declaration of the CLongitudinalPierDescription

#ifndef __LONGITUDINALPIERDESCRIPTION_H_
#define __LONGITUDINALPIERDESCRIPTION_H_

#include "resource.h"       // main symbols
#include "Segments.h"

/////////////////////////////////////////////////////////////////////////////
// CLongitudinalPierDescription
class ATL_NO_VTABLE CLongitudinalPierDescription : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLongitudinalPierDescription, &CLSID_LongitudinalPierDescription>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CLongitudinalPierDescription,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
   public ILongitudinalPierDescription,
   public IStructuredStorage2,
   public CSegmentsOwner
{
public:
   friend CLongitudinalPierDescription; // Friend of self for easy cloning

	CLongitudinalPierDescription()
	{
      m_Connectivity = ctPinned;
      m_Height = 1.0;
      m_BaseOffset = 0.0;
      //m_ContinuityStageIdx = INVALID_INDEX;
      m_bFractional = VARIANT_FALSE;
      m_bSymmetrical = VARIANT_FALSE;

      m_pPier = NULL;
	}
 
   HRESULT FinalConstruct();
   void FinalRelease();

   void SetPier(IPier* pier)
   {
      m_pPier = pier;
   }

   void SetBridge(IGenericBridge* pBridge)
   {
      m_pBridge = pBridge;
      m_pSegments->SetBridge(pBridge);
   }

   CSegments* GetSegments() { return m_pSegments; }

#if defined _DEBUG
   void AssertValid() const;
#endif // _DEBUG

DECLARE_REGISTRY_RESOURCEID(IDR_LONGITUDINALPIERDESCRIPTION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLongitudinalPierDescription)
   COM_INTERFACE_ENTRY(ILongitudinalPierDescription)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
END_COM_MAP()

private:
   ConnectivityType m_Connectivity;
   Float64 m_Height;
   Float64 m_BaseOffset;
   //StageIndexType m_ContinuityStageIdx;
   VARIANT_BOOL m_bFractional;
   VARIANT_BOOL m_bSymmetrical;
   IPier* m_pPier; // This is a weak reference to avoid a circular reference
   IGenericBridge* m_pBridge; // This is a weak referenece to avoid a circular referece

   CSegments* m_pSegments;

public:

// virtual methods for CSegmentsOwner
   virtual Float64 Length();


// ISupportsErrorInfo
public:
   STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ISegmentMeasure
public:
   STDMETHOD(IsFractional)();

// ILongitudinalPierDescription
public:
   STDMETHOD(get_Pier)(/*[out,retval]*/IPier* *pier);
   STDMETHOD(get_Fractional)(/*[out,retval]*/ VARIANT_BOOL* bFractional);
	STDMETHOD(get_Symmetrical)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_Symmetrical)(/*[in]*/ VARIANT_BOOL newVal);
   STDMETHOD(put_Fractional)(/*[in]*/ VARIANT_BOOL bFractional);
	STDMETHOD(get_Connectivity)(/*[out, retval]*/ ConnectivityType *pVal);
	STDMETHOD(put_Connectivity)(/*[in]*/ ConnectivityType newVal);
   STDMETHOD(get_Height)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_Height)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_BaseOffset)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_BaseOffset)(/*[in]*/ Float64 newVal);
   STDMETHOD(get_Length)(/*[out,retval]*/ Float64* value);
   //STDMETHOD(get_ContinuityStage)(/*[out,retval]*/ StageIndexType* pStageIdx);
   //STDMETHOD(put_ContinuityStage)(/*[in]*/ StageIndexType stageIdx);

   STDMETHOD(AddSegment)(/*[in]*/ISegment* segment);
   STDMETHOD(InsertSegment)(/*[in]*/ CollectionIndexType idx,/*[in]*/ISegment* segment);
	STDMETHOD(MoveSegmentTo)(/*[in]*/ CollectionIndexType fromIdx,/*[in]*/ CollectionIndexType toIdx);
	STDMETHOD(CopySegmentTo)(/*[in]*/ CollectionIndexType fromIdx, /*[in]*/ CollectionIndexType toIdx);
	STDMETHOD(RemoveSegment)(/*[in]*/ CollectionIndexType idx);
	STDMETHOD(RemoveSegments)();
	STDMETHOD(GetMemberSegments)(/*[out,retval]*/ IFilteredSegmentCollection **ppSeg);
	STDMETHOD(GetDistanceFromStartOfSegment)(/*[in]*/ Float64 Location,/*[out]*/Float64* dist,/*[out]*/ ISegmentItem **ppSeg);
	STDMETHOD(ReverseSegments)();
   STDMETHOD(get_SegmentCount)(/*[out,retval]*/ CollectionIndexType* count);
   STDMETHOD(get_SegmentLength)(/*[out,retval]*/ Float64* value);
   STDMETHOD(get_Segment)(/*[in]*/ CollectionIndexType idx,/*[out,retval]*/ ISegment* *segment);

// IStructuredStorage2
public:
	STDMETHOD(Load)(/*[in]*/ IStructuredLoad2* load);
	STDMETHOD(Save)(/*[in]*/ IStructuredSave2* save);
};

#endif //__LONGITUDINALPIERDESCRIPTION_H_
