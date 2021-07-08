///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Modeling Library
// Copyright © 1999-2021  Washington State Department of Transportation
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
#include "StdAfx.h"
#include "WBFLCOGO.h"
#include <WBFLCogo\CogoHelpers.h>
#include <WBFLGeometry\GeomHelpers.h>
#include "Angle.h"
#include "Direction.h"
#include "Station.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void cogoUtil::ToDMS(Float64 value,long* deg,long* min,Float64* sec)
{
   value *= 180.0/M_PI; // Convert value to degree

   long sign = BinarySign( value );
   value = fabs(value);

   *deg = (long)floor(value);
   value -= *deg;
   value *= 60;
   *min = (long)floor(value);
   value -= *min;
   *sec = value*60;

   if ( IsZero(60. - *sec,0.051) ) // 59.95 ==> 60.0, 59.94 ==> 59.9
   {
      *sec = 0.;
      *min += 1;
   }

   if ( *min == 60 )
   {
      *min = 0;
      *deg += 1;
   }

   *deg *= sign;
}

Float64 cogoUtil::FromDMS(long deg,long min,Float64 sec)
{
   Float64 angle;
   angle = BinarySign(deg)*(abs(deg) + (Float64)min/60. + sec/3600.);

   angle *= M_PI/180.; // Convert to radians

   return angle;
}

Float64 cogoUtil::NormalizeAngle(Float64 angle)
{
   // if angle is a large number, figure out how many 2PI's there are
   // and subtract out that number.
   int scale = (int)abs(angle / TWO_PI);
   if ( 1 < scale )
   {
      angle -= (scale*TWO_PI);
   }

   do
   {
      if ( angle < 0 )
      {
         angle += TWO_PI;
      }

      if ( angle >= TWO_PI )
      {
         angle -= TWO_PI;
      }
   } while ( angle < 0 || TWO_PI <= angle );

   return angle;
}

void cogoUtil::Inverse(IPoint2d* p1,IPoint2d* p2,Float64* pDist,IDirection** ppDir)
{
   Float64 x1, y1;
   Float64 x2, y2;
   p1->get_X(&x1);   p1->get_Y(&y1);
   p2->get_X(&x2);   p2->get_Y(&y2);

   Float64 dx = x2 - x1;
   Float64 dy = y2 - y1;

   *pDist = sqrt(dx*dx + dy*dy);
   Float64 dir  = atan2(dy,dx);

   if (IsZero(dir))
   {
      dir = 0.0;
   }
   else if ( dir < 0 )
   {
      dir += TWO_PI;
   }

   CreateDirection(dir,ppDir);
}

HRESULT CreateDirection(Float64 dir,IDirection** ppDirection)
{
   CComObject<CDirection>* pDirection;
   HRESULT hr = CComObject<CDirection>::CreateInstance(&pDirection);
   if ( SUCCEEDED(hr) )
   {
      *ppDirection = pDirection;
      (*ppDirection)->AddRef();
      (*ppDirection)->put_Value(dir);
   }

   return hr;
}


////////////////////////////////////////////////////////////////////
// Helper Methods
HRESULT cogoUtil::AngleFromVariant(VARIANT varAngle,IAngle** angle)
{
   CComPtr<IAngle> objAngle;
   switch( varAngle.vt )
   {
   case VT_UNKNOWN:
      varAngle.punkVal->QueryInterface(&objAngle);
      if ( objAngle == nullptr )
      {
         return E_INVALIDARG;
      }

      objAngle->QueryInterface(angle);
      break;

   case VT_DISPATCH:
      varAngle.pdispVal->QueryInterface(&objAngle);
      if ( objAngle == nullptr )
      {
         return E_INVALIDARG;
      }

      objAngle->QueryInterface(angle);
      break;

   case VT_BSTR:
      {
         CComPtr<IAngle> objAngle;
         objAngle.CoCreateInstance(CLSID_Angle);
         if ( SUCCEEDED(objAngle->FromString(varAngle.bstrVal)) )
         {
            (*angle) = objAngle;
            (*angle)->AddRef();
            break;
         }
         else
         {
            return E_INVALIDARG;
         }
      }

   default:
      {
         CComVariant var;
         if ( FAILED(::VariantChangeType(&var,&varAngle,0,VT_R8)))
         {
            return E_INVALIDARG;
         }

         CComObject<CAngle>* pAngle;
         CComObject<CAngle>::CreateInstance(&pAngle);
         pAngle->put_Value(var.dblVal);
         (*angle) = pAngle;
         (*angle)->AddRef();
      }
   }

   return S_OK;
}

