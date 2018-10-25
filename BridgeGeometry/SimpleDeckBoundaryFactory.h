///////////////////////////////////////////////////////////////////////
// BridgeGeometry
// Copyright © 1999-2013  Washington State Department of Transportation
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
      m_BackEdgeID   = INVALID_INDEX;
      m_BackEdgeType = setLayout;

      m_ForwardEdgeID   = INVALID_INDEX;
      m_ForwardEdgeType = setLayout;

      m_LeftEdgeID       = INVALID_INDEX;
      m_RightEdgeID      = INVALID_INDEX;
      m_LeftEdgeBreakID  = INVALID_INDEX;
      m_RightEdgeBreakID = INVALID_INDEX;

      m_vbBreakLeftEdge[etStart] = VARIANT_FALSE;
      m_vbBreakLeftEdge[etEnd]   = VARIANT_FALSE;
      
      m_vbBreakRightEdge[etStart] = VARIANT_FALSE;
      m_vbBreakRightEdge[etEnd]   = VARIANT_FALSE;
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

   LineIDType m_BackEdgeID;
   DeckBoundaryEdgeType m_BackEdgeType;

   LineIDType m_ForwardEdgeID;
   DeckBoundaryEdgeType m_ForwardEdgeType;

   LineIDType m_LeftEdgeID;
   LineIDType m_RightEdgeID;
   LineIDType m_LeftEdgeBreakID;
   LineIDType m_RightEdgeBreakID;

   VARIANT_BOOL m_vbBreakLeftEdge[2];
   VARIANT_BOOL m_vbBreakRightEdge[2];

public:
   STDMETHOD(put_BackEdgeID)(LineIDType ID);
   STDMETHOD(get_BackEdgeID)(LineIDType* ID);
   STDMETHOD(put_BackEdgeType)(DeckBoundaryEdgeType edgeType);
   STDMETHOD(get_BackEdgeType)(DeckBoundaryEdgeType* edgeType);
   STDMETHOD(put_ForwardEdgeID)(LineIDType ID);
   STDMETHOD(get_ForwardEdgeID)(LineIDType* ID);
   STDMETHOD(put_ForwardEdgeType)(DeckBoundaryEdgeType edgeType);
   STDMETHOD(get_ForwardEdgeType)(DeckBoundaryEdgeType* edgeType);
   STDMETHOD(put_LeftEdgeID)(LineIDType ID);
   STDMETHOD(get_LeftEdgeID)(LineIDType* ID);
   STDMETHOD(put_RightEdgeID)(LineIDType ID);
   STDMETHOD(get_RightEdgeID)(LineIDType* ID);
   STDMETHOD(put_LeftEdgeBreakID)(LineIDType ID);
   STDMETHOD(get_LeftEdgeBreakID)(LineIDType* ID);
   STDMETHOD(put_RightEdgeBreakID)(LineIDType ID);
   STDMETHOD(get_RightEdgeBreakID)(LineIDType* ID);
   STDMETHOD(put_BreakLeftEdge)(EndType end,VARIANT_BOOL bBreak);
   STDMETHOD(get_BreakLeftEdge)(EndType end,VARIANT_BOOL* bBreak);
   STDMETHOD(put_BreakRightEdge)(EndType end,VARIANT_BOOL bBreak);
   STDMETHOD(get_BreakRightEdge)(EndType end,VARIANT_BOOL* bBreak);

   STDMETHOD(Create)(IBridgeGeometry* pBridge,IDeckBoundary** ppDeckBoundary);
   STDMETHOD(Reset)();
};

OBJECT_ENTRY_AUTO(__uuidof(SimpleDeckBoundaryFactory), CSimpleDeckBoundaryFactory)
