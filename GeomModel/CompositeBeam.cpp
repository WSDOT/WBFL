///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
// Copyright © 1999-2022  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the Alternate Route Library Open Source License as published by 
// the Washington State Department of Transportation, Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but is distributed 
// AS IS, WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See the Alternate Route Library Open Source 
// License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License 
// along with this program; if not, write to the Washington State Department of 
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////


#include <GeomModel/GeomModelLib.h>
#include <GeomModel/CompositeBeam.h>
#include <GeomModel/Rectangle.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Index of composite section items
#define BEAM       0
#define HAUNCH     1
#define SLAB       2
#define TRIB_LEFT  3
#define TRIB_RIGHT 4
#define WS         5

using namespace WBFL::Geometry;

CompositeBeam::CompositeBeam()
{
   Init();
}

CompositeBeam::CompositeBeam(const CompositeBeam& other)
{
   Init();
   Copy(other);
}

CompositeBeam::~CompositeBeam()
{
}

void CompositeBeam::Init()
{
   // Add a section for the beam
   // Use a dummy rectangle shape
   std::unique_ptr<Rectangle> beam = std::make_unique<Rectangle>();
   m_Section.AddComponent(std::move(beam), 1.0, 1.0, 0.0, 0.0, SectionComponent::ComponentType::Structural);

   std::unique_ptr<Rectangle> haunch = std::make_unique<Rectangle>();
   m_Section.AddComponent(std::move(haunch), 1.0, 1.0, 0.0, 0.0, SectionComponent::ComponentType::Structural);

   std::unique_ptr<Rectangle> slab = std::make_unique<Rectangle>();
   m_Section.AddComponent(std::move(slab), 1.0, 1.0, 0.0, 0.0, SectionComponent::ComponentType::Structural);

   std::unique_ptr<Rectangle> left_tributary_area = std::make_unique<Rectangle>();
   m_Section.AddComponent(std::move(left_tributary_area), 1.0, 1.0, 0.0, 0.0, SectionComponent::ComponentType::Nonstructural);

   std::unique_ptr<Rectangle> right_tributary_area = std::make_unique<Rectangle>();
   m_Section.AddComponent(std::move(right_tributary_area), 1.0, 1.0, 0.0, 0.0, SectionComponent::ComponentType::Nonstructural);

   std::unique_ptr<Rectangle> sacrifical_wearing_surface = std::make_unique<Rectangle>();
   m_Section.AddComponent(std::move(sacrifical_wearing_surface), 1.0, 1.0, 0.0, 0.0, SectionComponent::ComponentType::Nonstructural);

   UpdateShapeLocations();
}

CompositeBeam& CompositeBeam::operator=(const CompositeBeam& other)
{
   if (this != &other)
   {
      Copy(other);
   }
   return *this;
}

void CompositeBeam::Copy(const CompositeBeam& other)
{
   m_Section = other.m_Section;
}

void CompositeBeam::SetBeam(Shape& beam)
{
   SetBeam(beam.CreateClone());
}

void CompositeBeam::SetBeam(std::unique_ptr<Shape>&& beam)
{
   m_Section.GetComponent(BEAM).SetShape(std::move(beam));
}

Shape& CompositeBeam::GetBeam()
{
   return m_Section.GetComponent(BEAM).GetShape();
}

const Shape& CompositeBeam::GetBeam() const
{
   return m_Section.GetComponent(BEAM).GetShape();
}

void CompositeBeam::SetEffectiveSlabWidth(Float64 wEff)
{
   Float64 trib_width = GetTributarySlabWidth(); // get before modifying composite beam

   auto& slab_component = m_Section.GetComponent(SLAB);
   Rectangle& slab = dynamic_cast<Rectangle&>(slab_component.GetShape());
   slab.SetWidth(wEff);

   auto& wearing_surface_component = m_Section.GetComponent(WS);
   Rectangle& ws = dynamic_cast<Rectangle&>(wearing_surface_component.GetShape());
   ws.SetWidth(wEff);

   Float64 overhang = max((trib_width - wEff) / 2,0.0);
   if (0 <= overhang)
   {
      auto& left_trib_component = m_Section.GetComponent(TRIB_LEFT);
      Rectangle& left_trib = dynamic_cast<Rectangle&>(left_trib_component.GetShape());

      auto& right_trib_component = m_Section.GetComponent(TRIB_RIGHT);
      Rectangle& right_trib = dynamic_cast<Rectangle&>(right_trib_component.GetShape());

      left_trib.SetWidth(overhang);
      right_trib.SetWidth(overhang);
   }
}

