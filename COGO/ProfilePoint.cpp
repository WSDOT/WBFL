///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry
// Copyright © 1999-2012  Washington State Department of Transportation
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

// ProfilePoint.cpp : Implementation of CProfilePoint
#include "stdafx.h"
#include "WBFLCOGO.h"
#include "ProfilePoint.h"
#include "CogoHelpers.h"
#include "Station.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProfilePoint

STDMETHODIMP CProfilePoint::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IProfilePoint,
		&IID_IStructuredStorage2,
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CProfilePoint::get_Station(IStation* *station)
{
   CHECK_RETOBJ(station);

   CComObject<CStation>* pStation;
   CComObject<CStation>::CreateInstance(&pStation);
   pStation->put_Value(m_Station);
   
   (*station) = pStation;
   (*station)->AddRef();

   return S_OK;
}

STDMETHODIMP CProfilePoint::put_Station(VARIANT varStation)
{
   CComPtr<IStation> objStation;
   HRESULT hr = cogoUtil::StationFromVariant(varStation,&objStation);
   if ( FAILED(hr) )
      return hr;

   Float64 station;
   objStation->get_Value(&station);

   if ( !IsEqual(station,m_Station) )
   {
      m_Station = station;
      Fire_OnProfilePointChanged(this);
   }
	return S_OK;
}

STDMETHODIMP CProfilePoint::get_Elevation(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Elevation;
	return S_OK;
}

STDMETHODIMP CProfilePoint::put_Elevation(Float64 newVal)
{
   if ( newVal != m_Elevation )
   {
      m_Elevation = newVal;
      Fire_OnProfilePointChanged(this);
   }
	return S_OK;
}

STDMETHODIMP CProfilePoint::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

STDMETHODIMP CProfilePoint::Clone(IProfilePoint* *clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CProfilePoint>* pClone;
   CComObject<CProfilePoint>::CreateInstance(&pClone);

   (*clone) = pClone;
   (*clone)->AddRef();

   (*clone)->put_Elevation(m_Elevation);
   (*clone)->put_Station(CComVariant(m_Station));

   return S_OK;
}

// IStructuredStorage2
STDMETHODIMP CProfilePoint::Save(IStructuredSave2* pSave)
{
   pSave->BeginUnit(CComBSTR("ProfilePoint"),1.0);
   pSave->put_Property(CComBSTR("Station"),CComVariant(m_Station));
   pSave->put_Property(CComBSTR("Elevation"),CComVariant(m_Elevation));
   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CProfilePoint::Load(IStructuredLoad2* pLoad)
{
   CComVariant var;
   pLoad->BeginUnit(CComBSTR("ProfilePoint"));

   pLoad->get_Property(CComBSTR("Station"),&var);
   m_Station = var.dblVal;

   pLoad->get_Property(CComBSTR("Elevation"),&var);
   m_Elevation = var.dblVal;

   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   return S_OK;
}
