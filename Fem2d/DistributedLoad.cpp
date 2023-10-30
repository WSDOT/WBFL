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
// DistributedLoad.cpp : Implementation of CDistributedLoad
#include "stdafx.h"
#include "DistributedLoad.h"
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
                          m_pModel->OnDistributedLoadChanged(this, Loadingid);

/////////////////////////////////////////////////////////////////////////////
// CDistributedLoad

STDMETHODIMP CDistributedLoad::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IFem2dDistributedLoad
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

void CDistributedLoad::Init(IFem2dModel* pParent, ModelEvents* pEvents, IFem2dLoading* pLoading, LoadIDType ID, MemberIDType memberID, Fem2dLoadDirection direction, Float64 startLocation, Float64 endLocation, Float64 wStart, Float64 wEnd, Fem2dLoadOrientation orientation)
{
   ATLASSERT(pLoading!=0);
   CheckLoadOrientation(orientation);

   InitParent(pParent); // CCircularChild implementation

   m_pModel = pEvents;  //  C++ model event handlers
   m_pLoading = pLoading;
   m_ID = ID;
   m_MemberID = memberID;
   m_Direction= direction;
   m_Orientation = orientation;
   m_StartLocation = startLocation;
   m_EndLocation = endLocation;
   m_WEnd = wEnd;
   m_WStart = wStart;
}

static const Float64 MY_VER=1.0;

STDMETHODIMP CDistributedLoad::Load(/*[in]*/ IStructuredLoad2 *pload)
{
   HRESULT hr;
   hr = pload->BeginUnit(CComBSTR("DistributedLoad"));
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

//		if ((Fem2dLoadOrientation)varlong.lVal == lotGlobal)
//         m_Orientation = lotGlobal;
//		else if ((Fem2dLoadOrientation)varlong.lVal == lotMember)
//         m_Orientation = lotMember;
//      else if ((Fem2dLoadOrientation)varlong.lVal == lotGlobalProjected)
//         m_Orientation = lotGlobalProjected;
//      else
//      {
//         ATLASSERT(false); // invalid orientation was written
//         return STRLOAD_E_INVALIDFORMAT;
//      }

      hr = pload->get_Property(CComBSTR("Direction"),&varlong);
      if (FAILED(hr))
         return hr;

      m_Direction = (Fem2dLoadDirection)varlong.lVal;
//		if ((long)varlong==(long)ldFx)
//         m_Direction = ldFx;
//		else if ((long)varlong==(long)ldFy)
//         m_Direction = ldFy;
//      else
//      {
//         ATLASSERT(false); // invalid direction was written
//         return STRLOAD_E_INVALIDFORMAT;
//      }

      CComVariant vardbl;
      vardbl.vt = VT_R8;
      hr = pload->get_Property(CComBSTR("StartLocation"),&vardbl);
      if (FAILED(hr))
         return hr;

      m_StartLocation = vardbl.dblVal;

      hr = pload->get_Property(CComBSTR("EndLocation"),&vardbl);
      if (FAILED(hr))
         return hr;

      m_EndLocation = vardbl.dblVal;

      hr = pload->get_Property(CComBSTR("WStart"),&vardbl);
      if (FAILED(hr))
         return hr;

      m_WStart = vardbl.dblVal;

      hr = pload->get_Property(CComBSTR("WEnd"),&vardbl);
      if (FAILED(hr))
         return hr;

      m_WEnd = vardbl.dblVal;
   }

   VARIANT_BOOL eb;
   hr = pload->EndUnit(&eb);
   if (FAILED(hr))
      return hr;

   if (eb!=VARIANT_TRUE)
      return STRLOAD_E_INVALIDFORMAT;

   return S_OK;
}

STDMETHODIMP CDistributedLoad::Save(/*[in]*/ IStructuredSave2 *psave)
{
   HRESULT hr;
   hr = psave->BeginUnit(CComBSTR("DistributedLoad"), MY_VER);
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

      hr = psave->put_Property(CComBSTR("Direction"),CComVariant((long)m_Direction));
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("StartLocation"),CComVariant(m_StartLocation));
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("EndLocation"),CComVariant(m_EndLocation));
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("WStart"),CComVariant(m_WStart));
      if (FAILED(hr))
         return hr;

      hr = psave->put_Property(CComBSTR("WEnd"),CComVariant(m_WEnd));
      if (FAILED(hr))
         return hr;
   }

   hr = psave->EndUnit();
   if (FAILED(hr))
      return hr;

   return S_OK;
}