HRESULT cogoUtil::DirectionFromVariant(VARIANT varDir,IDirection** dir)
{
   CComPtr<IDirection> objDir;
   switch( varDir.vt )
   {
   case VT_UNKNOWN:
      varDir.punkVal->QueryInterface(&objDir);
      if ( objDir == nullptr )
      {
         return E_INVALIDARG;
      }

      objDir->QueryInterface(dir);
      break;

   case VT_DISPATCH:
      varDir.pdispVal->QueryInterface(&objDir);
      if ( objDir == nullptr )
      {
         return E_INVALIDARG;
      }

      objDir->QueryInterface(dir);
      break;

   case VT_BSTR:
      {
         CComPtr<IDirection> objDir;
         objDir.CoCreateInstance(CLSID_Direction);
         if ( SUCCEEDED(objDir->FromString(varDir.bstrVal)) )
         {
            (*dir) = objDir;
            (*dir)->AddRef();
            break;
         }
         else
         {
            return E_INVALIDARG;
         }
      }

   default:
      {
         CComVariant var;
         if ( FAILED(::VariantChangeType(&var,&varDir,0,VT_R8)))
         {
            return E_INVALIDARG;
         }

         CComObject<CDirection>* pDir;
         CComObject<CDirection>::CreateInstance(&pDir);
         pDir->put_Value(var.dblVal);
         (*dir) = pDir;
         (*dir)->AddRef();
      }
   }

   return S_OK;
}

HRESULT cogoUtil::StationFromVariant(VARIANT varStation,bool bClone,IStation** station)
{
   CComPtr<IStation> objStation;
   switch( varStation.vt )
   {
   case VT_UNKNOWN:
      if ( varStation.punkVal == nullptr )
      {
         return E_INVALIDARG;
      }

      varStation.punkVal->QueryInterface(&objStation);
      if ( objStation.p == nullptr )
      {
         return E_INVALIDARG;
      }

      if ( bClone )
      {
         objStation->Clone(station);
      }
      else
      {
         objStation->QueryInterface(station);
      }
      break;

   case VT_DISPATCH:
      if ( varStation.pdispVal == nullptr )
      {
         return E_INVALIDARG;
      }

      varStation.pdispVal->QueryInterface(&objStation);
      if ( objStation.p == nullptr )
      {
         return E_INVALIDARG;
      }

      if ( bClone )
      {
         objStation->Clone(station);
      }
      else
      {
         objStation->QueryInterface(station);
      }
      break;

   case VT_BSTR:
      {
         CComObject<CStation>* pStation;
         CComObject<CStation>::CreateInstance(&pStation);
         CComPtr<IStation> sta(pStation); // need this so we don't leak pStation if this fails
         if ( FAILED(pStation->FromString(varStation.bstrVal,umUS)) ) // try US mode first
         {
            if ( FAILED(pStation->FromString(varStation.bstrVal,umSI)) ) // now try SI mode
            {
               // still failed... something is wrong
               return E_INVALIDARG;
            }
         }
         (*station) = pStation;
         (*station)->AddRef();
      }
      break;

   default:
      {
         CComVariant var;
         if ( FAILED(::VariantChangeType(&var,&varStation,0,VT_R8)))
         {
            return E_INVALIDARG;
         }

         CComObject<CStation>* pStation;
         CComObject<CStation>::CreateInstance(&pStation);
         pStation->put_Value(var.dblVal);
         (*station) = pStation;
         (*station)->AddRef();
      }
   }

   return S_OK;
}