Float64 CompositeBeam::GetEffectiveSlabWidth() const
{
   const auto& slab_component = m_Section.GetComponent(SLAB);
   const Rectangle& slab = dynamic_cast<const Rectangle&>(slab_component.GetShape());
   return slab.GetWidth();
}

void CompositeBeam::SetTributarySlabWidth(Float64 wTrib)
{
   Float64 wEff = GetEffectiveSlabWidth(); // get before modifing 

   if (wTrib < wEff) wEff = wTrib;

   auto& slab_component = m_Section.GetComponent(SLAB);
   Rectangle& slab = dynamic_cast<Rectangle&>(slab_component.GetShape());
   slab.SetWidth(wEff);

   auto& wearing_surface_component = m_Section.GetComponent(WS);
   Rectangle& ws = dynamic_cast<Rectangle&>(wearing_surface_component.GetShape());
   ws.SetWidth(wEff);

   Float64 overhang = max((wTrib - wEff) / 2, 0.0);
   if (0 <= overhang)
   {
      auto& left_trib_component = m_Section.GetComponent(TRIB_LEFT);
      Rectangle& left_trib = dynamic_cast<Rectangle&>(left_trib_component.GetShape());

      auto& right_trib_component = m_Section.GetComponent(TRIB_RIGHT);
      Rectangle& right_trib = dynamic_cast<Rectangle&>(right_trib_component.GetShape());

      left_trib.SetWidth(overhang);
      right_trib.SetWidth(overhang);
   }
}

Float64 CompositeBeam::GetTributarySlabWidth() const
{
   const auto& slab_component = m_Section.GetComponent(SLAB);
   const Rectangle& slab = dynamic_cast<const Rectangle&>(slab_component.GetShape());

   const auto& left_trib_component = m_Section.GetComponent(TRIB_LEFT);
   const Rectangle& left_trib = dynamic_cast<const Rectangle&>(left_trib_component.GetShape());

   const auto& right_trib_component = m_Section.GetComponent(TRIB_RIGHT);
   const Rectangle& right_trib = dynamic_cast<const Rectangle&>(right_trib_component.GetShape());

   return left_trib.GetWidth() + slab.GetWidth() + right_trib.GetWidth();
}

void CompositeBeam::SetGrossSlabDepth(Float64 tSlab)
{
   auto& slab_component = m_Section.GetComponent(SLAB);
   Rectangle& slab = dynamic_cast<Rectangle&>(slab_component.GetShape());

   auto& wearing_surface_component = m_Section.GetComponent(WS);
   Rectangle& ws = dynamic_cast<Rectangle&>(wearing_surface_component.GetShape());

   auto& left_trib_component = m_Section.GetComponent(TRIB_LEFT);
   Rectangle& left_trib = dynamic_cast<Rectangle&>(left_trib_component.GetShape());

   auto& right_trib_component = m_Section.GetComponent(TRIB_RIGHT);
   Rectangle& right_trib = dynamic_cast<Rectangle&>(right_trib_component.GetShape());

   Float64 wsDepth = ws.GetHeight();
   Float64 tStructuralSlab = tSlab - wsDepth;
   slab.SetHeight(tStructuralSlab);
   left_trib.SetHeight(tSlab);
   right_trib.SetHeight(tSlab);

   UpdateShapeLocations();
}

Float64 CompositeBeam::GetGrossSlabDepth() const
{
   const auto& slab_component = m_Section.GetComponent(SLAB);
   const Rectangle& slab = dynamic_cast<const Rectangle&>(slab_component.GetShape());

   const auto& wearing_surface_component = m_Section.GetComponent(WS);
   const Rectangle& ws = dynamic_cast<const Rectangle&>(wearing_surface_component.GetShape());

   return slab.GetHeight() + ws.GetHeight();
}

void CompositeBeam::SetSacrificialDepth(Float64 tSac)
{
   auto& slab_component = m_Section.GetComponent(SLAB);
   Rectangle& slab = dynamic_cast<Rectangle&>(slab_component.GetShape());

   auto& wearing_surface_component = m_Section.GetComponent(WS);
   Rectangle& ws = dynamic_cast<Rectangle&>(wearing_surface_component.GetShape());

   Float64 slabDepth = slab.GetHeight();
   Float64 wsDepth = ws.GetHeight();
   Float64 tSlab = slabDepth + wsDepth;

   slab.SetHeight(tSlab - tSac);
   ws.SetHeight(tSac);

   UpdateShapeLocations();
}

