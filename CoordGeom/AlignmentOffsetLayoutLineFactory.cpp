///////////////////////////////////////////////////////////////////////
// CoordGeom - Coordinate Geometry Library
// Copyright © 1999-2025  Washington State Department of Transportation
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
#include <CoordGeom/AlignmentOffsetLayoutLineFactory.h>
#include <CoordGeom/BridgeFramingGeometry.h>
#include <CoordGeom/Alignment.h>

using namespace WBFL::COGO;

AlignmentOffsetLayoutLineFactory::AlignmentOffsetLayoutLineFactory(IDType alignmentID, IDType firstLineID, IDType idIncrement, IndexType nLayoutLines, Float64 offset, Float64 offsetIncrement)
{
   SetLayoutLineParameters(alignmentID, firstLineID, idIncrement, nLayoutLines, offset, offsetIncrement);
}

void AlignmentOffsetLayoutLineFactory::SetLayoutLineParameters(IDType alignmentID, IDType firstLineID, IDType idIncrement, IndexType nLayoutLines, Float64 offset, Float64 offsetIncrement)
{
   m_AlignmentID = alignmentID;
   m_ID = firstLineID;
   m_IDInc = idIncrement;
   m_nLayoutLines = nLayoutLines;
   m_Offset = offset;
   m_OffsetInc = offsetIncrement;
}

std::tuple<IDType, IDType, IDType, IndexType, Float64, Float64> AlignmentOffsetLayoutLineFactory::GetLayoutLineParameters() const
{
   return std::make_tuple(m_AlignmentID, m_ID, m_IDInc, m_nLayoutLines, m_Offset, m_OffsetInc);
}

void AlignmentOffsetLayoutLineFactory::SetAlignmentID(IDType id)
{
   m_AlignmentID = id;
}

IDType AlignmentOffsetLayoutLineFactory::GetAlignmentID() const
{
   return m_AlignmentID;
}

void AlignmentOffsetLayoutLineFactory::SetLayoutLineID(IDType id)
{
   m_ID = id;
}

IDType AlignmentOffsetLayoutLineFactory::GetLayoutLineID() const
{
   return m_ID;
}

void AlignmentOffsetLayoutLineFactory::SetLayoutLineIDIncrement(IDType idIncrement)
{
   m_IDInc = idIncrement;
}

IDType AlignmentOffsetLayoutLineFactory::GetLayoutLineIDIncrement() const
{
   return m_IDInc;
}

void AlignmentOffsetLayoutLineFactory::SetLayoutLineCount(IndexType nLayoutLines)
{
   m_nLayoutLines = nLayoutLines;
}

IndexType AlignmentOffsetLayoutLineFactory::GetLayoutLineCount() const
{
   return m_nLayoutLines;
}

void AlignmentOffsetLayoutLineFactory::SetOffset(Float64 offset)
{
   m_Offset = offset;
}

Float64 AlignmentOffsetLayoutLineFactory::GetOffset() const
{
   return m_Offset;
}

void AlignmentOffsetLayoutLineFactory::SetOffsetIncrement(Float64 increment)
{
   m_OffsetInc = increment;
}

Float64 AlignmentOffsetLayoutLineFactory::GetOffsetIncrement() const
{
   return m_OffsetInc;
}

std::vector<std::pair<IDType,std::shared_ptr<Path>>> AlignmentOffsetLayoutLineFactory::Create(std::shared_ptr<const BridgeFramingGeometry> bridge) const
{
   PRECONDITION(m_AlignmentID != INVALID_ID);
   PRECONDITION(m_ID != INVALID_ID);

   std::vector<std::pair<IDType, std::shared_ptr<Path>>> vPaths;

   auto alignment = bridge->GetAlignment(m_AlignmentID);
   for (IndexType idx = 0; idx < m_nLayoutLines; idx++)
   {
      IDType lineID = m_ID + idx * m_IDInc;
      Float64 offset = m_Offset + idx * m_OffsetInc;

      auto path = alignment->CreateOffsetPath(offset);
      vPaths.emplace_back(lineID, path);
   }

   return vPaths;
}
