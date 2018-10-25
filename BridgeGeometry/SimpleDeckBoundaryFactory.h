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

// SimpleDeckBoundaryFactory.h : Declaration of the CSimpleDeckBoundaryFactory

#pragma once
#include "resource.h"       // main symbols

#include "WBFLBridgeGeometry.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif



// CSimpleDeckBoundaryFactory
//
// Creates a bridge DeckBoundary using previously defined layout lines. Ths DeckBoundary may have break backs at
// any of the four corners.

class ATL_NO_VTABLE CSimpleDeckBoundaryFactory :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSimpleDeckBoundaryFactory, &CLSID_SimpleDeckBoundaryFactory>,
	public ISimpleDeckBoundaryFactory
{
public:
	CSimpleDeckBoundaryFactory()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_SIMPLEDECKBOUNDARYFACTORY)

DECLARE_NOT_AGGREGATABLE(CSimpleDeckBoundaryFactory)

BEGIN_COM_MAP(CSimpleDeckBoundaryFactory)
	COM_INTERFACE_ENTRY(ISimpleDeckBoundaryFactory)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return Reset();
	}

	void FinalRelease()
	{
	}

   // Use the EndType enum to access these arrays
   PathIDType m_TransverseEdgeID[2]; // ID of the path that defines the transverse edge of the deck
   DeckBoundaryEdgeType m_TransverseEdgeType[2]; // Type of line that defines the transverse edge of deck

   // Use the SideType enum to access these arrays
   PathIDType m_EdgeID[2];       // ID of construction line that defines the edge of deck
   PathIDType m_EdgeBreakID[2];  // ID of construction line that defines the break back points

   // Boolean value that indicates if there is a break point 
   // in the ends of the slab.
   // use the EndType and SideType to access the array
   // e.g. m_vbBreakEdge[etStart][stLeft]
   VARIANT_BOOL m_vbBreakEdge[2][2];

public:
   STDMETHOD(put_TransverseEdgeID)(EndType end,LineIDType ID) override;
   STDMETHOD(get_TransverseEdgeID)(EndType end,LineIDType* ID) override;
   STDMETHOD(put_TransverseEdgeType)(EndType end,DeckBoundaryEdgeType edgeType) override;
   STDMETHOD(get_TransverseEdgeType)(EndType end,DeckBoundaryEdgeType* edgeType) override;
   STDMETHOD(put_EdgeID)(SideType side,PathIDType ID) override;
   STDMETHOD(get_EdgeID)(SideType side,PathIDType* ID) override;
   STDMETHOD(put_EdgeBreakID)(SideType side,LineIDType ID) override;
   STDMETHOD(get_EdgeBreakID)(SideType side,LineIDType* ID) override;
   STDMETHOD(put_BreakEdge)(EndType end,SideType side,VARIANT_BOOL bBreak) override;
   STDMETHOD(get_BreakEdge)(EndType end,SideType side,VARIANT_BOOL* bBreak) override;

   STDMETHOD(Create)(IBridgeGeometry* pBridge,IDeckBoundary** ppDeckBoundary) override;
   STDMETHOD(Reset)() override;
};

OBJECT_ENTRY_AUTO(__uuidof(SimpleDeckBoundaryFactory), CSimpleDeckBoundaryFactory)
