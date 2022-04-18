///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2022  Washington State Department of Transportation
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
// MemberStrain.cpp : Implementation of CMemberStrain
#include "stdafx.h"
#include "MemberStrain.h"
#include "ModelEvents.h"
#include "Loading.h"
#include "Beam.h"
#include "Model.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ON_LOAD_CHANGED() ATLASSERT(m_pModel!=0); \
                          ATLASSERT(m_pLoading!=0);\
                          LoadCaseIDType Loadingid; \
                          m_pLoading->get_ID(&Loadingid); \
                          m_pModel->OnMemberStrainChanged(this, Loadingid);

/////////////////////////////////////////////////////////////////////////////
// CMemberStrain
void CMemberStrain::Init(IFem2dModel* pParent, ModelEvents* pEvents, IFem2dLoading* pLoading, LoadIDType ID, MemberIDType memberID,Float64 xStart,Float64 xEnd, Float64 axial, Float64 curvature)
{
   ATLASSERT(pLoading!=0);

   InitParent(pParent); // CCircularChild implementation

   m_pModel = pEvents;  // for C++ event handlers
   m_pLoading = pLoading;
   m_ID = ID;
   m_MemberID = memberID;
   m_AxialStrain = axial;
   m_CurvatureStrain = curvature;
   m_StartLocation = xStart;
   m_EndLocation = xEnd;
}

STDMETHODIMP CMemberStrain::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IFem2dMemberStrain
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
      {
			return S_OK;
      }
	}
	return S_FALSE;
}

static const Float64 MY_VER=1.0;

STDMETHODIMP CMemberStrain::Load(/*[in]*/ IStructuredLoad2 *pload)
{
   HRESULT hr;
   hr = pload->BeginUnit(CComBSTR("MemberStrain"));
   if (FAILED(hr))
   {
      return hr;
   }

   Float64 ver;
   hr = pload->get_Version(&ver);
   if (FAILED(hr))
   {
      return hr;
   }

   if (ver!=MY_VER)
   {
      return STRLOAD_E_BADVERSION;
   }

   {        
      CComVariant varlong;
      varlong.vt = VT_I4;
      hr = pload->get_Property(CComBSTR("ID"),&varlong);
      if (FAILED(hr))
      {
         return hr;
      }

      m_ID = varlong.lVal;

      hr = pload->get_Property(CComBSTR("MemberID"),&varlong);
      if (FAILED(hr))
      {
         return hr;
      }

      m_MemberID = varlong.lVal;


      CComVariant vardbl;
      vardbl.vt = VT_R8;
      hr = pload->get_Property(CComBSTR("AxialStrain"),&vardbl);
      if (FAILED(hr))
      {
         return hr;
      }

      m_AxialStrain = vardbl.dblVal;

      hr = pload->get_Property(CComBSTR("CurvatureStrain"),&vardbl);
      if (FAILED(hr))
      {
         return hr;
      }

      m_CurvatureStrain = vardbl.dblVal;

      hr = pload->get_Property(CComBSTR("StartLocation"),&vardbl);
      if (FAILED(hr))
      {
         return hr;
      }

      m_StartLocation = vardbl.dblVal;

      hr = pload->get_Property(CComBSTR("EndLocation"),&vardbl);
      if (FAILED(hr))
      {
         return hr;
      }

      m_EndLocation = vardbl.dblVal;
   }

   VARIANT_BOOL eb;
   hr = pload->EndUnit(&eb);
   if (FAILED(hr))
   {
      return hr;
   }

   if (eb!=VARIANT_TRUE)
   {
      return STRLOAD_E_INVALIDFORMAT;
   }

   return S_OK;
}

