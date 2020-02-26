///////////////////////////////////////////////////////////////////////
// BridgeGeometry
// Copyright © 1999-2020  Washington State Department of Transportation
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

// DeckBoundary.h : Declaration of the CDeckBoundary

#pragma once
#include "resource.h"       // main symbols

#include "WBFLBridgeGeometry.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif



// CDeckBoundary

class ATL_NO_VTABLE CDeckBoundary :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CDeckBoundary, &CLSID_DeckBoundary>,
	public IDeckBoundary
{
public:
	CDeckBoundary()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_DECKBOUNDARY)

DECLARE_NOT_AGGREGATABLE(CDeckBoundary)

BEGIN_COM_MAP(CDeckBoundary)
	COM_INTERFACE_ENTRY(IDeckBoundary)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
      m_pBridge   = 0;

      m_TransverseEdgeID[etStart]   = INVALID_INDEX;
      m_TransverseEdgeType[etStart] = setLayout;

      m_TransverseEdgeID[etEnd]   = INVALID_INDEX;
      m_TransverseEdgeType[etEnd] = setLayout;

      m_EdgeID[etStart]       = INVALID_INDEX;
      m_EdgeBreakID[etStart]  = INVALID_INDEX;
      m_EdgeID[etEnd]         = INVALID_INDEX;
      m_EdgeBreakID[etEnd]    = INVALID_INDEX;

      m_vbBreakEdge[etStart][stLeft] = VARIANT_FALSE;
      m_vbBreakEdge[etEnd][stLeft]   = VARIANT_FALSE;
      
      m_vbBreakEdge[etStart][stRight] = VARIANT_FALSE;
      m_vbBreakEdge[etEnd][stRight]   = VARIANT_FALSE;

      return S_OK;
	}

	void FinalRelease()
	{
	}

   IBridgeGeometry* m_pBridge; // weak reference to the bridge

   // Use the EndType enum to access these arrays
   LineIDType m_TransverseEdgeID[2]; // ID of the path that defines the transverse edge of the deck
   DeckBoundaryEdgeType m_TransverseEdgeType[2]; // Type of line that defines the transverse edge of deck

   // Use the SideType enum to access these arrays
   PathIDType m_EdgeID[2];       // ID of construction line that defines the edge of deck
   PathIDType m_EdgeBreakID[2];  // ID of construction line that defines the break back points

   // Boolean value that indicates if there is a break point 
   // in the ends of the slab.
   // use the EndType and SideType to access the array
   // e.g. m_vbBreakEdge[etStart][stLeft]
   VARIANT_BOOL m_vbBreakEdge[2][2];

   // Coordinates that define the ends of the slab. 
   // Use the EndType and SideType to access the array
   // e.g. m_EdgePoint[etStart][stLeft]
   CComPtr<IPoint2d> m_EdgePoint[2][2];        // intersection of slab edge with the slab path
   CComPtr<IPoint2d> m_EdgeBreakPoint[2][2];   // location of break back point

   CComPtr<IPath> m_EdgePath[2];  // path that defined the edge of the deck. Use the SideType enum to access the array

   HRESULT UpdateGeometry();
   HRESULT CreateDeckBoundaryEndPoints(EndType endType,LineIDType endLineID,DeckBoundaryEdgeType edgeType,IPoint2d** end1,IPoint2d** end2,IPoint2d** end3,IPoint2d** end4);
   HRESULT CreateEdgePath(PathIDType edgePathID, IPoint2d* pntStart, IPoint2d* pntEnd,IPath** pPath);

public:
   STDMETHOD(get_Perimeter)(CollectionIndexType nMinPointsPerSide,IPoint2dCollection** points) override;
   STDMETHOD(get_PerimeterEx)(CollectionIndexType nMinPointsPerSide,PierIDType startPierID,Float64 Xstart,PierIDType endPierID,Float64 Xend, VARIANT_BOOL bParallelToPiers, IPoint2dCollection** points) override;
   STDMETHOD(get_TransverseEdgePoints)(EndType endType,IPoint2d** ppLeft,IPoint2d** ppLeftBreak,IPoint2d** ppRightBreak,IPoint2d** ppRight) override;
   STDMETHOD(get_EdgePath)(SideType side,VARIANT_BOOL vbLayoutLine,IPath** path) override;
};

OBJECT_ENTRY_NON_CREATEABLE_EX_AUTO(__uuidof(DeckBoundary), CDeckBoundary)
