///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
// Copyright © 1999-2018  Washington State Department of Transportation
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
#include "Profile.h"
#include <WBFLCogo\CogoHelpers.h>
#include "PointFactory.h"
#include "Station.h"
#include "StationEquationCollection.h"
#include <Float.h>
#include <cctype>

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

   CComObject<CProfile>* pProfile;
   CComObject<CProfile>::CreateInstance(&pProfile);
   m_Profile = pProfile;

   HRESULT hr = m_Profile.Advise(GetUnknown(),IID_IProfileEvents,&m_dwProfileCookie);
   ATLASSERT(SUCCEEDED(hr));
   InternalRelease();

   pProfile->putref_Alignment(this);

   CComObject<CStationEquationCollection>* pEquations;
   CComObject<CStationEquationCollection>::CreateInstance(&pEquations);
   m_Equations = pEquations;

   hr = m_Equations.Advise(GetUnknown(),IID_IStationEquationCollectionEvents,&m_dwEquationsCookie);
   ATLASSERT(SUCCEEDED(hr));
   InternalRelease();

   pEquations->putref_Alignment(this);

   m_RefStation = 0.0;

   return S_OK;
}

void CAlignment::FinalRelease()
{
   InternalAddRef();
   AtlUnadvise(m_Profile,IID_IProfileEvents,m_dwProfileCookie);

   InternalAddRef();
   AtlUnadvise(m_Equations,IID_IStationEquationCollectionEvents,m_dwEquationsCookie);

   PutPath(nullptr);
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
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
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
   HRESULT hr = cogoUtil::StationFromVariant(varStation,true,&objStation);
   if ( FAILED(hr) )
      return hr;

   Float64 station;
   objStation->get_Value(&station);

   if ( !IsEqual(m_RefStation,station) )
   {
      m_RefStation = station;
      Fire_OnAlignmentChanged(this);
   }

	return S_OK;
}

