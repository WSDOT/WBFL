///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Modeling Library
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
#include "StdAfx.h"
#include "WBFLCOGO.h"
#include <WBFLCogo\CogoHelpers.h>
#include <WBFLGeometry\GeomHelpers.h>
#include "Angle.h"
#include "Direction.h"
#include "Station.h"
#include "StationEquation.h"
#include "ProfileElement.h"
#include "CircularCurve.h"
#include "CompoundCurve.h"
#include "TransitionCurve.h"
#include "CubicSpline.h"
#include "Path.h"
#include "Alignment.h"
#include "Profile.h"
#include "Surface.h"
#include "SurfaceTemplate.h"
#include "ProfilePoint.h"
#include "PathSegment.h"
#include "ProfileSegment.h"
#include "VerticalCurve.h"
#include "SurfacePoint.h"
#include "SurfaceProfile.h"
#include "SurfaceTemplateSegment.h"
#include "Superelevation.h"
#include "Widening.h"

#include "GirderLineFactory.h"
#include "DiaphragmLineFactory.h"
#include "LayoutLineFactory.h"
#include "PierLineFactory.h"
#include "PierLine.h"
#include "GirderLine.h"
#include "DiaphragmLine.h"
#include "DeckBoundary.h"
#include "DeckBoundaryFactory.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


