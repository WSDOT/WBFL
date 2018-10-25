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

// DistributedLoad.h : Declaration of the CDistributedLoad

#ifndef __DISTRIBUTEDLOAD_H_
#define __DISTRIBUTEDLOAD_H_
#pragma once

#include "resource.h"       // main symbols
#include "CircularChild.h"
#include "MbrLoad.h"

class ModelEvents;
/////////////////////////////////////////////////////////////////////////////
// CDistributedLoad
class ATL_NO_VTABLE CDistributedLoad : 
	public CCircularChild<IFem2dModel, CComSingleThreadModel>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CDistributedLoad,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IFem2dDistributedLoad,
   public MbrLoad
{
public:
   CDistributedLoad()
	{
	}

   virtual ~CDistributedLoad()
	{
	}

   void Init(IFem2dModel* pParent, ModelEvents* pEvents, IFem2dLoading* pLoading, LoadIDType ID, MemberIDType memberID=-1, Fem2dLoadDirection direction=loadDirFy, Float64 startLocation=0.0, Float64 endLocation=0.0, Float64 WStart=0.0, Float64 WEnd=0.0, Fem2dLoadOrientation orientation=lotMember);

   // IStructuredStorage - sort of
   STDMETHOD(Load)(/*[in]*/ IStructuredLoad2 *load);
   STDMETHOD(Save)(/*[in]*/ IStructuredSave2 *save);

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CDistributedLoad)
	COM_INTERFACE_ENTRY(IFem2dDistributedLoad)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IFem2dDistributedLoad
public:
	STDMETHOD(get_WEnd)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_WEnd)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_WStart)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_WStart)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_EndLocation)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_EndLocation)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_StartLocation)(/*[out, retval]*/ Float64  *pVal);
	STDMETHOD(put_StartLocation)(/*[in]*/ Float64  newVal);
	STDMETHOD(get_Direction)(/*[out, retval]*/ Fem2dLoadDirection *pVal);
	STDMETHOD(put_Direction)(/*[in]*/ Fem2dLoadDirection newVal);
	STDMETHOD(get_Orientation)(/*[out, retval]*/ Fem2dLoadOrientation *pVal);
	STDMETHOD(put_Orientation)(/*[in]*/ Fem2dLoadOrientation newVal);
	STDMETHOD(get_MemberID)(/*[out, retval]*/ MemberIDType *pVal);
	STDMETHOD(put_MemberID)(/*[in]*/ MemberIDType newVal);
	STDMETHOD(get_ID)(/*[out, retval]*/ LoadIDType *pVal);
	STDMETHOD(get_Loading)(/*[out, retval]*/ LoadCaseIDType *pVal);

private:
   LoadIDType m_ID;
   MemberIDType m_MemberID;
   Fem2dLoadOrientation m_Orientation;
   Fem2dLoadDirection m_Direction;
   Float64 m_StartLocation;
   Float64 m_EndLocation;
   Float64 m_WEnd;
   Float64 m_WStart;

   ModelEvents* m_pModel; // for sending events back to model
   IFem2dLoading* m_pLoading;

public:
   // Member functions for fe analysis
   void GetForceVector(MbrType type,Float64 Length,Float64 Angle,Float64 *vector);
   void GetInternalForces(Float64 x,Float64 Length,Float64 Angle,Fem2dMbrFaceType face,Float64* pFx,Float64* pFy,Float64* pMz);
   void GetDispVector(MbrType type,Float64 Length,Float64 Angle,Float64 EA,Float64 EI,Float64 *vector);
   void GetDisplacement(Float64 x,MbrType type,Float64 Length,Float64 Angle,
                        Float64 EA,Float64 EI,
                        Float64* pdx,Float64* pdy,Float64* prz);
   void GetOriginForces(Float64 Length,Float64 Angle,Float64* pFx,Float64* pFy,Float64* pMz);

private:
   void CheckValid();
   void GetLocalData(Float64 Angle,Float64 length, Float64* pStartLoc, Float64* pEndLoc, Float64* pWxStart,Float64* pWyStart,Float64* pWxEnd,Float64* pWyEnd);

};

#endif //__DistributedLoad_H_
