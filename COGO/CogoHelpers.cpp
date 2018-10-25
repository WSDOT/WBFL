///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Modeling Library
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
#include "StdAfx.h"
#include "WBFLCOGO.h"
#include "CogoHelpers.h"
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
   if ( scale > 1 )
      angle -= (scale*TWO_PI);

   do
   {
      if ( angle < 0 )
         angle += TWO_PI;

      if ( angle >= TWO_PI )
         angle -= TWO_PI;

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
      dir = 0.0;
   else if ( dir < 0 )
      dir += TWO_PI;

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
      if ( objAngle == NULL )
         return E_INVALIDARG;

      objAngle->QueryInterface(angle);
      break;

   case VT_DISPATCH:
      varAngle.pdispVal->QueryInterface(&objAngle);
      if ( objAngle == NULL )
         return E_INVALIDARG;

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
            return E_INVALIDARG;

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
      if ( objDir == NULL )
         return E_INVALIDARG;

      objDir->QueryInterface(dir);
      break;

   case VT_DISPATCH:
      varDir.pdispVal->QueryInterface(&objDir);
      if ( objDir == NULL )
         return E_INVALIDARG;

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
            return E_INVALIDARG;

         CComObject<CDirection>* pDir;
         CComObject<CDirection>::CreateInstance(&pDir);
         pDir->put_Value(var.dblVal);
         (*dir) = pDir;
         (*dir)->AddRef();
      }
   }

   return S_OK;
}

HRESULT cogoUtil::StationFromVariant(VARIANT varStation,IStation** station)
{
   CComPtr<IStation> objStation;
   switch( varStation.vt )
   {
   case VT_UNKNOWN:
      varStation.punkVal->QueryInterface(&objStation);
      if ( objStation.p == NULL )
         return E_INVALIDARG;

      objStation->QueryInterface(station);
      break;

   case VT_DISPATCH:
      varStation.pdispVal->QueryInterface(&objStation);
      if ( objStation.p == NULL )
         return E_INVALIDARG;

      objStation->QueryInterface(station);
      break;

   default:
      {
         CComVariant var;
         if ( FAILED(::VariantChangeType(&var,&varStation,0,VT_R8)))
            return E_INVALIDARG;

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
   p1->get_X(&x1);
   p1->get_Y(&y1);

   Float64 x2,y2;
   p2->get_X(&x2);
   p2->get_Y(&y2);

   return IsZero(x1-x2) && IsZero(y1-y2);
}

void cogoUtil::CopyPoint(IPoint2d* to,IPoint2d* from)
{
   Float64 x,y;
   from->get_X(&x);
   from->get_Y(&y);

   to->put_X(x);
   to->put_Y(y);
}

HRESULT cogoUtil::LocateByDistDir(IPoint2d* from,Float64 dist,IDirection* objDir,Float64 offset,IPoint2dFactory* pFactory,IPoint2d** ppoint)
{
   Float64 dx;
   Float64 dy;
   Float64 x;
   Float64 y;
   Float64 dir;

   from->get_X(&x);
   from->get_Y(&y);

   objDir->get_Value(&dir);

   dx = dist * cos( dir );
   dy = dist * sin( dir );

   // Point on line
   x += dx;
   y += dy;

   // Apply offset
   x += offset * sin( dir );
   y -= offset * cos( dir );

   pFactory->CreatePoint(ppoint);

   (*ppoint)->Move(x,y);

   return S_OK;
}

void cogoUtil::LineCircleIntersect(ILine2d* line,ICircle* circle,IPoint2d* pntNearest,IPoint2dFactory* pFactory,IPoint2d** newPnt)
{
   (*newPnt) = NULL;

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
      (*newPnt) = NULL;
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
      dir = PI_OVER_2 - brgVal;
   else if ( InRange(PI_OVER_2,brgVal,M_PI) )
      dir = brgVal - PI_OVER_2;
   else if ( InRange(M_PI,brgVal,3*PI_OVER_2) )
      dir = 3*PI_OVER_2 - brgVal;
   else
      dir = brgVal - 3*PI_OVER_2;

   cogoUtil::ToDMS( dir, pDeg, pMin, pSec );
}


HRESULT cogoUtil::ParseAngleTags(std::string& strTag,std::string* strDegTag,std::string* strMinTag,std::string* strSecTag)
{
   std::string::size_type posFirst = strTag.find(",");
   std::string::size_type posSecond = strTag.find(",",posFirst+1);

   if (posFirst == std::string::npos || posSecond == std::string::npos )
      return E_INVALIDARG;

   strDegTag->assign(strTag,0,posFirst);
   strMinTag->assign(strTag,posFirst+1,posSecond-posFirst-1);
   strSecTag->assign(strTag,posSecond+1,strTag.size()-posFirst-1);

   return S_OK;
}
