///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
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

// BridgeFramingGeometry.h : Declaration of the CBridgeGeometry

#pragma once
#include "resource.h"       // main symbols

//#include "PierLineCollection.h"
//#include "PathCollection.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif



// CBridgeGeometry

class ATL_NO_VTABLE CBridgeGeometry :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CBridgeGeometry, &CLSID_BridgeGeometry>,
	public IBridgeGeometry
{
public:
   CBridgeGeometry()
	{
   }

DECLARE_REGISTRY_RESOURCEID(IDR_BRIDGEGEOMETRY)

DECLARE_NOT_AGGREGATABLE(CBridgeGeometry)

BEGIN_COM_MAP(CBridgeGeometry)
	COM_INTERFACE_ENTRY(IBridgeGeometry)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
      m_Bridge = WBFL::COGO::BridgeFramingGeometry::Create();
		return S_OK;
	}

	void FinalRelease()
	{
	}

   std::shared_ptr<WBFL::COGO::BridgeFramingGeometry> m_Bridge;

   using AlignmentCollection = std::map<IDType,CComPtr<IAlignment>>;
   AlignmentCollection m_Alignments;

public:
   STDMETHOD(AddAlignment)(IDType ID,IAlignment* pAligment) override;
   STDMETHOD(GetAlignment)(IDType ID,IAlignment** pAlignment) override;
   STDMETHOD(put_BridgeAlignmentID)(IDType ID) override;
   STDMETHOD(get_BridgeAlignmentID)(IDType* ID) override;
   STDMETHOD(get_BridgeAlignment)(IAlignment** alignment) override;
   STDMETHOD(put_ProfileID)(IDType profileID) override;
   STDMETHOD(get_ProfileID)(IDType* pProfileID) override;
   STDMETHOD(put_SurfaceID)(IDType surfaceID) override;
   STDMETHOD(get_SurfaceID)(IDType* pSurfaceID) override;

   STDMETHOD(put_BridgeLineOffset)(Float64 offset) override;
   STDMETHOD(get_BridgeLineOffset)(Float64* offset) override;
   STDMETHOD(get_BridgeLine)(IPath** path) override;

   STDMETHOD(AddPierLineFactory)(IPierLineFactory* pFactory) override;
   STDMETHOD(GetPierLine)(PierIndexType idx, IPierLine** ppPier) override;
   STDMETHOD(FindPierLine)(PierIDType ID, IPierLine** ppPier) override;
   STDMETHOD(get_PierLineCount)(PierIndexType* pVal) override;

   STDMETHOD(AddLayoutLineFactory)(ILayoutLineFactory* pFactory) override;
   STDMETHOD(GetLayoutLine)(IndexType idx, IPath** path) override;
   STDMETHOD(FindLayoutLine)(IDType ID,IPath** path) override;
   STDMETHOD(get_LayoutLineCount)(IndexType* pVal) override;

   STDMETHOD(AddGirderLineFactory)(IGirderLineFactory* pFactory) override;
   STDMETHOD(GetGirderLine)( IndexType idx, IGirderLine** ppGirderLine) override;
   STDMETHOD(FindGirderLine)(IDType ID, IGirderLine** ppGirderLine) override;
   STDMETHOD(get_GirderLineCount)(IndexType* pVal) override;

   STDMETHOD(AddDiaphragmLineFactory)(IDiaphragmLineFactory* pFactory) override;
   STDMETHOD(GetDiaphragmLine)( IndexType idx, IDiaphragmLine** ppDiaphragmLine) override;
   STDMETHOD(FindDiaphragmLine)(IDType ID, IDiaphragmLine** ppDiaphragmLine) override;
   STDMETHOD(get_DiaphragmLineCount)(IndexType* pVal) override;

   STDMETHOD(AddDeckBoundaryFactory)(IDeckBoundaryFactory* pFactory) override;
   STDMETHOD(get_DeckBoundary)(IDeckBoundary** ppDeckBoundary) override;
};
