///////////////////////////////////////////////////////////////////////
// UnitServer - Unit Conversion and Display Unit Management Library
// Copyright © 1999-2016  Washington State Department of Transportation
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

// UnitModeController.h : Declaration of the CUnitModeController

#ifndef __UNITMODECONTROLLER_H_
#define __UNITMODECONTROLLER_H_

#include "resource.h"       // main symbols
#include "WbflUnitServerCP.h"

/////////////////////////////////////////////////////////////////////////////
// CUnitModeController
class ATL_NO_VTABLE CUnitModeController : 
   public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CUnitModeController,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CUnitModeController, &CLSID_UnitModeController>,
   public ISupportErrorInfoImpl<&IID_IUnitModeController>,
	public IConnectionPointContainerImpl<CUnitModeController>,
	public IUnitModeController,
   public IObjectSafetyImpl<CUnitModeController,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
   public CProxyDUnitModeControllerEvents< CUnitModeController >
{
public:
	CUnitModeController()
	{
      m_UnitMode = umSI;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_UNITMODECONTROLLER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CUnitModeController)
	COM_INTERFACE_ENTRY(IUnitModeController)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CUnitModeController)
CONNECTION_POINT_ENTRY(IID_IUnitModeControllerEvents)
END_CONNECTION_POINT_MAP()

private:
   UnitModeType m_UnitMode;

// IUnitModeController
public:
	STDMETHOD(ShowSelectionDialogEx)(/*[in]*/ BSTR helpFile,/*[in]*/ long nID);
	STDMETHOD(ShowSelectionDialog)();
	STDMETHOD(get_UnitMode)(/*[out, retval]*/ UnitModeType *pVal);
	STDMETHOD(put_UnitMode)(/*[in]*/ UnitModeType newVal);
};

#endif //__UNITMODECONTROLLER_H_
