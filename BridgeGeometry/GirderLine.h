///////////////////////////////////////////////////////////////////////
// BridgeGeometry
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

// GirderLine.h : Declaration of the CGirderLine

#pragma once
#include "resource.h"       // main symbols

#include "WBFLBridgeGeometry.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif



// CGirderLine

class ATL_NO_VTABLE CGirderLine :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CGirderLine, &CLSID_GirderLine>,
	public IGirderLine
{
public:
	CGirderLine()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_GIRDERLINE)

DECLARE_NOT_AGGREGATABLE(CGirderLine)

BEGIN_COM_MAP(CGirderLine)
	COM_INTERFACE_ENTRY(IGirderLine)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
      m_ID           = INVALID_INDEX;
      m_LayoutLineID = INVALID_INDEX;
      m_StartPierID  = INVALID_INDEX;
      m_EndPierID    = INVALID_INDEX;
      m_Type         = glChord;
      m_MeasureType[etStart]  = mtAlongItem;
      m_MeasureLocation[etStart] = mlPierLine;
      m_MeasureType[etEnd]  = mtAlongItem;
      m_MeasureLocation[etEnd] = mlPierLine;

      m_LayoutLength     = -9999999999999; // obviously a bogus value
      m_GirderLength     = -9999999999999; // obviously a bogus value
      m_SpanLength       = -9999999999999; // obviously a bogus value
      m_BearingOffset[etStart] = -9999999999999; // obviously a bogus value
      m_BearingOffset[etEnd] = -9999999999999; // obviously a bogus value
      m_EndDistance[etStart]   = -9999999999999; // obviously a bogus value
      m_EndDistance[etEnd]   = -9999999999999; // obviously a bogus value
		return S_OK;
	}

	void FinalRelease()
	{
	}

   GirderIDType m_ID;
   LineIDType m_LayoutLineID;
   PierIDType m_StartPierID;
   PierIDType m_EndPierID;
   GirderLineType m_Type;
   MeasurementType m_MeasureType[2];
   MeasurementLocation m_MeasureLocation[2];

   IBridgeGeometry* m_pBridge;
   CComPtr<IPierLine> m_StartPierLine;
   CComPtr<IPierLine> m_EndPierLine;
   CComPtr<IPath> m_Path;
   CComPtr<IPoint2d> m_PierPoint[2];    // intersection of girder line and CL pier (index is EndType constant)
   CComPtr<IPoint2d> m_BearingPoint[2]; // intersection with CL bearing
   CComPtr<IPoint2d> m_EndPoint[2];     // end of girder
   Float64 m_LayoutLength; // pier to pier length
   Float64 m_SpanLength; // cl-brg to cl-brg length
   Float64 m_GirderLength; // end to end length
   Float64 m_BearingOffset[2]; // distance from cl-pier to cl-bearing along cl-girder
   Float64 m_EndDistance[2]; // distance from cl-bearing to end of girder along cl-girder
   CComPtr<IDirection> m_Direction;

   HRESULT UpdateGeometry();
   HRESULT CreatePath();
   HRESULT LocatePoints();

   HRESULT GetGirderSpacingLine(EndType endType,IPierLine* pPierLine,ILine2d** ppLine);

public:
   STDMETHOD(get_BearingOffset)(EndType endType,Float64* pBrgOffset);
   STDMETHOD(get_EndDistance)(EndType endType,Float64* pEndDistance);
   STDMETHOD(get_Direction)(IDirection** ppDirection);
   STDMETHOD(get_Path)(IPath** pVal);
   STDMETHOD(GetEndPoints)(IPoint2d** pntPier1,IPoint2d** pntEnd1,IPoint2d** pntBrg1,IPoint2d** pntBrg2,IPoint2d** pntEnd2,IPoint2d** pntPier2);
   STDMETHOD(get_EndPoint)(EndType endType,IPoint2d** ppPoint);
   STDMETHOD(get_PierPoint)(EndType endType,IPoint2d** ppPoint);
   STDMETHOD(get_BearingPoint)(EndType endType,IPoint2d** ppPoint);
   STDMETHOD(get_GirderLength)(Float64* pLength);
   STDMETHOD(get_SpanLength)(Float64* pLength);
   STDMETHOD(get_LayoutLength)(Float64* pLength);
   STDMETHOD(get_StartPier)(IPierLine** pVal);
   STDMETHOD(get_EndPier)(IPierLine** pVal);
   STDMETHOD(get_ID)(GirderIDType* pVal);
};

OBJECT_ENTRY_NON_CREATEABLE_EX_AUTO(__uuidof(GirderLine), CGirderLine)