STDMETHODIMP CAlignment::get_Profile(IProfile **pVal)
{
   CHECK_RETOBJ(pVal);
   (*pVal) = m_Profile;
   (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CAlignment::putref_Profile(IProfile* pVal)
{
   CHECK_IN(pVal);

   InternalAddRef();
   AtlUnadvise(m_Profile,IID_IProfileEvents,m_dwProfileCookie);

   m_Profile = pVal;

   m_Profile.Advise(GetUnknown(),IID_IProfileEvents,&m_dwProfileCookie);
   InternalRelease();

   Fire_OnProfileChanged(m_Profile);
   return S_OK;
}

STDMETHODIMP CAlignment::get_StationEquations(IStationEquationCollection* *pVal)
{
   CHECK_RETOBJ(pVal);
   (*pVal) = m_Equations;
   (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CAlignment::putref_StationEquations(IStationEquationCollection* pVal)
{
   CHECK_IN(pVal);

   InternalAddRef();
   AtlUnadvise(m_Equations,IID_IStationEquationCollectionEvents,m_dwProfileCookie);

   m_Equations = pVal;

   m_Equations.Advise(GetUnknown(),IID_IStationEquationCollectionEvents,&m_dwProfileCookie);
   InternalRelease();

   Fire_OnStationEquationsChanged(m_Equations);
   return S_OK;
}

STDMETHODIMP CAlignment::LocatePoint( VARIANT varStation, OffsetMeasureType offsetMeasure, Float64 offset, VARIANT varDir, IPoint2d* *newPoint)
{
   Float64 distance;
   HRESULT hr = StationToPathDistance(varStation,&distance);
   if (FAILED(hr))
   {
      return hr;
   }

   // if direction is nullptr, then assume offset direction is normal to the alignment
   if (varDir.vt == VT_UNKNOWN && varDir.punkVal == nullptr)
   {
      CComPtr<IDirection> dir;
      Normal(varStation, &dir);
      dir.QueryInterface(&varDir.punkVal);
   }

   return m_Path->LocatePoint(distance,offsetMeasure,offset,varDir,newPoint);
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

STDMETHODIMP CAlignment::GetDirection(VARIANT varStation, BSTR bstrOrientation,IDirection** direction)
{
   USES_CONVERSION;

   CHECK_RETOBJ(direction);

   CComPtr<IStation> objStation;
   HRESULT hr = cogoUtil::StationFromVariant(varStation,false,&objStation);
   if ( FAILED(hr) )
      return hr;

   Float64 station;
   objStation->get_Value(&station);


   // Convert the orientation string to something we can work with
   // Make it upper case for easy conparison
   std::_tstring strOrientation(OLE2T(bstrOrientation));
   std::transform(strOrientation.begin(),strOrientation.end(),strOrientation.begin(),(int(*)(int))std::toupper);


   // Get the alignment normal
   CComPtr<IDirection> normal;
   Normal(varStation,&normal); // This is the normal to the right

   // We want the normal to the left... Increment by 180 degrees
   normal->IncrementBy(CComVariant(M_PI));

   // process the orientation string
   if ( strOrientation.compare(_T("N")) == 0 || strOrientation.compare(_T("NORMAL")) == 0 )
   {
      // Normal to the alignment
      normal.CopyTo(direction);
   }
   else if (strOrientation[0] == _T('N') || strOrientation[0] == _T('S') )
   {
      // Defined by an explicit bearing
      CComPtr<IDirection> brg;
      brg.CoCreateInstance(CLSID_Direction);
      hr = brg->FromString(bstrOrientation);
      if ( FAILED(hr) )
         return hr;

      // if the bearing is to the right of the alignment, reverse it
      CComPtr<IDirection> align_dir;
      Bearing(varStation,&align_dir);

      CComPtr<IAngle> angle;
      brg->AngleBetween(align_dir,&angle);

      Float64 value;
      angle->get_Value(&value);

      // if the angle between is between 0 and 180, bearing is to the left
      if ( M_PI < value )
      {
         // bearing is to the right of the alignment.... increment by 180 degrees
         brg->IncrementBy(CComVariant(M_PI));
      }

      brg.CopyTo(direction);
   }
   else
   {
      CComPtr<IAngle> angle;
      angle.CoCreateInstance(CLSID_Angle);
      hr = angle->FromString(bstrOrientation);
      if ( FAILED(hr) )
         return hr;

      CComPtr<IDirection> brg;
      normal->Increment(CComVariant(angle),&brg);

      brg.CopyTo(direction);
   }

   return S_OK;
}

STDMETHODIMP CAlignment::DistanceBetweenStations(VARIANT station1,VARIANT station2,Float64* pDist)
{
   return m_Equations->Distance(station1,station2,pDist);
}

STDMETHODIMP CAlignment::CreateSubAlignment(VARIANT varStartStation,VARIANT varEndStation,IAlignment** ppAlignment)
{
   CHECK_RETOBJ(ppAlignment);

   Float64 start;
   HRESULT hr = StationToPathDistance(varStartStation,&start);
   if ( FAILED(hr) )
      return hr;

   Float64 end;
   hr = StationToPathDistance(varEndStation,&end);
   if ( FAILED(hr) )
      return hr;

   CComObject<CAlignment>* pAlignment;
   CComObject<CAlignment>::CreateInstance(&pAlignment);

   CComPtr<IPath> path;
   hr = m_Path->CreateSubPath(start,end,&path);
   if ( FAILED(hr) )
      return hr;

   (*ppAlignment) = pAlignment;
   (*ppAlignment)->AddRef();

   pAlignment->PutPath(path);
   pAlignment->put_RefStation(varStartStation);

   CComPtr<IProfile> cloneProfile;
   m_Profile->Clone(&cloneProfile);
   pAlignment->putref_Profile(cloneProfile);

   // Only copy the station equations that are within the range we are creating
   CComPtr<IStationEquationCollection> equations;
   pAlignment->get_StationEquations(&equations);
   CComPtr<IEnumStationEquations> pEnum;
   m_Equations->get__EnumStationEquations(&pEnum);
   CComPtr<IStationEquation> equation;
   ULONG nFetched;
   while ( pEnum->Next(1,&equation,&nFetched) != S_FALSE )
   {
      Float64 distance;
      equation->get_NormalizedValue(&distance);

      if ( ::InRange(start,distance,end) )
      {
         Float64 back, ahead;
         equation->GetEquation(&back,&ahead);
         
         CComPtr<IStationEquation> newEquation;
         equations->Add(back,ahead,&newEquation);
      }

      equation.Release();
   }


   // Need to add only those equations within the specified range

   CComPtr<IPoint2d> pntStart;
   LocatePoint(varStartStation,omtAlongDirection, 0.00,CComVariant(0.00),&pntStart);

   CollectionIndexType nElements;
   path->get_Count(&nElements);
   if ( nElements == 0 )
   {
      CComPtr<IPoint2d> pntEnd;
      LocatePoint(varEndStation,omtAlongDirection,0.00,CComVariant(0.00),&pntEnd);

      CComPtr<ILineSegment2d> lineSegment;
      lineSegment.CoCreateInstance(CLSID_LineSegment2d);
      lineSegment->ThroughPoints(pntStart,pntEnd);
      (*ppAlignment)->AddEx(lineSegment);
   }
   else
   {
      (*ppAlignment)->InsertEx(0,pntStart);
   }

   return S_OK;
}

STDMETHODIMP CAlignment::Clone(IAlignment* *clone)
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

   CComPtr<IProfile> cloneProfile;
   m_Profile->Clone(&cloneProfile);
   pClone->putref_Profile(cloneProfile);


   CComPtr<IStationEquationCollection> equations;
   pClone->get_StationEquations(&equations);

   CComPtr<IEnumStationEquations> pEnum;
   m_Equations->get__EnumStationEquations(&pEnum);
   CComPtr<IStationEquation> equation;
   ULONG nFetched;
   while ( pEnum->Next(1,&equation,&nFetched) != S_FALSE )
   {
      Float64 back, ahead;
      equation->GetEquation(&back,&ahead);
         
      CComPtr<IStationEquation> newEquation;
      equations->Add(back,ahead,&newEquation);

      equation.Release();
   }

   return S_OK;
}

STDMETHODIMP CAlignment::CreateParallelAlignment(Float64 offset,IAlignment** ppAlignment)
{
   CHECK_RETOBJ(ppAlignment);

   CComObject<CAlignment>* pClone;
   CComObject<CAlignment>::CreateInstance(&pClone);

   (*ppAlignment) = pClone;
   (*ppAlignment)->AddRef();

   pClone->put_RefStation(CComVariant(m_RefStation));

   CComPtr<IPath> clone_path;
   m_Path->CreateParallelPath(offset,&clone_path);
   pClone->PutPath(clone_path);

   CComPtr<IProfile> cloneProfile;
   m_Profile->Clone(&cloneProfile);
   pClone->putref_Profile(cloneProfile);


   CComPtr<IStationEquationCollection> equations;
   pClone->get_StationEquations(&equations);

   CComPtr<IEnumStationEquations> pEnum;
   m_Equations->get__EnumStationEquations(&pEnum);
   CComPtr<IStationEquation> equation;
   ULONG nFetched;
   while ( pEnum->Next(1,&equation,&nFetched) != S_FALSE )
   {
      Float64 back, ahead;
      equation->GetEquation(&back,&ahead);
         
      CComPtr<IStationEquation> newEquation;
      equations->Add(back,ahead,&newEquation);

      equation.Release();
   }

   return S_OK;
}

STDMETHODIMP CAlignment::CreateConnectedAlignment(IAlignment** ppAlignment)
{
   CHECK_RETOBJ(ppAlignment);

   CComObject<CAlignment>* pClone;
   CComObject<CAlignment>::CreateInstance(&pClone);

   (*ppAlignment) = pClone;
   (*ppAlignment)->AddRef();

   pClone->put_RefStation(CComVariant(m_RefStation));

   CComPtr<IPath> clone_path;
   HRESULT hr = m_Path->CreateConnectedPath(&clone_path);
   if ( FAILED(hr) )
      return hr;

   pClone->PutPath(clone_path);

   CComPtr<IProfile> cloneProfile;
   m_Profile->Clone(&cloneProfile);
   pClone->putref_Profile(cloneProfile);


   CComPtr<IStationEquationCollection> equations;
   pClone->get_StationEquations(&equations);

   CComPtr<IEnumStationEquations> pEnum;
   m_Equations->get__EnumStationEquations(&pEnum);
   CComPtr<IStationEquation> equation;
   ULONG nFetched;
   while ( pEnum->Next(1,&equation,&nFetched) != S_FALSE )
   {
      Float64 back, ahead;
      equation->GetEquation(&back,&ahead);
         
      CComPtr<IStationEquation> newEquation;
      equations->Add(back,ahead,&newEquation);

      equation.Release();
   }

   return S_OK;
}

STDMETHODIMP CAlignment::CreateParallelPath(Float64 offset,IPath** path)
{
   return m_Path->CreateParallelPath(offset,path);
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

   return m_Path->CreateSubPath(start,end,path);
}

STDMETHODIMP CAlignment::CreateConnectedPath(IPath** path)
{
   return m_Path->CreateConnectedPath(path);
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
   pSave->put_Property(CComBSTR("Profile"),CComVariant(m_Profile));
   pSave->put_Property(CComBSTR("StationEquations"),CComVariant(m_Equations));

   CComPtr<IStructuredStorage2> ss;
   m_Path->get_StructuredStorage(&ss);
   ATLASSERT(ss != nullptr);

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

   pLoad->get_Property(CComBSTR("Profile"),&var);
   CComPtr<IProfile> profile;
   _CopyVariantToInterface<IProfile>::copy(&profile,&var);
   putref_Profile(profile);

   pLoad->get_Property(CComBSTR("StationEquations"),&var);
   CComPtr<IStationEquationCollection> equations;
   _CopyVariantToInterface<IStationEquationCollection>::copy(&equations,&var);
   putref_StationEquations(equations);

   CComPtr<IStructuredStorage2> ss;
   m_Path->get_StructuredStorage(&ss);
   ATLASSERT(ss != nullptr);
   ss->Load(pLoad);

   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   return S_OK;
}


//////////////////////////////////////////////////////////
// Helpers
HRESULT CAlignment::CreateStation(Float64 location,IStation** pStation)
{
   return m_Equations->ConvertFromNormalizedStation(location,pStation);
}

HRESULT CAlignment::StationToPathDistance(VARIANT varStation,Float64* distance)
{
   Float64 normalizedStation;
   HRESULT hr = m_Equations->ConvertToNormalizedStation(varStation,&normalizedStation);

   if ( FAILED(hr) )
      return hr;

   (*distance) = normalizedStation - m_RefStation;

   return S_OK;
}
