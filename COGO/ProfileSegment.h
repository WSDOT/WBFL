///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
// Copyright © 1999-2024  Washington State Department of Transportation
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

// ProfileElement.h : Declaration of the CProfileElement

#pragma once

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CProfileSegment
class ATL_NO_VTABLE CProfileSegment : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CProfileSegment, &CLSID_ProfileSegment>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CProfileSegment,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
   public IProfileSegment,
   public IProfileElement
{
public:
	CProfileSegment()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

   void SetProfileSegment(std::shared_ptr<WBFL::COGO::ProfileSegment> segment) { m_Segment = segment; }
   std::shared_ptr<WBFL::COGO::ProfileSegment> GetProfileSegment() { return m_Segment; }

DECLARE_REGISTRY_RESOURCEID(IDR_PROFILESEGMENT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CProfileSegment)
	COM_INTERFACE_ENTRY(IProfileSegment)
   COM_INTERFACE_ENTRY(IProfileElement)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IProfileSegment
public:
   STDMETHOD(SetStartPoint)(IProfilePoint* pStart) override;
   STDMETHOD(SetEndPoint)(IProfilePoint* pEnd) override;
   STDMETHOD(Move)(IProfilePoint* pStart, IProfilePoint* pEnd) override;
   STDMETHOD(Location)(IProfilePoint** ppStart, IProfilePoint** ppEnd) override;

// IProfileElement
   //STDMETHOD(Clone)(IProfileElement** clone) override;
   STDMETHOD(get_Profile)(IProfile** pVal) override;
   STDMETHOD(put_Profile)(IProfile* newVal) override;
   STDMETHOD(GetStartPoint)(IProfilePoint** ppPoint) override;
   STDMETHOD(GetEndPoint)(IProfilePoint** ppPoint) override;
   STDMETHOD(GetLength)(Float64* pLength) override;
   STDMETHOD(ComputeGradeAndElevation)(VARIANT varStation, Float64* pGrade, Float64* pElevation) override;

private:
   std::shared_ptr<WBFL::COGO::ProfileSegment> m_Segment; // implementation object
   IProfile* m_pProfile; // weak pointer to actual COM object parent
};
