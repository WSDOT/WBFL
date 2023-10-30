///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Modeling Library
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

#pragma once

#include <WBFLCogo\COGOExp.h>
#include <CoordGeom/CoordGeom.h>
#include <string>

/// @brief  Utility class for COGO related operations. 
class COGOCLASS cogoUtil
{
public:
   static std::pair<HRESULT, WBFL::COGO::Direction> DirectionFromVariant(VARIANT varDirection);
   static WBFL::COGO::Direction& GetInnerDirection(IDirection* pDirection);
   static HRESULT CreateDirection(const WBFL::COGO::Direction& direction, IDirection** ppDir);

   static std::pair<HRESULT, WBFL::COGO::Station> StationFromVariant(VARIANT varStation);
   static WBFL::COGO::Station& GetInnerStation(IStation* pStation);
   static HRESULT CreateStation(const WBFL::COGO::Station& station, IStation** pStation);

   static HRESULT CreateStationEquation(const WBFL::COGO::StationEquation& equation, IStationEquation** ppEquation);

   static HRESULT CreateProfileElement(std::shared_ptr<WBFL::COGO::ProfileElement> pe, IProfileElement** ppProfileElement);
   static std::shared_ptr<WBFL::COGO::ProfileElement> GetInnerProfileElement(IProfileElement* pProfileElement);

   static HRESULT CreatePathElement(std::shared_ptr<WBFL::COGO::PathElement> pe, IPathElement** ppPathElement);
   static std::shared_ptr<WBFL::COGO::PathElement> GetInnerPathElement(IPathElement* pPathElement);

   static HRESULT CreatePathSegment(std::shared_ptr<WBFL::COGO::PathSegment> pathSegment, IPathSegment** ppPathSegment);
   static std::shared_ptr<WBFL::COGO::PathSegment> GetInnerPathSegment(IPathSegment* pPathSegment);

   static HRESULT CreateProfile(std::shared_ptr<WBFL::COGO::Profile> profile, IProfile** ppProfile);
   static std::shared_ptr<WBFL::COGO::Profile> GetInnerProfile(IProfile* pProfile);

   static HRESULT CreatePath(std::shared_ptr<WBFL::COGO::Path> path, IPath** ppPath);
   static std::shared_ptr<WBFL::COGO::Path> GetInnerPath(IPath* pPath);

   static HRESULT CreateAlignment(std::shared_ptr<WBFL::COGO::Alignment> alignment, IAlignment** ppAlignment);
   static std::shared_ptr<WBFL::COGO::Alignment> GetInnerAlignment(IAlignment* pAlignment);

   static HRESULT CreateSurface(std::shared_ptr<WBFL::COGO::Surface> surface, ISurface** ppSurface);
   static std::shared_ptr<WBFL::COGO::Surface> GetInnerSurface(ISurface* pSurface);

   static std::shared_ptr<WBFL::COGO::ProfilePoint> GetInnerProfilePoint(IProfilePoint* pProfilePoint);
   static WBFL::COGO::ProfilePoint GetProfilePoint(IProfilePoint* pProfilePoint);
   static HRESULT CreateProfilePoint(std::shared_ptr<WBFL::COGO::ProfilePoint> profilePoint, IProfilePoint** ppProfilePoint);
   static HRESULT CreateProfilePoint(const WBFL::COGO::ProfilePoint& profilePoint, IProfilePoint** ppProfilePoint);

   static std::shared_ptr<WBFL::COGO::SurfacePoint> GetInnerSurfacePoint(ISurfacePoint* pSurfacePoint);
   static HRESULT CreateSurfacePoint(std::shared_ptr<WBFL::COGO::SurfacePoint> surfacePoint, ISurfacePoint** ppSurfacePoint);

   static std::shared_ptr<WBFL::COGO::SurfaceProfile> GetInnerSurfaceProfile(ISurfaceProfile* pSurfaceProfile);
   static HRESULT CreateSurfaceProfile(ISurface* pSurface, std::shared_ptr<WBFL::COGO::SurfaceProfile> surfaceProfile, ISurfaceProfile** ppSurfaceProfile);