bool cogoUtil::IsPointBeforeStart(IPoint2d* pStart,IPoint2d* pEnd,IPoint2d* pPoint)
{
   CComPtr<ICoordinateXform2d> xform;
   xform.CoCreateInstance(CLSID_CoordinateXform2d);

   CComPtr<IDirection> dir;
   Float64 dist;
   cogoUtil::Inverse(pStart,pEnd,&dist,&dir);
   
   Float64 angle;
   dir->get_Value(&angle);

   xform->putref_NewOrigin(pStart);
   xform->put_RotationAngle(angle);

   CComPtr<IPoint2d> p;
   p.CoCreateInstance(CLSID_Point2d);
   cogoUtil::CopyPoint(p,pPoint);

   xform->Xform(&(p.p),xfrmOldToNew);

   Float64 x;
   p->get_X(&x);

   return x < 0 ? true : false;
}

bool cogoUtil::IsPointAfterEnd(IPoint2d* pStart,IPoint2d* pEnd,IPoint2d* pPoint)
{
   CComPtr<ICoordinateXform2d> xform;
   xform.CoCreateInstance(CLSID_CoordinateXform2d);

   CComPtr<IDirection> dir;
   Float64 dist;
   cogoUtil::Inverse(pStart,pEnd,&dist,&dir);
   
   Float64 angle;
   dir->get_Value(&angle);

   xform->putref_NewOrigin(pEnd);
   xform->put_RotationAngle(angle);

   CComPtr<IPoint2d> p;
   p.CoCreateInstance(CLSID_Point2d);
   cogoUtil::CopyPoint(p,pPoint);

   xform->Xform(&(p.p),xfrmOldToNew);

   Float64 x;
   p->get_X(&x);

   return 0 < x ? true : false;
}

bool cogoUtil::IsEqual(IPoint2d* p1,IPoint2d* p2)
{
   ATLASSERT( p1 != 0 && p2 != 0 );

   Float64 x1,y1;
   p1->Location(&x1,&y1);

   Float64 x2,y2;
   p2->Location(&x2,&y2);

   return IsZero(x1-x2) && IsZero(y1-y2);
}

void cogoUtil::CopyPoint(IPoint2d* to,IPoint2d* from)
{
   Float64 x,y;
   from->Location(&x,&y);
   to->Move(x,y);
}

HRESULT cogoUtil::LocateByDistDir(IPoint2d* from,Float64 dist,IDirection* objDir,Float64 offset,IPoint2dFactory* pFactory,IPoint2d** ppoint)
{
   Float64 dx;
   Float64 dy;
   Float64 x;
   Float64 y;
   Float64 dir;

   from->Location(&x,&y);

   objDir->get_Value(&dir);

   Float64 sindir = sin( dir );
   Float64 cosdir = cos( dir );

   dx = dist * cosdir;
   dy = dist * sindir;

   // Point on line
   x += dx;
   y += dy;

   // Apply offset
   x += offset * sindir;
   y -= offset * cosdir;

   if (pFactory)
   {
      pFactory->CreatePoint(ppoint);
   }
   else
   {
      CComPtr<IPoint2d> p;
      p.CoCreateInstance(CLSID_Point2d);
      p.CopyTo(ppoint);
   }

   (*ppoint)->Move(x,y);

   return S_OK;
}

void cogoUtil::LineCircleIntersect(ILine2d* line,ICircle* circle,IPoint2d* pntNearest,IPoint2dFactory* pFactory,IPoint2d** newPnt)
{
   (*newPnt) = nullptr;

   CComPtr<IGeomUtil2d> geomUtil;
   geomUtil.CoCreateInstance(CLSID_GeomUtil);
   
   CComQIPtr<IGeomUtil> gu(geomUtil);
   CComQIPtr<IPoint2dFactory> factory2d(pFactory);
   gu->putref_Point2dFactory(factory2d);

   short nIntersect;
   CComPtr<IPoint2d> p1, p2;
   geomUtil->LineCircleIntersect(line,circle,&p1,&p2,&nIntersect);

   CComQIPtr<IPoint2d> pnt1(p1);
   CComQIPtr<IPoint2d> pnt2(p2);

   if ( nIntersect == 0 )
   {
      (*newPnt) = nullptr;
   }
   else if ( nIntersect == 1 )
   {
      (*newPnt) = pnt1;
      (*newPnt)->AddRef();
   }
   else
   {
      ATLASSERT(nIntersect == 2);

      Float64 d1, d2;
      geomUtil->Distance(pntNearest,pnt1,&d1);
      geomUtil->Distance(pntNearest,pnt2,&d2);

      if ( d2 < d1 )
      {
         (*newPnt) = pnt2;
         (*newPnt)->AddRef();
      }
      else
      {
         (*newPnt) = pnt1;
         (*newPnt)->AddRef();
      }
   }
}

