///////////////////////////////////////////////////////////////////////
// LBAM Live Loader - Longitindal Bridge Analysis Model
// Copyright © 1999-2021  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the Alternate Route Library Open Source License as published by 
// the Washington State Department of Transportation, Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but is distributed 
// AS IS, WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See the Alternate Route Library Open Source 
// License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License 
// along with this program; if not, write to the Washington State Department of 
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// EnvelopedVehicularResponseFactory.h : Declaration of the CEnvelopedVehicularResponseFactory

#ifndef _ENVELOPEDVEHICULARRESPONSEFACTORY_H_
#define _ENVELOPEDVEHICULARRESPONSEFACTORY_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEnvelopedVehicularResponseFactory
class ATL_NO_VTABLE CEnvelopedVehicularResponseFactory : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEnvelopedVehicularResponseFactory, &CLSID_EnvelopedVehicularResponseFactory>,
	public ISupportErrorInfo,
	public IEnvelopedVehicularResponseFactory,
   public IObjectSafetyImpl<CEnvelopedVehicularResponseFactory,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>
{
public:
   CEnvelopedVehicularResponseFactory()
	{
	}
 
DECLARE_REGISTRY_RESOURCEID(IDR_ENVELOPEDVEHICULARRESPONSEFACTORY)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CEnvelopedVehicularResponseFactory)
	COM_INTERFACE_ENTRY(IEnvelopedVehicularResponseFactory)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IEnvelopedVehicularResponseFactory
public:
	STDMETHOD(CreateEnvelopedVehicularResponse)(/*[out,retval]*/IEnvelopedVehicularResponse** pEVR) override;
};

#endif //_ENVELOPEDVEHICULARRESPONSEFACTORY_H_
