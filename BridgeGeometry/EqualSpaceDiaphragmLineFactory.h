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

// EqualSpaceDiaphragmLineFactory.h : Declaration of the CEqualSpaceDiaphragmLineFactory

#pragma once
#include "resource.h"       // main symbols

#include "WBFLBridgeGeometry.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif



// CEqualSpaceDiaphragmLineFactory
//
// Create equally spaced diaphragm lines between two stations.

class ATL_NO_VTABLE CEqualSpaceDiaphragmLineFactory :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEqualSpaceDiaphragmLineFactory, &CLSID_EqualSpaceDiaphragmLineFactory>,
	public IEqualSpaceDiaphragmLineFactory
{
public:
	CEqualSpaceDiaphragmLineFactory()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_EQUALSPACEDIAPHRAGMLINEFACTORY)

DECLARE_NOT_AGGREGATABLE(CEqualSpaceDiaphragmLineFactory)

BEGIN_COM_MAP(CEqualSpaceDiaphragmLineFactory)
	COM_INTERFACE_ENTRY(IEqualSpaceDiaphragmLineFactory)
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
   Float64 m_StartStation;
   Float64 m_EndStation;
   LineIDType m_StartID; // ID of the first diaphragm line to be created
   LineIDType m_IDInc;   // diaphragm line ID increment
   Int16 m_Divisor;
   VARIANT_BOOL m_bStaggered;
   GirderIDType m_LeftGirderID;
   GirderIDType m_RightGirderID;

public:
   STDMETHOD(put_AlignmentID)(CogoObjectID ID) override;
   STDMETHOD(get_AlignmentID)(CogoObjectID* ID) override;
   STDMETHOD(put_StartStation)(Float64 station) override;
   STDMETHOD(get_StartStation)(Float64* pStation) override;
   STDMETHOD(put_EndStation)(Float64 station) override;
   STDMETHOD(get_EndStation)(Float64* pStation) override;
   STDMETHOD(put_DiaphragmLineID)(LineIDType newVal) override;
   STDMETHOD(get_DiaphragmLineID)(LineIDType* pVal) override;
   STDMETHOD(put_DiaphragmLineIDInc)(LineIDType newVal) override;
   STDMETHOD(get_DiaphragmLineIDInc)(LineIDType* pVal) override;
   STDMETHOD(put_Divisor)(Int16 divisor) override;
   STDMETHOD(get_Divisor)(Int16* divisor) override;
   STDMETHOD(put_Staggered)(VARIANT_BOOL bStaggered) override;
   STDMETHOD(get_Staggered)(VARIANT_BOOL* bStaggered) override;
   STDMETHOD(put_LeftGirderLineID)(GirderIDType ID) override;
   STDMETHOD(get_LeftGirderLineID)(GirderIDType* ID) override;
   STDMETHOD(put_RightGirderLineID)(GirderIDType ID) override;
   STDMETHOD(get_RightGirderLineID)(GirderIDType* ID) override;

   STDMETHOD(Create)(IBridgeGeometry* pBridge,IUnkArray** ppArrayDiaphagmLines) override;
   STDMETHOD(Reset)() override;
};

OBJECT_ENTRY_AUTO(__uuidof(EqualSpaceDiaphragmLineFactory), CEqualSpaceDiaphragmLineFactory)
