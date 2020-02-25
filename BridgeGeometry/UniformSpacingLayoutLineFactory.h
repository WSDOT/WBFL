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

// UniformSpacingLayoutLineFactory.h : Declaration of the CUniformSpacingLayoutLineFactory

#pragma once
#include "resource.h"       // main symbols

#include "WBFLBridgeGeometry.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif



// CUniformSpacingLayoutLineFactory
//
// Creates Layout Lines from a path object

class ATL_NO_VTABLE CUniformSpacingLayoutLineFactory :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CUniformSpacingLayoutLineFactory, &CLSID_UniformSpacingLayoutLineFactory>,
	public IUniformSpacingLayoutLineFactory
{
public:
	CUniformSpacingLayoutLineFactory()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_UNIFORMSPACINGLAYOUTLINEFACTORY)

BEGIN_COM_MAP(CUniformSpacingLayoutLineFactory)
	COM_INTERFACE_ENTRY(ILayoutLineFactory)
	COM_INTERFACE_ENTRY(IUniformSpacingLayoutLineFactory)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
      return Reset();
	}

	void FinalRelease()
	{
	}

   CogoObjectID m_AlignmentID;
   PierIDType m_StartPierID;
   PierIDType m_EndPierID;
   PierIDType m_PierIDInc;
   Float64 m_StartOffset;
   Float64 m_EndOffset;
   CComPtr<IDblArray> m_StartSpacing;
   CComPtr<IDblArray> m_EndSpacing;
   LineIDType m_LayoutLineID; // ID of first layout line
   LineIDType m_LayoutLineIDInc; // Layout line ID increment

public:
   STDMETHOD(Create)(IBridgeGeometry* pBridge,IPathCollection* pPaths) override;
   STDMETHOD(Reset)() override;

   STDMETHOD(get_AlignmentID)(CogoObjectID* ID) override;
   STDMETHOD(put_AlignmentID)(CogoObjectID ID) override;
   STDMETHOD(get_StartPierID)(PierIDType* pVal) override;
   STDMETHOD(put_StartPierID)(PierIDType newVal) override;
   STDMETHOD(get_EndPierID)(PierIDType* pVal) override;
   STDMETHOD(put_EndPierID)(PierIDType newVal) override;
   STDMETHOD(get_PierIDInc)(PierIDType* pVal) override;
   STDMETHOD(put_PierIDInc)(PierIDType newVal) override;
   STDMETHOD(get_StartSpacingOffset)(Float64* pVal) override;
   STDMETHOD(put_StartSpacingOffset)(Float64 newVal) override;
   STDMETHOD(get_EndSpacingOffset)(Float64* pVal) override;
   STDMETHOD(put_EndSpacingOffset)(Float64 newVal) override;
   STDMETHOD(get_StartSpacing)(IDblArray** pVal) override;
   STDMETHOD(put_StartSpacing)(IDblArray* newVal) override;
   STDMETHOD(get_EndSpacing)(IDblArray** pVal) override;
   STDMETHOD(put_EndSpacing)(IDblArray* newVal) override;
   STDMETHOD(put_LayoutLineID)(LineIDType ID) override;
   STDMETHOD(get_LayoutLineID)(LineIDType* ID) override;
   STDMETHOD(put_LayoutLineIDInc)(LineIDType inc) override;
   STDMETHOD(get_LayoutLineIDInc)(LineIDType* inc) override;

};

OBJECT_ENTRY_AUTO(__uuidof(UniformSpacingLayoutLineFactory), CUniformSpacingLayoutLineFactory)
