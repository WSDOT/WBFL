///////////////////////////////////////////////////////////////////////
// BridgeGeometry
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

// PierLine.cpp : Implementation of CPier

#include "stdafx.h"
#include "PierLine.h"

// CPierLine


STDMETHODIMP CPierLine::get_AlignmentID(CogoObjectID* ID)
{
   CHECK_RETVAL(ID);
   *ID = m_AlignmentID;
   return S_OK;
}

STDMETHODIMP CPierLine::get_Station(IStation** pVal)
{
   return m_Station->Clone(pVal);
}

STDMETHODIMP CPierLine::get_Direction(IDirection** pVal)
{
   return m_Direction->Clone(pVal);
}

STDMETHODIMP CPierLine::get_Normal(IDirection** pVal)
{
   return m_Normal->Clone(pVal);
}

STDMETHODIMP CPierLine::get_Skew(IAngle** pVal)
{
   return m_Skew->Clone(pVal);
}

STDMETHODIMP CPierLine::get_Index(PierIndexType* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_Index;

   return S_OK;
}

STDMETHODIMP CPierLine::get_ID(PierIDType* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_ID;

   return S_OK;
}

STDMETHODIMP CPierLine::get_NextPierLine(IPierLine** pVal)
{
   CHECK_RETOBJ(pVal);
   *pVal = m_pNextPier;
   if ( *pVal )
      (*pVal)->AddRef();

   return S_OK;
}

STDMETHODIMP CPierLine::get_PrevPierLine(IPierLine** pVal)
{
   CHECK_RETOBJ(pVal);
   *pVal = m_pPrevPier;
   if ( *pVal )
      (*pVal)->AddRef();

   return S_OK;
}

STDMETHODIMP CPierLine::get_BearingOffset(PierFaceType pierFace, Float64* brgOffset)
{
   CHECK_RETVAL(brgOffset);
   *brgOffset = m_BearingOffset[pierFace];
   return S_OK;
}

STDMETHODIMP CPierLine::put_BearingOffset(PierFaceType pierFace, Float64 brgOffset)
{
   m_BearingOffset[pierFace] = brgOffset;
   return S_OK;
}

STDMETHODIMP CPierLine::get_BearingOffsetMeasurementType(PierFaceType pierFace, MeasurementType* measure)
{
   CHECK_RETVAL(measure);
   *measure = m_BearingOffsetMeasure[pierFace];
   return S_OK;
}

STDMETHODIMP CPierLine::put_BearingOffsetMeasurementType(PierFaceType pierFace, MeasurementType measure)
{
   m_BearingOffsetMeasure[pierFace] = measure;
   return S_OK;
}

STDMETHODIMP CPierLine::get_EndDistance(PierFaceType pierFace, Float64* endDist)
{
   CHECK_RETVAL(endDist);
   *endDist = m_EndDistance[pierFace];
   return S_OK;
}

STDMETHODIMP CPierLine::put_EndDistance(PierFaceType pierFace, Float64 endDist)
{
   m_EndDistance[pierFace] = endDist;
   return S_OK;
}

STDMETHODIMP CPierLine::get_EndDistanceMeasurementType(PierFaceType pierFace, MeasurementType* measure)
{
   CHECK_RETVAL(measure);
   *measure = m_EndDistanceMeasure[pierFace];
   return S_OK;
}

STDMETHODIMP CPierLine::put_EndDistanceMeasurementType(PierFaceType pierFace, MeasurementType measure)
{
   m_EndDistanceMeasure[pierFace] = measure;
   return S_OK;
}

STDMETHODIMP CPierLine::get_EndDistanceMeasurementLocation(PierFaceType pierFace, MeasurementLocation* measure)
{
   CHECK_RETVAL(measure);
   *measure = m_EndDistanceMeasureLocation[pierFace];
   return S_OK;
}

STDMETHODIMP CPierLine::put_EndDistanceMeasurementLocation(PierFaceType pierFace, MeasurementLocation measure)
{
   m_EndDistanceMeasureLocation[pierFace] = measure;
   return S_OK;
}

STDMETHODIMP CPierLine::get_AlignmentPoint(IPoint2d** ppPoint)
{
   return m_pntAlignment->Clone(ppPoint);
}

STDMETHODIMP CPierLine::get_BridgePoint(IPoint2d** ppPoint)
{
   return m_pntBridge->Clone(ppPoint);
}

