///////////////////////////////////////////////////////////////////////
// BridgeGeometry
// Copyright © 1999-2023  Washington State Department of Transportation
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

#include "WBFLBridgeGeometry.h"


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
      m_pBridge   = 0;
      m_pPrevPier = 0;
      m_pNextPier = 0;

      m_Station.CoCreateInstance(CLSID_Station);
      m_AlignmentID = INVALID_INDEX;

      m_BearingOffset[pfBack]              = 0;
      m_BearingOffsetMeasure[pfBack]       = mtNormal;

      m_EndDistance[pfBack]                = 0;
      m_EndDistanceMeasure[pfBack]         = mtNormal;
      m_EndDistanceMeasureLocation[pfBack] = mlPierLine;


      m_BearingOffset[pfAhead]              = 0;
      m_BearingOffsetMeasure[pfAhead]       = mtNormal;

      m_EndDistance[pfAhead]                = 0;
      m_EndDistanceMeasure[pfAhead]         = mtNormal;
      m_EndDistanceMeasureLocation[pfAhead] = mlPierLine;

      m_Width = 0;

      return S_OK;
	}

	void FinalRelease()
	{
	}

   IBridgeGeometry* m_pBridge; // weak reference
   CogoObjectID m_AlignmentID; // ID of alignment this pier is located on
   CComPtr<IStation> m_Station;
   CComBSTR m_bstrOrientation;

   CComPtr<IDirection> m_Direction; // direction of the pier
   CComPtr<IDirection> m_Normal; // direction of normal to the pier, pointing ahead on station
   CComPtr<IAngle> m_Skew;  // skew angle relative to the alignment
   PierIndexType m_Index; // pier index (first pier in the bridge starts with 0)
   PierIDType m_ID; // use defined pier ID
   IPierLine* m_pPrevPier; // pointer to previous pier in bridge (weak reference)
   IPierLine* m_pNextPier; // pointer to next pier in bridge (weak reference)

   CComPtr<IPoint2d> m_pntAlignment; // CL-Pier/Alignment intersection point
   CComPtr<IPoint2d> m_pntBridge; // CL-Pier/Bridge Line intersection point
   CComPtr<IPoint2d> m_pntLeft; // point at left edge of pier
   CComPtr<IPoint2d> m_pntRight; // point at right edge of pier
   CComPtr<ILine2d> m_Centerline; // CL of pier

   Float64 m_BearingOffset[2];
   MeasurementType m_BearingOffsetMeasure[2];

   Float64 m_EndDistance[2];
   MeasurementType m_EndDistanceMeasure[2];
   MeasurementLocation m_EndDistanceMeasureLocation[2];

   Float64 m_Width; // transverse width of the pier, measure along the CL pier
   Float64 m_Offset; // offset of the left edge of the pier from alignment, measured along the CL pier

   HRESULT UpdateGeometry();

public:
   STDMETHOD(get_AlignmentID)(CogoObjectID* ID) override;
   STDMETHOD(get_Station)(IStation** pVal) override;
   STDMETHOD(get_Direction)(IDirection** pVal) override;
   STDMETHOD(get_Normal)(IDirection** pVal) override;
   STDMETHOD(get_Skew)(IAngle** pVal) override;
   STDMETHOD(get_Index)(PierIndexType* pVal) override;
   STDMETHOD(get_ID)(PierIDType* pVal) override;
   STDMETHOD(get_NextPierLine)(IPierLine** pVal) override;
   STDMETHOD(get_PrevPierLine)(IPierLine** pVal) override;

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
};

OBJECT_ENTRY_NON_CREATEABLE_EX_AUTO(__uuidof(PierLine), CPierLine)
