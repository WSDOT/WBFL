///////////////////////////////////////////////////////////////////////
// BridgeGeometry
// Copyright © 1999-2022  Washington State Department of Transportation
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

// SimpleGirderLineFactory.h : Declaration of the CSimpleGirderLineFactory

#pragma once
#include "resource.h"       // main symbols

#include "WBFLBridgeGeometry.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif



// CSimpleGirderLineFactory
//
// Create equally spaced girder lines between two previoiusly defined layout lines. Girder lines
// may be simple or continuous.

class ATL_NO_VTABLE CSimpleGirderLineFactory :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSimpleGirderLineFactory, &CLSID_SimpleGirderLineFactory>,
	public ISimpleGirderLineFactory
{
public:
	CSimpleGirderLineFactory()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_SIMPLEGIRDERLINEFACTORY)

DECLARE_NOT_AGGREGATABLE(CSimpleGirderLineFactory)

BEGIN_COM_MAP(CSimpleGirderLineFactory)
	COM_INTERFACE_ENTRY(ISimpleGirderLineFactory)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
      return Reset();
	}

	void FinalRelease()
	{
	}

   GirderIDType m_StartGirderLineID; // ID of the first girderline to be created
   GirderIDType m_GirderLineIDInc; // girder line ID increment
   LineIDType m_LeftLayoutLineID; // ID of the left layout line
   LineIDType m_RightLayoutLineID; // ID of the left layout line
   LineIDType m_LayoutLineIDInc; // layout line ID increment
   PierIDType m_StartPierID; // ID of the pier where the girder line begins
   PierIDType m_EndPierID; // ID of the pier where the girder line ends
   PierIDType m_PierIDInc; // pier ID increment
   GirderLineType m_GirderLineType; // Type of girder line that will be created
   VARIANT_BOOL m_bContinuous; // If VARIANT_TRUE, a single girder line is created between start and end piers
                               // otherwise, single span girder lines are created between start and end piers
                               // assuming a pier ID increment of 1.
   MeasurementType m_MeasureType[2];   // Defines if the girder layout line is intersected with
                                    // the centerline of the pier or with the normal to the alignment
                                    // where the pier intersects the alignment
   MeasurementLocation m_MeasureLocation[2]; // Defines if the girder layout line is is intersected with
                                          // the centerline of the pier or the centerline of bearing

public:
   STDMETHOD(get_GirderLineID)(GirderIDType* pVal) override;
   STDMETHOD(put_GirderLineID)(GirderIDType newVal) override;
   STDMETHOD(get_GirderLineIDInc)(GirderIDType* pVal) override;
   STDMETHOD(put_GirderLineIDInc)(GirderIDType newVal) override;
   STDMETHOD(get_LeftLayoutLineID)(LineIDType* pVal) override;
   STDMETHOD(put_LeftLayoutLineID)(LineIDType newVal) override;
   STDMETHOD(get_RightLayoutLineID)(LineIDType* pVal) override;
   STDMETHOD(put_RightLayoutLineID)(LineIDType newVal) override;
   STDMETHOD(get_LayoutLineIDInc)(LineIDType* pVal) override;
   STDMETHOD(put_LayoutLineIDInc)(LineIDType newVal) override;
   STDMETHOD(get_Type)(GirderLineType* pVal) override;
   STDMETHOD(put_Type)(GirderLineType newVal) override;
   STDMETHOD(get_StartPierID)(PierIDType* pVal) override;
   STDMETHOD(put_StartPierID)(PierIDType newVal) override;
   STDMETHOD(get_EndPierID)(PierIDType* pVal) override;
   STDMETHOD(put_EndPierID)(PierIDType newVal) override;
   STDMETHOD(get_PierIDInc)(PierIDType* pVal) override;
   STDMETHOD(put_PierIDInc)(PierIDType newVal) override;
   STDMETHOD(get_Continuous)(VARIANT_BOOL* pbContinuous) override;
   STDMETHOD(put_Continuous)(VARIANT_BOOL bContinuous) override;
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

OBJECT_ENTRY_AUTO(__uuidof(SimpleGirderLineFactory), CSimpleGirderLineFactory)
