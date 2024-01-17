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

// Pier.h : Declaration of the CPier

#pragma once
#include "resource.h"       // main symbols

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif



// CPier

class ATL_NO_VTABLE CPierLine :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPierLine, &CLSID_PierLine>,
	public IPierLine
{
public:
	CPierLine()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_PIERLINE)

DECLARE_NOT_AGGREGATABLE(CPierLine)

BEGIN_COM_MAP(CPierLine)
	COM_INTERFACE_ENTRY(IPierLine)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
      return S_OK;
	}

	void FinalRelease()
	{
	}

   void SetPierLine(std::shared_ptr<WBFL::COGO::PierLine> pierLine) { m_PierLine = pierLine; }
   std::shared_ptr<WBFL::COGO::PierLine> GetPierLine(){ return m_PierLine; }

public:
   STDMETHOD(get_AlignmentID)(IDType* ID) override;
   STDMETHOD(get_Station)(IStation** pVal) override;
   STDMETHOD(get_Direction)(IDirection** pVal) override;
   STDMETHOD(get_Normal)(IDirection** pVal) override;
   STDMETHOD(get_Skew)(IAngle** pVal) override;
   STDMETHOD(get_ID)(IDType* pVal) override;
   STDMETHOD(get_Index)(IndexType* pVal) override;

   STDMETHOD(get_BearingOffset)(PierFaceType pierFace, Float64* brgOffset) override;
   STDMETHOD(put_BearingOffset)(PierFaceType pierFace, Float64 brgOffset) override;
   STDMETHOD(get_BearingOffsetMeasurementType)(PierFaceType pierFace, MeasurementType* measure) override;
   STDMETHOD(put_BearingOffsetMeasurementType)(PierFaceType pierFace, MeasurementType measure) override;
   STDMETHOD(get_EndDistance)(PierFaceType pierFace, Float64* endDist) override;
   STDMETHOD(put_EndDistance)(PierFaceType pierFace, Float64 endDist) override;
   STDMETHOD(get_EndDistanceMeasurementType)(PierFaceType pierFace, MeasurementType* measure) override;
   STDMETHOD(put_EndDistanceMeasurementType)(PierFaceType pierFace, MeasurementType measure) override;
   STDMETHOD(get_EndDistanceMeasurementLocation)(PierFaceType pierFace, MeasurementLocation* measure) override;
   STDMETHOD(put_EndDistanceMeasurementLocation)(PierFaceType pierFace, MeasurementLocation measure) override;

   STDMETHOD(get_AlignmentPoint)(IPoint2d** pPoint) override;
   STDMETHOD(get_BridgePoint)(IPoint2d** ppPoint) override;
   STDMETHOD(get_LeftPoint)(IPoint2d** ppPoint) override;
   STDMETHOD(get_RightPoint)(IPoint2d** ppPoint) override;
   STDMETHOD(get_Centerline)(ILine2d** ppLine) override;
   STDMETHOD(GetBearingOffset)(PierFaceType pierFace,IDirection* direction,Float64* brgOffset) override;

private:
   std::shared_ptr<WBFL::COGO::PierLine> m_PierLine;
};
