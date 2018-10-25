///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2010  Washington State Department of Transportation
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

// JointCollection.h : Declaration of the CJointCollection

#ifndef __JointCollection_H_
#define __JointCollection_H_
#pragma once

#include "resource.h"       // main symbols

#include "Fem2dCollections.h"
#include "CircularChild.h"
#include "Joint.h"

typedef CModelCollection<IFem2dJointCollection, IFem2dJoint, CJoint, IFem2dEnumJoint, &IID_IFem2dEnumJoint,JointIDType> JointCollImpl;


/////////////////////////////////////////////////////////////////////////////
// CJointCollection
class ATL_NO_VTABLE CJointCollection : 
	public CCircularChild<IFem2dModel, CComSingleThreadModel>,
   //public CComRefCountTracer<CJointCollection,CCircularChild<IFem2dModel, CComSingleThreadModel> >,
	public ISupportErrorInfo, 
   public IObjectSafetyImpl<CJointCollection,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public JointCollImpl
{
public:
   CJointCollection()
	{
	}

   virtual ~CJointCollection()
	{
	}

   // IMPORTANT!!!
   // OnCreate must be called once and only once by creator
   void OnCreate(IFem2dModel* pModel, ModelEvents* pEvents);

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CJointCollection)
	COM_INTERFACE_ENTRY(IFem2dJointCollection)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IFem2dJointCollection
public:
	STDMETHOD(Create)(/*[in]*/JointIDType ID, /*[in]*/Float64 fltX, /*[in]*/Float64 fltY, /*[out, retval]*/ IFem2dJoint* *pVal);
	STDMETHOD(Remove)(/*[in]*/CollectionIndexType IDorIndex, /*[in]*/Fem2dAccessType AccessMethod,/*[out,retval]*/JointIDType* pid);
	STDMETHOD(Clear)();

};

#endif //__JointCollection_H_
