///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2017  Washington State Department of Transportation
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

// JointLoad.h : Declaration of the CJointLoad

#ifndef __JOINTLOAD_H_
#define __JOINTLOAD_H_
#pragma once

#include "resource.h"       // main symbols
#include "CircularChild.h"

class ModelEvents;
/////////////////////////////////////////////////////////////////////////////
// CJointLoad
class ATL_NO_VTABLE CJointLoad : 
	public CCircularChild<IFem2dModel, CComSingleThreadModel>,
   //public CComRefCountTracer<CJointLoad, CCircularChild<IFem2dModel, CComSingleThreadModel> >,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CJointLoad,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IFem2dJointLoad
{
public:
   CJointLoad():
   m_ID(0),
   m_Fx(0),
   m_Fy(0),
   m_Mz(0),
   m_JointID(0),
   m_pModel(0),
   m_pLoading(0)
	{
	}

   virtual ~CJointLoad()
   {;}


   void Init(IFem2dModel* pParent, ModelEvents* pEvents, IFem2dLoading* pLoading, LoadIDType ID, JointIDType jointID=-1, Float64 Fx=0.0, Float64 Fy=0.0, Float64 Mz=0.0);

   // IStructuredStorage - sort of
   STDMETHOD(Load)(/*[in]*/ IStructuredLoad2 *load);
   STDMETHOD(Save)(/*[in]*/ IStructuredSave2 *save);

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CJointLoad)
	COM_INTERFACE_ENTRY(IFem2dJointLoad)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IFem2dJointLoad
public:
	STDMETHOD(get_Loading)(/*[out, retval]*/ LoadCaseIDType *pVal);
	STDMETHOD(GetForce)(/*[out]*/Float64* Fx, /*[out]*/Float64* Fy, /*[out]*/Float64* Mz);
	STDMETHOD(SetForce)(/*[in]*/Float64 Fx, /*[in]*/Float64 Fy, /*[in]*/Float64 Mz);
	STDMETHOD(get_Mz)(/*[out, retval]*/ Float64  *pVal);
	STDMETHOD(put_Mz)(/*[in]*/ Float64  newVal);
	STDMETHOD(get_Fy)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_Fy)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_Fx)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_Fx)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_JointID)(/*[out, retval]*/ JointIDType *pVal);
	STDMETHOD(put_JointID)(/*[in]*/ JointIDType newVal);
	STDMETHOD(get_ID)(/*[out, retval]*/ LoadIDType *pVal);

private:
   LoadIDType m_ID;
   Float64 m_Fx;
   Float64 m_Fy;
   Float64 m_Mz;
   JointIDType m_JointID;

   ModelEvents* m_pModel; // for sending events back to model
   IFem2dLoading* m_pLoading;

};

#endif //__JOINTLOAD_H_
