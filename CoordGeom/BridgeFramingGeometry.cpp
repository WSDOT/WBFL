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
#include <CoordGeom/BridgeFramingGeometry.h>
#include <CoordGeom/Alignment.h>
#include <CoordGeom/PierLineFactory.h>
#include <CoordGeom/LayoutLineFactory.h>
#include <CoordGeom/GirderLineFactory.h>
#include <CoordGeom/DiaphragmLineFactory.h>
#include <CoordGeom/DeckBoundaryFactory.h>
#include <CoordGeom/XCoordGeom.h>

using namespace WBFL::COGO;



BridgeFramingGeometry::BridgeFramingGeometry(IDType bridgeAlignmentID, std::shared_ptr<const Alignment> alignment) :
   m_BridgeAlignmentID(bridgeAlignmentID)
{
   AddAlignment(bridgeAlignmentID, alignment);
}

BridgeFramingGeometry::BridgeFramingGeometry(IDType bridgeAlignmentID, const std::vector<std::pair<IDType,std::shared_ptr<const Alignment>>>& alignments,
   std::shared_ptr<LayoutLineFactory> layoutLineFactory, std::shared_ptr<PierLineFactory> pierLineFactory, std::shared_ptr<GirderLineFactory> girderLineFactory,
   std::shared_ptr<DiaphragmLineFactory> diaphragmLineFactory, std::shared_ptr<DeckBoundaryFactory> deckBoundaryFactory) :
   m_BridgeAlignmentID(bridgeAlignmentID)
{
   for (const auto& alignment : alignments)
   {
      AddAlignment(alignment.first, alignment.second);
   }

   m_LayoutLineFactory->AddFactory(layoutLineFactory);
   m_PierLineFactory->AddFactory(pierLineFactory);
   m_GirderLineFactory->AddFactory(girderLineFactory);
   m_DiaphragmLineFactory->AddFactory(diaphragmLineFactory);
   m_DeckBoundaryFactory = deckBoundaryFactory;
}

std::shared_ptr<BridgeFramingGeometry> BridgeFramingGeometry::Create()
{
   return std::shared_ptr<BridgeFramingGeometry>(new BridgeFramingGeometry());
}

std::shared_ptr<BridgeFramingGeometry> BridgeFramingGeometry::Create(IDType bridgeAlignmentID, std::shared_ptr<const Alignment> alignment)
{
   return std::shared_ptr<BridgeFramingGeometry>(new BridgeFramingGeometry(bridgeAlignmentID, alignment));
}

std::shared_ptr<BridgeFramingGeometry> BridgeFramingGeometry::Create(IDType bridgeAlignmentID, const std::vector<std::pair<IDType, std::shared_ptr<const Alignment>>>& alignments,
   std::shared_ptr<LayoutLineFactory> layoutLineFactory, std::shared_ptr<PierLineFactory> pierLineFactory, std::shared_ptr<GirderLineFactory> girderLineFactory,
   std::shared_ptr<DiaphragmLineFactory> diaphragmLineFactory, std::shared_ptr<DeckBoundaryFactory> deckBoundaryFactory)
{
   return std::shared_ptr<BridgeFramingGeometry>(new BridgeFramingGeometry(bridgeAlignmentID, alignments,
      std::move(layoutLineFactory), std::move(pierLineFactory), std::move(girderLineFactory),std::move(diaphragmLineFactory),std::move(deckBoundaryFactory)));
}

void BridgeFramingGeometry::AddAlignment(IDType alignmentID, std::shared_ptr<const Alignment> alignment)
{
   m_Alignments.emplace(alignmentID, alignment);
   InvalidateState(All); // all of the geometry depends on alignments so it must all be recomputed
}

std::shared_ptr<const Alignment> BridgeFramingGeometry::GetAlignment(IDType alignmentID) const
{
   auto found = m_Alignments.find(alignmentID);
   if (found == m_Alignments.end())
   {
      THROW_COGO(WBFL_COGO_E_INVALIDARG);
   }

   return found->second;
}