void cogoUtil::GetBrgParts(Float64 brgVal,NSDirectionType *pnsDir, long *pDeg, long *pMin, Float64 *pSec, EWDirectionType *pewDir)
{
   Float64 dir = brgVal;

   *pnsDir = InRange( 0., brgVal, M_PI ) ? nsNorth : nsSouth;
   *pewDir = InRange( 0., brgVal, PI_OVER_2 ) || InRange( 1.5*M_PI, brgVal, TWO_PI) ? ewEast : ewWest;

   if ( InRange( 0.0, brgVal, PI_OVER_2 ) )
   {
      dir = PI_OVER_2 - brgVal;
   }
   else if ( InRange(PI_OVER_2,brgVal,M_PI) )
   {
      dir = brgVal - PI_OVER_2;
   }
   else if ( InRange(M_PI,brgVal,3*PI_OVER_2) )
   {
      dir = 3*PI_OVER_2 - brgVal;
   }
   else
   {
      dir = brgVal - 3*PI_OVER_2;
   }

   cogoUtil::ToDMS( dir, pDeg, pMin, pSec );
}


HRESULT cogoUtil::ParseAngleTags(std::_tstring& strTag,std::_tstring* strDegTag,std::_tstring* strMinTag,std::_tstring* strSecTag)
{
   std::_tstring::size_type posFirst = strTag.find(_T(","));
   std::_tstring::size_type posSecond = strTag.find(_T(","),posFirst+1);

   if (posFirst == std::_tstring::npos || posSecond == std::_tstring::npos )
   {
      return E_INVALIDARG;
   }

   strDegTag->assign(strTag,0,posFirst);
   strMinTag->assign(strTag,posFirst+1,posSecond-posFirst-1);
   strSecTag->assign(strTag,posSecond+1,strTag.size()-posFirst-1);

   return S_OK;
}

bool cogoUtil::IsEqual(IProfile* pProfile,IStation* pSta1,IStation* pSta2)
{
   CComPtr<IAlignment> alignment;
   if ( pProfile )
   {
      pProfile->get_Alignment(&alignment);
   }

   return IsEqual(alignment,pSta1,pSta2);
}

bool cogoUtil::IsEqual(IAlignment* pAlignment,IStation* pSta1,IStation* pSta2)
{
   CComPtr<IStationEquationCollection> equations;
   if ( pAlignment )
   {
      pAlignment->get_StationEquations(&equations);
   }

   return IsEqual(equations,pSta1,pSta2);
}

bool cogoUtil::IsEqual(IStationEquationCollection* pEquations,IStation* pSta1,IStation* pSta2)
{
   if ( pEquations )
   {
      Float64 sta1,sta2;
      pEquations->ConvertToNormalizedStation(CComVariant(pSta1),&sta1);
      pEquations->ConvertToNormalizedStation(CComVariant(pSta2),&sta2);
      return ::IsEqual(sta1,sta2);
   }
   else
   {
      ZoneIndexType zoneIdx1, zoneIdx2;
      Float64 sta1, sta2;
      pSta1->GetStation(&zoneIdx1,&sta1);
      pSta2->GetStation(&zoneIdx2,&sta2);

      if ( zoneIdx1 != zoneIdx2 )
      {
         return false;
      }

      return ::IsEqual(sta1,sta2);
   }

   ATLASSERT(false); // should never get here
   return false;
}

Float64 cogoUtil::Distance(IProfile* pProfile,IStation* pSta1,IStation* pSta2)
{
   CComPtr<IAlignment> alignment;
   if ( pProfile )
   {
      pProfile->get_Alignment(&alignment);
   }

   return Distance(alignment,pSta1,pSta2);
}

