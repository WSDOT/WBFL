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

// DiaphragmLine.h : Declaration of the CDiaphragmLine

#pragma once
#include "resource.h"       // main symbols

#include "WBFLBridgeGeometry.h"
#include <map>

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif



// CDiaphragmLine

class ATL_NO_VTABLE CDiaphragmLine :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CDiaphragmLine, &CLSID_DiaphragmLine>,
	public IDiaphragmLine
{
public:
	CDiaphragmLine()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_DIAPHRAGMLINE)

DECLARE_NOT_AGGREGATABLE(CDiaphragmLine)

BEGIN_COM_MAP(CDiaphragmLine)
	COM_INTERFACE_ENTRY(IDiaphragmLine)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
      m_ID = INVALID_INDEX;

      m_pBridge   = 0;

      m_Line.CoCreateInstance(CLSID_Line2d);

      return S_OK;
	}

	void FinalRelease()
	{
	}

   LineIDType m_ID; // id of this diaphragm line
   GirderIDType m_LeftGirderID; // id of the girder line where this diaphragm starts
   GirderIDType m_RightGirderID;// id of the girder line where this diaphragm end
   bool m_bStaggered; // true if the diaphragm lines are staggared
   CComPtr<ILine2d> m_Line;

   IBridgeGeometry* m_pBridge;
   struct EndPoints
   {
      CComPtr<IPoint2d> pntLeft;
      CComPtr<IPoint2d> pntRight;
   };
   typedef std::map<GirderIDType,EndPoints> EndPointContainer;
   EndPointContainer m_EndPoints; // intersection of diaphragm lines between girder lines
                                                            // key is left hand girder ID
   CComPtr<IPoint2d> m_Point[2]; // intersection of diaphragm line and start and end girder line

   HRESULT UpdateGeometry();
   HRESULT LocatePoints();

public:
   STDMETHOD(get_Point)(GirderIDType gdrLineID,EndType endType,IPoint2d** ppPoint) override;
   STDMETHOD(get_Length)(GirderIDType gdrLineID,Float64* pLength) override;
   STDMETHOD(get_ID)(LineIDType* pVal) override;
};

OBJECT_ENTRY_NON_CREATEABLE_EX_AUTO(__uuidof(DiaphragmLine), CDiaphragmLine)
