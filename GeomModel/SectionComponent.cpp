///////////////////////////////////////////////////////////////////////
// GeomModel - Geometric Modeling of shapes and sections
// Copyright © 1999-2023  Washington State Department of Transportation
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
#include <GeomModel/Section.h>
#include <GeomModel/Shape.h>
#include <GeomModel/ElasticProperties.h>
#include <GeomModel/MassProperties.h>

#include <algorithm>

using namespace WBFL::Geometry;

SectionComponent::SectionComponent(std::shared_ptr<Shape> shape, Float64 fgModE, Float64 fgDensity, Float64 bgModE, Float64 bgDensity, ComponentType componentType) :
   m_Shape(shape),
   m_fgDensity(fgDensity),
   m_fgModE(fgModE),
   m_bgDensity(bgDensity),
   m_bgModE(bgModE),
   m_ComponentType(componentType)
{
}

void SectionComponent::SetShape(std::shared_ptr<Shape> shape)
{
   m_Shape = shape;
}

const Shape& SectionComponent::GetShape() const
{
   return *m_Shape;
}

Shape& SectionComponent::GetShape()
{
   return *m_Shape;
}

void SectionComponent::SetForegroundModE(Float64 modE)
{
   m_fgModE = modE;
}

Float64 SectionComponent::GetForegroundModE() const
{
   return m_fgModE;
}

void SectionComponent::SetForegroundDensity(Float64 density)
{
   m_fgDensity = density;
}

Float64 SectionComponent::GetForegroundDensity() const
{
   return m_fgDensity;
}

void SectionComponent::SetBackgroundModE(Float64 modE)
{
   m_bgModE = modE;
}

Float64 SectionComponent::GetBackgroundModE() const
{
   return m_bgModE;
}

void SectionComponent::SetBackgroundDensity(Float64 density)
{
   m_bgDensity = density;
}

Float64 SectionComponent::GetBackgroundDensity() const
{
   return m_bgDensity;
}

void SectionComponent::SetComponentType(SectionComponent::ComponentType componentType)
{
   m_ComponentType = componentType;
}

SectionComponent::ComponentType SectionComponent::GetComponentType() const
{
   return m_ComponentType;
}