STDMETHODIMP CDistributedLoad::get_ID(LoadIDType *pVal)
{
   CHECK_RETVAL(pVal);
   ATLASSERT(m_pModel!=0);
	*pVal = m_ID;

	return S_OK;
}

STDMETHODIMP CDistributedLoad::get_MemberID(MemberIDType *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_MemberID;

	return S_OK;
}

STDMETHODIMP CDistributedLoad::put_MemberID(MemberIDType newVal)
{
   if (m_MemberID != newVal)
   {
	   m_MemberID = newVal;
      ON_LOAD_CHANGED()
   }
	return S_OK;
}

STDMETHODIMP CDistributedLoad::get_Orientation(Fem2dLoadOrientation *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_Orientation;

	return S_OK;
}

STDMETHODIMP CDistributedLoad::put_Orientation(Fem2dLoadOrientation newVal)
{
   if( m_Orientation != newVal)
   {

      try
      {
         CheckLoadOrientation(newVal);
	      m_Orientation = newVal;

         ON_LOAD_CHANGED()
      }
      catch (CComException& re)
      {
         CComBSTR msg(re.GetErrorMessage());
         HRESULT hr = re.GetHresult();
         DWORD helpid = re.GetHelpID();
         return CComCoClass<CDistributedLoad,&CLSID_Fem2dDistributedLoad>::Error(msg, helpid, GetHelpFile(), IID_IFem2dModel, hr);
      }
      catch (...)
      {
         ATLASSERT(false);
         return E_FAIL;
      }
   }

	return S_OK;
}

STDMETHODIMP CDistributedLoad::get_Direction(Fem2dLoadDirection *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_Direction;

	return S_OK;
}

STDMETHODIMP CDistributedLoad::put_Direction(Fem2dLoadDirection newVal)
{
   if (m_Direction != newVal)
   {
	   m_Direction = newVal;

      ON_LOAD_CHANGED()
   }
	return S_OK;
}


STDMETHODIMP CDistributedLoad::get_StartLocation(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_StartLocation;

	return S_OK;
}

STDMETHODIMP CDistributedLoad::put_StartLocation(Float64 newVal)
{
   if (newVal < -1.0)
      return CComCoClass<CDistributedLoad,&CLSID_Fem2dDistributedLoad>::Error(IDS_E_INVALID_DIST_LOAD_LOCATION, IDH_E_INVALID_DIST_LOAD_LOCATION, GetHelpFile(), IID_IFem2dPointLoad, FEM2D_E_INVALID_DIST_LOAD_LOCATION);

   if (m_StartLocation != newVal)
   {
	   m_StartLocation = newVal;
      ON_LOAD_CHANGED()
   }
	return S_OK;
}

STDMETHODIMP CDistributedLoad::get_EndLocation(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_EndLocation;

	return S_OK;
}

STDMETHODIMP CDistributedLoad::put_EndLocation(Float64 newVal)
{
   if (newVal < -1.0)
      return CComCoClass<CDistributedLoad,&CLSID_Fem2dDistributedLoad>::Error(IDS_E_INVALID_DIST_LOAD_LOCATION, IDH_E_INVALID_DIST_LOAD_LOCATION, GetHelpFile(), IID_IFem2dPointLoad, FEM2D_E_INVALID_DIST_LOAD_LOCATION);

   if (m_EndLocation != newVal)
   {
	   m_EndLocation = newVal;
      ON_LOAD_CHANGED()
   }
	return S_OK;
}

STDMETHODIMP CDistributedLoad::get_WStart(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_WStart;

	return S_OK;
}

STDMETHODIMP CDistributedLoad::put_WStart(Float64 newVal)
{
   if (m_WStart != newVal)
   {
	   m_WStart = newVal;
      ON_LOAD_CHANGED()
   }
	return S_OK;
}

STDMETHODIMP CDistributedLoad::get_WEnd(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
	*pVal = m_WEnd;

	return S_OK;
}