void cogoUtil::Inverse(IPoint2d* p1, IPoint2d* p2, Float64* pDist, IDirection** ppDir)
{
   auto pnt1 = cogoUtil::GetInnerPoint(p1);
   auto pnt2 = cogoUtil::GetInnerPoint(p2);
   WBFL::COGO::Direction direction;
   std::tie(*pDist, direction) = WBFL::COGO::COGO::ComputeInverse(*pnt1, *pnt2);
   CreateDirection(direction, ppDir);
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

HRESULT cogoUtil::CreatePoint(std::shared_ptr<WBFL::Geometry::Point2d> point, IPoint2d** ppPoint)
{
   return geomUtil::CreatePoint(point, ppPoint);
}

HRESULT cogoUtil::CreatePoint(const WBFL::Geometry::Point2d& point, IPoint2d** ppPoint)
{
   return cogoUtil::CreatePoint(std::make_shared<WBFL::Geometry::Point2d>(point), ppPoint);
}

HRESULT cogoUtil::CreatePoint(std::shared_ptr<WBFL::Geometry::Point3d> point, IPoint3d** ppPoint)
{
   return geomUtil::CreatePoint(point, ppPoint);
}

HRESULT cogoUtil::CreatePoint(const WBFL::Geometry::Point3d& point, IPoint3d** ppPoint)
{
   return cogoUtil::CreatePoint(std::make_shared<WBFL::Geometry::Point3d>(point), ppPoint);
}

std::shared_ptr<WBFL::Geometry::Point2d> cogoUtil::GetInnerPoint(IPoint2d* pPoint)
{
   return geomUtil::GetInnerPoint(pPoint);
}

std::shared_ptr<WBFL::Geometry::Point3d> cogoUtil::GetInnerPoint(IPoint3d* pPoint)
{
   return geomUtil::GetInnerPoint(pPoint);
}

WBFL::Geometry::Point2d cogoUtil::GetPoint(IPoint2d* pPoint)
{
   return geomUtil::GetPoint(pPoint);
}

WBFL::Geometry::Line2d cogoUtil::GetLine(ILine2d* pLine)
{
   return geomUtil::GetLine(pLine);
}

WBFL::Geometry::LineSegment2d cogoUtil::GetLineSegment(ILineSegment2d* pLineSegment)
{
   return geomUtil::GetLineSegment(pLineSegment);
}

WBFL::Geometry::Circle cogoUtil::GetCircle(ICircle* pCircle)
{
   return geomUtil::GetCircle(pCircle);
}

WBFL::Geometry::Circle2d cogoUtil::GetCircle2d(ICircle* pCircle)
{
   return geomUtil::GetCircle2d(pCircle);
}

HRESULT cogoUtil::CreateLineSegment(const WBFL::Geometry::LineSegment2d& ls, ILineSegment2d** ppLineSegment)
{
   return geomUtil::CreateLineSegment(ls, ppLineSegment);
}

HRESULT cogoUtil::CreateLine(const WBFL::Geometry::Line2d& line, ILine2d** ppLine)
{
   return geomUtil::CreateLine(line, ppLine);
}

HRESULT cogoUtil::CreatePoints(const std::vector<WBFL::Geometry::Point2d>& points, IPoint2dCollection** ppPoints)
{
   return geomUtil::CreatePointCollection(points, ppPoints);
}

HRESULT cogoUtil::CreateAngle(const WBFL::COGO::Angle& angle, IAngle** ppAngle)
{
   return CreateAngle(std::make_shared<WBFL::COGO::Angle>(angle), ppAngle);
}

HRESULT cogoUtil::CreateAngle(std::shared_ptr<WBFL::COGO::Angle> angle, IAngle** ppAngle)
{
   CComObject<CAngle>* pAngle;
   CComObject<CAngle>::CreateInstance(&pAngle);
   pAngle->SetAngle(angle);
   (*ppAngle) = pAngle;
   (*ppAngle)->AddRef();
   return S_OK;
}

std::shared_ptr<WBFL::COGO::Angle> cogoUtil::GetInnerAngle(IAngle* pAngle)
{
   CAngle* angle = dynamic_cast<CAngle*>(pAngle);
   ATLASSERT(angle);
   return angle->GetAngle();
}

std::pair<HRESULT,WBFL::COGO::Angle> cogoUtil::AngleFromVariant(VARIANT varAngle)
{
   CComPtr<IAngle> angle;
   HRESULT hr = AngleFromVariant(varAngle, &angle);
   if (FAILED(hr))
      return std::make_pair(hr, WBFL::COGO::Angle(-9999999));

   Float64 value;
   angle->get_Value(&value);
   return std::make_pair(S_OK,WBFL::COGO::Angle(value));
}

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
         CComObject<CAngle>* pAngle;
         CComObject<CAngle>::CreateInstance(&pAngle);
         CComPtr<IAngle> objAngle = pAngle;
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

WBFL::COGO::Direction& cogoUtil::GetInnerDirection(IDirection* pDirection)
{
   CDirection* p = dynamic_cast<CDirection*>(pDirection);
   ATLASSERT(p);
   return p->GetDirection();
}

HRESULT cogoUtil::CreateDirection(const WBFL::COGO::Direction& direction, IDirection** ppDir)
{
   CComObject<CDirection>* pDirection;
   CComObject<CDirection>::CreateInstance(&pDirection);
   (*ppDir) = pDirection;
   (*ppDir)->AddRef();
   (*ppDir)->put_Value(direction.GetValue());
   return S_OK;
}

std::pair<HRESULT, WBFL::COGO::Direction> cogoUtil::DirectionFromVariant(VARIANT varDirection)
{
   HRESULT hr = S_OK;
   CComPtr<IDirection> objDir;

   if ((varDirection.vt == VT_UNKNOWN && varDirection.punkVal == nullptr) || (varDirection.vt == VT_DISPATCH) && varDirection.pdispVal == nullptr)
   {
      // null pointers are treated as a short hand for zero direction
      varDirection.vt = VT_R8;
      varDirection.dblVal = 0.0;
   }

   switch (varDirection.vt)
   {
   case VT_UNKNOWN:
      hr = varDirection.punkVal->QueryInterface(&objDir);
      break;

   case VT_DISPATCH:
      hr = varDirection.pdispVal->QueryInterface(&objDir);
      break;

   case VT_BSTR:
   {
      CComObject<CDirection>* pDirection;
      CComObject<CDirection>::CreateInstance(&pDirection);
      objDir = pDirection;
      hr = objDir->FromString(varDirection.bstrVal);
      if (FAILED(hr)) objDir.Release();
      break;
   }

   default:
   {
      CComVariant var;
      if (FAILED(::VariantChangeType(&var, &varDirection, 0, VT_R8)))
      {
         hr = E_INVALIDARG;
      }
      else
      {
         objDir.CoCreateInstance(CLSID_Direction);
         objDir->put_Value(var.dblVal);
      }
   }
   }

   if (FAILED(hr))
      return std::make_pair(hr, WBFL::COGO::Direction(-9999999));

   Float64 value;
   objDir->get_Value(&value);
   return std::make_pair(hr, WBFL::COGO::Direction(value));
}

HRESULT cogoUtil::CreateProfileElement(std::shared_ptr<WBFL::COGO::ProfileElement> pe, IProfileElement** ppProfileElement)
{
   auto segment = std::dynamic_pointer_cast<WBFL::COGO::ProfileSegment>(pe);
   auto vc = std::dynamic_pointer_cast<WBFL::COGO::VerticalCurve>(pe);
   if (segment)
   {
      CComObject<CProfileSegment>* pSegment;
      CComObject<CProfileSegment>::CreateInstance(&pSegment);
      pSegment->SetProfileSegment(segment);
      (*ppProfileElement) = pSegment;
      (*ppProfileElement)->AddRef();
   }
   else if (vc)
   {
      CComObject<CVerticalCurve>* pVC;
      CComObject<CVerticalCurve>::CreateInstance(&pVC);
      pVC->SetVerticalCurve(vc);
      (*ppProfileElement) = pVC;
      (*ppProfileElement)->AddRef();
   }
   else
   {
      ATLASSERT(false);// is there a new kind of profile element;
   }
   return S_OK;
}

std::shared_ptr<WBFL::COGO::ProfileElement> cogoUtil::GetInnerProfileElement(IProfileElement* pProfileElement)
{
   auto segment = dynamic_cast<CProfileSegment*>(pProfileElement);
   auto vc = dynamic_cast<CVerticalCurve*>(pProfileElement);

   std::shared_ptr<WBFL::COGO::ProfileElement> profile_element;
   if (segment)
   {
      profile_element = segment->GetProfileSegment();
   }
   else if (vc)
   {
      profile_element = vc->GetVerticalCurve();
   }
   else
   {
      ATLASSERT(false); // is there a new kind of profile element?
   }

   return profile_element;

}

HRESULT cogoUtil::CreatePathElement(std::shared_ptr<WBFL::COGO::PathElement> pe, IPathElement** ppPathElement)
{
   auto segment = std::dynamic_pointer_cast<WBFL::COGO::PathSegment>(pe);
   auto circular_curve = std::dynamic_pointer_cast<WBFL::COGO::CircularCurve>(pe);
   auto compound_curve = std::dynamic_pointer_cast<WBFL::COGO::CompoundCurve>(pe);
   auto transition_curve = std::dynamic_pointer_cast<WBFL::COGO::TransitionCurve>(pe);
   auto spline_curve = std::dynamic_pointer_cast<WBFL::COGO::CubicSpline>(pe);
   auto path = std::dynamic_pointer_cast<WBFL::COGO::Path>(pe);

   if (segment)
   {
      CComObject<CPathSegment>* pSegment;
      CComObject<CPathSegment>::CreateInstance(&pSegment);
      pSegment->SetPathSegment(segment);
      (*ppPathElement) = pSegment;
      (*ppPathElement)->AddRef();
   }
   else if (circular_curve)
   {
      CComObject<CCircularCurve>* pPE;
      CComObject<CCircularCurve>::CreateInstance(&pPE);
      pPE->SetCurve(circular_curve);
      (*ppPathElement) = pPE;
      (*ppPathElement)->AddRef();
   }
   else if (compound_curve)
   {
      CComObject<CCompoundCurve>* pPE;
      CComObject<CCompoundCurve>::CreateInstance(&pPE);
      pPE->SetCurve(compound_curve);
      (*ppPathElement) = pPE;
      (*ppPathElement)->AddRef();
   }
   else if (transition_curve)
   {
      CComObject<CTransitionCurve>* pPE;
      CComObject<CTransitionCurve>::CreateInstance(&pPE);
      pPE->SetCurve(transition_curve);
      (*ppPathElement) = pPE;
      (*ppPathElement)->AddRef();
   }
   else if (spline_curve)
   {
      CComObject<CCubicSpline>* pPE;
      CComObject<CCubicSpline>::CreateInstance(&pPE);
      pPE->SetSpline(spline_curve);
      (*ppPathElement) = pPE;
      (*ppPathElement)->AddRef();
   }
   else if (path)
   {
      CComObject<CPath>* pPE;
      CComObject<CPath>::CreateInstance(&pPE);
      pPE->SetPath(path);
      (*ppPathElement) = pPE;
      (*ppPathElement)->AddRef();
   }
   else
   {
      ATLASSERT(false); // is there a new kind of path element?
   }
   return S_OK;
}

std::shared_ptr<WBFL::COGO::PathElement> cogoUtil::GetInnerPathElement(IPathElement* pPathElement)
{
   auto segment = dynamic_cast<CPathSegment*>(pPathElement);
   auto circular_curve = dynamic_cast<CCircularCurve*>(pPathElement);
   auto compound_curve = dynamic_cast<CCompoundCurve*>(pPathElement);
   auto transition_curve = dynamic_cast<CTransitionCurve*>(pPathElement);
   auto spline_curve = dynamic_cast<CCubicSpline*>(pPathElement);
   auto path = dynamic_cast<CPath*>(pPathElement);

   std::shared_ptr<WBFL::COGO::PathElement> path_element;
   if (segment)
   {
      path_element = segment->GetPathSegment();
   }
   else if (circular_curve)
   {
      path_element = circular_curve->GetCurve();
   }
   else if (compound_curve)
   {
      path_element = compound_curve->GetCurve();
   }
   else if (transition_curve)
   {
      path_element = transition_curve->GetCurve();
   }
   else if (spline_curve)
   {
      path_element = spline_curve->GetSpline();
   }
   else if (path)
   {
      path_element = path->GetPath();
   }
   else
   {
      ATLASSERT(false); // is there a new kind of path element?
   }

   return path_element;
}

HRESULT cogoUtil::CreatePathSegment(std::shared_ptr<WBFL::COGO::PathSegment> pathSegment, IPathSegment** ppPathSegment)
{
   CComObject<CPathSegment>* pSegment;
   CComObject<CPathSegment>::CreateInstance(&pSegment);
   pSegment->SetPathSegment(pathSegment);
   (*ppPathSegment) = pSegment;
   (*ppPathSegment)->AddRef();
   return S_OK;
}

std::shared_ptr<WBFL::COGO::PathSegment> cogoUtil::GetInnerPathSegment(IPathSegment* pPathSegment)
{
   CPathSegment* segment = dynamic_cast<CPathSegment*>(pPathSegment);
   ATLASSERT(segment);
   return segment->GetPathSegment();
}

HRESULT cogoUtil::CreateProfile(std::shared_ptr<WBFL::COGO::Profile> profile, IProfile** ppProfile)
{
   CComObject<CProfile>* pProfile;
   CComObject<CProfile>::CreateInstance(&pProfile);
   pProfile->SetProfile(profile);
   (*ppProfile) = pProfile;
   (*ppProfile)->AddRef();
   return S_OK;
}

std::shared_ptr<WBFL::COGO::Profile> cogoUtil::GetInnerProfile(IProfile* pProfile)
{
   CProfile* profile = dynamic_cast<CProfile*>(pProfile);
   ATLASSERT(profile);
   return profile->GetProfile();
}

HRESULT cogoUtil::CreatePath(std::shared_ptr<WBFL::COGO::Path> path, IPath** ppPath)
{
   CComObject<CPath>* pPath;
   CComObject<CPath>::CreateInstance(&pPath);
   pPath->SetPath(path);
   (*ppPath) = pPath;
   (*ppPath)->AddRef();
   return S_OK;
}

std::shared_ptr<WBFL::COGO::Path> cogoUtil::GetInnerPath(IPath* pPath)
{
   CPath* path = dynamic_cast<CPath*>(pPath);
   ATLASSERT(path);
   return path->GetPath();
}

HRESULT cogoUtil::CreateAlignment(std::shared_ptr<WBFL::COGO::Alignment> alignment, IAlignment** ppAlignment)
{
   CComObject<CAlignment>* pAlignment;
   CComObject<CAlignment>::CreateInstance(&pAlignment);
   pAlignment->SetAlignment(alignment);
   (*ppAlignment) = pAlignment;
   (*ppAlignment)->AddRef();
   return S_OK;
}

std::shared_ptr<WBFL::COGO::Alignment> cogoUtil::GetInnerAlignment(IAlignment* pAlignment)
{
   CAlignment* alignment = dynamic_cast<CAlignment*>(pAlignment);
   ATLASSERT(alignment);
   return alignment->GetAlignment();
}

HRESULT cogoUtil::CreateSurface(std::shared_ptr<WBFL::COGO::Surface> surface, ISurface** ppSurface)
{
   CComObject<CSurface>* pSurface;
   CComObject<CSurface>::CreateInstance(&pSurface);
   pSurface->SetSurface(surface);
   (*ppSurface) = pSurface;
   (*ppSurface)->AddRef();
   return S_OK;
}

std::shared_ptr<WBFL::COGO::Surface> cogoUtil::GetInnerSurface(ISurface* pSurface)
{
   CSurface* surface = dynamic_cast<CSurface*>(pSurface);
   ATLASSERT(surface);
   return surface->GetSurface();
}

std::shared_ptr<WBFL::COGO::ProfilePoint> cogoUtil::GetInnerProfilePoint(IProfilePoint* pProfilePoint)
{
   CProfilePoint* point = dynamic_cast<CProfilePoint*>(pProfilePoint);
   ATLASSERT(point);
   return point->GetProfilePoint();
}

WBFL::COGO::ProfilePoint cogoUtil::GetProfilePoint(IProfilePoint* pProfilePoint)
{
   CProfilePoint* point = dynamic_cast<CProfilePoint*>(pProfilePoint);
   ATLASSERT(point);
   return *(point->GetProfilePoint());
}

HRESULT cogoUtil::CreateProfilePoint(const WBFL::COGO::ProfilePoint& profilePoint, IProfilePoint** ppProfilePoint)
{
   return cogoUtil::CreateProfilePoint(std::make_shared<WBFL::COGO::ProfilePoint>(profilePoint), ppProfilePoint);
}

HRESULT cogoUtil::CreateProfilePoint(std::shared_ptr<WBFL::COGO::ProfilePoint> profilePoint, IProfilePoint** ppProfilePoint)
{
   CComObject<CProfilePoint>* pPP;
   CComObject<CProfilePoint>::CreateInstance(&pPP);
   pPP->SetProfilePoint(profilePoint);
   (*ppProfilePoint) = pPP;
   (*ppProfilePoint)->AddRef();
   return S_OK;
}

std::shared_ptr<WBFL::COGO::SurfacePoint> cogoUtil::GetInnerSurfacePoint(ISurfacePoint* pSurfacePoint)
{
   CSurfacePoint* point = dynamic_cast<CSurfacePoint*>(pSurfacePoint);
   ATLASSERT(point);
   return point->GetSurfacePoint();
}

HRESULT cogoUtil::CreateSurfacePoint(std::shared_ptr<WBFL::COGO::SurfacePoint> surfacePoint, ISurfacePoint** ppSurfacePoint)
{
   CComObject<CSurfacePoint>* pPP;
   CComObject<CSurfacePoint>::CreateInstance(&pPP);
   pPP->SetSurfacePoint(surfacePoint);
   (*ppSurfacePoint) = pPP;
   (*ppSurfacePoint)->AddRef();
   return S_OK;
}

std::shared_ptr<WBFL::COGO::SurfaceProfile> cogoUtil::GetInnerSurfaceProfile(ISurfaceProfile* pSurfaceProfile)
{
   CSurfaceProfile* profile = dynamic_cast<CSurfaceProfile*>(pSurfaceProfile);
   ATLASSERT(profile);
   return profile->GetSurfaceProfile();
}

HRESULT cogoUtil::CreateSurfaceProfile(ISurface* pSurface,std::shared_ptr<WBFL::COGO::SurfaceProfile> surfaceProfile, ISurfaceProfile** ppSurfaceProfile)
{
   CComObject<CSurfaceProfile>* pPP;
   CComObject<CSurfaceProfile>::CreateInstance(&pPP);
   pPP->putref_Surface(pSurface);
   pPP->SetSurfaceProfile(surfaceProfile);
   (*ppSurfaceProfile) = pPP;
   (*ppSurfaceProfile)->AddRef();
   return S_OK;
}

std::shared_ptr<WBFL::COGO::SurfaceTemplate> cogoUtil::GetInnerSurfaceTemplate(ISurfaceTemplate* pSurfaceTemplate)
{
   CSurfaceTemplate* pTemplate = dynamic_cast<CSurfaceTemplate*>(pSurfaceTemplate);
   ATLASSERT(pTemplate);
   return pTemplate->GetSurfaceTemplate();
}

HRESULT cogoUtil::CreateSurfaceTemplate(ISurface* pSurface, std::shared_ptr<WBFL::COGO::SurfaceTemplate> st, ISurfaceTemplate** ppSurfaceTemplate)
{
   CComObject<CSurfaceTemplate>* pST;
   CComObject<CSurfaceTemplate>::CreateInstance(&pST);
   pST->putref_Surface(pSurface);
   pST->SetSurfaceTemplate(st);
   (*ppSurfaceTemplate) = pST;
   (*ppSurfaceTemplate)->AddRef();
   return S_OK;
}

HRESULT cogoUtil::CreateSurfaceTemplateSegment(const WBFL::COGO::SurfaceTemplateSegment& segment,ISurfaceTemplateSegment** ppSegment)
{
   CComObject<CSurfaceTemplateSegment>* pST;
   CComObject<CSurfaceTemplateSegment>::CreateInstance(&pST);
   pST->SetSurfaceTemplateSegment(segment);
   (*ppSegment) = pST;
   (*ppSegment)->AddRef();
   return S_OK;
}

std::shared_ptr<WBFL::COGO::Superelevation> cogoUtil::GetInnerSuperelevation(ISuperelevation* pSuperelevation)
{
   CSuperelevation* super = dynamic_cast<CSuperelevation*>(pSuperelevation);
   ATLASSERT(super);
   return super->GetSuperelevation();
}

HRESULT cogoUtil::CreateSuperelevation(std::shared_ptr<WBFL::COGO::Superelevation> superelevation, ISuperelevation** ppSuperelevation)
{
   CComObject<CSuperelevation>* pSuperelevation;
   CComObject<CSuperelevation>::CreateInstance(&pSuperelevation);
   pSuperelevation->SetSuperelevation(superelevation);
   (*ppSuperelevation) = pSuperelevation;
   (*ppSuperelevation)->AddRef();
   return S_OK;
}

std::shared_ptr<WBFL::COGO::Widening> cogoUtil::GetInnerWidening(IWidening* pWidening)
{
   CWidening* widening = dynamic_cast<CWidening*>(pWidening);
   ATLASSERT(widening);
   return widening->GetWidening();
}

HRESULT cogoUtil::CreateWidening(std::shared_ptr<WBFL::COGO::Widening> widening, IWidening** ppWidening)
{
   CComObject<CWidening>* pWidening;
   CComObject<CWidening>::CreateInstance(&pWidening);
   pWidening->SetWidening(widening);
   (*ppWidening) = pWidening;
   (*ppWidening)->AddRef();
   return S_OK;
}

std::shared_ptr<WBFL::COGO::CompoundCurve> cogoUtil::GetInnerCompoundCurve(ICompoundCurve* pCurve)
{
   CCompoundCurve* curve = dynamic_cast<CCompoundCurve*>(pCurve);
   ATLASSERT(curve);
   return curve->GetCurve();
}

HRESULT cogoUtil::CreateCompoundCurve(std::shared_ptr<WBFL::COGO::CompoundCurve> curve, ICompoundCurve** ppCurve)
{
   CComObject<CCompoundCurve>* pCurve;
   CComObject<CCompoundCurve>::CreateInstance(&pCurve);
   pCurve->SetCurve(curve);
   (*ppCurve) = pCurve;
   (*ppCurve)->AddRef();
   return S_OK;
}

std::shared_ptr<WBFL::COGO::CircularCurve> cogoUtil::GetInnerCircularCurve(ICircularCurve* pCurve)
{
   CCircularCurve* curve = dynamic_cast<CCircularCurve*>(pCurve);
   ATLASSERT(curve);
   return curve->GetCurve();
}

HRESULT cogoUtil::CreateCircularCurve(std::shared_ptr<WBFL::COGO::CircularCurve> curve, ICircularCurve** ppCurve)
{
   CComObject<CCircularCurve>* pCurve;
   CComObject<CCircularCurve>::CreateInstance(&pCurve);
   pCurve->SetCurve(curve);
   (*ppCurve) = pCurve;
   (*ppCurve)->AddRef();
   return S_OK;
}

std::shared_ptr<WBFL::COGO::TransitionCurve> cogoUtil::GetInnerTransitionCurve(ITransitionCurve* pCurve)
{
   CTransitionCurve* curve = dynamic_cast<CTransitionCurve*>(pCurve);
   ATLASSERT(curve);
   return curve->GetCurve();
}

HRESULT cogoUtil::CreateTransitionCurve(std::shared_ptr<WBFL::COGO::TransitionCurve> curve, ITransitionCurve** ppCurve)
{
   CComObject<CTransitionCurve>* pCurve;
   CComObject<CTransitionCurve>::CreateInstance(&pCurve);
   pCurve->SetCurve(curve);
   (*ppCurve) = pCurve;
   (*ppCurve)->AddRef();
   return S_OK;
}

std::shared_ptr<WBFL::COGO::CubicSpline> cogoUtil::GetInnerCubicSpline(ICubicSpline* pCurve)
{
   CCubicSpline* curve = dynamic_cast<CCubicSpline*>(pCurve);
   ATLASSERT(curve);
   return curve->GetSpline();
}

HRESULT cogoUtil::CreateCubicSpline(std::shared_ptr<WBFL::COGO::CubicSpline> curve, ICubicSpline** ppCurve)
{
   CComObject<CCubicSpline>* pCurve;
   CComObject<CCubicSpline>::CreateInstance(&pCurve);
   pCurve->SetSpline(curve);
   (*ppCurve) = pCurve;
   (*ppCurve)->AddRef();
   return S_OK;
}

std::shared_ptr<WBFL::COGO::ProfileSegment> cogoUtil::GetInnerProfileSegment(IProfileSegment* pSegment)
{
   CProfileSegment* segment = dynamic_cast<CProfileSegment*>(pSegment);
   ATLASSERT(segment);
   return segment->GetProfileSegment();
}

HRESULT cogoUtil::CreateProfileSegment(std::shared_ptr<WBFL::COGO::ProfileSegment> segment, IProfileSegment** ppSegment)
{
   CComObject<CProfileSegment>* pSegment;
   CComObject<CProfileSegment>::CreateInstance(&pSegment);
   pSegment->SetProfileSegment(segment);
   (*ppSegment) = pSegment;
   (*ppSegment)->AddRef();
   return S_OK;
}

std::shared_ptr<WBFL::COGO::VerticalCurve> cogoUtil::GetInnerVerticalCurve(IVerticalCurve* pVertCurve)
{
   CVerticalCurve* pVC = dynamic_cast<CVerticalCurve*>(pVertCurve);
   ATLASSERT(pVC);
   return pVC->GetVerticalCurve();
}

HRESULT cogoUtil::CreateVerticalCurve(std::shared_ptr<WBFL::COGO::VerticalCurve> vc, IVerticalCurve** ppVertCurve)
{
   CComObject<CVerticalCurve>* pVC;
   CComObject<CVerticalCurve>::CreateInstance(&pVC);
   pVC->SetVerticalCurve(vc);
   (*ppVertCurve) = pVC;
   (*ppVertCurve)->AddRef();
   return S_OK;
}

HRESULT cogoUtil::CreateStationEquation(const WBFL::COGO::StationEquation& equation, IStationEquation** ppEquation)
{
   CComObject<CStationEquation>* pEquation;
   CComObject<CStationEquation>::CreateInstance(&pEquation);
   pEquation->SetEquation(equation);
   (*ppEquation) = pEquation;
   (*ppEquation)->AddRef();
   return S_OK;
}

WBFL::COGO::Station& cogoUtil::GetInnerStation(IStation* pStation)
{
   CStation* s = dynamic_cast<CStation*>(pStation);
   ATLASSERT(s);
   return s->GetStation();
}

HRESULT cogoUtil::CreateStation(const WBFL::COGO::Station& station, IStation** ppStation)
{
   CComObject<CStation>* pStation;
   CComObject<CStation>::CreateInstance(&pStation);
   pStation->SetStation(station);
   (*ppStation) = pStation;
   (*ppStation)->AddRef();
   return S_OK;
}

std::pair<HRESULT, WBFL::COGO::Station> cogoUtil::StationFromVariant(VARIANT varStation)
{
   HRESULT hr = S_OK;
   CComPtr<IStation> objStation;
   switch (varStation.vt)
   {
   case VT_UNKNOWN:
      if (varStation.punkVal == nullptr)
      {
         hr = E_INVALIDARG;
      }
      else
      {
         varStation.punkVal->QueryInterface(&objStation);
         if (objStation.p == nullptr)
         {
            hr = E_INVALIDARG;
         }
      }
      break;

   case VT_DISPATCH:
      if (varStation.pdispVal == nullptr)
      {
         hr = E_INVALIDARG;
      }
      else
      {
         varStation.pdispVal->QueryInterface(&objStation);
         if (objStation.p == nullptr)
         {
            hr = E_INVALIDARG;
         }
      }
      break;

   case VT_BSTR:
   {
      CComObject<CStation>* pStation;
      CComObject<CStation>::CreateInstance(&pStation);
      CComPtr<IStation> sta(pStation); // need this so we don't leak pStation if this fails
      if (FAILED(pStation->FromString(varStation.bstrVal, umUS))) // try US mode first
      {
         if (FAILED(pStation->FromString(varStation.bstrVal, umSI))) // now try SI mode
         {
            // still failed... something is wrong
            hr = E_INVALIDARG;
         }
      }
      else
      {
         objStation = pStation;
      }
   }
   break;

   default:
   {
      CComVariant var;
      if (FAILED(::VariantChangeType(&var, &varStation, 0, VT_R8)))
      {
         hr = E_INVALIDARG;
      }
      else
      {
         CComObject<CStation>* pStation;
         CComObject<CStation>::CreateInstance(&pStation);
         pStation->put_Value(var.dblVal);
         objStation = pStation;
      }
   }
   }
   ATLASSERT(hr == S_OK);
   Float64 value; objStation->get_Value(&value);
   IndexType zoneIdx; objStation->get_StationZoneIndex(&zoneIdx);
   return std::make_pair(hr, WBFL::COGO::Station(zoneIdx, value));
}

bool cogoUtil::IsPointBeforeStart(IPoint2d* pStart,IPoint2d* pEnd,IPoint2d* pPoint)
{
   auto start = GetPoint(pStart);
   auto end = GetPoint(pEnd);
   auto point = GetPoint(pPoint);
   return WBFL::COGO::COGO::IsPointBeforeStart(start, end, point);
}

bool cogoUtil::IsPointAfterEnd(IPoint2d* pStart,IPoint2d* pEnd,IPoint2d* pPoint)
{
   auto start = GetPoint(pStart);
   auto end = GetPoint(pEnd);
   auto point = GetPoint(pPoint);
   return WBFL::COGO::COGO::IsPointAfterEnd(start, end, point);
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

HRESULT cogoUtil::LocateByDistDir(IPoint2d* pFrom,Float64 dist,IDirection* objDir,Float64 offset,IPoint2d** ppPoint)
{
   auto from = GetPoint(pFrom);
   Float64 direction;
   objDir->get_Value(&direction);
   auto point = WBFL::COGO::COGO::LocateByDistanceAndDirection(from, dist, direction, offset);
   return CreatePoint(point, ppPoint);
}

HRESULT cogoUtil::LineCircleIntersect(ILine2d* pLine,ICircle* pCircle,IPoint2d* pntNearest,IPoint2d** newPnt)
{
   auto line = GetLine(pLine);
   auto circle = GetCircle2d(pCircle);
   auto nearest = GetPoint(pntNearest);
   auto point = WBFL::COGO::COGO::IntersectLineAndCircle(line, circle, nearest);
   return CreatePoint(point, newPnt);
}

HRESULT cogoUtil::ParseAngleTags(std::_tstring& strTag,std::_tstring* strDegTag,std::_tstring* strMinTag,std::_tstring* strSecTag)
{
   try
   {
      std::tie(*strDegTag, *strMinTag, *strSecTag) = WBFL::COGO::COGO::ParseAngleTags(strTag);
   }
   catch (...)
   {
      return E_INVALIDARG;
   }
   return S_OK;
}

HRESULT cogoUtil::CreateArray(const std::vector<Float64>& values, IDblArray** ppArray)
{
   CComPtr<IDblArray> array;
   array.CoCreateInstance(CLSID_DblArray);
   for (const auto& value : values)
   {
      array->Add(value);
   }

   return array.CopyTo(ppArray);
}

std::vector<Float64> cogoUtil::GetArray(IDblArray* pArray)
{
   IndexType nItems;
   pArray->get_Count(&nItems);
   std::vector<Float64> vValues;
   vValues.reserve(nItems);
   for (IndexType i = 0; i < nItems; i++)
   {
      Float64 value;
      pArray->get_Item(i, &value);
      vValues.push_back(value);
   }

   return vValues;

}

std::shared_ptr<WBFL::COGO::GirderLineFactory> cogoUtil::GetInnerFactory(IGirderLineFactory* pFactory)
{
   CGirderLineFactory* p = dynamic_cast<CGirderLineFactory*>(pFactory);
   ATLASSERT(p);
   return p->GetFactory();
}

std::shared_ptr<WBFL::COGO::DiaphragmLineFactory> cogoUtil::GetInnerFactory(IDiaphragmLineFactory* pFactory)
{
   CDiaphragmLineFactory* p = dynamic_cast<CDiaphragmLineFactory*>(pFactory);
   ATLASSERT(p);
   return p->GetFactory();
}

std::shared_ptr<WBFL::COGO::LayoutLineFactory> cogoUtil::GetInnerFactory(ILayoutLineFactory* pFactory)
{
   CLayoutLineFactory* p = dynamic_cast<CLayoutLineFactory*>(pFactory);
   ATLASSERT(p);
   return p->GetFactory();
}

std::shared_ptr<WBFL::COGO::PierLineFactory> cogoUtil::GetInnerFactory(IPierLineFactory* pFactory)
{
   CPierLineFactory* p = dynamic_cast<CPierLineFactory*>(pFactory);
   ATLASSERT(p);
   return p->GetFactory();
}

std::shared_ptr<WBFL::COGO::DeckBoundaryFactory> cogoUtil::GetInnerFactory(IDeckBoundaryFactory* pFactory)
{
   CDeckBoundaryFactory* p = dynamic_cast<CDeckBoundaryFactory*>(pFactory);
   ATLASSERT(p);
   return p->GetFactory();
}

HRESULT cogoUtil::CreatePierLine(std::shared_ptr<WBFL::COGO::PierLine> pierLine, IPierLine** ppPierLine)
{
   CComObject<CPierLine>* pPierLine;
   HRESULT hr = CComObject<CPierLine>::CreateInstance(&pPierLine);
   if (SUCCEEDED(hr))
   {
      *ppPierLine = pPierLine;
      (*ppPierLine)->AddRef();
      pPierLine->SetPierLine(pierLine);
   }
   return hr;
}

HRESULT cogoUtil::CreateGirderLine(std::shared_ptr<WBFL::COGO::GirderLine> girderLine, IGirderLine** ppGirderLine)
{
   CComObject<CGirderLine>* pGirderLine;
   HRESULT hr = CComObject<CGirderLine>::CreateInstance(&pGirderLine);
   if (SUCCEEDED(hr))
   {
      *ppGirderLine = pGirderLine;
      (*ppGirderLine)->AddRef();
      pGirderLine->SetGirderLine(girderLine);
   }
   return hr;
}

HRESULT cogoUtil::CreateDiaphragmLine(std::shared_ptr<WBFL::COGO::DiaphragmLine> diaphragmLine, IDiaphragmLine** ppDiaphragmLine)
{
   CComObject<CDiaphragmLine>* pDiaphragmLine;
   HRESULT hr = CComObject<CDiaphragmLine>::CreateInstance(&pDiaphragmLine);
   if (SUCCEEDED(hr))
   {
      *ppDiaphragmLine = pDiaphragmLine;
      (*ppDiaphragmLine)->AddRef();
      pDiaphragmLine->SetDiaphragmLine(diaphragmLine);
   }
   return hr;
}

HRESULT cogoUtil::CreateDeckBoundary(std::shared_ptr<WBFL::COGO::DeckBoundary> deckBoundary, IDeckBoundary** ppDeckBoundary)
{
   CComObject<CDeckBoundary>* pDeckBoundary;
   HRESULT hr = CComObject<CDeckBoundary>::CreateInstance(&pDeckBoundary);
   if (SUCCEEDED(hr))
   {
      *ppDeckBoundary = pDeckBoundary;
      (*ppDeckBoundary)->AddRef();
      pDeckBoundary->SetDeckBoundary(deckBoundary);
   }
   return hr;
}
