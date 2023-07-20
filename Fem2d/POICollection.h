///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
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

// POICollection.h : Declaration of the CPOICollection

#ifndef __POICollection_H_
#define __POICollection_H_
#pragma once

#include "resource.h"       // main symbols

#include "Fem2dCollections.h"
#include "CircularChild.h"
#include "POI.h"

using POICollImpl = CModelCollection<IFem2dPOICollection, IFem2dPOI, CPOI, IFem2dEnumPOI, &IID_IFem2dEnumPOI, PoiIDType>;


/////////////////////////////////////////////////////////////////////////////
// CPOICollection
class ATL_NO_VTABLE CPOICollection : 
	public CCircularChild<IFem2dModel, CComSingleThreadModel>,
   // public CComRefCountTracer<CPOICollection,CCircularChild<IFem2dModel, CComSingleThreadModel> >,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CPOICollection,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public POICollImpl
{
public:
   CPOICollection()
	{
	}

   virtual ~CPOICollection()
	{
	}

   // IMPORTANT!!!
   // OnCreate must be called once and only once by creator
   void OnCreate(IFem2dModel* pModel, ModelEvents* pEvents);


DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPOICollection)
	COM_INTERFACE_ENTRY(IFem2dPOICollection)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IFem2dPOICollection
public:
	STDMETHOD(Create)(/*[in]*/PoiIDType ID, /*[in]*/MemberIDType memberID, /*[in]*/Float64 loc, /*[out, retval]*/ IFem2dPOI* *pVal) override;
	STDMETHOD(Remove)(/*[in]*/IndexType IDorIndex, /*[in]*/Fem2dAccessType AccessMethod,/*[out,retval]*/PoiIDType* pid) override;
	STDMETHOD(Clear)() override;
};

#endif //__POICollection_H_