STDMETHODIMP CMemberStrain::Save(/*[in]*/ IStructuredSave2 *psave)
{
   HRESULT hr;
   hr = psave->BeginUnit(CComBSTR("MemberStrain"), MY_VER);
   if (FAILED(hr))
   {
      return hr;
   }

   {
      hr = psave->put_Property(CComBSTR("ID"),CComVariant(m_ID));
      if (FAILED(hr))
      {
         return hr;
      }

      hr = psave->put_Property(CComBSTR("MemberID"),CComVariant(m_MemberID));
      if (FAILED(hr))
      {
         return hr;
      }

      hr = psave->put_Property(CComBSTR("AxialStrain"),CComVariant(m_AxialStrain));
      if (FAILED(hr))
      {
         return hr;
      }

      hr = psave->put_Property(CComBSTR("CurvatureStrain"),CComVariant(m_CurvatureStrain));
      if (FAILED(hr))
      {
         return hr;
      }

      hr = psave->put_Property(CComBSTR("StartLocation"),CComVariant(m_StartLocation));
      if (FAILED(hr))
      {
         return hr;
      }

      hr = psave->put_Property(CComBSTR("EndLocation"),CComVariant(m_EndLocation));
      if (FAILED(hr))
      {
         return hr;
      }
   }

   hr = psave->EndUnit();
   if (FAILED(hr))
   {
      return hr;
   }

   return S_OK;
}


STDMETHODIMP CMemberStrain::get_ID(LoadIDType *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_ID;

	return S_OK;
}

STDMETHODIMP CMemberStrain::get_MemberID(MemberIDType *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_MemberID;

	return S_OK;
}

STDMETHODIMP CMemberStrain::put_MemberID(MemberIDType newVal)
{
   if (m_MemberID != newVal)
   {
	   m_MemberID = newVal;
      ON_LOAD_CHANGED()
   }
	return S_OK;
}

STDMETHODIMP CMemberStrain::get_AxialStrain(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_AxialStrain;

	return S_OK;
}

STDMETHODIMP CMemberStrain::put_AxialStrain(Float64 newVal)
{
   if (m_AxialStrain != newVal)
   {
	   m_AxialStrain = newVal;
      ON_LOAD_CHANGED()
   }
	return S_OK;
}

STDMETHODIMP CMemberStrain::get_CurvatureStrain(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_CurvatureStrain;

	return S_OK;
}

STDMETHODIMP CMemberStrain::put_CurvatureStrain(Float64 newVal)
{
   if (m_CurvatureStrain != newVal)
   {
	   m_CurvatureStrain = newVal;
      ON_LOAD_CHANGED()
   }
	return S_OK;
}

STDMETHODIMP CMemberStrain::get_StartLocation(Float64  *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_StartLocation;
   return S_OK;
}

STDMETHODIMP CMemberStrain::put_StartLocation(Float64  newVal)
{
   if ( m_StartLocation != newVal )
   {
      m_StartLocation = newVal;
      ON_LOAD_CHANGED()
   }
   return S_OK;
}

STDMETHODIMP CMemberStrain::get_EndLocation(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_EndLocation;
   return S_OK;
}

STDMETHODIMP CMemberStrain::put_EndLocation(Float64 newVal)
{
   if ( m_EndLocation != newVal )
   {
      m_EndLocation = newVal;
      ON_LOAD_CHANGED()
   }
   return S_OK;
}

STDMETHODIMP CMemberStrain::get_Loading(LoadCaseIDType *pVal)
{
   CHECK_RETVAL(pVal);
	ATLASSERT(m_pLoading!=0);

   LoadCaseIDType id;
   m_pLoading->get_ID(&id);
   *pVal = id;

	return S_OK;
}


void CMemberStrain::GetForceVector(long leftBC,long rightBC,Float64 Length,Float64 Angle,Float64 *vector)
{
   Float64 La, Lb;
   GetLocalData(Angle, Length, &La, &Lb);

   // get stiffness coeff's from the member
   // must first get a CModel - This cast is ugly, but is done to reduce physical coupling
   CModel* pModel;
   pModel = static_cast<CModel*>(m_pModel);

   CMember* pmbr = pModel->GetMembers()->Find(m_MemberID);
   ATLASSERT(pmbr!=0);
   Float64 ea, ei;
   pmbr->get_EA(&ea);
   pmbr->get_EI(&ei);

   UniformMemberDistortionBeam Beam(m_AxialStrain, m_CurvatureStrain, La, Lb, Length, ea, ei, leftBC, rightBC);
   Float64 fxl,fyl,mzl,fxr,fyr,mzr;
   Beam.GetReactions( fxl, fyl, mzl, fxr, fyr, mzr);

   vector[0] = fxl;
   vector[1] = fyl;
   vector[2] = mzl;
   vector[3] = fxr;
   vector[4] = fyr;
   vector[5] = mzr;
}

