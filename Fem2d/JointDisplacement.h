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

// JointDeflection.h : Declaration of the CJointDeflection

#ifndef __JOINTDeflection_H_
#define __JOINTDeflection_H_
#pragma once

#include "resource.h"       // main symbols
#include "CircularChild.h"

class ModelEvents;
/////////////////////////////////////////////////////////////////////////////
// CJointDeflection
class ATL_NO_VTABLE CJointDeflection : 
	public CCircularChild<IFem2dModel, CComSingleThreadModel>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CJointDeflection,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IFem2dJointDeflection
{
public:
   CJointDeflection():
   m_ID(0),
   m_Dx(0),
   m_Dy(0),
   m_Rz(0),
   m_JointID(0),
   m_pModel(0),
   m_pLoading(0)
	{
	}

   virtual ~CJointDeflection()
   {}


   void Init(IFem2dModel* pParent, ModelEvents* pEvents, IFem2dLoading* pLoading, LoadIDType ID, JointIDType jointID=-1, Float64 Dx=0.0, Float64 Dy=0.0, Float64 Rz=0.0);

   // IStructuredStorage - sort of
   STDMETHOD(Load)(/*[in]*/ IStructuredLoad2 *load);
   STDMETHOD(Save)(/*[in]*/ IStructuredSave2 *save);

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CJointDeflection)
	COM_INTERFACE_ENTRY(IFem2dJointDeflection)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IFem2dJointDeflection
public:
	STDMETHOD(get_Loading)(/*[out, retval]*/ LoadCaseIDType *pVal);
	STDMETHOD(GetDeflection)(/*[out]*/Float64* Dx, /*[out]*/Float64* Dy, /*[out]*/Float64* Rz);
	STDMETHOD(SetDeflection)(/*[in]*/Float64 Dx, /*[in]*/Float64 Dy, /*[in]*/Float64 Rz);
	STDMETHOD(get_Rz)(/*[out, retval]*/ Float64  *pVal);
	STDMETHOD(put_Rz)(/*[in]*/ Float64  newVal);
	STDMETHOD(get_Dy)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_Dy)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_Dx)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_Dx)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_JointID)(/*[out, retval]*/ JointIDType *pVal);
	STDMETHOD(put_JointID)(/*[in]*/ JointIDType newVal);
	STDMETHOD(get_ID)(/*[out, retval]*/ LoadIDType *pVal);

private:
   LoadIDType m_ID;
   Float64 m_Dx;
   Float64 m_Dy;
   Float64 m_Rz;
   JointIDType m_JointID;

   ModelEvents* m_pModel; // for sending events back to model
   IFem2dLoading* m_pLoading;

};

#endif //__JointDeflection_H_
