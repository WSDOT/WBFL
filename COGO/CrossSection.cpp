///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
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

// CrossSection.cpp : Implementation of CCrossSection
#include "stdafx.h"
#include "WBFLCOGO.h"
#include "CrossSection.h"
#include "Station.h"
#include "CogoHelpers.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCrossSection
STDMETHODIMP CCrossSection::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ICrossSection,
      &IID_IStructuredStorage2,
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CCrossSection::get_Station(IStation* *station)
{
   CHECK_RETOBJ(station);

   CComObject<CStation>* pStation;
   CComObject<CStation>::CreateInstance(&pStation);
   pStation->put_Value(m_Station);

   (*station) = pStation;
   (*station)->AddRef();

	return S_OK;
}

STDMETHODIMP CCrossSection::put_Station(VARIANT varStation)
{
   CComPtr<IStation> objStation;
   HRESULT hr = cogoUtil::StationFromVariant(varStation,&objStation);
   if ( FAILED(hr) )
      return hr;

   Float64 station;
   objStation->get_Value(&station);

   if ( !IsEqual(m_Station,station) )
   {
      m_Station = station;
      Fire_OnCrossSectionMoved(this);
   }

	return S_OK;
}

STDMETHODIMP CCrossSection::get_CrownPointOffset(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_CrownPtOffset;
   return S_OK;
}

STDMETHODIMP CCrossSection::put_CrownPointOffset(Float64 newVal)
{
   m_CrownPtOffset = newVal;
   Fire_OnCrossSectionChanged(this);
	return S_OK;
}

STDMETHODIMP CCrossSection::get_LeftCrownSlope(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Left;
	return S_OK;
}

STDMETHODIMP CCrossSection::put_LeftCrownSlope(Float64 newVal)
{
   m_Left = newVal;
   Fire_OnCrossSectionChanged(this);
   return S_OK;
}

STDMETHODIMP CCrossSection::get_RightCrownSlope(Float64 *pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Right;
	return S_OK;
}

STDMETHODIMP CCrossSection::put_RightCrownSlope(Float64 newVal)
{
   m_Right = newVal;
   Fire_OnCrossSectionChanged(this);
   return S_OK;
}

STDMETHODIMP CCrossSection::Clone(ICrossSection* *clone)
{
   CHECK_RETOBJ(clone);

   CComObject<CCrossSection>* pClone;
   CComObject<CCrossSection>::CreateInstance(&pClone);

   (*clone) = pClone;
   (*clone)->AddRef();

   (*clone)->put_CrownPointOffset(m_CrownPtOffset);
   (*clone)->put_LeftCrownSlope(m_Left);
   (*clone)->put_RightCrownSlope(m_Right);
   (*clone)->put_Station(CComVariant(m_Station));

   return S_OK;
}

STDMETHODIMP CCrossSection::get_StructuredStorage(IStructuredStorage2* *pStg)
{
   CHECK_RETOBJ(pStg);
   return QueryInterface(IID_IStructuredStorage2,(void**)pStg);
}

// IStructuredStorage2
STDMETHODIMP CCrossSection::Save(IStructuredSave2* pSave)
{
   pSave->BeginUnit(CComBSTR("CrossSection"),1.0);
   pSave->put_Property(CComBSTR("Station"),CComVariant(m_Station));
   pSave->put_Property(CComBSTR("CrownPointOffset"),CComVariant(m_CrownPtOffset));
   pSave->put_Property(CComBSTR("Left"),CComVariant(m_Left));
   pSave->put_Property(CComBSTR("Right"),CComVariant(m_Right));
   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CCrossSection::Load(IStructuredLoad2* pLoad)
{
   CComVariant var;

   pLoad->BeginUnit(CComBSTR("CrossSection"));

   pLoad->get_Property(CComBSTR("Station"),&var);
   m_Station = var.dblVal;

   pLoad->get_Property(CComBSTR("CrownPointOffset"),&var);
   m_CrownPtOffset = var.dblVal;

   pLoad->get_Property(CComBSTR("Left"),&var);
   m_Left = var.dblVal;

   pLoad->get_Property(CComBSTR("Right"),&var);
   m_Right = var.dblVal;

   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   return S_OK;
}

