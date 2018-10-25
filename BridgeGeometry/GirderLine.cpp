///////////////////////////////////////////////////////////////////////
// BridgeGeometry
// Copyright © 1999-2015  Washington State Department of Transportation
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

// GirderLine.cpp : Implementation of CGirderLine

#include "stdafx.h"
#include "GirderLine.h"
#include "BridgeGeometryHelper.h"


// CGirderLine
STDMETHODIMP CGirderLine::get_BearingOffset(EndType endType,Float64* pBrgOffset)
{
   CHECK_RETVAL(pBrgOffset);
   *pBrgOffset = m_BearingOffset[endType];
   return S_OK;
}

STDMETHODIMP CGirderLine::get_EndDistance(EndType endType,Float64* pEndDistance)
{
   CHECK_RETVAL(pEndDistance);
   *pEndDistance = m_EndDistance[endType];
   return S_OK;
}

STDMETHODIMP CGirderLine::get_Direction(IDirection** ppDirection)
{
   CHECK_RETOBJ(ppDirection);
   return m_Direction.CopyTo(ppDirection);
}

STDMETHODIMP CGirderLine::get_Path(IPath** pVal)
{
   CHECK_RETOBJ(pVal);
#pragma Reminder("BUG: this is a bug")
   // should be calling m_Path->Clone(pVal);
   // but this is kind of slow.
   // The bug is that we need "by value" semantics here and we are returning
   // by reference. This means any outside actor can mess up our girder line path
   // and we will never know about it.
   return m_Path.CopyTo(pVal);
}

STDMETHODIMP CGirderLine::GetEndPoints(IPoint2d** pntPier1,IPoint2d** pntEnd1,IPoint2d** pntBrg1,IPoint2d** pntBrg2,IPoint2d** pntEnd2,IPoint2d** pntPier2)
{
   CHECK_RETOBJ(pntPier1);
   CHECK_RETOBJ(pntEnd1);
   CHECK_RETOBJ(pntBrg1);
   CHECK_RETOBJ(pntPier2);
   CHECK_RETOBJ(pntEnd2);
   CHECK_RETOBJ(pntBrg2);

   m_PierPoint[etStart]->Clone(pntPier1);
   m_PierPoint[etEnd]->Clone(pntPier2);

   m_EndPoint[etStart]->Clone(pntEnd1);
   m_EndPoint[etEnd]->Clone(pntEnd2);

   m_BearingPoint[etStart]->Clone(pntBrg1);
   m_BearingPoint[etEnd]->Clone(pntBrg2);

   return S_OK;
}

STDMETHODIMP CGirderLine::get_EndPoint(EndType endType,IPoint2d** ppPoint)
{
   CHECK_RETOBJ(ppPoint);
   return m_EndPoint[endType]->Clone(ppPoint);
}

STDMETHODIMP CGirderLine::get_PierPoint(EndType endType,IPoint2d** ppPoint)
{
   CHECK_RETOBJ(ppPoint);
   return m_PierPoint[endType]->Clone(ppPoint);
}

STDMETHODIMP CGirderLine::get_BearingPoint(EndType endType,IPoint2d** ppPoint)
{
   CHECK_RETOBJ(ppPoint);
   return m_BearingPoint[endType]->Clone(ppPoint);
}

STDMETHODIMP CGirderLine::get_GirderLength(Float64* pLength)
{
   CHECK_RETVAL(pLength);
   *pLength = m_GirderLength;
   return S_OK;
}

STDMETHODIMP CGirderLine::get_SpanLength(Float64* pLength)
{
   CHECK_RETVAL(pLength);
   *pLength = m_SpanLength;
   return S_OK;
}

STDMETHODIMP CGirderLine::get_LayoutLength(Float64* pLength)
{
   CHECK_RETVAL(pLength);
   *pLength = m_LayoutLength;
   return S_OK;
}

STDMETHODIMP CGirderLine::get_StartPier(IPierLine** pVal)
{
   CHECK_RETOBJ(pVal);
   (*pVal) = m_StartPierLine;
   if ( *pVal )
      (*pVal)->AddRef();

   return S_OK;
}

