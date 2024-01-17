///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
// Copyright © 1999-2024  Washington State Department of Transportation
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

// Index of composite section items
constexpr int BEAM       = 0;
constexpr int HAUNCH     = 1;
constexpr int SLAB       = 2;
constexpr int TRIB_LEFT  = 3;
constexpr int TRIB_RIGHT = 4;
constexpr int WS = 5;

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

void CompositeBeam::SetBeam(const Shape& beam)
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
   Float64 structural_slab_depth = tSlab - tSac;
   slab.SetHeight(structural_slab_depth);
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

void CompositeBeam::SetHookPoint(std::shared_ptr<Point2d> hookPnt)
{
   m_Section.SetHookPoint(hookPnt);
}

void CompositeBeam::SetHookPoint(const Point2d& hookPnt)
{
   m_Section.SetHookPoint(hookPnt);
}

std::shared_ptr<Point2d> CompositeBeam::GetHookPoint()
{
   return m_Section.GetHookPoint();
}

std::shared_ptr<const Point2d> CompositeBeam::GetHookPoint() const
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
