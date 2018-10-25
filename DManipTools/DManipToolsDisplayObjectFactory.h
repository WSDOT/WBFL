///////////////////////////////////////////////////////////////////////
// DManipTools - Direct Manipulation Tools
// Copyright © 1999-2010  Washington State Department of Transportation
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

// DManipToolsDisplayObjectFactory.h : Declaration of the CDManipToolsDisplayObjectFactory

#ifndef __DManipToolsDisplayObjectFactory_H_
#define __DManipToolsDisplayObjectFactory_H_
#pragma once

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDManipToolsDisplayObjectFactory
class ATL_NO_VTABLE CDManipToolsDisplayObjectFactory : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CDManipToolsDisplayObjectFactory, &CLSID_DManipToolsDisplayObjectFactory>,
	public ISupportErrorInfo,
   public iDisplayObjectFactory
{
public:
	CDManipToolsDisplayObjectFactory();

DECLARE_REGISTRY_RESOURCEID(IDR_DMANIPTOOLSDISPLAYOBJECTFACTORY)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CDManipToolsDisplayObjectFactory)
	COM_INTERFACE_ENTRY(iDisplayObjectFactory)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// iDisplayObjectFactory
   STDMETHOD_(void,Create)(CLIPFORMAT cfFormat,COleDataObject* pDataObject,iDisplayObject** dispObj);

};

#endif //__DManipToolsDisplayObjectFactory_H_


   