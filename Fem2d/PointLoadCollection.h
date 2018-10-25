///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2012  Washington State Department of Transportation
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

// PointLoadCollection.h : Declaration of the CPointLoadCollection

#ifndef __PointLoadCollection_H_
#define __PointLoadCollection_H_
#pragma once

#include "resource.h"       // main symbols

#include "Fem2dCollections.h"
#include "CircularChild.h"
#include "PointLoad.h"

typedef CLoadsCollection<IFem2dPointLoadCollection, IFem2dPointLoad, CPointLoad, IFem2dEnumPointLoad, &IID_IFem2dEnumPointLoad,LoadIDType> PointLoadCollImpl;

class ModelEvents;

/////////////////////////////////////////////////////////////////////////////
// CPointLoadCollection
class ATL_NO_VTABLE CPointLoadCollection : 
	public CCircularChild<IFem2dModel, CComSingleThreadModel>,
   // public CComRefCountTracer<CPointLoadCollection,CCircularChild<IFem2dModel, CComSingleThreadModel> >,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CPointLoadCollection,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public PointLoadCollImpl
{
public:
   CPointLoadCollection()
	{
	}

   virtual ~CPointLoadCollection()
	{
	}

   // IMPORTANT!!!
   // Init must be called once and only once by creator
   void Init(IFem2dModel* pParent, ModelEvents* pEvents, IFem2dLoading* pLoading);

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPointLoadCollection)
	COM_INTERFACE_ENTRY(IFem2dPointLoadCollection)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IFem2dPointLoadCollection
public:
	STDMETHOD(Create)(/*[in]*/LoadIDType ID,  /*[in]*/MemberIDType memberID, /*[in]*/Float64 location, /*[in]*/Float64 Fx, /*[in]*/Float64 Fy, /*[in]*/Float64 Mz, /*[in,optional,defaultvalue(lotMember)]*/ Fem2dLoadOrientation orientation, /*[out, retval]*/ IFem2dPointLoad** pVal);
	STDMETHOD(Remove)(/*[in]*/CollectionIndexType IDorIndex, /*[in]*/Fem2dAccessType AccessMethod,/*[out,retval]*/LoadIDType* pid);
	STDMETHOD(Clear)();
};

#endif //__PointLoadCollection_H_
