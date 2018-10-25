///////////////////////////////////////////////////////////////////////
// Fem2D - Two-dimensional Beam Analysis Engine
// Copyright © 1999-2011  Washington State Department of Transportation
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
// PointLoad.cpp : Implementation of CPointLoad
#include "stdafx.h"
#include "PointLoad.h"
#include "ModelEvents.h"
#include "Beam.h"
#include "Member.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ON_LOAD_CHANGED() ATLASSERT(m_pModel!=0); \
                          ATLASSERT(m_pLoading!=0);\
                          LoadCaseIDType Loadingid; \
                          m_pLoading->get_ID(&Loadingid); \
                          m_pModel->OnPointLoadChanged(this, Loadingid);

/////////////////////////////////////////////////////////////////////////////
// CPointLoad

STDMETHODIMP CPointLoad::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IFem2dPointLoad
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

void CPointLoad::Init(IFem2dModel* pParent, ModelEvents* pEvents, IFem2dLoading* pLoading, LoadIDType ID, MemberIDType memberID, Float64 location, Float64 Fx, Float64 Fy, Float64 Mz,Fem2dLoadOrientation orientation)
{
   ATLASSERT(pLoading!=0);
   CheckLoadOrientation(orientation);

   InitParent(pParent); // CCircularChild implementation

   m_pModel = pEvents;  //for C++ event handlers
   m_pLoading = pLoading;
   m_ID = ID;
   m_MemberID = memberID;
   m_Location = location;
   m_Orientation = orientation;
   m_Fx = Fx;
   m_Fy = Fy;
   m_Mz = Mz;
}


static const Float64 MY_VER=1.0;

STDMETHODIMP CPointLoad::Load(/*[in]*/ IStructuredLoad2 *pload)
{
   HRESULT hr;
   hr = pload->BeginUnit(CComBSTR("PointLoad"));
   if (FAILED(hr))
      return hr;

   Float64 ver;
   hr = pload->get_Version(&ver);
   if (FAILED(hr))
      return hr;

   if (ver!=MY_VER)
      return STRLOAD_E_BADVERSION;

   {        
      CComVariant varlong;
      varlong.vt = VT_I4;
      hr = pload->get_Property(CComBSTR("ID"),&varlong);
      if (FAILED(hr))
         return hr;

      m_ID = varlong.lVal;

      hr = pload->get_Property(CComBSTR("MemberID"),&varlong);
      if (FAILED(hr))
         return hr;

      m_MemberID = varlong.lVal;

      hr = pload->get_Property(CComBSTR("Orientation"),&varlong);
      if (FAILED(hr))
         return hr;

      m_Orientation = (Fem2dLoadOrientation)varlong.lVal;
//		if ((long)varlong==(long)lotGlobal)
//         m_Orientation = lotGlobal;
//		else if ((long)varlong==(long)lotMember)
//         m_Orientation = lotMember;
//      else if ((long)varlong==(long)lotGlobal)
//         m_Orientation = lotGlobalProjected;
//      else
//      {
//         ATLASSERT(0); // invalid orientation was written
//         return STRLOAD_E_INVALIDFORMAT;
//      }

      CComVariant vardbl;
      vardbl.vt = VT_R8;
      hr = pload->get_Property(CComBSTR("Location"),&vardbl);
      if (FAILED(hr))
         return hr;

      m_Location = vardbl.dblVal;

      hr = pload->get_Property(CComBSTR("Fx"),&vardbl);
      if (FAILED(hr))
         return hr;

      m_Fx = vardbl.dblVal;

      hr = pload->get_Property(CComBSTR("Fy"),&vardbl);
      if (FAILED(hr))
         return hr;

      m_Fy = vardbl.dblVal;

      hr = pload->get_Property(CComBSTR("Mz"),&vardbl);
      if (FAILED(hr))
         return hr;

      m_Mz = vardbl.dblVal;
   }

   VARIANT_BOOL eb;
   hr = pload->EndUnit(&eb);
   if (FAILED(hr))
      return hr;

   if (eb!=VARIANT_TRUE)
      return STRLOAD_E_INVALIDFORMAT;

   return S_OK;
}

