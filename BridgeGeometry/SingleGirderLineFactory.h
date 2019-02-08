///////////////////////////////////////////////////////////////////////
// BridgeGeometry
// Copyright © 1999-2019  Washington State Department of Transportation
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

// SingleGirderLineFactory.h : Declaration of the CSingleGirderLineFactory

#pragma once
#include "resource.h"       // main symbols

#include "WBFLBridgeGeometry.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif



// CSingleGirderLineFactory

class ATL_NO_VTABLE CSingleGirderLineFactory :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSingleGirderLineFactory, &CLSID_SingleGirderLineFactory>,
	public ISingleGirderLineFactory
{
public:
	CSingleGirderLineFactory()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_SINGLEGIRDERLINEFACTORY)

BEGIN_COM_MAP(CSingleGirderLineFactory)
	COM_INTERFACE_ENTRY(ISingleGirderLineFactory)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
      return Reset();
	}

	void FinalRelease()
	{
	}

   GirderIDType m_GirderLineID;     // ID of the girder line that will be created
   LineIDType m_LayoutLineID;       // ID of the layout line used to create the girder line
   GirderLineType m_GirderLineType; // Type of girder line that will be created
   PierIDType m_StartPierID;        // ID of the pier where the girder line begins
   PierIDType m_EndPierID;          // ID of the pier where the girder line ends
   MeasurementType m_MeasureType[2];   // Defines if the girder layout line is intersected with
                                    // the centerline of the pier or with the normal to the alignment
                                    // where the pier intersects the alignment
   MeasurementLocation m_MeasureLocation[2]; // Defines if the girder layout line is is intersected with
                                          // the centerline of the pier or the centerline of bearing

public:

   STDMETHOD(get_GirderLineID)(GirderIDType* pVal) override;
   STDMETHOD(put_GirderLineID)(GirderIDType newVal) override;
   STDMETHOD(get_LayoutLineID)(LineIDType* pVal) override;
   STDMETHOD(put_LayoutLineID)(LineIDType newVal) override;
   STDMETHOD(get_Type)(GirderLineType* pVal) override;
   STDMETHOD(put_Type)(GirderLineType newVal) override;
   STDMETHOD(get_StartPierID)(PierIDType* pVal) override;
   STDMETHOD(put_StartPierID)(PierIDType newVal) override;
   STDMETHOD(get_EndPierID)(PierIDType* pVal) override;
   STDMETHOD(put_EndPierID)(PierIDType newVal) override;
   STDMETHOD(get_StartMeasurementType)(MeasurementType* pVal) override;
   STDMETHOD(put_StartMeasurementType)(MeasurementType newVal) override;
   STDMETHOD(get_StartMeasurementLocation)(MeasurementLocation* pVal) override;
   STDMETHOD(put_StartMeasurementLocation)(MeasurementLocation newVal) override;
   STDMETHOD(get_EndMeasurementType)(MeasurementType* pVal) override;
   STDMETHOD(put_EndMeasurementType)(MeasurementType newVal) override;
   STDMETHOD(get_EndMeasurementLocation)(MeasurementLocation* pVal) override;
   STDMETHOD(put_EndMeasurementLocation)(MeasurementLocation newVal) override;

   STDMETHOD(Create)(IBridgeGeometry* pBridge,IUnkArray** ppArrayGirderLines) override;
   STDMETHOD(Reset)() override;
};

OBJECT_ENTRY_AUTO(__uuidof(SingleGirderLineFactory), CSingleGirderLineFactory)
