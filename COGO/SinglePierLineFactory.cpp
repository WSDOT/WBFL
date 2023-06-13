///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
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

// SinglePierLineFactory.cpp : Implementation of CSinglePierLineFactory

#include "stdafx.h"
#include "WBFLCogo.h"
#include "SinglePierLineFactory.h"
#include <WBFLCogo\CogoHelpers.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

STDMETHODIMP CSinglePierLineFactory::put_PierLineID(IDType id)
{
   m_Factory->SetPierLineID(id);
   return S_OK;
}

STDMETHODIMP CSinglePierLineFactory::get_PierLineID(IDType* pID)
{
   CHECK_RETVAL(pID);
   *pID = m_Factory->GetPierLineID();
   return S_OK;
}

STDMETHODIMP CSinglePierLineFactory::put_AlignmentID(IDType id)
{
   m_Factory->SetAlignmentID(id);
   return S_OK;
}

STDMETHODIMP CSinglePierLineFactory::get_AlignmentID(IDType* pID)
{
   CHECK_RETVAL(pID);
   *pID = m_Factory->GetAlignmentID();
   return S_OK;
}

STDMETHODIMP CSinglePierLineFactory::put_Station(VARIANT varStation)
{
   auto result = cogoUtil::StationFromVariant(varStation);
   if (FAILED(result.first)) return result.first;
   m_Factory->SetStation(result.second);
   return S_OK;
}

STDMETHODIMP CSinglePierLineFactory::get_Station(IStation** ppStation)
{
   CHECK_RETOBJ(ppStation);
   return cogoUtil::CreateStation(m_Factory->GetStation(), ppStation);
}

STDMETHODIMP CSinglePierLineFactory::put_Direction(BSTR direction)
{
   USES_CONVERSION;
   std::_tstring strDirection(OLE2T(direction));
   m_Factory->SetDirection(strDirection);
   return S_OK;
}

STDMETHODIMP CSinglePierLineFactory::get_Direction(BSTR* direction)
{
   USES_CONVERSION;
   CComBSTR bstrDirection(m_Factory->GetDirection().c_str());
   return bstrDirection.CopyTo(direction);
}

STDMETHODIMP CSinglePierLineFactory::put_Length(Float64 length)
{
   m_Factory->SetLength(length);
   return S_OK;
}

STDMETHODIMP CSinglePierLineFactory::get_Length(Float64* pLength)
{
   CHECK_RETVAL(pLength);
   *pLength = m_Factory->GetLength();
   return S_OK;
}

STDMETHODIMP CSinglePierLineFactory::put_Offset(Float64 offset)
{
   m_Factory->SetOffset(offset);
   return S_OK;
}

STDMETHODIMP CSinglePierLineFactory::get_Offset(Float64* pOffset)
{
   CHECK_RETVAL(pOffset);
   *pOffset = m_Factory->GetOffset();
   return S_OK;
}

STDMETHODIMP CSinglePierLineFactory::put_BearingOffset(PierFaceType pierFace, Float64 brgOffset)
{
   auto connection_geometry = m_Factory->GetConnectionGeometry(WBFL::COGO::PierFaceType(pierFace));
   connection_geometry.BearingOffset = brgOffset;
   m_Factory->SetConnectionGeometry(WBFL::COGO::PierFaceType(pierFace), connection_geometry);
   return S_OK;
}

STDMETHODIMP CSinglePierLineFactory::get_BearingOffset(PierFaceType pierFace, Float64* pBrgOffset)
{
   CHECK_RETVAL(pBrgOffset);
   const auto& connection_geometry = m_Factory->GetConnectionGeometry(WBFL::COGO::PierFaceType(pierFace));
   *pBrgOffset = connection_geometry.BearingOffset;
   return S_OK;
}

STDMETHODIMP CSinglePierLineFactory::put_BearingOffsetMeasurementType(PierFaceType pierFace, MeasurementType measure)
{
   auto connection_geometry = m_Factory->GetConnectionGeometry(WBFL::COGO::PierFaceType(pierFace));
   connection_geometry.BearingOffsetMeasurementType = WBFL::COGO::MeasurementType(measure);
   m_Factory->SetConnectionGeometry(WBFL::COGO::PierFaceType(pierFace), connection_geometry);
   return S_OK;
}

STDMETHODIMP CSinglePierLineFactory::get_BearingOffsetMeasurementType(PierFaceType pierFace, MeasurementType* pMeasure)
{
   CHECK_RETVAL(pMeasure);
   const auto& connection_geometry = m_Factory->GetConnectionGeometry(WBFL::COGO::PierFaceType(pierFace));
   *pMeasure = MeasurementType(connection_geometry.BearingOffsetMeasurementType);
   return S_OK;
}

STDMETHODIMP CSinglePierLineFactory::put_EndDistance(PierFaceType pierFace, Float64 endDist)
{
   auto connection_geometry = m_Factory->GetConnectionGeometry(WBFL::COGO::PierFaceType(pierFace));
   connection_geometry.EndDistance = endDist;
   m_Factory->SetConnectionGeometry(WBFL::COGO::PierFaceType(pierFace), connection_geometry);
   return S_OK;
}

STDMETHODIMP CSinglePierLineFactory::get_EndDistance(PierFaceType pierFace, Float64* pEndDist)
{
   CHECK_RETVAL(pEndDist);
   const auto& connection_geometry = m_Factory->GetConnectionGeometry(WBFL::COGO::PierFaceType(pierFace));
   *pEndDist = connection_geometry.EndDistance;
   return S_OK;
}

STDMETHODIMP CSinglePierLineFactory::put_EndDistanceMeasurementType(PierFaceType pierFace, MeasurementType measure)
{
   auto connection_geometry = m_Factory->GetConnectionGeometry(WBFL::COGO::PierFaceType(pierFace));
   connection_geometry.EndDistanceMeasurementType = WBFL::COGO::MeasurementType(measure);
   m_Factory->SetConnectionGeometry(WBFL::COGO::PierFaceType(pierFace), connection_geometry);
   return S_OK;
}

STDMETHODIMP CSinglePierLineFactory::get_EndDistanceMeasurementType(PierFaceType pierFace, MeasurementType* pMeasure)
{
   CHECK_RETVAL(pMeasure);
   const auto& connection_geometry = m_Factory->GetConnectionGeometry(WBFL::COGO::PierFaceType(pierFace));
   *pMeasure = MeasurementType(connection_geometry.EndDistanceMeasurementType);
   return S_OK;
}

STDMETHODIMP CSinglePierLineFactory::put_EndDistanceMeasurementLocation(PierFaceType pierFace, MeasurementLocation measure)
{
   auto connection_geometry = m_Factory->GetConnectionGeometry(WBFL::COGO::PierFaceType(pierFace));
   connection_geometry.EndDistanceMeasurementLocationType = WBFL::COGO::MeasurementLocation(measure);
   m_Factory->SetConnectionGeometry(WBFL::COGO::PierFaceType(pierFace), connection_geometry);
   return S_OK;
}

STDMETHODIMP CSinglePierLineFactory::get_EndDistanceMeasurementLocation(PierFaceType pierFace, MeasurementLocation* pMeasure)
{
   CHECK_RETVAL(pMeasure);
   const auto& connection_geometry = m_Factory->GetConnectionGeometry(WBFL::COGO::PierFaceType(pierFace));
   *pMeasure = MeasurementLocation(connection_geometry.EndDistanceMeasurementLocationType);
   return S_OK;
}