STDMETHODIMP CPointLoad::Save(/*[in]*/ IStructuredSave2 *psave)
{
   HRESULT hr;
   hr = psave->BeginUnit(CComBSTR("PointLoad"), MY_VER);
   if (FAILED(hr))
      return hr;

   {
      hr = psave->put_Property(CComBSTR("ID"),CComVariant(m_ID));
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("MemberID"),CComVariant(m_MemberID));
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("Orientation"),CComVariant((long)m_Orientation));
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("Location"),CComVariant(m_Location));
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("Fx"),CComVariant(m_Fx));
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("Fy"),CComVariant(m_Fy));
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("Mz"),CComVariant(m_Mz));
      if (FAILED(hr))
         return hr;
   }

   hr = psave->EndUnit();
   if (FAILED(hr))
      return hr;

   return S_OK;
}

STDMETHODIMP CPointLoad::get_ID(LoadIDType *pVal)
{
   CHECK_RETVAL(pVal);
   ATLASSERT(m_pModel!=0);
	*pVal = m_ID;

	return S_OK;
}

STDMETHODIMP CPointLoad::get_MemberID(MemberIDType *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_MemberID;

	return S_OK;
}

STDMETHODIMP CPointLoad::put_MemberID(MemberIDType newVal)
{
   if (m_MemberID != newVal)
   {
	   m_MemberID = newVal;
      ON_LOAD_CHANGED()
   }
	return S_OK;
}

STDMETHODIMP CPointLoad::get_Orientation(Fem2dLoadOrientation *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_Orientation;

	return S_OK;
}

STDMETHODIMP CPointLoad::put_Orientation(Fem2dLoadOrientation newVal)
{
   try
   {
      CheckLoadOrientation(newVal);
      if (m_Orientation != newVal)
      {
	      m_Orientation = newVal;
         ON_LOAD_CHANGED()
      }
   }
   catch (CComException& re)
   {
      CComBSTR msg(re.GetErrorMessage());
      HRESULT hr = re.GetHresult();
      DWORD helpid = re.GetHelpID();
      return CComCoClass<CPointLoad,&CLSID_Fem2dPointLoad>::Error(msg, helpid, GetHelpFile(), IID_IFem2dModel, hr);
   }
   catch (...)
   {
      ATLASSERT(0);
      return E_FAIL;
   }

	return S_OK;
}

STDMETHODIMP CPointLoad::get_Fx(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_Fx;

	return S_OK;
}

STDMETHODIMP CPointLoad::put_Fx(Float64 newVal)
{
   if (m_Fx != newVal)
   {
	   m_Fx = newVal;
      ON_LOAD_CHANGED()
   }
	return S_OK;
}

STDMETHODIMP CPointLoad::get_Fy(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_Fy;

	return S_OK;
}

STDMETHODIMP CPointLoad::put_Fy(Float64 newVal)
{
   if (m_Fy != newVal)
   {
	   m_Fy = newVal;
      ON_LOAD_CHANGED()
   }
	return S_OK;
}

STDMETHODIMP CPointLoad::get_Mz(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_Mz;

	return S_OK;
}

STDMETHODIMP CPointLoad::put_Mz(Float64 newVal)
{
   if (m_Mz != newVal)
   {
	   m_Mz = newVal;
      ON_LOAD_CHANGED()
   }
	return S_OK;
}

STDMETHODIMP CPointLoad::SetForce(Float64 Fx, Float64 Fy, Float64 Mz)
{
	m_Fx = Fx;
	m_Fy = Fy;
	m_Mz = Mz;

   ON_LOAD_CHANGED()
	return S_OK;
}

STDMETHODIMP CPointLoad::GetForce(Float64 *Fx, Float64 *Fy, Float64 *Mz)
{
   CHECK_RETVAL(Fx);
   CHECK_RETVAL(Fy);
   CHECK_RETVAL(Mz);
   *Fx = m_Fx;
   *Fy = m_Fy;
   *Mz = m_Mz;

	return S_OK;
}

STDMETHODIMP CPointLoad::get_Location(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_Location;

	return S_OK;
}

STDMETHODIMP CPointLoad::put_Location(Float64 newVal)
{
   if (newVal < -1.0)
      return CComCoClass<CPointLoad,&CLSID_Fem2dPointLoad>::Error(IDS_E_INVALID_POINT_LOAD_LOCATION, IDH_E_INVALID_POINT_LOAD_LOCATION, GetHelpFile(), IID_IFem2dPointLoad, FEM2D_E_INVALID_POINT_LOAD_LOCATION);

   if (m_Location = newVal)
   {
	   m_Location = newVal;
      ON_LOAD_CHANGED()
   }
	return S_OK;
}