Float64 cogoUtil::Distance(IAlignment* pAlignment,IStation* pSta1,IStation* pSta2)
{
   CComPtr<IStationEquationCollection> equations;
   if ( pAlignment )
   {
      pAlignment->get_StationEquations(&equations);
   }

   return Distance(equations,pSta1,pSta2);
}

Float64 cogoUtil::Distance(IStationEquationCollection* pEquations,IStation* pSta1,IStation* pSta2)
{
   if ( pEquations )
   {
      Float64 sta1,sta2;
      pEquations->ConvertToNormalizedStation(CComVariant(pSta1),&sta1);
      pEquations->ConvertToNormalizedStation(CComVariant(pSta2),&sta2);
      return sta2-sta1;
   }
   else
   {
      ZoneIndexType zoneIdx1, zoneIdx2;
      Float64 sta1, sta2;
      pSta1->GetStation(&zoneIdx1,&sta1);
      pSta2->GetStation(&zoneIdx2,&sta2);

      ATLASSERT(zoneIdx1 == zoneIdx2);

      return sta2-sta1;
   }

   ATLASSERT(false); // should never get here
   return -99999;
}

Int8 cogoUtil::Compare(IProfile* pProfile,IStation* pSta1,IStation* pSta2)
{
   CComPtr<IAlignment> alignment;
   if ( pProfile )
   {
      pProfile->get_Alignment(&alignment);
   }

   return Compare(alignment,pSta1,pSta2);
}

Int8 cogoUtil::Compare(IAlignment* pAlignment,IStation* pSta1,IStation* pSta2)
{
   CComPtr<IStationEquationCollection> equations;
   if ( pAlignment )
   {
      pAlignment->get_StationEquations(&equations);
   }

   return Compare(equations,pSta1,pSta2);
}

Int8 cogoUtil::Compare(IStationEquationCollection* pEquations,IStation* pSta1,IStation* pSta2)
{
   if ( pEquations )
   {
      Float64 sta1,sta2;
      pEquations->ConvertToNormalizedStation(CComVariant(pSta1),&sta1);
      pEquations->ConvertToNormalizedStation(CComVariant(pSta2),&sta2);
      return IsZero(sta2-sta1) ? 0 : ::Sign(sta2-sta1);
   }
   else
   {
      ZoneIndexType zoneIdx1, zoneIdx2;
      Float64 sta1, sta2;
      pSta1->GetStation(&zoneIdx1,&sta1);
      pSta2->GetStation(&zoneIdx2,&sta2);

      ATLASSERT(zoneIdx1 == zoneIdx2);

      return IsZero(sta2 - sta1) ? 0 : ::Sign(sta2-sta1);
   }

   ATLASSERT(false); // should never get here
   return -2;
}

Float64 cogoUtil::GetNormalizedStationValue(IProfile* pProfile,IStation* pSta)
{
   CComPtr<IAlignment> alignment;
   if ( pProfile )
   {
      pProfile->get_Alignment(&alignment);
   }

   return GetNormalizedStationValue(alignment,pSta);
}

Float64 cogoUtil::GetNormalizedStationValue(IAlignment* pAlignment,IStation* pSta)
{
   CComPtr<IStationEquationCollection> equations;
   if ( pAlignment )
   {
      pAlignment->get_StationEquations(&equations);
   }

   return GetNormalizedStationValue(equations,pSta);
}

Float64 cogoUtil::GetNormalizedStationValue(IStationEquationCollection* pEquations,IStation* pSta)
{
   if ( pEquations )
   {
      Float64 station;
      pEquations->ConvertToNormalizedStation(CComVariant(pSta),&station);
      return station;
   }
   else
   {
      ZoneIndexType zoneIdx;
      Float64 station;
      pSta->GetStation(&zoneIdx,&station);

      ATLASSERT(zoneIdx == INVALID_INDEX);

      return station;
   }

   ATLASSERT(false); // should never get here
   return -99999;
}