STDMETHODIMP CGirderLine::get_EndPier(IPierLine** pVal)
{
   CHECK_RETOBJ(pVal);
   (*pVal) = m_EndPierLine;
   if ( *pVal )
      (*pVal)->AddRef();

   return S_OK;
}

STDMETHODIMP CGirderLine::get_ID(GirderIDType* pVal)
{
   CHECK_RETVAL(pVal);
   *pVal = m_ID;

   return S_OK;
}

HRESULT CGirderLine::UpdateGeometry()
{
   // clear all the girder line geometry before proceeding
   m_Path.Release();
   m_PierPoint[etStart].Release();
   m_PierPoint[etEnd].Release();
   m_BearingPoint[etStart].Release();
   m_BearingPoint[etEnd].Release();
   m_EndPoint[etStart].Release();
   m_EndPoint[etEnd].Release();
   m_Direction.Release();

   CreatePath();
   LocatePoints();
   return S_OK;
}

HRESULT CGirderLine::CreatePath()
{
   // The girder line path goes from CL Pier to CL Pier

   HRESULT hr;
   CComPtr<IPath> layoutPath;
   hr = m_pBridge->FindLayoutLine(m_LayoutLineID,&layoutPath);
   ATLASSERT( SUCCEEDED(hr) ); // layout line must exist before updating geometry
   if ( FAILED(hr) )
      return hr;

   // get the pier lines that this girder line intersects with
   m_StartPierLine.Release();
   hr = m_pBridge->FindPierLine(m_StartPierID,&m_StartPierLine);
   ATLASSERT( SUCCEEDED(hr) ); // pier must exist before updating geometry
   if ( FAILED(hr) )
      return hr;

   m_EndPierLine.Release();
   hr = m_pBridge->FindPierLine(m_EndPierID,&m_EndPierLine);
   ATLASSERT( SUCCEEDED(hr) ); // pier must exist before updating geometry
   if ( FAILED(hr) )
      return hr;

   // get CL Pier/Alignment intersection points
   CComPtr<IPoint2d> pntStartPier, pntEndPier;
   m_StartPierLine->get_AlignmentPoint(&pntStartPier);
   m_EndPierLine->get_AlignmentPoint(&pntEndPier);

   // get the centerline of the piers
   CComPtr<ILine2d> clStartPier, clEndPier;
   m_StartPierLine->get_Centerline(&clStartPier);
   m_EndPierLine->get_Centerline(&clEndPier);


   if ( m_Type == glChord )
   {
      // girder line is a straight chord

      // get the lines the girder spacing is measured along
      CComPtr<ILine2d> leftLine, rightLine;
      hr = GetGirderSpacingLine(etStart,m_StartPierLine,&leftLine);
      ATLASSERT( SUCCEEDED(hr) );
      if ( FAILED(hr) )
         return hr;

      hr = GetGirderSpacingLine(etEnd,m_EndPierLine,&rightLine);
      ATLASSERT( SUCCEEDED(hr) );
      if ( FAILED(hr) )
         return hr;

      // intersect the spacing layout lines with the girder path
      CComPtr<IPoint2d> pnt1,pnt2;
      layoutPath->Intersect(leftLine, pntStartPier,&pnt1);
      layoutPath->Intersect(rightLine,pntEndPier,  &pnt2);

      // create a work line through the points on the girder spacing measurement line
      CComPtr<ILine2d> line;
      line.CoCreateInstance(CLSID_Line2d);
      line->ThroughPoints(pnt1,pnt2);

      // intersect the CL Piers with the girder work line
      PierLineIntersect(m_StartPierLine,line,&m_PierPoint[etStart]);
      PierLineIntersect(m_EndPierLine,  line,&m_PierPoint[etEnd]);

      // girder line is a straight line cord between the intersection of the CL-piers
      CComPtr<ILineSegment2d> lineSegment;
      lineSegment.CoCreateInstance(CLSID_LineSegment2d);
      lineSegment->ThroughPoints(m_PierPoint[etStart],m_PierPoint[etEnd]);

      m_Path.CoCreateInstance(CLSID_Path);
      m_Path->AddEx(lineSegment);
   }
   else
   {
      // girder line is a path

      // intersect CL Pier with layout path
      layoutPath->Intersect(clStartPier, pntStartPier, &m_PierPoint[etStart]);
      layoutPath->Intersect(clEndPier,   pntEndPier,   &m_PierPoint[etEnd]);

      // girder line is a sub-path of the layout path
      // determine where the girder path starts and end

      Float64 start_distance, end_distance, offset;
      layoutPath->Offset(m_PierPoint[etStart],&start_distance,&offset);
      ATLASSERT(IsZero(offset));
      
      layoutPath->Offset(m_PierPoint[etEnd],&end_distance,&offset);
      ATLASSERT(IsZero(offset));

      CComPtr<IPath> subPath;
      layoutPath->CreateSubPath(start_distance,end_distance,&subPath);

      m_Path.CoCreateInstance(CLSID_Path);
      m_Path->AddEx(subPath);
   }


   m_Path->get_Length(&m_LayoutLength);

   return S_OK;
}

