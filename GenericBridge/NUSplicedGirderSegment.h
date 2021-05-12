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

// NUSplicedGirderSegment.h : Declaration of the CNUSplicedGirderSegment

#pragma once

#include "resource.h"       // main symbols
#include "SplicedGirderSegmentImpl.h"

/////////////////////////////////////////////////////////////////////////////
// CNUSplicedGirderSegment
class ATL_NO_VTABLE CNUSplicedGirderSegment : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CSegment,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CNUSplicedGirderSegment, &CLSID_NUSplicedGirderSegment>,
   public ISplicedGirderSegmentImpl<CNUSplicedGirderSegment,INUGirderSection>,
   public IObjectSafetyImpl<CNUSplicedGirderSegment,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>
{
public:
   CNUSplicedGirderSegment()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();


DECLARE_REGISTRY_RESOURCEID(IDR_NUSPLICEDGIRDERSEGMENT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CNUSplicedGirderSegment)
	COM_INTERFACE_ENTRY(ISplicedGirderSegment)
   COM_INTERFACE_ENTRY(ISuperstructureMemberSegment)
	COM_INTERFACE_ENTRY(ISegment)
   COM_INTERFACE_ENTRY(IObjectSafety)
	COM_INTERFACE_ENTRY(IItemData)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

protected:
   virtual HRESULT GetPrimaryShape(Float64 Xs, SectionBias sectionBias, SectionCoordinateSystemType coordinateSystem, IShape** ppShape) override;
   void GetEndBlockWidth(Float64 Xs, SectionBias sectionBias,Float64* pWendBlock);
};

