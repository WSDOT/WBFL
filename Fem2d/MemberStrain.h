///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2023  Washington State Department of Transportation
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

// MemberStrain.h : Declaration of the CMemberStrain

#ifndef __MEMBERSTRAIN_H_
#define __MEMBERSTRAIN_H_
#pragma once

#include "resource.h"       // main symbols
#include "CircularChild.h"
#include "MbrLoad.h"

class ModelEvents;
/////////////////////////////////////////////////////////////////////////////
// CMemberStrain
class ATL_NO_VTABLE CMemberStrain : 
	public CCircularChild<IFem2dModel, CComSingleThreadModel>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CMemberStrain,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IFem2dMemberStrain,
   public MbrLoad
{
public:
   CMemberStrain():
   m_ID(0),
   m_AxialStrain(0),
   m_CurvatureStrain(0),
   m_StartLocation(0),
   m_EndLocation(-1.0),
   m_MemberID(0),
   m_pModel(0),
   m_pLoading(0)
	{
	}

   virtual ~CMemberStrain()
   {}

   void Init(IFem2dModel* pParent, ModelEvents* pEvents, IFem2dLoading* pLoading, LoadIDType ID, MemberIDType memberID=-1, Float64 xStart=0.0,Float64 xEnd=0.0,Float64 axialStrain=0.0, Float64 CurvatureStrain=0.0);

   // IStructuredStorage - sort of
   STDMETHOD(Load)(IStructuredLoad2 *load);
   STDMETHOD(Save)(IStructuredSave2 *save);

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMemberStrain)
	COM_INTERFACE_ENTRY(IFem2dMemberStrain)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IFem2dMemberStrain
public:
	STDMETHOD(get_Loading)(/*[out, retval]*/ LoadCaseIDType *pVal) override;
   STDMETHOD(get_StartLocation)(/*[out, retval]*/ Float64  *pVal) override;
	STDMETHOD(put_StartLocation)(/*[in]*/ Float64  newVal) override;
	STDMETHOD(get_EndLocation)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_EndLocation)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_CurvatureStrain)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_CurvatureStrain)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_AxialStrain)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_AxialStrain)(/*[in]*/ Float64 newVal) override;
	STDMETHOD(get_MemberID)(/*[out, retval]*/ MemberIDType *pVal) override;
	STDMETHOD(put_MemberID)(/*[in]*/ MemberIDType newVal) override;
	STDMETHOD(get_ID)(/*[out, retval]*/ LoadIDType *pVal) override;

// MbrLoad
public:
   void GetForceVector(long leftBC,long rightBC,Float64 Length,Float64 Angle,Float64 *vector);
   void GetInternalForces(Float64 x,Float64 Length,Float64 Angle,Fem2dMbrFaceType face,Float64* pFx,Float64* pFy,Float64* pMz);
   void GetDispVector(long leftBC,long rightBC,Float64 Length,Float64 Angle,Float64 EA,Float64 EI,Float64 *vector);
   void GetDeflection(Float64 x,long leftBC,long rightBC,Float64 Length,Float64 Angle,
                        Float64 EA,Float64 EI,
                        Float64* pdx,Float64* pdy,Float64* prz);
   void GetOriginForces(Float64 Length,Float64 Angle,Float64* pFx,Float64* pFy,Float64* pMz);

private:
   LoadIDType m_ID;
   Float64 m_AxialStrain;
   Float64 m_CurvatureStrain;
   Float64 m_StartLocation;
   Float64 m_EndLocation;
   MemberIDType m_MemberID;

   ModelEvents* m_pModel; // for sending events back to model
   IFem2dLoading* m_pLoading;

   void GetLocalData(Float64 Angle,Float64 length, Float64* pStartLoc, Float64* pEndLoc);
};

#endif //__MEMBERSTRAIN_H_