void CPointLoad::GetForceVector(MbrType type,Float64 Length,Float64 Angle,Float64 *vector)
{
   Float64 La;
   Float64 Px,Py,Mz;
   Float64 Fx1,Fy1,Mz1;
   Float64 Fx2,Fy2,Mz2;

   GetRealLoadLocation(Length, &La);

   // Initialize the force vector
   vector[0] = 0;
   vector[1] = 0;
   vector[2] = 0;
   vector[3] = 0;
   vector[4] = 0;
   vector[5] = 0;

   GetLoadComponents(Angle,&Px,&Py,&Mz);

   if (Px!=0.0)
   {
      ConcLdBeam Pbeam(Px,La,Beam::ForceX,Length,1,1,type);
      Pbeam.GetReactions(Fx1,Fy1,Mz1,Fx2,Fy2,Mz2);
      vector[0] += Fx1;
      vector[1] += Fy1;
      vector[2] += Mz1;
      vector[3] += Fx2;
      vector[4] += Fy2;
      vector[5] += Mz2;
   }

   if (Py!=0.0)
   {
      ConcLdBeam Vbeam(Py,La,Beam::ForceY,Length,1,1,type);
      Vbeam.GetReactions(Fx1,Fy1,Mz1,Fx2,Fy2,Mz2);
      vector[0] += Fx1;
      vector[1] += Fy1;
      vector[2] += Mz1;
      vector[3] += Fx2;
      vector[4] += Fy2;
      vector[5] += Mz2;
   }

   if (Mz!=0.0)
   {
      ConcLdBeam Mbeam(Mz,La,Beam::MomentZ,Length,1,1,type);
      Mbeam.GetReactions(Fx1,Fy1,Mz1,Fx2,Fy2,Mz2);
      vector[0] += Fx1;
      vector[1] += Fy1;
      vector[2] += Mz1;
      vector[3] += Fx2;
      vector[4] += Fy2;
      vector[5] += Mz2;
   }
}

void CPointLoad::GetDispVector(MbrType type,Float64 Length,Float64 Angle,
                                     Float64 EA,Float64 EI,
                                     Float64 *vector)
{
   Float64 La;
   Float64 Px,Py,Mz; // force or moment
   Float64 Dx1,Dy1,Rz1;
   Float64 Dx2,Dy2,Rz2;

   GetRealLoadLocation(Length, &La);

   // Initialize the force vector
   vector[0] = 0;
   vector[1] = 0;
   vector[2] = 0;
   vector[3] = 0;
   vector[4] = 0;
   vector[5] = 0;

   GetLoadComponents(Angle,&Px,&Py,&Mz);
   ConcLdBeam Pbeam(Px,La,Beam::ForceX,Length,EA,EI,type);
   ConcLdBeam Vbeam(Py,La,Beam::ForceY,Length,EA,EI,type);
   ConcLdBeam Mbeam(Mz,La,Beam::MomentZ,Length,EA,EI,type);

   Pbeam.GetDisplacements(Dx1,Dy1,Rz1,Dx2,Dy2,Rz2);
   vector[0] += Dx1;
   vector[1] += Dy1;
   vector[2] += Rz1;
   vector[3] += Dx2;
   vector[4] += Dy2;
   vector[5] += Rz2;

   Vbeam.GetDisplacements(Dx1,Dy1,Rz1,Dx2,Dy2,Rz2);
   vector[0] += Dx1;
   vector[1] += Dy1;
   vector[2] += Rz1;
   vector[3] += Dx2;
   vector[4] += Dy2;
   vector[5] += Rz2;

   Mbeam.GetDisplacements(Dx1,Dy1,Rz1,Dx2,Dy2,Rz2);
   vector[0] += Dx1;
   vector[1] += Dy1;
   vector[2] += Rz1;
   vector[3] += Dx2;
   vector[4] += Dy2;
   vector[5] += Rz2;
}

