///////////////////////////////////////////////////////////////////////
// CoordGeom - Coordinate Geometry Library
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

#include <CoordGeom/CoordGeomLib.h>
#include <CoordGeom/Superelevation.h>
#include "SuperelevationImpl.h"

using namespace WBFL::COGO;

std::shared_ptr<Superelevation> Superelevation::Create()
{
   std::shared_ptr<Superelevation> s(new Superelevation());
   return s;
}

std::shared_ptr<Superelevation> Superelevation::Create(const Superelevation& superelevation)
{
   std::shared_ptr<Superelevation> s(new Superelevation(superelevation));
   return s;
}

std::shared_ptr<Superelevation> Superelevation::Create(const Station& beginTransitionStation, const Station& beginFullSuperStation, const Station& endFullSuperStation, const Station& endTransitionStation,
   Float64 rate, IndexType pivotPointIdx, TransitionType beginTransitionType, Float64 beginL1, Float64 beginL2, TransitionType endTransitionType, Float64 endL1, Float64 endL2)
{
   std::shared_ptr<Superelevation> superelevation(new Superelevation());
   superelevation->Init(beginTransitionStation, beginFullSuperStation, endFullSuperStation, endTransitionStation, rate, pivotPointIdx, beginTransitionType, beginL1, beginL2, endTransitionType, endL1, endL2);
   return superelevation;
}

Superelevation::Superelevation()
{
   m_pImpl = std::make_unique<SuperelevationImpl>();
}

Superelevation::Superelevation(const Superelevation& superelevation)
{
   m_pImpl = std::make_unique<SuperelevationImpl>(*superelevation.m_pImpl);

   // The default constructor of the implementation class copies the surface data member.
   // A newly created superelevation object should not be associated with a surface,
   // so set the surface to nullptr
   m_pImpl->SetSurface(std::shared_ptr<Surface>(nullptr));
}

Superelevation::~Superelevation() = default; // when using the PIMPL idiom, this is how we have to define the destructor in order to keep the compiler happy

void Superelevation::SetSurface(std::weak_ptr<const Surface> surface)
{
   m_pImpl->SetSurface(surface);
}

std::shared_ptr<const Surface> Superelevation::GetSurface() const
{
   return m_pImpl->GetSurface();
}

void Superelevation::Init(const Station& beginTransitionStation, const Station& beginFullSuperStation, const Station& endFullSuperStation, const Station& endTransitionStation,
   Float64 rate, IndexType pivotPointIdx, TransitionType beginTransitionType, Float64 beginL1, Float64 beginL2, TransitionType endTransitionType, Float64 endL1, Float64 endL2)
{
   m_pImpl->Init(beginTransitionStation, beginFullSuperStation, endFullSuperStation, endTransitionStation,
      rate, pivotPointIdx, beginTransitionType, beginL1, beginL2, endTransitionType, endL1, endL2);
}

void Superelevation::SetBeginTransition(const Station& beginTrasitionStation)
{
   m_pImpl->SetBeginTransition(beginTrasitionStation);
}

const Station& Superelevation::GetBeginTransition() const
{
   return m_pImpl->GetBeginTransition();
}

void Superelevation::SetBeginFullSuperelevation(const Station& beginFullSuperStation)
{
   m_pImpl->SetBeginFullSuperelevation(beginFullSuperStation);
}

const Station& Superelevation::GetBeginFullSuperelevation() const
{
   return m_pImpl->GetBeginFullSuperelevation();
}

void Superelevation::SetEndFullSuperelevation(const Station& endFullSuperStation)
{
   m_pImpl->SetEndFullSuperelevation(endFullSuperStation);
}

const Station& Superelevation::GetEndFullSuperelevation() const
{
   return m_pImpl->GetEndFullSuperelevation();
}

void Superelevation::SetEndTransition(const Station& endTransitionStation)
{
   m_pImpl->SetEndTransition(endTransitionStation);
}

const Station& Superelevation::GetEndTransition() const
{
   return m_pImpl->GetEndTransition();
}

void Superelevation::SetRate(Float64 rate)
{
   m_pImpl->SetRate(rate);
}

Float64 Superelevation::GetRate() const
{
   return m_pImpl->GetRate();
}

void Superelevation::SetPivotPoint(IndexType pivotPointIdx)
{
   m_pImpl->SetPivotPoint(pivotPointIdx);
}

IndexType Superelevation::GetPivotPoint() const
{
   return m_pImpl->GetPivotPoint();
}

void Superelevation::SetBeginTransitionType(TransitionType type)
{
   m_pImpl->SetBeginTransitionType(type);
}

Superelevation::TransitionType Superelevation::GetBeginTransitionType() const
{
   return m_pImpl->GetBeginTransitionType();
}

void Superelevation::SetBeginTransitionParameters(Float64 l1, Float64 l2)
{
   m_pImpl->SetBeginTransitionParameters(l1, l2);
}

std::pair<Float64,Float64> Superelevation::GetBeginTransitionParameters() const
{
   return m_pImpl->GetBeginTransitionParameters();
}

void Superelevation::SetEndTransitionType(TransitionType type)
{
   return m_pImpl->SetEndTransitionType(type);
}

Superelevation::TransitionType Superelevation::GetEndTransitionType() const
{
   return m_pImpl->GetEndTransitionType();
}

void Superelevation::SetEndTransitionParameters(Float64 l1, Float64 l2)
{
   m_pImpl->SetEndTransitionParameters(l1, l2);
}

std::pair<Float64, Float64> Superelevation::GetEndTransitionParameters() const
{
   return m_pImpl->GetEndTransitionParameters();
}

Float64 Superelevation::GetSlope(const Station& station, Float64 templateSlope) const
{
   return m_pImpl->GetSlope(station, templateSlope);
}