std::shared_ptr<const Alignment> BridgeFramingGeometry::GetBridgeAlignment() const
{
   return GetAlignment(m_BridgeAlignmentID);
}

std::shared_ptr<const Path> BridgeFramingGeometry::GetBridgeLine() const
{
   if (m_BridgeLine == nullptr)
   {
      UpdateBridgeLine();
   }

   return m_BridgeLine;
}

void BridgeFramingGeometry::SetBridgeAlignmentID(IDType bridgeAlignemntID)
{
   m_BridgeAlignmentID = bridgeAlignemntID;
}

IDType BridgeFramingGeometry::GetBridgeAlignmentID() const
{
   return m_BridgeAlignmentID;
}

void BridgeFramingGeometry::SetProfileID(IDType profileID)
{
   m_ProfileID = profileID;
}

IDType BridgeFramingGeometry::GetProfileID() const
{
   return m_ProfileID;
}

void BridgeFramingGeometry::SetSurfaceID(IDType surfaceID)
{
   m_SurfaceID = surfaceID;
}

IDType BridgeFramingGeometry::GetSurfaceID() const
{
   return m_SurfaceID;
}

void BridgeFramingGeometry::SetBridgeLineOffset(Float64 offset)
{
   m_BridgeLineOffset = offset;
   m_BridgeLine.reset(); // this invalidates the bridge line
   InvalidateState(All); // all of the geometry depends on alignments so it must all be recomputed
}

Float64 BridgeFramingGeometry::GetBridgeLineOffset() const
{
   return m_BridgeLineOffset;
}

void BridgeFramingGeometry::AddLayoutLineFactory(std::shared_ptr<LayoutLineFactory> factory)
{
   m_LayoutLineFactory->AddFactory(factory);
   InvalidateState(LayoutLineState);
}

void BridgeFramingGeometry::AddPierLineFactory(std::shared_ptr<PierLineFactory> factory)
{
   m_PierLineFactory->AddFactory(factory);
   InvalidateState(PierLineState);
}

void BridgeFramingGeometry::AddGirderLineFactory(std::shared_ptr<GirderLineFactory> factory)
{
   m_GirderLineFactory->AddFactory(factory);
   InvalidateState(GirderLineState);
}

void BridgeFramingGeometry::AddDiaphragmLineFactory(std::shared_ptr<DiaphragmLineFactory> factory)
{
   m_DiaphragmLineFactory->AddFactory(factory);
   InvalidateState(DiaphragmLineState);
}

void BridgeFramingGeometry::SetDeckBoundaryFactory(std::shared_ptr<DeckBoundaryFactory> factory)
{
   m_DeckBoundaryFactory = factory;
   InvalidateState(DeckBoundaryState);
}

void BridgeFramingGeometry::InvalidateState(Int8 state) const
{
   m_CurrentState = min(m_CurrentState, max(All,state - 1));
}

void BridgeFramingGeometry::ValidateState(Int8 state) const
{
   if (state <= m_CurrentState) return; // already up to date - nothing to do

   if (m_CurrentState < PierLineState)
   {
      m_PierLines = m_PierLineFactory->Create(shared_from_this());
      auto bridge_alignment = GetBridgeAlignment();
      std::sort(m_PierLines.begin(), m_PierLines.end(), [bridge_alignment](auto& pierline1, auto& pierline2) {return bridge_alignment->CompareStations(pierline1->GetStation(), pierline2->GetStation()) == 1; });
      IndexType idx = 0;
      for (auto& pier_line : m_PierLines)
      {
         pier_line->SetIndex(idx++);
      }

      m_CurrentState = PierLineState;
   }

   if (m_CurrentState < LayoutLineState)
   {
      m_LayoutLines = m_LayoutLineFactory->Create(shared_from_this());
      m_CurrentState = LayoutLineState;
   }

   if (m_CurrentState < GirderLineState)
   {
      m_GirderLines = m_GirderLineFactory->Create(shared_from_this());
      m_CurrentState = GirderLineState;
   }

   if (m_CurrentState < DiaphragmLineState)
   {
      m_DiaphragmLines = m_DiaphragmLineFactory->Create(shared_from_this());
      m_CurrentState = DiaphragmLineState;
   }

   if (m_CurrentState < DeckBoundaryState)
   {
      if (m_DeckBoundaryFactory) m_DeckBoundary = m_DeckBoundaryFactory->Create(shared_from_this());
      m_CurrentState = DeckBoundaryState;
   }
}

