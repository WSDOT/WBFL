///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright © 1999-2017  Washington State Department of Transportation
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

// BearingLayout : Declaration of the CBearingLayout

#ifndef __BearingLayout_H_
#define __BearingLayout_H_

#include "resource.h"       // main symbols
#include <MathEx.h>
#include <vector>

typedef struct BearingLineData
{
   BearingLineData() { m_BrgLineOffset = 0; m_RefBrgIdx = 0; m_RefBrgOffset = 0; }

   bool operator==(const struct BearingLineData& other) const
   {
      return (m_RefBrgIdx == other.m_RefBrgIdx && IsEqual(m_RefBrgOffset,other.m_RefBrgOffset) && m_Spacing == other.m_Spacing);
   }

   Float64 m_BrgLineOffset; // offset from the CL of pier to the bearing line
   // Offsets to the back side of the pier are < 0.

   IndexType m_RefBrgIdx; // index of the reference bearing
   Float64 m_RefBrgOffset; // offset of the reference bearing from the alignment
   std::vector<Float64> m_Spacing; // one item for each space between bearings
} BearingLineData;

/////////////////////////////////////////////////////////////////////////////
// CBearingLayout
class ATL_NO_VTABLE CBearingLayout : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CBearingLayout, &CLSID_BearingLayout>,
	public ISupportErrorInfo,
	public IBearingLayout,
   public IStructuredStorage2,
   public IObjectSafetyImpl<CBearingLayout,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>
{
public:
	CBearingLayout()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

   void RenumberBearings();

DECLARE_REGISTRY_RESOURCEID(IDR_BEARINGLAYOUT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CBearingLayout)
	COM_INTERFACE_ENTRY(IBearingLayout)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(IObjectSafety)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

private:
   IPier* m_pPier; // weak reference
   std::vector<BearingLineData> m_BearingLines;

   // Returns the number of bearings as defined by the spacing object
   IndexType GetNumBearings(IndexType brgLineIdx) const;
   Float64 GetLeftBearingOffset(IndexType brgLineIdx);

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IBearingLayout
public:
   STDMETHOD(putref_Pier)(/*[in]*/IPier* pPier) override;
   STDMETHOD(get_Pier)(/*[out,retval]*/IPier** ppPier) override;
   STDMETHOD(get_BearingLineCount)(/*[out,retval]*/IndexType* pnBearingLines) override;
   STDMETHOD(put_BearingLineCount)(/*[in]*/IndexType nBearingLines) override;
   STDMETHOD(get_BearingLineOffset)(/*[in]*/IndexType brgLineIdx,/*[out,retval]*/Float64* pOffset) override;
   STDMETHOD(put_BearingLineOffset)(/*[in]*/IndexType brgLineIdx,/*[in]*/Float64 offset) override;
   STDMETHOD(get_BearingCount)(/*[in]*/IndexType brgLineIdx,/*[out,retval]*/ IndexType* nBearings) override;
   STDMETHOD(put_BearingCount)(/*[in]*/IndexType brgLineIdx,/*[in]*/IndexType nBearings) override;
   STDMETHOD(get_Spacing)(/*[in]*/IndexType brgLineIdx,/*[in]*/ SpacingIndexType spaceIdx,/*[out,retval]*/ Float64* space) override;
   STDMETHOD(put_Spacing)(/*[in]*/IndexType brgLineIdx,/*[in]*/ SpacingIndexType spaceIdx,/*[in]*/ Float64 space) override;
   STDMETHOD(Add)(/*[in]*/IndexType brgLineIdx,/*[in]*/ IndexType nBearings) override;
   STDMETHOD(Insert)(/*[in]*/IndexType brgLineIdx,/*[in]*/ SpacingIndexType spaceIdx,/*[in]*/ SpacingIndexType nInsert) override;
   STDMETHOD(Remove)(/*[in]*/IndexType brgLineIdx,/*[in]*/ IndexType brgIdx,/*[in]*/ IndexType nRemove) override;
   STDMETHOD(SetReferenceBearing)(/*[in]*/IndexType brgLineIdx,/*[in]*/IndexType brgIdx,/*[in]*/Float64 alignmentOffset) override;
   STDMETHOD(GetReferenceBearing)(/*[in]*/IndexType brgLineIdx,/*[out]*/IndexType* pBrgIdx,/*[out]*/Float64* pAlignmentOffset) override;
   STDMETHOD(get_BearingLayoutWidth)(/*[in]*/IndexType brgLineIdx,/*[out,retval]*/Float64* pCLW) override;
   STDMETHOD(get_BearingLocation)(/*[in]*/IndexType brgLineIdx,/*[in]*/IndexType brgIdx,/*[out,retval]*/Float64* pXxb) override;
   STDMETHOD(get_BearingOffset)(/*[in]*/IndexType brgLineIdx,/*[in]*/IndexType brgIdx,/*[out,retval]*/Float64* pOffset) override;
   STDMETHOD(get_BearingElevation)(/*[in]*/IndexType brgLineIdx,/*[in]*/IndexType brgIdx,/*[out,retval]*/Float64* pElev) override;

// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave) override;
   STDMETHOD(Load)(IStructuredLoad2* pLoad) override;
};

#endif //__BearingLayout_H_