void CMemberStrain::GetDispVector(long leftBC,long rightBC,Float64 Length,Float64 Angle,
                                     Float64 EA,Float64 EI,
                                     Float64 *vector)
{
   Float64 La, Lb;
   GetLocalData(Angle, Length, &La, &Lb);

   UniformMemberDistortionBeam Beam(m_AxialStrain, m_CurvatureStrain, La, Lb, Length, EA, EI, leftBC, rightBC);
   Float64 dxl,dyl,rzl,dxr,dyr,rzr;
   Beam.GetDeflections( dxl, dyl, rzl, dxr, dyr, rzr);

   vector[0] = dxl;
   vector[1] = dyl;
   vector[2] = rzl;
   vector[3] = dxr;
   vector[4] = dyr;
   vector[5] = rzr;
}

void CMemberStrain::GetInternalForces(Float64 x,Float64 Length,Float64 Angle,Fem2dMbrFaceType face,Float64* pFx,Float64* pFy,Float64* pMz)
{
   *pFx = 0;
   *pFy = 0;
   *pMz = 0;
}

void CMemberStrain::GetDeflection(Float64 x,long leftBC,long rightBC,Float64 Length,Float64 Angle,
                                       Float64 EA,Float64 EI,
                                       Float64* pdx,Float64* pdy,Float64* prz)
{
   Float64 La, Lb;
   GetLocalData(Angle, Length, &La, &Lb);

   UniformMemberDistortionBeam Beam(m_AxialStrain, m_CurvatureStrain, La, Lb, Length, EA, EI, leftBC, rightBC);
   Beam.GetDeflection( x, *pdx, *pdy, *prz);
}

void CMemberStrain::GetOriginForces(Float64 Length,Float64 Angle,Float64* pFx,Float64* pFy,Float64* pMz)
{
   *pFx = 0;
   *pFy = 0;
   *pMz = 0;
}

void CMemberStrain::GetLocalData(Float64 Angle, Float64 length, Float64* pStartLoc, Float64* pEndLoc)
{
   ATLASSERT(length>=-1.0);

   // first get locations
   // start location
   Float64 startloc = CMember::GetRealLocation(length, m_StartLocation);

   if (startloc==-1.0)
   {
      // we're in errorland
      if (m_StartLocation<0.0)
      {
         // fractional error
         ATLASSERT(m_StartLocation>=-1.0); // interface should be blocking this
         THROW_IDS(IDS_E_FRACTIONAL_VALUE_OUT_OF_RANGE, FEM2D_E_FRACTIONAL_VALUE_OUT_OF_RANGE, IDH_E_FRACTIONAL_VALUE_OUT_OF_RANGE);
      }
      else
      {
         // explicit location error
         LoadCaseIDType lid;
         m_pLoading->get_ID(&lid);
         CComBSTR msg(CreateErrorMsg2(IDS_E_STRAIN_LOAD_OFF_GIRDER_END, m_ID,lid));
         THROW_MSG(msg, FEM2D_E_STRAIN_LOAD_OFF_GIRDER_END, IDH_E_STRAIN_LOAD_OFF_GIRDER_END);
      }
   }


   // end location
   Float64 endloc = CMember::GetRealLocation(length, m_EndLocation);

   if (endloc==-1.0)
   {
      // we're in errorland
      if (m_EndLocation<0.0)
      {
         // fractional error
         ATLASSERT(m_EndLocation>=-1.0); // interface should be blocking this
         THROW_IDS(IDS_E_FRACTIONAL_VALUE_OUT_OF_RANGE, FEM2D_E_FRACTIONAL_VALUE_OUT_OF_RANGE, IDH_E_FRACTIONAL_VALUE_OUT_OF_RANGE);
      }
      else
      {
         // explicit location error
         LoadCaseIDType lid;
         m_pLoading->get_ID(&lid);
         CComBSTR msg(CreateErrorMsg2(IDS_E_STRAIN_LOAD_OFF_GIRDER_END, m_ID,lid));
         THROW_MSG(msg, FEM2D_E_STRAIN_LOAD_OFF_GIRDER_END, IDH_E_STRAIN_LOAD_OFF_GIRDER_END);
      }
   }
   
  // flip values if user entered start>end
  if (endloc < startloc)
  {
     *pStartLoc= endloc;
     *pEndLoc  = startloc;
  }
  else
  {
     *pStartLoc= startloc;
     *pEndLoc  = endloc;
  }
}
