///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
// Copyright © 1999-2024  Washington State Department of Transportation
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

// PierLine.cpp : Implementation of CPier

#include "stdafx.h"
#include "WBFLCogo.h"
#include "PierLine.h"
#include <WBFLCogo\CogoHelpers.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// CPierLine


STDMETHODIMP CPierLine::get_AlignmentID(IDType* ID)
{
   CHECK_RETVAL(ID);
   *ID = m_PierLine->GetAlignmentID();
   return S_OK;
}

STDMETHODIMP CPierLine::get_Station(IStation** pVal)
{
   return cogoUtil::CreateStation(m_PierLine->GetStation(), pVal);
}

STDMETHODIMP CPierLine::get_Direction(IDirection** pVal)
{
   return cogoUtil::CreateDirection(m_PierLine->GetDirection(), pVal);
}

STDMETHODIMP CPierLine::get_Normal(IDirection** pVal)
{
   return cogoUtil::CreateDirection(m_PierLine->GetNormal(), pVal);
}

STDMETHODIMP CPierLine::get_Skew(IAngle** pVal)
{
   return cogoUtil::CreateAngle(m_PierLine->GetSkewAngle(), pVal);
}

STDMETHODIMP CPierLine::get_ID(PierIDType* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_PierLine->GetID();

   return S_OK;
}

STDMETHODIMP CPierLine::get_Index(IndexType* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_PierLine->GetIndex();
   return S_OK;
}

STDMETHODIMP CPierLine::get_BearingOffset(PierFaceType pierFace, Float64* brgOffset)
{
   CHECK_RETVAL(brgOffset);
   *brgOffset = m_PierLine->GetConnectionGeometry(WBFL::COGO::PierFaceType(pierFace)).BearingOffset;
   return S_OK;
}

STDMETHODIMP CPierLine::put_BearingOffset(PierFaceType pierFace, Float64 brgOffset)
{
   auto connection_geometry = m_PierLine->GetConnectionGeometry(WBFL::COGO::PierFaceType(pierFace));
   connection_geometry.BearingOffset = brgOffset;
   m_PierLine->SetConnectionGeometry(WBFL::COGO::PierFaceType(pierFace), connection_geometry);
   return S_OK;
}

STDMETHODIMP CPierLine::get_BearingOffsetMeasurementType(PierFaceType pierFace, MeasurementType* measure)
{
   CHECK_RETVAL(measure);
   *measure = (MeasurementType)(m_PierLine->GetConnectionGeometry(WBFL::COGO::PierFaceType(pierFace)).BearingOffsetMeasurementType);
   return S_OK;
}

STDMETHODIMP CPierLine::put_BearingOffsetMeasurementType(PierFaceType pierFace, MeasurementType measure)
{
   auto connection_geometry = m_PierLine->GetConnectionGeometry(WBFL::COGO::PierFaceType(pierFace));
   connection_geometry.BearingOffsetMeasurementType = WBFL::COGO::MeasurementType(measure);
   m_PierLine->SetConnectionGeometry(WBFL::COGO::PierFaceType(pierFace), connection_geometry);
   return S_OK;
}

STDMETHODIMP CPierLine::get_EndDistance(PierFaceType pierFace, Float64* endDist)
{
   CHECK_RETVAL(endDist);
   *endDist = m_PierLine->GetConnectionGeometry(WBFL::COGO::PierFaceType(pierFace)).EndDistance;
   return S_OK;
}

STDMETHODIMP CPierLine::put_EndDistance(PierFaceType pierFace, Float64 endDist)
{
   auto connection_geometry = m_PierLine->GetConnectionGeometry(WBFL::COGO::PierFaceType(pierFace));
   connection_geometry.EndDistance = endDist;
   m_PierLine->SetConnectionGeometry(WBFL::COGO::PierFaceType(pierFace), connection_geometry);
   return S_OK;
}

STDMETHODIMP CPierLine::get_EndDistanceMeasurementType(PierFaceType pierFace, MeasurementType* measure)
{
   CHECK_RETVAL(measure);
   *measure = (MeasurementType)(m_PierLine->GetConnectionGeometry(WBFL::COGO::PierFaceType(pierFace)).EndDistanceMeasurementType);
   return S_OK;
}

STDMETHODIMP CPierLine::put_EndDistanceMeasurementType(PierFaceType pierFace, MeasurementType measure)
{
   auto connection_geometry = m_PierLine->GetConnectionGeometry(WBFL::COGO::PierFaceType(pierFace));
   connection_geometry.EndDistanceMeasurementType = WBFL::COGO::MeasurementType(measure);
   m_PierLine->SetConnectionGeometry(WBFL::COGO::PierFaceType(pierFace), connection_geometry);
   return S_OK;
}

STDMETHODIMP CPierLine::get_EndDistanceMeasurementLocation(PierFaceType pierFace, MeasurementLocation* measure)
{
   CHECK_RETVAL(measure);
   *measure = (MeasurementLocation)(m_PierLine->GetConnectionGeometry(WBFL::COGO::PierFaceType(pierFace)).EndDistanceMeasurementLocationType);
   return S_OK;
}

STDMETHODIMP CPierLine::put_EndDistanceMeasurementLocation(PierFaceType pierFace, MeasurementLocation measure)
{
   auto connection_geometry = m_PierLine->GetConnectionGeometry(WBFL::COGO::PierFaceType(pierFace));
   connection_geometry.EndDistanceMeasurementLocationType = WBFL::COGO::MeasurementLocation(measure);
   m_PierLine->SetConnectionGeometry(WBFL::COGO::PierFaceType(pierFace), connection_geometry);
   return S_OK;
}

STDMETHODIMP CPierLine::get_AlignmentPoint(IPoint2d** ppPoint)
{
   return cogoUtil::CreatePoint(m_PierLine->GetAlignmentPoint(), ppPoint);
}

STDMETHODIMP CPierLine::get_BridgePoint(IPoint2d** ppPoint)
{
   return cogoUtil::CreatePoint(m_PierLine->GetBridgeLinePoint(), ppPoint);
}

STDMETHODIMP CPierLine::get_LeftPoint(IPoint2d** ppPoint)
{
   return cogoUtil::CreatePoint(m_PierLine->GetLeftPoint(), ppPoint);
}

STDMETHODIMP CPierLine::get_RightPoint(IPoint2d** ppPoint)
{
   return cogoUtil::CreatePoint(m_PierLine->GetRightPoint(), ppPoint);
}

STDMETHODIMP CPierLine::get_Centerline(ILine2d** ppLine)
{
   CHECK_RETOBJ(ppLine);
   return cogoUtil::CreateLine(m_PierLine->GetCenterLine(), ppLine);
}

STDMETHODIMP CPierLine::GetBearingOffset(PierFaceType pierFace,IDirection* direction,Float64* pOffset)
{
   // computes the bearing offset, measured from the cl pier, along a line defined by direction,
   // on the face of the pier specified
   CHECK_IN(direction);
   CHECK_RETVAL(pOffset);

   auto dir = cogoUtil::GetInnerDirection(direction);
   *pOffset = m_PierLine->GetBearingOffset(WBFL::COGO::PierFaceType(pierFace), dir);
   return S_OK;
}
