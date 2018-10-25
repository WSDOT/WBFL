///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2015  Washington State Department of Transportation
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

// JointLoadCollection.h : Declaration of the CJointLoadCollection

#ifndef __JointLoadCollection_H_
#define __JointLoadCollection_H_
#pragma once

#include "resource.h"       // main symbols

#include "Fem2dCollections.h"
#include "CircularChild.h"
#include "JointLoad.h"

typedef CLoadsCollection<IFem2dJointLoadCollection, IFem2dJointLoad, CJointLoad, IFem2dEnumJointLoad, &IID_IFem2dEnumJointLoad, LoadIDType> JointLoadCollImpl;

class ModelEvents;

/////////////////////////////////////////////////////////////////////////////
// CJointLoadCollection
class ATL_NO_VTABLE CJointLoadCollection : 
	public CCircularChild<IFem2dModel, CComSingleThreadModel>,
   //public CComRefCountTracer<CJointLoadCollection,CCircularChild<IFem2dModel, CComSingleThreadModel> >,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CJointLoadCollection,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public JointLoadCollImpl
{
public:
   CJointLoadCollection()
	{
	}

   virtual ~CJointLoadCollection()
	{
	}

   // IMPORTANT!!!
   // Init must be called once and only once by creator
   void Init(IFem2dModel* pParent, ModelEvents* pEvents, IFem2dLoading* pLoading);

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CJointLoadCollection)
	COM_INTERFACE_ENTRY(IFem2dJointLoadCollection)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IFem2dJointLoadCollection
public:
	STDMETHOD(Create)(/*[in]*/LoadIDType ID,  /*[in]*/JointIDType joint, /*[in]*/Float64 Fx, /*[in]*/Float64 Fy, /*[in]*/Float64 Mz, /*[out, retval]*/ IFem2dJointLoad** pVal);
	STDMETHOD(Remove)(/*[in]*/CollectionIndexType IDorIndex, /*[in]*/Fem2dAccessType AccessMethod,/*[out,retval]*/LoadIDType* pid);
	STDMETHOD(Clear)();
};

#endif //__JointLoadCollection_H_
