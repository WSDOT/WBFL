///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
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
   STDMETHOD(Load)(/*[in]*/ IStructuredLoad2 *load);
   STDMETHOD(Save)(/*[in]*/ IStructuredSave2 *save);

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLoading)
	COM_INTERFACE_ENTRY(IFem2dLoading)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IFem2dLoading
public:
	STDMETHOD(get_PointLoads)(/*[out, retval]*/ IFem2dPointLoadCollection* *pVal);
	STDMETHOD(get_JointLoads)(/*[out, retval]*/ IFem2dJointLoadCollection* *pVal);
	STDMETHOD(get_JointDisplacements)(/*[out, retval]*/ IFem2dJointDisplacementCollection* *pVal);
	STDMETHOD(get_MemberStrains)(/*[out, retval]*/ IFem2dMemberStrainCollection* *pVal);
	STDMETHOD(get_DistributedLoads)(/*[out, retval]*/ IFem2dDistributedLoadCollection* *pVal);
	STDMETHOD(get_ID)(/*[out, retval]*/ LoadCaseIDType *pVal);

private:
   LoadCaseIDType m_ID;

   typedef CComObject<CPointLoadCollection>         PointLoads;
   typedef PointLoads::iterator                     PointLoadIterator;
   typedef CComObject<CJointLoadCollection>         JointLoads;
   typedef JointLoads::iterator                     JointLoadIterator;
   typedef CComObject<CDistributedLoadCollection>   DistributedLoads;
   typedef DistributedLoads::iterator               DistributedLoadIterator;
   typedef CComObject<CJointDisplacementCollection> JointDisplacements;
   typedef JointDisplacements::iterator             JointDisplacementIterator;
   typedef CComObject<CMemberStrainCollection>      MemberStrains;
   typedef MemberStrains::iterator                  MemberStrainIterator;

   JointLoads*         m_pJointLoads;
   DistributedLoads*   m_pDistributedLoads;
   MemberStrains*      m_pMemberStrains;
   JointDisplacements* m_pJointDisplacements;
   PointLoads*         m_pPointLoads;

   ModelEvents*           m_pModel;

private:
   // Fem-related functions
   virtual void ApplyLoads(CModel *model);
   virtual void ApplyLoads(CMember *member);

   friend CModel;

};

#endif //__LOADING_H_
