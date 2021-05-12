///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
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

#ifndef INCLUDED_DISPLAYOBJECTFACTORYIMPL_H_
#define INCLUDED_DISPLAYOBJECTFACTORYIMPL_H_
#pragma once

#include "resource.h"

class ATL_NO_VTABLE CDisplayObjectFactoryImpl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CDisplayObjectFactoryImpl, &CLSID_DisplayObjectFactory>,
   public iDisplayObjectFactory
{
public:
   CDisplayObjectFactoryImpl();
   virtual ~CDisplayObjectFactoryImpl();

DECLARE_PROTECT_FINAL_CONSTRUCT()

DECLARE_REGISTRY_RESOURCEID(IDR_DISPLAYOBJECTFACTORY)

BEGIN_COM_MAP(CDisplayObjectFactoryImpl)
	COM_INTERFACE_ENTRY(iDisplayObjectFactory)
END_COM_MAP()


// iDisplayObjectFactory
public:
   STDMETHOD_(void,Create)(CLIPFORMAT cfFormat,COleDataObject* pDataObject,iDisplayObject** dispObj) override;
};

#endif // INCLUDED_DISPLAYOBJECTFACTORYIMPL_H_