void cogoUtil::IncrementStationBy(IProfile* pProfile,IStation* pStation,Float64 dist)
{
   CComPtr<IAlignment> alignment;
   if ( pProfile )
   {
      pProfile->get_Alignment(&alignment);
   }
   IncrementStationBy(alignment,pStation,dist);
}

void cogoUtil::IncrementStationBy(IAlignment* pAlignment,IStation* pStation,Float64 dist)
{
   CComPtr<IStationEquationCollection> equations;
   if ( pAlignment )
   {
      pAlignment->get_StationEquations(&equations);
   }

   IncrementStationBy(equations,pStation,dist);
}

void cogoUtil::IncrementStationBy(IStationEquationCollection* pEquations,IStation* pStation,Float64 dist)
{
   if ( pEquations )
   {
      pEquations->IncrementBy(pStation,dist);
   }
   else
   {
      ZoneIndexType zoneIdx;
      Float64 station;
      pStation->GetStation(&zoneIdx,&station);

      ATLASSERT(zoneIdx == INVALID_INDEX);
      station += dist;
      pStation->SetStation(zoneIdx,station);
   }
}

void cogoUtil::CreateStation(IProfile* pProfile,Float64 normalizedStation,IStation** pSta)
{
   CComPtr<IAlignment> alignment;
   if ( pProfile )
   {
      pProfile->get_Alignment(&alignment);
   }

   return CreateStation(alignment,normalizedStation,pSta);
}

void cogoUtil::CreateStation(IAlignment* pAlignment,Float64 normalizedStation,IStation** pSta)
{
   CComPtr<IStationEquationCollection> equations;
   if ( pAlignment )
   {
      pAlignment->get_StationEquations(&equations);
   }

   return CreateStation(equations,normalizedStation,pSta);
}

void cogoUtil::CreateStation(IStationEquationCollection* pEquations,Float64 normalizedStation,IStation** pSta)
{
   if ( pEquations )
   {
      pEquations->ConvertFromNormalizedStation(normalizedStation,pSta);
   }
   else
   {
      CComObject<CStation>* pStation;
      CComObject<CStation>::CreateInstance(&pStation);
      (*pSta) = pStation;
      (*pSta)->AddRef();
      (*pSta)->SetStation(INVALID_INDEX,normalizedStation);
   }
}

HRESULT cogoUtil::CreateParallelLine(IPoint2d* pnt, IDirection* objDir, Float64 offset, ILine2dFactory* pLineFactory, ILine2d** line)
{
   // Save the direction of the line before it is altered.
   Float64 dir;
   objDir->get_Value(&dir);

   // Get the offset point for line
   CComPtr<IPoint2d> pntLine;
   CComPtr<IDirection> objClone;
   objDir->Clone(&objClone);
   objClone->IncrementBy(CComVariant(-PI_OVER_2));

   HRESULT hr = cogoUtil::LocateByDistDir(pnt, offset, objClone, 0.0, nullptr, &pntLine);
   ATLASSERT(SUCCEEDED(hr));

   // Create a vector in the direction of line
   CComPtr<IVector2d> vec;
   vec.CoCreateInstance(CLSID_Vector2d);
   vec->put_X(cos(dir));
   vec->put_Y(sin(dir));

   // Create line
   CComPtr<ILine2d> newLine;
   if (pLineFactory)
      pLineFactory->CreateLine(&newLine);
   else
      newLine.CoCreateInstance(CLSID_Line2d);

   newLine->SetExplicit(pntLine, vec);

   *line = newLine;
   (*line)->AddRef();

   return S_OK;
}