STDMETHODIMP CDistributedLoad::put_WEnd(Float64 newVal)
{
   if (m_WEnd!=newVal)
   {
	   m_WEnd = newVal;
      ON_LOAD_CHANGED()
   }
	return S_OK;
}

void CDistributedLoad::GetForceVector(long leftBC,long rightBC,Float64 Length,Float64 Angle,Float64 *vector)
{
   Float64 La, Lb;
   Float64 WxStart,WyStart,WxEnd,WyEnd;

   GetLocalData(Angle, Length, &La, &Lb, &WxStart, &WyStart, &WxEnd, &WyEnd);

   // Initialize the force vector
   vector[0] = 0;
   vector[1] = 0;
   vector[2] = 0;
   vector[3] = 0;
   vector[4] = 0;
   vector[5] = 0;

   Float64 Fx1,Fy1,Mz1;
   Float64 Fx2,Fy2,Mz2;
   if (WxStart!=0.0 || WxEnd!=0.0)
   {
      TrapezoidalLdBeam Pbeam(WxStart,WxEnd,La,Lb,Beam::ForceX,Length,1,1,leftBC,rightBC);
      Pbeam.GetReactions(Fx1,Fy1,Mz1,Fx2,Fy2,Mz2);
      vector[0] += Fx1;
      vector[1] += Fy1;
      vector[2] += Mz1;
      vector[3] += Fx2;
      vector[4] += Fy2;
      vector[5] += Mz2;
   }

   if (WyStart!=0.0 || WyEnd!=0.0)
   {
      TrapezoidalLdBeam Pbeam(WyStart,WyEnd,La,Lb,Beam::ForceY,Length,1,1,leftBC,rightBC);
      Pbeam.GetReactions(Fx1,Fy1,Mz1,Fx2,Fy2,Mz2);
      vector[0] += Fx1;
      vector[1] += Fy1;
      vector[2] += Mz1;
      vector[3] += Fx2;
      vector[4] += Fy2;
      vector[5] += Mz2;
   }
}


void CDistributedLoad::GetDispVector(long leftBC,long rightBC,Float64 Length,Float64 Angle,
                                     Float64 EA,Float64 EI,
                                     Float64 *vector)
{
   Float64 La, Lb;
   Float64 WxStart,WyStart,WxEnd,WyEnd;

   GetLocalData(Angle, Length, &La, &Lb, &WxStart, &WyStart, &WxEnd, &WyEnd);

   // Initialize the vector
   vector[0] = 0;
   vector[1] = 0;
   vector[2] = 0;
   vector[3] = 0;
   vector[4] = 0;
   vector[5] = 0;

   Float64 Dx1,Dy1,Rz1;
   Float64 Dx2,Dy2,Rz2;
   if (WxStart!=0.0 || WxEnd!=0.0)
   {
      TrapezoidalLdBeam Pbeam(WxStart,WxEnd,La,Lb,Beam::ForceX,Length,EA,EI,leftBC,rightBC);
      Pbeam.GetDeflections(Dx1,Dy1,Rz1,Dx2,Dy2,Rz2);
      vector[0] += Dx1;
      vector[1] += Dy1;
      vector[2] += Rz1;
      vector[3] += Dx2;
      vector[4] += Dy2;
      vector[5] += Rz2;
   }

   if (WyStart!=0.0 || WyEnd!=0.0)
   {
      TrapezoidalLdBeam Pbeam(WyStart,WyEnd,La,Lb,Beam::ForceY,Length,EA,EI,leftBC,rightBC);
      Pbeam.GetDeflections(Dx1,Dy1,Rz1,Dx2,Dy2,Rz2);
      vector[0] += Dx1;
      vector[1] += Dy1;
      vector[2] += Rz1;
      vector[3] += Dx2;
      vector[4] += Dy2;
      vector[5] += Rz2;
   }
}