STDMETHODIMP CPierLine::get_LeftPoint(IPoint2d** ppPoint)
{
   return m_pntLeft->Clone(ppPoint);
}

STDMETHODIMP CPierLine::get_RightPoint(IPoint2d** ppPoint)
{
   return m_pntRight->Clone(ppPoint);
}

STDMETHODIMP CPierLine::get_Centerline(ILine2d** ppLine)
{
   CHECK_RETOBJ(ppLine);
   return m_Centerline->Clone(ppLine);
}

STDMETHODIMP CPierLine::GetBearingOffset(PierFaceType pierFace,IDirection* direction,Float64* pOffset)
{
   // computes the bearing offset, measured from the cl pier, along a line defined by direction,
   // on the face of the pier specified
   CHECK_IN(direction);
   CHECK_RETVAL(pOffset);

   Float64 brgOffset = m_BearingOffset[pierFace];
   if ( m_BearingOffsetMeasure[pierFace] == mtNormal )
   {
      // bearing offset is measured normal to pier... adjust it so it is measured along "direction"
      CComPtr<IAngle> angle;
      m_Normal->AngleBetween(direction,&angle);
      Float64 value;
      angle->get_Value(&value);

      brgOffset /= cos(value);
   }
   else
   {
      // bearing offset is measured along item. no adjustment is necessary
   }

   *pOffset = brgOffset;
   return S_OK;
}

HRESULT CPierLine::UpdateGeometry()
{
   USES_CONVERSION;

   m_pntAlignment.Release();
   m_pntBridge.Release();
   m_pntLeft.Release();
   m_pntRight.Release();

   // Locate CL-Pier/Alignment intersection point
   CComPtr<IAlignment> alignment;
   HRESULT hr = m_pBridge->get_Alignment(m_AlignmentID,&alignment);
   if ( FAILED(hr) )
   {
      ATLASSERT(false); // bad alignmentID
      return hr;
   }

   m_Direction.Release();
   alignment->LocatePoint( CComVariant(m_Station),omtNormal,0.0,CComVariant(0.0),&m_pntAlignment);

   // get the direction of the pier
   alignment->GetDirection(CComVariant(m_Station),m_bstrOrientation,&m_Direction);

   // get the pier normal
   CComPtr<IDirection> normal; // normal to the alignment
   alignment->Normal(CComVariant(m_Station),&normal);
   normal->IncrementBy(CComVariant(M_PI)); // We want the normal to the left... Increment by 180 degrees

   // Skew angle is the difference between the pier direction and the normal
   m_Skew.Release();
   m_Direction->AngleBetween(normal,&m_Skew);

   // If the angle is more than PI/2, it is a right skew... Right skews are negative... adjust
   Float64 angle;
   m_Skew->get_Value(&angle);
   if ( PI_OVER_2 < angle )
   {
      angle = angle - TWO_PI;
      m_Skew->put_Value(angle);
   }

   //
   // Create the pier centerline
   //
   m_Centerline.Release();
   m_Centerline.CoCreateInstance(CLSID_Line2d);
   
   CComPtr<IVector2d> v;
   CComPtr<IPoint2d> p;
   m_Centerline->GetExplicit(&p,&v);

   Float64 value;
   m_Direction->get_Value(&value);
   v->put_Direction(value);

   m_Centerline->SetExplicit(m_pntAlignment,v);

   // pierline - bridge line intersection point
   CComPtr<IPath> bridge_line;
   m_pBridge->get_BridgeLine(&bridge_line);

   bridge_line->Intersect(m_Centerline,m_pntAlignment,&m_pntBridge);

   // locate left and right point
   CComPtr<ICogoModel> cogoModel;
   m_pBridge->get_CogoModel(&cogoModel);
   CComPtr<ICogoEngine> engine;
   cogoModel->get_Engine(&engine);
   CComPtr<ILocate2> locate;
   engine->get_Locate(&locate);

   locate->ByDistDir(m_pntAlignment,-m_Offset,CComVariant(m_Direction),0.0,&m_pntLeft);
   locate->ByDistDir(m_pntLeft,-m_Width,CComVariant(m_Direction),0.0,&m_pntRight);

   // create normal to the pier
   m_Normal.Release(); 
   m_Direction->Increment(CComVariant(-PI_OVER_2),&m_Normal);

   
   return S_OK;
}