HRESULT CGirderLine::LocatePoints()
{
   CComPtr<ICogoModel> cogoModel;
   m_pBridge->get_CogoModel(&cogoModel);
   CComPtr<ICogoEngine> cogoEngine;
   cogoModel->get_Engine(&cogoEngine);
   CComQIPtr<ILocate2> locate(cogoEngine);
   CComQIPtr<IMeasure2> measure(cogoEngine);

   measure->Direction(m_PierPoint[etStart],m_PierPoint[etEnd],&m_Direction);

   //
   // Locate intersection of girder line and centerline bearing
   //
   Float64 brgOffset[2];
   m_StartPierLine->get_BearingOffset(pfAhead,&brgOffset[etStart]);
   m_EndPierLine->get_BearingOffset(pfBack,&brgOffset[etEnd]);

   MeasurementType brgMeasureType[2];
   m_StartPierLine->get_BearingOffsetMeasurementType(pfAhead,&brgMeasureType[etStart]);
   m_EndPierLine->get_BearingOffsetMeasurementType(pfBack,&brgMeasureType[etEnd]);

   if ( brgMeasureType[etStart] == mtNormal )
   {
      // convert to distance along girder centerline
      CComPtr<IDirection> dirPier;
      m_StartPierLine->get_Direction(&dirPier);
      dirPier->IncrementBy(CComVariant(-PI_OVER_2)); // make this the pier normal
      CComPtr<IAngle> angle;
      dirPier->AngleBetween(m_Direction,&angle);

      Float64 value;
      angle->get_Value(&value);
      brgOffset[etStart] /= cos(value);
   }

   if ( brgMeasureType[etEnd] == mtNormal )
   {
      // convert to distance along girder centerline
      CComPtr<IDirection> dirPier;
      m_EndPierLine->get_Direction(&dirPier);
      dirPier->IncrementBy(CComVariant(-PI_OVER_2)); // make this the pier normal
      CComPtr<IAngle> angle;
      dirPier->AngleBetween(m_Direction,&angle);

      Float64 value;
      angle->get_Value(&value);
      brgOffset[etEnd] /= cos(value);
   }

   locate->PointOnLine(m_PierPoint[etStart],m_PierPoint[etEnd],  brgOffset[etStart],0.00,&m_BearingPoint[etStart]);
   locate->PointOnLine(m_PierPoint[etEnd],  m_PierPoint[etStart],brgOffset[etEnd],  0.00,&m_BearingPoint[etEnd]);

   //
   // Locate ends of girder
   //

   Float64 endDistance[2];
   m_StartPierLine->get_EndDistance(pfAhead,&endDistance[etStart]);
   m_EndPierLine->get_EndDistance(pfBack,&endDistance[etEnd]);

   MeasurementType measureType[2];
   m_StartPierLine->get_EndDistanceMeasurementType(pfAhead,&measureType[etStart]);
   m_EndPierLine->get_EndDistanceMeasurementType(pfBack,&measureType[etEnd]);

   MeasurementLocation measureLocation[2];
   m_StartPierLine->get_EndDistanceMeasurementLocation(pfAhead,&measureLocation[etStart]);
   m_EndPierLine->get_EndDistanceMeasurementLocation(pfBack,&measureLocation[etEnd]);

   m_EndPoint[etStart].Release();
   m_EndPoint[etEnd].Release();

   if ( measureType[etStart] == mtNormal )
   {
      // convert to distance along girder centerline
      CComPtr<IDirection> dirPier;
      m_StartPierLine->get_Direction(&dirPier);
      dirPier->IncrementBy(CComVariant(-PI_OVER_2)); // make this the pier normal
      CComPtr<IAngle> angle;
      dirPier->AngleBetween(m_Direction,&angle);

      Float64 value;
      angle->get_Value(&value);
      endDistance[etStart] /= cos(value);
   }

   if ( measureType[etEnd] == mtNormal )
   {
      // convert to distance along girder centerline
      CComPtr<IDirection> dirPier;
      m_EndPierLine->get_Direction(&dirPier);
      dirPier->IncrementBy(CComVariant(-PI_OVER_2)); // make this the pier normal
      CComPtr<IAngle> angle;
      dirPier->AngleBetween(m_Direction,&angle);

      Float64 value;
      angle->get_Value(&value);
      endDistance[etEnd] /= cos(value);
   }

   if ( measureLocation[etStart] == mlPierLine )
   {
      locate->PointOnLine(m_PierPoint[etStart],m_PierPoint[etEnd],endDistance[etStart],0.00,&m_EndPoint[etStart]);
   }
   else
   {
      ATLASSERT(measureLocation[etStart] == mlCenterlineBearing);
      locate->PointOnLine(m_BearingPoint[etStart],m_BearingPoint[etEnd],-endDistance[etStart],0.00,&m_EndPoint[etStart]);
   }

   if ( measureLocation[etEnd] == mlPierLine )
   {
      locate->PointOnLine(m_PierPoint[etEnd],m_PierPoint[etStart],endDistance[etEnd],0.00,&m_EndPoint[etEnd]);
   }
   else
   {
      ATLASSERT(measureLocation[etEnd] == mlCenterlineBearing);
      locate->PointOnLine(m_BearingPoint[etEnd],m_BearingPoint[etStart],-endDistance[etEnd],0.00,&m_EndPoint[etEnd]);
   }

#pragma Reminder("UPDATE: this is assuming the girder line is straight... it could be a curve")
   m_BearingPoint[etEnd]->DistanceEx(m_BearingPoint[etStart],&m_SpanLength);
   m_EndPoint[etEnd]->DistanceEx(m_EndPoint[etStart],&m_GirderLength);

   m_PierPoint[etStart]->DistanceEx(m_BearingPoint[etStart],&m_BearingOffset[etStart]);
   m_PierPoint[etEnd]->DistanceEx(  m_BearingPoint[etEnd],  &m_BearingOffset[etEnd]);

   m_BearingPoint[etStart]->DistanceEx(m_EndPoint[etStart],&m_EndDistance[etStart]);
   m_BearingPoint[etEnd]->DistanceEx(  m_EndPoint[etEnd],  &m_EndDistance[etEnd]);

   return S_OK;
}

