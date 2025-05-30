///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
// Copyright © 1999-2025  Washington State Department of Transportation
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

// ProfileSegment.cpp : Implementation of CProfileSegment
#include "stdafx.h"
#include "WBFLCOGO.h"
#include "ProfileSegment.h"
#include "ProfilePoint.h"
#include <WBFLCogo\CogoHelpers.h>




/////////////////////////////////////////////////////////////////////////////
// CProfileSegment
HRESULT CProfileSegment::FinalConstruct()
{
   m_Segment = WBFL::COGO::ProfileSegment::Create();
   m_pProfile = nullptr;
   return S_OK;
}

void CProfileSegment::FinalRelease()
{
}

STDMETHODIMP CProfileSegment::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IProfileSegment,
      &IID_IProfileElement,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

// IProfileSegment
STDMETHODIMP CProfileSegment::SetStartPoint(IProfilePoint* pStart)
{
   CHECK_IN(pStart);
   m_Segment->SetStartPoint(*cogoUtil::GetInnerProfilePoint(pStart));
   return S_OK;
}

STDMETHODIMP CProfileSegment::SetEndPoint(IProfilePoint* pEnd)
{
   CHECK_IN(pEnd);
   m_Segment->SetEndPoint(*cogoUtil::GetInnerProfilePoint(pEnd));
   return S_OK;
}

STDMETHODIMP CProfileSegment::Location(IProfilePoint** ppStart, IProfilePoint** ppEnd)
{
   auto [start, end] = m_Segment->GetLocation();
   auto hr1 = cogoUtil::CreateProfilePoint(std::make_shared<WBFL::COGO::ProfilePoint>(start), ppStart);
   auto hr2 = cogoUtil::CreateProfilePoint(std::make_shared<WBFL::COGO::ProfilePoint>(end), ppEnd);
   return (FAILED(hr1) || FAILED(hr2) ? E_FAIL : S_OK);
}

STDMETHODIMP CProfileSegment::Move(IProfilePoint* pStart, IProfilePoint* pEnd)
{
   CHECK_IN(pStart);
   CHECK_IN(pEnd);
   m_Segment->Move(*cogoUtil::GetInnerProfilePoint(pStart), *cogoUtil::GetInnerProfilePoint(pEnd));
   return S_OK;
}

// IProfileElement

//STDMETHODIMP CProfileSegment::Clone(IProfileElement** clone)
//{
//}

STDMETHODIMP CProfileSegment::get_Profile(IProfile** pVal)
{
   CHECK_RETOBJ(pVal);
   (*pVal) = m_pProfile;
   (*pVal)->AddRef();
   return S_OK;
}

STDMETHODIMP CProfileSegment::put_Profile(IProfile* newVal)
{
   m_pProfile = newVal;
   return S_OK;
}

STDMETHODIMP CProfileSegment::GetStartPoint(IProfilePoint** ppPoint)
{
   CHECK_RETOBJ(ppPoint);
   return cogoUtil::CreateProfilePoint(std::make_shared<WBFL::COGO::ProfilePoint>(m_Segment->GetStartPoint()), ppPoint);
}

STDMETHODIMP CProfileSegment::GetEndPoint(IProfilePoint** ppPoint)
{
   CHECK_RETOBJ(ppPoint);
   return cogoUtil::CreateProfilePoint(std::make_shared<WBFL::COGO::ProfilePoint>(m_Segment->GetEndPoint()), ppPoint);
}

STDMETHODIMP CProfileSegment::GetLength(Float64* pLength)
{
   CHECK_RETVAL(pLength);
   *pLength = m_Segment->GetLength();
   return S_OK;
}

STDMETHODIMP CProfileSegment::ComputeGradeAndElevation(VARIANT varStation, Float64* pGrade, Float64* pElevation)
{
   CHECK_RETVAL(pGrade);
   CHECK_RETVAL(pElevation);

   auto [hr, station] = cogoUtil::StationFromVariant(varStation);
   if (FAILED(hr)) return hr;

   std::tie(*pGrade, *pElevation) = m_Segment->ComputeGradeAndElevation(station);
   return S_OK;
}