   static std::shared_ptr<WBFL::COGO::SurfaceTemplate> GetInnerSurfaceTemplate(ISurfaceTemplate* pSurfaceTemplate);
   static HRESULT CreateSurfaceTemplate(ISurface* pSurface,std::shared_ptr<WBFL::COGO::SurfaceTemplate> st, ISurfaceTemplate** ppSurfaceTemplate);

   static HRESULT CreateSurfaceTemplateSegment(const WBFL::COGO::SurfaceTemplateSegment& segment, ISurfaceTemplateSegment** ppSegment);

   static std::shared_ptr<WBFL::COGO::Superelevation> GetInnerSuperelevation(ISuperelevation* pSuperelevation);
   static HRESULT CreateSuperelevation(std::shared_ptr<WBFL::COGO::Superelevation> superelevation, ISuperelevation** ppSuperelevation);

   static std::shared_ptr<WBFL::COGO::Widening> GetInnerWidening(IWidening* pWidening);
   static HRESULT CreateWidening(std::shared_ptr<WBFL::COGO::Widening> widening, IWidening** ppWidening);

   static std::shared_ptr<WBFL::COGO::CompoundCurve> GetInnerCompoundCurve(ICompoundCurve* pCurve);
   static HRESULT CreateCompoundCurve(std::shared_ptr<WBFL::COGO::CompoundCurve> curve, ICompoundCurve** ppCurve);

   static std::shared_ptr<WBFL::COGO::CircularCurve> GetInnerCircularCurve(ICircularCurve* pCurve);
   static HRESULT CreateCircularCurve(std::shared_ptr<WBFL::COGO::CircularCurve> curve, ICircularCurve** ppCurve);

   static std::shared_ptr<WBFL::COGO::TransitionCurve> GetInnerTransitionCurve(ITransitionCurve* pCurve);
   static HRESULT CreateTransitionCurve(std::shared_ptr<WBFL::COGO::TransitionCurve> curve, ITransitionCurve** ppCurve);

   static std::shared_ptr<WBFL::COGO::CubicSpline> GetInnerCubicSpline(ICubicSpline* pCurve);
   static HRESULT CreateCubicSpline(std::shared_ptr<WBFL::COGO::CubicSpline> curve, ICubicSpline** ppCurve);

   static std::shared_ptr<WBFL::COGO::ProfileSegment> GetInnerProfileSegment(IProfileSegment* pCurve);
   static HRESULT CreateProfileSegment(std::shared_ptr<WBFL::COGO::ProfileSegment> curve, IProfileSegment** ppCurve);

   static std::shared_ptr<WBFL::COGO::VerticalCurve> GetInnerVerticalCurve(IVerticalCurve* pVertCurve);
   static HRESULT CreateVerticalCurve(std::shared_ptr<WBFL::COGO::VerticalCurve> vc, IVerticalCurve** ppVertCurve);

   static HRESULT LocateByDistDir(IPoint2d* from,Float64 dist,IDirection* dir,Float64 offset,IPoint2d** ppoint);

   static HRESULT AngleFromVariant(VARIANT varAngle, IAngle** angle);
   static std::pair<HRESULT, WBFL::COGO::Angle> AngleFromVariant(VARIANT varAngle);
   static HRESULT CreateAngle(const WBFL::COGO::Angle& angle, IAngle** ppAngle);
   static HRESULT CreateAngle(std::shared_ptr<WBFL::COGO::Angle> angle, IAngle** ppAngle);
   static std::shared_ptr<WBFL::COGO::Angle> GetInnerAngle(IAngle* pAngle);