HRESULT CGirderLine::GetGirderSpacingLine(EndType endType,IPierLine* pPierLine,ILine2d** ppLine)
{
   PierFaceType pierFace = (endType == etStart ? pfAhead : pfBack);

   HRESULT hr = S_OK;
   if ( m_MeasureType[endType] == mtAlongItem )
   {
      // Girder spacing is measured along the CL Pier or CL Bearing
      if ( m_MeasureLocation[endType] == mlPierLine )
      {
         // Girder spacing was measured along the CL Pier so layout lines
         // were defined based on this.
         // Intersect the centerline of the pier with the layout line

         hr = pPierLine->get_Centerline(ppLine);
         if ( FAILED(hr) )
            return hr;
      }
      else
      {
         // girder spacing is measured along CL Bearing
         // locate the CL Bearing line
         ATLASSERT(m_MeasureLocation[endType] == mlCenterlineBearing);

         MeasurementType brgOffsetMeasurement;
         pPierLine->get_BearingOffsetMeasurementType(pierFace,&brgOffsetMeasurement);

         Float64 brgOffset;
         pPierLine->get_BearingOffset(pierFace,&brgOffset);

         if ( brgOffsetMeasurement == mtNormal )
         {
            // CL Bearing is located "brgOffset" from the CL Pier, measured normal to the pier
            // The CL Bearing line is parallel to the CL Pier line
            hr = pPierLine->get_Centerline(ppLine);
            if ( FAILED(hr) )
               return hr;

            // offset to make it the CL Bearing line
            hr = (*ppLine)->Offset( pierFace == pfAhead ? -brgOffset : brgOffset );
            if ( FAILED(hr) )
               return hr;
         }
         else
         {
            // CL Bearing line is located "brgOffset" along the centerline of this girder, measured
            // from the point where the centerline of this girder intersects with the CL pier
            // The CL Bearing line is parallel to the CL Pier line.

            // This input combination is not supported
            ATLASSERT(false);

            return E_FAIL;
         }
      }
   }
   else
   {
      // Girder spacing is measured normal to the alignment at the CL Pier or CL Bearing
      ATLASSERT(m_MeasureType[endType] == mtNormal);

      if ( m_MeasureLocation[endType] == mlPierLine )
      {
         // Girder spacing was measured along the normal to the alignment where
         // the CL Pier intersects the alignment

         // get the alignment
         CComPtr<IAlignment> alignment;
         m_pBridge->get_BridgeAlignment(&alignment);

         // get the station at the pier
         CComPtr<IStation> pierStation;
         pPierLine->get_Station(&pierStation);

         // get the normal to the alignment at this station
         CComPtr<IDirection> pierNormal;
         alignment->Normal(CComVariant(pierStation),&pierNormal);

         // get the intersection of the pier and the alignment
         CComPtr<IPoint2d> pntPier;
         pPierLine->get_AlignmentPoint(&pntPier);

         // create line objects to represent the normal
         CreateLine(pntPier,pierNormal,ppLine);
      }
      else
      {
         // Girder spacing was measured along the normal to the alignment where
         // the CL Bearing intersects the alignment

         ATLASSERT(m_MeasureLocation[endType] == mlCenterlineBearing);

         MeasurementType brgOffsetMeasurement;
         pPierLine->get_BearingOffsetMeasurementType(pierFace,&brgOffsetMeasurement);

         Float64 brgOffset;
         pPierLine->get_BearingOffset(pierFace,&brgOffset);

         if ( brgOffsetMeasurement == mtNormal )
         {
            // CL Bearing is located "brgOffset" from the CL Pier, measured normal to the pier
            // The CL Bearing line is parallel to the CL Pier line
            CComPtr<ILine2d> centerline;
            hr = pPierLine->get_Centerline(&centerline);
            if ( FAILED(hr) )
               return hr;

            // offset to make it the CL Bearing line
            hr = centerline->Offset( pierFace == pfAhead ? -brgOffset : brgOffset );
            if ( FAILED(hr) )
               return hr;

            // get alignment
            CComPtr<IAlignment> alignment;
            m_pBridge->get_BridgeAlignment(&alignment);

            // intersect CL bearing with alignment
            CComPtr<IPoint2d> pntPier, pntBrg;
            pPierLine->get_AlignmentPoint(&pntPier);
            alignment->Intersect(centerline,pntPier,&pntBrg);

            // get station and offset of CL Bearing/Alignment intersection point
            CComPtr<IStation> objCLBrgStation;
            Float64 offset;
            alignment->Offset(pntBrg,&objCLBrgStation,&offset);
            ATLASSERT(IsZero(offset));

            // get the normal at this station
            CComPtr<IDirection> normal;
            alignment->Normal(CComVariant(objCLBrgStation),&normal);

            // create the work line
            CreateLine(pntBrg,normal,ppLine);
         }
         else
         {
            // CL Bearing line is located "brgOffset" along the centerline of this girder, measured
            // from the point where the centerline of this girder intersects with the CL pier
            // The CL Bearing line is parallel to the CL Pier line

            // This input combination is not supported
            ATLASSERT(false);

            return E_FAIL;
         }
      }
   }

   return S_OK;
}
