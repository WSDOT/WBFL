///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
// Copyright © 1999-2025  Washington State Department of Transportation
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

// Diaphragm.h : Declaration of the CDiaphragm

#pragma once
#include "resource.h"       // main symbols
#include "DiaphragmLineFactory.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif



// CDiaphragm

class ATL_NO_VTABLE CThroughPointDiaphragmLineFactory :
	public CDiaphragmLineFactory,
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CThroughPointDiaphragmLineFactory, &CLSID_ThroughPointDiaphragmLineFactory>,
	public IThroughPointDiaphragmLineFactory
{
public:
	CThroughPointDiaphragmLineFactory()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_THROUGHPOINTDIAPHRAGMLINEFACTORY)

DECLARE_NOT_AGGREGATABLE(CThroughPointDiaphragmLineFactory)

BEGIN_COM_MAP(CThroughPointDiaphragmLineFactory)
	COM_INTERFACE_ENTRY(IThroughPointDiaphragmLineFactory)
	COM_INTERFACE_ENTRY(IDiaphragmLineFactory)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		m_Factory = std::make_shared<WBFL::COGO::ThroughPointDiaphragmLineFactory>();
		return S_OK;
	}

	void FinalRelease()
	{
	}

	virtual std::shared_ptr<WBFL::COGO::DiaphragmLineFactory> GetFactory() override { return m_Factory; }

public:
	STDMETHOD(put_Point)(IPoint2d* point) override;
	STDMETHOD(get_Point)(IPoint2d** point) override;
	STDMETHOD(put_Direction)(VARIANT varDirection) override;
	STDMETHOD(get_Direction)(IDirection** direction) override;
	STDMETHOD(get_DiaphragmLineID)(IDType* pVal) override;
	STDMETHOD(put_DiaphragmLineID)(IDType newVal) override;
	STDMETHOD(put_Staggered)(VARIANT_BOOL bStaggered) override;
	STDMETHOD(get_Staggered)(VARIANT_BOOL* bStaggered) override;
	STDMETHOD(put_LeftGirderLineID)(IDType ID) override;
	STDMETHOD(get_LeftGirderLineID)(IDType* ID) override;
	STDMETHOD(put_RightGirderLineID)(IDType ID) override;
	STDMETHOD(get_RightGirderLineID)(IDType* ID) override;

private:
	std::shared_ptr<WBFL::COGO::ThroughPointDiaphragmLineFactory> m_Factory;
};