HRESULT cogoUtil::IntersectBearings(IPoint2d* p1, VARIANT varDir1, Float64 offset1, IPoint2d* p2, VARIANT varDir2, Float64 offset2, IPoint2dFactory* pPointFactory, IPoint2d** point)
{
   CHECK_IN(p1);
   CHECK_IN(p2);
   CHECK_RETOBJ(point);

   HRESULT hr;

   // Get the input data and validate
   CComPtr<IPoint2d> pnt[2];
   pnt[0] = p1;
   pnt[1] = p2;

   CComPtr<IDirection> dir[2];
   hr = cogoUtil::DirectionFromVariant(varDir1, &dir[0]);
   if (FAILED(hr))
      return hr;

   hr = cogoUtil::DirectionFromVariant(varDir2, &dir[1]);
   if (FAILED(hr))
      return hr;

   Float64 offset[2];
   offset[0] = offset1;
   offset[1] = offset2;

   CComPtr<ILine2d> line[2];
   for (long i = 0; i < 2; i++)
   {
      cogoUtil::CreateParallelLine(pnt[i], dir[i], offset[i], nullptr/*line factory*/, &line[i]);
   }

   // Intersect the lines
   CComPtr<IPoint2d> p;
   hr = geomUtil::LineLineIntersect(line[0], line[1], pPointFactory, &p);
   if (FAILED(hr))
      return hr;

   if (p != nullptr)
   {
      p->QueryInterface(point);
   }
   else
   {
      *point = nullptr;
   }

   return S_OK;
}

HRESULT cogoUtil::IntersectBearingCircle(IPoint2d* pnt1, VARIANT varDir, Float64 offset, IPoint2d* pntCenter, Float64 radius, IPoint2d* pntNearest, IPoint2dFactory* pPointFactory, IPoint2d** point)
{
   CHECK_IN(pnt1);
   CHECK_IN(pntCenter);
   CHECK_IN(pntNearest);
   CHECK_RETOBJ(point);

   if (radius <= 0.0) return COGO_E_RADIUS;

   // Get the input data and validate
   HRESULT hr;


   CComPtr<IDirection> dir;
   hr = cogoUtil::DirectionFromVariant(varDir, &dir);
   if (FAILED(hr))
      return hr;

   CComPtr<ILine2d> line;
   cogoUtil::CreateParallelLine(pnt1, dir, offset, nullptr, &line);

   CComPtr<ICircle> circle;
   circle.CoCreateInstance(CLSID_Circle);
   circle->putref_Center(pntCenter);
   circle->put_Radius(radius);

   CComPtr<IPoint2d> p1, p2;
   short nIntersect;
   geomUtil::LineCircleIntersect(line, circle, pPointFactory, &p1, &p2, &nIntersect);

   if (nIntersect == 0)
   {
      (*point) = 0;
   }
   else if (nIntersect == 1)
   {
      p1.QueryInterface(point);
   }
   else
   {
      ATLASSERT(nIntersect == 2);

      Float64 d1, d2;
      p1->DistanceEx(pntNearest, &d1);
      p2->DistanceEx(pntNearest, &d2);

      if (d2 < d1)
      {
         p2.QueryInterface(point);
      }
      else
      {
         p1.QueryInterface(point);
      }
   }

   return S_OK;
}

HRESULT cogoUtil::IntersectCircles(IPoint2d* c1, Float64 r1, IPoint2d* c2, Float64 r2, IPoint2d* nearest, IPoint2dFactory* pPointFactory, IPoint2d** point)
{
   CHECK_IN(c1);
   CHECK_IN(c2);
   CHECK_IN(nearest);
   CHECK_RETOBJ(point);

   if (r1 <= 0.0 || r2 <= 0.0) return COGO_E_RADIUS;


   CComPtr<ICircle> circle1;
   circle1.CoCreateInstance(CLSID_Circle);
   circle1->putref_Center(c1);
   circle1->put_Radius(r1);

   CComPtr<ICircle> circle2;
   circle2.CoCreateInstance(CLSID_Circle);
   circle2->putref_Center(c2);
   circle2->put_Radius(r2);

   CComPtr<IPoint2d> p1, p2;
   short nIntersect;
   geomUtil::CircleCircleIntersect(circle1, circle2, pPointFactory, &p1, &p2, &nIntersect);

   if (nIntersect == 0)
   {
      (*point) = 0;
   }
   else if (nIntersect == 1)
   {
      p1.QueryInterface(point);
   }
   else
   {
      ATLASSERT(nIntersect == 2);

      Float64 d1, d2;
      p1->DistanceEx(nearest, &d1);
      p2->DistanceEx(nearest, &d2);

      if (d2 < d1)
      {
         p2.QueryInterface(point);
      }
      else
      {
         p1.QueryInterface(point);
      }
   }

   return S_OK;
}