   static HRESULT CreatePoint(std::shared_ptr<WBFL::Geometry::Point2d> point, IPoint2d** ppPoint);
   static HRESULT CreatePoint(const WBFL::Geometry::Point2d& point, IPoint2d** ppPoint);
   static HRESULT CreatePoint(std::shared_ptr<WBFL::Geometry::Point3d> point, IPoint3d** ppPoint);
   static HRESULT CreatePoint(const WBFL::Geometry::Point3d& point, IPoint3d** ppPoint);
   static std::shared_ptr<WBFL::Geometry::Point2d> GetInnerPoint(IPoint2d* pPoint);
   static std::shared_ptr<WBFL::Geometry::Point3d> GetInnerPoint(IPoint3d* pPoint);
   static WBFL::Geometry::Point2d GetPoint(IPoint2d* pPoint);
   static WBFL::Geometry::Line2d GetLine(ILine2d* pLine);
   static WBFL::Geometry::LineSegment2d GetLineSegment(ILineSegment2d* pLineSegment);
   static WBFL::Geometry::Circle GetCircle(ICircle* pCircle);
   static WBFL::Geometry::Circle2d GetCircle2d(ICircle* pCircle);
   static HRESULT CreateLineSegment(const WBFL::Geometry::LineSegment2d& ls, ILineSegment2d** ppLineSegment);
   static HRESULT CreateLine(const WBFL::Geometry::Line2d& line, ILine2d** ppLine);

   static HRESULT CreatePoints(const std::vector<WBFL::Geometry::Point2d>& points, IPoint2dCollection** ppPoints);

   static bool IsEqual(IPoint2d* p1,IPoint2d* p2);
   static void CopyPoint(IPoint2d* to,IPoint2d* from);
   static HRESULT LineCircleIntersect(ILine2d* line,ICircle* circle,IPoint2d* pntNearest,IPoint2d** newPnt);

   // returns true if pPoint is on the line formed by pStart and pEnd and comes before pStart
   static bool IsPointBeforeStart(IPoint2d* pStart,IPoint2d* pEnd,IPoint2d* pPoint);

   // returns true if pPoint is on the line formed by pStart and pEnd and comes after pEnd
   static bool IsPointAfterEnd(IPoint2d* pStart,IPoint2d* pEnd,IPoint2d* pPoint);

   // Solves the inverse problem for points (x1,y1) and (x2,y2);
   static void Inverse(IPoint2d* p1, IPoint2d* p2, Float64* pDist, IDirection** ppDir); 
   static HRESULT ParseAngleTags(std::_tstring& strTag,std::_tstring* strDegTag,std::_tstring* strMinTag,std::_tstring* strSecTag);

   static HRESULT CreateArray(const std::vector<Float64>& values, IDblArray** ppArray);
   static std::vector<Float64> GetArray(IDblArray* pArray);

   static std::shared_ptr<WBFL::COGO::LayoutLineFactory> GetInnerFactory(ILayoutLineFactory* pFactory);
   static std::shared_ptr<WBFL::COGO::PierLineFactory> GetInnerFactory(IPierLineFactory* pFactory);
   static std::shared_ptr<WBFL::COGO::GirderLineFactory> GetInnerFactory(IGirderLineFactory* pFactory);
   static std::shared_ptr<WBFL::COGO::DiaphragmLineFactory> GetInnerFactory(IDiaphragmLineFactory* pFactory);
   static std::shared_ptr<WBFL::COGO::DeckBoundaryFactory> GetInnerFactory(IDeckBoundaryFactory* pFactory);
   static HRESULT CreatePierLine(std::shared_ptr<WBFL::COGO::PierLine> pierLine, IPierLine** ppPierLine);
   static HRESULT CreateGirderLine(std::shared_ptr<WBFL::COGO::GirderLine> girderLine, IGirderLine** ppGirderLine);
   static HRESULT CreateDiaphragmLine(std::shared_ptr<WBFL::COGO::DiaphragmLine> diaphragmLine, IDiaphragmLine** ppDiaphragmLine);
   static HRESULT CreateDeckBoundary(std::shared_ptr<WBFL::COGO::DeckBoundary> deckBoundary, IDeckBoundary** ppDeckBoundary);

private:
   cogoUtil() = delete;
   cogoUtil(const cogoUtil& rOther) = delete;
   cogoUtil& operator=(const cogoUtil& rOther) = delete;
};

