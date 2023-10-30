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

// SinglePierLineFactory.h : Declaration of the CSinglePierLineFactory

#pragma once
#include "resource.h"       // main symbols
#include "GirderLineFactory.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif



// CPier

class ATL_NO_VTABLE CSingleGirderLineFactory :
   public CGirderLineFactory,
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSingleGirderLineFactory, &CLSID_SingleGirderLineFactory>,
	public ISingleGirderLineFactory
{
public:
   CSingleGirderLineFactory()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_SINGLEGIRDERLINEFACTORY)

DECLARE_NOT_AGGREGATABLE(CSingleGirderLineFactory)

BEGIN_COM_MAP(CSingleGirderLineFactory)
	COM_INTERFACE_ENTRY(ISingleGirderLineFactory)
   COM_INTERFACE_ENTRY(IGirderLineFactory)
END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
      m_Factory = std::make_shared<WBFL::COGO::SingleGirderLineFactory>();
      return S_OK;
	}

	void FinalRelease()
	{
	}

   virtual std::shared_ptr<WBFL::COGO::GirderLineFactory> GetFactory() override { return m_Factory; }

public:
   STDMETHOD(get_GirderLineID)(IDType* pVal) override;
   STDMETHOD(put_GirderLineID)(IDType newVal) override;
   STDMETHOD(get_LayoutLineID)(IDType* pVal) override;
   STDMETHOD(put_LayoutLineID)(IDType newVal) override;
   STDMETHOD(get_Type)(GirderLineType* pVal) override;
   STDMETHOD(put_Type)(GirderLineType newVal) override;
   STDMETHOD(get_StartPierID)(IDType* pVal) override;
   STDMETHOD(put_StartPierID)(IDType newVal) override;
   STDMETHOD(get_EndPierID)(IDType* pVal) override;
   STDMETHOD(put_EndPierID)(IDType newVal) override;
   STDMETHOD(get_StartMeasurementType)(MeasurementType* pVal) override;
   STDMETHOD(put_StartMeasurementType)(MeasurementType newVal) override;
   STDMETHOD(get_StartMeasurementLocation)(MeasurementLocation* pVal) override;
   STDMETHOD(put_StartMeasurementLocation)(MeasurementLocation newVal) override;
   STDMETHOD(get_EndMeasurementType)(MeasurementType* pVal) override;
   STDMETHOD(put_EndMeasurementType)(MeasurementType newVal) override;
   STDMETHOD(get_EndMeasurementLocation)(MeasurementLocation* pVal) override;
   STDMETHOD(put_EndMeasurementLocation)(MeasurementLocation newVal) override;

private:
   std::shared_ptr<WBFL::COGO::SingleGirderLineFactory> m_Factory;
};
