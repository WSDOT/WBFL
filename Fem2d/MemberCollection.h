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

// MemberCollection.h : Declaration of the CMemberCollection

#ifndef __MemberCollection_H_
#define __MemberCollection_H_
#pragma once

#include "resource.h"       // main symbols

#include "Fem2dCollections.h"
#include "CircularChild.h"
#include "Member.h"

typedef CModelCollection<IFem2dMemberCollection, IFem2dMember, CMember, IFem2dEnumMember, &IID_IFem2dEnumMember,MemberIDType> MemberCollImpl;

/////////////////////////////////////////////////////////////////////////////
// CMemberCollection
class ATL_NO_VTABLE CMemberCollection : 
	public CCircularChild<IFem2dModel, CComSingleThreadModel>,
   //public CComRefCountTracer<CMemberCollection,CCircularChild<IFem2dModel, CComSingleThreadModel> >,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CMemberCollection,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public MemberCollImpl
{
public:
   CMemberCollection()
	{
	}

   virtual ~CMemberCollection()
	{
	}

   // IMPORTANT!!!
   // OnCreate must be called once and only once by creator
   void OnCreate(IFem2dModel* pModel, ModelEvents* pEvents);

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMemberCollection)
	COM_INTERFACE_ENTRY(IFem2dMemberCollection)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IFem2dMemberCollection
public:
	STDMETHOD(Create)(/*[in]*/MemberIDType ID, /*[in]*/JointIDType startJoint,/*[in]*/JointIDType endJoint,/*[in]*/Float64 EA, /*[in]*/Float64 EI, /*[out, retval]*/ IFem2dMember* *pVal);
	STDMETHOD(Remove)(/*[in]*/CollectionIndexType IDorIndex, /*[in]*/Fem2dAccessType AccessMethod,/*[out,retval]*/MemberIDType* pid);
	STDMETHOD(Clear)();

private:
   HRESULT CMemberCollection::DuplicateJointError(JointIDType id);

};

#endif //__MemberCollection_H_
