///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
// Copyright © 1999-2010  Washington State Department of Transportation
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

// Alignment.cpp : Implementation of CAlignment
#include "stdafx.h"
#include "WBFLCogo.h"
#include "Alignment.h"
#include "Path.h"
#include "CogoHelpers.h"
#include "PointFactory.h"
#include "Station.h"
#include <MathEx.h>
#include <Float.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAlignment
HRESULT CAlignment::FinalConstruct()
{
   CComObject<CPath>* pPath;
   CComObject<CPath>::CreateInstance(&pPath);
   CComPtr<IPath> path = pPath;
   PutPath(path);

   m_RefStation = 0.0;

   return S_OK;
}

void CAlignment::FinalRelease()
{
   PutPath(NULL);
}

void CAlignment::PutPath(IPath* pPath)
{
   if (m_Path)
   {
      InternalAddRef();
      AtlUnadvise(m_Path,IID_IPathEvents,m_dwPathCookie);
   }

   m_Path = pPath;

   if ( m_Path )
   {
      HRESULT hr = m_Path.Advise(GetUnknown(),IID_IPathEvents,&m_dwPathCookie);
      ATLASSERT(SUCCEEDED(hr));
      InternalRelease();
   }
}

STDMETHODIMP CAlignment::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IAlignment,
      &IID_IStructuredStorage2,
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
      if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CAlignment::get_RefStation(IStation* *station)
{
   CHECK_RETOBJ(station);
   CComObject<CStation>* pStation;
   CComObject<CStation>::CreateInstance(&pStation);

   pStation->put_Value(m_RefStation);

   (*station) = pStation;
   (*station)->AddRef();

   return S_OK;
}

STDMETHODIMP CAlignment::put_RefStation(VARIANT varStation)
{
   CComPtr<IStation> objStation;
   HRESULT hr = cogoUtil::StationFromVariant(varStation,&objStation);
   if ( FAILED(hr) )
      return hr;

   Float64 station;
   objStation->get_Value(&station);

   if ( !IsEqual(m_RefStation,station) )
   {
      m_RefStation = station;
      Fire_OnPathChanged(this);
   }

	return S_OK;
}

STDMETHODIMP CAlignment::LocatePoint( VARIANT varStation, OffsetMeasureType offsetMeasure, Float64 offset, VARIANT varDir, IPoint2d* *newPoint)
{
   Float64 distance;
   HRESULT hr = StationToPathDistance(varStation,&distance);
   if ( FAILED(hr) )
      return hr;

   return m_Path->LocatePoint(distance,offsetMeasure,offset,varDir,newPoint);
}

STDMETHODIMP CAlignment::LocateCrownPoint2D(VARIANT varStation, VARIANT varDir,IPoint2d* *newPoint)
{
   CHECK_RETOBJ(newPoint);

   HRESULT hr = S_OK;
   CComPtr<IDirection> dir;
   hr = cogoUtil::DirectionFromVariant(varDir,&dir);
   if ( FAILED(hr) )
      return hr;

   Float64 dirValue;
   dir->get_Value(&dirValue);

   CComPtr<IPath> crown_point_path;
   CComPtr<IProfile> profile;
   m_Path->get_Profile(&profile);
   if ( profile )
   {
      CComPtr<ICrossSectionCollection> cross_sections;
      profile->get_CrossSections(&cross_sections);
      cross_sections->get_CrownPointPath(&crown_point_path);
   }

   CComPtr<IPoint2d> point_on_alignment;
   LocatePoint(varStation,omtAlongDirection,0.00,varDir,&point_on_alignment);
   if ( crown_point_path == NULL )
   {
      (*newPoint) = point_on_alignment;
      (*newPoint)->AddRef();
      return S_OK;
   }

   CComPtr<IVector2d> v;
   v.CoCreateInstance(CLSID_Vector2d);
   v->put_Direction(dirValue);
   CComPtr<ILine2d> line;
   line.CoCreateInstance(CLSID_Line2d);
   line->SetExplicit(point_on_alignment,v);
   return crown_point_path->Intersect(line,point_on_alignment,newPoint);
}

STDMETHODIMP CAlignment::LocateCrownPoint3D(VARIANT varStation, VARIANT varDir, IPoint3d* *newPoint)
{
   CComPtr<IPoint2d> pnt2d;
   HRESULT hr = LocateCrownPoint2D(varStation,varDir,&pnt2d);
   if ( FAILED(hr) )
      return hr;

   CComPtr<IStation> station;
   Float64 offset;
   Offset(pnt2d,&station,&offset);

   Float64 elevation;
   CComPtr<IProfile> profile;
   m_Path->get_Profile(&profile);
   profile->Elevation(CComVariant(station),offset,&elevation);

   CComPtr<IPoint3d> pnt3d;
   pnt3d.CoCreateInstance(CLSID_Point3d);
   
   Float64 x,y;
   pnt2d->Location(&x,&y);

   pnt3d->Move(x,y,elevation);

   (*newPoint) = pnt3d;
   (*newPoint)->AddRef();

   return S_OK;
}

STDMETHODIMP CAlignment::Bearing(VARIANT varStation,IDirection* *dir)
{
   Float64 distance;
   HRESULT hr = StationToPathDistance(varStation,&distance);
   if ( FAILED(hr) )
      return hr;

   return m_Path->Bearing(distance,dir);
}