void CDistributedLoad::GetInternalForces(Float64 x,Float64 Length,Float64 Angle,Fem2dMbrFaceType face,Float64* pFx,Float64* pFy,Float64* pMz)
{

   Float64 La, Lb;
   Float64 Wxa,Wya,Wxb,Wyb;
   GetLocalData(Angle, Length, &La, &Lb, &Wxa, &Wya, &Wxb, &Wyb);

   if (  La==Lb ||
         La==0.0 && Lb==0.0 ||
        ((face==mftLeft)  && (x<=La)) ||
        ((face==mftRight) && (x>=Lb)) )
   {
      // Load has no contribution at this location
      *pFx = 0;
      *pFy = 0;
      *pMz = 0;
      return;
   }

   if ( face == mftLeft)
   {
      if (x<Lb)
      {
         // get uniform load values at x
         Wxb = Wxa + (Wxb-Wxa)/(Lb-La)*(x-La);
         Wyb = Wya + (Wyb-Wya)/(Lb-La)*(x-La);
         Lb=x;
      }

      *pFx = (Wxa+Wxb)/2.*(Lb - La);
      *pFy = (Wya+Wyb)/2.*(Lb - La);
      if (*pFy!=0.0)
      {
         // moment arm to resultant force from left end
         Float64 ma = La + 2.*(Wyb/3. + Wya/6.)*(Lb-La)/(Wya+Wyb);
         *pMz = (*pFy)*(ma-x);
      }
      else
      {
         *pMz=0.0;
      }
   }
   else if ( face == mftRight)
   {
      if (x>La)
      {
      // get uniform load values at x
         Wxa = Wxa + (Wxb-Wxa)/(Lb-La)*(x-La);
         Wya = Wya + (Wyb-Wya)/(Lb-La)*(x-La);
         La = x;
      }

      *pFx = (Wxb+Wxa)/2.*(Lb - La);
      *pFy = (Wyb+Wya)/2.*(Lb - La);
      if (*pFy!=0.0)
      {
         // moment arm to resultant force from left end
         Float64 ma = La + 2.*(Wyb/3. + Wya/6.)*(Lb-La)/(Wya+Wyb);
         *pMz = (*pFy)*(ma-x);
      }
      else
      {
         *pMz = 0.0;
      }
   }
   else
      ATLASSERT(false); 
}

void CDistributedLoad::GetDeflection(Float64 x,long leftBC,long rightBC,Float64 Length,Float64 Angle,
                                       Float64 EA,Float64 EI,
                                       Float64* pdx,Float64* pdy,Float64* prz)

{
   *pdx = 0.0;
   *pdy = 0.0;
   *prz = 0.0;

   Float64 La, Lb;
   Float64 WxStart,WyStart,WxEnd,WyEnd;
   GetLocalData(Angle,Length, &La, &Lb, &WxStart, &WyStart, &WxEnd, &WyEnd);

   if (WxStart!=0.0 || WxEnd!=0.0)
   {
      TrapezoidalLdBeam Pbeam(WxStart,WxEnd,La,Lb,Beam::ForceX,Length,EA,EI,leftBC,rightBC);
      Pbeam.GetDeflection(x, *pdx, *pdy, *prz);
   }

   if (WyStart!=0.0 || WyEnd!=0.0)
   {
      Float64 dx, dy, rz;
      TrapezoidalLdBeam Pbeam(WyStart,WyEnd,La,Lb,Beam::ForceY,Length,EA,EI,leftBC,rightBC);
      Pbeam.GetDeflection(x, dx, dy, rz);
      *pdx += dx;
      *pdy += dy;
      *prz += rz;
   }
}

void CDistributedLoad::GetOriginForces(Float64 Length,Float64 Angle,Float64* pFx,Float64* pFy,Float64* pMz)
{
   Float64 La, Lb;
   Float64 Wxa,Wya,Wxb,Wyb;
   GetLocalData(Angle, Length, &La, &Lb, &Wxa, &Wya, &Wxb, &Wyb);

   if (  La==Lb || (m_WEnd == 0.0 && m_WStart == 0.0)) 
   {
      *pFx = 0;
      *pFy = 0;
      *pMz = 0;
      return;
   }

   *pFx = (Wxa+Wxb)/2.*(Lb - La);
   *pFy = (Wya+Wyb)/2.*(Lb - La);
   if (*pFy!=0.0)
   {
      // moment arm to resultant force from left end
      Float64 ma = La + 2.*(Wyb/3. + Wya/6.)*(Lb-La)/(Wya+Wyb);
      *pMz = (*pFy)*ma;
   }
   else
   {
      if (fabs(Wya) == fabs(Wyb) && !IsZero(Wya) && !IsZero(Wyb))
      {
         // this happens when the Wa and Wb have opposite signs but have equal magnitude
         // the moment effect is not zero... treat the loading as two triangular loads with
         // the zero load point being at La + (Lb-La)/2
         ATLASSERT(::BinarySign(Wya) != ::BinarySign(Wyb));
         Float64 ma = (La + (Lb - La)/6.)*Wya*(Lb - La) / 4.;
         Float64 mb = (La + 5.*(Lb - La)/6.)*Wyb*(Lb - La) / 4.;
         *pMz = ma + mb;
      }
      else
      {
         *pMz = 0.0;
      }
   }
}

