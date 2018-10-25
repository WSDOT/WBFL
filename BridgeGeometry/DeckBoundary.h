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
      return S_OK;
	}

	void FinalRelease()
	{
	}

   IBridgeGeometry* m_pBridge;
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

   CComPtr<IPoint2d> m_LeftEdgePoint[2];
   CComPtr<IPoint2d> m_LeftEdgeBreakPoint[2];
   CComPtr<IPoint2d> m_RightEdgeBreakPoint[2];
   CComPtr<IPoint2d> m_RightEdgePoint[2];

   CComPtr<IPath> m_LeftEdgePath;
   CComPtr<IPath> m_RightEdgePath;

   HRESULT UpdateGeometry();
   HRESULT CreateDeckBoundaryEndPoints(EndType endType,LineIDType endLineID,DeckBoundaryEdgeType edgeType,IPoint2d** end1,IPoint2d** end2,IPoint2d** end3,IPoint2d** end4);
   HRESULT CreateEdgePath(LineIDType edgePathID, IPoint2d* pntStart, IPoint2d* pntEnd,IPath** pPath);

public:
   STDMETHOD(get_Perimeter)(CollectionIndexType nPointsPerSide,IPoint2dCollection** points);
   STDMETHOD(get_PerimeterEx)(CollectionIndexType nPointsPerSide,PierIDType startPierID,PierIDType endPierID,IPoint2dCollection** points);
   STDMETHOD(get_TransverseEdgePoints)(EndType endType,IPoint2d** ppLeft,IPoint2d** ppLeftBreak,IPoint2d** ppRightBreak,IPoint2d** ppRight);
   STDMETHOD(get_LeftEdgePath)(VARIANT_BOOL vbLayoutLine,IPath** path);
   STDMETHOD(get_RightEdgePath)(VARIANT_BOOL vbLayoutLine,IPath** path);
};

OBJECT_ENTRY_NON_CREATEABLE_EX_AUTO(__uuidof(DeckBoundary), CDeckBoundary)