Float64 CompositeBeam::GetSacrificialDepth() const
{
   const auto& wearing_surface_component = m_Section.GetComponent(WS);
   const Rectangle& ws = dynamic_cast<const Rectangle&>(wearing_surface_component.GetShape());
   return ws.GetHeight();
}

void CompositeBeam::SetHaunchDepth(Float64 tHaunch)
{
   auto& haunch_component = m_Section.GetComponent(HAUNCH);
   Rectangle& haunch = dynamic_cast<Rectangle&>(haunch_component.GetShape());
   haunch.SetHeight(tHaunch);
   UpdateShapeLocations();
}

Float64 CompositeBeam::GetHaunchDepth() const
{
   const auto& haunch_component = m_Section.GetComponent(HAUNCH);
   const Rectangle& haunch = dynamic_cast<const Rectangle&>(haunch_component.GetShape());
   return haunch.GetHeight();
}

void CompositeBeam::SetHaunchWidth(Float64 wHaunch)
{
   auto& haunch_component = m_Section.GetComponent(HAUNCH);
   Rectangle& haunch = dynamic_cast<Rectangle&>(haunch_component.GetShape());
   haunch.SetWidth(wHaunch);
}

Float64 CompositeBeam::GetHaunchWidth() const
{
   const auto& haunch_component = m_Section.GetComponent(HAUNCH);
   const Rectangle& haunch = dynamic_cast<const Rectangle&>(haunch_component.GetShape());
   return haunch.GetWidth();
}


void CompositeBeam::SetSlabE(Float64 modE)
{
   m_Section.GetComponent(SLAB).SetForegroundModE(modE);
   m_Section.GetComponent(WS).SetForegroundModE(modE);
   m_Section.GetComponent(HAUNCH).SetForegroundModE(modE);
   m_Section.GetComponent(TRIB_LEFT).SetForegroundModE(modE);
   m_Section.GetComponent(TRIB_RIGHT).SetForegroundModE(modE);
}

Float64 CompositeBeam::GetSlabE() const
{
   return m_Section.GetComponent(SLAB).GetForegroundModE();
}

void CompositeBeam::SetSlabDensity(Float64 d)
{
   m_Section.GetComponent(SLAB).SetForegroundDensity(d);
   m_Section.GetComponent(WS).SetForegroundDensity(d);
   m_Section.GetComponent(HAUNCH).SetForegroundDensity(d);
   m_Section.GetComponent(TRIB_LEFT).SetForegroundDensity(d);
   m_Section.GetComponent(TRIB_RIGHT).SetForegroundDensity(d);
}

Float64 CompositeBeam::GetSlabDensity() const
{
   return m_Section.GetComponent(SLAB).GetForegroundDensity();
}

void CompositeBeam::SetBeamE(Float64 modE)
{
   m_Section.GetComponent(BEAM).SetForegroundModE(modE);
}

Float64 CompositeBeam::GetBeamE() const
{
   return m_Section.GetComponent(BEAM).GetForegroundModE();
}

void CompositeBeam::SetBeamDensity(Float64 d)
{
   m_Section.GetComponent(BEAM).SetForegroundDensity(d);
}

Float64 CompositeBeam::GetBeamDensity() const
{
   return m_Section.GetComponent(BEAM).GetForegroundDensity();
}

void CompositeBeam::SetHookPoint(std::shared_ptr<Point2d>& hookPnt)
{
   m_Section.SetHookPoint(hookPnt);
}

void CompositeBeam::SetHookPoint(const Point2d& hookPnt)
{
   m_Section.SetHookPoint(hookPnt);
}

std::shared_ptr<Point2d>& CompositeBeam::GetHookPoint()
{
   return m_Section.GetHookPoint();
}

const std::shared_ptr<Point2d>& CompositeBeam::GetHookPoint() const
{
   return m_Section.GetHookPoint();
}

Rect2d CompositeBeam::GetBoundingBox(bool bExcludeNonstructuralComponents) const
{
   return m_Section.GetBoundingBox(bExcludeNonstructuralComponents);
}

