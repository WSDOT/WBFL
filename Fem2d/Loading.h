///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2024  Washington State Department of Transportation
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

// Loading.h : Declaration of the CLoading

#ifndef __LOADING_H_
#define __LOADING_H_
#pragma once

#include "resource.h"       // main symbols

#include "CircularChild.h"
#include "JointLoadCollection.h"
#include "JointDisplacementCollection.h"
#include "PointLoadCollection.h"
#include "DistributedLoadCollection.h"
#include "MemberStrainCollection.h"

class CModel;
class ModelEvents;
class CMember;

/////////////////////////////////////////////////////////////////////////////
// CLoading
class ATL_NO_VTABLE CLoading : 
	//public CComRefCountTracer<CLoading,CCircularChild<IFem2dModel, CComSingleThreadModel> >,
	public CCircularChild<IFem2dModel, CComSingleThreadModel>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CLoading,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IFem2dLoading
{
public:
   CLoading():
   m_ID(0),
   m_pModel(0)
	{
	}

   virtual ~CLoading();

   HRESULT OnCreate(IFem2dModel* pModel, ModelEvents* pEvents, LoadCaseIDType id);

   // IStructuredStorage - sort of
   STDMETHOD(Load)(IStructuredLoad2 *load);
   STDMETHOD(Save)(IStructuredSave2 *save);

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLoading)
	COM_INTERFACE_ENTRY(IFem2dLoading)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IFem2dLoading
public:
	STDMETHOD(get_PointLoads)(/*[out, retval]*/ IFem2dPointLoadCollection* *pVal) override;
	STDMETHOD(get_JointLoads)(/*[out, retval]*/ IFem2dJointLoadCollection* *pVal) override;
	STDMETHOD(get_JointDeflections)(/*[out, retval]*/ IFem2dJointDeflectionCollection* *pVal) override;
	STDMETHOD(get_MemberStrains)(/*[out, retval]*/ IFem2dMemberStrainCollection* *pVal) override;
	STDMETHOD(get_DistributedLoads)(/*[out, retval]*/ IFem2dDistributedLoadCollection* *pVal) override;
	STDMETHOD(get_ID)(/*[out, retval]*/ LoadCaseIDType *pVal) override;

private:
   LoadCaseIDType m_ID;

   using PointLoads = CComObject<CPointLoadCollection>;
   using PointLoadIterator = PointLoads::iterator;
   using JointLoads = CComObject<CJointLoadCollection>;
   using JointLoadIterator = JointLoads::iterator;
   using DistributedLoads = CComObject<CDistributedLoadCollection>;
   using DistributedLoadIterator = DistributedLoads::iterator;
   using JointDeflections = CComObject<CJointDeflectionCollection>;
   using JointDeflectionIterator = JointDeflections::iterator;
   using MemberStrains = CComObject<CMemberStrainCollection>;
   using MemberStrainIterator = MemberStrains::iterator;

   JointLoads*         m_pJointLoads;
   DistributedLoads*   m_pDistributedLoads;
   MemberStrains*      m_pMemberStrains;
   JointDeflections* m_pJointDeflections;
   PointLoads*         m_pPointLoads;

   ModelEvents*           m_pModel;

private:
   // Fem-related functions
   void ApplyLoads(CModel *model);
   void ApplyLoads(CMember *member);

   friend CModel;

};

#endif //__LOADING_H_
