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

#if defined _UNITTEST
#include <CoordGeom/Alignment.h>
bool Superelevation::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("Superelevation");

   auto alignment = Alignment::Create();
   auto profile = Profile::Create();
   alignment->AddProfile(0, profile);
   auto surface = Surface::Create();
   profile->AddSurface(0, surface);

   auto super = Superelevation::Create();
   surface->AddSuperelevation(super);


   // Check default values
   TRY_TESTME(IsEqual(super->GetBeginTransition().GetValue(), 0.0));
   TRY_TESTME(super->GetBeginTransition().GetStationZoneIndex() == INVALID_INDEX);

   TRY_TESTME(IsEqual(super->GetBeginFullSuperelevation().GetValue(), 0.0));
   TRY_TESTME(super->GetBeginFullSuperelevation().GetStationZoneIndex() == INVALID_INDEX);

   TRY_TESTME(IsEqual(super->GetEndFullSuperelevation().GetValue(), 0.0));
   TRY_TESTME(super->GetEndFullSuperelevation().GetStationZoneIndex() == INVALID_INDEX);

   TRY_TESTME(IsEqual(super->GetEndTransition().GetValue(), 0.0));
   TRY_TESTME(super->GetEndTransition().GetStationZoneIndex() == INVALID_INDEX);

   TRY_TESTME(super->GetBeginTransitionType() == TransitionType::Linear);
   TRY_TESTME(super->GetEndTransitionType() == TransitionType::Linear);

   Float64 l1, l2;
   std::tie(l1,l2) = super->GetBeginTransitionParameters();
   TRY_TESTME(IsZero(l1) && IsZero(l2));

   std::tie(l1,l2) = super->GetEndTransitionParameters();
   TRY_TESTME(IsZero(l1) && IsZero(l2));

   // Setup some real parameters
   super->Init(500, 550, 1550, 1600, 0.06, 0);

   TRY_TESTME(IsEqual(super->GetSlope(400, -0.02), -0.02)); // before super
   TRY_TESTME(IsEqual(super->GetSlope(525, -0.02), 0.02)); // half-way through begin transition
   TRY_TESTME(IsEqual(super->GetSlope(1000, -0.02), 0.06)); // in full super
   TRY_TESTME(IsEqual(super->GetSlope(1575, -0.02), 0.02)); // half-way through end transition
   TRY_TESTME(IsEqual(super->GetSlope(1800, -0.02), -0.02)); // after super

   super->SetBeginTransitionType(TransitionType::Parabolic);
   super->SetBeginTransitionParameters(25, 25);
   super->SetEndTransitionType(TransitionType::Parabolic);
   super->SetEndTransitionParameters(25, 25);

   TRY_TESTME(IsEqual(super->GetSlope(400, -0.02), -0.02)); // before super
   TRY_TESTME(IsEqual(super->GetSlope(520, -0.02), 0.0056)); // 5 before half-way through begin transition
   TRY_TESTME(IsEqual(super->GetSlope(525, -0.02), 0.02)); // half-way through begin transition
   TRY_TESTME(IsEqual(super->GetSlope(530, -0.02), 0.0344)); // 5 after half-way through begin transition
   TRY_TESTME(IsEqual(super->GetSlope(1000, -0.02), 0.06)); // in full super
   TRY_TESTME(IsEqual(super->GetSlope(1570, -0.02), 0.0344)); // 5 before half-way through end transition
   TRY_TESTME(IsEqual(super->GetSlope(1575, -0.02), 0.02)); // half-way through end transition
   TRY_TESTME(IsEqual(super->GetSlope(1580, -0.02), 0.0056)); // 5 after half-way through end transition
   TRY_TESTME(IsEqual(super->GetSlope(1800, -0.02), -0.02)); // after super

   TESTME_EPILOG("Superelevation");
}
#endif // _UNITTEST


