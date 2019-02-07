///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2019  Washington State Department of Transportation
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

// PointLoad.h : Declaration of the CPointLoad

#ifndef __POINTLOAD_H_
#define __POINTLOAD_H_
#pragma once

#include "resource.h"       // main symbols
#include "CircularChild.h"
#include "MbrLoad.h"

class ModelEvents;
/////////////////////////////////////////////////////////////////////////////
// CPointLoad
class ATL_NO_VTABLE CPointLoad : 
	public CCircularChild<IFem2dModel, CComSingleThreadModel>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CPointLoad,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IFem2dPointLoad,
   public MbrLoad
{
public:
	CPointLoad()
	{
	}

	virtual ~CPointLoad()
	{
	}

   void Init(IFem2dModel* pParent, ModelEvents* pEvents, IFem2dLoading* pLoading, LoadIDType ID, MemberIDType memberID=-1, Float64 location=0.0, Float64 Fx=0.0, Float64 Fy=0.0, Float64 Mz=0.0, Fem2dLoadOrientation orientation=lotMember);

   // IStructuredStorage - sort of
   STDMETHOD(Load)(IStructuredLoad2 *load);
   STDMETHOD(Save)(IStructuredSave2 *save);

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPointLoad)
	COM_INTERFACE_ENTRY(IFem2dPointLoad)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IFem2dPointLoad
public:
	STDMETHOD(get_Location)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Location)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(GetForce)(/*[out]*/Float64* Fx, /*[out]*/Float64* Fy, /*[out]*/Float64* Mz) override;
	STDMETHOD(SetForce)(/*[in]*/Float64 Fx, /*[in]*/Float64 Fy, /*[in]*/Float64 Mz) override;
	STDMETHOD(get_Mz)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Mz)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_Fy)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Fy)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_Fx)(/*[out, retval]*/ Float64  *pVal) override;
	STDMETHOD(put_Fx)(/*[in]*/ Float64  newVal) override;
	STDMETHOD(get_Orientation)(/*[out, retval]*/ Fem2dLoadOrientation *pVal) override;
	STDMETHOD(put_Orientation)(/*[in]*/ Fem2dLoadOrientation newVal) override;
	STDMETHOD(get_MemberID)(/*[out, retval]*/ MemberIDType *pVal) override;
	STDMETHOD(put_MemberID)(/*[in]*/ MemberIDType newVal) override;
	STDMETHOD(get_ID)(/*[out, retval]*/ LoadIDType *pVal) override;
	STDMETHOD(get_Loading)(/*[out, retval]*/ LoadCaseIDType *pVal) override;

private:
   LoadIDType m_ID;
   MemberIDType m_MemberID;
   Fem2dLoadOrientation m_Orientation;
   Float64 m_Location;
   Float64 m_Fx;
   Float64 m_Fy;
   Float64 m_Mz;

   ModelEvents* m_pModel; // for sending events back to model
   IFem2dLoading* m_pLoading;

public:
   // Member functions for fe analysis
   void GetForceVector(long leftBC,long rightBC,Float64 Length,Float64 Angle,Float64 *vector);
   void GetInternalForces(Float64 x,Float64 Length,Float64 Angle,Fem2dMbrFaceType face,Float64* pFx,Float64* pFy,Float64* pMz);
   void GetDispVector(long leftBC,long rightBC,Float64 Length,Float64 Angle,Float64 EA,Float64 EI,Float64 *vector);
   void GetDeflection(Float64 x,long leftBC,long rightBC,Float64 Length,Float64 Angle,
                        Float64 EA,Float64 EI,
                        Float64* pdx,Float64* pdy,Float64* prz);
   void GetOriginForces(Float64 Length,Float64 Angle,Float64* pFx,Float64* pFy,Float64* pMz);

private:
   void GetLoadComponents(Float64 Angle,Float64* pPx,Float64* pPy,Float64* pMz);
   void GetRealLoadLocation(Float64 length, Float64* pLoc) const;

};

#endif //__POINTLOAD_H_