std::unique_ptr<Section> CompositeBeam::CreateClippedSection(const Line2d& line, Line2d::Side side) const
{
   return m_Section.CreateClippedSection(line, side);
}

std::unique_ptr<Section> CompositeBeam::CreateClippedSection(const Rect2d& r, Section::ClipRegion region) const
{
   return m_Section.CreateClippedSection(r, region);
}

Float64 CompositeBeam::GetQslab() const
{
   const auto& beam_component = m_Section.GetComponent(BEAM);
   ShapeProperties props = beam_component.GetShape().GetProperties();
   Float64 y = props.GetYtop() + props.GetYbottom();
   return GetQ(y);
}

Float64 CompositeBeam::GetQ(Float64 y) const
{
   ElasticProperties props = GetElasticProperties();
   const auto& cg = props.GetCentroid();
   Float64 Ycut = cg.Y() - props.GetYbottom() + y;
   Point2d p1(cg.X() + 2 * props.GetXleft(), Ycut);
   Point2d p2(cg.X() - 2 * props.GetXleft(), Ycut);
   Line2d line(p1, p2);

   Float64 Q = 0;
   auto clip = m_Section.CreateClippedSection(line, Line2d::Side::Left);
   if (clip != nullptr)
   {
      ElasticProperties clipElasticProps = clip->GetElasticProperties();

      const auto& component = m_Section.GetComponent(BEAM);
      Float64 beamE = component.GetForegroundModE();

      ShapeProperties clipProps = clipElasticProps.TransformProperties(beamE);

      // get area ablove/.below the clipping line
      Float64 area = clipProps.GetArea();

      // get the centroid of the clipped shape
      const auto& clipCG = clipProps.GetCentroid();

      // compute the first moment of area
      Q = area * (clipCG.Y() - cg.Y());
   }

   return Q;
}

ElasticProperties CompositeBeam::GetElasticProperties() const
{
   return m_Section.GetElasticProperties();
}

MassProperties CompositeBeam::GetMassProperties() const
{
   return m_Section.GetMassProperties();
}

void CompositeBeam::UpdateShapeLocations()
{
   auto& beam = m_Section.GetComponent(BEAM).GetShape();
   auto& haunch = m_Section.GetComponent(HAUNCH).GetShape();
   auto& slab = m_Section.GetComponent(SLAB).GetShape();
   auto& ws = m_Section.GetComponent(WS).GetShape();
   auto& left_trib = m_Section.GetComponent(TRIB_LEFT).GetShape();
   auto& right_trib = m_Section.GetComponent(TRIB_RIGHT).GetShape();

   // Align bottom center of haunch on top center of beam
   haunch.SetLocatorPoint(Shape::LocatorPoint::BottomCenter, beam.GetLocatorPoint(Shape::LocatorPoint::TopCenter));

   // Align bottom center of slab with top center of haunch
   slab.SetLocatorPoint(Shape::LocatorPoint::BottomCenter, haunch.GetLocatorPoint(Shape::LocatorPoint::TopCenter));

   // Align bottom center of wearing surface with top center of slab
   ws.SetLocatorPoint(Shape::LocatorPoint::BottomCenter, slab.GetLocatorPoint(Shape::LocatorPoint::TopCenter));

   // Align the bottom right of the left tributary area with the bottom left of the main slab
   left_trib.SetLocatorPoint(Shape::LocatorPoint::BottomRight, slab.GetLocatorPoint(Shape::LocatorPoint::BottomLeft));

   // Align the bottom left of the right tributary area with the bottom right of the main slab
   right_trib.SetLocatorPoint(Shape::LocatorPoint::BottomLeft, slab.GetLocatorPoint(Shape::LocatorPoint::BottomRight));
}

#if defined _DEBUG
bool CompositeBeam::AssertValid() const
{
   return m_Section.AssertValid();
}

void CompositeBeam::Dump(WBFL::Debug::LogContext& os) const
{
   m_Section.Dump(os);
}

#endif // _DEBUG