std::shared_ptr<const Path> BridgeFramingGeometry::FindLayoutLine(IDType id) const
{
   ValidateState(LayoutLineState);

   for (const auto& layout_line_record : m_LayoutLines)
   {
      if (layout_line_record.first == id)
         return layout_line_record.second;
   }

   return std::shared_ptr<const Path>();
}

IndexType BridgeFramingGeometry::GetLayoutLineCount() const
{
   ValidateState(LayoutLineState);

   return m_LayoutLines.size();
}

std::shared_ptr<const Path> BridgeFramingGeometry::GetLayoutLine(IndexType idx) const
{
   ValidateState(LayoutLineState);

   return m_LayoutLines[idx].second;
}

IndexType BridgeFramingGeometry::GetPierLineCount() const
{
   ValidateState(PierLineState);

   return m_PierLines.size();
}
std::shared_ptr<const PierLine> BridgeFramingGeometry::GetPierLine(PierIndexType idx) const
{
   ValidateState(PierLineState);

   return m_PierLines[idx];
}

std::shared_ptr<const PierLine> BridgeFramingGeometry::FindPierLine(PierIDType id) const
{
   ValidateState(PierLineState);

   for (auto& p : m_PierLines)
   {
      if (p->GetID() == id)
         return p;
   }

   return std::shared_ptr<PierLine>();
}

IndexType BridgeFramingGeometry::GetGirderLineCount() const
{
   ValidateState(GirderLineState);

   return m_GirderLines.size();
}

std::shared_ptr<const GirderLine> BridgeFramingGeometry::FindGirderLine(IDType id) const
{
   ValidateState(GirderLineState);

   for (const auto& girder_line : m_GirderLines)
   {
      if (girder_line->GetID() == id)
         return girder_line;
   }

   return std::shared_ptr<const GirderLine>();
}

std::shared_ptr<const GirderLine> BridgeFramingGeometry::GetGirderLine(IndexType idx) const
{
   ValidateState(GirderLineState);

   return m_GirderLines[idx];
}

IndexType BridgeFramingGeometry::GetDiaphragmLineCount() const
{
   ValidateState(DiaphragmLineState);

   return m_DiaphragmLines.size();
}

std::shared_ptr<const DiaphragmLine> BridgeFramingGeometry::FindDiaphragmLine(IDType id) const
{
   ValidateState(DiaphragmLineState);

   for (const auto& diaphragm_line : m_DiaphragmLines)
   {
      if (diaphragm_line->GetID() == id)
         return diaphragm_line;
   }

   return std::shared_ptr<const DiaphragmLine>();
}

std::shared_ptr<const DiaphragmLine> BridgeFramingGeometry::GetDiaphragmLine(IndexType idx) const
{
   ValidateState(DiaphragmLineState);

   return m_DiaphragmLines[idx];
}

std::shared_ptr<const DeckBoundary> BridgeFramingGeometry::GetDeckBoundary() const
{
   ValidateState(DeckBoundaryState);

   return m_DeckBoundary;
}

void BridgeFramingGeometry::UpdateBridgeLine() const
{
   auto alignment = GetBridgeAlignment();
   m_BridgeLine = alignment->CreateOffsetPath(m_BridgeLineOffset);
}

#if defined _UNITTEST
#include "Testing/TestBridgeFramingGeometry.h"
bool BridgeFramingGeometry::TestMe(WBFL::Debug::Log& rlog)
{
   TESTME_PROLOGUE("BridgeFramingGeometry");
   TRY_TESTME(CTestBridgeFramingGeometry::Test(rlog));
   TESTME_EPILOG("BridgeFramingGeometry");
}
#endif // _UNITTEST