STDMETHODIMP CAlignment::Normal(VARIANT varStation,IDirection* *dir)
{
   Float64 distance;
   HRESULT hr = StationToPathDistance(varStation,&distance);
   if ( FAILED(hr) )
      return hr;

   return m_Path->Normal(distance,dir);
}

STDMETHODIMP CAlignment::Offset(IPoint2d* point,IStation* *station,Float64* offset)
{
   CHECK_IN(point);
   CHECK_RETOBJ(station);
   CHECK_RETVAL(offset);

   Float64 location;
   HRESULT hr = m_Path->Offset(point,&location,offset);
   if ( FAILED(hr) )
      return hr;

   location += m_RefStation;
   hr = CreateStation(location,station);
   ATLASSERT(SUCCEEDED(hr));

   return S_OK;
}


STDMETHODIMP CAlignment::CreateSubPath(VARIANT varStartStation,VARIANT varEndStation,IPath** path)
{
   Float64 start;
   HRESULT hr = StationToPathDistance(varStartStation,&start);
   if ( FAILED(hr) )
      return hr;

   Float64 end;
   hr = StationToPathDistance(varEndStation,&end);
   if ( FAILED(hr) )
      return hr;

   hr = CreateSubPath(start,end,path);
   if ( FAILED(hr) )
      return hr;

   CComPtr<IPoint2d> pntStart;
   LocatePoint(varStartStation,omtAlongDirection, 0.00,CComVariant(0.00),&pntStart);

   CComQIPtr<IAlignment> alignment(*path);
   alignment->InsertEx(0,pntStart);
   alignment->put_RefStation(varStartStation);

   return S_OK;
}

STDMETHODIMP CAlignment::Clone(IPath* *clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CAlignment>* pClone;
   CComObject<CAlignment>::CreateInstance(&pClone);

   (*clone) = pClone;
   (*clone)->AddRef();

   pClone->put_RefStation(CComVariant(m_RefStation));

   CComPtr<IPath> clone_path;
   m_Path->Clone(&clone_path);
   pClone->PutPath(clone_path);

   return S_OK;
}

STDMETHODIMP CAlignment::CreateParallelPath(Float64 offset,IPath** path)
{
   CHECK_RETOBJ(path);

   CComObject<CAlignment>* pClone;
   CComObject<CAlignment>::CreateInstance(&pClone);

   (*path) = pClone;
   (*path)->AddRef();

   pClone->put_RefStation(CComVariant(m_RefStation));

   CComPtr<IPath> clone_path;
   m_Path->CreateParallelPath(offset,&clone_path);
   pClone->PutPath(clone_path);

   return S_OK;
}

STDMETHODIMP CAlignment::CreateSubPath(Float64 start,Float64 end,IPath** path)
{
   CHECK_RETOBJ(path);

   CComObject<CAlignment>* pSubAlignment;
   CComObject<CAlignment>::CreateInstance(&pSubAlignment);

   (*path) = pSubAlignment;
   (*path)->AddRef();

   CComPtr<IPath> sub_path;
   HRESULT hr = m_Path->CreateSubPath(start,end,&sub_path);
   if ( FAILED(hr) )
      return hr;

   pSubAlignment->PutPath(sub_path);

   return S_OK;
}

STDMETHODIMP CAlignment::CreateConnectedPath(IPath** path)
{
   CHECK_RETOBJ(path);

   CComObject<CAlignment>* pClone;
   CComObject<CAlignment>::CreateInstance(&pClone);

   (*path) = pClone;
   (*path)->AddRef();

   pClone->put_RefStation(CComVariant(m_RefStation));

   CComPtr<IPath> clone_path;
   HRESULT hr = m_Path->CreateConnectedPath(&clone_path);
   if ( FAILED(hr) )
      return hr;

   pClone->PutPath(clone_path);

   return S_OK;
}

STDMETHODIMP CAlignment::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

// IStructuredStorage2
STDMETHODIMP CAlignment::Save(IStructuredSave2* pSave)
{
   pSave->BeginUnit(CComBSTR("Alignment"),1.0);
   pSave->put_Property(CComBSTR("RefStation"),CComVariant(m_RefStation));

   CComPtr<IStructuredStorage2> ss;
   m_Path->get_StructuredStorage(&ss);
   ATLASSERT(ss != NULL);

   ss->Save(pSave);

   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CAlignment::Load(IStructuredLoad2* pLoad)
{
   CComVariant var;
   pLoad->BeginUnit(CComBSTR("Alignment"));

   pLoad->get_Property(CComBSTR("RefStation"),&var);
   m_RefStation = var.dblVal;

   CComPtr<IStructuredStorage2> ss;
   m_Path->get_StructuredStorage(&ss);
   ATLASSERT(ss != NULL);
   ss->Load(pLoad);

   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   return S_OK;
}


//////////////////////////////////////////////////////////
// Helpers
HRESULT CAlignment::CreateStation(Float64 location,IStation** pStation)
{
   CComObject<CStation>* pObjStation;
   CComObject<CStation>::CreateInstance(&pObjStation);
   pObjStation->put_Value(location);
   (*pStation) = pObjStation;
   (*pStation)->AddRef();

   return S_OK;
}

HRESULT CAlignment::StationToPathDistance(VARIANT varStation,Float64* distance)
{
   CComPtr<IStation> objStation;
   HRESULT hr = cogoUtil::StationFromVariant(varStation,&objStation);
   if ( FAILED(hr) )
      return hr;

   Float64 station;
   objStation->get_Value(&station);

   (*distance) = station - m_RefStation;
   return S_OK;
}