#if defined _UNITTEST
#include <GeomModel/PlateGirder.h>
#include <MathEx.h>
bool CompositeBeam::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("CompositeBeam");

   CompositeBeam beam;

   // define the girder (Plate Girder I-Beam)
   PlateGirder girder;
   girder.SetTopFlangeWidth(22);
   girder.SetTopFlangeThickness(1.25);
   girder.SetBottomFlangeWidth(22);
   girder.SetBottomFlangeThickness(2.25);
   girder.SetWebWidth(0.438);
   girder.SetWebHeight(122);

   beam.SetBeam(girder);
   beam.SetBeamDensity(420);
   beam.SetBeamE(1.0);

   // define the slab
   beam.SetGrossSlabDepth(7);
   beam.SetEffectiveSlabWidth(84);
   beam.SetHaunchWidth(22);
   beam.SetHaunchDepth(0.5);
   beam.SetSlabE(0.125);  // N = 8
   beam.SetSlabDensity(160.);

   // test bounding box
   Rect2d box = beam.GetBoundingBox(true);
   TRY_TESTME(IsEqual(box.Left(), -42.));
   TRY_TESTME(IsEqual(box.Right(), 42.));
   TRY_TESTME(IsEqual(box.Top(), 133.));
   TRY_TESTME(IsEqual(box.Bottom(), 0.));

   // Elastic Properties
   ElasticProperties props = beam.GetElasticProperties();
   TRY_TESTME(IsEqual(props.GetEA(), 205.311));
   TRY_TESTME(IsEqual(props.GetEIxx(), 627807.85259178));
   TRY_TESTME(IsEqual(props.GetEIyy(), 46379.979281332));
   TRY_TESTME(IsEqual(props.GetEIxy(), 0.));
   TRY_TESTME(IsEqual(props.GetXleft(), 42.));
   TRY_TESTME(IsEqual(props.GetXright(), 42.));
   TRY_TESTME(IsEqual(props.GetYtop(), 52.338305059154));
   TRY_TESTME(IsEqual(props.GetYbottom(), 80.661694640846));
   TRY_TESTME(IsEqual(props.GetCentroid().X(), 0.));
   TRY_TESTME(IsEqual(props.GetCentroid().Y(), 80.661694640846));

   // Check mass properties
   MassProperties mprops = beam.GetMassProperties();
   TRY_TESTME(IsEqual(mprops.GetMassPerLength(), 150623.12));

   // Test ClipIn
   // Clip so that only the top 1" of the slab remains
   Rect2d clipRect(-1000, 132, 1000, 1000);
   auto clip = beam.CreateClippedSection(clipRect, Section::ClipRegion::In);
   props = clip->GetElasticProperties();
   TRY_TESTME(IsEqual(props.GetEA(), 84. * 1. * 0.125));

   // Test clip with line
   Point2d p1 = clipRect.BottomRight();
   Point2d p2 = clipRect.BottomLeft();
   Line2d clipLine(p1, p2);
   clip = beam.CreateClippedSection(clipLine, Line2d::Side::Left);
   props = clip->GetElasticProperties();
   TRY_TESTME(IsEqual(props.GetEA(), 84. * 1. * 0.125));

   //auto hookPnt = beam.GetHookPoint();

   ////
   //// OffsetEx and Offset
   ////
   //Size2d size(10, 20);
   //beam.Offset(size);
   //CComPtr<ISize2d> size;
   //size.CoCreateInstance(CLSID_Size2d);
   //size->put_Dx(10);
   //size->put_Dy(20);
   //TRY_TEST(position->OffsetEx(nullptr), E_INVALIDARG);
   //TRY_TEST(position->OffsetEx(size), S_OK);

   //hookPnt->get_X(&x);
   //hookPnt->get_Y(&y);

   //TRY_TEST(IsEqual(x, 10.), true);
   //TRY_TEST(IsEqual(y, 20.), true);

   //TRY_TEST(position->Offset(10, 20), S_OK);

   //hookPnt->get_X(&x);
   //hookPnt->get_Y(&y);

   //TRY_TEST(IsEqual(x, 20.), true);
   //TRY_TEST(IsEqual(y, 40.), true);

   ////
   //// MoveEx
   ////
   //CComPtr<IPoint2d> from;
   //from.CoCreateInstance(CLSID_Point2d);
   //from->Move(10, 10);

   //CComPtr<IPoint2d> to;
   //to.CoCreateInstance(CLSID_Point2d);
   //to->Move(110, 110);

   //TRY_TEST(position->MoveEx(nullptr, to), E_INVALIDARG);
   //TRY_TEST(position->MoveEx(from, nullptr), E_INVALIDARG);
   //TRY_TEST(position->MoveEx(from, to), S_OK);

   //hookPnt->get_X(&x);
   //hookPnt->get_Y(&y);

   //TRY_TEST(IsEqual(x, 120.), true);
   //TRY_TEST(IsEqual(y, 140.), true);

   ////
   //// LocatorPoint property
   ////

   //to->Move(0, 0);
   //TRY_TEST(position->put_LocatorPoint(lpBottomCenter, to), S_OK);

   //hookPnt->get_X(&x);
   //hookPnt->get_Y(&y);

   //TRY_TEST(IsEqual(x, 0.), true);
   //TRY_TEST(IsEqual(y, 0.), true);

   //TRY_TEST(position->put_LocatorPoint(lpBottomLeft, nullptr), E_INVALIDARG);
   //TRY_TEST(position->get_LocatorPoint(lpBottomLeft, nullptr), E_POINTER);

   //// BottomLeft
   //to->Move(58, 100);
   //from.Release();
   //TRY_TEST(position->put_LocatorPoint(lpBottomLeft, to), S_OK);
   //TRY_TEST(position->get_LocatorPoint(lpBottomLeft, &from), S_OK);
   //from->get_X(&x);
   //from->get_Y(&y);
   //TRY_TEST(IsEqual(x, 58.0), true);
   //TRY_TEST(IsEqual(y, 100.0), true);
   //hookPnt->get_X(&x);
   //hookPnt->get_Y(&y);
   //TRY_TEST(IsEqual(x, 100.), true);
   //TRY_TEST(IsEqual(y, 100.), true);

   //// BottomCenter
   //to->Move(100, 100);
   //from.Release();
   //TRY_TEST(position->put_LocatorPoint(lpBottomCenter, to), S_OK);
   //TRY_TEST(position->get_LocatorPoint(lpBottomCenter, &from), S_OK);
   //from->get_X(&x);
   //from->get_Y(&y);
   //TRY_TEST(IsEqual(x, 100.0), true);
   //TRY_TEST(IsEqual(y, 100.0), true);
   //hookPnt->get_X(&x);
   //hookPnt->get_Y(&y);
   //TRY_TEST(IsEqual(x, 100.), true);
   //TRY_TEST(IsEqual(y, 100.), true);

   //// BottomRight
   //to->Move(142, 100);
   //from.Release();
   //TRY_TEST(position->put_LocatorPoint(lpBottomRight, to), S_OK);
   //TRY_TEST(position->get_LocatorPoint(lpBottomRight, &from), S_OK);
   //from->get_X(&x);
   //from->get_Y(&y);
   //TRY_TEST(IsEqual(x, 142.0), true);
   //TRY_TEST(IsEqual(y, 100.0), true);
   //hookPnt->get_X(&x);
   //hookPnt->get_Y(&y);
   //TRY_TEST(IsEqual(x, 100.), true);
   //TRY_TEST(IsEqual(y, 100.), true);

   //// CenterLeft
   //to->Move(58, 166.5);
   //from.Release();
   //TRY_TEST(position->put_LocatorPoint(lpCenterLeft, to), S_OK);
   //TRY_TEST(position->get_LocatorPoint(lpCenterLeft, &from), S_OK);
   //from->get_X(&x);
   //from->get_Y(&y);
   //TRY_TEST(IsEqual(x, 58.0), true);
   //TRY_TEST(IsEqual(y, 166.5), true);
   //hookPnt->get_X(&x);
   //hookPnt->get_Y(&y);
   //TRY_TEST(IsEqual(x, 100.), true);
   //TRY_TEST(IsEqual(y, 100.), true);

   //// CenterCenter
   //to->Move(100, 166.5);
   //from.Release();
   //TRY_TEST(position->put_LocatorPoint(lpCenterCenter, to), S_OK);
   //TRY_TEST(position->get_LocatorPoint(lpCenterCenter, &from), S_OK);
   //from->get_X(&x);
   //from->get_Y(&y);
   //TRY_TEST(IsEqual(x, 100.0), true);
   //TRY_TEST(IsEqual(y, 166.5), true);
   //hookPnt->get_X(&x);
   //hookPnt->get_Y(&y);
   //TRY_TEST(IsEqual(x, 100.), true);
   //TRY_TEST(IsEqual(y, 100.), true);

   //// CenterRight
   //to->Move(142, 166.5);
   //from.Release();
   //TRY_TEST(position->put_LocatorPoint(lpCenterRight, to), S_OK);
   //TRY_TEST(position->get_LocatorPoint(lpCenterRight, &from), S_OK);
   //from->get_X(&x);
   //from->get_Y(&y);
   //TRY_TEST(IsEqual(x, 142.0), true);
   //TRY_TEST(IsEqual(y, 166.5), true);
   //hookPnt->get_X(&x);
   //hookPnt->get_Y(&y);
   //TRY_TEST(IsEqual(x, 100.), true);
   //TRY_TEST(IsEqual(y, 100.), true);

   //// TopLeft
   //to->Move(58, 233);
   //from.Release();
   //TRY_TEST(position->put_LocatorPoint(lpTopLeft, to), S_OK);
   //TRY_TEST(position->get_LocatorPoint(lpTopLeft, &from), S_OK);
   //from->get_X(&x);
   //from->get_Y(&y);
   //TRY_TEST(IsEqual(x, 58.0), true);
   //TRY_TEST(IsEqual(y, 233.0), true);
   //hookPnt->get_X(&x);
   //hookPnt->get_Y(&y);
   //TRY_TEST(IsEqual(x, 100.), true);
   //TRY_TEST(IsEqual(y, 100.), true);

   //// TopCenter
   //to->Move(100, 233);
   //from.Release();
   //TRY_TEST(position->put_LocatorPoint(lpTopCenter, to), S_OK);
   //TRY_TEST(position->get_LocatorPoint(lpTopCenter, &from), S_OK);
   //from->get_X(&x);
   //from->get_Y(&y);
   //TRY_TEST(IsEqual(x, 100.0), true);
   //TRY_TEST(IsEqual(y, 233.0), true);
   //hookPnt->get_X(&x);
   //hookPnt->get_Y(&y);
   //TRY_TEST(IsEqual(x, 100.), true);
   //TRY_TEST(IsEqual(y, 100.), true);

   //// TopRight
   //to->Move(142, 233);
   //from.Release();
   //TRY_TEST(position->put_LocatorPoint(lpTopRight, to), S_OK);
   //TRY_TEST(position->get_LocatorPoint(lpTopRight, &from), S_OK);
   //from->get_X(&x);
   //from->get_Y(&y);
   //TRY_TEST(IsEqual(x, 142.0), true);
   //TRY_TEST(IsEqual(y, 233.0), true);
   //hookPnt->get_X(&x);
   //hookPnt->get_Y(&y);
   //TRY_TEST(IsEqual(x, 100.), true);
   //TRY_TEST(IsEqual(y, 100.), true);

   //// HookPoint
   //to->Move(100, 100);
   //from.Release();
   //TRY_TEST(position->put_LocatorPoint(lpHookPoint, to), S_OK);
   //TRY_TEST(position->get_LocatorPoint(lpHookPoint, &from), S_OK);
   //from->get_X(&x);
   //from->get_Y(&y);
   //TRY_TEST(IsEqual(x, 100.0), true);
   //TRY_TEST(IsEqual(y, 100.0), true);
   //hookPnt->get_X(&x);
   //hookPnt->get_Y(&y);
   //TRY_TEST(IsEqual(x, 100.), true);
   //TRY_TEST(IsEqual(y, 100.), true);

   ////
   //// Rotate and RotateEx
   ////
   //CComPtr<IPoint2d> rotPoint;
   //rotPoint.CoCreateInstance(CLSID_Point2d);

   //// Rotate about the origin of the coordinate system and check the bounding box
   //to->Move(100, 100);
   //TRY_TEST(position->put_LocatorPoint(lpBottomCenter, to), S_OK);
   //rotPoint->Move(0, 0);

   //TRY_TEST(position->RotateEx(nullptr, PI_OVER_2), E_INVALIDARG);
   //TRY_TEST(position->RotateEx(rotPoint, PI_OVER_2), S_OK);

   //CComQIPtr<ISection> section(position);
   //CComPtr<IRect2d> box;
   //section->get_BoundingBox(&box);
   //Float64 l, r, t, b;
   //box->get_Left(&l);
   //box->get_Right(&r);
   //box->get_Top(&t);
   //box->get_Bottom(&b);
   //TRY_TEST(IsEqual(l, -233.), true);
   //TRY_TEST(IsEqual(r, -100.), true);
   //TRY_TEST(IsEqual(t, 311.), true);
   //TRY_TEST(IsEqual(b, 58.), true);

   TESTME_EPILOG("CompositeBeam");
}
#endif // _UNITTEST