void CDistributedLoad::GetLocalData(Float64 Angle, Float64 length, Float64* pStartLoc, Float64* pEndLoc, Float64* pWxStart,Float64* pWyStart,Float64* pWxEnd,Float64* pWyEnd)
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
         CComBSTR msg(CreateErrorMsg2(IDS_E_DIST_LOAD_OFF_GIRDER_END, m_ID,lid));
         THROW_MSG(msg, FEM2D_E_DIST_LOAD_OFF_GIRDER_END, IDH_E_DIST_LOAD_OFF_GIRDER_END);
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
         CComBSTR msg(CreateErrorMsg2(IDS_E_DIST_LOAD_OFF_GIRDER_END, m_ID,lid));
         THROW_MSG(msg, FEM2D_E_DIST_LOAD_OFF_GIRDER_END, IDH_E_DIST_LOAD_OFF_GIRDER_END);
      }
   }
   

  // Local force components
  Float64 wxend, wxstart, wyend, wystart;
  if (m_Orientation == lotGlobal  || m_Orientation == lotGlobalProjected)
  {
     Float64 ca = cos(Angle);
     Float64 sa = sin(Angle);

     // factor for projection
     Float64 wend, wstart;
     if (m_Orientation == lotGlobalProjected)
     {
        if (m_Direction== loadDirFx)
        {
           wend   = m_WEnd  *fabs(sa);
           wstart = m_WStart*fabs(sa);
        }
        else if (m_Direction== loadDirFy)
        {
           wend   = m_WEnd  *fabs(ca);
           wstart = m_WStart*fabs(ca);
        }
        else
           ATLASSERT(false); // new direction we don't know about?
     }
     else
     {
        wend   = m_WEnd;
        wstart = m_WStart;
     }

     // perform rotation into member coords
     if (m_Direction == loadDirFx)
     {
        wxend   =  wend*ca;
        wyend   = -wend*sa;
        wxstart =  wstart*ca;
        wystart = -wstart*sa;
     }
     else if (m_Direction == loadDirFy)
     {
        wxend   = wend*sa;
        wyend   = wend*ca;
        wxstart = wstart*sa;
        wystart = wstart*ca;
     }
     else
        ATLASSERT(false); // new direction we don't know about?
  }
  else
  {
     if (m_Direction == loadDirFx)
     {
        wxend   =  m_WEnd;
        wyend   =  0.0;
        wxstart =  m_WStart;
        wystart =  0.0;
     }
     else if (m_Direction == loadDirFy)
     {
        wxend   = 0.0;
        wyend   = m_WEnd;
        wxstart = 0.0;
        wystart = m_WStart;
     }
     else
        ATLASSERT(false); // new direction we don't know about?
  }
   
  // flip values if user entered start>end
  if (endloc < startloc)
  {
     *pStartLoc= endloc;
     *pEndLoc  = startloc;

     *pWxEnd   = wxstart;
     *pWyEnd   = wystart;
     *pWxStart = wxend;
     *pWyStart = wyend;
  }
  else
  {
     *pStartLoc= startloc;
     *pEndLoc  = endloc;

     *pWxEnd   = wxend;
     *pWyEnd   = wyend;
     *pWxStart = wxstart;
     *pWyStart = wystart;
  }
}


STDMETHODIMP CDistributedLoad::get_Loading(LoadCaseIDType *pVal)
{
   CHECK_RETVAL(pVal);
	ATLASSERT(m_pLoading!=0);

   LoadCaseIDType id;
   m_pLoading->get_ID(&id);
   *pVal = id;

	return S_OK;
}