void CPointLoad::GetInternalForces(Float64 x,Float64 Length,Float64 Angle,Fem2dMbrFaceType face,Float64* pFx,Float64* pFy,Float64* pMz)
{
   Float64 La;
   Float64 Px,Py,Mo; // force or moment

   GetRealLoadLocation(Length, &La);

   const Float64 L_EPS=1.0e-10; // TRICKY: tolerance is very finicky
                               // found that 1.0e-07 was too loose and 1.0e-15 too tight

   if ( ((face == mftLeft)  && (x <= La+L_EPS)) ||
        ((face == mftRight) && (x >= La-L_EPS)) )
   {
      // Load has no contribution at this location.
      //
      // if (x == La) only consider it if (face == mbrLeftFace)
      *pFx = 0;
      *pFy = 0;
      *pMz = 0;
      return;
   }

   GetLoadComponents(Angle,&Px,&Py,&Mo);

   *pFx = Px;
   *pFy = Py;
   *pMz = Mo + Py*(La-x);
}

void CPointLoad::GetDisplacement(Float64 x,MbrType type,Float64 Length,Float64 Angle,
                                       Float64 EA,Float64 EI,
                                       Float64* pdx,Float64* pdy,Float64* prz)

{
   Float64 La;
   Float64 Px,Py,Mz;
   Float64 Dx,Dy,Rz;

   GetRealLoadLocation(Length, &La);

   // Initialize the force vector
   *pdx = 0;
   *pdy = 0;
   *prz = 0;

   GetLoadComponents(Angle,&Px,&Py,&Mz);
   ConcLdBeam Pbeam(Px,La,Beam::ForceX,Length,EA,EI,type);
   ConcLdBeam Vbeam(Py,La,Beam::ForceY,Length,EA,EI,type);
   ConcLdBeam Mbeam(Mz,La,Beam::MomentZ,Length,EA,EI,type);

   Pbeam.GetDeflection(x,Dx,Dy,Rz);
   *pdx += Dx;
   *pdy += Dy;
   *prz += Rz;

   Vbeam.GetDeflection(x,Dx,Dy,Rz);
   *pdx += Dx;
   *pdy += Dy;
   *prz += Rz;

   Mbeam.GetDeflection(x,Dx,Dy,Rz);
   *pdx += Dx;
   *pdy += Dy;
   *prz += Rz;
}

void CPointLoad::GetOriginForces(Float64 Length,Float64 Angle,Float64* pFx,Float64* pFy,Float64* pMz)
{
   Float64 La;
   Float64 Px,Py,Mo; // force or moment per unit length

   GetRealLoadLocation(Length, &La);

   GetLoadComponents(Angle,&Px,&Py,&Mo);

   *pFx = Px;
   *pFy = Py;
   *pMz = Mo + Py*La;
}

void CPointLoad::GetLoadComponents(Float64 Angle,Float64* pPx,Float64* pPy,Float64* pMz)
{
  // Fx component
  if (m_Orientation == lotGlobal || m_Orientation == lotGlobalProjected)
  {
     *pPx =  m_Fx*cos(Angle);
     *pPy =  -m_Fx*sin(Angle);
  }
  else
  {
     *pPx = m_Fx;
     *pPy = 0;
  }

   // Fy component
  if (m_Orientation == lotGlobal || m_Orientation == lotGlobalProjected)
  {
     *pPx += m_Fy*sin(Angle);
     *pPy += m_Fy*cos(Angle);
  }
  else
  {
     *pPy += m_Fy;
  }

  // Mz component
  *pMz = m_Mz;
}

void CPointLoad::GetRealLoadLocation(Float64 length, Float64* pLoc) const
{
   ATLASSERT(length>=-1.0);

   Float64 loc = CMember::GetRealLocation(length, m_Location);

   if (loc==-1.0)
   {
      // we're in errorland
      if (m_Location<0.0)
      {
         // fractional error
         ATLASSERT(m_Location>=-1.0); // interface should be blocking this
         THROW_IDS(IDS_E_FRACTIONAL_VALUE_OUT_OF_RANGE, FEM2D_E_FRACTIONAL_VALUE_OUT_OF_RANGE, IDH_E_FRACTIONAL_VALUE_OUT_OF_RANGE);
      }
      else
      {
         // explicit location error
         THROW_IDS(IDS_E_POINT_LOAD_OFF_GIRDER_END, FEM2D_E_POINT_LOAD_OFF_GIRDER_END, IDH_E_POINT_LOAD_OFF_GIRDER_END);
      }
   }

   *pLoc = loc;
}

STDMETHODIMP CPointLoad::get_Loading(LoadCaseIDType *pVal)
{
   CHECK_RETVAL(pVal);
	ATLASSERT(m_pLoading!=0);

   LoadCaseIDType id;
   m_pLoading->get_ID(&id);
   *pVal = id;

	return S_OK;
}
